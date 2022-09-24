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
//      server/economy.cpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#include <algorithm>
#include <cstdio>
#include <tbb/blocked_range.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>
#include <tbb/combinable.h>
#include <glm/gtx/compatibility.hpp>

#include "eng3d/log.hpp"
#include "eng3d/serializer.hpp"
#include "eng3d/thread_pool.hpp"
#include "eng3d/rand.hpp"

#include "action.hpp"
#include "server/economy.hpp"
#include "world.hpp"
#include "io_impl.hpp"
#include "server/server_network.hpp"
#include "product.hpp"
#include "good.hpp"
#include "emigration.hpp"

#undef min
#undef max

// Visual Studio does not define ssize_t because it's a POSIX-only type
#ifdef _MSC_VER
typedef signed int ssize_t;
#endif

struct Market {
    Good::Id good;
    std::vector<float> prices;
    std::vector<float> supply;
    std::vector<float> demand;
    std::vector<float> global_demand;
    float total_reciprocal_price;
};

struct PopNeed {
    float life_needs_met;
    float everyday_needs_met;
    float budget;
};

struct NewUnit {
    Unit unit;
    Province::Id unit_province;
    NewUnit(Unit& _unit, Province::Id _unit_province) 
        : unit{_unit},
        unit_province{ _unit_province }
    {

    }
};

void militancy_update(World& world, Nation& nation) {
    for(const auto province_id : nation.controlled_provinces) {
        auto& province = world.provinces[province_id];
        for(auto& pop : province.pops) {
            float growth = pop.size * pop.life_needs_met * 0.1f;
            pop.size += static_cast<float>((int)growth);
            pop.militancy += 0.01f * -pop.life_needs_met;
            pop.ideology_approval[world.get_id(*world.nations[province.owner_id].ideology)] += pop.life_needs_met * 0.25f;
        }
    }

    // Total anger in population (global)
    float total_anger = 0.f;
    // Anger per ideology (how much we hate the current ideology)
    std::vector<float> ideology_anger(world.ideologies.size(), 0.f);
    const float coup_chances = nation.controlled_provinces.size() * 1000.f;
    auto rand = Eng3D::get_local_generator();
    for(const auto province_id : nation.controlled_provinces) {
        const auto& province = world.provinces[province_id];
        for(const auto& pop : province.pops) {
            /// @todo Ok, look, the justification is that educated people
            // almost never do coups - in comparasion to uneducated
            // peseants, rich people don't need to protest!
            const float anger = glm::max(pop.militancy, 0.001f);
            total_anger += anger;
            for(const auto& ideology : world.ideologies)
                ideology_anger[world.get_id(ideology)] += (pop.ideology_approval[world.get_id(ideology)] * anger) * (pop.size / 1000);
        }
    }

    // Rebellions!
    /// @todo Broadcast this event to other people, maybe a REBEL_UPRISE action with a list of uprising provinces?
    if(std::fmod(rand(), glm::max(1.f, coup_chances - total_anger)) == 0) {
        /// @todo This might cause multithreading problems
        std::scoped_lock lock(world.rebel_mutex);

        // Compile list of uprising provinces
        std::vector<Province*> uprising_provinces;
        for(const auto province_id : nation.owned_provinces) {
            auto& province = world.provinces[province_id];
            float province_anger = 0.f;
            float province_threshold = 0.f;
            for(const auto& pop : province.pops) {
                province_anger += pop.militancy;
                province_threshold += pop.literacy * pop.life_needs_met;
            }

            if(province_anger > province_threshold)
                uprising_provinces.push_back(&province);
        }

        // Nation 0 is always the rebel nation
        auto& rebel_nation = world.nations[0];
        // Make the most angry provinces revolt!
        std::vector<TreatyClause::BaseClause*> clauses;
        for(auto& province : uprising_provinces) {
            /// @todo We should make a copy of the `rebel` nation for every rebellion!!!
            /// @todo We should also give them an unique ideology!!!
            rebel_nation.control_province(*province);
            for(const auto unit_id : world.unit_manager.get_province_units(province->get_id())) {
                auto& unit = world.unit_manager.units[unit_id];
                /// @todo Does battles affect ownership of provinces?
                if(unit.on_battle) continue;
                unit.set_owner(rebel_nation);
                rebel_nation.control_province(world.provinces[world.unit_manager.get_unit_current_province(unit.get_id())]);
            }

            // Declare war seeking all provinces from the owner
            auto* cl = new TreatyClause::AnnexProvince();
            cl->provinces = uprising_provinces;
            cl->sender = &rebel_nation;
            cl->receiver = &nation;
            cl->type = TreatyClauseType::ANNEX_PROVINCES;
            clauses.push_back(cl);
            Eng3D::Log::debug("game", "Revolt on " + province->ref_name + " by " + rebel_nation.ideology->ref_name);
        }
        rebel_nation.declare_war(nation, clauses);
    }

    // Roll a dice! (more probability with more anger!)
    if(!std::fmod(rand(), glm::max(coup_chances, coup_chances - total_anger))) {
        // Choose the ideology with most "anger" (the one more probable to coup d'
        // etat) - angry radicals will surely throw off the current administration
        // while peaceful people wonq't
        const int idx = std::distance(ideology_anger.begin(), std::max_element(ideology_anger.begin(), ideology_anger.end()));
        // Ideology_anger and ideologies are mapped 1:1 - so we just pick up the associated ideology
        // Apply the policies of the ideology
        nation.current_policy = world.ideologies[idx].policies;
        // Switch ideologies of nation
        nation.ideology = &world.ideologies[idx];
        // People who are aligned to the ideology are VERY happy now
        for(const auto province_id : nation.owned_provinces) {
            auto& province = world.provinces[province_id];
            for(auto& pop : province.pops)
                pop.militancy = -50.f;
        }
        Eng3D::Log::debug("game", "Coup d' etat on " + nation.ref_name + " by " + nation.ideology->ref_name);
    }
}

