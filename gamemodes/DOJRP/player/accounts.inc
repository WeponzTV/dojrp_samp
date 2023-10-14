#include <YSI_Coding\y_hooks>

forward OnPlayerRegister(playerid);
forward OnPlayerLogin(playerid, bool:success);

forward OnPasswordChange(playerid);

forward CheckForInjuries(playerid);

enum player_data
{
	player_master,
	player_character,
	player_name[24],
	player_logins,
	player_date[16],
	player_level,
	bool:player_vip,
	player_score,
	player_money,
	player_skin,
	player_job,
	player_style,
	player_healed,
	player_wanted,
	player_time,
	player_dept,
	player_paramedic,
	player_charid,
	Float:player_health,
	Float:player_armour,
	Float:player_x,
	Float:player_y,
	Float:player_z,
	Float:player_a,
	player_int,
	player_world,
	player_fails,
	player_hospital,
	player_hunger,
	player_thirst,
	player_injuries,
	player_onwounded,
	player_killerid,
	player_clantag[8],
	player_claninvite[8],
	player_warns,
	player_lastrob,
	player_tradeveh,
	bool:player_isinvited,
	bool:player_iswounded,
	bool:player_canaccept,
	bool:player_alert1,
	bool:player_alert2,
	bool:player_logged,
	bool:player_spawned,
	bool:player_death,
	bool:player_registered,
	bool:player_rejail,
	bool:player_new,
	bool:player_safe,
	bool:player_duty,
	bool:player_spectated,
	bool:player_muted
};
new PlayerData[MAX_PLAYERS][player_data];

enum stored_data
{
	Float:stored_x,
	Float:stored_y,
	Float:stored_z,
	Float:stored_a,
	stored_int,
	stored_world,
	stored_stars,
	stored_skin,
	Float:stored_health,
	Float:stored_armour,
	stored_melee,
	stored_meleeammo,
	stored_handgun,
	stored_handgunammo,
	stored_smg,
	stored_smgammo,
	stored_shotgun,
	stored_shotgunammo,
	stored_assault,
	stored_assaultammo,
	stored_rifle,
	stored_rifleammo,
	stored_heavy,
	stored_heavyammo,
	stored_throw,
	stored_throwammo,
	stored_action,
	stored_actionammo,
	stored_handheld,
	stored_handheldammo,
	stored_special,
	stored_specialammo,
	stored_remote,
	stored_remoteammo
};
new StoredData[MAX_PLAYERS][stored_data];

enum cam_data
{
	cam_mode,
	cam_flyobject,
	cam_keys,
	cam_leftright,
	cam_updown,
	cam_lastmove,
	Float:cam_acceleration,
	bool:cam_status
}
new CamData[MAX_PLAYERS][cam_data];

stock bool:GetCameraStatus(playerid) return CamData[playerid][cam_status];
stock SetCameraStatus(playerid, bool:status) return CamData[playerid][cam_status] = status;

stock IsPlayerLogged(playerid) return PlayerData[playerid][player_logged];

stock bool:GetPlayerMuted(playerid) return PlayerData[playerid][player_muted];
stock SetPlayerMuted(playerid, bool:status) return PlayerData[playerid][player_muted] = status;

stock GetPlayerWarns(playerid) return PlayerData[playerid][player_warns];
stock SetPlayerWarns(playerid, amount) return PlayerData[playerid][player_warns] = amount;

stock IsPlayerNew(playerid) return PlayerData[playerid][player_new];
stock SetPlayerNew(playerid, bool:status) return PlayerData[playerid][player_new] = status;

stock GetPlayerMasterID(playerid) return PlayerData[playerid][player_master];
stock GetPlayerCharacterID(playerid) return PlayerData[playerid][player_character];

stock GetPlayerLevel(playerid) return PlayerData[playerid][player_level];
stock SetPlayerLevel(playerid, level) return PlayerData[playerid][player_level] = level;

stock bool:GetPlayerVIP(playerid) return PlayerData[playerid][player_vip];
stock SetPlayerVIP(playerid, bool:status) return PlayerData[playerid][player_vip] = status;

stock GetPlayerJob(playerid) return PlayerData[playerid][player_job];
stock SetPlayerJob(playerid, type) return PlayerData[playerid][player_job] = type;

stock bool:IsPlayerSafe(playerid) return PlayerData[playerid][player_safe];
stock SetPlayerSafe(playerid, bool:status) return PlayerData[playerid][player_safe] = status;

stock bool:GetDutyStatus(playerid) return PlayerData[playerid][player_duty];
stock SetDutyStatus(playerid, bool:status) return PlayerData[playerid][player_duty] = status;

stock GetPlayerDept(playerid) return PlayerData[playerid][player_dept];
stock SetPlayerDept(playerid, city) return PlayerData[playerid][player_dept] = city;

stock GetPlayerJailTime(playerid) return PlayerData[playerid][player_time];
stock SetPlayerJailTime(playerid, time) return PlayerData[playerid][player_time] = time;

stock IsRejail(playerid) return PlayerData[playerid][player_rejail];
stock SetRejail(playerid, bool:status) return PlayerData[playerid][player_rejail] = status;

stock bool:GetPlayerRejail(playerid) return PlayerData[playerid][player_rejail];
stock SetPlayerRejail(playerid, bool:status) return PlayerData[playerid][player_rejail] = status;

stock bool:GetPlayerSpectated(playerid) return PlayerData[playerid][player_spectated];
stock SetPlayerSpectated(playerid, bool:status) return PlayerData[playerid][player_spectated] = status;

stock bool:GetIsInvited(playerid) return PlayerData[playerid][player_isinvited];
stock SetIsInvited(playerid, bool:status) return PlayerData[playerid][player_isinvited] = status;

stock GetPlayerHospital(playerid) return PlayerData[playerid][player_hospital];
stock SetPlayerHospital(playerid, city) return PlayerData[playerid][player_hospital] = city;

stock GetPlayerSkinEx(playerid) return PlayerData[playerid][player_skin];
stock SetPlayerSkinEx(playerid, skinid) return PlayerData[playerid][player_skin] = skinid;

stock Float:GetPlayerHealthEx(playerid) return PlayerData[playerid][player_health];
stock SetPlayerHealthEx(playerid, Float:health)
{
	PlayerData[playerid][player_health] = health;
	return 1;
}

stock Float:GetPlayerArmourEx(playerid) return PlayerData[playerid][player_armour];
stock SetPlayerArmourEx(playerid, Float:armour)
{
	PlayerData[playerid][player_armour] = armour;
	return 1;
}

stock GetPlayerThirst(playerid) return PlayerData[playerid][player_thirst];
stock GetPlayerHunger(playerid) return PlayerData[playerid][player_hunger];

stock SetPlayerThirst(playerid, amount) return PlayerData[playerid][player_thirst] = amount;
stock SetPlayerHunger(playerid, amount) return PlayerData[playerid][player_hunger] = amount;

stock GetPlayerLastRobbery(playerid) return PlayerData[playerid][player_lastrob];
stock SetPlayerLastRobbery(playerid, time) return PlayerData[playerid][player_lastrob] = time;

