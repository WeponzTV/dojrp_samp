#include <YSI_Coding\y_hooks>

new Iterator:Spikes<MAX_SPIKES>;
new Iterator:Blocks<MAX_BLOCKS>;

forward OnPlayerArrested(playerid);
forward OnPlayerFailTicket(playerid);
forward OnPlayerFlashed(playerid);

forward OnSpikeStripRemove(spikeid);
forward OnRoadBlockRemove(blockid);

enum camera_data
{
	speed_camera_ls,
	speed_camera_sf,
	speed_camera_lv
};
new CameraData[camera_data];

enum spike_data
{
	spike_id,
	spike_area,
	spike_timer,
	Float:spike_pos[4],
	bool:spike_active
};
new SpikeData[MAX_SPIKES][spike_data];

enum block_data
{
	block_id,
	block_timer,
	Float:block_pos[4],
	bool:block_active
};
new BlockData[MAX_BLOCKS][block_data];

enum gate_data
{
	gate_lspd,
	gate_sfpd1,
	gate_sfpd2,
	gate_lvpd1,
	gate_lvpd2
};
new GateData[gate_data];

enum dept_data
{
	//LSPD
	lspd_ent_cp,
	lspd_ext_cp,
	lspd_desk_cp,
	lspd_base_cp,
	lspd_cells_cp,
	lspd_roof_cp,
	lspd_garage_cp,
	lspd_desk_pickup,
	lspd_garage_pickup,

	//SFPD
	sfpd_ent_cp,
	sfpd_ext_cp,
	sfpd_desk_cp,
	sfpd_base_cp,
	sfpd_cells_cp,
	sfpd_roof_cp,
	sfpd_garage_cp,
	sfpd_desk_pickup,
	sfpd_garage_pickup,

	//LVPD
	lvpd_ent1_cp,
	lvpd_ent2_cp,
	lvpd_ext1_cp,
	lvpd_ext2_cp,
	lvpd_desk_cp,
	lvpd_base_cp,
	lvpd_cells_cp,
	lvpd_roof_cp,
	lvpd_garage_cp,
	lvpd_desk_pickup,
	lvpd_garage_pickup,

	//CIA Headquarters
	lscia_ent_cp,
	sfcia_ent_cp,
	lvcia_ent_cp,
	cia_exit_cp,
	cia_desk_cp,
	cia_desk_pickup,

	//Army Base
	army_desk_cp,
	army_desk_pickup,

	//Navy Base
	navy_desk_cp,
	navy_ladder1_cp,
	navy_ladder2_cp,
	navy_desk_pickup,

	//Docks Base
	docks_desk_cp,
	docks_desk_pickup
};
new DeptData[dept_data];

enum offender_data
{
	offender_fine,
	offender_ticketer,
	offender_timer,
	bool:offender_ticketed,
	bool:offender_arrested
};
new OffenderData[MAX_PLAYERS][offender_data];

enum officer_data
{
	pd_garage_location
};
new OfficerData[MAX_PLAYERS][officer_data];

new Text:speed_camera_flash;

stock IsPlayerArrested(playerid) return OffenderData[playerid][offender_arrested];
stock SetArrestStatus(playerid, bool:status) return OffenderData[playerid][offender_arrested] = status;

stock IsPlayerNearGate(gate)
{
	foreach(new i : Player)
	{
		new job = GetPlayerJob(i);
	    if(job == POLICE_JOB || job == CIA_JOB || job == ARMY_JOB)
		{
		 	if(gate == LSPD_GATE)
			{
				if(IsPlayerInRangeOfPoint(i, 10.0, 1588.9600000, -1637.9000000, 15.2000000)) return 1;
			}
			else if(gate == SFPD_GATE)
			{
				if(IsPlayerInRangeOfPoint(i, 10.0, -1631.4095, 688.3995, 8.1875)) return 1;
			}
			else if(gate == LVPD1_GATE)
			{
				if(IsPlayerInRangeOfPoint(i, 10.0, 2294.2000000, 2499.2800000, 5.4000000)) return 1;
			}
		 	else if(gate == LVPD2_GATE)
		 	{
				if(IsPlayerInRangeOfPoint(i, 10.0, 2334.6699000, 2443.5000000, 8.2000000)) return 1;
			}
		}
	}
	return 0;
}

stock ReturnDepartmentName(department)
{
	new name[8];
	if(department == LOS_SANTOS)
	{
		format(name, sizeof(name), "LSPD");
	}
	else if(department == SAN_FIERRO)
	{
		format(name, sizeof(name), "SFPD");
	}
	else
	{
		format(name, sizeof(name), "LVPD");
	}
	return name;
}

stock ReturnHeadquartersName(city)
{
	new name[32];
	if(city == LOS_SANTOS)
	{
		format(name, sizeof(name), "CIA Headquarters (LS)");
	}
	else if(city == SAN_FIERRO)
	{
		format(name, sizeof(name), "CIA Headquarters (SF)");
	}
	else
	{
		format(name, sizeof(name), "CIA Headquarters (LV)");
	}
	return name;
}

