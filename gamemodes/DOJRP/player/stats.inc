#include <YSI_Coding\y_hooks>

enum stats_data
{
	stats_kills,
	stats_deaths,
	stats_arrests,
	stats_tickets,
	stats_takedowns,
	stats_jailed,
	stats_robberies,
	stats_safes,
	stats_patients,
	stats_fires,
	stats_flights,
	stats_hauls,
	stats_fines
};
new StatsData[MAX_PLAYERS][stats_data];

stock GetPlayerStats(playerid, type)
{
	if(type == STATS_TYPE_KILLS) return StatsData[playerid][stats_kills];
	else if(type == STATS_TYPE_DEATHS) return StatsData[playerid][stats_deaths];
	else if(type == STATS_TYPE_ARRESTS) return StatsData[playerid][stats_arrests];
	else if(type == STATS_TYPE_TICKETS) return StatsData[playerid][stats_tickets];
	else if(type == STATS_TYPE_TAKEDOWNS) return StatsData[playerid][stats_takedowns];
	else if(type == STATS_TYPE_JAILED) return StatsData[playerid][stats_jailed];
	else if(type == STATS_TYPE_ROBBERIES) return StatsData[playerid][stats_robberies];
	else if(type == STATS_TYPE_SAFES) return StatsData[playerid][stats_safes];
	else if(type == STATS_TYPE_PATIENTS) return StatsData[playerid][stats_patients];
	else if(type == STATS_TYPE_FIRES) return StatsData[playerid][stats_fires];
	else if(type == STATS_TYPE_FLIGHTS) return StatsData[playerid][stats_flights];
	else if(type == STATS_TYPE_HAULS) return StatsData[playerid][stats_hauls];
	else if(type == STATS_TYPE_FINES) return StatsData[playerid][stats_fines];
	return 1;
}

stock SetPlayerStats(playerid, type, amount)
{
	if(type == STATS_TYPE_KILLS) return StatsData[playerid][stats_kills] = amount;
	else if(type == STATS_TYPE_DEATHS) return StatsData[playerid][stats_deaths] = amount;
	else if(type == STATS_TYPE_ARRESTS) return StatsData[playerid][stats_arrests] = amount;
	else if(type == STATS_TYPE_TICKETS) return StatsData[playerid][stats_tickets] = amount;
	else if(type == STATS_TYPE_TAKEDOWNS) return StatsData[playerid][stats_takedowns] = amount;
	else if(type == STATS_TYPE_JAILED) return StatsData[playerid][stats_jailed] = amount;
	else if(type == STATS_TYPE_ROBBERIES) return StatsData[playerid][stats_robberies] = amount;
	else if(type == STATS_TYPE_SAFES) return StatsData[playerid][stats_safes] = amount;
	else if(type == STATS_TYPE_PATIENTS) return StatsData[playerid][stats_patients] = amount;
	else if(type == STATS_TYPE_FIRES) return StatsData[playerid][stats_fires] = amount;
	else if(type == STATS_TYPE_FLIGHTS) return StatsData[playerid][stats_flights] = amount;
	else if(type == STATS_TYPE_HAULS) return StatsData[playerid][stats_hauls] = amount;
	else if(type == STATS_TYPE_FINES) return StatsData[playerid][stats_fines] = amount;
	return 1;
}

stock LoadStatsData(playerid)
{
	new query[200];
	format(query, sizeof(query), "SELECT * FROM `STATS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		StatsData[playerid][stats_kills] = db_get_field_assoc_int(database_result, "KILLS");
		StatsData[playerid][stats_deaths] = db_get_field_assoc_int(database_result, "DEATHS");
		StatsData[playerid][stats_arrests] = db_get_field_assoc_int(database_result, "ARRESTS");
		StatsData[playerid][stats_tickets] = db_get_field_assoc_int(database_result, "TICKETS");
		StatsData[playerid][stats_takedowns] = db_get_field_assoc_int(database_result, "TAKEDOWNS");
		StatsData[playerid][stats_jailed] = db_get_field_assoc_int(database_result, "JAILED");
		StatsData[playerid][stats_robberies] = db_get_field_assoc_int(database_result, "ROBBERIES");
		StatsData[playerid][stats_safes] = db_get_field_assoc_int(database_result, "SAFES");
		StatsData[playerid][stats_patients] = db_get_field_assoc_int(database_result, "PATIENTS");
		StatsData[playerid][stats_fires] = db_get_field_assoc_int(database_result, "FIRES");
		StatsData[playerid][stats_flights] = db_get_field_assoc_int(database_result, "FLIGHTS");
		StatsData[playerid][stats_hauls] = db_get_field_assoc_int(database_result, "HAULS");
		StatsData[playerid][stats_fines] = db_get_field_assoc_int(database_result, "FINES");
	}
	db_free_result@(database_result);
	return 1;
}