stock GetPlayerParamedic(playerid) return PlayerData[playerid][player_paramedic];
stock SetPlayerParamedic(playerid, targetid) return PlayerData[playerid][player_paramedic] = targetid;

stock GetPlayerLastHeal(playerid) return PlayerData[playerid][player_healed];
stock SetPlayerLastHeal(playerid, time) return PlayerData[playerid][player_healed] = time;

stock GetPlayerTradeVehicle(playerid) return PlayerData[playerid][player_tradeveh];
stock SetPlayerTradeVehicle(playerid, vehicleid) return PlayerData[playerid][player_tradeveh] = vehicleid;

stock GetStoredWantedLevel(playerid) return StoredData[playerid][stored_stars];
stock SetStoredWantedLevel(playerid, level) return StoredData[playerid][stored_stars] = level;

stock GetStoredSkin(playerid) return StoredData[playerid][stored_skin];
stock SetStoredSkin(playerid, skinid) return StoredData[playerid][stored_skin] = skinid;

stock StorePlayerPosition(playerid)
{
	GetPlayerPos(playerid, StoredData[playerid][stored_x], StoredData[playerid][stored_y], StoredData[playerid][stored_z]);
	GetPlayerFacingAngle(playerid, StoredData[playerid][stored_a]);
	StoredData[playerid][stored_int] = GetPlayerInterior(playerid);
	StoredData[playerid][stored_world] = GetPlayerVirtualWorld(playerid);
	return 1;
}

stock RestorePlayerPosition(playerid)
{
	SetPlayerInterior(playerid, StoredData[playerid][stored_int]);
	SetPlayerVirtualWorld(playerid, StoredData[playerid][stored_world]);
	SetPlayerPos(playerid, StoredData[playerid][stored_x], StoredData[playerid][stored_y], StoredData[playerid][stored_z]);
	SetPlayerFacingAngle(playerid, StoredData[playerid][stored_a]);
	return SetCameraBehindPlayer(playerid);
}

stock Float:GetStoredHealth(playerid) return StoredData[playerid][stored_health];
stock SetStoredHealth(playerid, Float:health)
{
	StoredData[playerid][stored_health] = health;
	return 1;
}

stock Float:GetStoredArmour(playerid) return StoredData[playerid][stored_armour];
stock SetStoredArmour(playerid, Float:armour)
{
	StoredData[playerid][stored_armour] = armour;
	return 1;
}

stock StoreWeaponData(playerid)
{
	new weapon[12], ammo[12];
	GetPlayerWeaponData(playerid, 1, weapon[0], ammo[0]);
	GetPlayerWeaponData(playerid, 2, weapon[1], ammo[1]);
	GetPlayerWeaponData(playerid, 3, weapon[2], ammo[2]);
	GetPlayerWeaponData(playerid, 4, weapon[3], ammo[3]);
	GetPlayerWeaponData(playerid, 5, weapon[4], ammo[4]);
	GetPlayerWeaponData(playerid, 6, weapon[5], ammo[5]);
	GetPlayerWeaponData(playerid, 7, weapon[6], ammo[6]);
	GetPlayerWeaponData(playerid, 8, weapon[7], ammo[7]);
	GetPlayerWeaponData(playerid, 9, weapon[8], ammo[8]);
	GetPlayerWeaponData(playerid, 10, weapon[9], ammo[9]);
	GetPlayerWeaponData(playerid, 11, weapon[10], ammo[10]);
	GetPlayerWeaponData(playerid, 12, weapon[11], ammo[11]);

	StoredData[playerid][stored_melee] = weapon[0];
	StoredData[playerid][stored_meleeammo] = ammo[0];
	StoredData[playerid][stored_handgun] = weapon[1];
	StoredData[playerid][stored_handgunammo] = ammo[1];
	StoredData[playerid][stored_shotgun] = weapon[2];
	StoredData[playerid][stored_shotgunammo] = ammo[2];
	StoredData[playerid][stored_smg] = weapon[3];
	StoredData[playerid][stored_smgammo] = ammo[3];
	StoredData[playerid][stored_assault] = weapon[4];
	StoredData[playerid][stored_assaultammo] = ammo[4];
	StoredData[playerid][stored_rifle] = weapon[5];
	StoredData[playerid][stored_rifleammo] = ammo[5];
	StoredData[playerid][stored_heavy] = weapon[6];
	StoredData[playerid][stored_heavyammo] = ammo[6];
	StoredData[playerid][stored_throw] = weapon[7];
	StoredData[playerid][stored_throwammo] = ammo[7];
	StoredData[playerid][stored_action] = weapon[8];
	StoredData[playerid][stored_actionammo] = ammo[8];
	StoredData[playerid][stored_handheld] = weapon[9];
	StoredData[playerid][stored_handheldammo] = ammo[9];
	StoredData[playerid][stored_special] = weapon[10];
	StoredData[playerid][stored_specialammo] = ammo[10];
	StoredData[playerid][stored_remote] = weapon[11];
	StoredData[playerid][stored_remoteammo] = ammo[11];
	return 1;
}

stock RestoreStoredWeapons(playerid)
{
	GivePlayerWeapon(playerid, StoredData[playerid][stored_melee], StoredData[playerid][stored_meleeammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_handgun], StoredData[playerid][stored_handgunammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_shotgun], StoredData[playerid][stored_shotgunammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_smg], StoredData[playerid][stored_smgammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_assault], StoredData[playerid][stored_assaultammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_rifle], StoredData[playerid][stored_rifleammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_heavy], StoredData[playerid][stored_heavyammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_throw], StoredData[playerid][stored_throwammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_action], StoredData[playerid][stored_actionammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_handheld], StoredData[playerid][stored_handheldammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_special], StoredData[playerid][stored_specialammo]);
	GivePlayerWeapon(playerid, StoredData[playerid][stored_remote], StoredData[playerid][stored_remoteammo]);
	return 1;
}

stock ResetStoredData(playerid)
{
	StoredData[playerid][stored_x] = FIRST_SPAWN_X;
	StoredData[playerid][stored_y] = FIRST_SPAWN_Y;
	StoredData[playerid][stored_z] = FIRST_SPAWN_Z;
	StoredData[playerid][stored_a] = FIRST_SPAWN_A;
	StoredData[playerid][stored_int] = FIRST_SPAWN_INT;
	StoredData[playerid][stored_world] = FIRST_SPAWN_WORLD;

	StoredData[playerid][stored_stars] = 0;
	StoredData[playerid][stored_skin] = 0;

	StoredData[playerid][stored_health] = 0.0;
	StoredData[playerid][stored_armour] = 0.0;

	StoredData[playerid][stored_melee] = 0;
	StoredData[playerid][stored_meleeammo] = 0;
	StoredData[playerid][stored_handgun] = 0;
	StoredData[playerid][stored_handgunammo] = 0;
	StoredData[playerid][stored_smg] = 0;
	StoredData[playerid][stored_smgammo] = 0;
	StoredData[playerid][stored_shotgun] = 0;
	StoredData[playerid][stored_shotgunammo] = 0;
	StoredData[playerid][stored_assault] = 0;
	StoredData[playerid][stored_assaultammo] = 0;
	StoredData[playerid][stored_rifle] = 0;
	StoredData[playerid][stored_rifleammo] = 0;
	StoredData[playerid][stored_heavy] = 0;
	StoredData[playerid][stored_heavyammo] = 0;
	StoredData[playerid][stored_throw] = 0;
	StoredData[playerid][stored_throwammo] = 0;
	StoredData[playerid][stored_action] = 0;
	StoredData[playerid][stored_actionammo] = 0;
	StoredData[playerid][stored_handheld] = 0;
	StoredData[playerid][stored_handheldammo] = 0;
	StoredData[playerid][stored_special] = 0;
	StoredData[playerid][stored_specialammo] = 0;
	StoredData[playerid][stored_remote] = 0;
	StoredData[playerid][stored_remoteammo] = 0;
	return 1;
}

