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
//      nation.hpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <queue>
#include <deque>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include "eng3d/string.hpp"

#include "objects.hpp"
#include "event.hpp"
#include "policy.hpp"

class Province;
class Ideology;
class Technology;
class Pop;
class Language;
class Religion;
namespace TreatyClause {
    class BaseClause;
}

// Defines a one side relation between a country
// This allows for cases where a country A hates country B, but country B loves country A
class NationRelation {
public:
    bool is_allied() const {
        return alliance > 0.f && !has_war;
    }

    bool has_landpass() const {
        return relation > 0.5f || alliance > 0.f || has_war;
    }

    float relation = 0.f;
    bool has_war = false;
    float alliance = 0.f; // From 0 to 1; 0 = diplomatic alliance, tariiff excemption
                          // 1 = political alliance, after this they can form a single country
};
template<>
class Serializer<NationRelation> {
public:
    template<bool is_serialize>
    static inline void deser_dynamic(Archive& ar, NationRelation& obj) {
        ::deser_dynamic<is_serialize>(ar, obj.alliance);
        ::deser_dynamic<is_serialize>(ar, obj.has_war);
        ::deser_dynamic<is_serialize>(ar, obj.relation);
    }
};

class Ideology;
/// @brief Hints for the client on how to display the nation
class NationClientHint {
public:
    uint32_t color;
    Eng3D::StringRef alt_name; // Alternate name, for example communist Russia would be called USSR
    IdeologyId ideology_id; // Ideology to which this hint applies to (nullptr = default fallback)
};
template<>
class Serializer<NationClientHint> {
public:
    template<bool is_serialize>
    static inline void deser_dynamic(Archive& ar, NationClientHint& obj) {
        ::deser_dynamic<is_serialize>(ar, obj.color);
        ::deser_dynamic<is_serialize>(ar, obj.alt_name);
        ::deser_dynamic<is_serialize>(ar, obj.ideology_id);
    }
};

class NationModifier : public RefnameEntity<NationModifierId> {
public:
    Eng3D::StringRef name;
    // Modifiers for a nation, which increases/decreases certain stuff
    // They should never be 0, a modifier of 1.0 is equal to no modifer at
    // all. And a modifier of 0.5 would cause a 1/2. Similar to a 2 which
    // would make a x2
    float industry_output_mod = 1.f;
    float industry_input_mod = 1.f;
    float workers_needed_mod = 1.f;
    float salary_paid_mod = 1.f;
    float delivery_cost_mod = 1.f;
    float literacy_learn_mod = 1.f;
    float reproduction_mod = 1.f;
    float death_mod = 1.f;
    float militancy_mod = 1.f;
    float life_needs_met_mod = 1.f;
    float everyday_needs_met_mod = 1.f;
    float luxury_needs_met_mod = 1.f;
    float immigration_attraction = 1.f;
};
template<>
class Serializer<NationModifier*>: public SerializerReferenceLocal<World, NationModifier> {};
template<>
class Serializer<const NationModifier*>: public SerializerReferenceLocal<World, const NationModifier> {};
template<>
class Serializer<NationModifier> {
public:
    template<bool is_serialize>
    static inline void deser_dynamic(Archive& ar, NationModifier& obj) {
        ::deser_dynamic<is_serialize>(ar, obj.cached_id);
        ::deser_dynamic<is_serialize>(ar, obj.name);
        ::deser_dynamic<is_serialize>(ar, obj.ref_name);
        ::deser_dynamic<is_serialize>(ar, obj.death_mod);
        ::deser_dynamic<is_serialize>(ar, obj.delivery_cost_mod);
        ::deser_dynamic<is_serialize>(ar, obj.everyday_needs_met_mod);
        ::deser_dynamic<is_serialize>(ar, obj.life_needs_met_mod);
        ::deser_dynamic<is_serialize>(ar, obj.literacy_learn_mod);
        ::deser_dynamic<is_serialize>(ar, obj.luxury_needs_met_mod);
        ::deser_dynamic<is_serialize>(ar, obj.militancy_mod);
        ::deser_dynamic<is_serialize>(ar, obj.reproduction_mod);
        ::deser_dynamic<is_serialize>(ar, obj.salary_paid_mod);
        ::deser_dynamic<is_serialize>(ar, obj.workers_needed_mod);
    }
};

class Technology;
class Nation : public RefnameEntity<NationId> {
    inline void do_diplomacy();
    inline bool can_do_diplomacy() const;

