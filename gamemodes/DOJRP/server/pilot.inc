#include <YSI_Coding\y_hooks>

enum airport_data
{
	ls_air_flight_pickup,
	ls_air_flight_cp,
	ls_air_pilot_pickup,
	ls_air_pilot_cp,

	sf_air_flight_pickup,
	sf_air_flight_cp,
	sf_air_pilot_pickup,
	sf_air_pilot_cp,

	lv_air_flight_pickup,
	lv_air_flight_cp,
	lv_air_pilot_pickup,
	lv_air_pilot_cp,

	cargo_one_flight_pickup,
	cargo_one_flight_cp,

	cargo_two_flight_pickup,
	cargo_two_flight_cp,

	cargo_three_flight_pickup,
	cargo_three_flight_cp,

	cargo_desk_pickup,
	cargo_desk_cp
};
new AirportData[airport_data];

enum flight_data
{
	flight_dest,
	flight_zone,
	flight_mapicon,
	bool:flight_passenger,
	bool:flight_cargo
};
new FlightData[MAX_PLAYERS][flight_data];

stock GetPlayerAirport(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 25.0, LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z)) return LOS_SANTOS;
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z)) return SAN_FIERRO;
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z)) return LAS_VENTURAS;
	return NO_CITY;
}

stock GetPlayerCargo(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z)) return 1;
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z)) return 2;
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z)) return 3;
	return 0;
}

stock GetPlayerPilotDesk(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1956.732299, -2181.556640, 13.546875)) return LOS_SANTOS;
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1545.416015, -442.688354, 6.000000)) return SAN_FIERRO;
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, 1717.111450, 1616.138061, 10.044930)) return LAS_VENTURAS;

	else if(IsPlayerInRangeOfPoint(playerid, 3.0, 414.8525, 2535.3264, 19.1484)) return DESERT_AIRPORT;
	return NO_CITY;
}

stock IsPlayerInPassengerPlane(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 511 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 519 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 553 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 577 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 593) return 1;
	}
	return 0;
}

stock IsPlayerInCargoHeli(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 417 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 469 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 563 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 548) return 1;
	}
	return 0;
}

stock OnPlayerFinishFlight(playerid)
{	
	new string[128], earnings = MAX_CARGO_EARNINGS;
	if(FlightData[playerid][flight_passenger] == true)
	{
		if(GetPlayerAirport(playerid) != FlightData[playerid][flight_dest]) return SendClientMessage(playerid, RED, "ERROR: This the the wrong airport, go to the marker on your minimap.");

		new high = (MAX_PASSENGER_EARNINGS - (MAX_PASSENGER_EARNINGS / 2)), low = (MAX_PASSENGER_EARNINGS / 2), passengers = 1;
		earnings = (random(high) + low);

		new vehicleid = GetPlayerVehicleID(playerid);
		switch(GetVehicleModel(vehicleid))
		{
			case 511://Beagle
			{
				passengers = 1;
			}
			case 519://Shamal
			{
				passengers = (random(4) + 4);
			}
			case 553://Nevada
			{
				passengers = (random(6) + 6);
			}
			case 577://AT400
			{
				passengers = (random(50) + 100);
			}
			case 593://Dodo
			{
				passengers = 1;
			}
			default:
			{
				passengers = 1;
			}
		}

		format(string, sizeof(string), "NOTICE: You have completed the passenger flight and moved %i passengers for: $%i", passengers, earnings);
		SendClientMessage(playerid, YELLOW, string);
	}
	else
	{
		if(GetPlayerCargo(playerid) != FlightData[playerid][flight_zone]) return SendClientMessage(playerid, RED, "ERROR: This the the wrong cargo depot, go to the marker on your minimap.");

		new high = (MAX_CARGO_EARNINGS - (MAX_CARGO_EARNINGS / 2)), low = (MAX_CARGO_EARNINGS / 2), cargo = (random(2) + 1);
		earnings = (random(high) + low);
			
		format(string, sizeof(string), "NOTICE: You have completed the cargo flight and moved %i tonnes for: $%i", cargo, earnings);
		SendClientMessage(playerid, YELLOW, string);
	}

	DestroyDynamicMapIcon(FlightData[playerid][flight_mapicon]);

	FlightData[playerid][flight_passenger] = false;
	FlightData[playerid][flight_cargo] = false;
	FlightData[playerid][flight_dest] = 0;
	FlightData[playerid][flight_zone] = 0;

	SetPlayerColor(playerid, WHITE);
			    	
	PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);

	SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);
	SetPlayerStats(playerid, STATS_TYPE_FLIGHTS, GetPlayerStats(playerid, STATS_TYPE_FLIGHTS) + 1);

	return GivePlayerMoney(playerid, earnings);
}