stock ShowPDMainDialog(playerid, department)
{
	new string[128], info[64], job = GetPlayerJob(playerid);
	format(info, sizeof(info), "{FFFFFF}%s Desk", ReturnDepartmentName(department));

	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_enforcement] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need an Enforcement Degree to clock-on as a police officer.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a police officer while you are wanted.");
		return ShowPlayerDialog(playerid, POLICE_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-on as a police officer?", "Yes", "No");
	}
	else if(job == POLICE_JOB)
	{
		return ShowPlayerDialog(playerid, POLICE_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-off as a police officer?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a police officer while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowCIADialog(playerid, city)
{
	new string[128], info[64], job = GetPlayerJob(playerid);
	format(info, sizeof(info), "{FFFFFF}%s", ReturnHeadquartersName(city));

	if(job == CIVILIAN_JOB)
	{
		if(GetPlayerDegree(playerid, DEGREE_INTELLIGENCE) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need an Intelligence Degree to clock-on as a CIA agent.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a CIA agent while you are wanted.");
		return ShowPlayerDialog(playerid, CIA_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-on as a CIA agent?", "Yes", "No");
	}
	else if(job == CIA_JOB)
	{
		return ShowPlayerDialog(playerid, CIA_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-off as a CIA agent?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a CIA agent while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowArmyMainDialog(playerid)
{
	new string[128], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_defense] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Defense Degree to clock-on as a soldier.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a soldier while you are wanted.");
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Army Desk", "{FFFFFF}Would you like to clock-on as a soldier?", "Yes", "No");
	}
	else if(job == ARMY_JOB)
	{
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Army Desk", "{FFFFFF}Would you like to clock-off as a soldier?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a soldier while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowNavyMainDialog(playerid)
{
	new string[128], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_defense] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Defense Degree to clock-on as a soldier.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a soldier while you are wanted.");
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Navy Desk", "{FFFFFF}Would you like to clock-on as a soldier?", "Yes", "No");
	}
	else if(job == ARMY_JOB)
	{
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Navy Desk", "{FFFFFF}Would you like to clock-off as a soldier?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a soldier while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowDocksMainDialog(playerid)
{
	new string[128], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_defense] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Defense Degree to clock-on as a soldier.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a soldier while you are wanted.");
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Docks Desk", "{FFFFFF}Would you like to clock-on as a soldier?", "Yes", "No");
	}
	else if(job == ARMY_JOB)
	{
		return ShowPlayerDialog(playerid, ARMY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Docks Desk", "{FFFFFF}Would you like to clock-off as a soldier?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a soldier while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowFireExitDialog(playerid, department)
{
	new job = GetPlayerJob(playerid);
	if(job == POLICE_JOB || job == CIA_JOB || job == ARMY_JOB)
	{
		if(department == LOS_SANTOS)
		{
			return ShowPlayerDialog(playerid, LSPD_FIRE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}LSPD Fire Exit", "{FFFFFF}Basement\nCells\nRooftop", "Select", "Cancel");
		}
		else if(department == SAN_FIERRO)
		{
			return ShowPlayerDialog(playerid, SFPD_FIRE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}SFPD Fire Exit", "{FFFFFF}Basement\nCells\nRooftop", "Select", "Cancel");
		}
		else if(department == LAS_VENTURAS)
		{
			return ShowPlayerDialog(playerid, LVPD_FIRE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}LVPD Fire Exit", "{FFFFFF}Basement\nCells\nRooftop", "Select", "Cancel");
		}
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: Only law enforcement can access this fire exit.");
	}
	return 1;
}

stock ShowPDGarageDialog(playerid, department)
{
	new info[64], job = GetPlayerJob(playerid);
	format(info, sizeof(info), "{FFFFFF}%s Garage", ReturnDepartmentName(department));

	if(job == POLICE_JOB || job == CIA_JOB || job == ARMY_JOB)
	{
		OfficerData[playerid][pd_garage_location] = department;
		ShowPlayerDialog(playerid, GARAGE_DIALOG, DIALOG_STYLE_LIST, info, "{FFFFFF}Repair Vehicle\nRefuel Vehicle", "Select", "Cancel");
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: Only law enforcement can access this garage.");
	}
	return 1;
}

stock PoliceRadio(colour, text[])
{
	new string[144];
	foreach(new i : Player)
	{
		new job = GetPlayerJob(i);
	 	if(job == POLICE_JOB || job == CIA_JOB || job == ARMY_JOB)
	 	{
	   		format(string, sizeof(string), "%s", text);
	    	SendClientMessage(i, colour, string);
		}
	}
	return 1;
}

stock GetFreeSpikeSlot()
{
	for(new i = 0; i < MAX_SPIKES; i++)
	{
		if(SpikeData[i][spike_active] == false) return i;
	}
	return -1;
}

stock GetFreeBlockSlot()
{
	for(new i = 0; i < MAX_BLOCKS; i++)
	{
		if(BlockData[i][block_active] == false) return i;
	}
	return -1;
}

stock CreateSpeedFlashTextdraw()
{
	speed_camera_flash = TextDrawCreate(-20.000000, 2.000000, "|");
	TextDrawUseBox(speed_camera_flash, 1);
	TextDrawBoxColor(speed_camera_flash, 0xffffff66);
	TextDrawTextSize(speed_camera_flash, 660.000000, 22.000000);
	TextDrawAlignment(speed_camera_flash, 0);
	TextDrawBackgroundColor(speed_camera_flash, 0x000000ff);
	TextDrawFont(speed_camera_flash, 3);
	TextDrawLetterSize(speed_camera_flash, 1.000000, 52.200000);
	TextDrawColor(speed_camera_flash, 0xffffffff);
	TextDrawSetOutline(speed_camera_flash, 1);
	TextDrawSetProportional(speed_camera_flash, 1);
	TextDrawSetShadow(speed_camera_flash, 1);
	return 1;
}

hook OnGameModeInit()
{
	CreateSpeedFlashTextdraw();

	CameraData[speed_camera_ls] = CreateDynamicRectangle(1422.205200, -1598.306396, 1436.699951, -1585.966918, 0, 0, -1, 0);//LS Speed Camera (Near LSPD)
	CameraData[speed_camera_sf] = CreateDynamicRectangle(-2013.359985, 102.131576, -2000.749633, 119.233474, 0, 0, -1, 0);//SF Speed Camera (Doherty Station)
	CameraData[speed_camera_lv] = CreateDynamicRectangle(2139.716552, 2124.344482, 2158.564453, 2156.702636, 0, 0, -1, 0);//LV Speed Camera (The Strip)

	CreateDynamicObject(18880, 1409.147827, -1598.165161, 13.546875 - 1.0, 0.0, 0.0, 90.0, -1, -1, -1, 250.0);//LS Speed Camera (Near LSPD)
	CreateDynamicObject(18880, -2012.843017, 98.499603, 27.687500 - 1.0, 0.0, 0.0, 180.0, -1, -1, -1, 250.0);//SF Speed Camera (Doherty Station)
	CreateDynamicObject(18880, 2158.520019, 2159.379882, 10.820312 - 1.0, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);//LV Speed Camera (The Strip)

	GateData[gate_lspd] = CreateDynamicObject(971,1588.9600000,-1637.9000000,15.2000000,0.0000000,0.0000000,180.0000000, -1, -1, -1, 250.0); //LSPD Gate
	CreateDynamicObject(2933,1579.9000000,-1638.1000000,14.1000000,0.0000000,0.0000000,0.0000000, -1, -1, -1, 250.0);//Barrier

	GateData[gate_sfpd1] = CreateDynamicObject(975,-1627.8000000,688.5000000,7.9000000,0.0000000,0.0000000,180.0000000, -1, -1, -1, 250.0); //SFPD Gate
	GateData[gate_sfpd2] = CreateDynamicObject(975,-1636.6000000,688.5000000,7.9000000,0.0000000,0.0000000,179.9950000, -1, -1, -1, 250.0); //SFPD Gate
	CreateDynamicObject(2933,-1617.9000000,688.2999900,7.9000000,0.0000000,0.0000000,180.0000000, -1, -1, -1, 250.0);//Barrier

	GateData[gate_lvpd1] = CreateDynamicObject(971,2294.2000000,2499.2800000,5.4000000,0.0000000,0.0000000,270.0000000, -1, -1, -1, 250.0); //LVPD Gate #1
	GateData[gate_lvpd2] = CreateDynamicObject(971,2334.6699000,2443.5000000,8.2000000,0.0000000,0.0000000,60.0000000, -1, -1, -1, 250.0); //LVPD Gate #2
	CreateDynamicObject(2933,2294.2000000,2493.0000000,4.6000000,0.0000000,90.0000000,90.0000000, -1, -1, -1, 250.0);//Barrier

	CreateDynamicMapIcon(1555.5001, -1675.6128, 16.1953, 30, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LSPD
	CreateDynamicMapIcon(-1605.5293, 710.2780, 13.8672, 30, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SFPD
	CreateDynamicMapIcon(2287.0400, 2432.3660, 10.8203, 30, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LVPD

	CreateDynamicMapIcon(1411.5087, -1699.5972, 13.5395, 16, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS CIA Headquarters
	CreateDynamicMapIcon(-1703.9641, 785.7291, 25.7364, 16, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF CIA Headquarters
	CreateDynamicMapIcon(2487.7410, 2397.2090, 10.8203, 16, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV CIA Headquarters

	CreateDynamicMapIcon(284.0110, 1943.9561, 17.6406, 37, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Army Base
	CreateDynamicMapIcon(-1316.204833, 491.737731, 11.195312, 37, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Navy Base
	CreateDynamicMapIcon(2745.950683, -2454.634521, 13.862256, 37, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Docks Base

	DeptData[lspd_desk_pickup] = CreateDynamicPickup(1239, 1, 250.0496, 67.7631, 1003.6406, -1, -1, -1, 50.0, -1, 0);//LSPD Desk Pickup
	DeptData[lspd_garage_pickup] = CreateDynamicPickup(1318, 1, 1585.1256, -1677.8413, 5.8970, -1, -1, -1, 100.00, -1, 0);//LSPD Garage

	DeptData[sfpd_desk_pickup] = CreateDynamicPickup(1239, 1, 246.4028, 118.5377, 1003.2188, -1, -1, -1, 50.0, -1, 0);//SFPD Desk Pickup
	DeptData[sfpd_garage_pickup] = CreateDynamicPickup(1318, 1, -1606.3809, 732.6853, -5.2422, -1, -1, -1, 100.0, -1, 0);//SFPD Garage

	DeptData[lvpd_desk_pickup] = CreateDynamicPickup(1239, 1, 232.2856, 165.1679, 1003.0234, -1, -1, -1, 50.0, -1, 0);//LVPD Desk Pickup
	DeptData[lvpd_garage_pickup] = CreateDynamicPickup(1318, 1, 2240.0205, 2430.9438, 3.2734, -1, -1, -1, 100.0, -1, 0);//LVPD Garage

	DeptData[cia_desk_pickup] = CreateDynamicPickup(1239, 1, 361.8299, 173.6531, 1008.3828, -1, -1, -1, 50.0, -1, 0);//CIA Headquarters Desk

	DeptData[army_desk_pickup] = CreateDynamicPickup(1239, 1, 284.0110, 1943.9561, 17.6406, -1, -1, -1, 50.0, -1, 0);//Army Desk
	DeptData[navy_desk_pickup] = CreateDynamicPickup(1239, 1, -1316.204833, 491.737731, 11.195312, -1, -1, -1, 50.0, -1, 0);//Navy Desk
	DeptData[docks_desk_pickup] = CreateDynamicPickup(1239, 1, 2745.950683, -2454.634521, 13.862256, -1, -1, -1, 50.0, -1, 0);//Docks Desk

	DeptData[lspd_ent_cp] = CreateDynamicCP(1555.5001, -1675.6128, 16.1953, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Entrance
	DeptData[lspd_ext_cp] = CreateDynamicCP(246.7801, 62.3251, 1003.6406, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Exit
	DeptData[lspd_desk_cp] = CreateDynamicCP(250.0496, 67.7631, 1003.6406, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Desk

	DeptData[lspd_base_cp] = CreateDynamicCP(1568.6329, -1689.9703, 6.2188, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Fire Exit (Basement)
	DeptData[lspd_cells_cp] = CreateDynamicCP(254.8615, 82.2829, 1002.4453, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Fire Exit (Cells)
	DeptData[lspd_roof_cp] = CreateDynamicCP(1564.8525, -1666.8971, 28.3956, 1.0, -1, -1, -1, 5.0, -1, 0);//LSPD Fire Exit (Rooftop)

	DeptData[lspd_garage_cp] = CreateDynamicCP(1585.1256, -1677.8413, 5.8970, 3.0, -1, -1, -1, 15.0, -1, 0);//LSPD Garage

	DeptData[sfpd_ent_cp] = CreateDynamicCP(-1605.5293, 710.2780, 13.8672, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Entrance
	DeptData[sfpd_ext_cp] = CreateDynamicCP(246.4149, 107.3009, 1003.2188, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Exit
	DeptData[sfpd_desk_cp] = CreateDynamicCP(246.4028, 118.5377, 1003.2188, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Desk

	DeptData[sfpd_base_cp] = CreateDynamicCP(-1594.2123, 716.2012, -4.9063, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Fire Exit (Basement)
	DeptData[sfpd_cells_cp] = CreateDynamicCP(214.1032, 119.1255, 999.0156, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Fire Exit (Cells)
	DeptData[sfpd_roof_cp] = CreateDynamicCP(-1610.0029, 703.3573, 48.9375, 1.0, -1, -1, -1, 5.0, -1, 0);//SFPD Fire Exit (Rooftop)

	DeptData[sfpd_garage_cp] = CreateDynamicCP(-1606.3809, 732.6853, -5.2422, 3.0, -1, -1, -1, 15.0, -1, 0);//SFPD Garage

	DeptData[lvpd_ent1_cp] = CreateDynamicCP(2287.0400, 2432.3660, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Entrance 1
	DeptData[lvpd_ent2_cp] = CreateDynamicCP(2337.1648, 2459.3130, 14.9742, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Entrance 2
	DeptData[lvpd_ext1_cp] = CreateDynamicCP(288.8626, 166.9246, 1007.1719, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Exit 1
	DeptData[lvpd_ext2_cp] = CreateDynamicCP(238.6626, 138.6895, 1003.0234, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Exit 2
	DeptData[lvpd_desk_cp] = CreateDynamicCP(232.2856, 165.1679, 1003.0234, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Desk

	DeptData[lvpd_base_cp] = CreateDynamicCP(2282.2268, 2423.1140, 3.4766, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Fire Exit (Basement)
	DeptData[lvpd_cells_cp] = CreateDynamicCP(196.3029, 168.1445, 1003.0234, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Fire Exit (Cells)
	DeptData[lvpd_roof_cp] = CreateDynamicCP(2296.5237, 2442.6028, 46.9775, 1.0, -1, -1, -1, 5.0, -1, 0);//LVPD Fire Exit (Rooftop)

	DeptData[lvpd_garage_cp] = CreateDynamicCP(2240.0205, 2430.9438, 3.2734, 3.0, -1, -1, -1, 15.0, -1, 0);//LVPD Garage

	DeptData[lscia_ent_cp] = CreateDynamicCP(1411.5087, -1699.5972, 13.5395, 1.0, -1, -1, -1, 5.0, -1, 0);//LS CIA Headquarters Entrance
	DeptData[sfcia_ent_cp] = CreateDynamicCP(-1703.9641, 785.7291, 25.7364, 1.0, -1, -1, -1, 5.0, -1, 0);//SF CIA Headquarters Entrance
	DeptData[lvcia_ent_cp] = CreateDynamicCP(2487.7410, 2397.2090, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LV CIA Headquarters Entrance
	DeptData[cia_exit_cp] = CreateDynamicCP(390.7698, 173.8202, 1008.3828, 1.0, -1, -1, -1, 5.0, -1, 0);//CIA Headquarters Exit
	DeptData[cia_desk_cp] = CreateDynamicCP(361.8299, 173.6531, 1008.3828, 1.0, -1, -1, -1, 5.0, -1, 0);//CIA Headquarters Desk

	DeptData[army_desk_cp] = CreateDynamicCP(284.0110, 1943.9561, 17.6406, 1.0, -1, -1, -1, 5.0, -1, 0);//Army Desk
	DeptData[navy_desk_cp] = CreateDynamicCP(-1316.204833, 491.737731, 11.195312, 1.0, -1, -1, -1, 5.0, -1, 0);//Navy Desk
	DeptData[docks_desk_cp] = CreateDynamicCP(2745.950683, -2454.634521, 13.862256, 1.0, -1, -1, -1, 5.0, -1, 0);//Docks Desk

	DeptData[navy_ladder1_cp] = CreateDynamicCP(-1320.350219, 484.237335, 6.377983, 1.0, -1, -1, -1, 5.0, -1, 0);//Navy Ladder (Bottom)
	DeptData[navy_ladder2_cp] = CreateDynamicCP(-1320.352905, 485.106964, 11.187500, 1.0, -1, -1, -1, 5.0, -1, 0);//Navy Ladder (Top)
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		OffenderData[playerid][offender_fine] = 0;
		OffenderData[playerid][offender_ticketer] = INVALID_PLAYER_ID;
		OffenderData[playerid][offender_timer] = -1;
		OffenderData[playerid][offender_ticketed] = false;
		OffenderData[playerid][offender_arrested] = false;

		OfficerData[playerid][pd_garage_location] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case POLICE_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_COP, true);
		    		ShowPoliceSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a police officer skin to clock-on as a police officer.");
		    	}
		    	else if(job == POLICE_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a police officer.");
		    	}
		    }
		    return 1;
		}
		case LSPD_FIRE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Basement
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1568.7290, -1691.8344, 5.8906);
						SetPlayerFacingAngle(playerid, 180.3006);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Cells
					{
						SetPlayerInterior(playerid, 6);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 254.8756, 83.8060, 1002.4453);
						SetPlayerFacingAngle(playerid, 359.4491);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Rooftop
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1564.8939, -1665.2053, 28.3956);
						SetPlayerFacingAngle(playerid, 357.7802);
						return SetCameraBehindPlayer(playerid);
					}
				}
			}
			return 1;
		}
		case SFPD_FIRE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Basement
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1592.2904, 716.1781, -5.2422);
						SetPlayerFacingAngle(playerid, 268.5692);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Cells
					{
						SetPlayerInterior(playerid, 10);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 215.6505, 119.1359, 999.0156);
						SetPlayerFacingAngle(playerid, 270.5016);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Rooftop
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1611.7924, 703.3594, 48.9375);
						SetPlayerFacingAngle(playerid, 89.1795);
						return SetCameraBehindPlayer(playerid);
					}
				}
			}
			return 1;
		}
		case LVPD_FIRE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Basement
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 2282.1763, 2425.2258, 3.4766);
						SetPlayerFacingAngle(playerid, 359.8269);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Cells
					{
						SetPlayerInterior(playerid, 3);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 197.8079, 168.1115, 1003.0234);
						SetPlayerFacingAngle(playerid, 269.6093);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Rooftop
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 2296.5134, 2444.5493, 46.9775);
						SetPlayerFacingAngle(playerid, 358.4346);
						return SetCameraBehindPlayer(playerid);
					}
				}
			}
			return 1;
		}
		case GARAGE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Repair
					{
						new Float:pos[3];
						foreach(new v : Vehicle)
						{
							GetVehiclePos(v, pos[0], pos[1], pos[2]);
							if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
						 	{
						   		RepairVehicle(v);

						   		ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

						   		ShowPDGarageDialog(playerid, OfficerData[playerid][pd_garage_location]);

								return PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to repair.");
					}
					case 1://Refuel
					{
						new Float:pos[3];
						foreach(new v : Vehicle)
						{
							GetVehiclePos(v, pos[0], pos[1], pos[2]);
						 	if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
						  	{
						   		SetVehicleFuel(v, 100);

						   		ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

						   		ShowPDGarageDialog(playerid, OfficerData[playerid][pd_garage_location]);

								return PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to refuel.");
					}
				}
			}
			return 1;
		}
		case CIA_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIA, true);
		    		ShowCIASkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a CIA skin to clock-on as a CIA agent.");
		    	}
		    	else if(job == CIA_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a CIA skin to clock-off as a CIA agent.");
		    	}
		    }
		    return 1;
		}
		case ARMY_DIALOG:
		{
			if(response)
			{
				new job = GetPlayerJob(playerid);
				if(job == CIVILIAN_JOB)
				{
		    		SetSkinRequest(playerid, REQUEST_TYPE_ARMY, true);
		    		ShowArmySkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a soldier skin to clock-on as a soldier.");
				}
				else if(job == ARMY_JOB)
				{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
				 	ShowCivilianSkinMenu(playerid);
				 	return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a soldier.");
				}
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == DeptData[lspd_desk_pickup] || pickupid == DeptData[sfpd_desk_pickup] || pickupid == DeptData[lvpd_desk_pickup])
	{
		return 1;
	}
	else if(pickupid == DeptData[lspd_garage_pickup] || pickupid == DeptData[sfpd_garage_pickup] || pickupid == DeptData[lvpd_garage_pickup])
	{
		return 1;
	}
	else if(pickupid == DeptData[cia_desk_pickup])
	{
		return 1;
	}
	else if(pickupid == DeptData[army_desk_pickup] || pickupid == DeptData[navy_desk_pickup] || pickupid == DeptData[docks_desk_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == DeptData[lspd_ent_cp])
		{
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 246.8269, 64.3228, 1003.6406);
			SetPlayerFacingAngle(playerid, 356.0650);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lspd_ext_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 1553.8295, -1675.6392, 16.1953);
			SetPlayerFacingAngle(playerid, 89.2095);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lspd_desk_cp])
		{
			return ShowPDMainDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == DeptData[lspd_base_cp] || checkpointid == DeptData[lspd_cells_cp] || checkpointid == DeptData[lspd_roof_cp])
		{
			return ShowFireExitDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == DeptData[lspd_garage_cp])
		{
			return ShowPDGarageDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == DeptData[sfpd_ent_cp])
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 246.3941, 109.3799, 1003.2188);
			SetPlayerFacingAngle(playerid, 359.8655);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[sfpd_ext_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, -1605.5231, 712.1763, 13.8672);
			SetPlayerFacingAngle(playerid, 354.2668);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[sfpd_desk_cp])
		{
			return ShowPDMainDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == DeptData[sfpd_base_cp] || checkpointid == DeptData[sfpd_cells_cp] || checkpointid == DeptData[sfpd_roof_cp])
		{
			return ShowFireExitDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == DeptData[sfpd_garage_cp])
		{
			return ShowPDGarageDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == DeptData[lvpd_ent1_cp])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 238.6027, 141.3288, 1003.0234);
			SetPlayerFacingAngle(playerid, 0.0568);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lvpd_ent2_cp])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 288.9532, 169.8294, 1007.1794);
			SetPlayerFacingAngle(playerid, 355.9600);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lvpd_ext1_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2336.8965, 2456.7803, 14.9688);
			SetPlayerFacingAngle(playerid, 176.4752);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lvpd_ext2_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2287.0466, 2429.0894, 10.8203);
			SetPlayerFacingAngle(playerid, 179.9845);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lvpd_desk_cp])
		{
			return ShowPDMainDialog(playerid, LAS_VENTURAS);
		}
		else if(checkpointid == DeptData[lvpd_base_cp] || checkpointid == DeptData[lvpd_cells_cp] || checkpointid == DeptData[lvpd_roof_cp])
		{
			return ShowFireExitDialog(playerid, LAS_VENTURAS);
		}
		else if(checkpointid == DeptData[lvpd_garage_cp])
		{
			return ShowPDGarageDialog(playerid, LAS_VENTURAS);
		}
		else if(checkpointid == DeptData[lscia_ent_cp])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 388.4813, 173.7632, 1008.3828);
			SetPlayerFacingAngle(playerid, 88.7266);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[sfcia_ent_cp])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 388.4813, 173.7632, 1008.3828);
			SetPlayerFacingAngle(playerid, 88.7266);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[lvcia_ent_cp])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerPos(playerid, 388.4813, 173.7632, 1008.3828);
			SetPlayerFacingAngle(playerid, 88.7266);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[cia_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS CIA Headquarters
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid,1413.4287, -1701.0034, 13.5395);
				SetPlayerFacingAngle(playerid, 232.7522);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//SF CIA Headquarters
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -1705.9448, 785.7507, 24.8906);
				SetPlayerFacingAngle(playerid, 89.7072);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//LV CIA Headquarters
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2490.3262, 2397.2917, 10.8203);
				SetPlayerFacingAngle(playerid, 271.7313);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == DeptData[cia_desk_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS CIA Headquarters
			{
				return ShowCIADialog(playerid, LOS_SANTOS);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//SF CIA Headquarters
			{
				return ShowCIADialog(playerid, SAN_FIERRO);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//LV CIA Headquarters
			{
				return ShowCIADialog(playerid, LAS_VENTURAS);
			}
		}
		else if(checkpointid == DeptData[army_desk_cp])
		{
			return ShowArmyMainDialog(playerid);
		}
		else if(checkpointid == DeptData[navy_desk_cp])
		{
			return ShowNavyMainDialog(playerid);
		}
		else if(checkpointid == DeptData[navy_ladder1_cp])
		{
			SetPlayerPos(playerid, -1321.904785, 486.004516, 11.187500);
			SetPlayerFacingAngle(playerid, 88.952171);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[navy_ladder2_cp])
		{
			SetPlayerPos(playerid, -1320.373901, 483.061645, 6.377983);
			SetPlayerFacingAngle(playerid, 178.305786);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == DeptData[docks_desk_cp])
		{
			return ShowDocksMainDialog(playerid);
		}
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(areaid == CameraData[speed_camera_ls] || areaid == CameraData[speed_camera_sf] || areaid == CameraData[speed_camera_lv])
	{
		if(IsPlayerEmergencyServices(playerid)) return 1;

		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleSpeed(GetPlayerVehicleID(playerid)) > SPEED_LIMIT)
		{
			new string[200], high = (SPEEDING_FINE - (SPEEDING_FINE / 2)), low = (SPEEDING_FINE / 2), fine = (random(high) + low);

			#if defined USE_MILES
				format(string, sizeof(string), "CAMERA: You were clocked doing %i MPH and were fined: $%i (Speed Limit: %i MPH)", (GetVehicleSpeed(GetPlayerVehicleID(playerid)) * 0.62137), fine, (SPEED_LIMIT * 0.62137));
			#else
				format(string, sizeof(string), "CAMERA: You were clocked doing %i KM/H and were fined: $%i (Speed Limit: %i KM/H)", GetVehicleSpeed(GetPlayerVehicleID(playerid)), fine, SPEED_LIMIT);
			#endif

			GivePlayerMoney(playerid, -fine);

			SetPlayerStats(playerid, STATS_TYPE_FINES, GetPlayerStats(playerid, STATS_TYPE_FINES) + 1);

			PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0);

			TextDrawShowForPlayer(playerid, speed_camera_flash);
			SetTimerEx("OnPlayerFlashed", 200, false, "i", playerid);

			return SendClientMessage(playerid, ORANGE, string);
		}
	}
	else
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			foreach(new i : Spikes)
			{
				if(SpikeData[i][spike_active] == true)
				{
					if(areaid == SpikeData[i][spike_area])
					{
						new vehicleid = GetPlayerVehicleID(playerid), panels, doors, headlights, tires;
						GetVehicleDamageStatus(vehicleid, panels, doors, headlights, tires);
						return UpdateVehicleDamageStatus(vehicleid, panels, doors, headlights, 15);
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerArrested(playerid)//Do not hook
{
	if(IsPlayerConnected(playerid))
	{
		OffenderData[playerid][offender_arrested] = false;

		new dept = ReturnPlayerCity(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		SendPlayerToJail(playerid, dept, JAIL_SECS);
	}
	return 1;
}

public OnPlayerFailTicket(playerid)//Do not hook
{
	new string[144], name[24];
	if(IsPlayerConnected(playerid))
	{
		SetPlayerWantedLevelEx(playerid, 6);

		SendClientMessage(playerid, ORANGE, "NOTICE: You have failed to pay the ticket in time.");

		GetPlayerName(playerid, name, sizeof(name));

		format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has failed to pay a ticket at: %s", name, playerid, ReturnPlayerLocation(playerid));
		PoliceRadio(ORANGE, string);
	}

	OffenderData[playerid][offender_ticketed] = false;
	OffenderData[playerid][offender_ticketer] = INVALID_PLAYER_ID;
	OffenderData[playerid][offender_fine] = 0;
	return 1;
}

public OnPlayerFlashed(playerid)//Do not hook
{
	TextDrawHideForPlayer(playerid, speed_camera_flash);
	return 1;
}

public OnSpikeStripRemove(spikeid)//Do not hook
{
	DestroyDynamicObject(SpikeData[spikeid][spike_id]);
	DestroyDynamicArea(SpikeData[spikeid][spike_area]);
	
	SpikeData[spikeid][spike_active] = false;

	Iter_Remove(Spikes, spikeid);
	return 1;
}

public OnRoadBlockRemove(blockid)//Do not hook
{
	DestroyDynamicObject(BlockData[blockid][block_id]);
	
	BlockData[blockid][block_active] = false;

	Iter_Remove(Blocks, blockid);
	return 1;
}

task OnPlayerUsePDGate[1000]()
{
	if(IsPlayerNearGate(LSPD_GATE))
	{
		MoveDynamicObject(GateData[gate_lspd], 1588.9600000, -1637.9000000, 7.2000000, 3.0, 0.0000000, 0.0000000, 180.0000000);
	}
	else
	{
		MoveDynamicObject(GateData[gate_lspd], 1588.9600000, -1637.9000000, 15.2000000, 3.0, 0.0000000, 0.0000000, 180.0000000);
	}

	if(IsPlayerNearGate(SFPD_GATE))
	{
		MoveDynamicObject(GateData[gate_sfpd1], -1644.8000000, 688.5000000, 7.9000000, 3.0, 0.0000000, 0.0000000, 180.0000000);
		MoveDynamicObject(GateData[gate_sfpd2], -1653.6000000, 688.5000000, 7.9000000, 3.0, 0.0000000, 0.0000000, 179.9950000);
	}
	else
	{
		MoveDynamicObject(GateData[gate_sfpd1], -1627.8000000, 688.5000000, 7.9000000, 3.0, 0.0000000, 0.0000000, 180.0000000);
		MoveDynamicObject(GateData[gate_sfpd2], -1636.6000000, 688.5000000, 7.9000000, 3.0, 0.0000000, 0.0000000, 179.9950000);
	}

	if(IsPlayerNearGate(LVPD1_GATE))
	{
		MoveDynamicObject(GateData[gate_lvpd1], 2294.2000000, 2499.2800000, 12.4000000, 3.0, 0.0000000, 0.0000000, 270.0000000);
	}
	else
	{
		MoveDynamicObject(GateData[gate_lvpd1], 2294.2000000, 2499.2800000, 5.4000000, 3.0, 0.0000000, 0.0000000, 270.0000000);
	}

	if(IsPlayerNearGate(LVPD2_GATE))
	{
		MoveDynamicObject(GateData[gate_lvpd2], 2334.6699000, 2443.5000000, 0.0000000, 3.0, -2.0000000, 0.0000000, 60.0000000);
	}
	else
	{
		MoveDynamicObject(GateData[gate_lvpd2], 2334.6699000, 2443.5000000, 8.2000000, 3.0, 0.0000000, 0.0000000, 60.0000000);
	}
	return 1;
}

YCMD:r(playerid, params[], help)
{
	new string[144], name[24], message[100], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(sscanf(params, "s[100]", message)) return SendClientMessage(playerid, RED, "USAGE: /r [message]");
	if(strlen(message) < 1 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-100 characters long.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	if((gettime() - 3) < GetTimerStatus(playerid, TIMER_TYPE_RADIO)) return SendClientMessage(playerid, RED, "ERROR: Please wait 3 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_RADIO, gettime());

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "RADIO(/r): %s %s: %s", ReturnPlayerJob(playerid), name, message);
	return PoliceRadio(ORANGE, string);
}

YCMD:ar(playerid, params[], help)
{
	new string[144], Float:pos[3], officer[24], offender[24], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(!IsHoldingFirearm(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be holding a firearm to make an arrest.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	
	foreach(new i : Player)
	{
	    if(GetPlayerJob(i) == CIVILIAN_JOB)
	    {
		    if(IsPlayerInRangeOfPoint(i, 5.0, pos[0], pos[1], pos[2]) && GetPlayerWantedLevel(i) >= 4 && OffenderData[i][offender_arrested] == false)
		    {
		    	if(IsPlayerInjured(i)) return SendClientMessage(playerid, RED, "ERROR: You cannot arrest injured/dead players.");
		    	if(IsPlayerRobbing(i))
		    	{
					OffenderData[i][offender_arrested] = true;
					CallLocalFunction("OnPlayerFinishRobbery", "iiii", i, GetRobberyClerkID(i), 0, TYPE_FAILED);
		    	}

				if(IsPlayerCracking(i, CALIGULAS_CASINO))
				{
					SetCrackingStatus(i, CALIGULAS_CASINO, false);
				}
				else if(IsPlayerCracking(i, FOUR_DRAGONS_CASINO))
				{
					SetCrackingStatus(i, FOUR_DRAGONS_CASINO, false);
				}
				else if(IsPlayerEvading(i))
				{
					SetEvadingStatus(i, false);
				}

				SetPlayerStats(playerid, STATS_TYPE_ARRESTS, GetPlayerStats(playerid, STATS_TYPE_ARRESTS) + 1);

				SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);
				SetPlayerScore(i, GetPlayerScore(i) - 1);

				GetPlayerName(playerid, officer, sizeof(officer));
				GetPlayerName(i, offender, sizeof(offender));

				format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just arrested Suspect %s (%i) at: %s", ReturnPlayerJob(playerid), officer, playerid, offender, i, ReturnPlayerLocation(playerid));
				PoliceRadio(ORANGE, string);

				new high = (MAX_ARREST_PAY - (MAX_ARREST_PAY / 2)), low = (MAX_ARREST_PAY / 2), pay = (random(high) + low);
				GivePlayerMoney(playerid, pay);

				format(string, sizeof(string), "NOTICE: You have been paid a $%i bonus for a successful arrest.", pay);
				SendClientMessage(playerid, YELLOW, string);

				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetAnimationStatus(playerid, true);
	        		ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 1);
	        		SendClientMessage(playerid, WHITE, "SERVER: Press ENTER to stop doing the arrest animation.");
	        	}

	        	if(GetPlayerState(i) == PLAYER_STATE_ONFOOT)
				{
	        		SetPlayerSpecialAction(i, SPECIAL_ACTION_HANDSUP);

	        		SetTimerEx("OnPlayerArrested", 3000, false, "i", i);
	        	}
	        	else
	        	{
	        		SetTimerEx("OnPlayerArrested", 100, false, "i", i);
	        	}

	        	return 1;
		    }
		}
	}
	return 1;
}

YCMD:cf(playerid, params[], help)
{
	new Float:pos[3], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to cuff someone.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
    
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	
	foreach(new i : Player)
	{
	    if(GetPlayerJob(i) == CIVILIAN_JOB)
	    {
		    if(IsPlayerInRangeOfPoint(i, 5.0, pos[0], pos[1], pos[2]) && GetPlayerWantedLevel(i) >= 4 && OffenderData[i][offender_arrested] == false)
		    {
		    	if(GetPlayerState(i) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: The player must be on foot to cuff them.");
		    	if(IsPlayerInjured(i)) return SendClientMessage(playerid, RED, "ERROR: You cannot cuff injured/dead players.");
		        
		        if(GetPlayerSpecialAction(i) != SPECIAL_ACTION_CUFFED)
		        {
		            return SetPlayerSpecialAction(i, SPECIAL_ACTION_CUFFED);
		        }
		        else if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_CUFFED)
		        {
					return SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);
		        }
		    }
		}
	}
	return 1;
}

YCMD:tk(playerid, params[], help)
{
	new string[128], Float:pos[3], officer[24], offender[24], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
    
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	
	foreach(new i : Player)
	{
	    if(GetPlayerJob(i) == CIVILIAN_JOB)
	    {
		    if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerWantedLevel(i) >= 1 && GetPlayerWantedLevel(i) <= 3 && OffenderData[i][offender_ticketed] == false)
		    {
		    	new high = (MAX_FINE_FEE - (MAX_FINE_FEE / 2)), low = (MAX_FINE_FEE / 2), fine = (random(high) + low);

		        OffenderData[i][offender_ticketed] = true;
		        OffenderData[i][offender_ticketer] = playerid;
		        OffenderData[i][offender_fine] = fine;

				GetPlayerName(playerid, officer, sizeof(officer));
				GetPlayerName(i, offender, sizeof(offender));

		        format(string, sizeof(string), "NOTICE: Officer %s (%i) has issued you a $%i ticket. Type /payticket to pay it within 15 seconds or become wanted.", officer, playerid, fine);
		        SendClientMessage(i, ORANGE, string);

		        format(string, sizeof(string), "NOTICE: Offender %s (%i) has been issued a ticket. Please wait 15 seconds for their response.", offender, i);
		        SendClientMessage(playerid, ORANGE, string);

		        OffenderData[i][offender_timer] = SetTimerEx("OnPlayerFailTicket", 15000, false, "i", i);
		        return 1;
		    }
		}
	}
	return 1;
}

YCMD:payticket(playerid, params[], help)
{
	if(OffenderData[playerid][offender_ticketed] == false) return SendClientMessage(playerid, RED, "ERROR: You have not been issued a ticket by a police officer.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	new string[128], fine = OffenderData[playerid][offender_fine], officer = OffenderData[playerid][offender_ticketer], offender[24];
	if(GetPlayerMoneyEx(playerid) < fine) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to pay the ticket.");

	KillTimer(OffenderData[playerid][offender_timer]);
	
	SetPlayerWantedLevel(playerid, 0);
	SetPlayerColourEx(playerid, CIVILIAN_JOB);

	GivePlayerMoney(playerid, -fine);

	format(string, sizeof(string), "NOTICE: You have paid your $%i ticket.", fine);
	SendClientMessage(playerid, ORANGE, string);

	if(IsPlayerConnected(officer))
	{
		SetPlayerStats(officer, STATS_TYPE_TICKETS, GetPlayerStats(officer, STATS_TYPE_TICKETS) + 1);
		SetPlayerScore(officer, GetPlayerScore(officer) + 1);

		GetPlayerName(playerid, offender, sizeof(offender));

		format(string, sizeof(string), "NOTICE: Offender %s (%i) has paid their ticket.", offender, playerid);
		SendClientMessage(officer, YELLOW, string);
	}

	OffenderData[playerid][offender_ticketer] = INVALID_PLAYER_ID;
	OffenderData[playerid][offender_timer] = -1;
	OffenderData[playerid][offender_ticketed] = false;
	OffenderData[playerid][offender_fine] = 0;
	return 1;
}

YCMD:strip(playerid, params[], help)
{
	new slot = GetFreeSpikeSlot(), Float:pos[4], string[144], name[24], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(slot == -1) return SendClientMessage(playerid, RED, "ERROR: There are currently too many spike strips, use /dstrip to remove one first.");
	if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot create spike strips inside interiors.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	GetXYInFrontOfPlayer(playerid, pos[0], pos[1], 2.5);

	SpikeData[slot][spike_pos][0] = pos[0];
	SpikeData[slot][spike_pos][1] = pos[1];
	SpikeData[slot][spike_pos][2] = pos[2];
	SpikeData[slot][spike_pos][3] = pos[3];

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 0);

	SpikeData[slot][spike_id] = CreateDynamicObject(2899, SpikeData[slot][spike_pos][0], SpikeData[slot][spike_pos][1], SpikeData[slot][spike_pos][2] - 0.9, 0.0, 0.0, SpikeData[slot][spike_pos][3], -1, -1, -1, 250.0);
	SpikeData[slot][spike_area] = CreateDynamicSphere(SpikeData[slot][spike_pos][0], SpikeData[slot][spike_pos][1], SpikeData[slot][spike_pos][2], 3.0, -1, -1, -1, 0);
	
	foreach(new i : Player)
	{
		Streamer_UpdateEx(i, SpikeData[slot][spike_pos][0], SpikeData[slot][spike_pos][1], SpikeData[slot][spike_pos][2], -1, -1);
	}

	SpikeData[slot][spike_timer] = SetTimerEx("OnSpikeStripRemove", 30000, false, "i", slot);

	SpikeData[slot][spike_active] = true;

	Iter_Add(Spikes, slot);

	GetPlayerName(playerid, name, sizeof(name));

	format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just laid down a spike strip at: %s", ReturnPlayerJob(playerid), name, playerid, ReturnPlayerLocation(playerid));
	PoliceRadio(ORANGE, string);
	return 1;
}

YCMD:dstrip(playerid, params[], help)
{
	new job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	foreach(new i : Spikes)
	{
		if(SpikeData[i][spike_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, SpikeData[i][spike_pos][0], SpikeData[i][spike_pos][1], SpikeData[i][spike_pos][2]))
			{
				KillTimer(SpikeData[i][spike_timer]);

				DestroyDynamicObject(SpikeData[i][spike_id]);
				DestroyDynamicArea(SpikeData[i][spike_area]);
	
				SpikeData[i][spike_active] = false;

				Iter_Remove(Spikes, i);
				
				return ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);
			}
		}
	}

	SendClientMessage(playerid, RED, "ERROR: You are not near any spike strips to delete.");
	return 1;
}

