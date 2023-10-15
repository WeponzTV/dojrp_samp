#include <YSI_Coding\y_hooks>

forward DisableVehicleAlarm(vehicleid);

enum motors_data
{
	ls_motors_pickup,
	ls_motors_cp,

	sf_motors_pickup,
	sf_motors_cp,

	lv_motors_pickup,
	lv_motors_cp
};
new MotorsData[motors_data];

enum vehicle_data
{
	vehicle_id,
	vehicle_charid,
	vehicle_model,
	vehicle_colour1,
	vehicle_colour2,
	vehicle_price,
	vehicle_engine,
	vehicle_lights,
	vehicle_alarm,
	vehicle_bonnet,
	vehicle_boot,
	vehicle_objective,
	vehicle_mods[17],
	vehicle_neons,
	vehicle_neonobj1,
	vehicle_neonobj2,
	vehicle_timer,
	Float:vehicle_x,
	Float:vehicle_y,
	Float:vehicle_z,
	Float:vehicle_a,
	Float:vehicle_health,
	vehicle_plate[32],
	vehicle_paintjob,
	vehicle_locked,
	vehicle_fuel,
	bool:vehicle_owned
}
new VehicleData[MAX_VEHICLES][vehicle_data];

static vehicle_names[][] = {
	"Landstalker", "Bravura", "Buffalo", "Linerunner", "Perennial", "Sentinel", "Dumper", "Fire Truck", "Trashmaster", "Stretch", "Manana",
	"Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam", "Esperanto", "Taxi", "Washington", "Bobcat",
	"Mr. Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife",
	"Articulated Trailer", "Previon", "Coach", "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo",
	"Seasparrow", "Pizzaboy", "Tram", "Articulated Trailer 2", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
	"Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez", "Sparrow",
	"Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina", "Comet", "BMX", "Burrito",
	"Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring Racer",
	"Sandking", "Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B",
	"Bloodring Banger", "Rancher", "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stuntplane", "Tanker",
	"Roadtrain", "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Towtruck", "Fortune",
	"Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine Harvester", "Feltzer", "Remington", "Slamvan", "Blade", "Freight", "Brown Streak",
	"Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Fire Truck Ladder", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa", "Sunrise", "Merit",
	"Utility Van", "Nevada", "Yosemite", "Windsor", "Monster A", "Monster B", "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance",
	"RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito", "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway",
	"Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400", "Newsvan", "Tug", "Tanker Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog",
	"Club", "Freight Box", "Articulated Trailer 3", "Andromada", "Dodo", "RC Cam", "Launch", "Police (LS)", "Police (SF)",
	"Police (LV)", "Ranger", "Picador", "S.W.A.T.", "Alpha", "Phoenix", "Glendale (Damaged)", "Sadler (Damaged)", "Baggage Box A",
	"Baggage Box B", "Tug Stairs", "Boxville", "Farm Trailer", "Utility Trailer"
};

static spoiler[20][2] =
{
	{1000,400},
	{1001,550},
	{1002,200},
	{1003,250},
	{1014,400},
	{1015,500},
	{1016,200},
	{1023,350},
	{1058,620},
	{1060,530},
	{1049,810},
	{1050,620},
	{1138,580},
	{1139,470},
	{1146,490},
	{1147,600},
	{1158,550},
	{1162,650},
	{1163,450},
	{1164,550}
};
 
static nitro[3][2] =
{
    {1008,500},
    {1009,200},
    {1010,1000}
};
 
static fbumper[23][2] =
{
    {1117,2040},
    {1152,910},
    {1153,1200},
    {1155,1030},
    {1157,930},
    {1160,1050},
    {1165,850},
    {1166,950},
    {1169,970},
    {1170,880},
    {1171,990},
    {1172,900},
    {1173,950},
    {1174,1000},
    {1175,900},
    {1179,2150},
    {1181,2050},
    {1182,2130},
    {1185,2040},
    {1188,2080},
    {1189,2200},
    {1190,1200},
    {1191,1040}
};
 
static rbumper[22][2] =
{
    {1140,870},
    {1141,980},
    {1148,890},
    {1149,1000},
    {1150,1090},
    {1151,840},
    {1154,1030},
    {1156,920},
    {1159,1050},
    {1161,950},
    {1167,850},
    {1168,950},
    {1176,1000},
    {1177,900},
    {1178,2050},
    {1180,2130},
    {1183,2040},
    {1184,2150},
    {1186,2095},
    {1187,2175},
    {1192,940},
    {1193,1100}
};
 
static exhaust[28][2] =
{
    {1018,350},
    {1019,300},
    {1020,250},
    {1021,200},
    {1022,150},
    {1028,770},
    {1029,680},
    {1037,690},
    {1043,500},
    {1044,500},
    {1045,510},
    {1046,710},
    {1059,720},
    {1064,830},
    {1065,850},
    {1066,750},
    {1089,650},
    {1092,750},
    {1104,1610},
    {1105,1540},
    {1113,3340},
    {1114,3250},
    {1126,3340},
    {1127,3250},
    {1129,1650},
    {1132,1590},
    {1135,1500},
    {1136,1000}
};
 
static bventr[2][2] =
{
    {1142,150},
    {1144,100}
};
 
static bventl[2][2] =
{
    {1143,150},
    {1145,100}
};
 
static bscoop[4][2] =
{
	{1004,100},
	{1005,150},
	{1011,220},
	{1012,250}
};
 
static rscoop[17][2] =
{
    {1006,80},
    {1032,170},
    {1033,120},
    {1035,150},
    {1038,190},
    {1053,130},
    {1054,210},
    {1055,230},
    {1061,180},
    {1067,250},
    {1068,200},
    {1088,150},
    {1091,100},
    {1103,3250},
    {1128,3340},
    {1130,3380},
    {1131,3290}
};
 
static rskirt[22][2] =
{
    {1007,500},
    {1026,480},
    {1031,370},
    {1036,500},
    {1041,390},
    {1042,1000},
    {1047,670},
    {1048,530},
    {1056,520},
    {1057,430},
    {1069,550},
    {1070,450},
    {1090,450},
    {1093,350},
    {1095,350},
    {1106,780},
    {1108,780},
    {1118,780},
    {1119,940},
    {1122,780},
    {1133,830},
    {1134,800}
};
 
static lskirt[20][2] =
{
    {1017,500},
    {1027,480},
    {1030,370},
    {1039,390},
    {1040,500},
    {1051,670},
    {1052,530},
    {1062,550},
    {1063,430},
    {1071,550},
    {1072,450},
    {1094,450},
    {1099,1000},
    {1101,780},
    {1102,830},
    {1107,780},
    {1120,780},
    {1121,940},
    {1124,780},
    {1137,800}
};
 
static hydraulics[1][2] =
{
    {1087,1500}
};
 
static base[1][2] =
{
    {1086,100}
};
 
static rbbars[4][2] =
{
    {1109,1610},
    {1110,1540},
    {1123,860},
    {1125,1120}
};
 
static fbbars[2][2] =
{
    {1115,2130},
    {1116,2050}
};
 
static wheels[17][2] =
{
    {1025,1000},
    {1073,1100},
    {1074,1030},
    {1075,980},
    {1076,1560},
    {1077,1620},
    {1078,1200},
    {1079,1030},
    {1080,900},
    {1081,1230},
    {1082,820},
    {1083,1560},
    {1084,1350},
    {1085,770},
    {1096,1000},
    {1097,620},
    {1098,1140}
};
 
static headlights[2][2] =
{
	{1013,100},
	{1024,50}
};

static Boats[11] =
{
	430,446,452,453,454,472,473,484,493,539,595
};

static Aircraft[20] =
{
	417,425,447,460,469,476,487,488,497,511,512,513,519,520,548,553,563,577,592,593
};

static Bicycles[3] =
{
	481,509,510
};

static Motorcycles[11] =
{
	448,461,462,463,468,471,521,522,523,581,586
};

static Trucks[14] =
{
	403,407,408,414,433,443,455,456,514,515,524,544,573,578
};

stock GetVehicleCharacterID(vehicleid) return VehicleData[vehicleid][vehicle_charid];

stock GetVehicleFuel(vehicleid) return VehicleData[vehicleid][vehicle_fuel];
stock SetVehicleFuel(vehicleid, fuel) return VehicleData[vehicleid][vehicle_fuel] = fuel;

stock GetVehicleNeons(vehicleid) return VehicleData[vehicleid][vehicle_neons];
stock SetVehicleNeons(vehicleid, colour) return VehicleData[vehicleid][vehicle_neons] = colour;

