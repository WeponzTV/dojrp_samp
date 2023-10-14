#include <YSI_Coding\y_hooks>

forward OnPlayerDoJailTime(playerid);

enum cell_data
{
	lspd_cell1_cp,

	sfpd_cell1_cp,
	sfpd_cell2_cp,
	sfpd_cell3_cp,
	sfpd_cell4_cp,

	lvpd_cell1_cp,
	lvpd_cell2_cp,
	lvpd_cell3_cp,
	lvpd_cell4_cp,
	lvpd_cell5_cp,
	lvpd_cell6_cp,
};
new CellData[cell_data];

enum prisoner_data
{
	prisoner_cell,
	prisoner_timer
};
new PrisonerData[MAX_PLAYERS][prisoner_data];

stock GetPlayerCell(department, playerid)
{
	if(department == LOS_SANTOS)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 266.7466, 76.4339, 1001.0391)) return 1;//LSPD Cell #1
	}
	else if(department == SAN_FIERRO)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 228.5883, 113.1787, 999.0156)) return 1;//SFPD Cell #1
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 224.7150, 113.1782, 999.0156)) return 2;//SFPD Cell #2
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 220.7773, 113.1787, 999.0156)) return 3;//SFPD Cell #3
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 216.8334, 113.1872, 999.0156)) return 4;//SFPD Cell #4
	}
	else if(department == LAS_VENTURAS)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 197.0638, 177.4871, 1003.0234)) return 1;//LVPD Cell #1
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 192.7801, 177.4865, 1003.1533)) return 2;//LVPD Cell #2
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 188.5325, 177.4865, 1003.1533)) return 3;//LVPD Cell #3
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 196.9326, 159.8857, 1003.1533)) return 4;//LVPD Cell #4
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 192.6790, 159.8863, 1003.1533)) return 5;//LVPD Cell #5
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, 188.4444, 159.8862, 1003.1533)) return 6;//LVPD Cell #6
	}
	return NO_CITY;
}

stock ShowCellDialog(playerid, department, cell)
{
	new query[800], string[128], info[64], name[24], total = 0;
	foreach(new i : Player)
	{
		new get_dept = GetPlayerDept(i), get_time = GetPlayerJailTime(i);
		if(get_dept == department && get_time > 0)
		{
			if(cell == PrisonerData[i][prisoner_cell])
			{
				GetPlayerName(i, name, sizeof(name));
				format(string, sizeof(string), "{FFFFFF}Prisoner: %s (%i) - Time: %i Secs\n", name, i, get_time);
				strcat(query, string);
				total++;
			}
		}
	}
	if(total == 0) return SendClientMessage(playerid, ORANGE, "SERVER: There are currently no prisoners in this cell.");

	format(info, sizeof(info), "{FFFFFF}%s Cell #%i", ReturnDepartmentName(department), cell);
	ShowPlayerDialog(playerid, CELL_DIALOG, DIALOG_STYLE_LIST, info, string, "Close", "");
	return 1;
}

