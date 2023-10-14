#include <YSI_Coding\y_hooks>

new Iterator:LSBusStops<MAX_LS_STOPS>;
new Iterator:SFBusStops<MAX_SF_STOPS>;
new Iterator:LVBusStops<MAX_LV_STOPS>;

enum transport_data
{
	ls_airport_pickup,
	ls_airport_cp,

	sf_airport_pickup,
	sf_airport_cp,

	lv_airport_pickup,
	lv_airport_cp
};
new TransportData[transport_data];

enum ls_bus_data
{
	stop_obj,
	stop_pickup,
	stop_icon,
	stop_name[64],
	Float:stop_x,
	Float:stop_y,
	Float:stop_z,
	Float:stop_r,
	bool:stop_active
};
new LSBusData[MAX_LS_STOPS][ls_bus_data];

enum sf_bus_data
{
	stop_obj,
	stop_pickup,
	stop_icon,
	stop_name[64],
	Float:stop_x,
	Float:stop_y,
	Float:stop_z,
	Float:stop_r,
	bool:stop_active
};
new SFBusData[MAX_SF_STOPS][sf_bus_data];

enum lv_bus_data
{
	stop_obj,
	stop_pickup,
	stop_icon,
	stop_name[64],
	Float:stop_x,
	Float:stop_y,
	Float:stop_z,
	Float:stop_r,
	bool:stop_active
};
new LVBusData[MAX_LV_STOPS][lv_bus_data];

stock GetXYBehindPoint(&Float:x, &Float:y, Float:angle, Float:distance)
{
	x -= (distance * floatsin(-angle, degrees));
	y -= (distance * floatcos(-angle, degrees));
	return 1;
}

stock GetFreeBusStopID(city)
{
	if(city == LOS_SANTOS)
	{
		for(new i = 0; i < MAX_LS_STOPS; i++)
		{
			if(LSBusData[i][stop_active] == false) return i;
		}
	}
	else if(city == SAN_FIERRO)
	{
		for(new i = 0; i < MAX_SF_STOPS; i++)
		{
			if(SFBusData[i][stop_active] == false) return i;
		}
	}
	else if(city == LAS_VENTURAS)
	{
		for(new i = 0; i < MAX_LV_STOPS; i++)
		{
			if(LVBusData[i][stop_active] == false) return i;
		}
	}
	return -1;
}

stock Float:ReturnSignRotation(direction[])
{
	if(!strcmp(direction, "north", true)) return 180.0;
	else if(!strcmp(direction, "south", true)) return 0.0;
	else if(!strcmp(direction, "east", true)) return 90.0;
	else if(!strcmp(direction, "west", true)) return -90.0;
	return 0.0;
}

stock IsPlayerInRangeOfStop(playerid, Float:range)
{
	foreach(new i : LSBusStops)
    {
		if(LSBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, range, LSBusData[i][stop_x], LSBusData[i][stop_y], LSBusData[i][stop_z])) return 1;
		}
	}

	foreach(new i : SFBusStops)
    {
		if(SFBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, range, SFBusData[i][stop_x], SFBusData[i][stop_y], SFBusData[i][stop_z])) return 1;
		}
	}

	foreach(new i : LVBusStops)
    {
		if(LVBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, range, LVBusData[i][stop_x], LVBusData[i][stop_y], LVBusData[i][stop_z])) return 1;
		}
	}
	return 0;
}