stock CreateVehicleNeons(vehicleid)
{
	if(!IsValidDynamicObject(VehicleData[vehicleid][vehicle_neonobj1]))
	{
		VehicleData[vehicleid][vehicle_neonobj1] = CreateDynamicObject(VehicleData[vehicleid][vehicle_neons], VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z], 0.0, 0.0, 0.0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(VehicleData[vehicleid][vehicle_neonobj1], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}

	if(!IsValidDynamicObject(VehicleData[vehicleid][vehicle_neonobj2]))
	{
		VehicleData[vehicleid][vehicle_neonobj2] = CreateDynamicObject(VehicleData[vehicleid][vehicle_neons], VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z], 0.0, 0.0, 0.0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(VehicleData[vehicleid][vehicle_neonobj2], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	return 1;
}

stock DestroyVehicleNeons(vehicleid)
{
	if(IsValidDynamicObject(VehicleData[vehicleid][vehicle_neonobj1])) { DestroyDynamicObject(VehicleData[vehicleid][vehicle_neonobj1]); }
	if(IsValidDynamicObject(VehicleData[vehicleid][vehicle_neonobj2])) { DestroyDynamicObject(VehicleData[vehicleid][vehicle_neonobj2]); }
	return 1;
}

stock GetVehicleModelName(modelid, name[], len)
{
	if(modelid >= 400 && modelid <= 611)
	{
		return strmid(name, vehicle_names[modelid - 400], 0, len, len);
	}
	return 0;
}

stock GetVehicleSpeed(vehicleid)
{
	new Float:pos[4];
    GetVehicleVelocity(vehicleid, pos[0], pos[1], pos[2]);
    pos[3] = floatsqroot(floatpower(floatabs(pos[0]), 2.0) + floatpower(floatabs(pos[1]), 2.0) + floatpower(floatabs(pos[2]), 2.0)) * 178.8617875;
    return floatround(pos[3], floatround_round);
}

stock GetOwnedVehicleCount(playerid)
{
	new count = 0, characterid = GetPlayerCharacterID(playerid);
	foreach(new v : Vehicle)
	{
		if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
		{
			count++;
		}
	}
	return count;
}

stock SaveVehicleData(playerid)
{
	new query[800], Float:health, characterid = GetPlayerCharacterID(playerid);
	for(new v = 0; v < MAX_VEHICLES; v++)//Foreach does not work
	{
		if(!IsValidVehicle(v)) continue;

		if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
		{
			GetVehicleHealth(v, health);

			format(query, sizeof(query),
			"UPDATE `VEHICLES` SET `COL1` = '%i', `COL2` = '%i', `X` = '%f', `Y` = '%f', `Z` = '%f', `A` = '%f', `HEALTH` = '%f', `PLATE` = '%q', `PAINT` = '%i', `LOCK` = '%i', `FUEL` = '%i', `NEONS` = '%i', `ENGINE` = '%i', `LIGHTS` = '%i', `ALARM` = '%i', `BONNET` = '%i', `BOOT` = '%i' WHERE `VEHICLE_ID` = '%i'", 
			VehicleData[v][vehicle_colour1], VehicleData[v][vehicle_colour2], VehicleData[v][vehicle_x], VehicleData[v][vehicle_y], VehicleData[v][vehicle_z], VehicleData[v][vehicle_a], health, VehicleData[v][vehicle_plate], VehicleData[v][vehicle_paintjob], VehicleData[v][vehicle_locked], VehicleData[v][vehicle_fuel], VehicleData[v][vehicle_neons], 
			VehicleData[v][vehicle_engine], VehicleData[v][vehicle_lights], VehicleData[v][vehicle_alarm], VehicleData[v][vehicle_bonnet], VehicleData[v][vehicle_boot], VehicleData[v][vehicle_id]);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			format(query, sizeof(query),
			"UPDATE `MODS` SET `M1` = '%i', `M2` = '%i', `M3` = '%i', `M4` = '%i', `M5` = '%i', `M6` = '%i', `M7` = '%i', `M8` = '%i', `M9` = '%i', `M10` = '%i', `M11` = '%i', `M12` = '%i', `M13` = '%i', `M14` = '%i', `M15` = '%i', `M16` = '%i', `M17` = '%i' WHERE `VEHICLE_ID` = '%i'", 
			VehicleData[v][vehicle_mods][0], VehicleData[v][vehicle_mods][1], VehicleData[v][vehicle_mods][2], VehicleData[v][vehicle_mods][3], VehicleData[v][vehicle_mods][4], VehicleData[v][vehicle_mods][5], VehicleData[v][vehicle_mods][6], VehicleData[v][vehicle_mods][7], VehicleData[v][vehicle_mods][8], 
			VehicleData[v][vehicle_mods][9], VehicleData[v][vehicle_mods][10], VehicleData[v][vehicle_mods][11], VehicleData[v][vehicle_mods][12], VehicleData[v][vehicle_mods][13], VehicleData[v][vehicle_mods][14], VehicleData[v][vehicle_mods][15], VehicleData[v][vehicle_mods][16], VehicleData[v][vehicle_id]);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			if(VehicleData[v][vehicle_neons] != NO_NEONS)
			{
				DestroyVehicleNeons(v);
			}
			VehicleData[v][vehicle_neons] = NO_NEONS;

			DestroyVehicle(v);

			for(new i = 0; i < 17; i++)
			{
		 		VehicleData[v][vehicle_mods][i] = 0;
		 	}

			VehicleData[v][vehicle_owned] = false;
		}
	}
	return 1;
}

stock LoadVehicleData(playerid)
{
	new query[300], characterid = GetPlayerCharacterID(playerid), plate[32], charid, vehid, model, col1, col2, price, paint, lock, fuel, neons, engine, lights, alarm, bonnet, boot, Float:pos[4], Float:health;
	format(query, sizeof(query), "SELECT * FROM `VEHICLES` WHERE `CHARACTER_ID` = '%i' LIMIT %i", characterid, MAX_VIP_VEHICLES);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
    {
        do
        {
	        db_get_field_assoc@(database_result, "PLATE", plate, sizeof(plate));

			vehid = db_get_field_assoc_int(database_result, "VEHICLE_ID");
			charid = db_get_field_assoc_int(database_result, "CHARACTER_ID");
			model = db_get_field_assoc_int(database_result, "MODEL");
			col1 = db_get_field_assoc_int(database_result, "COL1");
			col2 = db_get_field_assoc_int(database_result, "COL2");
			price = db_get_field_assoc_int(database_result, "PRICE");
			paint = db_get_field_assoc_int(database_result, "PAINT");
			lock = db_get_field_assoc_int(database_result, "LOCK");
			fuel = db_get_field_assoc_int(database_result, "FUEL");
			neons = db_get_field_assoc_int(database_result, "NEONS");

			engine = db_get_field_assoc_int(database_result, "ENGINE");
			lights = db_get_field_assoc_int(database_result, "LIGHTS");
			alarm = db_get_field_assoc_int(database_result, "ALARM");
			bonnet = db_get_field_assoc_int(database_result, "BONNET");
			boot = db_get_field_assoc_int(database_result, "BOOT");

			pos[0] = db_get_field_assoc_float(database_result, "X");
			pos[1] = db_get_field_assoc_float(database_result, "Y");
			pos[2] = db_get_field_assoc_float(database_result, "Z");
			pos[3] = db_get_field_assoc_float(database_result, "A");

			health = db_get_field_assoc_float(database_result, "HEALTH");

			new vehicleid = CreateVehicle(model, pos[0], pos[1], pos[2], pos[3], col1, col2, -1);

			new query2[200], DBResult:mods_result;
			format(query2, sizeof(query2), "SELECT * FROM `MODS` WHERE `VEHICLE_ID` = '%i'", vehid);
			mods_result = db_query@(server_database, query2);
			if(db_num_rows(mods_result))
    		{
				VehicleData[vehicleid][vehicle_mods][0] = db_get_field_assoc_int(mods_result, "M1");
				VehicleData[vehicleid][vehicle_mods][1] = db_get_field_assoc_int(mods_result, "M2");
				VehicleData[vehicleid][vehicle_mods][2] = db_get_field_assoc_int(mods_result, "M3");
				VehicleData[vehicleid][vehicle_mods][3] = db_get_field_assoc_int(mods_result, "M4");
				VehicleData[vehicleid][vehicle_mods][4] = db_get_field_assoc_int(mods_result, "M5");
				VehicleData[vehicleid][vehicle_mods][5] = db_get_field_assoc_int(mods_result, "M6");
				VehicleData[vehicleid][vehicle_mods][6] = db_get_field_assoc_int(mods_result, "M7");
				VehicleData[vehicleid][vehicle_mods][7] = db_get_field_assoc_int(mods_result, "M8");
				VehicleData[vehicleid][vehicle_mods][8] = db_get_field_assoc_int(mods_result, "M9");
				VehicleData[vehicleid][vehicle_mods][9] = db_get_field_assoc_int(mods_result, "M10");
				VehicleData[vehicleid][vehicle_mods][10] = db_get_field_assoc_int(mods_result, "M11");
				VehicleData[vehicleid][vehicle_mods][11] = db_get_field_assoc_int(mods_result, "M12");
				VehicleData[vehicleid][vehicle_mods][12] = db_get_field_assoc_int(mods_result, "M13");
				VehicleData[vehicleid][vehicle_mods][13] = db_get_field_assoc_int(mods_result, "M14");
				VehicleData[vehicleid][vehicle_mods][14] = db_get_field_assoc_int(mods_result, "M15");
				VehicleData[vehicleid][vehicle_mods][15] = db_get_field_assoc_int(mods_result, "M16");
				VehicleData[vehicleid][vehicle_mods][16] = db_get_field_assoc_int(mods_result, "M17");
			}
			db_free_result@(mods_result);

			VehicleData[vehicleid][vehicle_plate] = plate;

			VehicleData[vehicleid][vehicle_charid] = charid;
			VehicleData[vehicleid][vehicle_id] = vehid;
			VehicleData[vehicleid][vehicle_model] = model;
			VehicleData[vehicleid][vehicle_colour1] = col1;
			VehicleData[vehicleid][vehicle_colour2] = col2;
			VehicleData[vehicleid][vehicle_price] = price;
			VehicleData[vehicleid][vehicle_paintjob] = paint;
			VehicleData[vehicleid][vehicle_locked] = lock;
			VehicleData[vehicleid][vehicle_fuel] = fuel;
			VehicleData[vehicleid][vehicle_neons] = neons;

			VehicleData[vehicleid][vehicle_x] = pos[0];
			VehicleData[vehicleid][vehicle_y] = pos[1];
			VehicleData[vehicleid][vehicle_z] = pos[2];
			VehicleData[vehicleid][vehicle_a] = pos[3];

			VehicleData[vehicleid][vehicle_engine] = engine;
			VehicleData[vehicleid][vehicle_lights] = lights;
			VehicleData[vehicleid][vehicle_alarm] = alarm;
			VehicleData[vehicleid][vehicle_bonnet] = bonnet;
			VehicleData[vehicleid][vehicle_boot] = boot;
			VehicleData[vehicleid][vehicle_objective] = VEHICLE_PARAMS_OFF;

			VehicleData[vehicleid][vehicle_health] = health;

			VehicleData[vehicleid][vehicle_owned] = true;

			SetVehicleNumberPlate(vehicleid, VehicleData[vehicleid][vehicle_plate]);
			SetVehicleHealth(vehicleid, VehicleData[vehicleid][vehicle_health]);

			SetVehicleParamsForAll(vehicleid, VehicleData[vehicleid][vehicle_objective], VehicleData[vehicleid][vehicle_locked]);
	        SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);

			SetVehicleToRespawn(vehicleid);
        }
        while(db_next_row(database_result));
    }
    db_free_result@(database_result);
	return 1;
}

stock GetNearestVehicle(playerid)
{
    foreach(new v : Vehicle)
	{
		new Float:pos[3];
		GetVehiclePos(v, pos[0], pos[1], pos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return v;
	}
	return INVALID_VEHICLE_ID;
}

stock SetVehicleParamsForAll(vehicleid, objective, locked)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		SetVehicleParamsForPlayer(vehicleid, i, objective, locked);
	}
	return 1;
}

stock SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
{
	VehicleData[vehicleid][vehicle_engine] = engine;
	VehicleData[vehicleid][vehicle_lights] = lights;
	VehicleData[vehicleid][vehicle_alarm] = alarm;
	VehicleData[vehicleid][vehicle_locked] = doors;
	VehicleData[vehicleid][vehicle_bonnet] = bonnet;
	VehicleData[vehicleid][vehicle_boot] = boot;
	VehicleData[vehicleid][vehicle_objective] = objective;

    SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(alarm)
    {
        KillTimer(VehicleData[vehicleid][vehicle_timer]);
        VehicleData[vehicleid][vehicle_timer] = SetTimerEx("DisableVehicleAlarm", 20000, false, "i", vehicleid);
    }
    return 1;
}

stock IsVehicleBoat(vehicleid)
{
	for(new i = 0; i < sizeof(Boats); i++)
	{
	 	if(GetVehicleModel(vehicleid) == Boats[i]) return 1;
	}
	return 0;
}

stock IsVehicleAircraft(vehicleid)
{
	for(new i = 0; i < sizeof(Aircraft); i++)
	{
	 	if(GetVehicleModel(vehicleid) == Aircraft[i]) return 1;
	}
	return 0;
}

stock IsVehicleBicycle(vehicleid)
{
	for(new i = 0; i < sizeof(Bicycles); i++)
	{
	 	if(GetVehicleModel(vehicleid) == Bicycles[i]) return 1;
	}
	return 0;
}

stock IsVehicleMotorcycle(vehicleid)
{
	for(new i = 0; i < sizeof(Motorcycles); i++)
	{
	 	if(GetVehicleModel(vehicleid) == Motorcycles[i]) return 1;
	}
	return 0;
}

stock IsVehicleTruck(vehicleid)
{
	for(new i = 0; i < sizeof(Trucks); i++)
	{
	 	if(GetVehicleModel(vehicleid) == Trucks[i]) return 1;
	}
	return 0;
}

stock GetVehicleDriverID(vehicleid)
{
	foreach(new i : Player)
	{
		if(IsPlayerInAnyVehicle(i))
		{
         	if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER) return i;
		}
	}
	return INVALID_PLAYER_ID;
}

