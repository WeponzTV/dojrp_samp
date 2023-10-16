#include <YSI_Coding\y_hooks>

enum restaurant_data
{
	temple_burger_cp,
	garcia_burger_cp,
	juniper_burger_cp,
	redsands_burger_cp,
	whitewood_burger_cp,

	angel_cluck_cp,
	bone_cluck_cp,
	tierra_cluck_cp,

	idle_pizza_cp,
	palomino_pizza_cp,
	mont_pizza_cp,
	
	burger_counter_cp,
	burger_exit_cp,

	cluck_counter_cp,
	cluck_exit_cp,

	pizza_counter_cp,
	pizza_exit_cp
};
new RestaurantData[restaurant_data];

stock ShowBurgerDialog(playerid)
{
	return ShowPlayerDialog(playerid, BURGER_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Burger Shot", "{FFFFFF}Burger: $5\nSprunk: $1", "Buy", "Cancel");
}

stock ShowCluckDialog(playerid)
{
	return ShowPlayerDialog(playerid, CLUCK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Cluckin' Bell", "{FFFFFF}Taco: $3\nSprunk: $1", "Buy", "Cancel");
}

stock ShowPizzaDialog(playerid)
{
	return ShowPlayerDialog(playerid, PIZZA_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}The Well Stacked Pizza Co.", "{FFFFFF}Pizza: $7\nSprunk: $1", "Buy", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1199.2576, -918.1426, 43.1232, 10, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Burger Shot (Temple)
	CreateDynamicMapIcon(-2336.8679, -166.8378, 35.5547, 10, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City Burger Shot (Garcia)
	CreateDynamicMapIcon(-2355.8169, 1008.1158, 50.8984, 10, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City Burger Shot (Juniper Hollow)
	CreateDynamicMapIcon(1872.2581, 2071.8367, 11.0625, 10, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City Burger Shot (Redsands East)
	CreateDynamicMapIcon(1157.9177, 2072.2339, 11.0625, 10, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City Burger Shot (Whitewood Estates)

	CreateDynamicMapIcon(-2155.3225, -2460.1731, 30.8516, 14, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Country Cluckin' Bell (Angel Pine)
	CreateDynamicMapIcon(172.9798, 1177.1833, 14.7578, 14, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Cluckin' Bell (Bone County)
	CreateDynamicMapIcon(-1213.8129, 1830.3478, 41.9297, 14, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Cluckin' Bell (Tierra Robada)

	CreateDynamicMapIcon(2105.4875, -1806.4839, 13.5547, 29, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Well Stacked (Idlewood)
	CreateDynamicMapIcon(2331.8096, 75.0378, 26.6210, 29, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Country Well Stacked (Palomino Creek)
	CreateDynamicMapIcon(1367.5314, 248.3644, 19.5669, 29, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Country Well Stacked (Montgomery)

	RestaurantData[temple_burger_cp] = CreateDynamicCP(1199.2576, -918.1426, 43.1232, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Burger Shot (Temple)
	RestaurantData[garcia_burger_cp] = CreateDynamicCP(-2336.8679, -166.8378, 35.5547, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City Burger Shot (Garcia)
	RestaurantData[juniper_burger_cp] = CreateDynamicCP(-2355.8169, 1008.1158, 50.8984, 1.0, -1, -1, -1, 5.0, -1, 0);//SF City Burger Shot (Juniper Hollow)
	RestaurantData[redsands_burger_cp] = CreateDynamicCP(1872.2581, 2071.8367, 11.0625, 1.0, -1, -1, -1, 5.0, -1, 0);//LV City Burger Shot (Redsands East)
	RestaurantData[whitewood_burger_cp] = CreateDynamicCP(1157.9177, 2072.2339, 11.0625, 1.0, -1, -1, -1, 5.0, -1, 0);//LV City Burger Shot (Whitewood Estates)

	RestaurantData[angel_cluck_cp] = CreateDynamicCP(-2155.3225, -2460.1731, 30.8516, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Country Cluckin' Bell (Angel Pine)
	RestaurantData[bone_cluck_cp] = CreateDynamicCP(172.9798, 1177.1833, 14.7578, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Country Cluckin' Bell (Bone County)
	RestaurantData[tierra_cluck_cp] = CreateDynamicCP(-1213.8129, 1830.3478, 41.9297, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Country Cluckin' Bell (Tierra Robada)

	RestaurantData[idle_pizza_cp] = CreateDynamicCP(2105.4875, -1806.4839, 13.5547, 1.0, -1, -1, -1, 5.0, -1, 0);//LS City Well Stacked (Idlewood)
	RestaurantData[palomino_pizza_cp] = CreateDynamicCP(2331.8096, 75.0378, 26.6210, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Country Well Stacked (Palomino Creek)
	RestaurantData[mont_pizza_cp] = CreateDynamicCP(1367.5314, 248.3644, 19.5669, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Country Well Stacked (Montgomery)

	RestaurantData[burger_counter_cp] = CreateDynamicCP(376.5110, -67.4347, 1001.5078, 1.0, -1, -1, -1, 5.0, -1, 0);//Burger Shot Counter
	RestaurantData[burger_exit_cp] = CreateDynamicCP(362.8742, -75.1701, 1001.5078, 1.0, -1, -1, -1, 5.0, -1, 0);//Burger Shot Exit

	RestaurantData[cluck_counter_cp] = CreateDynamicCP(368.1016, -6.0170, 1001.8516, 1.0, -1, -1, -1, 5.0, -1, 0);//Cluckin' Bell Counter
	RestaurantData[cluck_exit_cp] = CreateDynamicCP(364.8949, -11.7618, 1001.8516, 1.0, -1, -1, -1, 5.0, -1, 0);//Cluckin' Bell Exit

	RestaurantData[pizza_counter_cp] = CreateDynamicCP(374.7158, -118.8025, 1001.4995, 1.0, -1, -1, -1, 5.0, -1, 0);//Well Stacked Counter
	RestaurantData[pizza_exit_cp] = CreateDynamicCP(372.3575, -133.5244, 1001.4922, 1.0, -1, -1, -1, 5.0, -1, 0);//Well Stacked Exit
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case PIZZA_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Pizza: $7
					{
						if(GetPlayerMoneyEx(playerid) < 7) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(PIZZA_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(PIZZA_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, PIZZA_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, PIZZA_MODEL, 1, false);

						GivePlayerMoney(playerid, -7);

						return ShowPizzaDialog(playerid);
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

						return ShowPizzaDialog(playerid);
					}
				}
			}
			return 1;
		}
		case CLUCK_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Taco: $3
					{
						if(GetPlayerMoneyEx(playerid) < 3) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

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

						GivePlayerMoney(playerid, -3);

						return ShowCluckDialog(playerid);
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

						return ShowCluckDialog(playerid);
					}
				}
			}
			return 1;
		}
		case BURGER_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Burger: $5
					{
						if(GetPlayerMoneyEx(playerid) < 5) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(BURGER_MODEL)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(BURGER_MODEL)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, BURGER_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
						}

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						AddItemToInventory(playerid, BURGER_MODEL, 1, false);

						GivePlayerMoney(playerid, -5);

						return ShowBurgerDialog(playerid);
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

						return ShowBurgerDialog(playerid);
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
		if(checkpointid == RestaurantData[idle_pizza_cp])//LS City Well Stacked (Idlewood)
		{
			SetPlayerInterior(playerid, 5);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 372.3555, -131.9322, 1001.4922);
			SetPlayerFacingAngle(playerid, 358.9020);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[palomino_pizza_cp])//LS Country Well Stacked (Palomino Creek)
		{
			SetPlayerInterior(playerid, 5);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 372.3555, -131.9322, 1001.4922);
			SetPlayerFacingAngle(playerid, 358.9020);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[mont_pizza_cp])//LS Country Well Stacked (Montgomery)
		{
			SetPlayerInterior(playerid, 5);
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerPos(playerid, 372.3555, -131.9322, 1001.4922);
			SetPlayerFacingAngle(playerid, 358.9020);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[pizza_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS City Well Stacked (Idlewood)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2103.5935, -1806.4716, 13.5547);
				SetPlayerFacingAngle(playerid, 90.2619);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//LS Country Well Stacked (Palomino Creek)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2333.7256, 75.0266, 26.6210);
				SetPlayerFacingAngle(playerid, 269.7739);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//LS Country Well Stacked (Montgomery)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1365.7317, 249.1301, 19.5669);
				SetPlayerFacingAngle(playerid, 68.7962);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == RestaurantData[pizza_counter_cp])
		{
			return ShowPizzaDialog(playerid);
		}
		else if(checkpointid == RestaurantData[angel_cluck_cp])//SF Country Cluckin' Bell (Angel Pine)
		{
			SetPlayerInterior(playerid, 9);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 364.9673, -10.4878, 1001.8516);
			SetPlayerFacingAngle(playerid, 357.5923);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[bone_cluck_cp])//LV Country Cluckin' Bell (Bone County)
		{
			SetPlayerInterior(playerid, 9);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 364.9673, -10.4878, 1001.8516);
			SetPlayerFacingAngle(playerid, 357.5923);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[tierra_cluck_cp])//LV Country Cluckin' Bell (Tierra Robada)
		{
			SetPlayerInterior(playerid, 9);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 364.9673, -10.4878, 1001.8516);
			SetPlayerFacingAngle(playerid, 357.5923);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[cluck_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 0)//SF Country Cluckin' Bell (Angel Pine)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -2153.7976, -2461.4563, 30.8516);
				SetPlayerFacingAngle(playerid, 230.1178);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 1)//LV Country Cluckin' Bell (Bone County)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 171.9923, 1175.7528, 14.7645);
				SetPlayerFacingAngle(playerid, 163.6057);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//LV Country Cluckin' Bell (Tierra Robada)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -1212.5507, 1831.5690, 41.9297);
				SetPlayerFacingAngle(playerid, 314.1778);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == RestaurantData[cluck_counter_cp])
		{
			return ShowCluckDialog(playerid);
		}
		else if(checkpointid == RestaurantData[temple_burger_cp])//LS City Burger Shot (Temple)
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerPos(playerid, 364.1770, -74.0263, 1001.5078);
			SetPlayerFacingAngle(playerid, 311.1857);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[garcia_burger_cp])//SF City Burger Shot (Garcia)
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 4);
			SetPlayerPos(playerid, 364.1770, -74.0263, 1001.5078);
			SetPlayerFacingAngle(playerid, 311.1857);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[juniper_burger_cp])//SF City Burger Shot (Juniper Hollow)
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 5);
			SetPlayerPos(playerid, 364.1770, -74.0263, 1001.5078);
			SetPlayerFacingAngle(playerid, 311.1857);
			SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == RestaurantData[redsands_burger_cp])//LV City Burger Shot (Redsands East)
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 6);
			SetPlayerPos(playerid, 364.1770, -74.0263, 1001.5078);
			SetPlayerFacingAngle(playerid, 311.1857);
			SetCameraBehindPlayer(playerid);
			return 1;
		}
		else if(checkpointid == RestaurantData[whitewood_burger_cp])//LV City Burger Shot (Whitewood Estates)
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 7);
			SetPlayerPos(playerid, 364.1770, -74.0263, 1001.5078);
			SetPlayerFacingAngle(playerid, 311.1857);
			SetCameraBehindPlayer(playerid);
			return 1;
		}
		else if(checkpointid == RestaurantData[burger_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 3)//LS City Burger Shot (Temple)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1199.4580, -919.9054, 43.1086);
				SetPlayerFacingAngle(playerid, 189.9887);
				SetCameraBehindPlayer(playerid);
				return 1;
			}
			else if(GetPlayerVirtualWorld(playerid) == 4)//SF City Burger Shot (Garcia)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -2334.6248, -166.8671, 35.5547);
				SetPlayerFacingAngle(playerid, 270.0114);
				SetCameraBehindPlayer(playerid);
				return 1;
			}
			else if(GetPlayerVirtualWorld(playerid) == 5)//SF City Burger Shot (Juniper Hollow)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -2357.4595, 1008.1487, 50.8984);
				SetPlayerFacingAngle(playerid, 87.3525);
				SetCameraBehindPlayer(playerid);
				return 1;
			}
			else if(GetPlayerVirtualWorld(playerid) == 6)//LV City Burger Shot (Redsands East)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1874.1664, 2071.8208, 11.0625);
				SetPlayerFacingAngle(playerid, 271.6162);
				SetCameraBehindPlayer(playerid);
				return 1;
			}
			else if(GetPlayerVirtualWorld(playerid) == 7)//LV City Burger Shot (Whitewood Estates)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1159.6353, 2072.1956, 11.0625);
				SetPlayerFacingAngle(playerid, 271.4557);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == RestaurantData[burger_counter_cp])
		{
			return ShowBurgerDialog(playerid);
		}
	}
	return 1;
}