stock SendPlayerToJail(playerid, department, seconds)
{
	SetPlayerJailTime(playerid, seconds);
	SetPlayerDept(playerid, department);

	if(IsRejail(playerid))
	{
		SetRejail(playerid, false);
	}
	else
	{
		SetPlayerStats(playerid, STATS_TYPE_JAILED, GetPlayerStats(playerid, STATS_TYPE_JAILED) + 1);
	}

	new Float:health, Float:armour;
	GetPlayerHealth(playerid, health);
	GetPlayerArmour(playerid, armour);

	SetStoredHealth(playerid, health);
	SetStoredArmour(playerid, armour);

	SetPlayerHealth(playerid, MAX_HEALTH);
	SetPlayerArmour(playerid, 0.0);

	SetPlayerWantedLevel(playerid, 0);
	SetPlayerColor(playerid, GREY);

	ResetPlayerWeapons(playerid);

	PrisonerData[playerid][prisoner_timer] = SetTimerEx("OnPlayerDoJailTime", 1000, true, "i", playerid);

	new string[200];
	if(department == LOS_SANTOS)
	{
		PrisonerData[playerid][prisoner_cell] = 1;

		SetPlayerInterior(playerid, 6);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 264.2708, 77.5481, 1001.0391);
		SetPlayerFacingAngle(playerid, 269.2578);
		SetCameraBehindPlayer(playerid);

    	format(string, sizeof(string), "SERVER: Welcome to LSPD Cell #1, you have been incarcerated for %i seconds.", seconds);
    	SendClientMessage(playerid, ORANGE, string);

    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
	}
	else if(department == SAN_FIERRO)
	{
		new cell = random(4);
	
		SetPlayerInterior(playerid, 10);
		SetPlayerVirtualWorld(playerid, 0);

		if(cell == 0)
		{
			PrisonerData[playerid][prisoner_cell] = 1;

			SetPlayerPos(playerid, 227.4670, 111.2068, 999.0156);
			SetPlayerFacingAngle(playerid, 0.7828);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to SFPD Cell #1, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 1)
		{
			PrisonerData[playerid][prisoner_cell] = 2;
			
			SetPlayerPos(playerid, 223.5224, 111.2230, 999.0156);
			SetPlayerFacingAngle(playerid, 359.8194);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to SFPD Cell #2, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 2)
		{
			PrisonerData[playerid][prisoner_cell] = 3;
			
			SetPlayerPos(playerid, 219.4849, 111.0348, 999.0156);
			SetPlayerFacingAngle(playerid, 358.5428);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to SFPD Cell #3, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else
		{
			PrisonerData[playerid][prisoner_cell] = 4;
			
			SetPlayerPos(playerid, 215.5570, 111.1174, 999.0156);
			SetPlayerFacingAngle(playerid, 1.0260);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to SFPD Cell #4, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		return 1;
	}
	else
	{
		new cell = random(6);

		SetPlayerInterior(playerid, 3);
    	SetPlayerVirtualWorld(playerid, 0);

		Streamer_UpdateEx(playerid, 198.0651, 176.7253, 1003.0234, -1, -1);//load cell objects

		if(cell == 0)
		{
			PrisonerData[playerid][prisoner_cell] = 1;
			
    		SetPlayerPos(playerid, 198.0651, 176.7253, 1003.0234);
    		SetPlayerFacingAngle(playerid, 359.4248);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #1, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 1)
		{
			PrisonerData[playerid][prisoner_cell] = 2;
			
    		SetPlayerPos(playerid, 193.8369, 176.7251, 1003.0234);
    		SetPlayerFacingAngle(playerid, 0.6781);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #2, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 2)
		{
			PrisonerData[playerid][prisoner_cell] = 3;
			
    		SetPlayerPos(playerid, 189.5884, 176.7243, 1003.1533);
    		SetPlayerFacingAngle(playerid, 357.5681);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #3, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 3)
		{
			PrisonerData[playerid][prisoner_cell] = 4;
			
    		SetPlayerPos(playerid, 198.0573, 160.6476, 1003.1533);
    		SetPlayerFacingAngle(playerid, 178.6532);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #4, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else if(cell == 4)
		{
			PrisonerData[playerid][prisoner_cell] = 5;
			
    		SetPlayerPos(playerid, 193.8127, 160.6480, 1003.1533);
    		SetPlayerFacingAngle(playerid, 178.0266);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #5, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	return SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
		else
		{
			PrisonerData[playerid][prisoner_cell] = 6;
			
    		SetPlayerPos(playerid, 189.5607, 160.6474, 1003.1533);
    		SetPlayerFacingAngle(playerid, 180.1966);
			SetCameraBehindPlayer(playerid);

	    	format(string, sizeof(string), "SERVER: Welcome to LVPD Cell #6, you have been incarcerated for %i seconds.", seconds);
	    	SendClientMessage(playerid, ORANGE, string);

	    	SendClientMessage(playerid, WHITE, "NOTE: You can try /esc or get someone to /break or /bail you out.");
		}
	}
	return 1;
}

hook OnGameModeInit()
{
	CellData[lspd_cell1_cp] = CreateDynamicCP(266.7466, 76.4339, 1001.0391, 1.0, -1, -1, -1, 3.0, -1, 0);//LSPD Cell #1

	CellData[sfpd_cell1_cp] = CreateDynamicCP(228.5883, 113.1787, 999.0156, 1.0, -1, -1, -1, 3.0, -1, 0);//SFPD Cell #1
	CellData[sfpd_cell2_cp] = CreateDynamicCP(224.7150, 113.1782, 999.0156, 1.0, -1, -1, -1, 3.0, -1, 0);//SFPD Cell #2
	CellData[sfpd_cell3_cp] = CreateDynamicCP(220.7773, 113.1787, 999.0156, 1.0, -1, -1, -1, 3.0, -1, 0);//SFPD Cell #3
	CellData[sfpd_cell4_cp] = CreateDynamicCP(216.8334, 113.1872, 999.0156, 1.0, -1, -1, -1, 3.0, -1, 0);//SFPD Cell #4

	CellData[lvpd_cell1_cp] = CreateDynamicCP(197.0638, 177.4871, 1003.0234, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #1
	CellData[lvpd_cell2_cp] = CreateDynamicCP(192.7801, 177.4865, 1003.1533, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #2
	CellData[lvpd_cell3_cp] = CreateDynamicCP(188.5325, 177.4865, 1003.1533, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #3
	CellData[lvpd_cell4_cp] = CreateDynamicCP(196.9326, 159.8857, 1003.1533, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #4
	CellData[lvpd_cell5_cp] = CreateDynamicCP(192.6790, 159.8863, 1003.1533, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #5
	CellData[lvpd_cell6_cp] = CreateDynamicCP(188.4444, 159.8862, 1003.1533, 1.0, -1, -1, -1, 3.0, -1, 0);//LVPD Cell #6
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		PrisonerData[playerid][prisoner_cell] = 0;
		PrisonerData[playerid][prisoner_timer] = -1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new time = GetPlayerJailTime(playerid);
		if(checkpointid == CellData[lspd_cell1_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LOS_SANTOS, 1);
		}
		else if(checkpointid == CellData[sfpd_cell1_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, SAN_FIERRO, 1);
		}
		else if(checkpointid == CellData[sfpd_cell2_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, SAN_FIERRO, 2);
		}
		else if(checkpointid == CellData[sfpd_cell3_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, SAN_FIERRO, 3);
		}
		else if(checkpointid == CellData[sfpd_cell4_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, SAN_FIERRO, 4);
		}
		else if(checkpointid == CellData[lvpd_cell1_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 1);
		}
		else if(checkpointid == CellData[lvpd_cell2_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 2);
		}
		else if(checkpointid == CellData[lvpd_cell3_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 3);
		}
		else if(checkpointid == CellData[lvpd_cell4_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 4);
		}
		else if(checkpointid == CellData[lvpd_cell5_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 5);
		}
		else if(checkpointid == CellData[lvpd_cell6_cp])
		{
			if(time > 0) return 1;
			return ShowCellDialog(playerid, LAS_VENTURAS, 6);
		}
	}
	return 1;
}

public OnPlayerDoJailTime(playerid)//Do not hook
{
	new string[128];
	if(IsPlayerConnected(playerid))
	{
		if(GetPlayerJailTime(playerid) > 0)
		{
		    SetPlayerJailTime(playerid, GetPlayerJailTime(playerid) - 1);

		    new time = GetPlayerJailTime(playerid);
		    format(string, sizeof(string), "~w~Time: %i Secs", time);
		    return GameTextForPlayer(playerid, string, 1500, 5);
		}
		else
		{
		 	KillTimer(PrisonerData[playerid][prisoner_timer]);

		 	PrisonerData[playerid][prisoner_timer] = -1;

			new dept = GetPlayerDept(playerid);
			if(dept == LOS_SANTOS)
			{
				SetPlayerInterior(playerid, 6);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 268.4887, 76.7792, 1001.0391);
				SetPlayerFacingAngle(playerid, 358.2731);
				SetCameraBehindPlayer(playerid);
			}
			else if(dept == SAN_FIERRO)
			{
				SetPlayerInterior(playerid, 10);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 214.8856, 114.6345, 999.0156);
				SetPlayerFacingAngle(playerid, 271.6863);
				SetCameraBehindPlayer(playerid);
			}
			else
			{
				SetPlayerInterior(playerid, 3);
				SetPlayerVirtualWorld(playerid, 0);
	    		SetPlayerPos(playerid, 203.4530, 168.1289, 1003.0234);
	    		SetPlayerFacingAngle(playerid, 84.7917);
				SetCameraBehindPlayer(playerid);
			}

			SetPlayerHealth(playerid, GetStoredHealth(playerid));
			SetPlayerArmour(playerid, GetStoredArmour(playerid));

			SetPlayerColourEx(playerid, CIVILIAN_JOB);

		 	SetPlayerJailTime(playerid, 0);
		 	SetPlayerDept(playerid, NO_CITY);
		 	
		 	PrisonerData[playerid][prisoner_cell] = 0;

			new high = (MAX_BAIL_FEE - (MAX_BAIL_FEE / 2)), low = (MAX_BAIL_FEE / 2), fees = (random(high) + low);
			GivePlayerMoney(playerid, -fees);

			format(string, sizeof(string), "NOTICE: You have paid $%i in bail fees.", fees);
			SendClientMessage(playerid, ORANGE, string);
		}
		return 1;
	}
	else
	{
		KillTimer(PrisonerData[playerid][prisoner_timer]);
	}
	return 1;
}

CMD:break(playerid, params[])
{
	new string[144], name[24], targetid, department = NO_CITY;
	if(GetPlayerJob(playerid) != CIVILIAN_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to civilians only.");
	if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in jail.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /break [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");
	if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(playerid == targetid) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command on yourself.");
	if(GetPlayerJailTime(targetid) <= 0) return SendClientMessage(playerid, RED, "ERROR: That player is not in jail.");

	if(GetPlayerInterior(playerid) == 6 && GetPlayerVirtualWorld(playerid) == 0) { department = LOS_SANTOS; }
	else if(GetPlayerInterior(playerid) == 10 && GetPlayerVirtualWorld(playerid) == 0) { department = SAN_FIERRO; }
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 0) { department = LAS_VENTURAS; }
	else return SendClientMessage(playerid, RED, "ERROR: You must be inside a police department to use this command.");

	if(GetPlayerCell(department, playerid) == NO_CITY) return SendClientMessage(playerid, RED, "ERROR: You must be standing at a cell to use this command.");
	if(GetPlayerCell(department, playerid) != PrisonerData[targetid][prisoner_cell]) return SendClientMessage(playerid, RED, "ERROR: That player is not in this cell.");

	if((gettime() - 10) < GetTimerStatus(playerid, TIMER_TYPE_BREAKOUT)) return SendClientMessage(playerid, RED, "ERROR: Please wait 10 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_BREAKOUT, gettime());

	GetPlayerName(playerid, name, sizeof(name));

	new fail = random(4);
	if(fail == 0)
	{
		KillTimer(PrisonerData[targetid][prisoner_timer]);

	 	PrisonerData[targetid][prisoner_timer] = -1;

		new city = GetPlayerDept(targetid);
		if(city == LOS_SANTOS)
		{
			SetPlayerPos(targetid, 268.3202, 79.6065, 1001.0391);
			SetPlayerFacingAngle(targetid, 359.7126);
			SetCameraBehindPlayer(targetid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just broken someone out of from jail at: LSPD", name, playerid);
		}
		else if(city == SAN_FIERRO)
		{
			SetPlayerPos(targetid, 215.2703, 115.2483, 999.0156);
			SetPlayerFacingAngle(targetid, 269.4115);
			SetCameraBehindPlayer(targetid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just broken someone out of from jail at: SFPD", name, playerid);
		}
		else
		{
    		SetPlayerPos(targetid, 200.6972, 168.2653, 1003.0234);
    		SetPlayerFacingAngle(targetid, 89.0391);
			SetCameraBehindPlayer(targetid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just broken someone out of from jail at: LVPD", name, playerid);
		}

		PoliceRadio(ORANGE, string);

		SetPlayerHealth(targetid, 100.0);

		SetPlayerWantedLevelEx(targetid, 6);

		GivePlayerWeapon(targetid, 24, 500);

	 	SetPlayerJailTime(targetid, 0);
	 	SetPlayerDept(targetid, NO_CITY);
	 	
	 	PrisonerData[targetid][prisoner_cell] = 0;
	 	
	 	SetPlayerWantedLevel(playerid, 6);
	 	SetPlayerColor(playerid, RED);

	 	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully broken the prisoner out and handed them a gun!");
	}
	else
	{
		SetPlayerWantedLevelEx(playerid, 6);

		if(department == LOS_SANTOS) { format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just tried to break someone out of jail at: LSPD", name, playerid); }
		else if(department == SAN_FIERRO) { format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just tried to break someone out of jail at: SFPD", name, playerid); }
		else if(department == LAS_VENTURAS) { format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just tried to break someone out of jail at: LVPD", name, playerid); }

		PoliceRadio(ORANGE, string);

		SendClientMessage(playerid, ORANGE, "NOTICE: You failed to break the prisoner out, please wait 10 seconds before trying again.");
	}
	return 1;
}

CMD:bail(playerid, params[])
{
	new string[128], name[24], targetid, department = NO_CITY;
	if(GetPlayerJob(playerid) != POLICE_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to police officers only.");
	if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in jail.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /bail [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");
	if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(playerid == targetid) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command on yourself.");
	if(GetPlayerJailTime(targetid) <= 0) return SendClientMessage(playerid, RED, "ERROR: That player is not in jail.");

	if(GetPlayerInterior(playerid) == 6 && GetPlayerVirtualWorld(playerid) == 0) { department = LOS_SANTOS; }
	else if(GetPlayerInterior(playerid) == 10 && GetPlayerVirtualWorld(playerid) == 0) { department = SAN_FIERRO; }
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 0) { department = LAS_VENTURAS; }
	else return SendClientMessage(playerid, RED, "ERROR: You must be inside a police department to use this command.");

	if(GetPlayerCell(department, playerid) == NO_CITY) return SendClientMessage(playerid, RED, "ERROR: You must be standing at a cell to use this command.");
	if(GetPlayerCell(department, playerid) != PrisonerData[targetid][prisoner_cell]) return SendClientMessage(playerid, RED, "ERROR: That player is not in this cell.");

	KillTimer(PrisonerData[targetid][prisoner_timer]);

	PrisonerData[targetid][prisoner_timer] = -1;

	new city = GetPlayerDept(targetid);
	if(city == LOS_SANTOS)
	{
		SetPlayerPos(targetid, 268.3202, 79.6065, 1001.0391);
		SetPlayerFacingAngle(targetid, 359.7126);
		SetCameraBehindPlayer(targetid);
	}
	else if(city == SAN_FIERRO)
	{
		SetPlayerPos(targetid, 215.2703, 115.2483, 999.0156);
		SetPlayerFacingAngle(targetid, 269.4115);
		SetCameraBehindPlayer(targetid);
	}
	else
	{
		SetPlayerPos(targetid, 200.6972, 168.2653, 1003.0234);
    	SetPlayerFacingAngle(targetid, 89.0391);
		SetCameraBehindPlayer(targetid);
	}

	SetPlayerHealth(targetid, 100.0);

	SetPlayerJailTime(targetid, 0);
	SetPlayerDept(targetid, NO_CITY);

	SetPlayerColourEx(targetid, CIVILIAN_JOB);
	 	
	PrisonerData[targetid][prisoner_cell] = 0;

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: Officer %s (%i) has just bailed you out of jail.", name, playerid);
	SendClientMessage(targetid, YELLOW, string);

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have bailed Prisoner %s (%i) out of jail.", name, targetid);
	SendClientMessage(playerid, YELLOW, string);
	return 1;
}

CMD:escape(playerid, params[])
{
	if(GetPlayerJailTime(playerid) <= 0) return SendClientMessage(playerid, RED, "ERROR: You must be in jail to use this command.");

	if((gettime() - 10) < GetTimerStatus(playerid, TIMER_TYPE_ESCAPE)) return SendClientMessage(playerid, RED, "ERROR: Please wait 10 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_ESCAPE, gettime());

	new string[144], name[24], fail = random(7);
	if(fail == 0)
	{
		KillTimer(PrisonerData[playerid][prisoner_timer]);

	 	PrisonerData[playerid][prisoner_timer] = -1;

		GetPlayerName(playerid, name, sizeof(name));

		new city = GetPlayerDept(playerid);
		if(city == LOS_SANTOS)
		{
			SetPlayerPos(playerid, 268.3202, 79.6065, 1001.0391);
			SetPlayerFacingAngle(playerid, 359.7126);
			SetCameraBehindPlayer(playerid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just escaped from jail at: LSPD", name, playerid);
		}
		else if(city == SAN_FIERRO)
		{
			SetPlayerPos(playerid, 215.2703, 115.2483, 999.0156);
			SetPlayerFacingAngle(playerid, 269.4115);
			SetCameraBehindPlayer(playerid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just escaped from jail at: SFPD", name, playerid);
		}
		else
		{
    		SetPlayerPos(playerid, 200.6972, 168.2653, 1003.0234);
    		SetPlayerFacingAngle(playerid, 89.0391);
			SetCameraBehindPlayer(playerid);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has just escaped from jail at: LVPD", name, playerid);
		}

		PoliceRadio(ORANGE, string);

		SetPlayerHealth(playerid, 100.0);

		SetPlayerWantedLevelEx(playerid, 6);

		GivePlayerWeapon(playerid, 24, 500);

		SetPlayerJailTime(playerid, 0);
		SetPlayerDept(playerid, NO_CITY);
		 	
		PrisonerData[playerid][prisoner_cell] = 0;

	 	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully escaped the cell and found a gun!");
	}
	else
	{
		SendClientMessage(playerid, ORANGE, "NOTICE: You failed to escape the cell, please wait 10 seconds before trying again.");
	}
	return 1;
}