constexpr float price_update_delay = 2;
constexpr float price_change_rate = 0.025f;
constexpr float base_price = 1.f;
constexpr float min_price = 0.01f;
constexpr float max_price = 10.f;
constexpr float epsilon = 0.001f;
constexpr float purchasing_change_rate = 1.f;
void economy_single_good_tick(World& world, const Market& market) {
    auto good_id = market.good;
    // Determine new prices
    for(Province::Id i = 0; i < world.provinces.size(); i++) {
        auto& province = world.provinces[i];
        auto& product = province.products[good_id];
        auto supply = market.supply[i] + epsilon;
        auto demand_in_state = market.global_demand[i] + epsilon;
        auto current_price = market.prices[i];
        auto new_price = current_price * demand_in_state / supply;
        new_price = glm::clamp<float>(new_price, base_price * min_price, base_price * max_price);
        auto state_price_delta = (std::lerp(current_price, new_price, price_change_rate) - current_price) / price_update_delay;
        product.price += state_price_delta;
    }
}

constexpr float production_scaling_speed_factor = 0.5f;
constexpr float scale_speed(float v) {
    return 1.f - production_scaling_speed_factor + production_scaling_speed_factor * v;
}

// Updates supply, demand, and set wages for workers
static void update_factory_production(World& world, Building& building, BuildingType& building_type, Province& province, float& pop_payment)
{
    if(building_type.output == nullptr || building.level == 0.f) return;

    // TODO add output modifier
    // Calculate outputs
    auto* output = building_type.output;
    auto& output_product = province.products[output->get_id()];
    auto output_amount = 1.f * building.production_scale;

    // TODO set min wages
    float min_wage = 1.f;

    // TODO set output depending on amount of workers
    float total_worker_pop = building.workers;
    min_wage = glm::max(min_wage, 0.0001f);

    // TODO add input modifier
    auto inputs_cost = 0.f;
    for(const auto& input : building_type.req_goods)
        inputs_cost += province.products[input.first->get_id()].price * input.second;
    inputs_cost *= building.production_scale;
    auto output_value = output_amount * output_product.price;
    auto profit = output_value - min_wage - inputs_cost;

    for(const auto& neighbour_id : province.neighbour_ids)
        world.provinces[neighbour_id].products[building_type.output->get_id()].supply += output_amount * 0.1f;
    output_product.supply += output_amount * 0.5f; // Increment supply of output

    for(const auto& input : building_type.req_goods) // Increase demand of inputs
        province.products[input.first->get_id()].demand += input.second; // * price ?
    
    if(profit <= 0) {
        if(output_value - inputs_cost > 0)
            pop_payment += (output_value - inputs_cost);
    } else {
        pop_payment += min_wage + profit * 0.2f * building.workers;
        // TODO pay profit to owner
    }

    // Rescale production
    // This is used to set how much the of the maximum capicity the factory produce
    building.production_scale = glm::clamp<float>(building.production_scale * scale_speed((float)output_value / (min_wage + inputs_cost)), 1.5f, 5.f);
}

