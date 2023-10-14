#include <YSI_Coding\y_hooks>

enum arms_dealer_data
{
	dealer_ent,
	dealer_exit,
	dealer_cp
};
new ArmsDealerData[arms_dealer_data];

enum craft_data
{
	craft_targetid,
	craft_price,
	craft_weaponid,
	craft_materials
};
new CraftData[MAX_PLAYERS][craft_data];

stock ShowMaterialsDialog(playerid)
{
	return ShowPlayerDialog(playerid, SELLTO_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Gun Materials > Sell To", "{FFFFFF}Enter the id of the player you want to craft a gun for:", "Enter", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicActor(73, 414.3972, 2536.8096, 10.0000, 266.3536, true, 100.0, 2, 10, -1, STREAMER_ACTOR_SD, -1, 0);//Arms Dealer

	ArmsDealerData[dealer_ent] = CreateDynamicCP(423.2502, 2536.5022, 16.1484, 1.0, -1, -1, -1, 5.0, -1, 0);//Arms Dealer Entrance
	ArmsDealerData[dealer_exit] = CreateDynamicCP(422.5719, 2536.4778, 10.0000, 1.0, -1, -1, -1, 5.0, -1, 0);//Arms Dealer Exit
	ArmsDealerData[dealer_cp] = CreateDynamicCP(415.0965, 2536.8420, 10.0000, 1.0, -1, -1, -1, 5.0, -1, 0);//Arms Dealer Checkpoint
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DEALER_ASK_DIALOG:
		{
			if(response)
			{
				new string[200];
				format(string, sizeof(string), "{FFFFFF}Okay, how many boxes do you want? (Price: $%i Each)", MATERIALS_COST);
				ShowPlayerDialog(playerid, DEALER_AMOUNT_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Arms Dealer", string, "Buy", "Cancel");
			}
			return 1;
		}
		case DEALER_AMOUNT_DIALOG:
		{
			if(response)
			{
				new amount = strval(inputtext);
	            if(!IsNumeric(inputtext) || amount < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");

	            new cost = (strval(inputtext) * MATERIALS_COST);
	            if(GetPlayerMoneyEx(playerid) < cost) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");

	            if(GetPlayerVIP(playerid))
				{
					if((ReturnInventoryWeight(playerid) + ReturnItemWeight(MATERIALS_MODEL) * amount) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
				}
				else
				{
					if((ReturnInventoryWeight(playerid) + ReturnItemWeight(MATERIALS_MODEL) * amount) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
				}

				new slot = CheckInventoryForItem(playerid, MATERIALS_MODEL);
				if(slot == 0)
				{
					slot = GetFreeInventorySlot(playerid);
					if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
				}

	            GivePlayerMoney(playerid, -cost);

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				
				AddItemToInventory(playerid, MATERIALS_MODEL, amount, false);
			}
			return 1;
		}
		case SELLTO_DIALOG:
		{
			if(response)
			{
				new Float:pos[3], targetid = strval(inputtext);
				if(!IsNumeric(inputtext) || strval(inputtext) < 0) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
				if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
				if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
				if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");

				GetPlayerPos(targetid, pos[0], pos[1], pos[2]);
				if(!IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You need to be within 5 metres of the player to craft a weapon for them.");
				
				CraftData[playerid][craft_targetid] = targetid;
				CraftData[targetid][craft_targetid] = playerid;

				ShowPlayerDialog(playerid, SELLGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Gun Materials > Craft Gun", "{FFFFFF}Craft: Desert Eagle (x2 Gun Materials)\nCraft: Combat Shotgun (x3 Gun Materials)\nCraft: MP5 (x3 Gun Materials)\nCraft: M4 (x4 Gun Materials)\nCraft: Sniper Rifle (x4 Gun Materials)", "Craft", "Cancel");
			}
			return 1;
		}
		case SELLVERIFY_DIALOG:
		{
			if(response)
			{
				new string[200], name[24], price = CraftData[playerid][craft_price], weaponid = CraftData[playerid][craft_weaponid], sellerid = CraftData[playerid][craft_targetid];
				if(!IsPlayerConnected(sellerid) || CraftData[sellerid][craft_targetid] == INVALID_PLAYER_ID) return SendClientMessage(playerid, RED, "ERROR: The player has recently disconnected.");
				if(GetPlayerMoneyEx(playerid) < price) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");
				
				GivePlayerMoney(playerid, -price);
				if(playerid != sellerid)
				{
					GivePlayerMoney(sellerid, price);
				}

				GivePlayerWeapon(playerid, weaponid, 100);

				new mats = CraftData[sellerid][craft_materials], slot = CheckInventoryForItem(sellerid, MATERIALS_MODEL);
				RemoveItemFromInventory(sellerid, slot, mats, false);

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				ApplyAnimation(sellerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				GetPlayerName(sellerid, name, sizeof(name));
				format(string, sizeof(string), "NOTICE: You have accepted %s's offer and handed them $%i.", name, price);
				SendClientMessage(playerid, YELLOW, string);
				
				if(playerid != sellerid)
				{
					GetPlayerName(playerid, name, sizeof(name));
					format(string, sizeof(string), "NOTICE: %s has accepted your offer and handed you $%i.", name, price);
					SendClientMessage(sellerid, YELLOW, string);
				}
				return 1;
			}
			else
			{
				new string[200], name[24], sellerid = CraftData[playerid][craft_targetid];

				GetPlayerName(playerid, name, sizeof(name));
				format(string, sizeof(string), "NOTICE: %s has just rejected your offer.", name);
				SendClientMessage(sellerid, ORANGE, string);

				GetPlayerName(sellerid, name, sizeof(name));
				format(string, sizeof(string), "NOTICE: You have just rejected %s's offer.", name);
				SendClientMessage(playerid, ORANGE, string);
			}
			return 1;
		}
		case SELLFOR_DIALOG:
		{
			if(response)
			{
				if(!IsNumeric(inputtext) || strval(inputtext) < 0) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");

				new string[200], name[24], weapon[32], targetid = CraftData[playerid][craft_targetid], weaponid = CraftData[playerid][craft_weaponid], price = strval(inputtext);
				CraftData[targetid][craft_price] = price;

				GetWeaponName(weaponid, weapon, sizeof(weapon));

				GetPlayerName(playerid, name, sizeof(name));
				format(string, sizeof(string), "{FFFFFF}%s has offered you a %s for $%i, do you accept?", name, weapon, price);
				ShowPlayerDialog(targetid, SELLVERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Gun Offer", string, "Yes", "No");

				GetPlayerName(targetid, name, sizeof(name));
				format(string, sizeof(string), "NOTICE: You have offered %s a %s for $%i, wait for their reponse.", name, weapon, price);
				SendClientMessage(playerid, YELLOW, string);
			}
			return 1;
		}
		case SELLGUN_DIALOG:
		{
			if(response)
			{
				new string[200], weapon[32], name[24], targetid = CraftData[playerid][craft_targetid];
				switch(listitem)
				{
					case 0://Desert Eagle
					{
						if(GetItemCount(playerid, MATERIALS_MODEL) < 2) return SendClientMessage(playerid, RED, "ERROR: You don't have enough gun materials to craft this weapon.");
						CraftData[targetid][craft_weaponid] = 24;
						CraftData[playerid][craft_materials] = 2;
					}
					case 1://Combat Shotgun
					{
						if(GetItemCount(playerid, MATERIALS_MODEL) < 3) return SendClientMessage(playerid, RED, "ERROR: You don't have enough gun materials to craft this weapon.");
						CraftData[targetid][craft_weaponid] = 27;
						CraftData[playerid][craft_materials] = 3;
					}
					case 2://MP5
					{
						if(GetItemCount(playerid, MATERIALS_MODEL) < 3) return SendClientMessage(playerid, RED, "ERROR: You don't have enough gun materials to craft this weapon.");
						CraftData[targetid][craft_weaponid] = 29;
						CraftData[playerid][craft_materials] = 3;
					}
					case 3://M4
					{
						if(GetItemCount(playerid, MATERIALS_MODEL) < 4) return SendClientMessage(playerid, RED, "ERROR: You don't have enough gun materials to craft this weapon.");
						CraftData[targetid][craft_weaponid] = 31;
						CraftData[playerid][craft_materials] = 4;
					}
					case 4://Sniper Rifle
					{
						if(GetItemCount(playerid, MATERIALS_MODEL) < 4) return SendClientMessage(playerid, RED, "ERROR: You don't have enough gun materials to craft this weapon.");
						CraftData[targetid][craft_weaponid] = 34;
						CraftData[playerid][craft_materials] = 4;
					}
				}

				GetWeaponName(CraftData[targetid][craft_weaponid], weapon, sizeof(weapon));

				GetPlayerName(targetid, name, sizeof(name));
				format(string, sizeof(string), "{FFFFFF}How much would you like to sell the %s to %s for?", weapon, name);
				ShowPlayerDialog(playerid, SELLFOR_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Gun Materials > Sell For", string, "Enter", "Cancel");
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
		if(checkpointid == ArmsDealerData[dealer_ent])
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 421.0563, 2536.4792, 10.0000);
			SetPlayerFacingAngle(playerid, 90.0000);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == ArmsDealerData[dealer_exit])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 424.6588, 2536.5259, 16.1484);
			SetPlayerFacingAngle(playerid, 268.9328);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == ArmsDealerData[dealer_cp])
		{
			return ShowPlayerDialog(playerid, DEALER_ASK_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Arms Dealer", "{FFFFFF}Hello, do you want to buy some gun materials?", "Yes", "No");
		}
	}
	return 1;
}