    Nation& operator=(const Nation&) = default;
public:
    void declare_war(Nation& nation, std::vector<TreatyClause::BaseClause*> clauses = std::vector<TreatyClause::BaseClause*>());
    bool is_ally(const Nation& nation) const;
    bool is_enemy(const Nation& nation) const;
    bool exists() const;
    void auto_relocate_capital();
    void set_policy(const Policies& policies);
    bool is_accepted_language(const Language& language) const;
    bool is_accepted_religion(const Religion& relgion) const;
    float get_tax(const Pop& pop) const;
    void give_province(Province& province);
    void control_province(Province& province);
    const NationClientHint& get_client_hint() const;
    float get_research_points() const;
    bool can_research(const Technology& tech) const;
    void change_research_focus(const Technology& tech);
    std::vector<Nation*> get_allies();
    float get_industry_output_mod();
    float get_industry_input_mod();
    float get_workers_needed_mod();
    float get_salary_paid_mod();
    float get_delivery_cost_mod();
    float get_literacy_learn_mod();
    float get_reproduction_mod();
    float get_death_mod();
    float get_militancy_mod();
    float get_life_needs_met_mod();
    float get_everyday_needs_met_mod();
    float get_luxury_needs_met_mod();
    float get_immigration_attraction_mod();

    Eng3D::StringRef name;
    float diplomacy_points; // Amount of diplomacy points available
    float prestige = 0.1f; // Amount of prestige
    float infamy = 0; // Level of infamy
    // 3 key scores used to define a nation's minimum prestige, how willing would the AI
    // be to challenge this nations and other valuable stuff
    float military_score = 0.f, naval_score = 0.f, economy_score = 0.f;
    // Total budget of the nation (money in ark), this is not equal to GDP, the GDP is the total sum of the price
    // of all products in the nation, which are volatile unless they are sold
    float budget = 10000.f;
    // Default and can be disabled by the player
    bool ai_controlled = true;
    bool ai_do_cmd_troops = true;

    NationId puppet_master_id; // Pupeeter of this nation (if any)
    ProvinceId capital_id; // The capital of this nation (can be invalid id)
    IdeologyId ideology_id; // Current ideology of the nation
    TechnologyId focus_tech_id; // Current tech being researched
    Policies current_policy; // Current policy of this nation
    uint16_t diplomatic_timer; // Time until a diplomacy can be done
    // Accepted languages in this nation, the accepted languages may have some bonuses on provinces *totally*
    // owned by this nation
    std::vector<float> language_discrim;
    std::vector<float> religion_discrim;
    // List of provinces which are owned by this nation (including partial ownership)
    /// @todo Add controlled provinces to serializer
    std::vector<ProvinceId> owned_provinces;
    std::vector<ProvinceId> controlled_provinces;
    std::vector<NationModifier*> modifiers;
    std::deque<Event> inbox; // Inbox of the nation; events that require our attention / should be processed
    std::vector<float> research; // Progress on technologies (1:1)
    std::vector<NationClientHint> client_hints; // Hints for the client on how to draw a nation on the client
    std::string client_username; // Used by clients to store usernames from nations - not saved
};
template<>
class Serializer<Nation*>: public SerializerReferenceLocal<World, Nation> {};
template<>
class Serializer<const Nation*>: public SerializerReferenceLocal<World, const Nation> {};
template<>
class Serializer<Nation> {
public:
    template<bool is_serialize>
    static inline void deser_dynamic(Archive& ar, Nation& obj) {
        ::deser_dynamic<is_serialize>(ar, obj.cached_id);
        ::deser_dynamic<is_serialize>(ar, obj.name);
        ::deser_dynamic<is_serialize>(ar, obj.ref_name);
        ::deser_dynamic<is_serialize>(ar, obj.puppet_master_id);
        ::deser_dynamic<is_serialize>(ar, obj.diplomacy_points);
        ::deser_dynamic<is_serialize>(ar, obj.prestige);
        ::deser_dynamic<is_serialize>(ar, obj.infamy);
        ::deser_dynamic<is_serialize>(ar, obj.military_score);
        ::deser_dynamic<is_serialize>(ar, obj.naval_score);
        ::deser_dynamic<is_serialize>(ar, obj.economy_score);
        ::deser_dynamic<is_serialize>(ar, obj.budget);
        ::deser_dynamic<is_serialize>(ar, obj.capital_id);
        ::deser_dynamic<is_serialize>(ar, obj.language_discrim);
        ::deser_dynamic<is_serialize>(ar, obj.religion_discrim);
        ::deser_dynamic<is_serialize>(ar, obj.owned_provinces);
        ::deser_dynamic<is_serialize>(ar, obj.controlled_provinces);
        ::deser_dynamic<is_serialize>(ar, obj.current_policy);
        ::deser_dynamic<is_serialize>(ar, obj.diplomatic_timer);
        ::deser_dynamic<is_serialize>(ar, obj.inbox);
        ::deser_dynamic<is_serialize>(ar, obj.client_hints);
        ::deser_dynamic<is_serialize>(ar, obj.ideology_id);
        ::deser_dynamic<is_serialize>(ar, obj.research);
        ::deser_dynamic<is_serialize>(ar, obj.focus_tech_id);
    }
};