stock IsPlayerInjured(playerid)
{
	new Float:health;
	GetPlayerHealth(playerid, health);
	if(health != MAX_HEALTH)
	{
		if(health == 1.0 || health == 2.0) return 1;
	}
	return 0;
}

stock IsPlayerEmergencyServices(playerid)
{
	if(PlayerData[playerid][player_job] == POLICE_JOB) return 1;
	else if(PlayerData[playerid][player_job] == CIA_JOB) return 1;
	else if(PlayerData[playerid][player_job] == ARMY_JOB) return 1;
	else if(PlayerData[playerid][player_job] == EMS_JOB) return 1;
	else if(PlayerData[playerid][player_job] == FIRE_JOB) return 1;
	return 0;
}

stock GetClanTag(playerid)
{
	new string[8];
	format(string, sizeof(string), "%s", PlayerData[playerid][player_clantag]);
	return string;
}

stock SetClanTag(playerid, tag[])
{
	new string[8];
	format(string, sizeof(string), "%s", tag);
	PlayerData[playerid][player_clantag] = string;
	return 1;
}

stock GetClanInvite(playerid)
{
	new string[8];
	format(string, sizeof(string), "%s", PlayerData[playerid][player_claninvite]);
	return string;
}

stock SetClanInvite(playerid, invite[])
{
	new string[8];
	format(string, sizeof(string), "%s", invite);
	PlayerData[playerid][player_claninvite] = string;
	return 1;
}