stock ShowBusDialog(playerid, city)
{
	new string[128], query[800], total = 0;
	if(city == LOS_SANTOS)
	{
		foreach(new i : LSBusStops)
		{
			if(LSBusData[i][stop_active] == true)
			{
				new Float:distance = GetPlayerDistanceFromPoint(playerid, LSBusData[i][stop_x], LSBusData[i][stop_y], LSBusData[i][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
				new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

				format(string, sizeof(string), "{FFFFFF}To: %s - Fare: $%i\n", LSBusData[i][stop_name], fare);
				strcat(query, string);
				total++;
			}
		}

		if(total == 0) return SendClientMessage(playerid, ORANGE, "SERVER: There are currently no bus stops.");
		else return ShowPlayerDialog(playerid, LS_BUS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bus Stop (LS)", query, "Travel", "Cancel");
	}
	else if(city == SAN_FIERRO)
	{
		foreach(new i : SFBusStops)
		{
			if(SFBusData[i][stop_active] == true)
			{
				new Float:distance = GetPlayerDistanceFromPoint(playerid, SFBusData[i][stop_x], SFBusData[i][stop_y], SFBusData[i][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
				new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

				format(string, sizeof(string), "{FFFFFF}To: %s - Fare: $%i\n", SFBusData[i][stop_name], fare);
				strcat(query, string);
				total++;
			}
		}
		
		if(total == 0) return SendClientMessage(playerid, ORANGE, "SERVER: There are currently no bus stops.");
		else return ShowPlayerDialog(playerid, SF_BUS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bus Stop (SF)", query, "Travel", "Cancel");
	}
	else if(city == LAS_VENTURAS)
	{
		foreach(new i : LVBusStops)
		{
			if(LVBusData[i][stop_active] == true)
			{
				new Float:distance = GetPlayerDistanceFromPoint(playerid, LVBusData[i][stop_x], LVBusData[i][stop_y], LVBusData[i][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
				new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

				format(string, sizeof(string), "{FFFFFF}To: %s - Fare: $%i\n", LVBusData[i][stop_name], fare);
				strcat(query, string);
				total++;
			}
		}
		
		if(total == 0) return SendClientMessage(playerid, ORANGE, "SERVER: There are currently no bus stops.");
		else return ShowPlayerDialog(playerid, LV_BUS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bus Stop (LV)", query, "Travel", "Cancel");
	}
	return 1;
}

stock LoadBusStops()
{
	new query[200], name[64];
    for(new ls = 0; ls < MAX_LS_STOPS; ls++)
    {
		format(query, sizeof(query), "SELECT * FROM `LSBUS` WHERE `STOP_ID` = '%i'", ls);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_get_field_assoc@(database_result, "NAME", name, sizeof(name));
			LSBusData[ls][stop_name] = name;

			LSBusData[ls][stop_x] = db_get_field_assoc_float(database_result, "X");
			LSBusData[ls][stop_y] = db_get_field_assoc_float(database_result, "Y");
			LSBusData[ls][stop_z] = db_get_field_assoc_float(database_result, "Z");
			LSBusData[ls][stop_r] = db_get_field_assoc_float(database_result, "R");

			LSBusData[ls][stop_pickup] = CreateDynamicPickup(1239, 2, LSBusData[ls][stop_x], LSBusData[ls][stop_y], LSBusData[ls][stop_z], -1, -1, -1, 50.0, -1, 0);
			LSBusData[ls][stop_obj] = CreateDynamicObject(1229, LSBusData[ls][stop_x], LSBusData[ls][stop_y], LSBusData[ls][stop_z], 0.0, 0.0, LSBusData[ls][stop_r], -1, -1, -1, 100.0);
			LSBusData[ls][stop_icon] = CreateDynamicMapIcon(LSBusData[ls][stop_x], LSBusData[ls][stop_y], LSBusData[ls][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

			LSBusData[ls][stop_active] = true;

			Iter_Add(LSBusStops, ls);
		}
		db_free_result@(database_result);
	}

	for(new sf = 0; sf < MAX_SF_STOPS; sf++)
    {
		format(query, sizeof(query), "SELECT * FROM `SFBUS` WHERE `STOP_ID` = '%i'", sf);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_get_field_assoc@(database_result, "NAME", name, sizeof(name));
			SFBusData[sf][stop_name] = name;

			SFBusData[sf][stop_x] = db_get_field_assoc_float(database_result, "X");
			SFBusData[sf][stop_y] = db_get_field_assoc_float(database_result, "Y");
			SFBusData[sf][stop_z] = db_get_field_assoc_float(database_result, "Z");
			SFBusData[sf][stop_r] = db_get_field_assoc_float(database_result, "R");

			SFBusData[sf][stop_pickup] = CreateDynamicPickup(1239, 2, SFBusData[sf][stop_x], SFBusData[sf][stop_y], SFBusData[sf][stop_z], -1, -1, -1, 50.0, -1, 0);
			SFBusData[sf][stop_obj] = CreateDynamicObject(1229, SFBusData[sf][stop_x], SFBusData[sf][stop_y], SFBusData[sf][stop_z], 0.0, 0.0, SFBusData[sf][stop_r], -1, -1, -1, 100.0);
			SFBusData[sf][stop_icon] = CreateDynamicMapIcon(SFBusData[sf][stop_x], SFBusData[sf][stop_y], SFBusData[sf][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

			SFBusData[sf][stop_active] = true;

			Iter_Add(SFBusStops, sf);
		}
		db_free_result@(database_result);
	}

	for(new lv = 0; lv < MAX_LV_STOPS; lv++)
    {
		format(query, sizeof(query), "SELECT * FROM `LVBUS` WHERE `STOP_ID` = '%i'", lv);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_get_field_assoc@(database_result, "NAME", name, sizeof(name));
			LVBusData[lv][stop_name] = name;

			LVBusData[lv][stop_x] = db_get_field_assoc_float(database_result, "X");
			LVBusData[lv][stop_y] = db_get_field_assoc_float(database_result, "Y");
			LVBusData[lv][stop_z] = db_get_field_assoc_float(database_result, "Z");
			LVBusData[lv][stop_r] = db_get_field_assoc_float(database_result, "R");

			LVBusData[lv][stop_pickup] = CreateDynamicPickup(1239, 2, LVBusData[lv][stop_x], LVBusData[lv][stop_y], LVBusData[lv][stop_z], -1, -1, -1, 50.0, -1, 0);
			LVBusData[lv][stop_obj] = CreateDynamicObject(1229, LVBusData[lv][stop_x], LVBusData[lv][stop_y], LVBusData[lv][stop_z], 0.0, 0.0, LVBusData[lv][stop_r], -1, -1, -1, 100.0);
			LVBusData[lv][stop_icon] = CreateDynamicMapIcon(LVBusData[lv][stop_x], LVBusData[lv][stop_y], LVBusData[lv][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

			LVBusData[lv][stop_active] = true;

			Iter_Add(LVBusStops, lv);
		}
		db_free_result@(database_result);
	}
	return 1;
}

stock UnloadBusStops()
{
	foreach(new i : LSBusStops)
	{
		DestroyDynamicMapIcon(LSBusData[i][stop_icon]);
		DestroyDynamicObject(LSBusData[i][stop_obj]);
		DestroyDynamicPickup(LSBusData[i][stop_pickup]);

		Iter_Remove(LSBusStops, i);
	}

	foreach(new i : SFBusStops)
	{
		DestroyDynamicMapIcon(SFBusData[i][stop_icon]);
		DestroyDynamicObject(SFBusData[i][stop_obj]);
		DestroyDynamicPickup(SFBusData[i][stop_pickup]);

		Iter_Remove(SFBusStops, i);
	}

	foreach(new i : LVBusStops)
	{
		DestroyDynamicMapIcon(LVBusData[i][stop_icon]);
		DestroyDynamicObject(LVBusData[i][stop_obj]);
		DestroyDynamicPickup(LVBusData[i][stop_pickup]);

		Iter_Remove(LVBusStops, i);
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1642.2594, -2335.4983, 13.5469, 5, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Airport
	CreateDynamicMapIcon(-1421.1642, -286.9779, 14.1484, 5, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Airport
	CreateDynamicMapIcon(1672.5367, 1447.8446, 10.7881, 5, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Airport

	TransportData[ls_airport_pickup] = CreateDynamicPickup(1239, 1, 1642.2594, -2335.4983, 13.5469, -1, -1, -1, 100.0, -1, 0);//LS Airport
	TransportData[sf_airport_pickup] = CreateDynamicPickup(1239, 1, -1421.1642, -286.9779, 14.1484, -1, -1, -1, 100.0, -1, 0);//SF Airport
	TransportData[lv_airport_pickup] = CreateDynamicPickup(1239, 1, 1672.5367, 1447.8446, 10.7881, -1, -1, -1, 100.0, -1, 0);//LV Airport

	TransportData[ls_airport_cp] = CreateDynamicCP(1642.2594, -2335.4983, 13.5469, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Airport
	TransportData[sf_airport_cp] = CreateDynamicCP(-1421.1642, -286.9779, 14.1484, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Airport
	TransportData[lv_airport_cp] = CreateDynamicCP(1672.5367, 1447.8446, 10.7881, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Airport
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case AIRPORT_DIALOG:
		{
			if(response)
			{
				new Float:ls = GetPlayerDistanceFromPoint(playerid, 1642.2594, -2335.4983, 13.5469), Float:ls_zones = (ls / PLANE_ZONE_DIST);
				new Float:sf = GetPlayerDistanceFromPoint(playerid, -1421.1642, -286.9779, 14.1484), Float:sf_zones = (sf / PLANE_ZONE_DIST);
				new Float:lv = GetPlayerDistanceFromPoint(playerid, 1672.5367, 1447.8446, 10.7881), Float:lv_zones = (lv / PLANE_ZONE_DIST);

				new string[128], ls_fare = floatround((BASE_PLANE_FAIR * ls_zones), floatround_round), sf_fare = floatround((BASE_PLANE_FAIR * sf_zones), floatround_round), lv_fare = floatround((BASE_PLANE_FAIR * lv_zones), floatround_round);

				switch(listitem)
				{
					case 0://Los Santos Airport
					{
						if(GetPlayerMoneyEx(playerid) < ls_fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the plane fare.");
						GivePlayerMoney(playerid, -ls_fare);

						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1642.2411, -2332.7742, 13.5469);
						SetPlayerFacingAngle(playerid, 0.1502);
						SetCameraBehindPlayer(playerid);

						format(string, sizeof(string), "NOTICE: You paid a $%i plane fare.", ls_fare);
						return SendClientMessage(playerid, ORANGE, string);
					}
					case 1://San Fierro Airport
					{
						if(GetPlayerMoneyEx(playerid) < sf_fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the plane fare.");
						GivePlayerMoney(playerid, -sf_fare);

						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1422.7832, -288.7293, 14.1484);
						SetPlayerFacingAngle(playerid, 136.3390);
						SetCameraBehindPlayer(playerid);

						format(string, sizeof(string), "NOTICE: You paid a $%i plane fare.", sf_fare);
						return SendClientMessage(playerid, ORANGE, string);
					}
					case 2://Las Venturas Airport
					{
						if(GetPlayerMoneyEx(playerid) < lv_fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the plane fare.");
						GivePlayerMoney(playerid, -lv_fare);

						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1674.5664, 1447.8522, 10.7900);
						SetPlayerFacingAngle(playerid, 269.8492);
						SetCameraBehindPlayer(playerid);

						format(string, sizeof(string), "NOTICE: You paid a $%i plane fare.", lv_fare);
						return SendClientMessage(playerid, ORANGE, string);
					}
				}
			}
			return 1;
		}
		case LS_BUS_DIALOG:
		{
			if(response)
			{
				if(LSBusData[listitem][stop_active] == true)
				{
					new Float:distance = GetPlayerDistanceFromPoint(playerid, LSBusData[listitem][stop_x], LSBusData[listitem][stop_y], LSBusData[listitem][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
					new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

					if(GetPlayerMoneyEx(playerid) < fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the bus fare.");

					GivePlayerMoney(playerid, -fare);

					new string[64], Float:pos[4];
					pos[0] = LSBusData[listitem][stop_x];
					pos[1] = LSBusData[listitem][stop_y];
					pos[2] = LSBusData[listitem][stop_z];
					pos[3] = LSBusData[listitem][stop_r];

					GetXYBehindPoint(pos[0], pos[1], pos[3], 2.0);

					SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
					SetPlayerFacingAngle(playerid, pos[3]);
					SetCameraBehindPlayer(playerid);

					format(string, sizeof(string), "NOTICE: You paid a $%i bus fare.", fare);
					SendClientMessage(playerid, ORANGE, string);
				}
			}
			return 1;
		}
		case SF_BUS_DIALOG:
		{
			if(response)
			{
				if(SFBusData[listitem][stop_active] == true)
				{
					new Float:distance = GetPlayerDistanceFromPoint(playerid, SFBusData[listitem][stop_x], SFBusData[listitem][stop_y], SFBusData[listitem][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
					new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

					if(GetPlayerMoneyEx(playerid) < fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the bus fare.");

					GivePlayerMoney(playerid, -fare);

					new string[64], Float:pos[4];
					pos[0] = SFBusData[listitem][stop_x];
					pos[1] = SFBusData[listitem][stop_y];
					pos[2] = SFBusData[listitem][stop_z];
					pos[3] = SFBusData[listitem][stop_r];

					GetXYBehindPoint(pos[0], pos[1], pos[3], 2.0);

					SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
					SetPlayerFacingAngle(playerid, pos[3]);
					SetCameraBehindPlayer(playerid);

					format(string, sizeof(string), "NOTICE: You paid a $%i bus fare.", fare);
					SendClientMessage(playerid, ORANGE, string);
				}
			}
			return 1;
		}
		case LV_BUS_DIALOG:
		{
			if(response)
			{
				if(LVBusData[listitem][stop_active] == true)
				{
					new Float:distance = GetPlayerDistanceFromPoint(playerid, LVBusData[listitem][stop_x], LVBusData[listitem][stop_y], LVBusData[listitem][stop_z]), Float:zones = (distance / BUS_ZONE_DIST);
					new fare = floatround((BASE_BUS_FAIR * zones), floatround_round);

					if(GetPlayerMoneyEx(playerid) < fare) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the bus fare.");

					GivePlayerMoney(playerid, -fare);

					new string[64], Float:pos[4];
					pos[0] = LVBusData[listitem][stop_x];
					pos[1] = LVBusData[listitem][stop_y];
					pos[2] = LVBusData[listitem][stop_z];
					pos[3] = LVBusData[listitem][stop_r];

					GetXYBehindPoint(pos[0], pos[1], pos[3], 2.0);

					SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
					SetPlayerFacingAngle(playerid, pos[3]);
					SetCameraBehindPlayer(playerid);

					format(string, sizeof(string), "NOTICE: You paid a $%i bus fare.", fare);
					SendClientMessage(playerid, ORANGE, string);
				}
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == TransportData[ls_airport_cp])
		{
			new Float:ls = GetPlayerDistanceFromPoint(playerid, 1642.2594, -2335.4983, 13.5469), Float:ls_zones = (ls / PLANE_ZONE_DIST);
			new Float:sf = GetPlayerDistanceFromPoint(playerid, -1421.1642, -286.9779, 14.1484), Float:sf_zones = (sf / PLANE_ZONE_DIST);
			new Float:lv = GetPlayerDistanceFromPoint(playerid, 1672.5367, 1447.8446, 10.7881), Float:lv_zones = (lv / PLANE_ZONE_DIST);

			new ls_fare = floatround((BASE_PLANE_FAIR * ls_zones), floatround_round), sf_fare = floatround((BASE_PLANE_FAIR * sf_zones), floatround_round), lv_fare = floatround((BASE_PLANE_FAIR * lv_zones), floatround_round);

			new string[300];
			format(string, sizeof(string), "{FFFFFF}To: Los Santos Airport - Fare: $%i\nTo: San Fierro Airport - Fare: $%i\nTo: Las Venturas Airport - Fare: $%i", ls_fare, sf_fare, lv_fare);
			return ShowPlayerDialog(playerid, AIRPORT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Airport", string, "Travel", "Cancel");
		}
		else if(checkpointid == TransportData[sf_airport_cp])
		{
			new Float:ls = GetPlayerDistanceFromPoint(playerid, 1642.2594, -2335.4983, 13.5469), Float:ls_zones = (ls / PLANE_ZONE_DIST);
			new Float:sf = GetPlayerDistanceFromPoint(playerid, -1421.1642, -286.9779, 14.1484), Float:sf_zones = (sf / PLANE_ZONE_DIST);
			new Float:lv = GetPlayerDistanceFromPoint(playerid, 1672.5367, 1447.8446, 10.7881), Float:lv_zones = (lv / PLANE_ZONE_DIST);

			new ls_fare = floatround((BASE_PLANE_FAIR * ls_zones), floatround_round), sf_fare = floatround((BASE_PLANE_FAIR * sf_zones), floatround_round), lv_fare = floatround((BASE_PLANE_FAIR * lv_zones), floatround_round);

			new string[300];
			format(string, sizeof(string), "{FFFFFF}To: Los Santos Airport - Fare: $%i\nTo: San Fierro Airport - Fare: $%i\nTo: Las Venturas Airport - Fare: $%i", ls_fare, sf_fare, lv_fare);
			return ShowPlayerDialog(playerid, AIRPORT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Airport", string, "Travel", "Cancel");
		}
		else if(checkpointid == TransportData[lv_airport_cp])
		{
			new Float:ls = GetPlayerDistanceFromPoint(playerid, 1642.2594, -2335.4983, 13.5469), Float:ls_zones = (ls / PLANE_ZONE_DIST);
			new Float:sf = GetPlayerDistanceFromPoint(playerid, -1421.1642, -286.9779, 14.1484), Float:sf_zones = (sf / PLANE_ZONE_DIST);
			new Float:lv = GetPlayerDistanceFromPoint(playerid, 1672.5367, 1447.8446, 10.7881), Float:lv_zones = (lv / PLANE_ZONE_DIST);

			new ls_fare = floatround((BASE_PLANE_FAIR * ls_zones), floatround_round), sf_fare = floatround((BASE_PLANE_FAIR * sf_zones), floatround_round), lv_fare = floatround((BASE_PLANE_FAIR * lv_zones), floatround_round);

			new string[300];
			format(string, sizeof(string), "{FFFFFF}To: Los Santos Airport - Fare: $%i\nTo: San Fierro Airport - Fare: $%i\nTo: Las Venturas Airport - Fare: $%i", ls_fare, sf_fare, lv_fare);
			return ShowPlayerDialog(playerid, AIRPORT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Airport", string, "Travel", "Cancel");
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == TransportData[ls_airport_pickup] || pickupid == TransportData[sf_airport_pickup] || pickupid == TransportData[lv_airport_pickup])
	{
		return 1;
	}
	else
	{
		for(new ls = 0; ls < MAX_LS_STOPS; ls++)
		{
			if(LSBusData[ls][stop_active] == true)
			{
				if(pickupid == LSBusData[ls][stop_pickup])
				{
					return ShowBusDialog(playerid, LOS_SANTOS);
				}
			}
		}

		for(new sf = 0; sf < MAX_SF_STOPS; sf++)
		{
			if(SFBusData[sf][stop_active] == true)
			{
				if(pickupid == SFBusData[sf][stop_pickup])
				{
					return ShowBusDialog(playerid, SAN_FIERRO);
				}
			}
		}

		for(new lv = 0; lv < MAX_LV_STOPS; lv++)
		{
			if(LVBusData[lv][stop_active] == true)
			{
				if(pickupid == LVBusData[lv][stop_pickup])
				{
					return ShowBusDialog(playerid, LAS_VENTURAS);
				}
			}
		}
	}
	return 1;
}

YCMD:createstop(playerid, params[], help)
{
	new query[400], string[128], busstop[64], id = -1, Float:pos[3], city[4], direction[8], name[64];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	if(sscanf(params, "s[4]s[8]s[64]", city, direction, name)) return SendClientMessage(playerid, RED, "USAGE: /createstop [city] [direction] [name]");
	if(strcmp(direction, "north", true) && strcmp(direction, "south", true) && strcmp(direction, "east", true) && strcmp(direction, "west", true)) return SendClientMessage(playerid, RED, "ERROR: The bus sign direction must be either: north/south/east/west");
	if(strlen(name) < 1 || strlen(name) > 64) return SendClientMessage(playerid, RED, "ERROR: The name must be from 1-64 characters long.");
	if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot create bus stops inside interiors.");
	
	if(IsPlayerInRangeOfStop(playerid, BUS_ZONE_DIST))
	{
		format(string, sizeof(string), "ERROR: You cannot create a bus stop within %0.0f metres of another bus stop.", BUS_ZONE_DIST);
		return SendClientMessage(playerid, RED, string);
	}

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	format(busstop, sizeof(busstop), "%s", name);

	if(!strcmp(city, "ls", true))
	{
		id = GetFreeBusStopID(LOS_SANTOS);
		if(id == -1) return SendClientMessage(playerid, RED, "ERROR: The server has reached the max aloud bus stops for this city. Change MAX_LS_STOPS in script.");

		LSBusData[id][stop_name] = busstop;
		LSBusData[id][stop_x] = pos[0];
		LSBusData[id][stop_y] = pos[1];
		LSBusData[id][stop_z] = pos[2];
		LSBusData[id][stop_r] = ReturnSignRotation(direction);

		GetXYBehindPlayer(playerid, pos[0], pos[1], 2.0);
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		LSBusData[id][stop_pickup] = CreateDynamicPickup(1239, 2, LSBusData[id][stop_x], LSBusData[id][stop_y], LSBusData[id][stop_z], -1, -1, -1, 50.0, -1, 0);
		LSBusData[id][stop_obj] = CreateDynamicObject(1229, LSBusData[id][stop_x], LSBusData[id][stop_y], LSBusData[id][stop_z], 0.0, 0.0, LSBusData[id][stop_r], -1, -1, -1, 100.0);
		LSBusData[id][stop_icon] = CreateDynamicMapIcon(LSBusData[id][stop_x], LSBusData[id][stop_y], LSBusData[id][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

		format(query, sizeof(query), "INSERT INTO `LSBUS` (`STOP_ID`, `NAME`, `X`, `Y`, `Z`, `R`) VALUES ('%i', '%q', '%f', '%f', '%f', '%f')", 
		id, LSBusData[id][stop_name], LSBusData[id][stop_x], LSBusData[id][stop_y], LSBusData[id][stop_z], LSBusData[id][stop_r]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		LSBusData[id][stop_active] = true;

		Iter_Add(LSBusStops, id);
		return 1;
	}
	else if(!strcmp(city, "sf", true))
	{
		id = GetFreeBusStopID(SAN_FIERRO);
		if(id == -1) return SendClientMessage(playerid, RED, "ERROR: The server has reached the max aloud bus stops for this city. Change MAX_SF_STOPS in script.");

		SFBusData[id][stop_name] = busstop;
		SFBusData[id][stop_x] = pos[0];
		SFBusData[id][stop_y] = pos[1];
		SFBusData[id][stop_z] = pos[2];
		SFBusData[id][stop_r] = ReturnSignRotation(direction);

		GetXYBehindPlayer(playerid, pos[0], pos[1], 2.0);
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		SFBusData[id][stop_pickup] = CreateDynamicPickup(1239, 2, SFBusData[id][stop_x], SFBusData[id][stop_y], SFBusData[id][stop_z], -1, -1, -1, 50.0, -1, 0);
		SFBusData[id][stop_obj] = CreateDynamicObject(1229, SFBusData[id][stop_x], SFBusData[id][stop_y], SFBusData[id][stop_z], 0.0, 0.0, SFBusData[id][stop_r], -1, -1, -1, 100.0);
		SFBusData[id][stop_icon] = CreateDynamicMapIcon(SFBusData[id][stop_x], SFBusData[id][stop_y], SFBusData[id][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

		format(query, sizeof(query), "INSERT INTO `SFBUS` (`STOP_ID`, `NAME`, `X`, `Y`, `Z`, `R`) VALUES ('%i', '%q', '%f', '%f', '%f', '%f')", 
		id, SFBusData[id][stop_name], SFBusData[id][stop_x], SFBusData[id][stop_y], SFBusData[id][stop_z], SFBusData[id][stop_r]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		SFBusData[id][stop_active] = true;

		Iter_Add(SFBusStops, id);
		return 1;
	}
	else if(!strcmp(city, "lv", true))
	{
		id = GetFreeBusStopID(LAS_VENTURAS);
		if(id == -1) return SendClientMessage(playerid, RED, "ERROR: The server has reached the max aloud bus stops for this city. Change MAX_LV_STOPS in script.");

		LVBusData[id][stop_name] = busstop;
		LVBusData[id][stop_x] = pos[0];
		LVBusData[id][stop_y] = pos[1];
		LVBusData[id][stop_z] = pos[2];
		LVBusData[id][stop_r] = ReturnSignRotation(direction);

		GetXYBehindPlayer(playerid, pos[0], pos[1], 2.0);
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		LVBusData[id][stop_pickup] = CreateDynamicPickup(1239, 2, LVBusData[id][stop_x], LVBusData[id][stop_y], LVBusData[id][stop_z], -1, -1, -1, 50.0, -1, 0);
		LVBusData[id][stop_obj] = CreateDynamicObject(1229, LVBusData[id][stop_x], LVBusData[id][stop_y], LVBusData[id][stop_z], 0.0, 0.0, LVBusData[id][stop_r], -1, -1, -1, 100.0);
		LVBusData[id][stop_icon] = CreateDynamicMapIcon(LVBusData[id][stop_x], LVBusData[id][stop_y], LVBusData[id][stop_z], 56, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);

		format(query, sizeof(query), "INSERT INTO `LVBUS` (`STOP_ID`, `NAME`, `X`, `Y`, `Z`, `R`) VALUES ('%i', '%q', '%f', '%f', '%f', '%f')", 
		id, LVBusData[id][stop_name], LVBusData[id][stop_x], LVBusData[id][stop_y], LVBusData[id][stop_z], LVBusData[id][stop_r]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		LVBusData[id][stop_active] = true;

		Iter_Add(LVBusStops, id);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: The bus route city must be either: ls/sf/lv");
	}
	return 1;
}

YCMD:deletestop(playerid, params[], help)
{
	new query[128];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");

	foreach(new i : LSBusStops)
    {
		if(LSBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, LSBusData[i][stop_x], LSBusData[i][stop_y], LSBusData[i][stop_z]))
			{
				format(query, sizeof(query), "DELETE FROM `LSBUS` WHERE `STOP_ID` = '%i'", i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				DestroyDynamicObject(LSBusData[i][stop_obj]);
				DestroyDynamicPickup(LSBusData[i][stop_pickup]);
				DestroyDynamicMapIcon(LSBusData[i][stop_icon]);

				LSBusData[i][stop_active] = false;

				Iter_Remove(LSBusStops, i);
				return 1;
			}
		}
	}

	foreach(new i : SFBusStops)
    {
		if(SFBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, SFBusData[i][stop_x], SFBusData[i][stop_y], SFBusData[i][stop_z]))
			{
				format(query, sizeof(query), "DELETE FROM `SFBUS` WHERE `STOP_ID` = '%i'", i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				DestroyDynamicObject(SFBusData[i][stop_obj]);
				DestroyDynamicPickup(SFBusData[i][stop_pickup]);
				DestroyDynamicMapIcon(SFBusData[i][stop_icon]);

				SFBusData[i][stop_active] = false;

				Iter_Remove(SFBusStops, i);
				return 1;
			}
		}
	}

    foreach(new i : LVBusStops)
    {
		if(LVBusData[i][stop_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, LVBusData[i][stop_x], LVBusData[i][stop_y], LVBusData[i][stop_z]))
			{
				format(query, sizeof(query), "DELETE FROM `LVBUS` WHERE `STOP_ID` = '%i'", i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				DestroyDynamicObject(LVBusData[i][stop_obj]);
				DestroyDynamicPickup(LVBusData[i][stop_pickup]);
				DestroyDynamicMapIcon(LVBusData[i][stop_icon]);

				LVBusData[i][stop_active] = false;

				Iter_Remove(LVBusStops, i);
				return 1;
			}
		}
	}

	SendClientMessage(playerid, RED, "ERROR: You are not near any bus stops to delete.");
	return 1;
}
