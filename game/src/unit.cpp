// Symphony of Empires
// Copyright (C) 2021, Symphony of Empires contributors
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ----------------------------------------------------------------------------
// Name:
//      unit.cpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#include <string>
#include <algorithm>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "eng3d/log.hpp"
#include "eng3d/utils.hpp"

#include "server/server_network.hpp"
#include "action.hpp"
#include "unit.hpp"
#include "province.hpp"
#include "world.hpp"

//
// Unit
//
void Unit::attack(Unit& enemy) {
    assert(this->is_valid());
    assert(enemy.is_valid());
    /// @todo Better attack algorithm

    // It's important that a size of zero nullifies the attack, this prevents the edge case
    // of 1 v 1 units that kill each other
    const float damage = (type->attack * static_cast<float>(this->size)) * this->morale * 0.08f;
    enemy.size -= glm::min<size_t>(enemy.size, damage);
}

glm::vec2 Unit::get_pos() const {
    assert(this->is_valid());
    const auto& world = World::get_instance();
    auto prov_id = this->province_id();
    auto& province = world.provinces[prov_id];
    return province.get_pos();
}

Province::Id Unit::province_id() const {
    assert(this->is_valid());
    // Don't know if this is cleaner than getting it from unit manager :thinking:
    const auto& world = World::get_instance();
    return world.unit_manager.unit_province[cached_id];
}

void Unit::set_target(const Province& province) {
    assert(this->is_valid());
    assert(this->target_province_id != this->province_id());
    assert(province.get_id() != this->province_id());
    assert(this->can_move());
    this->target_province_id = province.get_id();
    this->days_left_until_move = this->days_to_move_to(province);
}

void Unit::stop_movement() {
    this->target_province_id = Province::invalid();
    this->days_left_until_move = 0;
}

float Unit::days_to_move_to(const Province& _province) const {
    assert(this->is_valid());
    const auto& world = World::get_instance();
    auto& start_province = world.provinces[this->province_id()];
    auto& end_province = _province;

    const glm::vec2 world_size{ world.width, world.height };
    const auto distance = start_province.euclidean_distance(end_province, world_size, 100) * world.terrain_types[start_province.terrain_type_id].penalty * world.terrain_types[end_province.terrain_type_id].penalty;
    return distance;
}

bool Unit::update_movement(UnitManager& unit_manager) {
    if(Province::is_invalid(this->target_province_id)) return false;

    this->days_left_until_move--;
    if(this->days_left_until_move <= 0) {
        this->days_left_until_move = 0;
        unit_manager.move_unit(this->get_id(), this->target_province_id);
        this->target_province_id = Province::invalid();

        // Follow the path
        if(!this->path.empty()) {
            this->set_target(World::get_instance().provinces[this->path.back()]);
            this->path.pop_back();
        }
        return true;
    }
    return false;
}

/// @brief Fill in the relationship vectors for each nation
void UnitManager::init(World& world) {
    province_units.resize(world.provinces.size());
}

void UnitManager::add_unit(Unit unit, Province::Id unit_current_province) {
    Unit::Id id;
    if(free_unit_slots.empty()) {
        id = units.size();
        units.emplace_back(unit);
        unit_province.push_back(unit_current_province);
    } else {
        id = free_unit_slots.back();
        free_unit_slots.pop_back();
        units[id] = unit;
        unit_province[id] = unit_current_province;
    }
    units[id].cached_id = id;
    if(unit_current_province >= province_units.size())
        province_units.resize(unit_current_province + 1);
    province_units[unit_current_province].push_back(id);

    if(g_server != nullptr)
        /// @todo Obtain the cached ID of the newly added unit
        g_server->broadcast(Action::UnitAdd::form_packet(units[id]));
}

void UnitManager::remove_unit(Unit::Id unit_id) {
    if(g_server != nullptr)
        g_server->broadcast(Action::UnitRemove::form_packet(units[unit_id]));

    const auto current_province_id = unit_province[unit_id];
    Eng3D::fast_erase(province_units[current_province_id], unit_id);
    units[unit_id].cached_id = Unit::invalid();
    free_unit_slots.push_back(unit_id);
}

void UnitManager::move_unit(Unit::Id unit_id, Province::Id target_province_id) {
    assert(units[unit_id].can_move()); // Must be able to move to perform this...
    assert(unit_province[unit_id] != target_province_id); // Not setting to same province

    const auto current_province_id = unit_province[unit_id];
    Eng3D::fast_erase(province_units[current_province_id], unit_id);
    unit_province[unit_id] = target_province_id;
    province_units[target_province_id].push_back(unit_id);
    if(g_server != nullptr)
        g_server->broadcast(Action::UnitMove::form_packet(units[unit_id], World::get_instance().provinces[target_province_id]));
}

void Unit::set_owner(const Nation& nation)
{
    assert(Nation::is_valid(nation.get_id()));
    this->owner_id = nation.get_id();
}

/// @brief Checks if the unit can move (if it can set_province)
/// @return true 
/// @return false 
bool Unit::can_move() const {
    // Unit must not be on a battle
    return !(this->on_battle);
}

const std::vector<Province::Id> Unit::get_path() const {
    return path;
}

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include "eng3d/pathfind.hpp"
#include "province.hpp"
void Unit::set_path(const Province& target) {
    auto& world = World::get_instance();
    auto& nation = world.nations[this->owner_id];
    auto start_id = world.unit_manager.get_unit_current_province(this->get_id());
        this->path = Eng3D::Pathfind::get_path<Province::Id>(start_id, target.get_id(),
        /// @brief Calculates the neighbors for a given Tile. The neighbors are the 8 tiles around
        /// it, while taking into account the map bounds.
        [&world](Province::Id province_id) -> std::vector<Province::Id> {
            const auto& province = world.provinces[province_id];
            std::vector<Province::Id> result;
            result.resize(province.neighbour_ids.size(), 0);
            std::transform(province.neighbour_ids.cbegin(), province.neighbour_ids.cend(), result.begin(), [](const auto e) {
                return e;
            });
            return result;
        },
        /// @brief Euclidean distance calculation
        [&world](Province::Id province1_id, Province::Id province2_id) -> float {
            const auto& province1 = world.provinces[province1_id];
            const auto& province2 = world.provinces[province2_id];
            const glm::vec2 world_size{ world.width, world.height };
            auto get_sphere_coord = ([](const Province& province, glm::vec2 world_size) -> glm::vec3 {
                const glm::vec2 normalized_pos = province.get_pos() / world_size;
                glm::vec2 radiance_pos;
                radiance_pos.x = normalized_pos.x * 2.f * glm::pi<float>();
                radiance_pos.y = normalized_pos.y * glm::pi<float>();

                glm::vec3 sphere_position;
                sphere_position.x = glm::cos(radiance_pos.x) * glm::sin(radiance_pos.y);
                sphere_position.y = glm::sin(radiance_pos.x) * glm::sin(radiance_pos.y);
                sphere_position.z = glm::cos(radiance_pos.y);
                return sphere_position;
            });
            const auto sphere_coord1 = get_sphere_coord(province1, world_size);
            const auto sphere_coord2 = get_sphere_coord(province2, world_size);
            float cos_angle = glm::dot(sphere_coord1, sphere_coord2);
            float angle = glm::acos(cos_angle);
            float distance = angle / (2 * glm::pi<float>());
            return distance;
        });
    
    if(!this->path.empty() && this->path.back() == start_id)
        this->path.pop_back(); // Pop the start point
}

Province::Id Unit::get_target_province_id() const {
    return target_province_id;
}
