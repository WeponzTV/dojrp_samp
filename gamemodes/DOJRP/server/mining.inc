#include <YSI_Coding\y_hooks>

forward OnOreRenew(oreid);

new Float:MiningOre[10][3] =
{
	{618.320373, 867.055297, -42.960937},
	{623.212890, 870.000305, -42.953437},
	{618.770935, 872.831542, -42.960937},
	{621.581237, 877.929626, -42.953437},
	{628.428283, 876.679260, -42.953437},
	{631.711120, 881.749328, -42.960937},
	{629.669494, 886.847595, -42.960937},
	{636.425476, 887.240600, -42.960937},
	{634.598144, 893.037292, -42.960937},
	{641.372375, 892.955749, -42.953437}
};

enum quarry_data
{
	quarry_office_pickup,
	quarry_office_cp,
	quarry_unload_cp
};
new QuarryData[quarry_data];

enum minerals_data
{
	minerals_id,
	minerals_stone,
	minerals_gold,
	minerals_diamonds,
	bool:minerals_mining
};
new MineralsData[MAX_PLAYERS][minerals_data];

enum ore_data
{
	ore_id,
	ore_type,
	ore_area,
	Float:ore_pos[3],
	Float:ore_hp,
	Text3D:ore_label,
	bool:ore_active
};
new OreData[sizeof(MiningOre)][ore_data];

stock SaveMineralsData(playerid)
{
	new query[400], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `MINERALS` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `MINERALS` SET `STONE` = '%i', `GOLD` = '%i', `DIAMONDS` = '%i' WHERE `CHARACTER_ID` = '%i'", MineralsData[playerid][minerals_stone], MineralsData[playerid][minerals_gold], MineralsData[playerid][minerals_diamonds], id);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `MINERALS` (`CHARACTER_ID`, `STONE`, `GOLD`, `DIAMONDS`) VALUES ('%i', '%i', '%i', '%i')", id, MineralsData[playerid][minerals_stone], MineralsData[playerid][minerals_gold], MineralsData[playerid][minerals_diamonds]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	return 1;
}

stock LoadMineralsData(playerid)
{
	new query[200];
	format(query, sizeof(query), "SELECT * FROM `MINERALS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		MineralsData[playerid][minerals_stone] = db_get_field_assoc_int(database_result, "STONE");
		MineralsData[playerid][minerals_gold] = db_get_field_assoc_int(database_result, "GOLD");
		MineralsData[playerid][minerals_diamonds] = db_get_field_assoc_int(database_result, "DIAMONDS");
	}
	db_free_result@(database_result);
	return 1;
}

