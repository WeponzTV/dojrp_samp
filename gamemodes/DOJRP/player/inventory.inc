#include <YSI_Coding\y_hooks>

forward OnItemDisappear(itemid);

enum item_data
{
	item_model,
	item_object,
	item_weight,
	item_amount,
	Float:item_x,
	Float:item_y,
	Float:item_z,
	item_int,
	item_world,
	item_timer,
	Text3D:item_label,
	bool:item_active
};
new ItemData[MAX_ITEMS][item_data];

enum inventory_data
{
	inv_getitem,
	inv_getamount,
	inv_getslot,

	inv_1,
	inv_1a,
	inv_2,
	inv_2a,
	inv_3,
	inv_3a,
	inv_4,
	inv_4a,
	inv_5,
	inv_5a,
	inv_6,
	inv_6a,
	inv_7,
	inv_7a,
	inv_8,
	inv_8a,
	inv_9,
	inv_9a,
	inv_10,
	inv_10a
};
new InventoryData[MAX_PLAYERS][inventory_data];

stock EmptyPlayerInventory(playerid)
{
    if(CheckInventoryForItem(playerid, PHONE_MODEL))
    {
    	RemovePlayerPhone(playerid);
    }

	InventoryData[playerid][inv_1] = 0;
	InventoryData[playerid][inv_1a] = 0;
	InventoryData[playerid][inv_2] = 0;
	InventoryData[playerid][inv_2a] = 0;
	InventoryData[playerid][inv_3] = 0;
	InventoryData[playerid][inv_3a] = 0;
	InventoryData[playerid][inv_4] = 0;
	InventoryData[playerid][inv_4a] = 0;
	InventoryData[playerid][inv_5] = 0;
	InventoryData[playerid][inv_5a] = 0;
	InventoryData[playerid][inv_6] = 0;
	InventoryData[playerid][inv_6a] = 0;
	InventoryData[playerid][inv_7] = 0;
	InventoryData[playerid][inv_7a] = 0;
	InventoryData[playerid][inv_8] = 0;
	InventoryData[playerid][inv_8a] = 0;
	InventoryData[playerid][inv_9] = 0;
	InventoryData[playerid][inv_9a] = 0;
	InventoryData[playerid][inv_10] = 0;
	InventoryData[playerid][inv_10a] = 0;
	return SaveInventoryData(playerid);
}

stock SaveInventoryData(playerid)
{
	new query[800], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `INVENTORY` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `INVENTORY` SET S1 = '%i', S1A = '%i', S2 = '%i', S2A = '%i', S3 = '%i', S3A = '%i', S4 = '%i', S4A = '%i', S5 = '%i', S5A = '%i', S6 = '%i', S6A = '%i', S7 = '%i', S7A = '%i', S8 = '%i', S8A = '%i', S9 = '%i', S9A = '%i', S10 = '%i', S10A = '%i' WHERE `CHARACTER_ID` = '%i'", 
		InventoryData[playerid][inv_1], InventoryData[playerid][inv_1a], InventoryData[playerid][inv_2], InventoryData[playerid][inv_2a], InventoryData[playerid][inv_3], InventoryData[playerid][inv_3a], InventoryData[playerid][inv_4], InventoryData[playerid][inv_4a], InventoryData[playerid][inv_5], InventoryData[playerid][inv_5a], 
		InventoryData[playerid][inv_6], InventoryData[playerid][inv_6a], InventoryData[playerid][inv_7], InventoryData[playerid][inv_7a], InventoryData[playerid][inv_8], InventoryData[playerid][inv_8a], InventoryData[playerid][inv_9], InventoryData[playerid][inv_9a], InventoryData[playerid][inv_10], InventoryData[playerid][inv_10a], id);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `INVENTORY` (`CHARACTER_ID`, `S1`, `S1A`, `S2`, `S2A`, `S3`, `S3A`, `S4`, `S4A`, `S5`, `S5A`, `S6`, `S6A`, `S7`, `S7A`, `S8`, `S8A`, `S9`, `S9A`, `S10`, `S10A`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		id, InventoryData[playerid][inv_1], InventoryData[playerid][inv_1a], InventoryData[playerid][inv_2], InventoryData[playerid][inv_2a], InventoryData[playerid][inv_3], InventoryData[playerid][inv_3a], InventoryData[playerid][inv_4], InventoryData[playerid][inv_4a], InventoryData[playerid][inv_5], InventoryData[playerid][inv_5a], 
		InventoryData[playerid][inv_6], InventoryData[playerid][inv_6a], InventoryData[playerid][inv_7], InventoryData[playerid][inv_7a], InventoryData[playerid][inv_8], InventoryData[playerid][inv_8a], InventoryData[playerid][inv_9], InventoryData[playerid][inv_9a], InventoryData[playerid][inv_10], InventoryData[playerid][inv_10a]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	db_free_result@(database_result);
	return 1;
}