stock GetVehicleParameter(const string[], return_str[], delim, start_index)
{
	new x = 0;
	while(string[start_index] != EOS && string[start_index] != delim)
	{
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;

	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}

stock LoadVehiclesFromFile(const file[])
{
	new File:handle, line[256], param[64], index, modelid, Float:pos[4], colour1, colour2, delay;
	handle = fopen(file, filemode:io_read);
	if(!handle) return 0;

	while(fread(handle, line, sizeof(line)) > 0)
	{
	    index = 0;

  		index = GetVehicleParameter(line, param, ',', index);
  		if(index == (-1)) continue;
  		modelid = strval(param);
   		//if(modelid < 400 || modelid > 611) continue;

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[0] = floatstr(param);

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[1] = floatstr(param);

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[2] = floatstr(param);

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[3] = floatstr(param);

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		colour1 = strval(param);

  		index = GetVehicleParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		colour2 = strval(param);

  		index = GetVehicleParameter(line, param, ';', index + 1);
  		delay = strval(param);
  		
  		AddStaticVehicleEx(modelid, pos[0], pos[1], pos[2], pos[3], colour1, colour2, delay);
	}

	fclose(handle);
	return 1;
}

stock ShowMotorsDialog(playerid, city)
{
	if(city == LOS_SANTOS)
	{
		return ShowPlayerDialog(playerid, LS_MOTORS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Motors", "{FFFFFF}Purchase Vehicle\nTrade-In Vehicle", "Select", "Cancel");
	}
	else if(city == SAN_FIERRO)
	{
		return ShowPlayerDialog(playerid, SF_MOTORS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Motors", "{FFFFFF}Purchase Vehicle\nTrade-In Vehicle", "Select", "Cancel");
	}
	else if(city == LAS_VENTURAS)
	{
		ShowPlayerDialog(playerid, LV_MOTORS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Motors", "{FFFFFF}Purchase Vehicle\nTrade-In Vehicle", "Select", "Cancel");
	}
	return 1;
}

stock ShowLSListDialog(playerid)
{
	return ShowPlayerDialog(playerid, LS_LIST_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Motors > Purchase Vehicle", "{FFFFFF}Used Vehicles\nNew Vehicles\nSpecial Vehicles", "Select", "Back");
}

stock ShowSFListDialog(playerid)
{
	return ShowPlayerDialog(playerid, SF_LIST_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Motors > Purchase Vehicle", "{FFFFFF}Used Vehicles\nNew Vehicles\nSpecial Vehicles", "Select", "Back");
}

stock ShowLVListDialog(playerid)
{
	return ShowPlayerDialog(playerid, LV_LIST_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Motors > Purchase Vehicle", "{FFFFFF}Used Vehicles\nNew Vehicles\nSpecial Vehicles", "Select", "Back");
}

stock OnPlayerBuyUsedVehicle(playerid, listitem)
{
	new query[800], string[200], price = 0, model = 0, count = GetOwnedVehicleCount(playerid), characterid = GetPlayerCharacterID(playerid);
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "SERVER: You must be on foot to be able to purchase a vehicle.");

	if(GetPlayerVIP(playerid))
	{
	  	if(count >= MAX_VIP_VEHICLES)
	  	{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_VIP_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
	  	}
	}
	else 
	{
		if(count >= MAX_PLAYER_VEHICLES)
		{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_PLAYER_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
		}
	}

	switch(listitem)
	{
		case 0://Buffalo
		{
			price = USED_BUFFALO_PRICE;
			model = 402;
		}
		case 1://Perenail
		{
			price = USED_PERENAIL_PRICE;
			model = 404;
		}
		case 2://Voodoo
		{
			price = USED_VOODOO_PRICE;
			model = 412;
		}
		case 3://Oceanic
		{
			price = USED_OCEANIC_PRICE;
			model = 467;
		}
		case 4://Blista Compact
		{
			price = USED_BLISTA_PRICE;
			model = 496;
		}
		case 5://Clover
		{
			price = USED_CLOVER_PRICE;
			model = 542;
		}
		case 6://Hustler
		{
			price = USED_HUSTLER_PRICE;
			model = 545;
		}
		case 7://Tornado
		{
			price = USED_TORNADO_PRICE;
			model = 576;
		}
		case 8://Club
		{
			price = USED_CLUB_PRICE;
			model = 589;
		}
	}

	if(GetPlayerMoneyEx(playerid) < price) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this vehicle.");

	GivePlayerMoney(playerid, -price);

	new Float:pos[4], colour1 = random(255), colour2 = random(255), name[24], plate[32];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	GetPlayerName(playerid, name, sizeof(name));

	new vehicleid = CreateVehicle(model, pos[0], pos[1], pos[2], pos[3], colour1, colour2, -1);
	SetVehicleNumberPlate(vehicleid, name);
	SetVehicleToRespawn(vehicleid);
	SetVehicleHealth(vehicleid, 1000.0);

	PutPlayerInVehicle(playerid, vehicleid, 0);

	VehicleData[vehicleid][vehicle_charid] = characterid;
	VehicleData[vehicleid][vehicle_model] = model;
	VehicleData[vehicleid][vehicle_x] = pos[0];
	VehicleData[vehicleid][vehicle_y] = pos[1];
	VehicleData[vehicleid][vehicle_z] = pos[2];
	VehicleData[vehicleid][vehicle_a] = pos[3];
	VehicleData[vehicleid][vehicle_health] = 1000.0;
	VehicleData[vehicleid][vehicle_colour1] = colour1;
	VehicleData[vehicleid][vehicle_colour2] = colour2;
	VehicleData[vehicleid][vehicle_paintjob] = 3;
	format(plate, sizeof(plate), "%s", name);
	VehicleData[vehicleid][vehicle_plate] = plate;
	VehicleData[vehicleid][vehicle_price] = price;
	VehicleData[vehicleid][vehicle_neons] = NO_NEONS;
	VehicleData[vehicleid][vehicle_locked] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_owned] = true;

	VehicleData[vehicleid][vehicle_engine] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_lights] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_alarm] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_bonnet] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_boot] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_objective] = VEHICLE_PARAMS_OFF;

	SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);

	format(query, sizeof(query), "INSERT INTO `VEHICLES` (`CHARACTER_ID`, `MODEL`, `COL1`, `COL2`, `PRICE`, `X`, `Y`, `Z`, `A`, `HEALTH`, `PLATE`, `PAINT`, `LOCK`, `FUEL`, `NEONS`, `ENGINE`, `LIGHTS`, `ALARM`, `BONNET`, `BOOT`) VALUES ('%i', '%i', '%i', '%i', '%i', '%f', '%f', '%f', '%f', '%f', '%s', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
	VehicleData[vehicleid][vehicle_charid], VehicleData[vehicleid][vehicle_model], VehicleData[vehicleid][vehicle_colour1], VehicleData[vehicleid][vehicle_colour2], VehicleData[vehicleid][vehicle_price], VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z], VehicleData[vehicleid][vehicle_a], 
	VehicleData[vehicleid][vehicle_health], VehicleData[vehicleid][vehicle_plate], VehicleData[vehicleid][vehicle_paintjob], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_fuel], VehicleData[vehicleid][vehicle_neons], 
	VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot]);
	database_result = db_query@(server_database, query);

	VehicleData[vehicleid][vehicle_id] = db_last_insert_rowid(server_database);

	db_free_result@(database_result);

	format(query, sizeof(query), "INSERT INTO `MODS` (`VEHICLE_ID`, `M1`, `M2`, `M3`, `M4`, `M5`, `M6`, `M7`, `M8`, `M9`, `M10`, `M11`, `M12`, `M13`, `M14`, `M15`, `M16`, `M17`) VALUES ('%i', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0')", 
	VehicleData[vehicleid][vehicle_id]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return 1;
}

