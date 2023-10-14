#include <YSI_Coding\y_hooks>

enum store_data
{
	store_mul_ent_cp,
	store_down_ent_cp,
	store_roca_ent_cp,

	store_exit_cp,
	store_counter_cp
};
new StoreData[store_data];

stock ShowStoreDialog(playerid)
{
	return ShowPlayerDialog(playerid, STORE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}24-7 Store", "{FFFFFF}Lotto Ticket: $15\nCell Phone: $1000\nMedikit: $100\nJerrycan: $30\nToolbox: $180\nCrowbar: $50\nTaco: $5\nSprunk: $1", "Buy", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1315.4771, -897.6827, 39.5781, 17, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City 24-7 Store (Mulholland)
	CreateDynamicMapIcon(-1880.7062, 822.4490, 35.1778, 17, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City 24-7 Store (Downtown)
	CreateDynamicMapIcon(2247.6665, 2396.1682, 10.8203, 17, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City 24-7 Store (Roca Escalante)

	StoreData[store_mul_ent_cp] = CreateDynamicCP(1315.4771, -897.6827, 39.5781, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City 24-7 Store (Mulholland)
	StoreData[store_down_ent_cp] = CreateDynamicCP(-1880.7062, 822.4490, 35.1778, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City 24-7 Store (Downtown)
	StoreData[store_roca_ent_cp] = CreateDynamicCP(2247.6665, 2396.1682, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LV City 24-7 Store (Roca Escalante)

	StoreData[store_exit_cp] = CreateDynamicCP(-27.3940, -58.2720, 1003.5469, 1.0, -1, -1, -1, 5.0, -1, 0);//24-7 Store Exit
	StoreData[store_counter_cp] = CreateDynamicCP(-23.3640, -55.6381, 1003.5469, 1.0, -1, -1, -1, 5.0, -1, 0);//24-7 Store Counter
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case STORE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Lotto Ticket: $15
					{
						new amount = GetItemCount(playerid, TICKET_MODEL);
						if(amount > 0) return SendClientMessage(playerid, RED, "ERROR: You can only hold x1 Lotto Ticket at a time.");
						if(GetPlayerMoneyEx(playerid) < 15) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						new slot = CheckInventoryForItem(playerid, TICKET_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, TICKET_MODEL, 1, false);

						GivePlayerMoney(playerid, -15);

						ProcessLottoTicket(playerid);

						return ShowStoreDialog(playerid);
					}
					case 1://Cell Phone: $1000
					{
						if(GetPlayerPhone(playerid)) return SendClientMessage(playerid, RED, "ERROR: You already have a cell phone.");
						if(GetPlayerMoneyEx(playerid) < 1000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						new slot = CheckInventoryForItem(playerid, PHONE_MODEL);
						if(slot != 0) return SendClientMessage(playerid, RED, "ERROR: You already have a cell phone in your inventory.");
						
						slot = GetFreeInventorySlot(playerid);
						if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, PHONE_MODEL, 1, false);

						GivePlayerPhone(playerid);

						GivePlayerMoney(playerid, -1000);

						return ShowStoreDialog(playerid);
					}
					case 2://Medikit: $100
					{
						if(GetPlayerMoneyEx(playerid) < 100) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(MEDIKIT_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(MEDIKIT_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, MEDIKIT_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, MEDIKIT_MODEL, 1, false);

						GivePlayerMoney(playerid, -100);

						return ShowStoreDialog(playerid);
					}
					case 3://Jerrycan: $30
					{
						if(GetPlayerMoneyEx(playerid) < 30) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(JERRYCAN_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(JERRYCAN_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, JERRYCAN_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, JERRYCAN_MODEL, 1, false);

						GivePlayerMoney(playerid, -30);

						return ShowStoreDialog(playerid);
					}
					case 4://Toolbox: $180
					{
						if(GetPlayerMoneyEx(playerid) < 180) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(TOOLBOX_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(TOOLBOX_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, TOOLBOX_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, TOOLBOX_MODEL, 1, false);

						GivePlayerMoney(playerid, -180);

						return ShowStoreDialog(playerid);
					}
					case 5://Crowbar: $50
					{
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(CROWBAR_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(CROWBAR_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, CROWBAR_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, CROWBAR_MODEL, 1, false);

						GivePlayerMoney(playerid, -50);

						return ShowStoreDialog(playerid);
					}
					case 6://Taco: $5
					{
						if(GetPlayerMoneyEx(playerid) < 5) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(TACO_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(TACO_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, TACO_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, TACO_MODEL, 1, false);

						GivePlayerMoney(playerid, -5);

						return ShowStoreDialog(playerid);
					}
					case 7://Sprunk: $1
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

						return ShowStoreDialog(playerid);
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
		if(checkpointid == StoreData[store_mul_ent_cp])//LS City 24-7 Store (Mulholland)
		{
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, -27.3803, -56.9567, 1003.5469);
			SetPlayerFacingAngle(playerid, 359.3671);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == StoreData[store_down_ent_cp])//SF City 24-7 Store (Downtown)
		{
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerPos(playerid, -27.3803, -56.9567, 1003.5469);
			SetPlayerFacingAngle(playerid, 359.3671);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == StoreData[store_roca_ent_cp])//LV City 24-7 Store (Roca Escalante)
		{
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid, 4);
			SetPlayerPos(playerid, -27.3803, -56.9567, 1003.5469);
			SetPlayerFacingAngle(playerid, 359.3671);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == StoreData[store_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 2)//LS City 24-7 Store (Mulholland)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1315.3547, -899.6282, 39.5781);
				SetPlayerFacingAngle(playerid, 177.1103);
				SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//SF City 24-7 Store (Downtown)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -1882.5708, 824.3330, 35.1750);
				SetPlayerFacingAngle(playerid, 41.6001);
				SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 4)//LV City 24-7 Store (Roca Escalante)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2247.7068, 2397.6184, 10.8203);
				SetPlayerFacingAngle(playerid, 358.3683);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == StoreData[store_counter_cp])
		{
			return ShowStoreDialog(playerid);
		}
	}
	return 1;
}
