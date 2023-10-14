#include <YSI_Coding\y_hooks>

new BannableWeapons[] =
{
    9,//Chainsaw
    10,//Purple Dildo
    11,//Small White Vibrator
    12,//Large White Vibrator
    13,//Silver Vibrator
    14,//Flowers
    16,//Grenades
    17,//Tear Gas
    18,//Molotov Cocktail
    35,//Rocket Launcher
    36,//HS Rocket Launcher
	37,//Flamethrower
	38,//Minigun
	39,//Satchel Charge
	40,//Detonator
	42,//Fire Extinguisher
	43,//Camera
	44,//Nightvision Goggles
	45//Thermal Goggles
};

enum weapon_data
{
	weapon_1,
	weapon_1a,
	weapon_2,
	weapon_2a,
	weapon_3,
	weapon_3a,
	weapon_4,
	weapon_4a,
	weapon_5,
	weapon_5a,
	weapon_6,
	weapon_6a,
	weapon_7,
	weapon_7a,
	weapon_8,
	weapon_8a,
	weapon_9,
	weapon_9a,
	weapon_10,
	weapon_10a,
	weapon_11,
	weapon_11a,
	weapon_12,
	weapon_12a,
};
new WeaponData[MAX_PLAYERS][weapon_data];

stock LoadWeaponData(playerid)
{
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `WEAPONS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		WeaponData[playerid][weapon_1] = db_get_field_assoc_int(database_result, "W1");
		WeaponData[playerid][weapon_1a] = db_get_field_assoc_int(database_result, "W1A");
		WeaponData[playerid][weapon_2] = db_get_field_assoc_int(database_result, "W2");
		WeaponData[playerid][weapon_2a] = db_get_field_assoc_int(database_result, "W2A");
		WeaponData[playerid][weapon_3] = db_get_field_assoc_int(database_result, "W3");
		WeaponData[playerid][weapon_3a] = db_get_field_assoc_int(database_result, "W3A");
		WeaponData[playerid][weapon_4] = db_get_field_assoc_int(database_result, "W4");
		WeaponData[playerid][weapon_4a] = db_get_field_assoc_int(database_result, "W4A");
		WeaponData[playerid][weapon_5] = db_get_field_assoc_int(database_result, "W5");
		WeaponData[playerid][weapon_5a] = db_get_field_assoc_int(database_result, "W5A");
		WeaponData[playerid][weapon_6] = db_get_field_assoc_int(database_result, "W6");
		WeaponData[playerid][weapon_6a] = db_get_field_assoc_int(database_result, "W6A");
		WeaponData[playerid][weapon_7] = db_get_field_assoc_int(database_result, "W7");
		WeaponData[playerid][weapon_7a] = db_get_field_assoc_int(database_result, "W7A");
		WeaponData[playerid][weapon_8] = db_get_field_assoc_int(database_result, "W8");
		WeaponData[playerid][weapon_8a] = db_get_field_assoc_int(database_result, "W8A");
		WeaponData[playerid][weapon_9] = db_get_field_assoc_int(database_result, "W9");
		WeaponData[playerid][weapon_9a] = db_get_field_assoc_int(database_result, "W9A");
		WeaponData[playerid][weapon_10] = db_get_field_assoc_int(database_result, "W10");
		WeaponData[playerid][weapon_10a] = db_get_field_assoc_int(database_result, "W10A");
		WeaponData[playerid][weapon_11] = db_get_field_assoc_int(database_result, "W11");
		WeaponData[playerid][weapon_11a] = db_get_field_assoc_int(database_result, "W11A");
		WeaponData[playerid][weapon_12] = db_get_field_assoc_int(database_result, "W12");
		WeaponData[playerid][weapon_12a] = db_get_field_assoc_int(database_result, "W12A");
	}
	db_free_result@(database_result);
	return 1;
}

stock SaveWeaponData(playerid)
{
	new query[800], w[12], a[12], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT * FROM `WEAPONS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		if(GetDutyStatus(playerid) == true || GetCameraStatus(playerid) == true || IsPlayerSafe(playerid) == true)
		{
			w[0] = StoredData[playerid][stored_melee];
			a[0] = StoredData[playerid][stored_meleeammo];
			w[1] = StoredData[playerid][stored_handgun];
			a[1] = StoredData[playerid][stored_handgunammo];
			w[2] = StoredData[playerid][stored_shotgun];
			a[2] = StoredData[playerid][stored_shotgunammo];
			w[3] = StoredData[playerid][stored_smg];
			a[3] = StoredData[playerid][stored_smgammo];
			w[4] = StoredData[playerid][stored_assault];
			a[4] = StoredData[playerid][stored_assaultammo];
			w[5] = StoredData[playerid][stored_rifle];
			a[5] = StoredData[playerid][stored_rifleammo];
			w[6] = StoredData[playerid][stored_heavy];
			a[6] = StoredData[playerid][stored_heavyammo];
			w[7] = StoredData[playerid][stored_throw];
			a[7] = StoredData[playerid][stored_throwammo];
			w[8] = StoredData[playerid][stored_action];
			a[8] = StoredData[playerid][stored_actionammo];
			w[9] = StoredData[playerid][stored_handheld];
			a[9] = StoredData[playerid][stored_handheldammo];
			w[10] = StoredData[playerid][stored_special];
			a[10] = StoredData[playerid][stored_specialammo];
			w[11] = StoredData[playerid][stored_remote];
			a[11] = StoredData[playerid][stored_remoteammo];
		}
		else
		{
		    GetPlayerWeaponData(playerid, 1, w[0], a[0]);
			GetPlayerWeaponData(playerid, 2, w[1], a[1]);
			GetPlayerWeaponData(playerid, 3, w[2], a[2]);
			GetPlayerWeaponData(playerid, 4, w[3], a[3]);
			GetPlayerWeaponData(playerid, 5, w[4], a[4]);
			GetPlayerWeaponData(playerid, 6, w[5], a[5]);
			GetPlayerWeaponData(playerid, 7, w[6], a[6]);
			GetPlayerWeaponData(playerid, 8, w[7], a[7]);
			GetPlayerWeaponData(playerid, 9, w[8], a[8]);
			GetPlayerWeaponData(playerid, 10, w[9], a[9]);
			GetPlayerWeaponData(playerid, 11, w[10], a[10]);
			GetPlayerWeaponData(playerid, 12, w[11], a[11]);
		}

		format(query, sizeof(query), 
		"UPDATE `WEAPONS` SET W1 = '%i', W1A = '%i', W2 = '%i', W2A = '%i', W3 = '%i', W3A = '%i', W4 = '%i', W4A = '%i', W5 = '%i', W5A = '%i', W6 = '%i', W6A = '%i', W7 = '%i', W7A = '%i', W8 = '%i', W8A = '%i', W9 = '%i', W9A = '%i', W10 = '%i', W10A = '%i', W11 = '%i', W11A = '%i', W12 = '%i', W12A = '%i' WHERE `CHARACTER_ID` = '%i'", 
		w[0], a[0], w[1], a[1], w[2], a[2], w[3], a[3], w[4], a[4], w[5], a[5], w[6], a[6], w[7], a[7], w[8], a[8], w[9], a[9], w[10], a[10], w[11], a[11], id);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `WEAPONS` (`CHARACTER_ID`, `W1`, `W1A`, `W2`, `W2A`, `W3`, `W3A`, `W4`, `W4A`, `W5`, `W5A`, `W6`, `W6A`, `W7`, `W7A`, `W8`, `W8A`, `W9`, `W9A`, `W10`, `W10A`, `W11`, `W11A`, `W12`, `W12A`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		id, w[0], a[0], w[1], a[1], w[2], a[2], w[3], a[3], w[4], a[4], w[5], a[5], w[6], a[6], w[7], a[7], w[8], a[8], w[9], a[9], w[10], a[10], w[11], a[11]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	db_free_result@(database_result);
	return 1;
}

stock GivePlayerWeapons(playerid)
{
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_1], WeaponData[playerid][weapon_1a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_2], WeaponData[playerid][weapon_2a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_3], WeaponData[playerid][weapon_3a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_4], WeaponData[playerid][weapon_4a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_5], WeaponData[playerid][weapon_5a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_6], WeaponData[playerid][weapon_6a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_7], WeaponData[playerid][weapon_7a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_8], WeaponData[playerid][weapon_8a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_9], WeaponData[playerid][weapon_9a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_10], WeaponData[playerid][weapon_10a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_11], WeaponData[playerid][weapon_11a]);
	GivePlayerWeapon(playerid, WeaponData[playerid][weapon_12], WeaponData[playerid][weapon_12a]);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		WeaponData[playerid][weapon_1] = 0;
		WeaponData[playerid][weapon_1a] = 0;
		WeaponData[playerid][weapon_2] = 0;
		WeaponData[playerid][weapon_2a] = 0;
		WeaponData[playerid][weapon_3] = 0;
		WeaponData[playerid][weapon_3a] = 0;
		WeaponData[playerid][weapon_4] = 0;
		WeaponData[playerid][weapon_4a] = 0;
		WeaponData[playerid][weapon_5] = 0;
		WeaponData[playerid][weapon_5a] = 0;
		WeaponData[playerid][weapon_6] = 0;
		WeaponData[playerid][weapon_6a] = 0;
		WeaponData[playerid][weapon_7] = 0;
		WeaponData[playerid][weapon_7a] = 0;
		WeaponData[playerid][weapon_8] = 0;
		WeaponData[playerid][weapon_8a] = 0;
		WeaponData[playerid][weapon_9] = 0;
		WeaponData[playerid][weapon_9a] = 0;
		WeaponData[playerid][weapon_10] = 0;
		WeaponData[playerid][weapon_10a] = 0;
		WeaponData[playerid][weapon_11] = 0;
		WeaponData[playerid][weapon_11a] = 0;
		WeaponData[playerid][weapon_12] = 0;
		WeaponData[playerid][weapon_12a] = 0;
	}
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		if(GetPlayerVIP(playerid))
		{
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);
		}
		else
		{
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 40);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 500);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 50);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 250);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 200);
		    SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 300);
		}
	}
    return 1;
}
