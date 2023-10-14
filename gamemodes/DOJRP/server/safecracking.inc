#include <YSI_Coding\y_hooks>

forward OnPlayerCrackSafe(playerid);
forward OnPlayerTakeEarnings(playerid);

forward OnCalgSafeUpdate();
forward OnDragSafeUpdate();

enum safe_data
{
	dragons_safe_cp,
	dragons_closed_obj,
	dragons_open_obj,
	dragons_robbed,
	bool:dragons_cracking,

	caligulas_safe_cp,
	caligulas_closed_obj,
	caligulas_open_obj,
	caligulas_robbed,
	bool:caligulas_cracking
};
new SafeData[safe_data];

enum cracking_data
{
	cracking_robbed,
	cracking_safe_timer,
	cracking_evade_timer,
	bool:cracking_caligulas,
	bool:cracking_dragons,
	bool:cracking_evading
};
new CrackingData[MAX_PLAYERS][cracking_data];

stock IsPlayerCracking(playerid, casino)
{
	if(casino == CALIGULAS_CASINO) return CrackingData[playerid][cracking_caligulas];
	else return CrackingData[playerid][cracking_dragons];
}

stock SetCrackingStatus(playerid, casino, bool:status)
{
	if(casino == CALIGULAS_CASINO)
	{
		if(status == false)
		{
			KillTimer(CrackingData[playerid][cracking_safe_timer]);
			CrackingData[playerid][cracking_safe_timer] = -1;
		}
		CrackingData[playerid][cracking_caligulas] = status;
		return 1;
	}
	else if(casino == FOUR_DRAGONS_CASINO)
	{
		if(status == false)
		{
			KillTimer(CrackingData[playerid][cracking_safe_timer]);
			CrackingData[playerid][cracking_safe_timer] = -1;
		}
		CrackingData[playerid][cracking_dragons] = status;
	}
	return 1;
}

stock IsPlayerEvading(playerid)
{
	return CrackingData[playerid][cracking_evading];
}

stock SetEvadingStatus(playerid, bool:status)
{
	if(status == false)
	{
		KillTimer(CrackingData[playerid][cracking_evade_timer]);
		CrackingData[playerid][cracking_evade_timer] = -1;
	}
	return CrackingData[playerid][cracking_evading] = status;
}

stock GetPlayerSafe(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, 2144.1875, 1641.9336, 993.5761)) return CALIGULAS_CASINO;
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, 2131.2161, 1600.5803, 1008.3594)) return FOUR_DRAGONS_CASINO;
	return 0;
}

