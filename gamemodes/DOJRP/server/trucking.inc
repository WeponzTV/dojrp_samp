#include <YSI_Coding\y_hooks>

enum depot_data
{
	//Main Depot (Blueberry)
	blueberry_desk_pickup,
	blueberry_desk_cp,

	//LS
	blueberry_depot_cp,
	blueberry_depot_pickup,
	oceandocks_depot_cp,
	oceandocks_depot_pickup,

	//SF
	doherty_depot_cp,
	doherty_depot_pickup,

	//LV
	blackfield_depot_cp,
	blackfield_depot_pickup
};
new DepotData[depot_data];

enum haul_data
{
	haul_dest,
	haul_mapicon,
	bool:haul_active
};
new HaulData[MAX_PLAYERS][haul_data];

stock IsPlayerInWorkTruck(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 578) return 1;
	}
	return 0;
}

stock ShowDepotDeskDialog(playerid)
{
	new string[128], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(GetPlayerLicence(playerid, LICENCE_TRUCK) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Truck License to clock-on as a truck driver.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a truck driver while you are wanted.");

		return ShowPlayerDialog(playerid, DEPOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Blueberry Truck Depot", "{FFFFFF}Would you like to clock-on as a truck driver?", "Yes", "No");
	}
	else if(job == TRUCKER_JOB)
	{
		return ShowPlayerDialog(playerid, DEPOT_DESK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Blueberry Truck Depot", "{FFFFFF}Would you like to clock-off as a truck driver?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a truck driver while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock GetPlayerDepot(playerid)
{
	//LS
	if(IsPlayerInRangeOfPoint(playerid, 25.0, 103.9129, -270.6762, 1.5781)) return 1;//Blueberry Truck Depot (LS)
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, 2204.6218, -2236.0657, 13.5469)) return 2;//Ocean Docks Truck Depot (LS)

	//SF
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, -2115.2649, -214.6453, 35.3203)) return 3;//Doherty Truck Depot (SF)

	//LV
	else if(IsPlayerInRangeOfPoint(playerid, 25.0, 1048.0469, 1317.9489, 10.8203)) return 4;//BlackField Truck Depot (LV)
	return 0;
}