YCMD:block(playerid, params[], help)
{
	new slot = GetFreeBlockSlot(), Float:pos[4], string[144], name[24], job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(slot == -1) return SendClientMessage(playerid, RED, "ERROR: There are currently too many road blocks, use /dblock to remove one first.");
	if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot create road blocks inside interiors.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	BlockData[slot][block_pos][0] = pos[0];
	BlockData[slot][block_pos][1] = pos[1];
	BlockData[slot][block_pos][2] = pos[2];
	BlockData[slot][block_pos][3] = pos[3];

	BlockData[slot][block_id] = CreateDynamicObject(978, BlockData[slot][block_pos][0], BlockData[slot][block_pos][1], BlockData[slot][block_pos][2] - 0.2, 0.0, 0.0, BlockData[slot][block_pos][3], -1, -1, -1, 250.0);
	
	BlockData[slot][block_timer] = SetTimerEx("OnRoadBlockRemove", 300000, false, "i", slot);

	BlockData[slot][block_active] = true;

	Iter_Add(Blocks, slot);

	GetXYBehindPlayer(playerid, pos[0], pos[1], 1.0);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	GetPlayerName(playerid, name, sizeof(name));

	format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just created a road block at: %s", ReturnPlayerJob(playerid), name, playerid, ReturnPlayerLocation(playerid));
	PoliceRadio(ORANGE, string);
	return 1;
}

