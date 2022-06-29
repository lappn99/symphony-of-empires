// Symphony of Empires
// Copyright (C) 2021, Symphony of Empires contributors
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// ----------------------------------------------------------------------------
// Name:
//      nation.cpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#include <cassert>

#include "eng3d/log.hpp"

#include "nation.hpp"
#include "technology.hpp"
#include "province.hpp"
#include "ideology.hpp"
#include "world.hpp"

//
// Nation
//

// Declare war
/// @todo Make some form of "WarParticipationRequest" so we don't force allies to join
// and we also make sure betrayals are possible
void Nation::declare_war(Nation& nation, std::vector<TreatyClause::BaseClause*> clauses) {
    World& world = World::get_instance();
    auto* war = new War();

    Eng3D::Log::debug("game", ref_name + " has declared war on " + nation.ref_name);

    war->wargoals = clauses;

    // Recollect offenders
    // - Those who are allied to us
    for(Nation::Id i = 0; i < world.nations.size(); i++) {
        if(&world.nations[i] == this || &world.nations[i] == &nation) continue;

        const auto& relation = world.get_relation(i, world.get_id(*this));
        if(relation.has_alliance || world.nations[i].puppet_master == this)
            war->attackers.push_back(&world.nations[i]);
    }
    war->attackers.push_back(this);

    Eng3D::Log::debug("game", "Attackers");
    for(const auto& attacker : war->attackers)
        Eng3D::Log::debug("game", attacker->ref_name.get_string());

    // Recollect defenders
    // - Those who are on a defensive pact with the target
    // - Those who are allied with the target
    for(Nation::Id i = 0; i < world.nations.size(); i++) {
        if(&world.nations[i] == this || &world.nations[i] == &nation) continue;
        const auto& relation = world.get_relation(i, world.get_id(nation));
        if(relation.has_alliance || relation.has_defensive_pact || world.nations[i].puppet_master == &nation)
            war->attackers.push_back(&world.nations[i]);
    }
    war->defenders.push_back(&nation);

    // Attackers are at war with the defenders
    for(auto attacker : war->attackers) {
        for(auto defender : war->defenders) {
            /// @todo A better way to make sure these two nations don't equal
            if(attacker == defender) continue;
            assert(attacker != defender);
            if(attacker->puppet_master == defender)
                attacker->puppet_master = nullptr;
            else if(defender->puppet_master == attacker)
                defender->puppet_master = nullptr;
            auto& relation = world.get_relation(world.get_id(*defender), world.get_id(*attacker));
            // Declare war
            relation.has_war = true;
            relation.has_alliance = false;
            relation.has_defensive_pact = false;
            relation.relation = -200.f;
        }
    }

    Eng3D::Log::debug("game", "Defenders");
    for(const auto& defender : war->defenders)
        Eng3D::Log::debug("game", defender->ref_name.get_string());
    war->name = "War of " + this->name + " against " + nation.name;
    Eng3D::Log::debug("game", war->name.get_string());
    world.insert(*war);
}

bool Nation::is_ally(const Nation& nation) const {
    const World& world = World::get_instance();
    const auto& relation = world.get_relation(world.get_id(*this), world.get_id(nation));
    if(relation.has_war) return false;
    return true;
}

bool Nation::is_enemy(const Nation& nation) const {
    const World& world = World::get_instance();
    const auto& relation = world.get_relation(world.get_id(*this), world.get_id(nation));
    if(relation.has_war) return true;
    return false;
}

// Whetever the nation exists at all - we cannot add nations in-game so we just check
// if the nation "exists" at all, this means that it has a presence and a goverment
// must own atleast 1 province
bool Nation::exists() const {
    return !(controlled_provinces.empty());
}

inline void Nation::do_diplomacy() {
    /// @todo Fix this formula which is currently broken
    //diplomatic_timer = std::max((60 * 48) - std::min(10.f * 48.f, prestige / 100.f), 4.f);
    diplomatic_timer = 48;
}

inline bool Nation::can_do_diplomacy() const {
    return (diplomatic_timer == 0);
}

void Nation::increase_relation(Nation& target) {
    World& world = World::get_instance();
    auto& relation = world.get_relation(world.get_id(*this), world.get_id(target));

    relation.relation += 5.f;
    Eng3D::Log::debug("game", ref_name + " increases relations with " + target.ref_name);
    this->do_diplomacy();
}