// Update the factory employment
static void update_factories_employment(const World& world, Province& province, std::vector<float>& new_workers) {
    float unallocated_workers = 0.f;
    for(auto& pop : province.pops)
        if(world.pop_types[pop.type_id].group == PopGroup::LABORER)
            unallocated_workers += pop.size;
    
    // TODO set pop size to float ?

    // Sort factories by production scale, which is suppose to represent how profitable the factory is
    // Might be better to calculate how profitable it really is and use that instead
    std::vector<std::pair<size_t, float>> factories_by_profitability(province.buildings.size());
    for(Building::Id i = 0; i < province.buildings.size(); i++)
        factories_by_profitability[i] = std::pair<size_t, float>(i, province.buildings[i].production_scale);
    std::sort(std::begin(factories_by_profitability), std::end(factories_by_profitability), [](const auto& a, const auto& b) { return a.second > b.second; });

    // Cancel operations
    float is_operating = (province.controller_id == province.owner_id) ? 1.f : 0.f;
    // The most profitable factory gets to pick workers first
    for(const auto& factory_index : factories_by_profitability) {
        auto& building = province.buildings[factory_index.first];
        const auto& type = world.building_types[factory_index.first];
        auto factory_workers = building.level * type.num_req_workers * building.production_scale;
        auto allocated_workers = glm::min(factory_workers, unallocated_workers);
        // Average with how much the factory had before
        // Makes is more stable so everyone don't change workplace immediately
        new_workers[factory_index.first] = ((allocated_workers) / 16.0f + (building.workers * 15.0f) / 16.0f) * is_operating;
        unallocated_workers -= building.workers * is_operating;
    }
}

/// @brief Calculate the budget that we spend on each needs
void update_pop_needs(World& world, Province& province, std::vector<PopNeed>& pop_needs) {
    pop_needs.assign(province.pops.size(), PopNeed{});
    for(Pop::Id i = 0; i < province.pops.size(); i++) {
        auto& pop_need = pop_needs[i];
        auto& pop = province.pops[i];
        const auto& type = world.pop_types[pop.type_id];
        
        pop_need.life_needs_met = -0.01f;
        // Do basic needs
        {
            auto total_price = 0.f;
            for(Good::Id j = 0; j < world.goods.size(); j++)
                total_price += type.basic_needs_amount[j] * province.products[j].price;
            auto buying_factor = glm::clamp(pop_need.budget / total_price, 0.1f, 1.f);
            for(Good::Id j = 0; j < world.goods.size(); j++) {
                const auto amount = glm::clamp(type.basic_needs_amount[j] * buying_factor, 0.f, province.products[j].supply);
                province.products[j].demand += amount;
                province.products[j].supply -= amount;
            }
            pop_need.life_needs_met += buying_factor;
            pop_need.budget -= total_price;
        }

        pop_need.everyday_needs_met = -0.01f;
        // Do luxury needs
        // TODO proper calulcation with pops trying to optimize satifcation
        {
            auto total_price = 0.f;
            for(Good::Id j = 0; j < world.goods.size(); j++)
                total_price += type.luxury_needs_satisfaction[j] * province.products[j].price;
            auto buying_factor = glm::clamp(pop_need.budget / total_price, 0.1f, 1.f);
            for(Good::Id j = 0; j < world.goods.size(); j++) {
                const auto amount = glm::clamp(type.luxury_needs_satisfaction[j] * buying_factor, 0.f, province.products[j].supply);
                province.products[j].demand += amount;
                province.products[j].supply -= amount;
            }
            pop_need.everyday_needs_met += buying_factor;
            pop_need.budget -= total_price;
        }
    }
}