stock OnPlayerBuyNewVehicle(playerid, listitem)
{
	new query[800], string[200], price = 0, model = 0, count = GetOwnedVehicleCount(playerid), characterid = GetPlayerCharacterID(playerid);
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "SERVER: You must be on foot to be able to purchase a vehicle.");

	if(GetPlayerVIP(playerid))
	{
	  	if(count >= MAX_VIP_VEHICLES)
	  	{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_VIP_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
	  	}
	}
	else 
	{
		if(count >= MAX_PLAYER_VEHICLES)
		{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_PLAYER_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
		}
	}

	switch(listitem)
	{
		case 0://Infernus
		{
			price = NEW_INFERNUS_PRICE;
			model = 411;
		}
		case 1://Cheetah
		{
			price = NEW_CHEETAH_PRICE;
			model = 415;
		}
		case 2://Banshee
		{
			price = NEW_BANSHEE_PRICE;
			model = 429;
		}
		case 3://Turismo
		{
			price = NEW_TURISMO_PRICE;
			model = 451;
		}
		case 4://ZR-350
		{
			price = NEW_ZR350_PRICE;
			model = 477;
		}
		case 5://Comet
		{
			price = NEW_COMET_PRICE;
			model = 480;
		}
		case 6://Super GT
		{
			price = NEW_SUPERGT_PRICE;
			model = 506;
		}
		case 7://Bullet
		{
			price = NEW_BULLET_PRICE;
			model = 541;
		}
		case 8://Sultan
		{
			price = NEW_SULTAN_PRICE;
			model = 560;
		}
	}

	if(GetPlayerMoneyEx(playerid) < price) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this vehicle.");

	GivePlayerMoney(playerid, -price);

	new Float:pos[4], colour1 = random(255), colour2 = random(255), name[24], plate[32];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	GetPlayerName(playerid, name, sizeof(name));

	new vehicleid = CreateVehicle(model, pos[0], pos[1], pos[2], pos[3], colour1, colour2, -1);
	SetVehicleNumberPlate(vehicleid, name);
	SetVehicleToRespawn(vehicleid);
	SetVehicleHealth(vehicleid, 1000.0);

	PutPlayerInVehicle(playerid, vehicleid, 0);

	VehicleData[vehicleid][vehicle_charid] = characterid;
	VehicleData[vehicleid][vehicle_model] = model;
	VehicleData[vehicleid][vehicle_x] = pos[0];
	VehicleData[vehicleid][vehicle_y] = pos[1];
	VehicleData[vehicleid][vehicle_z] = pos[2];
	VehicleData[vehicleid][vehicle_a] = pos[3];
	VehicleData[vehicleid][vehicle_health] = 1000.0;
	VehicleData[vehicleid][vehicle_colour1] = colour1;
	VehicleData[vehicleid][vehicle_colour2] = colour2;
	VehicleData[vehicleid][vehicle_paintjob] = 3;
	format(plate, sizeof(plate), "%s", name);
	VehicleData[vehicleid][vehicle_plate] = plate;
	VehicleData[vehicleid][vehicle_price] = price;
	VehicleData[vehicleid][vehicle_neons] = NO_NEONS;
	VehicleData[vehicleid][vehicle_locked] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_owned] = true;

	VehicleData[vehicleid][vehicle_engine] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_lights] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_alarm] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_bonnet] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_boot] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_objective] = VEHICLE_PARAMS_OFF;

	SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);

	format(query, sizeof(query), "INSERT INTO `VEHICLES` (`CHARACTER_ID`, `MODEL`, `COL1`, `COL2`, `PRICE`, `X`, `Y`, `Z`, `A`, `HEALTH`, `PLATE`, `PAINT`, `LOCK`, `FUEL`, `NEONS`, `ENGINE`, `LIGHTS`, `ALARM`, `BONNET`, `BOOT`) VALUES ('%i', '%i', '%i', '%i', '%i', '%f', '%f', '%f', '%f', '%f', '%s', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
	VehicleData[vehicleid][vehicle_charid], VehicleData[vehicleid][vehicle_model], VehicleData[vehicleid][vehicle_colour1], VehicleData[vehicleid][vehicle_colour2], VehicleData[vehicleid][vehicle_price], VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z], VehicleData[vehicleid][vehicle_a], 
	VehicleData[vehicleid][vehicle_health], VehicleData[vehicleid][vehicle_plate], VehicleData[vehicleid][vehicle_paintjob], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_fuel], VehicleData[vehicleid][vehicle_neons], 
	VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot]);
	database_result = db_query@(server_database, query);

	VehicleData[vehicleid][vehicle_id] = db_last_insert_rowid(server_database);
	
	db_free_result@(database_result);

	format(query, sizeof(query), "INSERT INTO `MODS` (`VEHICLE_ID`, `M1`, `M2`, `M3`, `M4`, `M5`, `M6`, `M7`, `M8`, `M9`, `M10`, `M11`, `M12`, `M13`, `M14`, `M15`, `M16`, `M17`) VALUES ('%i', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0')", 
	VehicleData[vehicleid][vehicle_id]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return 1;
}