stock OnPlayerFinishHaul(playerid)
{	
	new string[128], earnings = MAX_HAUL_EARNINGS;
	if(HaulData[playerid][haul_active] == true)
	{
		if(GetPlayerDepot(playerid) != HaulData[playerid][haul_dest]) return SendClientMessage(playerid, RED, "ERROR: This the the wrong depot, go to the marker on your minimap.");

		new high = (MAX_HAUL_EARNINGS - (MAX_HAUL_EARNINGS / 2)), low = (MAX_HAUL_EARNINGS / 2), amount = (random(50) + 50);
		earnings = (random(high) + low);

		new vehicleid = GetPlayerVehicleID(playerid), cargo[32];
		if(IsTrailerAttachedToVehicle(vehicleid))
		{
			new trailerid = GetVehicleTrailer(vehicleid);
			switch(GetVehicleModel(trailerid))
			{
				case 435://Article Trailer
				{
					cargo = "tonnes of White Goods";
				}
				case 450://Article Trailer #2
				{
					cargo = "tonnes of Dirt";
				}
				case 584://Petrol Trailer
				{
					cargo = "thousand gallons of Petroleum";
				}
				case 591://Article Trailer #3
				{
					cargo = "tonnes of Electronics";
				}
				default:
				{
					cargo = "pounds of Paper Work";
				}
			}
		}
		else
		{
			cargo = "pounds of Paper Work";
		}

		format(string, sizeof(string), "NOTICE: You have completed the haul and moved %i %s for: $%i", amount, cargo, earnings);
		SendClientMessage(playerid, YELLOW, string);

		if(HaulData[playerid][haul_mapicon] != -1) { DestroyDynamicMapIcon(HaulData[playerid][haul_mapicon]); }

		HaulData[playerid][haul_active] = false;
		HaulData[playerid][haul_dest] = 0;

		SetPlayerColor(playerid, WHITE);
				    	
		PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);

		SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);
		SetPlayerStats(playerid, STATS_TYPE_HAULS, GetPlayerStats(playerid, STATS_TYPE_HAULS) + 1);

		GivePlayerMoney(playerid, earnings);
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(86.4582, -296.9216, 1.5781, 51, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Blueberry Truck Depot (Office)

	CreateDynamicMapIcon(103.9129, -270.6762, 1.5781, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Blueberry Truck Depot (LS)
	CreateDynamicMapIcon(2204.6218, -2236.0657, 13.5469, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Ocean Docks Truck Depot (LS)

	CreateDynamicMapIcon(-2115.2649, -214.6453, 35.3203, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Doherty Truck Depot (SF)

	CreateDynamicMapIcon(1048.0469, 1317.9489, 10.8203, 53, -1, -1, -1, -1, 500.0, MAPICON_LOCAL, -1, 0);//Blackfield Truck Depot (LV)

	//Main Depot (Blueberry)
	DepotData[blueberry_desk_pickup] = CreateDynamicPickup(1239, 1, 86.4582, -296.9216, 1.5781, -1, -1, -1, 50.0, -1, 0);//Blueberry Truck Depot (Office)
	
	DepotData[blueberry_desk_cp] = CreateDynamicCP(86.4582, -296.9216, 1.5781, 1.0, -1, -1, -1, 5.0, -1, 0);//Blueberry Truck Depot (Office)

	//LS Depot Locations
	DepotData[blueberry_depot_pickup] = CreateDynamicPickup(1318, 1, 103.9129, -270.6762, 1.5781, -1, -1, -1, 100.0, -1, 0);//Blueberry Truck Depot (LS)
	DepotData[blueberry_depot_cp] = CreateDynamicCP(103.9129, -270.6762, 1.5781, 10.0, -1, -1, -1, 25.0, -1, 0);//Blueberry Truck Depot (LS)

	DepotData[oceandocks_depot_pickup] = CreateDynamicPickup(1318, 1, 2204.6218, -2236.0657, 13.5469, -1, -1, -1, 100.0, -1, 0);//Ocean Docks Truck Depot (LS)
	DepotData[oceandocks_depot_cp] = CreateDynamicCP(2204.6218, -2236.0657, 13.5469, 10.0, -1, -1, -1, 25.0, -1, 0);//Ocean Docks Truck Depot (LS)
	
	//SF Depot Locations
	DepotData[doherty_depot_pickup] = CreateDynamicPickup(1318, 1, -2115.2649, -214.6453, 35.3203, -1, -1, -1, 100.0, -1, 0);//Doherty Truck Depot (SF)
	DepotData[doherty_depot_cp] = CreateDynamicCP(-2115.2649, -214.6453, 35.3203, 10.0, -1, -1, -1, 25.0, -1, 0);//Doherty Truck Depot (SF)
	
	//LV Depot Locations
	DepotData[blackfield_depot_pickup] = CreateDynamicPickup(1318, 1, 1048.0469, 1317.9489, 10.8203, -1, -1, -1, 100.0, -1, 0);//Blackfield Truck Depot (LV)
	DepotData[blackfield_depot_cp] = CreateDynamicCP(1048.0469, 1317.9489, 10.8203, 10.0, -1, -1, -1, 25.0, -1, 0);//Blackfield Truck Depot (LV)
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		HaulData[playerid][haul_dest] = 0;
		HaulData[playerid][haul_mapicon] = -1;
		HaulData[playerid][haul_active] = false;
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{
		if(HaulData[playerid][haul_mapicon] != -1) { DestroyDynamicMapIcon(HaulData[playerid][haul_mapicon]); }
		HaulData[playerid][haul_dest] = 0;
		HaulData[playerid][haul_mapicon] = -1;
		HaulData[playerid][haul_active] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DEPOT_DESK_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_TRUCKER, true);
		    		ShowWorkerSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a worker skin to clock-on as a truck driver.");
		    	}
		    	else if(job == TRUCKER_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a truck driver.");
		    	}
		    }
		    return 1;
		}
	}
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(HaulData[playerid][haul_active] == true)
    {
    	if(HaulData[playerid][haul_mapicon] != -1) { DestroyDynamicMapIcon(HaulData[playerid][haul_mapicon]); }
		HaulData[playerid][haul_dest] = 0;
		HaulData[playerid][haul_mapicon] = -1;
		HaulData[playerid][haul_active] = false;

		new string[128], high = (MAX_CANCEL_FINE - (MAX_CANCEL_FINE / 2)), low = (MAX_CANCEL_FINE / 2), fine = (random(high) + low);
		GivePlayerMoney(playerid, -fine);
		
		format(string, sizeof(string), "NOTICE: Haul cancelled, you left the truck. (Fine: $%i)", fine);
    	SendClientMessage(playerid, ORANGE, string);
    }
    return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == DepotData[blueberry_desk_pickup])
	{
		return 1;
	}
	else if(pickupid == DepotData[blueberry_depot_pickup] || pickupid == DepotData[oceandocks_depot_pickup] || pickupid == DepotData[doherty_depot_pickup] || pickupid == DepotData[blackfield_depot_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(checkpointid == DepotData[blueberry_depot_cp] || checkpointid == DepotData[oceandocks_depot_cp] || checkpointid == DepotData[doherty_depot_cp] || checkpointid == DepotData[blackfield_depot_cp])
		{
			if(GetPlayerLicence(playerid, LICENCE_TRUCK) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Truck License to be able to do hauling jobs.");
			if(GetPlayerJob(playerid) != TRUCKER_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a truck driver to be able to do hauling jobs.");
			if(!IsPlayerInWorkTruck(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Tanker, Roadtrain, or DFT-30 to be able to do hauling jobs.");
			if(HaulData[playerid][haul_active] == false) return SendClientMessage(playerid, WHITE, "NOTE: Type /haul to start a hauling job.");
			return OnPlayerFinishHaul(playerid);
		}
		return 1;
	}
	else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == DepotData[blueberry_desk_cp])
		{
			ShowDepotDeskDialog(playerid);
		}
		return 1;
	}
	return 1;
}

YCMD:haul(playerid, params[], help)
{
	new depot = GetPlayerDepot(playerid);
	if(depot != 0)
	{
		if(HaulData[playerid][haul_active] == true) return SendClientMessage(playerid, RED, "ERROR: You are already doing a haul, go to the waypoint marked on your minimap.");
		if(GetPlayerJob(playerid) != TRUCKER_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a truck driver to be able to do hauling jobs.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot do hauling jobs while you are wanted.");
		if(GetPlayerLicence(playerid, LICENCE_TRUCK) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Truck License to be able to do hauling jobs.");
	    if(!IsPlayerInWorkTruck(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be in a Tanker, Roadtrain, or DFT-30 to be able to do hauling jobs.");

        HaulData[playerid][haul_active] = true;
        
		new location = (random(4) + 1);
		if(location == 1)//Blueberry Truck Depot (LS)
		{
		    if(depot == 1)
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(2204.6218, -2236.0657, 13.5469, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 2;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Ocean Docks Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(82.2818, -227.8469, 1.5781, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 1;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Blueberry Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else if(location == 2)//Ocean Docks Truck Depot (LS)
		{
		    if(depot == 2)
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(82.2818, -227.8469, 1.5781, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 1;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Blueberry Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(2204.6218, -2236.0657, 13.5469, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 2;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Ocean Docks Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else if(location == 3)//Doherty Truck Depot (SF)
		{
		    if(depot == 3)
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(1048.0469, 1317.9489, 10.8203, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 4;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Blackfield Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(-2115.2649, -214.6453, 35.3203, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 3;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Doherty Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		else if(location == 4)//Blackfield Truck Depot (LV)
		{
		    if(depot == 4)
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(-2115.2649, -214.6453, 35.3203, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 3;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Doherty Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    else
		    {
		    	HaulData[playerid][haul_mapicon] = CreateDynamicMapIcon(1048.0469, 1317.9489, 10.8203, 41, -1, -1, -1, playerid, 6000.0, MAPICON_GLOBAL, -1, 1);

		    	HaulData[playerid][haul_dest] = 4;
     			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
     			SetPlayerColor(playerid, ORANGE);

				SendClientMessage(playerid, WHITE, "SERVER: Your destination is Blackfield Truck Depot, a waypoint has been marked on your minimap.");
		    }
		    return 1;
		}
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: You must be at a Truck Depot to use this command.");
	}
	return 1;
}