void Nation::decrease_relation(Nation& target) {
    World& world = World::get_instance();
    auto& relation = world.get_relation(world.get_id(*this), world.get_id(target));

    relation.relation -= 5.f;
    Eng3D::Log::debug("game", ref_name + " decreases relations with " + target.ref_name);
    this->do_diplomacy();
}

// Automatically relocates the capital of a nation to another province
// Use this when a treaty makes a nation lose it's capital
void Nation::auto_relocate_capital() {
    const World& world = World::get_instance();
    auto best_candidate = std::max_element(owned_provinces.begin(), owned_provinces.end(), [&world](const auto& lhs, const auto& rhs) {
        return world.provinces[lhs].total_pops() < world.provinces[rhs].total_pops();
    });
    capital_id = *best_candidate;
}

// Enacts a policy on a nation
// @return false if policy draft failed to be applied, true if policy passed and is in-effect
void Nation::set_policy(const Policies& policies) {
    // No parliament? No referendum
    if(current_policy.legislative_parliament != true) {
        this->current_policy = policies;
        Eng3D::Log::debug("game", "Parliament-less policy passed!");
    }

    unsigned int approvals = 0, disapprovals = 0;
    std::vector<Pop*> disapprovers, approvers;
    for(const auto province_id : owned_provinces) {
        auto& province = World::get_instance().provinces[province_id];
        for(auto& pop : province.pops) {
            const Policies& pop_policies = pop.get_ideology().policies;
            // To "cheese it up" we mix some ideologies of the people, randomly
            for(Ideology::Id i = 0; i < World::get_instance().ideologies.size(); i++) {
                pop.ideology_approval[i] += std::fmod(std::rand() / 1000.f, current_policy.difference(pop_policies));
                pop.ideology_approval[i] = glm::clamp<float>(pop.ideology_approval[i], -1.f, 1.f); // Clamp
            }

            // Must have the minimum required social value
            // the min-social-value is taken from the new enacted policy
            if(pop.type->social_value < policies.min_sv_for_parliament) continue;
            // Disapproval of old (current) policy
            const int old_disapproval = current_policy.difference(pop_policies);
            // Dissaproval of new policy
            const int new_disapproval = policies.difference(pop_policies);
            if(new_disapproval < old_disapproval) {
                approvals += pop.size;
                disapprovers.push_back(&pop);
            } else {
                disapprovals += pop.size;
                approvers.push_back(&pop);
            }
        }
    }

    // Policy is enacted and passed parliament
    if(approvals > disapprovals) {
        // Set new policy
        this->current_policy = policies;
        // All who agreed are happy
        for(auto& pop : approvers)
            pop->militancy *= 0.8f;
        // All who disagreed are angered
        for(auto& pop : disapprovers) {
            pop->militancy += 0.2f;
            pop->militancy *= 1.2f;
        }
        Eng3D::Log::debug("game", "New enacted policy passed parliament!");
    }
    // Legislation does not make it into the official law
    else {
        // All people who agreed gets angered
        for(auto& pop : disapprovers)
            pop->militancy *= 0.8f;
        // All people who disagreed gets happy
        for(auto& pop : approvers) {
            pop->militancy += 0.2f;
            pop->militancy *= 1.2f;
        }
        Eng3D::Log::debug("game", "New enacted policy did not made it into the parliament!");
    }
}

// Checks if a POP is part of one of our accepted cultures
bool Nation::is_accepted_culture(const Pop& pop) const {
    return is_accepted_culture(*pop.culture);
}
// Checks if a CULTURE is part of one of our accepted cultures
bool Nation::is_accepted_culture(const Culture& culture) const {
    return culture_discrim[World::get_instance().get_id(culture)] >= 0.5f;
}

// Checks if a POP is part of one of our accepted religion
bool Nation::is_accepted_religion(const Pop& pop) const {
    return is_accepted_religion(*pop.religion);
}
// Checks if a RELIGION is part of one of our accepted relgion
bool Nation::is_accepted_religion(const Religion& religion) const {
    return religion_discrim[World::get_instance().get_id(religion)] >= 0.5f;
}