stock LoadInventoryData(playerid)
{
	new query[200];
	format(query, sizeof(query), "SELECT * FROM `INVENTORY` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		InventoryData[playerid][inv_1] = db_get_field_assoc_int(database_result, "S1");
		InventoryData[playerid][inv_1a] = db_get_field_assoc_int(database_result, "S1A");
		InventoryData[playerid][inv_2] = db_get_field_assoc_int(database_result, "S2");
		InventoryData[playerid][inv_2a] = db_get_field_assoc_int(database_result, "S2A");
		InventoryData[playerid][inv_3] = db_get_field_assoc_int(database_result, "S3");
		InventoryData[playerid][inv_3a] = db_get_field_assoc_int(database_result, "S3A");
		InventoryData[playerid][inv_4] = db_get_field_assoc_int(database_result, "S4");
		InventoryData[playerid][inv_4a] = db_get_field_assoc_int(database_result, "S4A");
		InventoryData[playerid][inv_5] = db_get_field_assoc_int(database_result, "S5");
		InventoryData[playerid][inv_5a] = db_get_field_assoc_int(database_result, "S5A");
		InventoryData[playerid][inv_6] = db_get_field_assoc_int(database_result, "S6");
		InventoryData[playerid][inv_6a] = db_get_field_assoc_int(database_result, "S6A");
		InventoryData[playerid][inv_7] = db_get_field_assoc_int(database_result, "S7");
		InventoryData[playerid][inv_7a] = db_get_field_assoc_int(database_result, "S7A");
		InventoryData[playerid][inv_8] = db_get_field_assoc_int(database_result, "S8");
		InventoryData[playerid][inv_8a] = db_get_field_assoc_int(database_result, "S8A");
		InventoryData[playerid][inv_9] = db_get_field_assoc_int(database_result, "S9");
		InventoryData[playerid][inv_9a] = db_get_field_assoc_int(database_result, "S9A");
		InventoryData[playerid][inv_10] = db_get_field_assoc_int(database_result, "S10");
		InventoryData[playerid][inv_10a] = db_get_field_assoc_int(database_result, "S10A");
	}
	db_free_result@(database_result);
	return 1;
}

stock GetFreeItemID()
{
	for(new i = 0; i < MAX_ITEMS; i++)
	{
		if(ItemData[i][item_active] == false) return i;
	}
	return -1;
}

stock Float:ReturnItemHeight(modelid)
{
	if(modelid == SPRUNK_MODEL) return 0.9;
	else if(modelid == ALCOHOL_MODEL) return 1.0;
	else if(modelid == BURGER_MODEL) return 0.95;
	else if(modelid == TACO_MODEL) return 0.95;
	else if(modelid == PIZZA_MODEL) return 1.0;
	else if(modelid == MEDIKIT_MODEL) return 0.95;
	else if(modelid == TOOLBOX_MODEL) return 0.9;
	else if(modelid == MATERIALS_MODEL) return 0.85;
	else if(modelid == JERRYCAN_MODEL) return 0.65;
	else if(modelid == CROWBAR_MODEL) return 0.8;
	else if(modelid == TICKET_MODEL) return 0.95;
	else if(modelid == SEEDS_MODEL) return 0.85;
	else if(modelid == WEED_MODEL) return 1.05;
	else if(modelid == PHONE_MODEL) return 1.0;
	return 0.7;
}

stock Float:ReturnLabelHeight(modelid)
{
	if(modelid == SPRUNK_MODEL) return 0.2;
	else if(modelid == ALCOHOL_MODEL) return 0.4;
	else if(modelid == BURGER_MODEL) return 0.2;
	else if(modelid == TACO_MODEL) return 0.2;
	else if(modelid == PIZZA_MODEL) return 0.2;
	else if(modelid == MEDIKIT_MODEL) return 0.3;
	else if(modelid == TOOLBOX_MODEL) return 0.2;
	else if(modelid == MATERIALS_MODEL) return 0.25;
	else if(modelid == JERRYCAN_MODEL) return 0.2;
	else if(modelid == CROWBAR_MODEL) return 0.2;
	else if(modelid == TICKET_MODEL) return 0.2;
	else if(modelid == SEEDS_MODEL) return 0.3;
	else if(modelid == WEED_MODEL) return 0.3;
	else if(modelid == PHONE_MODEL) return 0.2;
	return 0.2;
}

stock ReturnItemWeight(modelid)
{
	if(modelid == SPRUNK_MODEL) return 1;
	else if(modelid == ALCOHOL_MODEL) return 2;
	else if(modelid == BURGER_MODEL) return 0;
	else if(modelid == TACO_MODEL) return 0;
	else if(modelid == PIZZA_MODEL) return 0;
	else if(modelid == MEDIKIT_MODEL) return 2;
	else if(modelid == TOOLBOX_MODEL) return 4;
	else if(modelid == MATERIALS_MODEL) return 1;
	else if(modelid == JERRYCAN_MODEL) return 3;
	else if(modelid == CROWBAR_MODEL) return 3;
	else if(modelid == TICKET_MODEL) return 0;
	else if(modelid == SEEDS_MODEL) return 0;
	else if(modelid == WEED_MODEL) return 1;
	else if(modelid == PHONE_MODEL) return 1;
	return 0;
}