void Economy::do_tick(World& world, EconomyState& economy_state) {
    world.profiler.start("E-init");
    std::vector<Market> markets{ world.goods.size() };
    for(Good::Id good_id = 0; good_id < world.goods.size(); good_id++) {
        auto& market = markets[good_id];
        market.good = good_id;
    }
    tbb::parallel_for(tbb::blocked_range(markets.begin(), markets.end()), [&world](const auto& markets_range) {
        for(auto& market : markets_range) {
            market.prices.reserve(world.provinces.size());
            market.supply.reserve(world.provinces.size());
            market.demand.reserve(world.provinces.size());
            market.global_demand = std::vector(world.provinces.size(), 0.f);
            market.total_reciprocal_price = 0;
            for(const auto& province : world.provinces) {
                auto& product = province.products[market.good];
                market.demand[province.get_id()] = 0.f;
                market.prices[province.get_id()] = product.price;
                market.supply[province.get_id()] = product.supply;
                market.total_reciprocal_price += 1 / (product.price + epsilon);
            }
        }
    });
    world.profiler.stop("E-init");

    world.profiler.start("E-trade");
    if(economy_state.trade.trade_costs.empty())
        economy_state.trade.recalculate(world);
    auto& trade = economy_state.trade;

    std::vector<float> total_reciprocal_trade_costs(world.provinces.size(), 0.f);
    tbb::parallel_for((Province::Id)0, (Province::Id)world.provinces.size(), [&trade, &total_reciprocal_trade_costs](const auto province_id) {
        float total_reciprocal_trade_cost = 0;
        for(const auto other_province_id : trade.cost_eval)
            total_reciprocal_trade_cost += 1 / (trade.trade_costs[province_id][other_province_id] + epsilon);
        total_reciprocal_trade_costs[province_id] = total_reciprocal_trade_cost;
    });

    tbb::parallel_for(tbb::blocked_range(markets.begin(), markets.end()), [&world, &trade, &total_reciprocal_trade_costs](const auto& markets_range) {
        for(auto& market : markets_range) {
            for(const auto province_id : trade.cost_eval) {
                float reciprocal_price = 1 / (market.prices[province_id] + epsilon);
                float total_reciprocal_price = market.total_reciprocal_price;
                for(const auto other_province_id : trade.cost_eval) {
                    float reciprocal_trade_cost = 1 / (trade.trade_costs[province_id][other_province_id] + epsilon);
                    float reciprocal_cost = reciprocal_price + reciprocal_trade_cost;
                    float total_reciprocal_cost = total_reciprocal_price + total_reciprocal_trade_costs[other_province_id];
                    market.global_demand[province_id] += market.demand[other_province_id] * (reciprocal_cost / total_reciprocal_cost);
                }
            }
        }
    });
    world.profiler.stop("E-trade");

    world.profiler.start("E-good");
    tbb::parallel_for(tbb::blocked_range(markets.begin(), markets.end()), [&world](const auto& markets_range) {
        for(const auto& market : markets_range)
            economy_single_good_tick(world, market);
    });
    world.profiler.stop("E-good");

    world.profiler.start("E-big");
    tbb::combinable<tbb::concurrent_vector<NewUnit>> province_new_units;
    std::vector<std::vector<float>> buildings_new_worker(world.provinces.size());
    std::vector<std::vector<PopNeed>> pops_new_needs(world.provinces.size());
    tbb::parallel_for((Province::Id)0, (Province::Id)world.provinces.size(), [&world, &buildings_new_worker, &province_new_units, &pops_new_needs](const auto province_id) {
        auto& province = world.provinces[province_id];
        if(Nation::is_invalid(province.controller_id))
            return;

        float laborers_payment = 1.f;
        for(auto& building_type : world.building_types) {
            auto& building = province.buildings[building_type.get_id()];
            update_factory_production(world, building, building_type, province, laborers_payment);
        }

        auto& new_needs = pops_new_needs[province_id];
        new_needs.assign(province.pops.size(), PopNeed{});
        for(Pop::Id i = 0; i < province.pops.size(); i++) {
            auto& pop = province.pops[i];
            new_needs[i].budget = pop.budget;
        }

        float laborers_amount = 0.f;
        for(auto& pop : province.pops)
            if(world.pop_types[pop.type_id].group == PopGroup::LABORER)
                laborers_amount += pop.size;
        for(Pop::Id i = 0; i < province.pops.size(); i++) {
            const auto& pop = province.pops[i];
            if(world.pop_types[pop.type_id].group == PopGroup::LABORER)
                new_needs[i].budget += (pop.size / laborers_amount) * laborers_payment;
        }

        std::vector<float>& new_workers = buildings_new_worker[province_id];
        new_workers.assign(world.building_types.size(), 0.f);
        update_factories_employment(world, province, new_workers);
        update_pop_needs(world, province, new_needs);
        for(auto& building : province.buildings) {
            // There must not be conflict ongoing otherwise they wont be able to build shit
            if(province.controller_id == province.owner_id && building.working_unit_type != nullptr && building.can_build_unit()) {
                // Ratio of health:person is 25, thus making units very expensive
                const float army_size = 100;
                /// @todo Consume special soldier pops instead of farmers!!!
                auto it = std::find_if(province.pops.begin(), province.pops.end(), [&world, building, army_size](const auto& e) {
                    return (e.size >= army_size && world.pop_types[e.type_id].group == PopGroup::FARMER);
                });

                if(it != province.pops.end()) {
                    auto& nation = world.nations[province.owner_id];
                    const auto final_size = glm::min<float>((*it).size, army_size);
                    const auto given_money = final_size;
                    // Nation must have money to pay the units
                    if(given_money >= nation.budget) continue;

                    /// @todo Maybe delete if size becomes 0?
                    (*it).size -= final_size;
                    if(final_size) {
                        nation.budget -= given_money;
                        Unit unit{};
                        unit.type = building.working_unit_type;
                        unit.set_owner(nation);
                        unit.budget = given_money;
                        unit.size = final_size;
                        unit.base = unit.type->max_health;
                        Province::Id province_id = province.get_id(); 
                        province_new_units.local().emplace_back(unit, province_id);
                        building.working_unit_type = nullptr;
                        Eng3D::Log::debug("economy", "[" + province.ref_name + "]: Has built an unit of [" + unit.type->ref_name + "]");
                    }
                }
            }
        }
    });
    world.profiler.stop("E-big");

    world.profiler.start("E-mutex");
    // Collect list of nations that exist
    std::vector<Nation*> eval_nations;
    for(auto& nation : world.nations)
        if(nation.exists())
            eval_nations.push_back(&nation);

    // -------------------------- MUTEX PROTECTED WORLD CHANGES BELOW -------------------------------
    const std::scoped_lock lock(world.world_mutex);

    tbb::parallel_for((Province::Id)0, (Province::Id)world.provinces.size(), [&world, &pops_new_needs, &buildings_new_worker](const auto province_id) {
        auto& province = world.provinces[province_id];
        if(Nation::is_invalid(province.controller_id))
            return;
        
        const auto& new_needs = pops_new_needs[province_id];
        for(Pop::Id i = 0; i < province.pops.size(); i++) {
            auto& pop = province.pops[i];
            pop.budget = new_needs[i].budget;
            pop.life_needs_met = new_needs[i].life_needs_met;
            pop.everyday_needs_met = new_needs[i].everyday_needs_met;
            pop.budget += 0.25f;
        }
        const auto& new_workers = buildings_new_worker[province_id];
        for(Building::Id i = 0; i < province.buildings.size(); i++)
            province.buildings[i].workers = new_workers[i];
    });

    tbb::parallel_for(tbb::blocked_range(eval_nations.begin(), eval_nations.end()), [&world](const auto& nations_range) {
        for(const auto nation : nations_range) {
            // Do research on focused research
            if(nation->focus_tech != nullptr) {
                const float research = nation->get_research_points() / nation->focus_tech->cost;
                nation->research[world.get_id(*nation->focus_tech)] += research;
            }
            militancy_update(world, *nation);
        }
    });

    // Lock for world is already acquired since the economy runs inside the world's do_tick which
    // should be lock guarded by the callee
    province_new_units.combine_each([&world](auto& new_unit_list) {
        for(auto& new_unit : new_unit_list)
            // Now commit the transaction of the new units into the main world area
            world.unit_manager.add_unit(new_unit.unit, new_unit.unit_province);
    });

    world.profiler.start("Emigration");
    do_emigration(world);
    world.profiler.stop("Emigration");
    world.profiler.stop("E-mutex");
}