stock OnPlayerBuySpecialVehicle(playerid, listitem)
{
	new query[800], string[200], price = 0, model = 0, count = GetOwnedVehicleCount(playerid), characterid = GetPlayerCharacterID(playerid);
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "SERVER: You must be on foot to be able to purchase a vehicle.");

	if(GetPlayerVIP(playerid))
	{
	  	if(count >= MAX_VIP_VEHICLES)
	  	{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_VIP_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
	  	}
	}
	else 
	{
		if(count >= MAX_PLAYER_VEHICLES)
		{
	  		format(string, sizeof(string), "ERROR: You can only own a max of x%i vehicle(s) at a time, trade one in first.", MAX_PLAYER_VEHICLES);
	  		return SendClientMessage(playerid, RED, string);
		}
	}

	switch(listitem)
	{
		case 0://BF Injection
		{
			price = SPECIAL_BFINJECTION_PRICE;
			model = 424;
		}
		case 1://Hotknife
		{
			price = SPECIAL_HOTKNIFE_PRICE;
			model = 434;
		}
		case 2://Monster
		{
			price = SPECIAL_MONSTER_PRICE;
			model = 444;
		}
		case 3://NRG-500
		{
			price = SPECIAL_NRG500_PRICE;
			model = 522;
		}
		case 4://PCJ-600
		{
			price = SPECIAL_PCJ600_PRICE;
			model = 461;
		}
		case 5://Freeway
		{
			price = SPECIAL_FREEWAY_PRICE;
			model = 463;
		}
		case 6://Sanchez
		{
			price = SPECIAL_SANCHEZ_PRICE;
			model = 468;
		}
		case 7://Quad
		{
			price = SPECIAL_QUAD_PRICE;
			model = 471;
		}
		case 8://Maverick
		{
			price = SPECIAL_MAVERICK_PRICE;
			model = 487;
		}
	}

	if(GetPlayerMoneyEx(playerid) < price) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this vehicle.");

	GivePlayerMoney(playerid, -price);

	new Float:pos[4], colour1 = random(255), colour2 = random(255), name[24], plate[32];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	GetPlayerName(playerid, name, sizeof(name));

	new vehicleid = CreateVehicle(model, pos[0], pos[1], pos[2], pos[3], colour1, colour2, -1);
	SetVehicleNumberPlate(vehicleid, name);
	SetVehicleToRespawn(vehicleid);
	SetVehicleHealth(vehicleid, 1000.0);

	PutPlayerInVehicle(playerid, vehicleid, 0);

	VehicleData[vehicleid][vehicle_charid] = characterid;
	VehicleData[vehicleid][vehicle_model] = model;
	VehicleData[vehicleid][vehicle_x] = pos[0];
	VehicleData[vehicleid][vehicle_y] = pos[1];
	VehicleData[vehicleid][vehicle_z] = pos[2];
	VehicleData[vehicleid][vehicle_a] = pos[3];
	VehicleData[vehicleid][vehicle_health] = 1000.0;
	VehicleData[vehicleid][vehicle_colour1] = colour1;
	VehicleData[vehicleid][vehicle_colour2] = colour2;
	VehicleData[vehicleid][vehicle_paintjob] = 3;
	format(plate, sizeof(plate), "%s", name);
	VehicleData[vehicleid][vehicle_plate] = plate;
	VehicleData[vehicleid][vehicle_price] = price;
	VehicleData[vehicleid][vehicle_neons] = NO_NEONS;
	VehicleData[vehicleid][vehicle_locked] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_owned] = true;

	VehicleData[vehicleid][vehicle_engine] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_lights] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_alarm] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_bonnet] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_boot] = VEHICLE_PARAMS_OFF;
	VehicleData[vehicleid][vehicle_objective] = VEHICLE_PARAMS_OFF;

	SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);

	format(query, sizeof(query), "INSERT INTO `VEHICLES` (`CHARACTER_ID`, `MODEL`, `COL1`, `COL2`, `PRICE`, `X`, `Y`, `Z`, `A`, `HEALTH`, `PLATE`, `PAINT`, `LOCK`, `FUEL`, `NEONS`, `ENGINE`, `LIGHTS`, `ALARM`, `BONNET`, `BOOT`) VALUES ('%i', '%i', '%i', '%i', '%i', '%f', '%f', '%f', '%f', '%f', '%s', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
	VehicleData[vehicleid][vehicle_charid], VehicleData[vehicleid][vehicle_model], VehicleData[vehicleid][vehicle_colour1], VehicleData[vehicleid][vehicle_colour2], VehicleData[vehicleid][vehicle_price], VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z], VehicleData[vehicleid][vehicle_a], 
	VehicleData[vehicleid][vehicle_health], VehicleData[vehicleid][vehicle_plate], VehicleData[vehicleid][vehicle_paintjob], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_fuel], VehicleData[vehicleid][vehicle_neons], 
	VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot]);
	database_result = db_query@(server_database, query);

	VehicleData[vehicleid][vehicle_id] = db_last_insert_rowid(server_database);
	
	db_free_result@(database_result);

	format(query, sizeof(query), "INSERT INTO `MODS` (`VEHICLE_ID`, `M1`, `M2`, `M3`, `M4`, `M5`, `M6`, `M7`, `M8`, `M9`, `M10`, `M11`, `M12`, `M13`, `M14`, `M15`, `M16`, `M17`) VALUES ('%i', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0')", 
	VehicleData[vehicleid][vehicle_id]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return 1;
}

stock OnPlayerTradeInVehicle(playerid)
{
	new string[128], query[128], name[32], vehicleid = GetPlayerTradeVehicle(playerid);
	if(vehicleid != INVALID_VEHICLE_ID)
	{
		DestroyVehicleNeons(vehicleid);

		DestroyVehicle(vehicleid);

		VehicleData[vehicleid][vehicle_owned] = false;

		SetPlayerTradeVehicle(playerid, INVALID_VEHICLE_ID);

		format(query, sizeof(query), "DELETE FROM `VEHICLES` WHERE `VEHICLE_ID` = '%i'", VehicleData[vehicleid][vehicle_id]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		new cash = (VehicleData[vehicleid][vehicle_price] / 2);
		GivePlayerMoney(playerid, cash);

		GetVehicleModelName(VehicleData[vehicleid][vehicle_model], name, sizeof(name));

		format(string, sizeof(string), "SERVER: You have just traded in your %s for: $%i", name, cash);
		SendClientMessage(playerid, WHITE, string);
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2131.3433, -1132.6162, 25.6622, 55, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Motors
    CreateDynamicMapIcon(-1983.1237, 268.1202, 35.1719, 55, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Motors
    CreateDynamicMapIcon(1735.7432, 1866.1516, 10.8203, 55, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Motors

	MotorsData[ls_motors_pickup] = CreateDynamicPickup(1318, 1, 2131.3433, -1132.6162, 25.6622, -1, -1, -1, 100.0, -1, 0);//LS Motors
	MotorsData[sf_motors_pickup] = CreateDynamicPickup(1318, 1, -1983.1237, 268.1202, 35.1719, -1, -1, -1, 100.0, -1, 0);//SF Motors
	MotorsData[lv_motors_pickup] = CreateDynamicPickup(1318, 1, 1735.7432, 1866.1516, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV Motors

	MotorsData[ls_motors_cp] = CreateDynamicCP(2131.3433, -1132.6162, 25.6622, 3.0, -1, -1, -1, 10.0, -1, 0);//LS Motors
    MotorsData[sf_motors_cp] = CreateDynamicCP(-1983.1237, 268.1202, 35.1719, 3.0, -1, -1, -1, 10.0, -1, 0);//SF Motors
    MotorsData[lv_motors_cp] = CreateDynamicCP(1735.7432, 1866.1516, 10.8203, 3.0, -1, -1, -1, 10.0, -1, 0);//LV Motors

	LoadVehiclesFromFile("DOJRP/vehicles/ls.txt");
	LoadVehiclesFromFile("DOJRP/vehicles/sf.txt");
	LoadVehiclesFromFile("DOJRP/vehicles/lv.txt");

	for(new v = 0; v < MAX_VEHICLES; v++)
	{
		new fuel = (random(90) + 10);
		VehicleData[v][vehicle_fuel] = fuel;
		VehicleData[v][vehicle_locked] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_neons] = NO_NEONS;
	    VehicleData[v][vehicle_owned] = false;
		VehicleData[v][vehicle_timer] = -1;

	    VehicleData[v][vehicle_engine] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_lights] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_alarm] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_bonnet] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_boot] = VEHICLE_PARAMS_OFF;
		VehicleData[v][vehicle_objective] = VEHICLE_PARAMS_OFF;

		for(new i = 0; i < 17; i++)
		{
	 		VehicleData[v][vehicle_mods][i] = 0;
	 	}

		if(IsVehicleBicycle(v))
		{
			VehicleData[v][vehicle_fuel] = 0;
			VehicleData[v][vehicle_engine] = VEHICLE_PARAMS_ON;
		}

		SetVehicleParamsEx_Fixed(v, VehicleData[v][vehicle_engine], VehicleData[v][vehicle_lights], VehicleData[v][vehicle_alarm], VehicleData[v][vehicle_locked], VehicleData[v][vehicle_bonnet], VehicleData[v][vehicle_boot], VehicleData[v][vehicle_objective]);

	    SetVehicleNumberPlate(v, SERVER_TAG);

		VehicleData[v][vehicle_health] = 1000.0;
		SetVehicleHealth(v, VehicleData[v][vehicle_health]);
		
		SetVehicleToRespawn(v);
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);

		//Fuel Check
        if(!IsVehicleBicycle(vehicleid) && VehicleData[vehicleid][vehicle_fuel] <= 0)
		{
		    RemovePlayerFromVehicle(playerid);
			return SendClientMessage(playerid, RED, "ERROR: This vehicle is out of fuel.");
		}

		//Restricted Vehicle Check
		new job = GetPlayerJob(playerid);
		switch(GetVehicleModel(vehicleid))
		{
			case 427, 523, 528, 596, 597, 598, 599, 497://Police Vehicles
			{
				if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only law enforcement can use this vehicle.");
				}
			}
			case 490://CIA Vehicles
			{
				if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only law enforcement can use this vehicle.");
				}
			}
			case 425, 432, 433, 470, 520://Army Vehicles
			{
				if(job != ARMY_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only army soldiers can use this vehicle.");
				}
			}
			case 416://Hospital Vehicles
			{
				if(job != EMS_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only paramedics can use this vehicle.");
				}
			}
			case 407://Fire Station Vehicles
			{
				if(job != FIRE_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only firefighters can use this vehicle.");
				}
				else
				{
					RemovePlayerWeapon(playerid, 42);
					GivePlayerWeapon(playerid, 42, 99999);
				}
			}
			case 514, 515, 578://Trucks
			{
				if(job != TRUCKER_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only truck drivers can use this vehicle.");
				}
			}
			case 519, 553, 577, 593://Planes
			{
				if(job != PILOT_JOB)
			    {
			    	RemovePlayerFromVehicle(playerid);
					return SendClientMessage(playerid, RED, "ERROR: Only pilots can use this vehicle.");
				}
			}
		}
    }
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
	if(VehicleData[vehicleid][vehicle_owned] == true)
	{
		SetVehiclePos(vehicleid, VehicleData[vehicleid][vehicle_x], VehicleData[vehicleid][vehicle_y], VehicleData[vehicleid][vehicle_z]);
		SetVehicleZAngle(vehicleid, VehicleData[vehicleid][vehicle_a]);

		SetVehicleParamsForAll(vehicleid, VehicleData[vehicleid][vehicle_objective], VehicleData[vehicleid][vehicle_locked]);

		for(new i = 0; i < 17; i++)
		{
			if(VehicleData[vehicleid][vehicle_mods][i] != 0)
			{
				AddVehicleComponent(vehicleid, VehicleData[vehicleid][vehicle_mods][i]);
			}
		}

		if(VehicleData[vehicleid][vehicle_paintjob] != 0)
		{
			ChangeVehiclePaintjob(vehicleid, VehicleData[vehicleid][vehicle_paintjob]);
		}
			
		if(VehicleData[vehicleid][vehicle_neons] != NO_NEONS)
		{
			CreateVehicleNeons(vehicleid);
		}
	}

	SetVehicleHealth(vehicleid, VehicleData[vehicleid][vehicle_health]);

	SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
	if(VehicleData[vehicleid][vehicle_owned] == false)
	{
		new fuel = (random(90) + 10);
		VehicleData[vehicleid][vehicle_fuel] = fuel;

		for(new i = 0; i < 17; i++)
		{
			VehicleData[vehicleid][vehicle_mods][i] = 0;
		}
	}
	else
	{	
		if(VehicleData[vehicleid][vehicle_neons] != NO_NEONS)
		{
			DestroyVehicleNeons(vehicleid);
		}
	}

	VehicleData[vehicleid][vehicle_health] = 1000.0;
	return 1;
}