stock SpawnAtHospital(playerid)
{
	new city = ReturnPlayerCity(playerid);
	SetPlayerHospital(playerid, city);

	SetPlayerHealth(playerid, 100.0);
	if(GetPlayerVIP(playerid))
	{
		SetPlayerArmour(playerid, 100.0);
	}
	else 
	{
		ResetPlayerWeapons(playerid);
		SetPlayerArmour(playerid, 0.0);
	}

	if(city == LOS_SANTOS)
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 2025.2469, -1403.4918, 17.2098);
		SetPlayerFacingAngle(playerid, 180.7238);
		SetCameraBehindPlayer(playerid);

		SetSpawnInfo(playerid, 1, GetPlayerSkinEx(playerid), 2025.2469, -1403.4918, 17.2098, 180.7238, 0, 0, 0, 0, 0, 0);
	}
	else if(city == SAN_FIERRO)
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, -2655.1104, 638.3422, 14.4531);
		SetPlayerFacingAngle(playerid, 180.1129);
		SetCameraBehindPlayer(playerid);

		SetSpawnInfo(playerid, 1, GetPlayerSkinEx(playerid), -2655.1104, 638.3422, 14.4531, 180.1129, 0, 0, 0, 0, 0, 0);
	}
	else
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 1607.4288, 1817.2189, 10.8203);
		SetPlayerFacingAngle(playerid, 359.7627);
		SetCameraBehindPlayer(playerid);

		SetSpawnInfo(playerid, 1, GetPlayerSkinEx(playerid), 1607.4288, 1817.2189, 10.8203, 359.7627, 0, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock ShowPasswordDialog(playerid)
{
	return ShowPlayerDialog(playerid, CHANGEPASS_DIALOG, DIALOG_STYLE_PASSWORD, "{FFFFFF}Change Password", "{FFFFFF}Please enter a {008000}new password {FFFFFF}below:", "Change", "Cancel");
}

stock ResetPlayerMoneyEx(playerid)
{
    PlayerData[playerid][player_money] = 0;
	return ResetPlayerMoney(playerid);
}

#if defined _ALS_ResetPlayerMoney
    #undef ResetPlayerMoney
#else
    #define _ALS_ResetPlayerMoney
#endif

#define ResetPlayerMoney ResetPlayerMoneyEx

stock GivePlayerMoneyEx(playerid, amount)
{
    PlayerData[playerid][player_money] += amount;
	return GivePlayerMoney(playerid, amount);
}

#if defined _ALS_GivePlayerMoney
    #undef GivePlayerMoney
#else
    #define _ALS_GivePlayerMoney
#endif

#define GivePlayerMoney GivePlayerMoneyEx

stock GetPlayerMoneyEx(playerid) return PlayerData[playerid][player_money];

stock RemoveCharacterFromDatabase(id)
{
	new query[128];

	//Characters
	format(query, sizeof(query), "DELETE FROM `CHARACTERS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Clans
	format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Weapons
	format(query, sizeof(query), "DELETE FROM `WEAPONS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Inventory
	format(query, sizeof(query), "DELETE FROM `INVENTORY` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Stats
	format(query, sizeof(query), "DELETE FROM `STATS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Degrees
	format(query, sizeof(query), "DELETE FROM `DEGREES` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Licences
	format(query, sizeof(query), "DELETE FROM `LICENCES` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Lotto
	format(query, sizeof(query), "DELETE FROM `LOTTO` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Materials
	format(query, sizeof(query), "DELETE FROM `MINERALS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Vehicles
	format(query, sizeof(query), "DELETE FROM `VEHICLES` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Mods
	format(query, sizeof(query), "DELETE FROM `MODS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	//Plants
	for(new i = 0; i < 10; i++)
	{
		format(query, sizeof(query), "DELETE FROM `PLANT%i` WHERE `CHARACTER_ID` = '%i'", (i + 1), id);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}

	//Houses
	RemoveHouseOwnerFromDatabase(id);

	//Businesses
	RemoveBusinessOwnerFromDatabase(id);
	return 1;
}

stock ReturnRegisterDate(playerid)
{
	new date[16];
	format(date, sizeof(date), "%s", PlayerData[playerid][player_date]);
	return date;
}

stock ReturnJoinName(playerid)
{
	new name[24];
	format(name, sizeof(name), "%s", PlayerData[playerid][player_name]);
	return name;
}

stock ReturnLoginCount(playerid) return PlayerData[playerid][player_logins];

stock ReturnPlayerStatus(playerid)
{
	new status[16];
	if(GetPlayerScore(playerid) >= 50 && GetPlayerScore(playerid) <= 99) { status = "Active"; }
	else if(GetPlayerScore(playerid) >= 100 && GetPlayerScore(playerid) <= 249) { status = "Regular"; }
	else if(GetPlayerScore(playerid) >= 250 && GetPlayerScore(playerid) <= 499) { status = "Veteran"; }
	else if(GetPlayerScore(playerid) >= 500 && GetPlayerScore(playerid) <= 999) { status = "Legend"; }
	else if(GetPlayerScore(playerid) >= 1000 && GetPlayerScore(playerid) <= 4999) { status = "Icon"; }
	else if(GetPlayerScore(playerid) >= 5000) { status = "Godlike"; }
	else { status = "Newbie"; }
	return status;
}

stock ReturnMasterID(playerid)
{
	new query[128], name[24];
	GetPlayerName(playerid, name, sizeof(name));

	format(query, sizeof(query), "SELECT `MASTER_ID` FROM `ACCOUNTS` WHERE `JOIN_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		new id = db_get_field_assoc_int(database_result, "MASTER_ID");
		db_free_result@(database_result);
		return id;
	}
	db_free_result@(database_result);
	return 0;
}

stock ReturnCharacterID(name[])
{
	new query[128];
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		new id = db_get_field_assoc_int(database_result, "CHARACTER_ID");
		db_free_result@(database_result);
		return id;
	}
	db_free_result@(database_result);
	return 0;
}

stock ReturnCharacterName(characterid)
{
	new query[128], name[24];
	format(name, sizeof(name), "Unknown");
	format(query, sizeof(query), "SELECT `CHARACTER_NAME` FROM `CHARACTERS` WHERE `CHARACTER_ID` = '%i'", characterid);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_get_field_assoc@(database_result, "CHARACTER_NAME", name, sizeof(name));
	}
	db_free_result@(database_result);
	return name;
}

stock GetCharacterCount(playerid)
{
	new query[128], count = 0;
	format(query, sizeof(query), "SELECT `MASTER_ID` FROM `CHARACTERS` WHERE `MASTER_ID` = '%i'", PlayerData[playerid][player_master]);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		count = db_num_rows(database_result);
	}
	db_free_result@(database_result);
	return count;
}

stock SavePlayerAccount(playerid)
{
	if(IsPlayerSpawned(playerid) && PlayerData[playerid][player_logged] == true)
	{
		new query[800], name[24], Float:pos[4], Float:health, Float:armour, interior, world, mute = 0;
		GetPlayerName(playerid, name, sizeof(name));

		interior = GetPlayerInterior(playerid);
		world = GetPlayerVirtualWorld(playerid);

	 	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	 	GetPlayerFacingAngle(playerid, pos[3]);

		if(GetPlayerJailTime(playerid) > 0 || GetDutyStatus(playerid) == true || GetCameraStatus(playerid) == true || IsPlayerSafe(playerid) == true)
		{
			health = StoredData[playerid][stored_health];
			armour = StoredData[playerid][stored_armour];
		}
		else
		{
	    	GetPlayerHealth(playerid, health);
	    	GetPlayerArmour(playerid, armour);
		}

		if(GetPlayerMuted(playerid) == true) { mute = 1; }

	  	format(query, sizeof(query),
		"UPDATE `CHARACTERS` SET SKIN = '%i', SCORE = '%i', MONEY = '%i', JOB = '%i', WANTED = '%i', TIME = '%i', DEPT = '%i', STYLE = '%i', HUNGER = '%i', THIRST = '%i', HEALTH = '%f', ARMOUR = '%f', X = '%f', Y = '%f', Z = '%f', A = '%f', INT = '%i', WORLD = '%i', MUTE = '%i', ROB = '%i' WHERE `CHARACTER_ID` = '%i'",
		GetPlayerSkin(playerid), GetPlayerScore(playerid), GetPlayerMoneyEx(playerid), PlayerData[playerid][player_job], GetPlayerWantedLevel(playerid), PlayerData[playerid][player_time], PlayerData[playerid][player_dept], GetPlayerFightingStyle(playerid), PlayerData[playerid][player_hunger], 
		PlayerData[playerid][player_thirst], health, armour, pos[0], pos[1], pos[2], pos[3], interior, world, mute, PlayerData[playerid][player_lastrob], PlayerData[playerid][player_character]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		SaveWeaponData(playerid);
		SaveInventoryData(playerid);
		SaveStatsData(playerid);
		SaveBankData(playerid);
		SaveLottoData(playerid);
		SaveMineralsData(playerid);
	}
	return 1;
}

stock ShowAccountDialog(playerid, bool:register)
{
	new string1[64], string2[128], name[24];
	GetPlayerName(playerid, name, sizeof(name));

	if(register)
	{
		format(string1, sizeof(string1), "{FFFFFF}Welcome, {008000}%s{FFFFFF}!", name);
		format(string2, sizeof(string2), "{FFFFFF}Please enter a {FF0000}strong password {FFFFFF}below to register an account:", name);
		ShowPlayerDialog(playerid, REGISTER_DIALOG, DIALOG_STYLE_PASSWORD, string1, string2, "Register", "Quit");
	}
	else
	{
		format(string1, sizeof(string1), "{FFFFFF}Welcome back, {008000}%s{FFFFFF}!", name);
		format(string2, sizeof(string2), "{FFFFFF}Please enter {008000}your password {FFFFFF}below to login to your account:", name);
		ShowPlayerDialog(playerid, LOGIN_DIALOG, DIALOG_STYLE_PASSWORD, string1, string2, "Login", "Quit");
	}
	return 1;
}

stock ShowCharacterDialog(playerid)
{
	return ShowPlayerDialog(playerid, CHAR_MAIN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Character Selection", "{FFFFFF}Create Character\nLoad Character\nDelete Character", "Select", "Quit");
}

stock ShowCreateDialog(playerid)
{
	return ShowPlayerDialog(playerid, CHAR_CREATE_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Character Selection > Create", "{FFFFFF}Please make up a name for your character in a {FF0000}FirstName_LastName {FFFFFF}format:", "Create", "Back");
}

stock ReturnPlayerJob(playerid)
{
	new type[16];

	//Degree Jobs
	if(PlayerData[playerid][player_job] == POLICE_JOB) { type = "Officer"; }
	else if(PlayerData[playerid][player_job] == CIA_JOB) { type = "Agent"; }
	else if(PlayerData[playerid][player_job] == ARMY_JOB) { type = "Soldier"; }
	else if(PlayerData[playerid][player_job] == EMS_JOB) { type = "Paramedic"; }
	else if(PlayerData[playerid][player_job] == FIRE_JOB) { type = "Firefighter"; }
	else if(PlayerData[playerid][player_job] == MINER_JOB) { type = "Miner"; }
	
	//Licence Jobs
	else if(PlayerData[playerid][player_job] == PILOT_JOB) { type = "Pilot"; }
	else if(PlayerData[playerid][player_job] == TRUCKER_JOB) { type = "Trucker"; }
	else { type = "Unemployed"; }
	return type;
}

stock ReturnJobName(job)
{
	new type[16];

	//Degree Jobs
	if(job == POLICE_JOB) { type = "Officer"; }
	else if(job == CIA_JOB) { type = "Agent"; }
	else if(job == ARMY_JOB) { type = "Soldier"; }
	else if(job == EMS_JOB) { type = "Paramedic"; }
	else if(job == FIRE_JOB) { type = "Firefighter"; }
	else if(job == MINER_JOB) { type = "Miner"; }
	
	//Licence Jobs
	else if(job == PILOT_JOB) { type = "Pilot"; }
	else if(job == TRUCKER_JOB) { type = "Trucker"; }
	else { type = "Unemployed"; }
	return type;
}

stock RunNameCheckForPlayer(name[])
{
	new query[300];
	format(query, sizeof(query), "SELECT `JOIN_NAME` FROM `ACCOUNTS` WHERE `JOIN_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);
		return 1;
	}
	db_free_result@(database_result);

	format(query, sizeof(query), "SELECT `CHARACTER_NAME` FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);
		return 1;
	}
	db_free_result@(database_result);
	return 0;
}

stock CheckForBan(playerid, id)
{
	new query[200], reason[32], string[200], admin[24], timestamp;
	format(query, sizeof(query), "SELECT * FROM `BANS` WHERE `MASTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_get_field_assoc@(database_result, "REASON", reason, sizeof(reason));
		db_get_field_assoc@(database_result, "ADMIN", admin, sizeof(admin));
		timestamp = db_get_field_assoc_int(database_result, "TIMESTAMP");

		db_free_result@(database_result);

		if(timestamp == 0)
		{
			format(string, sizeof(string), "AUTO: You are PERM-BANNED. (Banned By: %s - Reason: %s - Days Left: NEVER)", admin, reason);
			SendClientMessage(playerid, RED, string);
			return KickPlayer(playerid);
		}
		else
		{
			if(gettime() < timestamp)
			{
				format(string, sizeof(string), "AUTO: You are TEMP-BANNED. (Banned By: %s - Reason: %s - Days Left: %i)", admin, reason, ((timestamp - gettime()) / 86400));
				SendClientMessage(playerid, RED, string);
				return KickPlayer(playerid);
			}
			else if(gettime() >= timestamp)
			{
				format(query, sizeof(query), "DELETE FROM `BANS` WHERE `MASTER_ID` = '%i'", id);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				SendClientMessage(playerid, YELLOW, "AUTO: Your temp-ban has expired. Be sure to follow the /rules this time.");

				PlayerData[playerid][player_registered] = true;
				ShowAccountDialog(playerid, false);//Login
			}
		}
		return 1;
	}
	else
	{
		db_free_result@(database_result);

		PlayerData[playerid][player_registered] = true;
		ShowAccountDialog(playerid, false);//Login
  	}
	return 1;
}

hook OnGameModeInit()
{
	AddPlayerClass(0, FIRST_SPAWN_X, FIRST_SPAWN_Y, FIRST_SPAWN_Z, FIRST_SPAWN_A, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnPlayerSpawn(playerid)//Forced to be called last
{
	if(!IsPlayerNPC(playerid))
	{
		if(PlayerData[playerid][player_spawned] == false)
		{
			PlayerData[playerid][player_spawned] = true;

			SetPlayerFightingStyle(playerid, PlayerData[playerid][player_style]);
		
			SetPlayerSkin(playerid, PlayerData[playerid][player_skin]);
			SetPlayerScore(playerid, PlayerData[playerid][player_score]);

			SetPlayerHealth(playerid, PlayerData[playerid][player_health]);
			SetPlayerArmour(playerid, PlayerData[playerid][player_armour]);

			if(GetPlayerJailTime(playerid) > 0)
			{
				SetPlayerRejail(playerid, true);
				return SendPlayerToJail(playerid, GetPlayerDept(playerid), GetPlayerJailTime(playerid));
			}

			if(PlayerData[playerid][player_job] == CIVILIAN_JOB)
			{
				SetPlayerWantedLevelEx(playerid, PlayerData[playerid][player_wanted]);
			}
			else
			{
				SetPlayerColourEx(playerid, PlayerData[playerid][player_job]);
			}

			SetPlayerInterior(playerid, PlayerData[playerid][player_int]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][player_world]);
			SetPlayerPos(playerid, PlayerData[playerid][player_x], PlayerData[playerid][player_y], PlayerData[playerid][player_z]);
			SetPlayerFacingAngle(playerid, PlayerData[playerid][player_a]);
			SetCameraBehindPlayer(playerid);

			if(IsPlayerNew(playerid))
			{
				SetPlayerHealth(playerid, MAX_HEALTH);

				ShowCivilianSkinMenu(playerid);

				SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to continue, you can change it again at Binco.");
			}
			else
			{
				GivePlayerWeapons(playerid);
			}
			return SetTimerEx("CheckForInjuries", 1000, false, "i", playerid);
		}
		else  
		{
			if(GetCameraStatus(playerid) == true)
			{
				SetCameraStatus(playerid, false);

				SetPlayerSkin(playerid, GetStoredSkin(playerid));
				SetPlayerWantedLevel(playerid, GetStoredWantedLevel(playerid));

				SetPlayerHealth(playerid, GetStoredHealth(playerid));
				SetPlayerArmour(playerid, GetStoredArmour(playerid));

				RestoreStoredWeapons(playerid);
				return RestorePlayerPosition(playerid);
			}

			if(GetPlayerJailTime(playerid) > 0)
			{
				SetPlayerRejail(playerid, true);
				return SendPlayerToJail(playerid, GetPlayerDept(playerid), GetPlayerJailTime(playerid));
			}

			if(PlayerData[playerid][player_death] == true)
			{
				RestoreStoredWeapons(playerid);
				RestorePlayerPosition(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][player_skin]);

				OnPlayerWounded(playerid, PlayerData[playerid][player_killerid], 255);

				PlayerData[playerid][player_death] = false;
				PlayerData[playerid][player_killerid] = INVALID_PLAYER_ID;
			}
			ResetStoredData(playerid);
		}
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)//Forced to be called last
{
	StoreWeaponData(playerid);
	ResetPlayerWeapons(playerid);
	StorePlayerPosition(playerid);
	PlayerData[playerid][player_skin] = GetPlayerSkin(playerid);

	PlayerData[playerid][player_death] = true;
	PlayerData[playerid][player_killerid] = killerid;
	return 1;
}

hook OnPlayerConnect(playerid)
{
    if(!IsPlayerNPC(playerid))
    {
		PlayerData[playerid][player_master] = 0;
		PlayerData[playerid][player_level] = PLAYER;
		PlayerData[playerid][player_vip] = false;
		PlayerData[playerid][player_job] = CIVILIAN_JOB;
		PlayerData[playerid][player_wanted] = 0;
		PlayerData[playerid][player_time] = 0;
		PlayerData[playerid][player_dept] = NO_CITY;
		PlayerData[playerid][player_style] = FIGHT_STYLE_NORMAL;
		PlayerData[playerid][player_hospital] = NO_CITY;
		PlayerData[playerid][player_hunger] = (random(20) + 80);
		PlayerData[playerid][player_thirst] = (random(20) + 80);
		PlayerData[playerid][player_score] = 0;
		PlayerData[playerid][player_money] = 0;
		PlayerData[playerid][player_skin] = 0;
		PlayerData[playerid][player_logins] = 0;
		PlayerData[playerid][player_paramedic] = INVALID_PLAYER_ID;
		PlayerData[playerid][player_healed] = 0;
		PlayerData[playerid][player_charid] = 0;
		PlayerData[playerid][player_x] = FIRST_SPAWN_X;
		PlayerData[playerid][player_y] = FIRST_SPAWN_Y;
		PlayerData[playerid][player_z] = FIRST_SPAWN_Z;
		PlayerData[playerid][player_a] = FIRST_SPAWN_A;
		PlayerData[playerid][player_int] = FIRST_SPAWN_INT;
		PlayerData[playerid][player_world] = FIRST_SPAWN_WORLD;
		PlayerData[playerid][player_health] = 100.0;
		PlayerData[playerid][player_armour] = 0.0;
		PlayerData[playerid][player_warns] = 0;
		PlayerData[playerid][player_lastrob] = 0;
		PlayerData[playerid][player_tradeveh] = INVALID_VEHICLE_ID;
		PlayerData[playerid][player_killerid] = INVALID_PLAYER_ID;

		PlayerData[playerid][player_logged] = false;
		PlayerData[playerid][player_spawned] = false;
		PlayerData[playerid][player_registered] = false;
		PlayerData[playerid][player_rejail] = false;
		PlayerData[playerid][player_new] = false;
		PlayerData[playerid][player_safe] = false;
		PlayerData[playerid][player_duty] = false;
		PlayerData[playerid][player_spectated] = false;
		PlayerData[playerid][player_muted] = false;
		PlayerData[playerid][player_death] = false;

		ResetStoredData(playerid);

		new query[128], name[24], id;
		GetPlayerName(playerid, name, sizeof(name));

		SetPlayerColourEx(playerid, CIVILIAN_JOB);

	    format(query, sizeof(query), "SELECT `MASTER_ID` FROM `ACCOUNTS` WHERE `JOIN_NAME` = '%q' COLLATE NOCASE", name);
 		database_result = db_query@(server_database, query);
  		if(db_num_rows(database_result))
  		{
			id = db_get_field_assoc_int(database_result, "MASTER_ID");
  			db_free_result@(database_result);
			CheckForBan(playerid, id);
  		}
  		else
  		{
  			db_free_result@(database_result);
  			ShowAccountDialog(playerid, true);//Register
  		}

		RemoveBuildingForPlayer(playerid, 955, 0.0, 0.0, 0.0, 6000.0);//Sprunk Vending Machine #1
		RemoveBuildingForPlayer(playerid, 956, 0.0, 0.0, 0.0, 6000.0);//Normal Vending Machine #1
		RemoveBuildingForPlayer(playerid, 1209, 0.0, 0.0, 0.0, 6000.0);//Soda Vending Machine #1
		RemoveBuildingForPlayer(playerid, 1302, 0.0, 0.0, 0.0, 6000.0);//Soda Vending Machine #2
		RemoveBuildingForPlayer(playerid, 1775, 0.0, 0.0, 0.0, 6000.0);//Sprunk Vending Machine #2
		RemoveBuildingForPlayer(playerid, 1776, 0.0, 0.0, 0.0, 6000.0);//Normal Vending Machine #2
   	}
    return 1;
}

public OnPlayerDisconnect(playerid, reason)//Forced to be called last
{
    if(!IsPlayerNPC(playerid))
    {
    	SetPlayerName(playerid, ReturnJoinName(playerid));
    	
		SavePlayerAccount(playerid);
    	SavePlantData(playerid);
		SaveVehicleData(playerid);
   	}
   	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case CHANGEPASS_DIALOG:
		{
			if(response)
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 24)
				{
					SendClientMessage(playerid, RED, "ERROR: Your password must be from 3-24 characters long. Please try again.");
					return ShowPasswordDialog(playerid);
				}
				else
				{
				    bcrypt_hash(playerid, "OnPasswordChange", inputtext, 12);
				}
			}
			return 1;
		}
		case REGISTER_DIALOG:
		{
		    if(response)
		    {
	      		if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 24)
				{
					SendClientMessage(playerid, RED, "ERROR: Your password must be from 3-24 characters long. Please try again.");
					return ShowAccountDialog(playerid, true);
				}
				else
				{
				    bcrypt_hash(playerid, "OnPlayerRegister", inputtext, 12);
				}
				return 1;
			}
			else
			{
				Kick(playerid);
			}
			return 1;
		}
		case LOGIN_DIALOG:
		{
		    if(response)
		    {
		    	new pass[63], query[300], name[24];
		    	GetPlayerName(playerid, name, sizeof(name));

		    	format(query, sizeof(query), "SELECT `PASS` FROM `ACCOUNTS` WHERE `JOIN_NAME` = '%q' COLLATE NOCASE", name);
				database_result = db_query@(server_database, query);
		     	if(db_num_rows(database_result))
				{
					db_get_field_assoc@(database_result, "PASS", pass, sizeof(pass));
			    	bcrypt_verify(playerid, "OnPlayerLogin", inputtext, pass);
				}
				db_free_result@(database_result);
		    	return 1;
		    }
			else
			{
				Kick(playerid);
			}
			return 1;
		}
		case CHAR_CREATE_DIALOG:
		{
			if(response)
			{
				new query[800], string[200], name[24];
				GetPlayerName(playerid, name, sizeof(name));
				if(strlen(inputtext) < 5 || strlen(inputtext) > 24)
				{
					SendClientMessage(playerid, RED, "ERROR: Your name must be from 5-24 characters long.");
					return ShowCreateDialog(playerid);
				}

				if(strfind(inputtext, "_", true) == -1)
				{
					SendClientMessage(playerid, RED, "ERROR: Your name must contain an underscore '_' separating your first name from your last name.");
					return ShowCreateDialog(playerid);
				}

				if(!strcmp(inputtext, name, true))
				{
					SendClientMessage(playerid, RED, "ERROR: Your character name cannot be the same as your login name.");
					return ShowCreateDialog(playerid);
				}

				if(RunNameCheckForPlayer(inputtext) == 1)
				{
					SendClientMessage(playerid, RED, "ERROR: That name is already taken, please choose another one.");
					return ShowCreateDialog(playerid);
				}

				if(!GetPlayerVIP(playerid))
				{
					if(GetCharacterCount(playerid) >= 2)
					{
						SendClientMessage(playerid, RED, "ERROR: You can only have a maximum of x2 characters at a time, delete one first.");
						return ShowCharacterDialog(playerid);
					}
				}
				else
				{
					if(GetCharacterCount(playerid) >= 4)
					{
						SendClientMessage(playerid, RED, "ERROR: You can only have a maximum of x4 characters at a time, delete one first.");
						return ShowCharacterDialog(playerid);
					}
				}

				PlayerData[playerid][player_name] = name;

				SetPlayerName(playerid, inputtext);

				PlayerData[playerid][player_money] = 0;
				GivePlayerMoney(playerid, PLAYER_STARTING_MONEY);

				format(query, sizeof(query), "INSERT INTO `CHARACTERS` (`MASTER_ID`, `CHARACTER_NAME`, `SKIN`, `SCORE`, `MONEY`, `JOB`, `WANTED`, `TIME`, `DEPT`, `STYLE`, `HUNGER`, `THIRST`, `HEALTH`, `ARMOUR`, `X`, `Y`, `Z`, `A`, `INT`, `WORLD`, `MUTE`, `ROB`) VALUES ('%i', '%q', '0', '0', '%i', '%i', '0', '0', '%i', '%i', '100', '100', '100.0', '0.0', '%f', '%f', '%f', '%f', '%i', '%i', '0', '0')",
				PlayerData[playerid][player_master], inputtext, PLAYER_STARTING_MONEY, CIVILIAN_JOB, NO_CITY, FIGHT_STYLE_NORMAL, FIRST_SPAWN_X, FIRST_SPAWN_Y, FIRST_SPAWN_Z, FIRST_SPAWN_A, FIRST_SPAWN_INT, FIRST_SPAWN_WORLD);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				new dbid = ReturnCharacterID(inputtext);
				if(dbid == 0) return printf("[%s] Error: Function 'ReturnCharacterID' failed under 'Character Creation' for player: %s", SERVER_TAG, name);
				PlayerData[playerid][player_character] = dbid;

				PlayerData[playerid][player_logged] = true;
				PlayerData[playerid][player_registered] = true;
				PlayerData[playerid][player_new] = true;

				format(string, sizeof(string), "ACCOUNT: %s (aka %s) has just created an account.", inputtext, name);
				SendClientMessageToAll(GREY, string);

				SetSpawnInfo(playerid, 1, PlayerData[playerid][player_skin], FIRST_SPAWN_X, FIRST_SPAWN_Y, FIRST_SPAWN_Z, FIRST_SPAWN_A, 0, 0, 0, 0, 0, 0);
				return SpawnPlayer(playerid);
			}
			else
			{
				ShowCharacterDialog(playerid);
			}
			return 1;
		}
		case CHAR_MAIN_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Create Character
					{
						return ShowCreateDialog(playerid);
					}
					case 1://Load Character
					{
						new query[600], string[600], name[24], id = 0, score = 0, total = 0;
						format(query, sizeof(query), "SELECT `CHARACTER_ID`, `CHARACTER_NAME`, `SCORE` FROM `CHARACTERS` WHERE `MASTER_ID` = '%i'", PlayerData[playerid][player_master]);
					    database_result = db_query@(server_database, query);
					    if((total = db_num_rows(database_result)))
					    {
					        query[0] = EOS;
					        do
					        {
						        db_get_field_assoc@(database_result, "CHARACTER_NAME", name, sizeof(name));

						        id = db_get_field_assoc_int(database_result, "CHARACTER_ID");
						        score = db_get_field_assoc_int(database_result, "SCORE");

					            format(string, sizeof(string), "{FFFFFF}%i\t{FFFFFF}%s\t{FFFFFF}%i\n", id, name, score);
								strcat(query, string);
					        }
					        while(db_next_row(database_result));
					    }
					    db_free_result@(database_result);

					    if(total == 0)
					    {
					    	SendClientMessage(playerid, RED, "ERROR: You don't have any characters to load, create one first.");
							return ShowCharacterDialog(playerid);
					    }

						format(string, sizeof(string), "ID\tName\tScore\n%s", query);
					    return ShowPlayerDialog(playerid, CHAR_LOAD_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Character Selection > Load", string, "Load", "Back");
					}
					case 2://Delete Character
					{
						new query[600], string[600], name[24], id = 0, score = 0, total = 0;
						format(query, sizeof(query), "SELECT `CHARACTER_ID`, `CHARACTER_NAME`, `JOB` FROM `CHARACTERS` WHERE `MASTER_ID` = '%i'", PlayerData[playerid][player_master]);
					    database_result = db_query@(server_database, query);
					    if((total = db_num_rows(database_result)))
					    {
					        query[0] = EOS;
					        do
					        {
						        db_get_field_assoc@(database_result, "CHARACTER_NAME", name, sizeof(name));

						        id = db_get_field_assoc_int(database_result, "CHARACTER_ID");
						        score = db_get_field_assoc_int(database_result, "SCORE");

					            format(string, sizeof(string), "{FFFFFF}%i\t{FFFFFF}%s\t{FFFFFF}%i\n", id, name, score);
								strcat(query, string);
					        }
					        while(db_next_row(database_result));
					    }
					    db_free_result@(database_result);

					    if(total == 0)
					    {
					    	SendClientMessage(playerid, RED, "ERROR: You don't have any characters to delete, create one first.");
							return ShowCharacterDialog(playerid);
					    }

						format(string, sizeof(string), "ID\tName\tScore\n%s", query);
					    return ShowPlayerDialog(playerid, CHAR_DELETE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Character Selection > Delete", string, "Delete", "Back");
					}
				}
			}
			else
			{
				Kick(playerid);
			}
			return 1;
		}
		case CHAR_LOAD_DIALOG:
		{
			if(response)
			{
				new query[300], string[200], name[24], oldname[24], id = strval(inputtext);
				format(query, sizeof(query), "SELECT * FROM `CHARACTERS` WHERE `CHARACTER_ID` = '%i'", id);
				database_result = db_query@(server_database, query);
				if(db_num_rows(database_result))
				{
					db_get_field_assoc@(database_result, "CHARACTER_NAME", name, sizeof(name));

					PlayerData[playerid][player_character] = db_get_field_assoc_int(database_result, "CHARACTER_ID");
					PlayerData[playerid][player_skin] = db_get_field_assoc_int(database_result, "SKIN");
					PlayerData[playerid][player_score] = db_get_field_assoc_int(database_result, "SCORE");
					PlayerData[playerid][player_job] = db_get_field_assoc_int(database_result, "JOB");
					PlayerData[playerid][player_wanted] = db_get_field_assoc_int(database_result, "WANTED");
					PlayerData[playerid][player_time] = db_get_field_assoc_int(database_result, "TIME");
					PlayerData[playerid][player_dept] = db_get_field_assoc_int(database_result, "DEPT");
					PlayerData[playerid][player_style] = db_get_field_assoc_int(database_result, "STYLE");

					PlayerData[playerid][player_hunger] = db_get_field_assoc_int(database_result, "HUNGER");
					PlayerData[playerid][player_thirst] = db_get_field_assoc_int(database_result, "THIRST");

					PlayerData[playerid][player_health] = db_get_field_assoc_float(database_result, "HEALTH");
					PlayerData[playerid][player_armour] = db_get_field_assoc_float(database_result, "ARMOUR");

					PlayerData[playerid][player_x] = db_get_field_assoc_float(database_result, "X");
					PlayerData[playerid][player_y] = db_get_field_assoc_float(database_result, "Y");
					PlayerData[playerid][player_z] = db_get_field_assoc_float(database_result, "Z");
					PlayerData[playerid][player_a] = db_get_field_assoc_float(database_result, "A");

					PlayerData[playerid][player_int] = db_get_field_assoc_int(database_result, "INT");
					PlayerData[playerid][player_world] = db_get_field_assoc_int(database_result, "WORLD");

					PlayerData[playerid][player_lastrob] = db_get_field_assoc_int(database_result, "ROB");

					new mute = db_get_field_assoc_int(database_result, "MUTE");
					if(mute == 1)
					{
						SetPlayerMuted(playerid, true);
					}

					new get_money = db_get_field_assoc_int(database_result, "MONEY");

					db_free_result@(database_result);

					PlayerData[playerid][player_money] = 0;
					GivePlayerMoney(playerid, get_money);

					GetPlayerName(playerid, oldname, sizeof(oldname));
					PlayerData[playerid][player_name] = oldname;

					SetPlayerName(playerid, name);

					LoadWeaponData(playerid);
					LoadInventoryData(playerid);
					LoadStatsData(playerid);
					LoadBankData(playerid);
					LoadLottoData(playerid);
					LoadMineralsData(playerid);
					LoadDegreeData(playerid);
					LoadLicenceData(playerid);
					
					LoadPlantData(playerid);
					LoadVehicleData(playerid);

					for(new i = 0; i < (MAX_VIP_VEHICLES - 1); i++)//dodgy fix? I know.. possible y_hooks bug? (do while statements do not loop in hooked callbacks)
					{
						SaveVehicleData(playerid);//forcing "do while" to repeat (don't ask me why it doesn't)
						LoadVehicleData(playerid);//forcing "do while" to repeat (don't ask me why it doesn't)
					}

					LoadPlayerClan(playerid);

					PlayerData[playerid][player_logged] = true;
					PlayerData[playerid][player_registered] = true;
					PlayerData[playerid][player_new] = false;

					format(string, sizeof(string), "ACCOUNT: %s (aka %s) has just logged into their account.", name, oldname);
					SendClientMessageToAll(GREY, string);

					SetSpawnInfo(playerid, 1, PlayerData[playerid][player_skin], PlayerData[playerid][player_x], PlayerData[playerid][player_y], PlayerData[playerid][player_z], PlayerData[playerid][player_a], 0, 0, 0, 0, 0, 0);

					SpawnPlayer(playerid);
				}
				db_free_result@(database_result);
				return 1;
			}
			else
			{
				ShowCharacterDialog(playerid);
			}
			return 1;
		}
		case CHAR_DELETE_DIALOG:
		{
			if(response)
			{
				new query[300], string[200], name[24], id = strval(inputtext), score = 0;
				PlayerData[playerid][player_charid] = id;

				format(query, sizeof(query), "SELECT `CHARACTER_NAME`, `SCORE` FROM `CHARACTERS` WHERE `CHARACTER_ID` = '%i'", id);
				database_result = db_query@(server_database, query);
				if(db_num_rows(database_result))
				{

					db_get_field_assoc@(database_result, "CHARACTER_NAME", name, sizeof(name));
					score = db_get_field_assoc_int(database_result, "SCORE");

					format(string, sizeof(string), "{FFFFFF}Are you sure you want to delete {FF0000}'%s' {FFFFFF}with {FF0000}%i {FFFFFF}score?", name, score);
					ShowPlayerDialog(playerid, CHAR_VERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Character Selection > Delete", string, "Yes", "No");
				}
				db_free_result@(database_result);
				return 1;
			}
			else
			{
				ShowCharacterDialog(playerid);
			}
			return 1;
		}
		case CHAR_VERIFY_DIALOG:
		{
			if(response)
			{
				new query[300], id = PlayerData[playerid][player_charid];
				format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `CHARACTERS` WHERE `CHARACTER_ID` = '%i'", id);
				database_result = db_query@(server_database, query);
				if(db_num_rows(database_result))
				{
					db_free_result@(database_result);

					RemoveCharacterFromDatabase(id);

					SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully deleted the character.");
					ShowCharacterDialog(playerid);
				}
				db_free_result@(database_result);
				return 1;
			}
			else
			{
				ShowCharacterDialog(playerid);
			}
		}
	}
	return 1;
}

hook OnPasswordChange(playerid)
{
	new password[64], query[300];
	bcrypt_get_hash(password);

	format(query, sizeof(query), "UPDATE `ACCOUNTS` SET PASS = '%s' WHERE `MASTER_ID` = '%i'", password, PlayerData[playerid][player_master]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully changed your password.");
}

hook OnPlayerRegister(playerid)
{
	new password[64], name[24], ip[16], query[300], year, month, day, date[16];
	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerIp(playerid, ip, sizeof(ip));

	bcrypt_get_hash(password);

	getdate(year, month, day);
	format(date, sizeof(date), "%02d/%02d/%d", day, month, year);

	PlayerData[playerid][player_date] = date;

	format(query, sizeof(query), "INSERT INTO `ACCOUNTS` (`JOIN_NAME`, `PASS`, `IP`, `REGISTERED`, `LOGINS`, `LEVEL`, `VIP`) VALUES ('%q', '%s', '%s', '%s', '1', '0', '0')", name, password, ip, date);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	new dbid = ReturnMasterID(playerid);
	if(dbid == 0) return printf("[%s] Error: Function 'ReturnMasterID' failed under callback 'OnPlayerRegister' for player: %s", SERVER_TAG, name);
	PlayerData[playerid][player_master] = dbid;

	return ShowCharacterDialog(playerid);
}

hook OnPlayerLogin(playerid, bool:success)
{
 	if(success)
	{
		new query[300], ip[16], name[24], vip;
		GetPlayerName(playerid, name, sizeof(name));
		GetPlayerIp(playerid, ip, sizeof(ip));

	    format(query, sizeof(query), "SELECT * FROM `ACCOUNTS` WHERE `JOIN_NAME` = '%q' COLLATE NOCASE", name);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_get_field_assoc@(database_result, "REGISTERED", PlayerData[playerid][player_date], 16);

			PlayerData[playerid][player_master] = db_get_field_assoc_int(database_result, "MASTER_ID");
			PlayerData[playerid][player_level] = db_get_field_assoc_int(database_result, "LEVEL");

			vip = db_get_field_assoc_int(database_result, "VIP");
			if(vip == 1) { PlayerData[playerid][player_vip] = true; }
			else { PlayerData[playerid][player_vip] = false; }

			PlayerData[playerid][player_logins] = db_get_field_assoc_int(database_result, "LOGINS");

			db_free_result@(database_result);

			PlayerData[playerid][player_logins]++;

			format(query, sizeof(query), "UPDATE `ACCOUNTS` SET IP = '%s', LOGINS = '%i' WHERE `MASTER_ID` = '%i'", ip, PlayerData[playerid][player_logins], PlayerData[playerid][player_master]);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
			
			return ShowCharacterDialog(playerid);
		}
		db_free_result@(database_result);
		return 1;
	}
	else
 	{
 		PlayerData[playerid][player_fails]++;
		if(PlayerData[playerid][player_fails] < MAX_FAILS)
		{
			new string[128];
			format(string, sizeof(string), "ERROR: Incorrect password. (%i/%i Warnings)", PlayerData[playerid][player_fails], MAX_FAILS);
			SendClientMessage(playerid, RED, string);
			return ShowAccountDialog(playerid, false);
		}
		else
		{
			new string[128], name[24];
			GetPlayerName(playerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Incorrect Password x%i", name, playerid, MAX_FAILS);
			SendClientMessageToAll(RED, string);

			KickPlayer(playerid);
		}
 	}
	return 1;
}

public CheckForInjuries(playerid)//Do not hook
{
	new Float:health;
	GetPlayerHealth(playerid, health);
	if(health == 2.0)
	{
		OnPlayerWounded(playerid, INVALID_PLAYER_ID, 255);
	}
	else if(health == 1.0)
	{
		TriggerPlayerDeath(playerid, INVALID_PLAYER_ID, 255);
	}
	return 1;
}

ptask OnAccountSave[300000](playerid)
{
	return SavePlayerAccount(playerid);
}