// Gets the total tax applied to a POP depending on their "wealth"
// (not exactly like that, more like by their type/status)
float Nation::get_tax(const Pop& pop) const {
    float base_tax = 1.f;

    if(!is_accepted_culture(pop) && !is_accepted_religion(pop)) {
        // Exterminate imposes a scale of 3(+1), which will be enough to drive off most POPs
        const int scale = 1 + current_policy.treatment;
        base_tax *= 2 * scale;
    }

    if(pop.type->social_value <= 1.f)
        return current_policy.poor_flat_tax * base_tax;
    // For the medium class
    else if(pop.type->social_value <= 2.f)
        return current_policy.med_flat_tax * base_tax;
    // For the high class
    else if(pop.type->social_value <= 3.f)
        return current_policy.rich_flat_tax * base_tax;
    return base_tax;
}

#include "client/game_state.hpp"
#include "client/map.hpp"
#include "client/map_render.hpp"
// Gives this nation a specified province (for example on a treaty)
void Nation::give_province(Province& province) {
    World& world = World::get_instance();
    this->control_province(province);
    if(province.owner_id != (Nation::Id)-1)
        world.nations[province.owner_id].owned_provinces.erase(province.get_id());
    owned_provinces.insert(world.get_id(province));
    province.owner_id = this->get_id();

    // Update the province changed
    world.province_manager.mark_province_owner_changed(province.get_id());
}

void Nation::control_province(Province& province) {
    World& world = World::get_instance();
    if(province.controller != nullptr)
        province.controller->controlled_provinces.erase(world.get_id(province));
    controlled_provinces.insert(world.get_id(province));
    province.controller = this;

    // Update the province changed
    world.province_manager.mark_province_control_changed(province.get_id());

    // Cancel the unit construction projects
    province.cancel_construction_project();
}

const NationClientHint& Nation::get_client_hint() const {
    return this->client_hints[g_world.get_id(*this->ideology)];
}

float Nation::get_research_points() const {
    float research = 0.f;
    for(const auto province_id : this->owned_provinces) {
        const auto& province = World::get_instance().provinces[province_id];
        for(const auto& pop : province.pops)
            research += pop.size * pop.literacy;
        if(research && !province.pops.empty())
            research /= province.pops.size();
    }
    return research / 100.f;
}

bool Nation::can_research(const Technology& technology) const {
    // Only military/navy technologies can actually be researched
    // or not? wink, wink ;)
    //if(tech->type != TechnologyType::MILITARY && tech->type != TechnologyType::NAVY) return false;

    // All required technologies for this one must be researched
    for(const auto& req_tech_id : technology.req_technologies) {
        if(research[req_tech_id] > 0.f) return false;
    }
    return true;
}

void Nation::change_research_focus(const Technology& technology) {
    // Can't have already researched it (it would be dumb to re-research
    if(!this->research[World::get_instance().get_id(technology)]) return;
    // Must be able to research it
    if(!this->can_research(technology)) return;
    this->focus_tech = const_cast<Technology*>(&technology);
}

std::vector<Nation*> Nation::get_allies() {
    World& world = World::get_instance();

    std::vector<Nation*> list;
    for(auto& nation : world.nations) {
        if(&nation == this) continue;
        const auto& relation = g_world.get_relation(world.get_id(*this), world.get_id(nation));
        if(relation.has_alliance)
            list.push_back(&nation);
    }
    return list;
}

/*float Nation::get_industry_output_rate() {
    for(const auto& p: techs) {

    }
}*/

float Nation::get_industry_output_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->industry_input_mod;
    return ((1.f));
}

float Nation::get_industry_input_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->industry_input_mod;
    return ((1.f));
}

float Nation::get_workers_needed_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->workers_needed_mod;
    return ((1.f));
}

float Nation::get_salary_paid_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->salary_paid_mod;
    return ((1.f));
}

float Nation::get_delivery_cost_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->delivery_cost_mod;
    return ((1.f));
}

float Nation::get_literacy_learn_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->literacy_learn_mod;
    return ((1.f));
}

float Nation::get_reproduction_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->reproduction_mod;
    return ((1.f));
}

float Nation::get_death_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->death_mod;
    return ((1.f));
}

float Nation::get_militancy_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->militancy_mod;
    return ((1.f));
}

float Nation::get_life_needs_met_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->life_needs_met_mod;
    return ((1.f));
}

float Nation::get_everyday_needs_met_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->everyday_needs_met_mod;
    return ((1.f));
}

float Nation::get_luxury_needs_met_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->luxury_needs_met_mod;
    return ((1.f));
}

float Nation::get_immigration_attraction_mod() {
    float c = 1.f;
    for(const auto& mod : modifiers)
        c += mod->immigration_attraction;
    return ((1.f));
}
