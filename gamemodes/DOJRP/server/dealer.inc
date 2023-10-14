#include <YSI_Coding\y_hooks>

enum trap_house_data
{
	trap_ent,
	trap_exit,
	trap_cp
};
new TrapHouseData[trap_house_data];

enum plant_data
{
	plant_id,
	plant_age,
	plant_stage,
	Float:plant_pos[3],
	Text3D:plant_label,
	bool:plant_active
};
new PlantData[MAX_PLAYERS][10][plant_data];

stock GetFreePlantSlot(playerid)
{
	for(new plant = 0; plant < 10; plant++)
	{
		if(PlantData[playerid][plant][plant_active] == false) return plant;
	}
	return -1;
}

stock GetPlantCount(playerid)
{
	new count = 0;
	for(new plant = 0; plant < 10; plant++)
	{
		if(PlantData[playerid][plant][plant_active] == true)
		{
			count++;
		}
	}
	return count;
}

stock IsPlayerInRangeOfPlant(playerid)
{
	foreach(new i : Player)
	{
		for(new plant = 0; plant < 10; plant++)
		{
			if(PlantData[i][plant][plant_active] == true)
			{
				if(IsPlayerInRangeOfPoint(playerid, 2.0, PlantData[i][plant][plant_pos][0], PlantData[i][plant][plant_pos][1], PlantData[i][plant][plant_pos][2])) return 1;
			}
		}
	}
	return 0;
}

