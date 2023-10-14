#include <YSI_Coding\y_hooks>

enum bar_data
{
	ganton_bar_cp,
	ganton_counter_cp,
	ganton_exit_cp,

	probe_bar_cp,
	probe_counter_cp,
	probe_exit_cp
};
new BarData[bar_data];

stock ShowBarDialog(playerid)
{
	return ShowPlayerDialog(playerid, BAR_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bar Menu", "{FFFFFF}Alcohol: $5\nSprunk: $1", "Buy", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2310.0554, -1643.5039, 14.8270, 49, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Bar (Ganton)
	CreateDynamicMapIcon(-89.6134, 1378.2462, 10.4698, 49, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Bar (Lil' Probe Inn)

	BarData[ganton_bar_cp] = CreateDynamicCP(2310.0554, -1643.5039, 14.8270, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Bar (Ganton)
	BarData[probe_bar_cp] = CreateDynamicCP(-89.6134, 1378.2462, 10.4698, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Country Bar (Lil' Probe Inn)

	BarData[ganton_counter_cp] = CreateDynamicCP(498.0328, -76.0404, 998.7578, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Bar Counter (Ganton)
	BarData[probe_counter_cp] = CreateDynamicCP(-224.7822, 1403.9365, 27.7734, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Country Bar Counter (Lil' Probe Inn)

	BarData[ganton_exit_cp] = CreateDynamicCP(501.9340, -67.5629, 998.7578, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Bar Exit (Ganton)
	BarData[probe_exit_cp] = CreateDynamicCP(-229.2937, 1401.1893, 27.7656, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Country Bar Exit (Lil' Probe Inn)
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case BAR_DIALOG:
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

						return ShowBarDialog(playerid);
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

						return ShowBarDialog(playerid);
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
		if(checkpointid == BarData[ganton_bar_cp])//LS City Bar (Ganton)
		{
			SetPlayerInterior(playerid, 11);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 501.9094, -68.9924, 998.7578);
			SetPlayerFacingAngle(playerid, 179.2375);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BarData[probe_bar_cp])//LV Country Bar (Lil' Probe Inn)
		{
			SetPlayerInterior(playerid, 18);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, -227.9175, 1401.1628, 27.7656);
			SetPlayerFacingAngle(playerid, 268.5385);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BarData[ganton_exit_cp])//LS City Bar (Ganton)
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2310.0117, -1645.2815, 14.8270);
			SetPlayerFacingAngle(playerid, 177.3800);
			SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BarData[probe_exit_cp])//LV Country Bar (Lil' Probe Inn)
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, -87.3199, 1378.6394, 10.2734);
			SetPlayerFacingAngle(playerid, 279.4306);
			SetCameraBehindPlayer(playerid);
			return 1;
		}
		else if(checkpointid == BarData[ganton_counter_cp] || checkpointid == BarData[probe_counter_cp])
		{
			return ShowBarDialog(playerid);
		}
	}
	return 1;
}
