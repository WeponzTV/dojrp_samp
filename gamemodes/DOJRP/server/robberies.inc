#include <YSI_Coding\y_hooks>

enum robbing_data
{
	robbery_clerkid,
	bool:robbery_status
};
new RobbingData[MAX_PLAYERS][robbing_data];

stock IsPlayerRobbing(playerid) return RobbingData[playerid][robbery_status];
stock GetRobberyClerkID(playerid) return RobbingData[playerid][robbery_clerkid];

hook OnGameModeInit()
{
	Robbery_CreateActor(141, 2318.3074, -7.3343, 26.7496, 87.9017, 1, (MAX_BANK_ROBBERY / 2), MAX_BANK_ROBBERY);//LS Bank
	Robbery_CreateActor(141, 2318.3074, -7.3343, 26.7496, 87.9017, 2, (MAX_BANK_ROBBERY / 2), MAX_BANK_ROBBERY);//SF Bank
	Robbery_CreateActor(141, 2318.3074, -7.3343, 26.7496, 87.9017, 3, (MAX_BANK_ROBBERY / 2), MAX_BANK_ROBBERY);//LV Bank

	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 1, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS Ammunation (City)
	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 2, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS Ammunation (Country)
	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 3, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//SF Ammunation (City)
	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 4, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//SF Ammunation (Country)
	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 5, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LV Ammunation (City)
	Robbery_CreateActor(179, 293.5446, -83.5540, 1001.5156, 89.9373, 6, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LV Ammunation (Country)

	Robbery_CreateActor(211, 207.5954, -98.7015, 1005.2578, 180.0261, 1, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS Binco
	Robbery_CreateActor(211, 207.5954, -98.7015, 1005.2578, 180.0261, 2, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//SF Binco
	Robbery_CreateActor(211, 207.5954, -98.7015, 1005.2578, 180.0261, 3, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LV Binco

	Robbery_CreateActor(11, 498.0328, -77.5581, 998.7651, 2.2258, 0, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS City Bar (Ganton)
	Robbery_CreateActor(11, -223.1638, 1403.8470, 27.7734, 83.9405, 0, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LV Country Bar (Lil' Probe Inn)

	Robbery_CreateActor(11, 501.6992, -20.4465, 1000.6797, 89.3898, 0, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS City Club (Idlewood)
	Robbery_CreateActor(11, -2655.5132, 1407.5466, 906.2734, 268.5392, 7, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//SF City Club (Battery Point)

	Robbery_CreateActor(65, -23.3640, -57.3273, 1003.5469, 357.3208, 2, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LS City 24-7 Store (Mulholland)
	Robbery_CreateActor(65, -23.3640, -57.3273, 1003.5469, 357.3208, 3, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//SF City 24-7 Store (Downtown)
	Robbery_CreateActor(65, -23.3640, -57.3273, 1003.5469, 357.3208, 4, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//LV City 24-7 Store (Roca Escalante)

	Robbery_CreateActor(205, 376.5193, -65.8487, 1001.5078, 179.2946, 3, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Burger Shot (Temple)
	Robbery_CreateActor(205, 376.5193, -65.8487, 1001.5078, 179.2946, 4, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Burger Shot (Garcia)
	Robbery_CreateActor(205, 376.5193, -65.8487, 1001.5078, 179.2946, 5, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Burger Shot (Juniper Hollow)
	Robbery_CreateActor(205, 376.5193, -65.8487, 1001.5078, 179.2946, 6, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Burger Shot (Redsands East)
	Robbery_CreateActor(205, 376.5193, -65.8487, 1001.5078, 179.2946, 7, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Burger Shot (Whitewood Estates)

	Robbery_CreateActor(167, 368.1264, -4.4920, 1001.8516, 178.3874, 0, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Cluckin' Bell (Angel Pine)
	Robbery_CreateActor(167, 368.1264, -4.4920, 1001.8516, 178.3874, 1, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Cluckin' Bell (Bone County)
	Robbery_CreateActor(167, 368.1264, -4.4920, 1001.8516, 178.3874, 2, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Cluckin' Bell (Tierra Robada)

	Robbery_CreateActor(155, 374.7267, -117.2760, 1001.4922, 178.7570, 1, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Well Stacked (Idlewood)
	Robbery_CreateActor(155, 374.7267, -117.2760, 1001.4922, 178.7570, 2, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Well Stacked (Palomino Creek)
	Robbery_CreateActor(155, 374.7267, -117.2760, 1001.4922, 178.7570, 3, (MAX_STORE_ROBBERY / 2), MAX_STORE_ROBBERY);//Well Stacked (Montgomery)
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		RobbingData[playerid][robbery_clerkid] = -1;
		RobbingData[playerid][robbery_status] = false;
	}
	return 1;
}

public OnPlayerRequestRobbery(playerid, actorid)//Hooking does not work...
{
	if(GetPlayerJob(playerid) != CIVILIAN_JOB)
	{
		SendClientMessage(playerid, ORANGE, "SERVER: You must be a civilian to be able to hold up businesses.");
		return 0;
	}

	if(!IsHoldingFirearm(playerid))
	{
		SendClientMessage(playerid, ORANGE, "SERVER: You must be holding a firearm to commit a holdup.");
		return 0;
	}

	if(GetPlayerLastRobbery(playerid) > 0)
	{
		if((gettime() - 300) < GetPlayerLastRobbery(playerid))
		{
			SendClientMessage(playerid, RED, "ERROR: Please wait 5 minutes before doing another robbery.");
			return 0;
		}
	}
	return 1;
}

public OnPlayerStartRobbery(playerid, actorid, bool:robbed_recently)//Hooking does not work...
{
	if(robbed_recently == true) return 0;
	if(GetPlayerJob(playerid) != CIVILIAN_JOB) return 0;

	SetPlayerLastRobbery(playerid, gettime());

	RobbingData[playerid][robbery_clerkid] = actorid;
	RobbingData[playerid][robbery_status] = true;
	
	SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 4);
	SetPlayerColor(playerid, RED);

	SendClientMessage(playerid, ORANGE, "NOTICE: You are currently holding up the business, wait until you finish.");

	new string[144], name[24];
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) is holding up the business at: %s", name, playerid, ReturnPlayerLocation(playerid));
	return PoliceRadio(ORANGE, string);
}

public OnPlayerFinishRobbery(playerid, actorid, robbedmoney, type)//Hooking does not work...
{
	if(RobbingData[playerid][robbery_status] == true)
	{
		RobbingData[playerid][robbery_status] = false;
		RobbingData[playerid][robbery_clerkid] = -1;

		if(type == TYPE_FAILED)
		{
			if(GetPlayerJob(playerid) != CIVILIAN_JOB) return 0;
			if(!IsPlayerArrested(playerid))
			{
				SetPlayerWantedLevel(playerid, 6);
				SetPlayerColor(playerid, RED);

				SendClientMessage(playerid, RED, "NOTICE: You have failed to rob the business.");
			}
			else
			{
				SetArrestStatus(playerid, false);
			}
			return 0;
		}
		else
		{
			SetPlayerWantedLevel(playerid, 6);
			SetPlayerColor(playerid, RED);

			if(robbedmoney > 0)
			{
				GivePlayerMoney(playerid, robbedmoney);

				SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);

				SetPlayerStats(playerid, STATS_TYPE_ROBBERIES, GetPlayerStats(playerid, STATS_TYPE_ROBBERIES) + 1);

				new string[128];
				format(string, sizeof(string), "NOTICE: You have successfully robbed the business for $%i!", robbedmoney);
				SendClientMessage(playerid, YELLOW, string);
			}
			else
			{
				SendClientMessage(playerid, RED, "NOTICE: You have failed to rob the business.");
			}
		}
	}
	return 1;
}