stock ReturnItemName(modelid)
{
	new name[32];
	format(name, sizeof(name), "Empty Slot");
	if(modelid == SPRUNK_MODEL) { format(name, sizeof(name), "Sprunk"); }
	else if(modelid == ALCOHOL_MODEL) { format(name, sizeof(name), "Alcohol"); }
	else if(modelid == BURGER_MODEL) { format(name, sizeof(name), "Burger"); }
	else if(modelid == TACO_MODEL) { format(name, sizeof(name), "Taco"); }
	else if(modelid == PIZZA_MODEL) { format(name, sizeof(name), "Pizza"); }
	else if(modelid == MEDIKIT_MODEL) { format(name, sizeof(name), "Medikit"); }
	else if(modelid == TOOLBOX_MODEL) { format(name, sizeof(name), "Toolbox"); }
	else if(modelid == MATERIALS_MODEL) { format(name, sizeof(name), "Gun Materials"); }
	else if(modelid == JERRYCAN_MODEL) { format(name, sizeof(name), "Jerrycan"); }
	else if(modelid == CROWBAR_MODEL) { format(name, sizeof(name), "Crowbar"); }
	else if(modelid == TICKET_MODEL) { format(name, sizeof(name), "Lotto Ticket"); }
	else if(modelid == SEEDS_MODEL) { format(name, sizeof(name), "Seeds"); }
	else if(modelid == WEED_MODEL) { format(name, sizeof(name), "Weed"); }
	else if(modelid == PHONE_MODEL) { format(name, sizeof(name), "Cell Phone"); }
	return name;
}

stock GetItemCount(playerid, modelid)
{
	new count = 0;
	if(InventoryData[playerid][inv_1] == modelid) { count += InventoryData[playerid][inv_1a]; }
	else if(InventoryData[playerid][inv_2] == modelid) { count += InventoryData[playerid][inv_2a]; }
	else if(InventoryData[playerid][inv_3] == modelid) { count += InventoryData[playerid][inv_3a]; }
	else if(InventoryData[playerid][inv_4] == modelid) { count += InventoryData[playerid][inv_4a]; }
	else if(InventoryData[playerid][inv_5] == modelid) { count += InventoryData[playerid][inv_5a]; }
	else if(InventoryData[playerid][inv_6] == modelid) { count += InventoryData[playerid][inv_6a]; }
	else if(InventoryData[playerid][inv_7] == modelid) { count += InventoryData[playerid][inv_7a]; }
	else
	{
		if(GetPlayerVIP(playerid))
		{
			if(InventoryData[playerid][inv_8] == modelid) { count += InventoryData[playerid][inv_8a]; }
			else if(InventoryData[playerid][inv_9] == modelid) { count += InventoryData[playerid][inv_9a]; }
			else if(InventoryData[playerid][inv_10] == modelid) { count += InventoryData[playerid][inv_10a]; }
		}
	}
	return count;
}

stock CheckInventoryForItem(playerid, modelid)
{
	if(InventoryData[playerid][inv_1] == modelid) return 1;
	else if(InventoryData[playerid][inv_2] == modelid) return 2;
	else if(InventoryData[playerid][inv_3] == modelid) return 3;
	else if(InventoryData[playerid][inv_4] == modelid) return 4;
	else if(InventoryData[playerid][inv_5] == modelid) return 5;
	else if(InventoryData[playerid][inv_6] == modelid) return 6;
	else if(InventoryData[playerid][inv_7] == modelid) return 7;
	else
	{
		if(GetPlayerVIP(playerid))
		{
			if(InventoryData[playerid][inv_8] == modelid) return 8;
			else if(InventoryData[playerid][inv_9] == modelid) return 9;
			else if(InventoryData[playerid][inv_10] == modelid) return 10;
		}
	}
	return 0;
}

stock IsPlayerInRangeOfItem(playerid, Float:range)
{
	for(new i = 0; i < MAX_ITEMS; i++)
	{
		if(ItemData[i][item_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, range, ItemData[i][item_x], ItemData[i][item_y], ItemData[i][item_z])) return 1;
		}
	}
	return 0;
}