hook OnVehicleStreamIn(vehicleid, forplayerid)
{
	if(VehicleData[vehicleid][vehicle_owned] == true)
	{
 		SetVehicleParamsForAll(vehicleid, VehicleData[vehicleid][vehicle_objective], VehicleData[vehicleid][vehicle_locked]);
    	SetVehicleParamsEx_Fixed(vehicleid, VehicleData[vehicleid][vehicle_engine], VehicleData[vehicleid][vehicle_lights], VehicleData[vehicleid][vehicle_alarm], VehicleData[vehicleid][vehicle_locked], VehicleData[vehicleid][vehicle_bonnet], VehicleData[vehicleid][vehicle_boot], VehicleData[vehicleid][vehicle_objective]);
   	}
	return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2)
{
 	VehicleData[vehicleid][vehicle_colour1] = color1;
	VehicleData[vehicleid][vehicle_colour2] = color2;
	return 1;
}

hook OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
 	VehicleData[vehicleid][vehicle_paintjob] = paintjobid;
	return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		for(new i = 0; i < sizeof(spoiler); i++)
		{
 			if(componentid == spoiler[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][0] = componentid;
			}
		}

		for(new i = 0; i < sizeof(bscoop); i++)
		{
 			if(componentid == bscoop[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][1] = componentid;
			}
		}

		for(new i = 0; i < sizeof(rscoop); i++)
		{
 			if(componentid == rscoop[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][2] = componentid;
			}
		}

		for(new i = 0; i < sizeof(rskirt); i++)
		{
 			if(componentid == rskirt[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][3] = componentid;
			}
		}

		for(new i = 0; i < sizeof(headlights); i++)
		{
 			if(componentid == headlights[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][4] = componentid;
			}
		}

		for(new i = 0; i < sizeof(nitro); i++)
		{
 			if(componentid == nitro[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][5] = componentid;
			}
		}

		for(new i = 0; i < sizeof(exhaust); i++)
		{
 			if(componentid == exhaust[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][6] = componentid;
			}
		}

		for(new i = 0; i < sizeof(wheels); i++)
		{
 			if(componentid == wheels[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][7] = componentid;
			}
		}

		for(new i = 0; i < sizeof(base); i++)
		{
 			if(componentid == base[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][8] = componentid;
			}
		}

		for(new i = 0; i < sizeof(hydraulics); i++)
		{
 			if(componentid == hydraulics[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][9] = componentid;
			}
		}

		for(new i = 0; i < sizeof(fbumper); i++)
		{
 			if(componentid == fbumper[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][10] = componentid;
			}
		}

		for(new i = 0; i < sizeof(rbumper); i++)
		{
 			if(componentid == rbumper[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][11] = componentid;
			}
		}

		for(new i = 0; i < sizeof(bventr); i++)
		{
 			if(componentid == bventr[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][12] = componentid;
			}
		}

		for(new i = 0; i < sizeof(bventl); i++)
		{
 			if(componentid == bventl[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][13] = componentid;
			}
		}

		for(new i = 0; i < sizeof(rbbars); i++)
		{
 			if(componentid == rbbars[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][14] = componentid;
			}
		}

		for(new i = 0; i < sizeof(fbbars); i++)
		{
 			if(componentid == fbbars[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][15] = componentid;
			}
		}

		for(new i = 0; i < sizeof(lskirt); i++)
		{
 			if(componentid == lskirt[i][0])
 			{
   				VehicleData[vehicleid][vehicle_mods][16] = componentid;
			}
		}
	}
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case LS_LIST_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Used Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Buffalo: $%i\nPerenail: $%i\nVoodoo: $%i\nOceanic: $%i\nBlista Compact: $%i\nClover: $%i\nHustler: $%i\nTornado: $%i\nClub: $%i", 
						USED_BUFFALO_PRICE, USED_PERENAIL_PRICE, USED_VOODOO_PRICE, USED_OCEANIC_PRICE, USED_BLISTA_PRICE, USED_CLOVER_PRICE, USED_HUSTLER_PRICE, USED_TORNADO_PRICE, USED_CLUB_PRICE);
						return ShowPlayerDialog(playerid, LS_USED_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Motors > Used Vehicles", string, "Buy", "Back");
					}
					case 1://New Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Infernus: $%i\nCheetah: $%i\nBanshee: $%i\nTurismo: $%i\nZR-350: $%i\nComet: $%i\nSuper GT: $%i\nBullet: $%i\nSultan: $%i", 
						NEW_INFERNUS_PRICE, NEW_CHEETAH_PRICE, NEW_BANSHEE_PRICE, NEW_TURISMO_PRICE, NEW_ZR350_PRICE, NEW_COMET_PRICE, NEW_SUPERGT_PRICE, NEW_BULLET_PRICE, NEW_SULTAN_PRICE);
						return ShowPlayerDialog(playerid, LS_NEW_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Motors > New Vehicles", string, "Buy", "Back");
					}
					case 2://Special Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}BF Injection: $%i\nHotknife: $%i\nMonster: $%i\nNRG-500: $%i\nPCJ-600: $%i\nFreeway: $%i\nSanchez: $%i\nQuad: $%i\nMaverick: $%i", 
						SPECIAL_BFINJECTION_PRICE, SPECIAL_HOTKNIFE_PRICE, SPECIAL_MONSTER_PRICE, SPECIAL_NRG500_PRICE, SPECIAL_PCJ600_PRICE, SPECIAL_FREEWAY_PRICE, SPECIAL_SANCHEZ_PRICE, SPECIAL_QUAD_PRICE, SPECIAL_MAVERICK_PRICE);
						ShowPlayerDialog(playerid, LS_SPECIAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Motors > Special Vehicles", string, "Buy", "Back");
					}
				}
				return 1;
			}
			else
			{
				ShowMotorsDialog(playerid, LOS_SANTOS);
			}
			return 1;
		}
		case SF_LIST_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Used Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Buffalo: $%i\nPerenail: $%i\nVoodoo: $%i\nOceanic: $%i\nBlista Compact: $%i\nClover: $%i\nHustler: $%i\nTornado: $%i\nClub: $%i", 
						USED_BUFFALO_PRICE, USED_PERENAIL_PRICE, USED_VOODOO_PRICE, USED_OCEANIC_PRICE, USED_BLISTA_PRICE, USED_CLOVER_PRICE, USED_HUSTLER_PRICE, USED_TORNADO_PRICE, USED_CLUB_PRICE);
						return ShowPlayerDialog(playerid, SF_USED_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Motors > Used Vehicles", string, "Buy", "Back");
					}
					case 1://New Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Infernus: $%i\nCheetah: $%i\nBanshee: $%i\nTurismo: $%i\nZR-350: $%i\nComet: $%i\nSuper GT: $%i\nBullet: $%i\nSultan: $%i", 
						NEW_INFERNUS_PRICE, NEW_CHEETAH_PRICE, NEW_BANSHEE_PRICE, NEW_TURISMO_PRICE, NEW_ZR350_PRICE, NEW_COMET_PRICE, NEW_SUPERGT_PRICE, NEW_BULLET_PRICE, NEW_SULTAN_PRICE);
						return ShowPlayerDialog(playerid, SF_NEW_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Motors > New Vehicles", string, "Buy", "Back");
					}
					case 2://Special Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}BF Injection: $%i\nHotknife: $%i\nMonster: $%i\nNRG-500: $%i\nPCJ-600: $%i\nFreeway: $%i\nSanchez: $%i\nQuad: $%i\nMaverick: $%i", 
						SPECIAL_BFINJECTION_PRICE, SPECIAL_HOTKNIFE_PRICE, SPECIAL_MONSTER_PRICE, SPECIAL_NRG500_PRICE, SPECIAL_PCJ600_PRICE, SPECIAL_FREEWAY_PRICE, SPECIAL_SANCHEZ_PRICE, SPECIAL_QUAD_PRICE, SPECIAL_MAVERICK_PRICE);
						ShowPlayerDialog(playerid, SF_SPECIAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Motors > Special Vehicles", string, "Buy", "Back");
					}
				}
				return 1;
			}
			else
			{
				ShowMotorsDialog(playerid, SAN_FIERRO);
			}
			return 1;
		}
		case LV_LIST_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Used Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Buffalo: $%i\nPerenail: $%i\nVoodoo: $%i\nOceanic: $%i\nBlista Compact: $%i\nClover: $%i\nHustler: $%i\nTornado: $%i\nClub: $%i", 
						USED_BUFFALO_PRICE, USED_PERENAIL_PRICE, USED_VOODOO_PRICE, USED_OCEANIC_PRICE, USED_BLISTA_PRICE, USED_CLOVER_PRICE, USED_HUSTLER_PRICE, USED_TORNADO_PRICE, USED_CLUB_PRICE);
						return ShowPlayerDialog(playerid, LV_USED_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Motors > Used Vehicles", string, "Buy", "Back");
					}
					case 1://New Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}Infernus: $%i\nCheetah: $%i\nBanshee: $%i\nTurismo: $%i\nZR-350: $%i\nComet: $%i\nSuper GT: $%i\nBullet: $%i\nSultan: $%i", 
						NEW_INFERNUS_PRICE, NEW_CHEETAH_PRICE, NEW_BANSHEE_PRICE, NEW_TURISMO_PRICE, NEW_ZR350_PRICE, NEW_COMET_PRICE, NEW_SUPERGT_PRICE, NEW_BULLET_PRICE, NEW_SULTAN_PRICE);
						return ShowPlayerDialog(playerid, LV_NEW_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Motors > New Vehicles", string, "Buy", "Back");
					}
					case 2://Special Vehicles
					{
						new string[400];
						format(string, sizeof(string),
						"{FFFFFF}BF Injection: $%i\nHotknife: $%i\nMonster: $%i\nNRG-500: $%i\nPCJ-600: $%i\nFreeway: $%i\nSanchez: $%i\nQuad: $%i\nMaverick: $%i", 
						SPECIAL_BFINJECTION_PRICE, SPECIAL_HOTKNIFE_PRICE, SPECIAL_MONSTER_PRICE, SPECIAL_NRG500_PRICE, SPECIAL_PCJ600_PRICE, SPECIAL_FREEWAY_PRICE, SPECIAL_SANCHEZ_PRICE, SPECIAL_QUAD_PRICE, SPECIAL_MAVERICK_PRICE);
						ShowPlayerDialog(playerid, LV_SPECIAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Motors > Special Vehicles", string, "Buy", "Back");
					}
				}
				return 1;
			}
			else
			{
				ShowMotorsDialog(playerid, LAS_VENTURAS);
			}
			return 1;
		}
		case LS_USED_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyUsedVehicle(playerid, listitem);
			}
			else
			{
				ShowLSListDialog(playerid);
			}
			return 1;
		}
		case SF_USED_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyUsedVehicle(playerid, listitem);
			}
			else
			{
				ShowSFListDialog(playerid);
			}
			return 1;
		}
		case LV_USED_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyUsedVehicle(playerid, listitem);
			}
			else
			{
				ShowLVListDialog(playerid);
			}
			return 1;
		}
		case LS_NEW_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyNewVehicle(playerid, listitem);
			}
			else
			{
				ShowLSListDialog(playerid);
			}
			return 1;
		}
		case SF_NEW_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyNewVehicle(playerid, listitem);
			}
			else
			{
				ShowSFListDialog(playerid);
			}
			return 1;
		}
		case LV_NEW_DIALOG:
		{
			if(response)
			{
				OnPlayerBuyNewVehicle(playerid, listitem);
			}
			else
			{
				ShowLVListDialog(playerid);
			}
			return 1;
		}
		case LS_SPECIAL_DIALOG:
		{
			if(response)
			{
				OnPlayerBuySpecialVehicle(playerid, listitem);
			}
			else
			{
				ShowLSListDialog(playerid);
			}
			return 1;
		}
		case SF_SPECIAL_DIALOG:
		{
			if(response)
			{
				OnPlayerBuySpecialVehicle(playerid, listitem);
			}
			else
			{
				ShowSFListDialog(playerid);
			}
			return 1;
		}
		case LV_SPECIAL_DIALOG:
		{
			if(response)
			{
				OnPlayerBuySpecialVehicle(playerid, listitem);
			}
			else
			{
				ShowLVListDialog(playerid);
			}
			return 1;
		}
		case LS_MOTORS_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						ShowLSListDialog(playerid);
					}
					case 1:
					{
						new Float:pos[3], string[200], name[32], characterid = GetPlayerCharacterID(playerid);
						foreach(new v : Vehicle)
						{
							if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
							{
								GetVehiclePos(v, pos[0], pos[1], pos[2]);
								if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
								{
									GetVehicleModelName(VehicleData[v][vehicle_model], name, sizeof(name));

									SetPlayerTradeVehicle(playerid, v);

    								format(string, sizeof(string), "{FFFFFF}Are you sure you want to trade your %s in for $%i?", name, (VehicleData[v][vehicle_price] / 2));
									return ShowPlayerDialog(playerid, LS_VERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Los Santos Motors > Trade-In Vehicle", string, "Yes", "No");
								}
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: You must be next to an owned vehicle to trade it in.");
					}
				}
			}
			return 1;
		}
		case SF_MOTORS_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						ShowSFListDialog(playerid);
					}
					case 1:
					{
						new Float:pos[3], string[200], name[32], characterid = GetPlayerCharacterID(playerid);
						foreach(new v : Vehicle)
						{
							if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
							{
								GetVehiclePos(v, pos[0], pos[1], pos[2]);
								if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
								{
									GetVehicleModelName(VehicleData[v][vehicle_model], name, sizeof(name));

									SetPlayerTradeVehicle(playerid, v);

    								format(string, sizeof(string), "{FFFFFF}Are you sure you want to trade your %s in for $%i?", name, (VehicleData[v][vehicle_price] / 2));
									return ShowPlayerDialog(playerid, SF_VERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Los Santos Motors > Trade-In Vehicle", string, "Yes", "No");
								}
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: You must be next to an owned vehicle to trade it in.");
					}
				}
			}
			return 1;
		}
		case LV_MOTORS_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						ShowLVListDialog(playerid);
					}
					case 1:
					{
						new Float:pos[3], string[200], name[32], characterid = GetPlayerCharacterID(playerid);
						foreach(new v : Vehicle)
						{
							if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
							{
								GetVehiclePos(v, pos[0], pos[1], pos[2]);
								if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
								{
									GetVehicleModelName(VehicleData[v][vehicle_model], name, sizeof(name));

									SetPlayerTradeVehicle(playerid, v);

    								format(string, sizeof(string), "{FFFFFF}Are you sure you want to trade your %s in for $%i?", name, (VehicleData[v][vehicle_price] / 2));
									return ShowPlayerDialog(playerid, LV_VERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Los Santos Motors > Trade-In Vehicle", string, "Yes", "No");
								}
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: You must be next to an owned vehicle to trade it in.");
					}
				}
			}
			return 1;
		}
		case LS_VERIFY_DIALOG, SF_VERIFY_DIALOG, LV_VERIFY_DIALOG:
		{
			if(response)
			{
				OnPlayerTradeInVehicle(playerid);
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == MotorsData[ls_motors_pickup] || pickupid == MotorsData[sf_motors_pickup] || pickupid == MotorsData[lv_motors_pickup]) return 1;
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == MotorsData[ls_motors_cp])
		{
			return ShowMotorsDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == MotorsData[sf_motors_cp])
		{
			return ShowMotorsDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == MotorsData[lv_motors_cp])
		{
			return ShowMotorsDialog(playerid, LAS_VENTURAS);
		}
	}
	return 1;
}