stock OnPlayerPlantSeed(playerid)
{
	if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot plant seeds inside interiors.");
	if(GetPlantCount(playerid) >= 10) return SendClientMessage(playerid, RED, "ERROR: You can only have x10 active plants at any given time.");
	if(IsPlayerInRangeOfPlant(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot plant a seed within 2 metres of another plant.");

	new Float:pos[3], plant = GetFreePlantSlot(playerid);
	if(plant == -1) return 1;

	new seeds = CheckInventoryForItem(playerid, SEEDS_MODEL);
	RemoveItemFromInventory(playerid, seeds, 1, false);

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	PlantData[playerid][plant][plant_stage] = 0;
	PlantData[playerid][plant][plant_age] = 0;

	PlantData[playerid][plant][plant_pos][0] = pos[0];
	PlantData[playerid][plant][plant_pos][1] = pos[1];
	PlantData[playerid][plant][plant_pos][2] = pos[2];

	PlantData[playerid][plant][plant_active] = true;

	new label[32];
	format(label, sizeof(label), "%i/100", PlantData[playerid][plant][plant_stage]);
	PlantData[playerid][plant][plant_label] = CreateDynamic3DTextLabel(label, WHITE, pos[0], pos[1], pos[2] - 0.7, 10.0, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 1, -1, -1, -1, 10.0);

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);

	new query[400];
	format(query, sizeof(query), "INSERT INTO `PLANT%i` (`CHARACTER_ID`, `X`, `Y`, `Z`, `STAGE`, `AGE`) VALUES ('%i', '%f', '%f', '%f', '0', '0')", (plant + 1), GetPlayerCharacterID(playerid), pos[0], pos[1], pos[2]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return 1;
}

stock LoadPlantData(playerid)
{
	new query[300];
	for(new i = 0; i < 10; i++)
	{
		format(query, sizeof(query), "SELECT * FROM `PLANT%i` WHERE `CHARACTER_ID` = '%i'", (i + 1), GetPlayerCharacterID(playerid));
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			PlantData[playerid][i][plant_pos][0] = db_get_field_assoc_float(database_result, "X");
			PlantData[playerid][i][plant_pos][1] = db_get_field_assoc_float(database_result, "Y");
			PlantData[playerid][i][plant_pos][2] = db_get_field_assoc_float(database_result, "Z");

			PlantData[playerid][i][plant_stage] = db_get_field_assoc_int(database_result, "STAGE");
			PlantData[playerid][i][plant_age] = db_get_field_assoc_int(database_result, "AGE");

			new label[32];
			format(label, sizeof(label), "%i/100", PlantData[playerid][i][plant_stage]);
			PlantData[playerid][i][plant_label] = CreateDynamic3DTextLabel(label, WHITE, PlantData[playerid][i][plant_pos][0], PlantData[playerid][i][plant_pos][1], PlantData[playerid][i][plant_pos][2] - 0.7, 10.0, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 1, -1, -1, -1, 10.0);

			if(PlantData[playerid][i][plant_stage] >= 75)
			{
				PlantData[playerid][i][plant_id] = CreateDynamicObject(19473, PlantData[playerid][i][plant_pos][0], PlantData[playerid][i][plant_pos][1], PlantData[playerid][i][plant_pos][2] - 1.2, 0.0, 0.0, 0.0, 0, 0, -1, 25.0);
			}

			PlantData[playerid][i][plant_active] = true;
		}
	}
	return 1;
}

stock SavePlantData(playerid)
{
	new query[400];
	for(new i = 0; i < 10; i++)
	{
		if(PlantData[playerid][i][plant_active] == true)
		{
			format(query, sizeof(query), "UPDATE `PLANT%i` SET `STAGE` = '%i', `AGE` = '%i' WHERE `CHARACTER_ID` = '%i'", (i + 1), PlantData[playerid][i][plant_stage], PlantData[playerid][i][plant_age], GetPlayerCharacterID(playerid));
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			PlantData[playerid][i][plant_active] = false;
			PlantData[playerid][i][plant_stage] = 0;
			PlantData[playerid][i][plant_age] = 0;

			DestroyDynamic3DTextLabel(PlantData[playerid][i][plant_label]);
			if(IsValidDynamicObject(PlantData[playerid][i][plant_id])) { DestroyDynamicObject(PlantData[playerid][i][plant_id]); }
		}
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicActor(1, 2451.174072, -1685.742187, 1013.507812, 180.281860, true, 100.0, 0, 2, -1, STREAMER_ACTOR_SD, -1, 0);//Drug Dealer

	TrapHouseData[trap_ent] = CreateDynamicCP(870.403869, -24.924095, 63.985424, 1.0, -1, -1, -1, 5.0, -1, 0);//Trap House Entrance
	TrapHouseData[trap_exit] = CreateDynamicCP(2468.841308, -1698.271362, 1013.507812, 1.0, -1, -1, -1, 5.0, -1, 0);//Trap House Exit
	TrapHouseData[trap_cp] = CreateDynamicCP(2451.179443, -1686.443725, 1013.507812, 1.0, -1, -1, -1, 5.0, -1, 0);//Trap House Checkpoint
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		PlantData[playerid][0][plant_active] = false;
		PlantData[playerid][1][plant_active] = false;
		PlantData[playerid][2][plant_active] = false;
		PlantData[playerid][3][plant_active] = false;
		PlantData[playerid][4][plant_active] = false;
		PlantData[playerid][5][plant_active] = false;
		PlantData[playerid][6][plant_active] = false;
		PlantData[playerid][7][plant_active] = false;
		PlantData[playerid][8][plant_active] = false;
		PlantData[playerid][9][plant_active] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case TRAP_BUY_DIALOG:
		{
			if(response)
			{
				new amount = strval(inputtext);
				if(!IsNumeric(inputtext) || amount < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");

				new cost = (amount * SEEDS_COST);
	            if(GetPlayerMoneyEx(playerid) < cost) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");

	            if(GetPlayerVIP(playerid))
				{
					if((ReturnInventoryWeight(playerid) + ReturnItemWeight(SEEDS_MODEL) * amount) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The seeds are too heavy to fit in your inventory.");
				}
				else
				{
					if((ReturnInventoryWeight(playerid) + ReturnItemWeight(SEEDS_MODEL) * amount) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The seeds are too heavy to fit in your inventory.");
				}

				new slot = CheckInventoryForItem(playerid, SEEDS_MODEL);
				if(slot == 0)
				{
					slot = GetFreeInventorySlot(playerid);
					if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots to store the seeds.");
				}

	            GivePlayerMoney(playerid, -cost);

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				
				AddItemToInventory(playerid, SEEDS_MODEL, amount, false);
				return 1;
			}
			return 1;
		}
		case TRAP_SELL_DIALOG:
		{
			if(response)
			{
				new amount = strval(inputtext), pounds = GetItemCount(playerid, WEED_MODEL);
				if(!IsNumeric(inputtext) || amount < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
				if(pounds < amount) return SendClientMessage(playerid, RED, "ERROR: You don't have that many pounds of weed in your inventory.");
				
				GivePlayerMoney(playerid, (POUNDS_PRICE * amount));

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				new slot = CheckInventoryForItem(playerid, WEED_MODEL);
				RemoveItemFromInventory(playerid, slot, amount, false);

				new string[200];
				format(string, sizeof(string), "NOTICE: You have just sold %i pound(s) of weed for $%i. (Price: $%i Each)", amount, (POUNDS_PRICE * amount), POUNDS_PRICE);
				return SendClientMessage(playerid, YELLOW, string);
			}
			return 1;
		}
		case TRAP_MAIN_DIALOG:
		{
			if(response)
			{
				new string[200];
				format(string, sizeof(string), "{FFFFFF}Ok, how many seeds do you want to buy? (Price: $%i Each)", SEEDS_COST);
				ShowPlayerDialog(playerid, TRAP_BUY_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Drug Dealer > Buy Seeds", string, "Buy", "Cancel");
			}
			else
			{
				new string[200], pounds = GetItemCount(playerid, WEED_MODEL);
				if(pounds == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any pounds of weed in your inventory.");
				format(string, sizeof(string), "{FFFFFF}Ok, how many pounds do you want to sell? (Holding: %i Pounds)", pounds);
				ShowPlayerDialog(playerid, TRAP_SELL_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Drug Dealer > Sell Weed", string, "Sell", "Cancel");
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
		if(checkpointid == TrapHouseData[trap_ent])
		{
			SetPlayerInterior(playerid, 2);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2467.468505, -1698.240966, 1013.507812);
			SetPlayerFacingAngle(playerid, 88.752708);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == TrapHouseData[trap_exit])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 869.884033, -26.096519, 63.894306);
			SetPlayerFacingAngle(playerid, 156.314376);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == TrapHouseData[trap_cp])
		{
			return ShowPlayerDialog(playerid, TRAP_MAIN_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Drug Dealer", "{FFFFFF}Hello, would you like to buy seeds or sell weed?", "Buy", "Sell");
		}
	}
	return 1;
}

task OnWeedUpdate[45000]()
{
	foreach(new i : Player)
	{
		if(IsPlayerLogged(i))
		{
			for(new plant = 0; plant < 10; plant++)
			{
				if(PlantData[i][plant][plant_active] == true)
				{
					if(PlantData[i][plant][plant_stage] < 100)
					{
						PlantData[i][plant][plant_stage]++;

						new label[32];
						format(label, sizeof(label), "%i/100", PlantData[i][plant][plant_stage]);
						UpdateDynamic3DTextLabelText(PlantData[i][plant][plant_label], WHITE, label);

						if(PlantData[i][plant][plant_stage] < 75)
						{
							if(IsValidDynamicObject(PlantData[i][plant][plant_id]))
							{
								DestroyDynamicObject(PlantData[i][plant][plant_id]);
							}
						}
						else if(PlantData[i][plant][plant_stage] >= 75)
						{
							if(!IsValidDynamicObject(PlantData[i][plant][plant_id]))
							{
								PlantData[i][plant][plant_id] = CreateDynamicObject(19473, PlantData[i][plant][plant_pos][0], PlantData[i][plant][plant_pos][1], PlantData[i][plant][plant_pos][2] - 1.2, 0.0, 0.0, 0.0, 0, 0, -1, 25.0);
							}
						}
					}
					else
					{
						new query[200];
						PlantData[i][plant][plant_age]++;
						if(PlantData[i][plant][plant_age] > 50)
						{
							format(query, sizeof(query), "DELETE FROM `PLANT%i` WHERE `CHARACTER_ID` = '%i'", (plant + 1), GetPlayerCharacterID(i));
							database_result = db_query@(server_database, query);
							db_free_result@(database_result);

							PlantData[i][plant][plant_active] = false;
							PlantData[i][plant][plant_stage] = 0;
							PlantData[i][plant][plant_age] = 0;

							DestroyDynamic3DTextLabel(PlantData[i][plant][plant_label]);
							DestroyDynamicObject(PlantData[i][plant][plant_id]);
						}
					}
				}
			}
		}
	}
	return 1;
}

CMD:harvest(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");

	foreach(new i : Player)
	{
		if(IsPlayerLogged(i))
		{
			for(new plant = 0; plant < 10; plant++)
			{
				if(PlantData[i][plant][plant_active] == true)
				{
					if(IsPlayerInRangeOfPoint(playerid, 2.0, PlantData[i][plant][plant_pos][0], PlantData[i][plant][plant_pos][1], PlantData[i][plant][plant_pos][2]))
					{
						if(PlantData[i][plant][plant_stage] < 75) return SendClientMessage(playerid, RED, "ERROR: This plant is too young to harvest at the moment.");
						
						new pounds = 1;
						if(PlantData[i][plant][plant_stage] >= 100) { pounds = 2; }

						if(GetPlayerVIP(playerid))
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(WEED_MODEL)) * pounds > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The weed is too heavy to fit in your inventory.");
						}
						else
						{
							if((ReturnInventoryWeight(playerid) + ReturnItemWeight(WEED_MODEL)) * pounds > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The weed is too heavy to fit in your inventory.");
						}

						new slot = CheckInventoryForItem(playerid, WEED_MODEL);
						if(slot == 0)
						{
							slot = GetFreeInventorySlot(playerid);
							if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots to store the weed.");
						}

						AddItemToInventory(playerid, WEED_MODEL, pounds, false);

						PlantData[i][plant][plant_active] = false;
						PlantData[i][plant][plant_stage] = 0;
						PlantData[i][plant][plant_age] = 0;

						DestroyDynamic3DTextLabel(PlantData[i][plant][plant_label]);
						DestroyDynamicObject(PlantData[i][plant][plant_id]);

						new query[200];
						format(query, sizeof(query), "DELETE FROM `PLANT%i` WHERE `CHARACTER_ID` = '%i'", (plant + 1), GetPlayerCharacterID(i));
						database_result = db_query@(server_database, query);
						db_free_result@(database_result);

						if(playerid != i)
						{
							new string[128];
							if(GetPlantCount(i) == 1)
							{
								format(string, sizeof(string), "NOTICE: Your last weed plant has just been stolen at: %s", ReturnPlayerLocation(playerid));
								SendClientMessage(i, ORANGE, string);
							}
							else
							{
								format(string, sizeof(string), "NOTICE: One of your weed plants has just been stolen at: %s", ReturnPlayerLocation(playerid));
								SendClientMessage(i, ORANGE, string);
							}
						}
						return ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);
					}
				}
			}
		}
	}
	return SendClientMessage(playerid, RED, "ERROR: You are not near any weed plants to harvest.");
}