stock CreateItem(modelid, amount, Float:x, Float:y, Float:z, interior, world)
{
	new label[128], id = GetFreeItemID();
	if(id == -1)
	{
		for(new item = 0; item < MAX_ITEMS; item++)
		{
			if(ItemData[item][item_active] == true)
			{
				DestroyDynamicObject(ItemData[item][item_object]);
				ItemData[item][item_active] = false;
			}
		}
		id = GetFreeItemID();
		if(id == -1) return 1;
	}

	ItemData[id][item_model] = modelid;
	ItemData[id][item_weight] = ReturnItemWeight(modelid);
	ItemData[id][item_amount] = amount;
	ItemData[id][item_x] = x;
	ItemData[id][item_y] = y;
	ItemData[id][item_z] = (z - ReturnItemHeight(modelid));
	ItemData[id][item_int] = interior;
	ItemData[id][item_world] = world;

	format(label, sizeof(label), "x%i %s\nPress ~k~~CONVERSATION_NO~", amount, ReturnItemName(modelid));
	ItemData[id][item_label] = CreateDynamic3DTextLabel(label, WHITE, ItemData[id][item_x], ItemData[id][item_y], ItemData[id][item_z] + ReturnLabelHeight(modelid), 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 5.0);
	ItemData[id][item_object] = CreateDynamicObject(ItemData[id][item_model], ItemData[id][item_x], ItemData[id][item_y], ItemData[id][item_z], 0.0, 0.0, 0.0, ItemData[id][item_world], ItemData[id][item_int], -1, 100.0);

	ItemData[id][item_active] = true;
	ItemData[id][item_timer] = SetTimerEx("OnItemDisappear", 600000, false, "i", id);
	return 1;
}

stock GetFreeInventorySlot(playerid)
{
	if(InventoryData[playerid][inv_1] == 0) return 1;
	else if(InventoryData[playerid][inv_2] == 0) return 2;
	else if(InventoryData[playerid][inv_3] == 0) return 3;
	else if(InventoryData[playerid][inv_4] == 0) return 4;
	else if(InventoryData[playerid][inv_5] == 0) return 5;
 	else if(InventoryData[playerid][inv_6] == 0) return 6;
	else if(InventoryData[playerid][inv_7] == 0) return 7;
	else
	{
		if(GetPlayerVIP(playerid))
		{
			if(InventoryData[playerid][inv_8] == 0) return 8;
			else if(InventoryData[playerid][inv_9] == 0) return 9;
			else if(InventoryData[playerid][inv_10] == 0) return 10;
		}
	}
	return 0;
}

stock ReturnInventoryWeight(playerid)
{
	new weight = 0;
	weight += (ReturnItemWeight(InventoryData[playerid][inv_1]) * InventoryData[playerid][inv_1a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_2]) * InventoryData[playerid][inv_2a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_3]) * InventoryData[playerid][inv_3a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_4]) * InventoryData[playerid][inv_4a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_5]) * InventoryData[playerid][inv_5a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_6]) * InventoryData[playerid][inv_6a]);
	weight += (ReturnItemWeight(InventoryData[playerid][inv_7]) * InventoryData[playerid][inv_7a]);

	if(GetPlayerVIP(playerid))
	{
		weight += (ReturnItemWeight(InventoryData[playerid][inv_8]) * InventoryData[playerid][inv_8a]);
		weight += (ReturnItemWeight(InventoryData[playerid][inv_9]) * InventoryData[playerid][inv_9a]);
		weight += (ReturnItemWeight(InventoryData[playerid][inv_10]) * InventoryData[playerid][inv_10a]);
	}
	return weight;
}