public DisableVehicleAlarm(vehicleid)//Do not hook
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    if(alarm == VEHICLE_PARAMS_ON)
    {
    	VehicleData[vehicleid][vehicle_alarm] = VEHICLE_PARAMS_OFF;
    	SetVehicleParamsEx_Fixed(vehicleid, engine, lights, VEHICLE_PARAMS_OFF, doors, bonnet, boot, objective);
    }
	return 1;
}

task OnVehicleUseFuel[30000]()
{
	foreach(new v : Vehicle)
	{
		if(!IsVehicleBicycle(v) && VehicleData[v][vehicle_engine] == VEHICLE_PARAMS_ON)
		{
			new driverid = GetVehicleDriverID(v);
			VehicleData[v][vehicle_fuel]--;

			if(VehicleData[v][vehicle_fuel] > 0)
			{
				if(VehicleData[v][vehicle_fuel] <= 5 && driverid != INVALID_PLAYER_ID)
				{
					if(driverid != INVALID_PLAYER_ID)
					{
						SendClientMessage(driverid, ORANGE, "NOTICE: This vehicle is almost out of fuel.");
					}
				}
	        }
	        else
	        {
	        	if(VehicleData[v][vehicle_engine] == VEHICLE_PARAMS_ON)
	        	{
		    		VehicleData[v][vehicle_engine] = VEHICLE_PARAMS_OFF;
		    		SetVehicleParamsEx_Fixed(v, VehicleData[v][vehicle_engine], VehicleData[v][vehicle_lights], VehicleData[v][vehicle_alarm], VehicleData[v][vehicle_locked], VehicleData[v][vehicle_bonnet], VehicleData[v][vehicle_boot], VehicleData[v][vehicle_objective]);
				}

				if(driverid != INVALID_PLAYER_ID)
				{
		    		RemovePlayerFromVehicle(driverid);
					SendClientMessage(driverid, RED, "ERROR: This vehicle is out of fuel.");
				}
	        }
        }
	}
	return 1;
}

