#include <YSI_Coding\y_hooks>

enum retail_data
{
	//LS
	lsbinco_ent_cp,

	//SF
	sfbinco_ent_cp,

	//LV
	lvbinco_ent_cp,

	binco_exit_cp,
	binco_counter_cp
};
new RetailData[retail_data];

hook OnGameModeInit()
{
	//LS
	CreateDynamicMapIcon(2244.3191, -1665.5475, 15.4766, 45, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Binco

	//SF
	CreateDynamicMapIcon(-2373.7749, 910.1467, 45.4453, 45, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Binco

	//LV
	CreateDynamicMapIcon(1657.0343, 1733.3533, 10.8281, 45, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Binco

	//LS
	RetailData[lsbinco_ent_cp] = CreateDynamicCP(2244.3191, -1665.5475, 15.4766, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Binco Entrance

	//SF
	RetailData[sfbinco_ent_cp] = CreateDynamicCP(-2373.7749, 910.1467, 45.4453, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Binco Entrance

	//LV
	RetailData[lvbinco_ent_cp] = CreateDynamicCP(1657.0343, 1733.3533, 10.8281, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Binco Entrance

    RetailData[binco_exit_cp] = CreateDynamicCP(207.6858, -111.2659, 1005.1328, 1.0, -1, -1, -1, 5.0, -1, 0);//Binco Exit
	RetailData[binco_counter_cp] = CreateDynamicCP(207.6285, -100.3396, 1005.2578, 1.0, -1, -1, -1, 5.0, -1, 0);//Binco Counter
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == RetailData[lsbinco_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerInterior(playerid, 15);
			SetPlayerPos(playerid, 207.6797, -109.7500, 1005.1328);
			SetPlayerFacingAngle(playerid, 0.0248);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RetailData[sfbinco_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerInterior(playerid, 15);
			SetPlayerPos(playerid, 207.6797, -109.7500, 1005.1328);
			SetPlayerFacingAngle(playerid, 0.0248);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RetailData[lvbinco_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerInterior(playerid, 15);
			SetPlayerPos(playerid, 207.6797, -109.7500, 1005.1328);
			SetPlayerFacingAngle(playerid, 0.0248);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RetailData[binco_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS Binco
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, 2244.6360, -1664.5170, 15.4766);
				SetPlayerFacingAngle(playerid, 346.0298);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//SF Binco
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, -2375.7122, 910.1544, 45.4453);
				SetPlayerFacingAngle(playerid, 89.9471);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//LV Binco
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, 1655.6273, 1733.3518, 10.8281);
				SetPlayerFacingAngle(playerid, 91.1724);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == RetailData[binco_counter_cp])
		{
			new job = GetPlayerJob(playerid);
			if(job == POLICE_JOB)
		 	{
		      	ShowPoliceSkinMenu(playerid);
		 	}
			else if(job == CIA_JOB)
		  	{
		      	ShowCIASkinMenu(playerid);
		 	}
		 	else if(job == ARMY_JOB)
		 	{
		     	ShowArmySkinMenu(playerid);
			}
			else if(job == EMS_JOB)
			{
		     	ShowParamedicSkinMenu(playerid);
			}
			else if(job == FIRE_JOB)
		 	{
		     	ShowFirefighterSkinMenu(playerid);
			}
		 	else if(job == MINER_JOB)
		 	{
		      	ShowWorkerSkinMenu(playerid);
		 	}
		 	else if(job == PILOT_JOB)
		  	{
		  		ShowPilotSkinMenu(playerid);
		 	}
		 	else if(job == TRUCKER_JOB)
		  	{
		  		ShowWorkerSkinMenu(playerid);
		 	}
		 	else
			{
		   		ShowCivilianSkinMenu(playerid);
		 	}
		}
		return 1;
	}
	return 1;
}