stock ProcessSafeRobbery(playerid)
{
	new string[144], name[24], chance = random(4), crowbar = GetItemCount(playerid, CROWBAR_MODEL);
	GetPlayerName(playerid, name, sizeof(name));
	if(GetPlayerSafe(playerid) == CALIGULAS_CASINO)
	{
		if(crowbar > 0)
		{
			SetPlayerLastRobbery(playerid, gettime());
			
			if(chance == 0)
			{
				new check = CheckInventoryForItem(playerid, CROWBAR_MODEL);
				if(check > 0)
				{
					SafeData[caligulas_robbed] = gettime();

					RemoveItemFromInventory(playerid, check, 1, false);

					SetPlayerWantedLevel(playerid, 6);
					SetPlayerColor(playerid, RED);

					format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has failed to rob the safe at: %s", name, playerid, ReturnPlayerLocation(playerid));
					PoliceRadio(ORANGE, string);

					return SendClientMessage(playerid, ORANGE, "NOTICE: You have broken your crowbar and failed the robbery.");
				}
			}

			SafeData[caligulas_robbed] = gettime();
			SafeData[caligulas_cracking] = true;

			SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 4);
			SetPlayerColor(playerid, RED);

			CrackingData[playerid][cracking_caligulas] = true;
			CrackingData[playerid][cracking_safe_timer] = SetTimerEx("OnPlayerCrackSafe", (SAFE_CRACK_SECS * 1000), false, "i", playerid);

			if(IsValidDynamicObject(SafeData[caligulas_closed_obj]))
			{
				DestroyDynamicObject(SafeData[caligulas_closed_obj]);
				SafeData[caligulas_open_obj] = CreateDynamicObject(1829,2144.2000000,1642.3920000,993.0000000,0.0000000,0.0000000,0.0000000, -1, -1, -1, 250.0); //object(man_safenew) (1)
					
				foreach(new i : Player)
				{
					Streamer_UpdateEx(i, 2144.2000000, 1642.3920000, 993.0000000, -1, -1);
				}

				SetTimer("OnCalgSafeUpdate", (SAFE_WAIT_SECS * 1000), false);
			}

			SetAnimationStatus(playerid, false);
			ApplyAnimation(playerid, "ROB_BANK", "CAT_Safe_Rob", 4.0, 1, 0, 0, 1, 0);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) is currently robbing the safe at: %s", name, playerid, ReturnPlayerLocation(playerid));
			PoliceRadio(ORANGE, string);

			SendClientMessage(playerid, ORANGE, "NOTICE: You are currently loading up the cash, wait until you finish.");
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: You need a Crowbar to be able to crack safes.");
		}
		return 1;
	}
	else if(GetPlayerSafe(playerid) == FOUR_DRAGONS_CASINO)
	{
		if(crowbar > 0)
		{
			SetPlayerLastRobbery(playerid, gettime());
			
			if(chance == 0)
			{
				new check = CheckInventoryForItem(playerid, CROWBAR_MODEL);
				if(check > 0)
				{
					SafeData[dragons_robbed] = gettime();

					RemoveItemFromInventory(playerid, check, 1, false);

					SetPlayerWantedLevel(playerid, 6);
					SetPlayerColor(playerid, RED);

					format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) has failed to rob the safe at: %s", name, playerid, ReturnPlayerLocation(playerid));
					PoliceRadio(ORANGE, string);

					return SendClientMessage(playerid, ORANGE, "NOTICE: You have broken your crowbar and failed the robbery.");
				}
			}

			SafeData[dragons_robbed] = gettime();
			SafeData[dragons_cracking] = true;

			SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 4);
			SetPlayerColor(playerid, RED);

			CrackingData[playerid][cracking_dragons] = true;
			CrackingData[playerid][cracking_safe_timer] = SetTimerEx("OnPlayerCrackSafe", (SAFE_CRACK_SECS * 1000), false, "i", playerid);

			if(IsValidDynamicObject(SafeData[dragons_closed_obj]))
			{
				DestroyDynamicObject(SafeData[dragons_closed_obj]);
				SafeData[dragons_open_obj] = CreateDynamicObject(1829,2130.7629000,1600.6100000,1007.8200000,0.0000000,0.0000000,90.0000000, -1, -1, -1, 250.0); //object(man_safenew) (2)
					
				foreach(new i : Player)
				{
				 	Streamer_UpdateEx(i, 2130.7629000, 1600.6100000, 1007.8200000, -1, -1);
				}

				SetTimer("OnDragSafeUpdate", (SAFE_WAIT_SECS * 1000), false);
			}

			SetAnimationStatus(playerid, false);
			ApplyAnimation(playerid, "ROB_BANK", "CAT_Safe_Rob", 4.0, 1, 0, 0, 1, 0);

			format(string, sizeof(string), "RADIO(/r): Suspect %s (%i) is currently robbing the safe at: %s", name, playerid, ReturnPlayerLocation(playerid));
			PoliceRadio(ORANGE, string);

			SendClientMessage(playerid, ORANGE, "NOTICE: You are currently loading up the cash, wait until you finish.");
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: You need a Crowbar to be able to crack safes.");
		}
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: You must be at a safe to perform this action.");
	}
	return 1;
}