stock AddItemToInventory(playerid, modelid, amount, bool:anim)
{
	new slot = CheckInventoryForItem(playerid, modelid);
	if(slot > 0)
	{
		switch(slot)
		{
			case 1: { InventoryData[playerid][inv_1a] += amount; }
			case 2: { InventoryData[playerid][inv_2a] += amount; }
			case 3: { InventoryData[playerid][inv_3a] += amount; }
			case 4: { InventoryData[playerid][inv_4a] += amount; }
			case 5: { InventoryData[playerid][inv_5a] += amount; }
			case 6: { InventoryData[playerid][inv_6a] += amount; }
			case 7: { InventoryData[playerid][inv_7a] += amount; }
			case 8: { InventoryData[playerid][inv_8a] += amount; }
			case 9: { InventoryData[playerid][inv_9a] += amount; }
			case 10: { InventoryData[playerid][inv_10a] += amount; }
		}
	}
	else
	{
		slot = GetFreeInventorySlot(playerid);
		if(slot == 0) return 1;
		else if(slot == 1) { InventoryData[playerid][inv_1] = modelid; InventoryData[playerid][inv_1a] += amount; }
		else if(slot == 2) { InventoryData[playerid][inv_2] = modelid; InventoryData[playerid][inv_2a] += amount; }
		else if(slot == 3) { InventoryData[playerid][inv_3] = modelid; InventoryData[playerid][inv_3a] += amount; }
		else if(slot == 4) { InventoryData[playerid][inv_4] = modelid; InventoryData[playerid][inv_4a] += amount; }
		else if(slot == 5) { InventoryData[playerid][inv_5] = modelid; InventoryData[playerid][inv_5a] += amount; }
		else if(slot == 6) { InventoryData[playerid][inv_6] = modelid; InventoryData[playerid][inv_6a] += amount; }
		else if(slot == 7) { InventoryData[playerid][inv_7] = modelid; InventoryData[playerid][inv_7a] += amount; }
		else if(slot == 8) { InventoryData[playerid][inv_8] = modelid; InventoryData[playerid][inv_8a] += amount; }
		else if(slot == 9) { InventoryData[playerid][inv_9] = modelid; InventoryData[playerid][inv_9a] += amount; }
		else if(slot == 10) { InventoryData[playerid][inv_10] = modelid; InventoryData[playerid][inv_10a] += amount; }
	}

	if(anim == true)
	{
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock RemoveItemFromInventory(playerid, slot, amount, bool:anim)
{
	new item = 0;
	if(slot == 1)
	{
		if(InventoryData[playerid][inv_1] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_1];

		InventoryData[playerid][inv_1a] -= amount;
		if(InventoryData[playerid][inv_1a] <= 0) { InventoryData[playerid][inv_1] = 0; InventoryData[playerid][inv_1a] = 0; }
	}
	else if(slot == 2)
	{
		if(InventoryData[playerid][inv_2] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_2];

		InventoryData[playerid][inv_2a] -= amount;
		if(InventoryData[playerid][inv_2a] <= 0) { InventoryData[playerid][inv_2] = 0; InventoryData[playerid][inv_2a] = 0; }
	}
	else if(slot == 3)
	{
		if(InventoryData[playerid][inv_3] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_3];

		InventoryData[playerid][inv_3a] -= amount;
		if(InventoryData[playerid][inv_3a] <= 0) { InventoryData[playerid][inv_3] = 0; InventoryData[playerid][inv_3a] = 0; }
	}
	else if(slot == 4)
	{
		if(InventoryData[playerid][inv_4] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_4];

		InventoryData[playerid][inv_4a] -= amount;
		if(InventoryData[playerid][inv_4a] <= 0) { InventoryData[playerid][inv_4] = 0; InventoryData[playerid][inv_4a] = 0; }
	}
	else if(slot == 5)
	{
		if(InventoryData[playerid][inv_5] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_5];

		InventoryData[playerid][inv_5a] -= amount;
		if(InventoryData[playerid][inv_5a] <= 0) { InventoryData[playerid][inv_5] = 0; InventoryData[playerid][inv_5a] = 0; }
	}
	else if(slot == 6)
	{
		if(InventoryData[playerid][inv_6] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_6];

		InventoryData[playerid][inv_6a] -= amount;
		if(InventoryData[playerid][inv_6a] <= 0) { InventoryData[playerid][inv_6] = 0; InventoryData[playerid][inv_6a] = 0; }
	}
	else if(slot == 7)
	{
		if(InventoryData[playerid][inv_7] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_7];

		InventoryData[playerid][inv_7a] -= amount;
		if(InventoryData[playerid][inv_7a] <= 0) { InventoryData[playerid][inv_7] = 0; InventoryData[playerid][inv_7a] = 0; }
	}
	else if(slot == 8)
	{
		if(InventoryData[playerid][inv_8] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_8];

		InventoryData[playerid][inv_8a] -= amount;
		if(InventoryData[playerid][inv_8a] <= 0) { InventoryData[playerid][inv_8] = 0; InventoryData[playerid][inv_8a] = 0; }
	}
	else if(slot == 9)
	{
		if(InventoryData[playerid][inv_9] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_9];

		InventoryData[playerid][inv_9a] -= amount;
		if(InventoryData[playerid][inv_9a] <= 0) { InventoryData[playerid][inv_9] = 0; InventoryData[playerid][inv_9a] = 0; }
	}
	else if(slot == 10)
	{
		if(InventoryData[playerid][inv_10] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
		
		item = InventoryData[playerid][inv_10];

		InventoryData[playerid][inv_10a] -= amount;
		if(InventoryData[playerid][inv_10a] <= 0) { InventoryData[playerid][inv_10] = 0; InventoryData[playerid][inv_10a] = 0; }
	}

	if(item == PHONE_MODEL)
	{
		RemovePlayerPhone(playerid);
	}

	if(anim == true)
	{
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);

		if(item > 0)
		{
			new Float:pos[3];
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			CreateItem(item, amount, pos[0], pos[1], pos[2], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
		}
	}
	return 1;
}

stock OnPlayerUseInventoryItem(playerid, slot, item)
{
	if(!strcmp(ReturnItemName(item), "Empty Slot", true)) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
	
	if(item == SPRUNK_MODEL)
	{
		if(GetPlayerThirst(playerid) >= 100) return SendClientMessage(playerid, RED, "ERROR: You are not thirsty at the moment.");

		SetPlayerThirst(playerid, GetPlayerThirst(playerid) + 25);
		if(GetPlayerThirst(playerid) > 100) { SetPlayerThirst(playerid, 100); }

		ApplyAnimation(playerid, "BAR", "dnk_stndM_loop", 4.1, 0, 0, 0, 0, 0, 1);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == ALCOHOL_MODEL)
	{
		SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 4000);
		if(GetPlayerDrunkLevel(playerid) > 50000) { SetPlayerDrunkLevel(playerid, 4000); }

		ApplyAnimation(playerid, "BAR", "dnk_stndM_loop", 4.1, 0, 0, 0, 0, 0, 1);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == BURGER_MODEL)
	{
		if(GetPlayerHunger(playerid) >= 100) return SendClientMessage(playerid, RED, "ERROR: You are not hungry at the moment.");

		SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 25);
		if(GetPlayerHunger(playerid) > 100) { SetPlayerHunger(playerid, 100); }

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == TACO_MODEL)
	{
		if(GetPlayerHunger(playerid) >= 100) return SendClientMessage(playerid, RED, "ERROR: You are not hungry at the moment.");

		SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 25);
		if(GetPlayerHunger(playerid) > 100) { SetPlayerHunger(playerid, 100); }

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == PIZZA_MODEL)
	{
		if(GetPlayerHunger(playerid) >= 100) return SendClientMessage(playerid, RED, "ERROR: You are not hungry at the moment.");

		SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 25);
		if(GetPlayerHunger(playerid) > 100) { SetPlayerHunger(playerid, 100); }

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == MEDIKIT_MODEL)
	{
		if((gettime() - 60) < GetTimerStatus(playerid, TIMER_TYPE_HEAL)) return SendClientMessage(playerid, RED, "ERROR: Please wait 60 seconds before healing yourself again.");
    	SetTimerStatus(playerid, TIMER_TYPE_HEAL, gettime());

		new Float:health;
		GetPlayerHealth(playerid, health);
		if(health >= 100) return SendClientMessage(playerid, RED, "ERROR: You currently have maximum health.");

		SetPlayerHealth(playerid, 100.0);

		ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

		return RemoveItemFromInventory(playerid, slot, 1, false);
	}
	else if(item == TOOLBOX_MODEL)
	{
		if(DegreeData[playerid][degree_mechanical] == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Mechanical Degree to be able to repair vehicles.");

		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		foreach(new v : Vehicle)
		{
			GetVehiclePos(v, pos[0], pos[1], pos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
			{
				RepairVehicle(v);

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

				foreach(new i : Player)
				{
					if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
					{
						format(string, sizeof(string), "** %s repairs their vehicle...", name);
						SendClientMessage(i, GREY, string);
					}
				}
				return 1;
			}
		}
		return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to repair.");
	}
	else if(item == MATERIALS_MODEL)
	{
		return ShowMaterialsDialog(playerid);
	}
	else if(item == JERRYCAN_MODEL)
	{
		new string[128], Float:pos[3], name[24];
		GetPlayerName(playerid, name, sizeof(name));
		foreach(new v : Vehicle)
		{
			GetVehiclePos(v, pos[0], pos[1], pos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
			{
				if(IsVehicleBicycle(v)) return SendClientMessage(playerid, RED, "ERROR: You cannot refuel bicycles.");
				if(GetVehicleFuel(v) >= 100) return SendClientMessage(playerid, RED, "ERROR: That vehicle currently has 100 percent fuel.");

				if((GetVehicleFuel(v) + 50) > 100) { SetVehicleFuel(v, 100); }
				else { SetVehicleFuel(v, (GetVehicleFuel(v) + 50)); }

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

				RemoveItemFromInventory(playerid, slot, 1, false);

				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				
				foreach(new i : Player)
				{
					if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
					{
						format(string, sizeof(string), "** %s refuels their vehicle...", name);
					 	SendClientMessage(i, GREY, string);
					}
			  	}
				return 1;
			}
		}
		return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to refuel.");
	}
	else if(item == CROWBAR_MODEL)
	{
		return ProcessSafeRobbery(playerid);
	}
	else if(item == TICKET_MODEL)
	{
		new amount = GetItemCount(playerid, TICKET_MODEL);
		if(amount > 0)
		{
			ShowLottoNumbers(playerid);
		}
		return 1;
	}
	else if(item == SEEDS_MODEL)
	{
		return OnPlayerPlantSeed(playerid);
	}
	else if(item == WEED_MODEL)
	{
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: You are already smoking weed, press ENTER to stop the animation.");
		if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before smoking weed.");
		SetAnimationStatus(playerid, true);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
	}
	else if(item == PHONE_MODEL)
	{
		ShowPlayerPhone(playerid);
	}
	return 1;
}

stock ShowPlayerInventory(playerid)
{
	new string1[128], string2[600];
	if(GetPlayerVIP(playerid))
	{
		format(string1, sizeof(string1), "{FFFFFF}Inventory (Weight: %i/%i Pounds)", ReturnInventoryWeight(playerid), MAX_VIP_WEIGHT);
		format(string2, sizeof(string2), "{FFFFFF}%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)", 
		ReturnItemName(InventoryData[playerid][inv_1]), InventoryData[playerid][inv_1a],
		ReturnItemName(InventoryData[playerid][inv_2]), InventoryData[playerid][inv_2a],
		ReturnItemName(InventoryData[playerid][inv_3]), InventoryData[playerid][inv_3a],
		ReturnItemName(InventoryData[playerid][inv_4]), InventoryData[playerid][inv_4a],
		ReturnItemName(InventoryData[playerid][inv_5]), InventoryData[playerid][inv_5a],
		ReturnItemName(InventoryData[playerid][inv_6]), InventoryData[playerid][inv_6a],
		ReturnItemName(InventoryData[playerid][inv_7]), InventoryData[playerid][inv_7a],
		ReturnItemName(InventoryData[playerid][inv_8]), InventoryData[playerid][inv_8a],
		ReturnItemName(InventoryData[playerid][inv_9]), InventoryData[playerid][inv_9a],
		ReturnItemName(InventoryData[playerid][inv_10]), InventoryData[playerid][inv_10a]);
	}
	else
	{
		format(string1, sizeof(string1), "{FFFFFF}Inventory (Weight: %i/%i Pounds)", ReturnInventoryWeight(playerid), MAX_PLAYER_WEIGHT);
		format(string2, sizeof(string2), "{FFFFFF}%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)\n%s (x%i)", 
		ReturnItemName(InventoryData[playerid][inv_1]), InventoryData[playerid][inv_1a],
		ReturnItemName(InventoryData[playerid][inv_2]), InventoryData[playerid][inv_2a],
		ReturnItemName(InventoryData[playerid][inv_3]), InventoryData[playerid][inv_3a],
		ReturnItemName(InventoryData[playerid][inv_4]), InventoryData[playerid][inv_4a],
		ReturnItemName(InventoryData[playerid][inv_5]), InventoryData[playerid][inv_5a],
		ReturnItemName(InventoryData[playerid][inv_6]), InventoryData[playerid][inv_6a],
		ReturnItemName(InventoryData[playerid][inv_7]), InventoryData[playerid][inv_7a]);
	}
	return ShowPlayerDialog(playerid, INVENTORY_DIALOG, DIALOG_STYLE_LIST, string1, string2, "Action", "Cancel");
}

hook OnGameModeInit()
{
	for(new i = 0; i < MAX_ITEMS; i++)
	{
		ItemData[i][item_timer] = -1;
		ItemData[i][item_active] = false;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		InventoryData[playerid][inv_getitem] = 0;
		InventoryData[playerid][inv_getamount] = 0;
		InventoryData[playerid][inv_getslot] = 0;

		InventoryData[playerid][inv_1] = 0;
		InventoryData[playerid][inv_1a] = 0;
		InventoryData[playerid][inv_2] = 0;
		InventoryData[playerid][inv_2a] = 0;
		InventoryData[playerid][inv_3] = 0;
		InventoryData[playerid][inv_3a] = 0;
		InventoryData[playerid][inv_4] = 0;
		InventoryData[playerid][inv_4a] = 0;
		InventoryData[playerid][inv_5] = 0;
		InventoryData[playerid][inv_5a] = 0;
		InventoryData[playerid][inv_6] = 0;
		InventoryData[playerid][inv_6a] = 0;
		InventoryData[playerid][inv_7] = 0;
		InventoryData[playerid][inv_7a] = 0;
		InventoryData[playerid][inv_8] = 0;
		InventoryData[playerid][inv_8a] = 0;
		InventoryData[playerid][inv_9] = 0;
		InventoryData[playerid][inv_9a] = 0;
		InventoryData[playerid][inv_10] = 0;
		InventoryData[playerid][inv_10a] = 0;
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_NO) && !(oldkeys & KEY_NO) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)//N
	{
		for(new i = 0; i < MAX_ITEMS; i++)
		{
			if(ItemData[i][item_active] == true)
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.5, ItemData[i][item_x], ItemData[i][item_y], ItemData[i][item_z]) && GetPlayerInterior(playerid) == ItemData[i][item_int] && GetPlayerInterior(playerid) == ItemData[i][item_int] && GetPlayerVirtualWorld(playerid) == ItemData[i][item_world])
				{
					if(GetPlayerVIP(playerid))
					{
						if((ReturnInventoryWeight(playerid) + ReturnItemWeight(ItemData[i][item_model]) * ItemData[i][item_amount]) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
					}
					else
					{
						if((ReturnInventoryWeight(playerid) + ReturnItemWeight(ItemData[i][item_model]) * ItemData[i][item_amount]) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: That item is too heavy to fit in your inventory.");
					}

					new slot = CheckInventoryForItem(playerid, ItemData[i][item_model]);
					if(slot == 0)
					{
						slot = GetFreeInventorySlot(playerid);
						if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: You don't have any free inventory slots.");
					}

					if(ItemData[i][item_model] == TICKET_MODEL)
					{
						new amount = GetItemCount(playerid, TICKET_MODEL);
						if(amount > 0)
						{
							return SendClientMessage(playerid, RED, "ERROR: You can only hold x1 Lotto Ticket at a time.");
						}
						else
						{
							ProcessLottoTicket(playerid);
						}
					}
					else if(ItemData[i][item_model] == PHONE_MODEL)
					{
						if(!GetPlayerPhone(playerid))
						{
							GivePlayerPhone(playerid);
						}
					}

					if(ItemData[i][item_timer] != -1)
					{
						KillTimer(ItemData[i][item_timer]);
						ItemData[i][item_timer] = -1;
					}

				 	DestroyDynamic3DTextLabel(ItemData[i][item_label]);
				 	DestroyDynamicObject(ItemData[i][item_object]);
				 	ItemData[i][item_active] = false;

				 	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
				 	{
						AddItemToInventory(playerid, ItemData[i][item_model], ItemData[i][item_amount], false);
					}
					else 
				 	{
						AddItemToInventory(playerid, ItemData[i][item_model], ItemData[i][item_amount], true);
					}
					return 1;
				}
			}
		}
		return 1;
	}
	else if((newkeys & KEY_YES) && !(oldkeys & KEY_YES) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !IsPlayerInjured(playerid))//Y
	{
		ShowPlayerInventory(playerid);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case INVENTORY_DIALOG:
		{
			if(response)
			{
				new string[200];
				switch(listitem)
				{
					case 0:
					{
						if(InventoryData[playerid][inv_1] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_1]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_1];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_1a];
						InventoryData[playerid][inv_getslot] = 1;
					}
					case 1:
					{
						if(InventoryData[playerid][inv_2] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_2]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_2];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_2a];
						InventoryData[playerid][inv_getslot] = 2;
					}
					case 2:
					{
						if(InventoryData[playerid][inv_3] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_3]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_3];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_3a];
						InventoryData[playerid][inv_getslot] = 3;
					}
					case 3:
					{
						if(InventoryData[playerid][inv_4] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_4]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_4];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_4a];
						InventoryData[playerid][inv_getslot] = 4;
					}
					case 4:
					{
						if(InventoryData[playerid][inv_5] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_5]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_5];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_5a];
						InventoryData[playerid][inv_getslot] = 5;
					}
					case 5:
					{
						if(InventoryData[playerid][inv_6] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_6]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_6];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_6a];
						InventoryData[playerid][inv_getslot] = 6;
					}
					case 6:
					{
						if(InventoryData[playerid][inv_7] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_7]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_7];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_7a];
						InventoryData[playerid][inv_getslot] = 7;
					}
					case 7:
					{
						if(InventoryData[playerid][inv_8] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_8]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_8];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_8a];
						InventoryData[playerid][inv_getslot] = 8;
					}
					case 8:
					{
						if(InventoryData[playerid][inv_9] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_9]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_9];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_9a];
						InventoryData[playerid][inv_getslot] = 9;
					}
					case 9:
					{
						if(InventoryData[playerid][inv_10] == 0) return SendClientMessage(playerid, RED, "ERROR: That inventory slot is empty.");
						format(string, sizeof(string), "{FFFFFF}What would you like to do with your %s?", ReturnItemName(InventoryData[playerid][inv_10]));
						InventoryData[playerid][inv_getitem] = InventoryData[playerid][inv_10];
						InventoryData[playerid][inv_getamount] = InventoryData[playerid][inv_10a];
						InventoryData[playerid][inv_getslot] = 10;
					}
				}

				ShowPlayerDialog(playerid, ACTION_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Inventory > Action", string, "Use", "Drop");
			}
			return 1;
		}
		case ACTION_DIALOG:
		{
			if(response)
			{
				OnPlayerUseInventoryItem(playerid, InventoryData[playerid][inv_getslot], InventoryData[playerid][inv_getitem]);
			}
			else
			{
				new string[200], amount = InventoryData[playerid][inv_getamount], item = InventoryData[playerid][inv_getitem], slot = InventoryData[playerid][inv_getslot];
				if(IsPlayerInRangeOfItem(playerid, 2.0)) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot drop an item within 2 metres of another item.");
				if(amount > 1)
				{
					format(string, sizeof(string), "{FFFFFF}How much would you like to drop? (Holding: x%i %s)", amount, ReturnItemName(item));
					return ShowPlayerDialog(playerid, DROP_AMOUNT_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Inventory > Drop", string, "Drop", "Back");
				}
				else
				{
					RemoveItemFromInventory(playerid, slot, 1, true);
				}
			}
			return 1;
		}
		case DROP_AMOUNT_DIALOG:
		{
			if(response)
			{
				if(!IsNumeric(inputtext) || strval(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
				if(strval(inputtext) > GetItemCount(playerid, InventoryData[playerid][inv_getitem])) return SendClientMessage(playerid, RED, "ERROR: You don't have that many items in your inventory.");
				return RemoveItemFromInventory(playerid, InventoryData[playerid][inv_getslot], strval(inputtext), true);
			}
			else
			{
				ShowPlayerInventory(playerid);
			}
		}
	}
	return 1;
}

public OnItemDisappear(itemid)//Do not hook
{
	if(IsValidDynamic3DTextLabel(ItemData[itemid][item_label])) { DestroyDynamic3DTextLabel(ItemData[itemid][item_label]); }
	if(IsValidDynamicObject(ItemData[itemid][item_object])) { DestroyDynamicObject(ItemData[itemid][item_object]); }
	ItemData[itemid][item_timer] = -1;
	ItemData[itemid][item_active] = false;
	return 1;
}

YCMD:inventory(playerid, params[], help)
{
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	return ShowPlayerInventory(playerid);
}