stock SaveStatsData(playerid)
{
	new query[600], characterid = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `STATS` WHERE `CHARACTER_ID` = '%i'", characterid);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `STATS` SET `KILLS` = '%i', `DEATHS` = '%i', `ARRESTS` = '%i', `TICKETS` = '%i', `TAKEDOWNS` = '%i', `JAILED` = '%i', `ROBBERIES` = '%i', `SAFES` = '%i', `PATIENTS` = '%i', `FIRES` = '%i', `FLIGHTS` = '%i', `HAULS` = '%i', `FINES` = '%i' WHERE `CHARACTER_ID` = '%i'", 
		StatsData[playerid][stats_kills], StatsData[playerid][stats_deaths], StatsData[playerid][stats_arrests], StatsData[playerid][stats_tickets], StatsData[playerid][stats_takedowns], StatsData[playerid][stats_jailed], StatsData[playerid][stats_robberies], StatsData[playerid][stats_safes], StatsData[playerid][stats_patients], StatsData[playerid][stats_fires], StatsData[playerid][stats_flights], StatsData[playerid][stats_hauls], StatsData[playerid][stats_fines], characterid);
		database_result = db_query@(server_database, query);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `STATS` (`CHARACTER_ID`, `KILLS`, `DEATHS`, `ARRESTS`, `TICKETS`, `TAKEDOWNS`, `JAILED`, `ROBBERIES`, `SAFES`, `PATIENTS`, `FIRES`, `FLIGHTS`, `HAULS`, `FINES`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		characterid, StatsData[playerid][stats_kills], StatsData[playerid][stats_deaths], StatsData[playerid][stats_arrests], StatsData[playerid][stats_tickets], StatsData[playerid][stats_takedowns], StatsData[playerid][stats_jailed], StatsData[playerid][stats_robberies], StatsData[playerid][stats_safes], StatsData[playerid][stats_patients], StatsData[playerid][stats_fires], StatsData[playerid][stats_flights], StatsData[playerid][stats_hauls], StatsData[playerid][stats_fines]);
		database_result = db_query@(server_database, query);
	}
	db_free_result@(database_result);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		StatsData[playerid][stats_kills] = 0;
		StatsData[playerid][stats_deaths] = 0;
		StatsData[playerid][stats_arrests] = 0;
		StatsData[playerid][stats_tickets] = 0;
		StatsData[playerid][stats_takedowns] = 0;
		StatsData[playerid][stats_jailed] = 0;
		StatsData[playerid][stats_robberies] = 0;
		StatsData[playerid][stats_safes] = 0;
		StatsData[playerid][stats_patients] = 0;
		StatsData[playerid][stats_fires] = 0;
		StatsData[playerid][stats_flights] = 0;
		StatsData[playerid][stats_hauls] = 0;
		StatsData[playerid][stats_fines] = 0;
	}
	return 1;
}

CMD:stats(playerid, params[])
{
	new targetid, name[24], string1[64], string2[400];
	if(sscanf(params, "u", targetid))
	{
		GetPlayerName(playerid, name, sizeof(name));
		format(string1, sizeof(string1), "{FFFFFF}%s (Aka: %s)", name, ReturnJoinName(playerid));
		format(string2, sizeof(string2), 
		"{FFFFFF}Level: %s\nStatus: %s\nJob: %s\nClan: %s\nScore: %i\nKills: %i\nDeaths: %i\nArrests: %i\nTakedowns: %i\nJailed: %i\nRobberies: %i\nSafes: %i\nPatients: %i\nFires: %i\nFlights: %i\nHauls: %i\nFines: %i\nLogins: %i\nJoined: %s", 
		ReturnPlayerLevel(playerid), ReturnPlayerStatus(playerid), ReturnPlayerJob(playerid), GetPlayerClanName(playerid), GetPlayerScore(playerid), StatsData[playerid][stats_kills], StatsData[playerid][stats_deaths], StatsData[playerid][stats_arrests], StatsData[playerid][stats_takedowns], StatsData[playerid][stats_jailed], 
		StatsData[playerid][stats_robberies], StatsData[playerid][stats_safes], StatsData[playerid][stats_patients], StatsData[playerid][stats_fires], StatsData[playerid][stats_flights], StatsData[playerid][stats_hauls], StatsData[playerid][stats_fines], ReturnLoginCount(playerid), ReturnRegisterDate(playerid));
		return ShowPlayerDialog(playerid, STATS_DIALOG, DIALOG_STYLE_LIST, string1, string2, "Close", "");
	}
	else
	{
		if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
		if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
		if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");

		GetPlayerName(targetid, name, sizeof(name));
		format(string1, sizeof(string1), "{FFFFFF}%s (Aka: %s)", name, ReturnJoinName(targetid));
		format(string2, sizeof(string2), 
		"{FFFFFF}Level: %s\nStatus: %s\nJob: %s\nClan: %s\nScore: %i\nKills: %i\nDeaths: %i\nArrests: %i\nTakedowns: %i\nJailed: %i\nRobberies: %i\nSafes: %i\nPatients: %i\nFires: %i\nFlights: %i\nHauls: %i\nFines: %i\nLogins: %i\nJoined: %s", 
		ReturnPlayerLevel(targetid), ReturnPlayerStatus(targetid), ReturnPlayerJob(targetid), GetPlayerClanName(targetid), GetPlayerScore(targetid), StatsData[targetid][stats_kills], StatsData[targetid][stats_deaths], StatsData[targetid][stats_arrests], StatsData[targetid][stats_takedowns], StatsData[targetid][stats_jailed], 
		StatsData[targetid][stats_robberies], StatsData[targetid][stats_safes], StatsData[targetid][stats_patients], StatsData[targetid][stats_fires], StatsData[targetid][stats_flights], StatsData[targetid][stats_hauls], StatsData[targetid][stats_fines], ReturnLoginCount(targetid), ReturnRegisterDate(targetid));
		ShowPlayerDialog(playerid, STATS_DIALOG, DIALOG_STYLE_LIST, string1, string2, "Close", "");
	}
	return 1;
}