hook OnGameModeInit()
{
	SafeData[dragons_safe_cp] = CreateDynamicCP(2131.2161, 1600.5803, 1008.3594, 1.0, -1, -1, -1, 2.0, -1, 0);//Four Dragons Casino Safe
	SafeData[caligulas_safe_cp] = CreateDynamicCP(2144.1875, 1641.9336, 993.5761, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Casino Safe

	SafeData[dragons_closed_obj] = CreateDynamicObject(2332,2130.4500000,1600.6000000,1007.8200000,0.0000000,0.0000000,90.0000000, -1, -1, -1, 250.0); //object(kev_safe) (4)
	SafeData[caligulas_closed_obj] = CreateDynamicObject(2332,2144.2000000,1642.7000000,993.0000000,0.0000000,0.0000000,0.0000000, -1, -1, -1, 250.0); //object(kev_safe) (1)
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		CrackingData[playerid][cracking_robbed] = 0;
		CrackingData[playerid][cracking_safe_timer] = -1;
		CrackingData[playerid][cracking_evade_timer] = -1;
		CrackingData[playerid][cracking_caligulas] = false;
		CrackingData[playerid][cracking_dragons] = false;
		CrackingData[playerid][cracking_evading] = false;
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{
		if(CrackingData[playerid][cracking_evade_timer] != -1)
		{
			KillTimer(CrackingData[playerid][cracking_evade_timer]);
		}
		else if(CrackingData[playerid][cracking_safe_timer] != -1)
		{
			KillTimer(CrackingData[playerid][cracking_safe_timer]);
		}

		CrackingData[playerid][cracking_evade_timer] = -1;
		CrackingData[playerid][cracking_safe_timer] = -1;

		CrackingData[playerid][cracking_robbed] = 0;
		CrackingData[playerid][cracking_evading] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DRAGONS_SAFE_DIALOG, CALIGULAS_SAFE_DIALOG:
		{
			if(response)
			{
				return ProcessSafeRobbery(playerid);
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
		if(checkpointid == SafeData[dragons_safe_cp])
		{
			if(GetPlayerJob(playerid) != CIVILIAN_JOB) return SendClientMessage(playerid, ORANGE, "SERVER: You must be a civilian to be able to crack the safe.");
			if(CrackingData[playerid][cracking_evading] == true) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while evading arrest.");
			if(IsPlayerArrested(playerid)) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while you are under arrest.");
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while you are cuffed.");
			if(GetPlayerScore(playerid) < 50) return SendClientMessage(playerid, ORANGE, "SERVER: You need at least 50 score to be able to crack safes.");
			if(SafeData[dragons_cracking] == true) return SendClientMessage(playerid, ORANGE, "SERVER: This safe is currently being cracked.");
			if((gettime() - SAFE_WAIT_SECS) < SafeData[dragons_robbed]) return SendClientMessage(playerid, ORANGE, "SERVER: This safe has been cracked recently, come back later.");
			if(CheckInventoryForItem(playerid, CROWBAR_MODEL) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Crowbar to be able to crack safes.");

			if(GetPlayerLastRobbery(playerid) > 0)
			{
				if((gettime() - 300) < GetPlayerLastRobbery(playerid))
				{
					SendClientMessage(playerid, RED, "ERROR: Please wait 5 minutes before doing another robbery.");
					return 0;
				}
			}
			return ShowPlayerDialog(playerid, DRAGONS_SAFE_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Four Dragons Casino Safe", "{FFFFFF}Would you like to start cracking the safe?", "Yes", "No");
		}
		else if(checkpointid == SafeData[caligulas_safe_cp])
		{
			if(GetPlayerJob(playerid) != CIVILIAN_JOB) return SendClientMessage(playerid, ORANGE, "SERVER: You must be a civilian to be able to crack the safe.");
			if(CrackingData[playerid][cracking_evading] == true) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while evading arrest.");
			if(IsPlayerArrested(playerid)) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while you are under arrest.");
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot crack a safe while you are cuffed.");
			if(GetPlayerScore(playerid) < 50) return SendClientMessage(playerid, ORANGE, "SERVER: You need at least 50 score to be able to crack safes.");
			if(SafeData[caligulas_cracking] == true) return SendClientMessage(playerid, ORANGE, "SERVER: This safe is currently being cracked.");
			if((gettime() - SAFE_WAIT_SECS) < SafeData[caligulas_robbed]) return SendClientMessage(playerid, ORANGE, "SERVER: This safe has been cracked recently, come back later.");
			if(CheckInventoryForItem(playerid, CROWBAR_MODEL) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Crowbar to be able to crack safes.");

			if(GetPlayerLastRobbery(playerid) > 0)
			{
				if((gettime() - 300) < GetPlayerLastRobbery(playerid))
				{
					SendClientMessage(playerid, RED, "ERROR: Please wait 5 minutes before doing another robbery.");
					return 0;
				}
			}
			return ShowPlayerDialog(playerid, CALIGULAS_SAFE_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Caligula's Casino Safe", "{FFFFFF}Would you like to start cracking the safe?", "Yes", "No");
		}
	}
	return 1;
}

public OnCalgSafeUpdate()//Do not hook
{
	if(IsValidDynamicObject(SafeData[caligulas_open_obj]))
	{
		DestroyDynamicObject(SafeData[caligulas_open_obj]);
		SafeData[caligulas_closed_obj] = CreateDynamicObject(2332,2144.2000000,1642.7000000,993.0000000,0.0000000,0.0000000,0.0000000, -1, -1, -1, 250.0); //object(kev_safe) (1)
		
		foreach(new i : Player)
		{
			Streamer_UpdateEx(i, 2144.2000000, 1642.7000000, 993.0000000, -1, -1);
		}
	}
	return 1;
}

public OnDragSafeUpdate()//Do not hook
{
	if(IsValidDynamicObject(SafeData[dragons_open_obj]))
	{
		DestroyDynamicObject(SafeData[dragons_open_obj]);
		SafeData[dragons_closed_obj] = CreateDynamicObject(2332,2130.4500000,1600.6000000,1007.8200000,0.0000000,0.0000000,90.0000000, -1, -1, -1, 250.0); //object(kev_safe) (4)
		
		foreach(new i : Player)
		{
			Streamer_UpdateEx(i, 2130.4500000, 1600.6000000, 1007.8200000, -1, -1);
		}
	}
	return 1;
}

public OnPlayerCrackSafe(playerid)//Do not hook
{
	new success = random(SAFE_CRACK_CHANCE);
	if(CrackingData[playerid][cracking_caligulas] == true)
	{
		SafeData[caligulas_cracking] = false;
	}
	else if(CrackingData[playerid][cracking_dragons] == true)
	{
		SafeData[dragons_cracking] = false;
	}

	if(IsPlayerConnected(playerid))
	{
		ClearAnimations(playerid);

		CrackingData[playerid][cracking_caligulas] = false;
		CrackingData[playerid][cracking_dragons] = false;

		if(success == 0)
		{
			SetPlayerWantedLevelEx(playerid, 6);
			return SendClientMessage(playerid, ORANGE, "NOTICE: You have failed to crack the safe.");
		}
		else
		{
			SetPlayerAttachedObject(playerid, 0, 1550, 1, 0.110900, -0.273500, 0.020000, 0.000000, 90.000000, 0.000000, 1.000000, 1.000000, 1.000000);

			new high = (MAX_SAFE_ROBBERY - (MAX_SAFE_ROBBERY / 2)), low = (MAX_SAFE_ROBBERY / 2), take = (random(high) + low);
			CrackingData[playerid][cracking_robbed] = take;

			CrackingData[playerid][cracking_evading] = true;
			CrackingData[playerid][cracking_evade_timer] = SetTimerEx("OnPlayerTakeEarnings", 120000, false, "i", playerid);
				
			SetPlayerWantedLevelEx(playerid, 6);

			SetPlayerStats(playerid, STATS_TYPE_SAFES, GetPlayerStats(playerid, STATS_TYPE_SAFES) + 1);
			SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);

			new string[144];
			format(string, sizeof(string), "NOTICE: You have successfully cracked the safe and bagged $%i!", take);
			SendClientMessage(playerid, YELLOW, string);

			SendClientMessage(playerid, WHITE, "NOTE: You need to evade arrest for 2 minutes to pocket the cash.");
		}
		return 1;
	}
	return 1;
}

public OnPlayerTakeEarnings(playerid)//Do not hook
{
	if(IsPlayerConnected(playerid))
	{
		if(CrackingData[playerid][cracking_evading] == true)
		{
			RemovePlayerAttachedObject(playerid, 0);

			new earnings = CrackingData[playerid][cracking_robbed];
			GivePlayerMoney(playerid, earnings);

			CrackingData[playerid][cracking_robbed] = 0;
			CrackingData[playerid][cracking_evading] = false;
			CrackingData[playerid][cracking_evade_timer] = -1;

			SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully evaded arrest and pocketed the cash.");
		}
	}
	return 1;
}