YCMD:engine(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, RED, "ERROR: You must be in the drivers seat of a vehicle to toggle the engine.");

	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsVehicleBicycle(vehicleid)) return SendClientMessage(playerid, RED, "ERROR: This bicycle does not have an engine.");

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(engine == VEHICLE_PARAMS_OFF)
	{
		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		foreach(new i : Player)
		{
			if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
			{
				format(string, sizeof(string), "** %s turns on their engine...", name);
				SendClientMessage(i, GREY, string);
			}
		}
		
		SetVehicleParamsEx_Fixed(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
	}
	else
	{
		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		foreach(new i : Player)
		{
			if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
			{
				format(string, sizeof(string), "** %s turns off their engine...", name);
				SendClientMessage(i, GREY, string);
			}
		}
		
		SetVehicleParamsEx_Fixed(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}

YCMD:lights(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, RED, "ERROR: You must be in the drivers seat of a vehicle to toggle the lights.");

	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsVehicleBicycle(vehicleid)) return SendClientMessage(playerid, RED, "ERROR: This bicycle does not have any lights.");

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine == VEHICLE_PARAMS_OFF) return SendClientMessage(playerid, RED, "ERROR: The engine must be on to be able to toggle the lights.");

	if(lights == VEHICLE_PARAMS_OFF)
	{
		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		foreach(new i : Player)
		{
			if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
			{
				format(string, sizeof(string), "** %s turns on their lights...", name);
				SendClientMessage(i, GREY, string);
			}
		}
		
		SetVehicleParamsEx_Fixed(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
	}
	else
	{
		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		foreach(new i : Player)
		{
			if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
			{
				format(string, sizeof(string), "** %s turns off their lights...", name);
				SendClientMessage(i, GREY, string);
			}
		}
		
		SetVehicleParamsEx_Fixed(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}

YCMD:trunk(playerid, params[], help)
{
    new vehicleid = GetNearestVehicle(playerid);
    if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessage(playerid, RED, "ERROR: You must be next to a vehicle to use this command.");

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(boot == VEHICLE_PARAMS_OFF)
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_ON, objective);
	}
	else
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_OFF, objective);
	}
	return 1;
}

YCMD:hood(playerid, params[], help)
{
    new vehicleid = GetNearestVehicle(playerid);
    if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessage(playerid, RED, "ERROR: You must be next to a vehicle to use this command.");

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(bonnet == VEHICLE_PARAMS_OFF)
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_ON, objective);
	}
	else
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_OFF, objective);
	}
	return 1;
}

YCMD:alarm(playerid, params[], help)
{
    new vehicleid = GetNearestVehicle(playerid);
    if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessage(playerid, RED, "ERROR: You must be next to a vehicle to use this command.");

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(alarm == VEHICLE_PARAMS_OFF)
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, VEHICLE_PARAMS_ON, doors, bonnet, boot, objective);
	}
	else
	{
	    SetVehicleParamsEx_Fixed(vehicleid, engine, lights, VEHICLE_PARAMS_OFF, doors, bonnet, boot, objective);
	}
	return 1;
}

YCMD:park(playerid, params[], help)
{
	new vehicleid = GetPlayerVehicleID(playerid), Float:pos[4], string[128], name[24], characterid = GetPlayerCharacterID(playerid);
	if(!IsPlayerInAnyVehicle(playerid) || characterid != GetVehicleCharacterID(vehicleid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a vehicle you own to use this command.");

	GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
	GetVehicleZAngle(vehicleid, pos[3]);

	VehicleData[vehicleid][vehicle_x] = pos[0];
	VehicleData[vehicleid][vehicle_y] = pos[1];
	VehicleData[vehicleid][vehicle_z] = pos[2];
	VehicleData[vehicleid][vehicle_a] = pos[3];

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerName(playerid, name, sizeof(name));

	foreach(new i : Player)
	{
		if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
	  	{
			format(string, sizeof(string), "** %s parks their vehicle...", name);
	     	SendClientMessage(i, GREY, string);
	    }
	}
	return 1;
}

YCMD:lock(playerid, params[], help)
{
    new vehicleid, string[128], Float:pos[3], name[24], characterid = GetPlayerCharacterID(playerid);
    if(IsPlayerInAnyVehicle(playerid) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
    {
    	vehicleid = GetPlayerVehicleID(playerid);
    	if(characterid != GetVehicleCharacterID(vehicleid)) return SendClientMessage(playerid, RED, "ERROR: You can only lock vehicles you own.");
    }
    else
    {
    	vehicleid = GetNearestVehicle(playerid);
	    if(vehicleid == INVALID_VEHICLE_ID || characterid != GetVehicleCharacterID(vehicleid)) return SendClientMessage(playerid, RED, "ERROR: You must be next to a vehicle you own to use this command.");
    }

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerName(playerid, name, sizeof(name));

	if(doors == VEHICLE_PARAMS_OFF)
	{
		SetVehicleParamsForAll(vehicleid, VehicleData[vehicleid][vehicle_objective], VEHICLE_PARAMS_ON);
		SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);

		foreach(new i : Player)
		{
		  	if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
		 	{
				format(string, sizeof(string), "** %s locks their vehicle...", name);
		    	SendClientMessage(i, GREY, string);
		 	}
		}
		return 1;
	}
	else
	{
		SetVehicleParamsForAll(vehicleid, VehicleData[vehicleid][vehicle_objective], VEHICLE_PARAMS_OFF);
		SetVehicleParamsEx_Fixed(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);

		foreach(new i : Player)
		{
		 	if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
		 	{
				format(string, sizeof(string), "** %s unlocks their vehicle...", name);
		     	SendClientMessage(i, GREY, string);
		 	}
		}
	}
	return 1;
}

YCMD:torch(playerid, params[], help)
{
	new string[128], Float:health, vehicleid = GetNearestVehicle(playerid), slot = CheckInventoryForItem(playerid, JERRYCAN_MODEL);
    if(!GetPlayerVIP(playerid) && GetPlayerScore(playerid) < MIN_SCORE_TORCH_VEHICLES)
    {
    	format(string, sizeof(string), "ERROR: You need at least %i score to torch vehicles.", MIN_SCORE_TORCH_VEHICLES);
    	return SendClientMessage(playerid, RED, string);
    }
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
    if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessage(playerid, RED, "ERROR: You must be next to a vehicle to use this command.");
    if(VehicleData[vehicleid][vehicle_owned] == true) return SendClientMessage(playerid, RED, "ERROR: You cannot torch owned vehicles.");
    if(GetVehicleSpeed(vehicleid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot torch moving vehicles.");

    if(GetPlayerJob(playerid) != CIVILIAN_JOB)
    {
    	format(string, sizeof(string), "ERROR: You cannot torch vehicles while you are clocked on as a: %s", ReturnPlayerJob(playerid));
		return SendClientMessage(playerid, RED, string);
	}
	if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You need to have a Jerrycan to be able to torch the vehicle.");
	
	GetVehicleHealth(vehicleid, health);
	if(health < 250) return SendClientMessage(playerid, RED, "ERROR: That vehicle is already on fire and is about to explode.");

	RemoveItemFromInventory(playerid, slot, 1, false);

    ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
	return SetVehicleHealth(vehicleid, 0.0);
}

YCMD:findcars(playerid, params[], help)
{
	new count = 0, Float:pos[3], string[144], name[32], characterid = GetPlayerCharacterID(playerid);
	foreach(new v : Vehicle)
	{
		if(VehicleData[v][vehicle_owned] == true && characterid == GetVehicleCharacterID(v))
		{
			GetVehiclePos(v, pos[0], pos[1], pos[2]);
			GetVehicleModelName(VehicleData[v][vehicle_model], name, sizeof(name));

			for(new z = 0; z < sizeof(sa_zones); z++)
			{
				if(pos[0] >= sa_zones[z][zone_area][0] && pos[0] <= sa_zones[z][zone_area][3] && pos[1] >= sa_zones[z][zone_area][1] && pos[1] <= sa_zones[z][zone_area][4])
				{
					new Float:dist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);
					format(string, sizeof(string), "SERVER: Your %s is located in: %s (%0.2f Metres Away)", name, sa_zones[z][zone_name], dist);
					break;
				}
			}
			SendClientMessage(playerid, WHITE, string);
			count++;
		}
	}

	if(count == 0)
	{
		SendClientMessage(playerid, RED, "ERROR: You don't own any vehicles.");
	}
	return 1;
}