stock ShowPilotDeskDialog(playerid)
{
	new string[128], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(GetPlayerLicence(playerid, LICENCE_PILOT) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Pilot License to clock-on as a pilot.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a pilot while you are wanted.");

		if(GetPlayerPilotDesk(playerid) == LOS_SANTOS)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Los Santos Airport Gate", "{FFFFFF}Would you like to clock-on as a pilot?", "Yes", "No");
		}
		else if(GetPlayerPilotDesk(playerid) == SAN_FIERRO)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}San Fierro Airport Gate", "{FFFFFF}Would you like to clock-on as a pilot?", "Yes", "No");
		}
		else if(GetPlayerPilotDesk(playerid) == LAS_VENTURAS)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Las Venturas Airport Gate", "{FFFFFF}Would you like to clock-on as a pilot?", "Yes", "No");
		}
		
		else if(GetPlayerPilotDesk(playerid) == DESERT_AIRPORT)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Desert Airport Desk", "{FFFFFF}Would you like to clock-on as a pilot?", "Yes", "No");
		}
	}
	else if(job == PILOT_JOB)
	{
		if(GetPlayerPilotDesk(playerid) == LOS_SANTOS)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Los Santos Airport Gate", "{FFFFFF}Would you like to clock-off as a pilot?", "Yes", "No");
		}
		else if(GetPlayerPilotDesk(playerid) == SAN_FIERRO)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}San Fierro Airport Gate", "{FFFFFF}Would you like to clock-off as a pilot?", "Yes", "No");
		}
		else if(GetPlayerPilotDesk(playerid) == LAS_VENTURAS)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Las Venturas Airport Gate", "{FFFFFF}Would you like to clock-off as a pilot?", "Yes", "No");
		}
		
		else if(GetPlayerPilotDesk(playerid) == DESERT_AIRPORT)
		{
			return ShowPlayerDialog(playerid, PILOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Desert Airport Desk", "{FFFFFF}Would you like to clock-off as a pilot?", "Yes", "No");
		}
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a pilot while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Airport Flights
    CreateDynamicMapIcon(SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Airport Flights
    CreateDynamicMapIcon(LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Airport Flights

    CreateDynamicMapIcon(CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Cargo #1 Flights
    CreateDynamicMapIcon(CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Cargo #2 Flights
    CreateDynamicMapIcon(CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Cargo #3 Flights

    AirportData[ls_air_flight_pickup] = CreateDynamicPickup(1318, 1, LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z, -1, -1, -1, 100.0, -1, 0);//LS Airport Flights
	AirportData[ls_air_pilot_pickup] = CreateDynamicPickup(1239, 1, 1956.732299, -2181.556640, 13.546875, -1, -1, -1, 50.0, -1, 0);//LS Airport Pilot Front Gate

	AirportData[sf_air_flight_pickup] = CreateDynamicPickup(1318, 1, SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z, -1, -1, -1, 100.0, -1, 0);//SF Airport Flights
	AirportData[sf_air_pilot_pickup] = CreateDynamicPickup(1239, 1, -1545.416015, -442.688354, 6.000000, -1, -1, -1, 50.0, -1, 0);//SF Airport Pilot Front Gate

	AirportData[lv_air_flight_pickup] = CreateDynamicPickup(1318, 1, LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z, -1, -1, -1, 100.0, -1, 0);//LV Airport Flights
	AirportData[lv_air_pilot_pickup] = CreateDynamicPickup(1239, 1, 1717.111450, 1616.138061, 10.044930, -1, -1, -1, 50.0, -1, 0);//LV Airport Pilot Front Gate

	AirportData[cargo_one_flight_pickup] = CreateDynamicPickup(1318, 1, CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z, -1, -1, -1, 100.0, -1, 0);//Cargo #1 Flights
	AirportData[cargo_two_flight_pickup] = CreateDynamicPickup(1318, 1, CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z, -1, -1, -1, 100.0, -1, 0);//Cargo #2 Flights
	AirportData[cargo_three_flight_pickup] = CreateDynamicPickup(1318, 1, CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z, -1, -1, -1, 100.0, -1, 0);//Cargo #3 Flights

	AirportData[cargo_desk_pickup] = CreateDynamicPickup(1239, 1, 414.8525, 2535.3264, 19.1484, -1, -1, -1, 100.0, -1, 0);//Desert Airport (Cargo) Desk

	AirportData[ls_air_flight_cp] = CreateDynamicCP(LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//LS Airport Flights
	AirportData[ls_air_pilot_cp] = CreateDynamicCP(1956.732299, -2181.556640, 13.546875, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Airport Pilot Front Gate

	AirportData[sf_air_flight_cp] = CreateDynamicCP(SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//SF Airport Flights
	AirportData[sf_air_pilot_cp] = CreateDynamicCP(-1545.416015, -442.688354, 6.000000, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Airport Pilot Front Gate

	AirportData[lv_air_flight_cp] = CreateDynamicCP(LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//LV Airport Flights
	AirportData[lv_air_pilot_cp] = CreateDynamicCP(1717.111450, 1616.138061, 10.044930, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Airport Pilot Front Gate

	AirportData[cargo_one_flight_cp] = CreateDynamicCP(CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//Cargo #1 Flights
	AirportData[cargo_two_flight_cp] = CreateDynamicCP(CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//Cargo #2 Flights
	AirportData[cargo_three_flight_cp] = CreateDynamicCP(CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z, 10.0, -1, -1, -1, 50.0, -1, 0);//Cargo #3 Flights

	AirportData[cargo_desk_cp] = CreateDynamicCP(414.8525, 2535.3264, 19.1484, 1.0, -1, -1, -1, 5.0, -1, 0);//Desert Airport (Cargo) Desk
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		FlightData[playerid][flight_dest] = 0;
		FlightData[playerid][flight_zone] = 0;
		FlightData[playerid][flight_mapicon] = -1;
		FlightData[playerid][flight_passenger] = false;
		FlightData[playerid][flight_cargo] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case PILOT_DESK_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_PILOT, true);
		    		ShowPilotSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a pilot skin to clock-on as a pilot.");
		    	}
		    	else if(job == PILOT_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a pilot.");
		    	}
		    }
		    return 1;
		}
	}
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(FlightData[playerid][flight_passenger] == true || FlightData[playerid][flight_cargo] == true)
    {
    	DestroyDynamicMapIcon(FlightData[playerid][flight_mapicon]);
		FlightData[playerid][flight_passenger] = false;
		FlightData[playerid][flight_cargo] = false;
		FlightData[playerid][flight_dest] = 0;
		FlightData[playerid][flight_zone] = 0;

		new string[128], high = (MAX_CANCEL_FINE - (MAX_CANCEL_FINE / 2)), low = (MAX_CANCEL_FINE / 2), fine = (random(high) + low);
		GivePlayerMoney(playerid, -fine);
		
		format(string, sizeof(string), "NOTICE: Flight cancelled, you left the aircraft. (Fine: $%i)", fine);
    	SendClientMessage(playerid, ORANGE, string);
    }
    return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == AirportData[ls_air_flight_pickup] || pickupid == AirportData[sf_air_flight_pickup] || pickupid == AirportData[lv_air_flight_pickup] || pickupid == AirportData[ls_air_pilot_pickup] || 
	pickupid == AirportData[sf_air_pilot_pickup] || pickupid == AirportData[lv_air_pilot_pickup] || pickupid == AirportData[cargo_one_flight_pickup] || pickupid == AirportData[cargo_two_flight_pickup] || 
	pickupid == AirportData[cargo_three_flight_pickup] || pickupid == AirportData[cargo_desk_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(checkpointid == AirportData[ls_air_flight_cp] || checkpointid == AirportData[sf_air_flight_cp] || checkpointid == AirportData[lv_air_flight_cp])
		{
			if(GetPlayerLicence(playerid, LICENCE_PILOT) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Pilot License to be able to do passenger flights.");
			if(GetPlayerJob(playerid) != PILOT_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a pilot to be able to do passenger flights.");
			if(!IsPlayerInPassengerPlane(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Shamal, Nevada, AT-400, Beagle, or Dodo to be able to do passenger flights.");
			if(FlightData[playerid][flight_passenger] == false) return SendClientMessage(playerid, WHITE, "NOTE: Type /flight to start a passenger flight.");
			else return OnPlayerFinishFlight(playerid);
		}
		else if(checkpointid == AirportData[cargo_one_flight_cp] || checkpointid == AirportData[cargo_two_flight_cp] || checkpointid == AirportData[cargo_three_flight_cp])
		{
			if(GetPlayerLicence(playerid, LICENCE_PILOT) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Pilot License to be able to do passenger flights.");
			if(GetPlayerJob(playerid) != PILOT_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a pilot to be able to do cargo flights.");
			if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot do cargo flights while you are wanted.");
			if(!IsPlayerInCargoHeli(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Levetian, Sparrow, Raindance, or Cargobob to be able to do cargo flights.");
			if(FlightData[playerid][flight_cargo] == false) return SendClientMessage(playerid, WHITE, "NOTE: Type /flight to start a cargo flight.");
			else return OnPlayerFinishFlight(playerid);
		}
		return 1;
	}
	else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == AirportData[ls_air_pilot_cp] || checkpointid == AirportData[sf_air_pilot_cp] || checkpointid == AirportData[lv_air_pilot_cp] || checkpointid == AirportData[cargo_desk_cp])
		{
			ShowPilotDeskDialog(playerid);
		}
		return 1;
	}
	return 1;
}

YCMD:flight(playerid, params[], help)
{
	if(GetPlayerAirport(playerid))
	{
		if(FlightData[playerid][flight_passenger] == true) return SendClientMessage(playerid, RED, "ERROR: You are already doing a passenger flight, go to the waypoint marked on your minimap.");
		if(GetPlayerJob(playerid) != PILOT_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a pilot to be able to do passenger flights.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot do passenger flights while you are wanted.");
		if(GetPlayerLicence(playerid, LICENCE_PILOT) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Pilot License to be able to do passenger flights.");
	    if(!IsPlayerInPassengerPlane(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Shamal, Nevada, AT-400, Beagle, or Dodo to do passenger flights.");

        FlightData[playerid][flight_passenger] = true;
        
		new location = random(3);
		if(location == 0)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = SAN_FIERRO;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is San Fierro Airport, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = LOS_SANTOS;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Los Santos Airport, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else if(location == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = LAS_VENTURAS;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Las Venturas Airport, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(SF_AIRPORT_X, SF_AIRPORT_Y, SF_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = SAN_FIERRO;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is San Fierro Airport, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(LS_AIRPORT_X, LS_AIRPORT_Y, LS_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = LOS_SANTOS;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Los Santos Airport, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(LV_AIRPORT_X, LV_AIRPORT_Y, LV_AIRPORT_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_dest] = LAS_VENTURAS;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Las Venturas Airport, a waypoint has been marked on your minimap.");
		    }
		}
		return 1;
	}
	else if(GetPlayerCargo(playerid))
	{
		if(FlightData[playerid][flight_cargo] == true) return SendClientMessage(playerid, RED, "ERROR: You are already doing a cargo flight, go to the waypoint marked on your minimap.");
		if(GetPlayerLicence(playerid, LICENCE_PILOT) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Pilot License to be able to do cargo flights.");
		if(GetPlayerJob(playerid) != PILOT_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a pilot to be able to do cargo flights.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot do cargo flights while you are wanted.");
	    if(!IsPlayerInCargoHeli(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Levetian, Sparrow, Raindance, or Cargobob to do cargo flights.");

        FlightData[playerid][flight_cargo] = true;
        
		new location = random(3);
		if(location == 0)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 2;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #2, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 1;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #1, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else if(location == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 3;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #3, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_TWO_X, CARGO_TWO_Y, CARGO_TWO_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 2;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #2, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else
		{
		    if(IsPlayerInRangeOfPoint(playerid, 25.0, CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z))
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_ONE_X, CARGO_ONE_Y, CARGO_ONE_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 1;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #1, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	FlightData[playerid][flight_mapicon] = CreateDynamicMapIcon(CARGO_THREE_X, CARGO_THREE_Y, CARGO_THREE_Z, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	FlightData[playerid][flight_zone] = 3;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Cargo Depot #3, a waypoint has been marked on your minimap.");
		    }
		}
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: You must be at an Airport or Cargo Depot to use this command.");
	}
	return 1;
}