YCMD:dblock(playerid, params[], help)
{
	new job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	foreach(new i : Blocks)
	{
		if(BlockData[i][block_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, BlockData[i][block_pos][0], BlockData[i][block_pos][1], BlockData[i][block_pos][2]))
			{
				KillTimer(BlockData[i][block_timer]);

				DestroyDynamicObject(BlockData[i][block_id]);
	
				BlockData[i][block_active] = false;

				Iter_Remove(Blocks, i);
				return 1;
			}
		}
	}

	SendClientMessage(playerid, RED, "ERROR: You are not near any road blocks to delete.");
	return 1;
}

CMD:confiscate(playerid, params[])
{
	new job = GetPlayerJob(playerid);
	if(job != POLICE_JOB && job != CIA_JOB && job != ARMY_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to law enforcement only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	foreach(new i : Player)
	{
		if(IsPlayerLogged(i))
		{
			for(new plant = 0; plant < 10; plant++)
			{
				if(PlantData[i][plant][plant_active] == true)
				{
					if(IsPlayerInRangeOfPoint(playerid, 2.0, PlantData[i][plant][plant_pos][0], PlantData[i][plant][plant_pos][1], PlantData[i][plant][plant_pos][2]))
					{
						if(playerid == i) return SendClientMessage(playerid, RED, "ERROR: You cannot confiscate your own plants.");

						new query[200];
						format(query, sizeof(query), "DELETE FROM `PLANT%i` WHERE `CHARACTER_ID` = '%i'", (plant + 1), GetPlayerCharacterID(i));
						database_result = db_query@(server_database, query);
						db_free_result@(database_result);

						new string[128];
						if(GetPlantCount(i) == 1)
						{
							format(string, sizeof(string), "NOTICE: Your last weed plant has just been confiscated at: %s", ReturnPlayerLocation(playerid));
							SendClientMessage(i, ORANGE, string);
						}
						else
						{
							format(string, sizeof(string), "NOTICE: One of your weed plants has just been confiscated at: %s", ReturnPlayerLocation(playerid));
							SendClientMessage(i, ORANGE, string);
						}

						if(PlantData[i][plant][plant_stage] >= 75)
						{
							SendClientMessage(playerid, WHITE, "EVIDENCE: You proceed to bag up the plant as evidence.");
						}
						else
						{
							SendClientMessage(playerid, WHITE, "EVIDENCE: You proceed to bag up the seeds as evidence.");
						}

						PlantData[i][plant][plant_active] = false;
						PlantData[i][plant][plant_stage] = 0;
						PlantData[i][plant][plant_age] = 0;

						DestroyDynamic3DTextLabel(PlantData[i][plant][plant_label]);
						DestroyDynamicObject(PlantData[i][plant][plant_id]);

						return ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);
					}
				}
			}
		}
	}
	return SendClientMessage(playerid, RED, "ERROR: You are not near any weed plants to confiscate.");
}
