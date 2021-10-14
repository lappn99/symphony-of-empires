math.randomseed(os.time())

function cake_test()
	-- Requirements
	return EVENT_CONDITIONS_MET
end
function cake_event()
	local title = "Cake"
	local text = "Sir, a cake has just magically appeared in your desk, what would you like to do?"
	descision = Descision:new{
		ref_name = "cake_descision_0",
		name = "I think i will eat it",
		descision_fn = "cake_descision_0",
		effects = "You will consume cake"
	}
	cake_thing:add_descision(descision)
	
	descision = Descision:new{
		ref_name = "cake_descision_1",
		name = "Fuck you",
		descision_fn = "cake_descision_1",
		effects = "You will consume cake anyways"
	}
	cake_thing:add_descision(descision)

	descision = Descision:new{
		ref_name = "cake_descision_2",
		name = "Cake!?",
		descision_fn = "cake_descision_2",
		effects = "Your compulsory desire for cake has began to grow"
	}
	cake_thing:add_descision(descision)

	descision = Descision:new{
		ref_name = "cake_descision_3",
		name = "Britain, we have a problem",
		descision_fn = "cake_descision_3",
		effects = "What the fuck is britain gonna do, invade us?"
	}
	cake_thing:add_descision(descision)
	return EVENT_DO_ONE_TIME
end
function cake_descision_0()
	print('The cake tasted like a cake, what a surprise! and you find a bunch of peseants outside your palace... oh no')
end
function cake_descision_1()
	print('Why no eat my poisoned cake? i put so much poison in it :(')
end
function cake_descision_2()
	print('Bruh, where the fuck am i?')
end
function cake_descision_3()
	print('Britain converted the cake into tea')
end
cake_thing = Event:new{
	ref_name = "cake_thing",
	conditions_fn = "cake_test",
	event_fn = "cake_event",
	
	title = "Cake",
	text = "Sir, a cake has just magically appeared in your desk, what would you like to do?"
}
cake_thing:register()
cake_thing:add_receivers(Nation:get("hawai_i"))

function kalmar_union_test()
    local needed_provinces = {
        -- Finish key provinces
        "aland", "helsinki", "oulu", "east_oulu", "turku",
        -- Swedish key provinces
        "gotland", "oland", "varmland", "smaland", "jamtland",
        -- Norwegian key provinces
        "oslo"
    }
    local n_needed_provinces = 11

    -- Only these countries can form Scandinavia
    local sweden = Nation:get("sweden")
    local n_sweden_provinces = 0
    local finland = Nation:get("finland")
    local n_finland_provinces = 0
    local norway = Nation:get("norway")
    local n_norway_provinces = 0
    for k, v in pairs(needed_provinces) do
        province = Province:get(v)

        if province.owner_id == sweden.id then
            n_sweden_provinces = n_sweden_provinces + 1
        elseif province.owner_id == finland.id then
            n_finland_provinces = n_finland_provinces + 1
        elseif province.owner_id == norway.id then
            n_norway_provinces = n_norway_provinces + 1
        end
    end

    if n_sweden_provinces >= n_needed_provinces then
        kalmar_union_evhdl:add_receivers(Nation:get("sweden"))
        return EVENT_CONDITIONS_MET
    elseif n_finland_provinces >= n_needed_provinces then
        kalmar_union_evhdl:add_receivers(Nation:get("finland"))
        return EVENT_CONDITIONS_MET
    elseif n_norway_provinces >= n_needed_provinces then
        kalmar_union_evhdl:add_receivers(Nation:get("norway"))
        return EVENT_CONDITIONS_MET
    end
    return EVENT_CONDITIONS_UNMET
end
function kalmar_union_event()
    descision = Descision:new{
        ref_name = "kalmar_union_descision_0",
        name = "Unify scandinavia once again",
        descision_fn = "kalmar_union_descision_0",
        effects = "Become Kalmar Union"
    }
    kalmar_union_evhdl:add_descision(descision)

    descision = Descision:new{
        ref_name = "kalmar_union_descision_1",
        name = "We don't need the others, right?",
        descision_fn = "kalmar_union_descision_1",
        effects = "No Kalmar Union"
    }
    kalmar_union_evhdl:add_descision(descision)
    return EVENT_DO_ONE_TIME
end
function kalmar_union_descision_0()
    
end
function kalmar_union_descision_1()

end
kalmar_union_evhdl = Event:new{
    ref_name = "kalmar_union_evhdl",
    conditions_fn = "kalmar_union_test",
    event_fn = "kalmar_union_event",
    title = "Kalmar Union",
    text = "The Kalmar Union was a country that covered the whole scandinavia - now with the newly aquired provinces in your power we may be able to renew this nation"
}
kalmar_union_evhdl:register()

-- The minas crash was a car crash occuring on the brazilian province of minas
function the_minas_crash_test()
    local year = get_year()
    if year >= 1900 and year <= 1950 and math.random(0, 100) == 0 then
        -- Get the current owner of the minas province
        local nation = Province:get_owner(Province:get("minas_gerais"))
        the_minas_crash:add_receivers(nation)
        return EVENT_CONDITIONS_MET
    end
	return EVENT_CONDITIONS_UNMET
end
function the_minas_crash_event()
	descision = Descision:new{
		ref_name = "the_minas_crash_descision_0",
		name = "I'm sorry for such tragedy",
		descision_fn = "the_minas_crash_descision_0",
		effects = "None"
	}
	the_minas_crash:add_descision(descision)
    descision = Descision:new{
		ref_name = "the_minas_crash_descision_1",
		name = "Well yeah they should be held accountable!",
		descision_fn = "the_minas_crash_descision_1",
		effects = "None"
	}
	the_minas_crash:add_descision(descision)
	return EVENT_DO_ONE_TIME
end
function the_minas_crash_descision_0()
end
function the_minas_crash_descision_1()
end
the_minas_crash = Event:new{
	ref_name = "the_minas_crash",
	conditions_fn = "the_minas_crash_test",
	event_fn = "the_minas_crash_event",
    title = "The minas crash",
	text = "2 cars have been circulating on the minas province recently where they collided with each other on a catastrophic event"
}
the_minas_crash:register()

set_date(1825, 0, 0)
print("********************************************************************************")
print("Industrial era mod")
print("Date: ", get_year(), "/", get_month(), "/", get_day())
print("********************************************************************************")