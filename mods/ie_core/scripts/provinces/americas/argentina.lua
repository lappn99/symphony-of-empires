--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: South America
-- Country: Argentina + Paragonia

province = Province:new{ ref_name = "buenos_aires", color = 0xff1900 }
province.name = _("Buenos Aires")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)
argentina:set_capital(province)

province = Province:new{ ref_name = "misiones", color = 0xff9e54 }
province.name = _("Misiones")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "entre_rios", color = 0x00a9ff }
province.name = _("Entre Ríos")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "corrientes", color = 0xf19efe }
province.name = _("Corrientes")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

--province = Province:new{ ref_name = "rio_gallegos", color = 0x617bc9 }
--province.name = _("Rio Gallegos")
--province:register()
--province:add_industry(wheat_farm, andes_transport)
--province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
--province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
--province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
--province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
--province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
--province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
--province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
--province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
--province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
--province:add_nucleus(argentina)

province = Province:new{ ref_name = "tierra_del_fuego", color = 0x040d88 }
province.name = _("Tierra del Fuego")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:add_nucleus(chile)

province = Province:new{ ref_name = "tandil", color = 0x9670ff }
province.name = _("Tandil")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_industry(oil_refinery, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "viedma", color = 0x880098 }
province.name = _("Viedma")
province:register()
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(sulfur_mine, andes_transport)
province:add_industry(oil_refinery, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "rio_negro", color = 0xff4c4c }
province.name = _("Río Negro")
province:register()
province:add_industry(oil_refinery, andes_transport)
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "chubut", color = 0x241f3d }
province.name = _("Chubut")
province:register()
province:add_industry(oil_refinery, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "santa_cruz_andes", color = 0x3d222a }
province.name = _("Santa Cruz")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "neuquen", color = 0xe28eff }
province.name = _("Neuquén")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "la_pampa", color = 0xffa5ea }
province.name = _("La Pampa")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "mendoza", color = 0xfff0b2 }
province.name = _("Mendoza")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "rosario", color = 0xdeb7ff }
province.name = _("Rosario")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "mar_chiquita", color = 0xfde0ff }
province.name = _("Mar Chiquita")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "cordoba", color = 0x00ff9d }
province.name = _("Córdoba")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "san_luis", color = 0x2200ff }
province.name = _("San Luis")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(lumberjack, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "san_juan", color = 0x00ff4c }
province.name = _("San Juan")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(cotton_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "la_rioja", color = 0xff7577 }
province.name = _("La Rioja")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "santa_fe", color = 0xff0af2 }
province.name = _("Santa Fe")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "catamarca", color = 0x3d9eff }
province.name = _("Catamarca")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(lumberjack, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "tucuman", color = 0xff6daa }
province.name = _("Tucumán")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "southern_puna", color = 0xff87d9 }
province.name = _("Southern Puna")
province:register()
province:add_industry(lumberjack, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "central_puna", color = 0xe1ff00 }
province.name = _("Central Puna")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "rinconada", color = 0xcdffba }
province.name = _("Rinconada")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "jujuy", color = 0x96ffc3 }
province.name = _("Jujuy")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "santiago_del_estero", color = 0xff6a56 }
province.name = _("Santiago del Estero")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "chaco", color = 0xe4a8ff }
province.name = _("Chaco")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "resistencia", color = 0x0d1b3a }
province.name = _("Resistencia")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "formosa", color = 0x60ffec }
province.name = _("Formosa")
province:register()
province:add_industry(lumberjack, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "las_lomitas", color = 0xdaaaf9 }
province.name = _("Las Lomitas")
province:register()
province:add_industry(lumberjack, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "monte_quemado", color = 0xc7ff4f }
province.name = _("Monte Quemado")
province:register()
province:add_industry(lumberjack, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)
province:give_to(argentina)

province = Province:new{ ref_name = "laboulaye", color = 0xff8060 }
province.name = _("Laboulaye")
province:register()
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "dupuy", color = 0xff966d }
province.name = _("Dupuy")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)

province = Province:new{ ref_name = "llancanelo", color = 0xafffb2 }
province.name = _("Llancanelo")
province:register()
province:add_industry(rice_farm, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(lumberjack, andes_transport)
province:add_industry(vineyard, andes_transport)
province:add_industry(wheat_farm, andes_transport)
province:add_pop(artisan, argentinian, catholic, 2000, 0.8)
province:add_pop(farmer, argentinian, catholic, 8000, 0.5)
province:add_pop(soldier, argentinian, catholic, 1000, 0.6)
province:add_pop(craftsmen, argentinian, catholic, 2000, 0.4)
province:add_pop(bureaucrat, argentinian, catholic, 500, 0.6)
province:add_pop(aristocrat, argentinian, catholic, 100, 0.8)
province:add_pop(clergymen, argentinian, catholic, 1000, 0.5)
province:add_pop(laborer, argentinian, catholic, 1000, 0.5)
province:add_pop(entrepreneur, argentinian, catholic, 50, 0.9)
province:add_nucleus(argentina)