stock ShowQuarryOfficeDialog(playerid)
{
	new string[200], job = GetPlayerJob(playerid);
	if(job == CIVILIAN_JOB)
	{
		if(GetPlayerDegree(playerid, DEGREE_MINING) == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Mining Degree to clock-on as a miner.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a miner while you are wanted.");
		return ShowPlayerDialog(playerid, QUARRY_OFFICE_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Quarry Office", "{FFFFFF}Would you like to clock-on as a miner?", "Yes", "No");
	}
	else if(job == MINER_JOB)
	{
		return ShowPlayerDialog(playerid, QUARRY_OFFICE_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Quarry Office", "{FFFFFF}Would you like to clock-off as a miner?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a miner while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowQuarryUnloadDialog(playerid)
{
	new string[400];
	format(string, sizeof(string), "{FFFFFF}Stone (Holding: %i/100 Grams)\nGold (Holding: %i/100 Grams)\nDiamonds (Holding: %i/100 Grams)", MineralsData[playerid][minerals_stone], MineralsData[playerid][minerals_gold], MineralsData[playerid][minerals_diamonds]);
	return ShowPlayerDialog(playerid, QUARRY_UNLOAD_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Quarry Unload Point", string, "Unload", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(816.675476, 856.724426, 12.789062, 11, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Quarry (Office)

	QuarryData[quarry_office_pickup] = CreateDynamicPickup(1239, 1, 816.675476, 856.724426, 12.789062, -1, -1, -1, 50.0, -1, 0);//Quarry (Office)
	QuarryData[quarry_office_cp] = CreateDynamicCP(816.675476, 856.724426, 12.789062, 1.0, -1, -1, -1, 5.0, -1, 0);//Quarry (Office)

	QuarryData[quarry_unload_cp] = CreateDynamicCP(618.519348, 891.151855, -37.128540, 1.0, -1, -1, -1, 50.0, -1, 0);//Quarry (Unload)

	for(new o = 0; o < sizeof(MiningOre); o++)
	{
		OreData[o][ore_pos][0] = MiningOre[o][0];
		OreData[o][ore_pos][1] = MiningOre[o][1];
		OreData[o][ore_pos][2] = MiningOre[o][2];

		OreData[o][ore_hp] = 1000.0;

		new type = random(3), label[32];
		if(type == ORE_TYPE_STONE)
		{
			OreData[o][ore_type] = ORE_TYPE_STONE;

			format(label, sizeof(label), "%0.0f/1000", OreData[o][ore_hp]);

			OreData[o][ore_id] = CreateDynamicObject(3931, OreData[o][ore_pos][0], OreData[o][ore_pos][1], OreData[o][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
			SetDynamicObjectMaterial(OreData[o][ore_id], 0, 18202, "w_towncs_t", "hatwall256hi", 0xFFFFFFFF);//Credits: Amagida
		}
		else if(type == ORE_TYPE_GOLD)
		{
			OreData[o][ore_type] = ORE_TYPE_GOLD;

			format(label, sizeof(label), "%0.0f/1000", OreData[o][ore_hp]);

			OreData[o][ore_id] = CreateDynamicObject(3931, OreData[o][ore_pos][0], OreData[o][ore_pos][1], OreData[o][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
			SetDynamicObjectMaterial(OreData[o][ore_id], 0, 8463, "vgseland", "tiadbuddhagold", 0xFFFFFFFF);//Credits: Amagida
		}
		else if(type == ORE_TYPE_DIAMOND)
		{
			OreData[o][ore_type] = ORE_TYPE_DIAMOND;

			format(label, sizeof(label), "%0.0f/1000", OreData[o][ore_hp]);

			OreData[o][ore_id] = CreateDynamicObject(3931, OreData[o][ore_pos][0], OreData[o][ore_pos][1], OreData[o][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
			SetDynamicObjectMaterial(OreData[o][ore_id], 0, 5154, "dkcargoshp_las2", "Diamondp64", 0xFFFFFFFF);//Credits: Amagida
		}

		OreData[o][ore_label] = CreateDynamic3DTextLabel(label, WHITE, OreData[o][ore_pos][0], OreData[o][ore_pos][1], OreData[o][ore_pos][2] - 0.3, 10.0, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 0, -1, -1, -1, 10.0);
		OreData[o][ore_area] = CreateDynamicSphere(OreData[o][ore_pos][0], OreData[o][ore_pos][1], OreData[o][ore_pos][2], 1.5, -1, -1, -1, 0);

		OreData[o][ore_active] = true;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		MineralsData[playerid][minerals_id] = -1;
		MineralsData[playerid][minerals_stone] = 0;
		MineralsData[playerid][minerals_gold] = 0;
		MineralsData[playerid][minerals_diamonds] = 0;

		MineralsData[playerid][minerals_mining] = false;
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE) && MineralsData[playerid][minerals_mining] == true)
	{
		new id = MineralsData[playerid][minerals_id];
		if(OreData[id][ore_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, OreData[id][ore_pos][0], OreData[id][ore_pos][1], OreData[id][ore_pos][2]))
			{
				new label[32];
				if(OreData[id][ore_type] == ORE_TYPE_STONE)
				{
					if(MineralsData[playerid][minerals_stone] >= 100) return SendClientMessage(playerid, RED, "ERROR: You can only hold up to 100 grams of stone at a time, unload it first.");

					OreData[id][ore_hp] = (OreData[id][ore_hp] - 1.0);

					format(label, sizeof(label), "%0.0f/1000", OreData[id][ore_hp]);

					MineralsData[playerid][minerals_stone]++;
				}
				else if(OreData[id][ore_type] == ORE_TYPE_GOLD)
				{
					if(MineralsData[playerid][minerals_gold] >= 100) return SendClientMessage(playerid, RED, "ERROR: You can only hold up to 100 grams of gold at a time, unload it first.");

					OreData[id][ore_hp] = (OreData[id][ore_hp] - 1.0);

					format(label, sizeof(label), "%0.0f/1000", OreData[id][ore_hp]);

					MineralsData[playerid][minerals_gold]++;
				}
				else if(OreData[id][ore_type] == ORE_TYPE_DIAMOND)
				{
					if(MineralsData[playerid][minerals_diamonds] >= 100) return SendClientMessage(playerid, RED, "ERROR: You can only hold up to 100 grams of diamonds at a time, unload it first.");

					OreData[id][ore_hp] = (OreData[id][ore_hp] - 1.0);

					format(label, sizeof(label), "%0.0f/1000", OreData[id][ore_hp]);

					MineralsData[playerid][minerals_diamonds]++;
				}

				UpdateDynamic3DTextLabelText(OreData[id][ore_label], WHITE, label);

				if(OreData[id][ore_hp] <= 0.0)
				{
					OreData[id][ore_active] = false;

					DestroyDynamicObject(OreData[id][ore_id]);
					DestroyDynamic3DTextLabel(OreData[id][ore_label]);
					DestroyDynamicArea(OreData[id][ore_area]);

					SetTimerEx("OnOreRenew", 600000, false, "i", id);
				}

				return ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 0, 0, 0, 0, 0, 0);
			}
		}
		return 1;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case QUARRY_OFFICE_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_MINER, true);
		    		ShowWorkerSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a worker skin to clock-on as a miner.");
		    	}
		    	else if(job == MINER_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a miner.");
		    	}
		    }
		    return 1;
		}
		case QUARRY_UNLOAD_DIALOG:
		{
		    if(response)
		    {
		    	switch(listitem)
		    	{
		    		case 0://Stone
		    		{
		    			if(MineralsData[playerid][minerals_stone] < 1) return SendClientMessage(playerid, RED, "ERROR: You don't have any stone to unload, go and mine some first.");

		    			new string[128], earnings = (MineralsData[playerid][minerals_stone] * STONE_ORE_PRICE), amount = MineralsData[playerid][minerals_stone];

		    			MineralsData[playerid][minerals_stone] = 0;

		    			GivePlayerMoney(playerid, earnings);

		    			ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    			
		    			format(string, sizeof(string), "NOTICE: You have unloaded %i grams of stone and received: $%i (Price: $%i/Gram)", amount, earnings, STONE_ORE_PRICE);
		    			SendClientMessage(playerid, YELLOW, string);

		    			return ShowQuarryUnloadDialog(playerid);
		    		}
		    		case 1://Gold
		    		{
		    			if(MineralsData[playerid][minerals_gold] < 1) return SendClientMessage(playerid, RED, "ERROR: You don't have any gold to unload, go and mine some first.");

		    			new string[128], earnings = (MineralsData[playerid][minerals_gold] * GOLD_ORE_PRICE), amount = MineralsData[playerid][minerals_gold];

		    			MineralsData[playerid][minerals_gold] = 0;

		    			GivePlayerMoney(playerid, earnings);

		    			ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    			
		    			format(string, sizeof(string), "NOTICE: You have unloaded %i grams of gold and received: $%i (Price: $%i/Gram)", amount, earnings, GOLD_ORE_PRICE);
		    			SendClientMessage(playerid, YELLOW, string);

		    			return ShowQuarryUnloadDialog(playerid);
		    		}
		    		case 2://Diamonds
		    		{
		    			if(MineralsData[playerid][minerals_diamonds] < 1) return SendClientMessage(playerid, RED, "ERROR: You don't have any diamonds to unload, go and mine some first.");

		    			new string[128], earnings = (MineralsData[playerid][minerals_diamonds] * DIAMONDS_ORE_PRICE), amount = MineralsData[playerid][minerals_diamonds];

		    			MineralsData[playerid][minerals_diamonds] = 0;

		    			GivePlayerMoney(playerid, earnings);

		    			ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    			
		    			format(string, sizeof(string), "NOTICE: You have unloaded %i grams of diamonds and received: $%i (Price: $%i/Gram)", amount, earnings, DIAMONDS_ORE_PRICE);
		    			SendClientMessage(playerid, YELLOW, string);

		    			return ShowQuarryUnloadDialog(playerid);
		    		}
		    	}
		    }
			return 1;
		}
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerJob(playerid) == MINER_JOB)
	{
		for(new i = 0; i < sizeof(MiningOre); i++)
		{
			if(OreData[i][ore_active] == true)
			{
				if(areaid == OreData[i][ore_area])
				{
					MineralsData[playerid][minerals_id] = i;
					MineralsData[playerid][minerals_mining] = true;

					if(OreData[i][ore_type] == ORE_TYPE_STONE)
					{
						return SendClientMessage(playerid, WHITE, "NOTE: Press LMB to start mining ore from this stone rock.");
					}
					else if(OreData[i][ore_type] == ORE_TYPE_GOLD)
					{
						return SendClientMessage(playerid, WHITE, "NOTE: Press LMB to start mining ore from this gold rock.");
					}
					else if(OreData[i][ore_type] == ORE_TYPE_DIAMOND)
					{
						return SendClientMessage(playerid, WHITE, "NOTE: Press LMB to start mining ore from this diamond rock.");
					}
				}
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	if(MineralsData[playerid][minerals_mining] == true)
	{
		MineralsData[playerid][minerals_id] = -1;
		MineralsData[playerid][minerals_mining] = false;
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == QuarryData[quarry_office_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == QuarryData[quarry_office_cp])
		{
			return ShowQuarryOfficeDialog(playerid);
		}
		else if(checkpointid == QuarryData[quarry_unload_cp])
		{
			if(GetPlayerJob(playerid) != MINER_JOB) return SendClientMessage(playerid, RED, "ERROR: You must be clocked on as a miner to unload ore at this checkpoint.");
			return ShowQuarryUnloadDialog(playerid);
		}
	}
	return 1;
}

public OnOreRenew(oreid)//Do not hook
{
	OreData[oreid][ore_hp] = 1000.0;

	new label[32];
	if(OreData[oreid][ore_type] == ORE_TYPE_STONE)
	{
		OreData[oreid][ore_type] = ORE_TYPE_STONE;

		format(label, sizeof(label), "%0.0f/1000", OreData[oreid][ore_hp]);

		OreData[oreid][ore_id] = CreateDynamicObject(3931, OreData[oreid][ore_pos][0], OreData[oreid][ore_pos][1], OreData[oreid][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
		SetDynamicObjectMaterial(OreData[oreid][ore_id], 0, 18202, "w_towncs_t", "hatwall256hi", 0xFFFFFFFF);//Credits: Amagida
	}
	else if(OreData[oreid][ore_type] == ORE_TYPE_GOLD)
	{
		OreData[oreid][ore_type] = ORE_TYPE_GOLD;

		format(label, sizeof(label), "%0.0f/1000", OreData[oreid][ore_hp]);

		OreData[oreid][ore_id] = CreateDynamicObject(3931, OreData[oreid][ore_pos][0], OreData[oreid][ore_pos][1], OreData[oreid][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
		SetDynamicObjectMaterial(OreData[oreid][ore_id], 0, 8463, "vgseland", "tiadbuddhagold", 0xFFFFFFFF);//Credits: Amagida
	}
	else if(OreData[oreid][ore_type] == ORE_TYPE_DIAMOND)
	{
		OreData[oreid][ore_type] = ORE_TYPE_DIAMOND;

		format(label, sizeof(label), "%0.0f/1000", OreData[oreid][ore_hp]);

		OreData[oreid][ore_id] = CreateDynamicObject(3931, OreData[oreid][ore_pos][0], OreData[oreid][ore_pos][1], OreData[oreid][ore_pos][2] - 0.7, 0.0, 0.0, 0.0, -1, -1, -1, 250.0);
		SetDynamicObjectMaterial(OreData[oreid][ore_id], 0, 5154, "dkcargoshp_las2", "Diamondp64", 0xFFFFFFFF);//Credits: Amagida
	}

	OreData[oreid][ore_label] = CreateDynamic3DTextLabel(label, WHITE, OreData[oreid][ore_pos][0], OreData[oreid][ore_pos][1], OreData[oreid][ore_pos][2] - 0.3, 10.0, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 0, -1, -1, -1, 10.0);
	OreData[oreid][ore_area] = CreateDynamicSphere(OreData[oreid][ore_pos][0], OreData[oreid][ore_pos][1], OreData[oreid][ore_pos][2], 1.5, -1, -1, -1, 0);

	OreData[oreid][ore_active] = true;
	return 1;
}
