#include <YSI_Coding\y_hooks>

enum club_data
{
	idle_club_cp,
	idle_counter_cp,
	idle_exit_cp,

	battery_club_cp,
	battery_counter_cp,
	battery_exit_cp
};
new ClubData[club_data];

stock ShowClubDialog(playerid)
{
	return ShowPlayerDialog(playerid, CLUB_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Club Menu", "{FFFFFF}Alcohol: $5\nSprunk: $1", "Buy", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1836.9934, -1682.4458, 13.3247, 48, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Club (Idlewood)
	CreateDynamicMapIcon(-2624.6968, 1412.7223, 7.0938, 48, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City Club (Battery Point)

	ClubData[idle_club_cp] = CreateDynamicCP(1836.9934, -1682.4458, 13.3247, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Club (Idlewood)
	ClubData[battery_club_cp] = CreateDynamicCP(-2624.6968, 1412.7223, 7.0938, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City Club (Battery Point)

	ClubData[idle_counter_cp] = CreateDynamicCP(499.9702, -20.4441, 1000.6797, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Club (Idlewood)
	ClubData[battery_counter_cp] = CreateDynamicCP(-2654.0144, 1407.5364, 906.2734, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City Club (Battery Point)

	ClubData[idle_exit_cp] = CreateDynamicCP(493.3211, -24.8202, 1000.6797, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Club (Idlewood)
	ClubData[battery_exit_cp] = CreateDynamicCP(-2636.6877, 1402.4630, 906.4609, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City Club (Battery Point)
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case CLUB_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Alcohol: $5
					{
						if(GetPlayerMoneyEx(playerid) < 5) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(ALCOHOL_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(ALCOHOL_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, ALCOHOL_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, ALCOHOL_MODEL, 1, false);

						GivePlayerMoney(playerid, -5);

						return ShowClubDialog(playerid);
					}
					case 1://Sprunk: $1
					{
						if(GetPlayerMoneyEx(playerid) < 1) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(SPRUNK_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(SPRUNK_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, SPRUNK_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, SPRUNK_MODEL, 1, false);

						GivePlayerMoney(playerid, -1);

						return ShowClubDialog(playerid);
					}
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
		if(checkpointid == ClubData[idle_club_cp])//LS City Club (Idlewood)
		{
			SetPlayerInterior(playerid, 17);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 493.3540, -22.9894, 1000.6797);
			SetPlayerFacingAngle(playerid, 359.4624);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == ClubData[battery_club_cp])//SF City Club (Battery Point)
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 7);
			SetPlayerPos(playerid, -2636.6570, 1404.2460, 906.4609);
			SetPlayerFacingAngle(playerid, 358.9809);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == ClubData[idle_exit_cp])//LS City Club (Idlewood)
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 1835.2395, -1682.4131, 13.3980);
			SetPlayerFacingAngle(playerid, 89.5166);
			SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == ClubData[battery_exit_cp])//SF City Club (Battery Point)
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, -2623.9082, 1410.3813, 7.0938);
			SetPlayerFacingAngle(playerid, 198.9750);
			SetCameraBehindPlayer(playerid);
			return 1;
		}
		else if(checkpointid == ClubData[idle_counter_cp] || checkpointid == ClubData[battery_counter_cp])
		{
			return ShowClubDialog(playerid);
		}
	}
	return 1;
}
