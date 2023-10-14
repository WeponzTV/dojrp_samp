#include <YSI_Coding\y_hooks>

new Iterator:Businesses<MAX_BUSINESSES>;

enum business_data
{
	business_charid,
	business_city,
	business_value,
	business_stock,
	business_profit,
	business_name[64],
	Float:business_extx,
	Float:business_exty,
	Float:business_extz,
	Float:business_intx,
	Float:business_inty,
	Float:business_intz,
	Float:business_enterx,
	Float:business_entery,
	Float:business_enterz,
	Float:business_entera,
	Float:business_exitx,
	Float:business_exity,
	Float:business_exitz,
	Float:business_exita,
	business_intinterior,
	business_intworld,
	business_entercp,
	business_exitcp,
	business_countercp,
	business_pickup,
	business_clerk,
	Text3D:business_label,
	bool:business_active
};
new BusinessData[MAX_BUSINESSES][business_data];

enum owner_data
{
	owner_businessid,
	owner_salebusiness,
	owner_saleprice,
	owner_saleowner,
	owner_saleto,
	bool:owner_saleactive
};
new OwnerData[MAX_PLAYERS][owner_data];

stock GetFreeBusinessSlot()
{
	for(new i = 0; i < MAX_BUSINESSES; i++)
	{
	    if(BusinessData[i][business_active] == false) return i;
	}
	return -1;
}

stock ReturnBusinessPercent(amount, percent)
{
	return (amount / 100 * percent);
}

stock GetOwnedBusinessCount(playerid)
{
	new count = 0;
	foreach(new i : Businesses)
    {
    	if(BusinessData[i][business_active] == true)
    	{
	    	if(GetPlayerCharacterID(playerid) == BusinessData[i][business_charid])
	        {
	        	count++;
	        }
    	}
    }
	return count;
}

stock UpdateNearbyCommercialValue(businessid)
{
	new query[200];
    foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true && i != businessid)
		{
			if(PointInRangeOfPoint(250.0, BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz]))
			{
				BusinessData[i][business_value] += ReturnBusinessPercent(BusinessData[i][business_value], COMMERCIAL_VALUE_PERCENT);

			 	format(query, sizeof(query), "UPDATE `BUSINESSES` SET `VALUE` = '%i' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_value], i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);
		    }
	    }
	}
	return 1;
}

stock LoadBusinesses()
{
	new query[128], name[64];
	for(new i = 0; i < MAX_BUSINESSES; i++)
	{
		format(query, sizeof(query), "SELECT * FROM `BUSINESSES` WHERE `BUSINESS_ID` = '%i'", i);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_get_field_assoc@(database_result, "NAME", name, sizeof(name));
			BusinessData[i][business_name] = name;

			BusinessData[i][business_charid] = db_get_field_assoc_int(database_result, "CHARACTER_ID");
			BusinessData[i][business_city] = db_get_field_assoc_int(database_result, "CITY");
			BusinessData[i][business_value] = db_get_field_assoc_int(database_result, "VALUE");
			BusinessData[i][business_stock] = db_get_field_assoc_int(database_result, "STOCK");
			BusinessData[i][business_profit] = db_get_field_assoc_int(database_result, "PROFIT");

			BusinessData[i][business_extx] = db_get_field_assoc_float(database_result, "EXTX");
			BusinessData[i][business_exty] = db_get_field_assoc_float(database_result, "EXTY");
			BusinessData[i][business_extz] = db_get_field_assoc_float(database_result, "EXTZ");

			BusinessData[i][business_intx] = db_get_field_assoc_float(database_result, "INTX");
			BusinessData[i][business_inty] = db_get_field_assoc_float(database_result, "INTY");
			BusinessData[i][business_intz] = db_get_field_assoc_float(database_result, "INTZ");

			BusinessData[i][business_enterx] = db_get_field_assoc_float(database_result, "ENTERX");
			BusinessData[i][business_entery] = db_get_field_assoc_float(database_result, "ENTERY");
			BusinessData[i][business_enterz] = db_get_field_assoc_float(database_result, "ENTERZ");
			BusinessData[i][business_entera] = db_get_field_assoc_float(database_result, "ENTERA");

			BusinessData[i][business_exitx] = db_get_field_assoc_float(database_result, "EXITX");
			BusinessData[i][business_exity] = db_get_field_assoc_float(database_result, "EXITY");
			BusinessData[i][business_exitz] = db_get_field_assoc_float(database_result, "EXITZ");
			BusinessData[i][business_exita] = db_get_field_assoc_float(database_result, "EXITA");

			BusinessData[i][business_intinterior] = db_get_field_assoc_int(database_result, "INTINTERIOR");
			BusinessData[i][business_intworld] = db_get_field_assoc_int(database_result, "INTWORLD");

			BusinessData[i][business_clerk] = CreateDynamicActor(65, -30.8971, -30.7111, 1003.5573, 359.4400, true, 100.0, BusinessData[i][business_intworld], BusinessData[i][business_intinterior], -1, 50.0, -1, 0);

			if(BusinessData[i][business_charid] == 0)
			{
				BusinessData[i][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], -1, -1, -1, 50.0, -1, 0);
			}
			else
			{
				BusinessData[i][business_pickup] = CreateDynamicPickup(1272, 1, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], -1, -1, -1, 50.0, -1, 0);
			}

			BusinessData[i][business_label] = CreateDynamic3DTextLabel(name, WHITE, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 10.0);

			BusinessData[i][business_entercp] = CreateDynamicCP(BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], 1.0, 0, 0, -1, 4.0);
			BusinessData[i][business_exitcp] = CreateDynamicCP(BusinessData[i][business_intx], BusinessData[i][business_inty], BusinessData[i][business_intz], 1.0, BusinessData[i][business_intworld], BusinessData[i][business_intinterior], -1, 4.0);

			BusinessData[i][business_countercp] = CreateDynamicCP(-30.8866, -29.0168, 1003.5573, 1.0, BusinessData[i][business_intworld], BusinessData[i][business_intinterior], -1, 4.0);

			BusinessData[i][business_active] = true;

			Iter_Add(Businesses, i);
		}
		db_free_result@(database_result);
	}
	return 1;
}

stock UnloadBusinesses()
{
	foreach(new i : Businesses)
	{
		DestroyDynamicActor(BusinessData[i][business_clerk]);
		DestroyDynamic3DTextLabel(BusinessData[i][business_label]);
		DestroyDynamicPickup(BusinessData[i][business_pickup]);
		DestroyDynamicCP(BusinessData[i][business_entercp]);
		DestroyDynamicCP(BusinessData[i][business_exitcp]);

		Iter_Remove(Businesses, i);
	}
	return 1;
}

stock ShowMenuDialog(playerid)
{
	new string[300], businessid = OwnerData[playerid][owner_businessid];
	format(string, sizeof(string), "{FFFFFF}Current Value: $%i\nAvailable Profit: $%i\nTotal Stock: %i/%i\nChange Name\nSell Business", BusinessData[businessid][business_value], BusinessData[businessid][business_profit], BusinessData[businessid][business_stock], MAX_STOCK);
	return ShowPlayerDialog(playerid, BUSINESS_MENU_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business Menu", string, "Select", "Cancel");
}

stock ShowBusinessDialog(playerid)
{
	return ShowPlayerDialog(playerid, BUSINESS_MAIN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business > Main Menu", "{FFFFFF}Items\nWeapons", "Select", "Cancel");
}

stock ShowItemsDialog(playerid)
{
	return ShowPlayerDialog(playerid, BUSINESS_ITEM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business > Items", "{FFFFFF}{FFFFFF}Lotto Ticket: $15\nCell Phone: $1000\nMedikit: $100\nJerrycan: $30\nToolbox: $180\nCrowbar: $50\nTaco: $5\nSprunk: $1", "Buy", "Back");
}

stock ShowWeaponsDialog(playerid)
{
	return ShowPlayerDialog(playerid, BUSINESS_WEAPON_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business > Weapons", "{FFFFFF}Desert Eagle: $4000 (100 Ammo)\nCombat Shotgun: $5000 (100 Ammo)\nMP5: $8000 (200 Ammo)\nM4: $10000 (200 Ammo)\nSniper Rifle: $15000 (100 Ammo)", "Buy", "Back");
}

stock GetOwnedBusinessID(playerid)
{
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true && GetPlayerCharacterID(playerid) == BusinessData[i][business_charid])
	 	{
			if(IsPlayerInRangeOfPoint(playerid, 100.0, BusinessData[i][business_intx], BusinessData[i][business_inty], BusinessData[i][business_intz]) && GetPlayerInterior(playerid) == BusinessData[i][business_intinterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][business_intworld]) return i;
		}
	}
	return -1;
}

stock ReturnBusinessID(playerid)
{
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	 	{
			if(IsPlayerInRangeOfPoint(playerid, 100.0, BusinessData[i][business_intx], BusinessData[i][business_inty], BusinessData[i][business_intz]) && GetPlayerInterior(playerid) == BusinessData[i][business_intinterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][business_intworld]) return i;
		}
	}
	return -1;
}

stock GetBusinessCity(houseid)
{
	return BusinessData[houseid][business_city];
}

stock GetBusinessDoor(businessid, &Float:x, &Float:y, &Float:z)
{
	x = BusinessData[businessid][business_extx];
	y = BusinessData[businessid][business_exty];
	z = BusinessData[businessid][business_extz];
	return 1;
}

stock ProcessBusinessPurchase(playerid, price)
{
	foreach(new i : Businesses)
	{
		if(BusinessData[i][business_active] == true)
		{
			if(IsPlayerInRangeOfPoint(playerid, 100.0, BusinessData[i][business_intx], BusinessData[i][business_inty], BusinessData[i][business_intz]) && GetPlayerInterior(playerid) == BusinessData[i][business_intinterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][business_intworld])
			{
				if(BusinessData[i][business_stock] > 0)
				{
					BusinessData[i][business_stock]--;
					BusinessData[i][business_profit] += (price / 8);
					BusinessData[i][business_value] += ReturnBusinessPercent(price, BUSINESS_PROFIT_PERCENT);

					if(BusinessData[i][business_charid] == 0)
					{
						new label[64];
		      			format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[i][business_value]);
		      			BusinessData[i][business_name] = label;

		     			UpdateDynamic3DTextLabelText(BusinessData[i][business_label], WHITE, label);
					}

					new query[400];
	    			format(query, sizeof(query), "UPDATE `BUSINESSES` SET `VALUE` = '%i', `STOCK` = '%i', `PROFIT` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_value], BusinessData[i][business_stock], BusinessData[i][business_profit], BusinessData[i][business_name], i);
					database_result = db_query@(server_database, query);
					db_free_result@(database_result);
					break;
				}
			}
		}
	}
	return 1;
}

stock RemoveBusinessOwnerFromDatabase(characterid)
{
	new query[300], label[64];
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true && characterid == BusinessData[i][business_charid])
	 	{
			BusinessData[i][business_charid] = 0;
		  	format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[i][business_value]);
		  	BusinessData[i][business_name] = label;

		  	UpdateDynamic3DTextLabelText(BusinessData[i][business_label], WHITE, label);

		   	DestroyDynamicPickup(BusinessData[i][business_pickup]);
			BusinessData[i][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], -1, -1, -1, 50.0, -1, 0);

			format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_charid], label, i);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		OwnerData[playerid][owner_businessid] = -1;
		OwnerData[playerid][owner_salebusiness] = -1;
		OwnerData[playerid][owner_saleprice] = 0;
		OwnerData[playerid][owner_saleowner] = INVALID_PLAYER_ID;
		OwnerData[playerid][owner_saleto] = INVALID_PLAYER_ID;
		OwnerData[playerid][owner_saleactive] = false;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case BUSINESS_VERIFY_DIALOG:
	    {
	        if(response)
	        {
	        	new query[300], label[64], name[24], businessid = OwnerData[playerid][owner_businessid], price = BusinessData[businessid][business_value];

	        	BusinessData[businessid][business_charid] = GetPlayerCharacterID(playerid);

	        	GetPlayerName(playerid, name, sizeof(name));
		     	format(label, sizeof(label), "%s's Business", name);
		      	BusinessData[businessid][business_name] = label;

		     	UpdateDynamic3DTextLabelText(BusinessData[businessid][business_label], WHITE, label);

		     	DestroyDynamicPickup(BusinessData[businessid][business_pickup]);
		     	BusinessData[businessid][business_pickup] = CreateDynamicPickup(1272, 1, BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], -1, -1, -1, 50.0, -1, 0);

				format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_charid], label, businessid);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

		     	GivePlayerMoney(playerid, -price);

				UpdateNearbyCommercialValue(businessid);

		     	return SendClientMessage(playerid, WHITE, "SERVER: You have successfully purchased the business.");
	        }
	        return 1;
	    }
		case BUSINESS_VALUE_DIALOG:
	    {
	        if(response)
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
		case BUSINESS_PROFIT_DIALOG:
	    {
	    	if(response)
	    	{
	    		new query[300], string[128], businessid = OwnerData[playerid][owner_businessid], profit = BusinessData[businessid][business_profit];
	    		if(profit <= 0) return SendClientMessage(playerid, RED, "ERROR: You do not have any profit to withdraw.");

	    		GivePlayerMoney(playerid, profit);
	    		BusinessData[businessid][business_profit] = 0;

	    		format(query, sizeof(query), "UPDATE `BUSINESSES` SET `PROFIT` = '%i' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_stock], businessid);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				format(string, sizeof(string), "SERVER: You have successfully withdrawn $%i in profit.", profit);
				return SendClientMessage(playerid, WHITE, string);
	    	}
	        else
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
		case BUSINESS_STOCK_DIALOG:
	    {
	    	if(response)
	    	{
	    		new string[128];
	    		format(string, sizeof(string), "{FFFFFF}How much stock would you like to order? (Price: $%i/Stock)", STOCK_PRICE);
	    		return ShowPlayerDialog(playerid, BUSINESS_ORDER_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Business Menu > Order", string, "Enter", "Back");
	    	}
	        else
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
		case BUSINESS_ORDER_DIALOG:
	    {
	    	if(response)
	    	{
	    		new query[300], string[128], businessid = OwnerData[playerid][owner_businessid], current_stock = BusinessData[businessid][business_stock], new_stock = strval(inputtext);
	    		if(!IsNumeric(inputtext)) return SendClientMessage(playerid, RED, "ERROR: You must input a number value.");
	    		if(new_stock < 1 || new_stock > MAX_STOCK)
	    		{
	    			format(string, sizeof(string), "ERROR: You must input a number from: 1-%i", MAX_STOCK);
	    			return SendClientMessage(playerid, RED, string);
	    		}
	    		if((new_stock + current_stock) > MAX_STOCK)
	    		{
	    			format(string, sizeof(string), "ERROR: You cannot store that much stock in your business. (Stock: %i/%i)", current_stock, MAX_STOCK);
	    			return SendClientMessage(playerid, RED, string);
	    		}
	    		if(GetPlayerMoneyEx(playerid) < (new_stock * STOCK_PRICE))
	    		{
	    			format(string, sizeof(string), "ERROR: You don't have enough money to purchase the stock. (Need: $%i)", (new_stock * STOCK_PRICE));
	    			return SendClientMessage(playerid, RED, string);
	    		}

	    		GivePlayerMoney(playerid, -(new_stock * STOCK_PRICE));

	    		BusinessData[businessid][business_stock] += new_stock;

	    		format(query, sizeof(query), "UPDATE `BUSINESSES` SET `STOCK` = '%i' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_stock], businessid);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

	    		format(string, sizeof(string), "SERVER: You have just added to your business stock. (Cost: $%i)", (new_stock * STOCK_PRICE));
	    		return SendClientMessage(playerid, WHITE, string);
	    	}
	        else
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
		case BUSINESS_SELL_DIALOG:
	    {
	    	if(response)
	    	{
	    		new string[128], query[300], label[64], businessid = OwnerData[playerid][owner_businessid], price = (BusinessData[businessid][business_value] / 2);

	    		BusinessData[businessid][business_charid] = 0;
		      	format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[businessid][business_value]);
		      	BusinessData[businessid][business_name] = label;

		     	UpdateDynamic3DTextLabelText(BusinessData[businessid][business_label], WHITE, label);

		      	DestroyDynamicPickup(BusinessData[businessid][business_pickup]);
				BusinessData[businessid][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], -1, -1, -1, 50.0, -1, 0);

				format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_charid], label, businessid);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				GivePlayerMoney(playerid, price);

				format(string, sizeof(string), "SERVER: You have successfully sold the business for: $%i", price);
				return SendClientMessage(playerid, WHITE, string);
	    	}
	        else
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
		case BUSINESS_MENU_DIALOG:
	    {
	        if(response)
	        {
	        	switch(listitem)
	        	{
	        		case 0://Current Value
	        		{
	        			new string[128], businessid = OwnerData[playerid][owner_businessid];
						format(string, sizeof(string), "{FFFFFF}Current Value: $%i (Sell Price: $%i)", BusinessData[businessid][business_value], (BusinessData[businessid][business_value] / 2));
						return ShowPlayerDialog(playerid, BUSINESS_VALUE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business Menu > Value", string, "Back", "");
	        		}
	        		case 1://Available Profit
	        		{
	        			new string[128], businessid = OwnerData[playerid][owner_businessid];
						format(string, sizeof(string), "{FFFFFF}Available Profit: $%i", BusinessData[businessid][business_profit]);
						return ShowPlayerDialog(playerid, BUSINESS_PROFIT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business Menu > Profit", string, "Withdraw", "Back");
	        		}
	        		case 2://Total Stock
	        		{
	        			new string[128], businessid = OwnerData[playerid][owner_businessid];
						format(string, sizeof(string), "{FFFFFF}Total Stock: %i/%i", BusinessData[businessid][business_stock], MAX_STOCK);
						return ShowPlayerDialog(playerid, BUSINESS_STOCK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Business Menu > Stock", string, "Order", "Back");
	        		}
	        		case 3://Change Name
	        		{
						return ShowPlayerDialog(playerid, BUSINESS_NAME_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Business Menu > Name", "{FFFFFF}Please enter a new name for your business below:", "Change", "Back");
	        		}
	        		case 4://Sell Business
	        		{
	        			new string[128], businessid = OwnerData[playerid][owner_businessid];
						format(string, sizeof(string), "{FFFFFF}Are you sure you want to sell your business for: $%i?", (BusinessData[businessid][business_value] / 2));
						return ShowPlayerDialog(playerid, BUSINESS_SELL_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Business Menu > Sell", string, "Sell", "Back");
	        		}
	        	}
	        }
	    }
	    case BUSINESS_NAME_DIALOG:
	    {
	        if(response)
	        {
	        	new query[300], name[64], string[200], businessid = OwnerData[playerid][owner_businessid];
	        	if(strlen(inputtext) < 2 || strlen(inputtext) > 64) return SendClientMessage(playerid, RED, "ERROR: Your business name must be from 2-64 characters long.");

	        	format(name, sizeof(name), "%s", inputtext);
	        	BusinessData[businessid][business_name] = name;

				format(query, sizeof(query), "UPDATE `BUSINESSES` SET `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_name], businessid);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

		     	UpdateDynamic3DTextLabelText(BusinessData[businessid][business_label], WHITE, name);
		     	format(string, sizeof(string), "SERVER: You have changed your business name to: %s", BusinessData[businessid][business_name]);
	        	return SendClientMessage(playerid, WHITE, string);
	        }
	        else
	        {
	        	ShowMenuDialog(playerid);
	        }
	        return 1;
	    }
	    case BUSINESS_MAIN_DIALOG:
	    {
	        if(response)
	        {
	        	switch(listitem)
	        	{
	        		case 0://Items
	        		{
	        			return ShowItemsDialog(playerid);
	        		}
	        		case 1://Weapons
	        		{
	        			return ShowWeaponsDialog(playerid);
	        		}
	        	}
	        }
	        return 1;
	    }
	    case BUSINESS_WEAPON_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Desert Eagle: $4000 (100 Ammo)
					{
						if(GetPlayerMoneyEx(playerid) < 4000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						GivePlayerMoney(playerid, -4000);
						ProcessBusinessPurchase(playerid, 4000);

						GivePlayerWeapon(playerid, 24, 100);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowWeaponsDialog(playerid);
					}
					case 1://Combat Shotgun: $5000 (100 Ammo)
					{
						if(GetPlayerMoneyEx(playerid) < 5000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						GivePlayerMoney(playerid, -5000);
						ProcessBusinessPurchase(playerid, 5000);

						GivePlayerWeapon(playerid, 27, 100);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowWeaponsDialog(playerid);
					}
					case 2://MP5: $8000 (200 Ammo)
					{
						if(GetPlayerMoneyEx(playerid) < 8000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						GivePlayerMoney(playerid, -8000);
						ProcessBusinessPurchase(playerid, 8000);

						GivePlayerWeapon(playerid, 29, 200);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowWeaponsDialog(playerid);
					}
					case 3://M4: $10000 (200 Ammo)
					{
						if(GetPlayerMoneyEx(playerid) < 10000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						GivePlayerMoney(playerid, -10000);
						ProcessBusinessPurchase(playerid, 10000);

						GivePlayerWeapon(playerid, 31, 200);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowWeaponsDialog(playerid);
					}
					case 4://Sniper Rifle: $15000 (100 Ammo)
					{
						if(GetPlayerMoneyEx(playerid) < 15000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this item.");

						GivePlayerMoney(playerid, -15000);
						ProcessBusinessPurchase(playerid, 15000);

						GivePlayerWeapon(playerid, 34, 100);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowWeaponsDialog(playerid);
					}
				}
			}
			else
			{
				return ShowBusinessDialog(playerid);
			}
			return 1;
		}
	    case BUSINESS_ITEM_DIALOG:
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
						ProcessBusinessPurchase(playerid, 15);

						LottoData[playerid][lotto_number1] = (random(98) + 1);
						LottoData[playerid][lotto_number2] = (random(98) + 1);
						LottoData[playerid][lotto_number3] = (random(98) + 1);
						LottoData[playerid][lotto_number4] = (random(98) + 1);
						LottoData[playerid][lotto_number5] = (random(98) + 1);
						LottoData[playerid][lotto_number6] = (random(98) + 1);

						SaveLottoData(playerid);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 1000);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 100);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 30);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 180);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 50);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 5);

						return ShowItemsDialog(playerid);
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
						ProcessBusinessPurchase(playerid, 1);

						return ShowItemsDialog(playerid);
					}
				}
			}
			else
			{
				return ShowBusinessDialog(playerid);
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
		foreach(new i : Businesses)
		{
			if(BusinessData[i][business_active] == true)
			{
				if(checkpointid == BusinessData[i][business_entercp])
				{
			   	 	SetPlayerInterior(playerid, BusinessData[i][business_intinterior]);
					SetPlayerVirtualWorld(playerid, BusinessData[i][business_intworld]);
			   	    SetPlayerPos(playerid, BusinessData[i][business_enterx], BusinessData[i][business_entery], BusinessData[i][business_enterz]);
			   	    SetPlayerFacingAngle(playerid, BusinessData[i][business_entera]);
			   	    SetCameraBehindPlayer(playerid);

			   	    if(BusinessData[i][business_charid] == GetPlayerCharacterID(playerid))
			   	    {
			   	    	SendClientMessage(playerid, WHITE, "SERVER: Type /bmenu to access the list of business features.");
			   	   	}
					return 1;
			 	}
			  	else if(checkpointid == BusinessData[i][business_exitcp])
			  	{
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
			   		SetPlayerPos(playerid, BusinessData[i][business_exitx], BusinessData[i][business_exity], BusinessData[i][business_exitz]);
			   	 	SetPlayerFacingAngle(playerid, BusinessData[i][business_exita]);
			  	 	return SetCameraBehindPlayer(playerid);
			  	}
			  	else if(checkpointid == BusinessData[i][business_countercp])
			  	{
			  		return ShowBusinessDialog(playerid);
			  	}
		 	}
	 	}
 	}
	return 1;
}

//Player Commands
YCMD:bmenu(playerid, params[], help)
{
	new businessid = GetOwnedBusinessID(playerid);
	if(businessid == -1) return SendClientMessage(playerid, RED, "ERROR: You must be inside a business you own to use this command.");
	OwnerData[playerid][owner_businessid] = businessid;
	return ShowMenuDialog(playerid);
}

YCMD:buybusiness(playerid, params[], help)
{
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		    if(IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz]))
		  	{
		  		new string[300], count = GetOwnedBusinessCount(playerid);
		  		if(GetPlayerVIP(playerid))
				{
				  	if(count >= MAX_VIP_BUSINESSES)
				  	{
				  		format(string, sizeof(string), "ERROR: You can only own a max of x%i business(es) at a time, sell one first.", MAX_VIP_BUSINESSES);
				  		return SendClientMessage(playerid, RED, string);
				  	}
				}
				else 
				{
					if(count >= MAX_PLAYER_BUSINESSES)
					{
				  		format(string, sizeof(string), "ERROR: You can only own a max of x%i business(es) at a time, sell one first.", MAX_PLAYER_BUSINESSES);
				  		return SendClientMessage(playerid, RED, string);
					}
				}

		  		if(BusinessData[i][business_charid] != 0) return SendClientMessage(playerid, RED, "ERROR: This business is not for sale.");
		  		if(GetPlayerMoneyEx(playerid) < BusinessData[i][business_value]) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this business.");

		  		OwnerData[playerid][owner_businessid] = i;

		   		format(string, sizeof(string), "{FFFFFF}Are you sure you want to buy this business for $%i?", BusinessData[i][business_value]);
		  		return ShowPlayerDialog(playerid, BUSINESS_VERIFY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Verify Purchase", string, "Yes", "No");
		  	}
		}
	}
	return 1;
}

YCMD:sellbusiness(playerid, params[], help)
{
	new Float:pos[3], string[300], targetid, price, businessid = GetOwnedBusinessID(playerid), name[24];
	if(businessid == -1) return SendClientMessage(playerid, RED, "ERROR: You must be inside a business you own to sell it.");
	if(sscanf(params, "ui", targetid, price)) return SendClientMessage(playerid, RED, "USAGE: /sellbusiness [player] [price]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot sell your business to yourself.");
	if(price < 1) return SendClientMessage(playerid, RED, "ERROR: The sale price must be greater than 0.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if(!IsPlayerInRangeOfPoint(targetid, 10.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You must be within 10 metres of the player to use this command.");

	new count = GetOwnedBusinessCount(targetid);
	if(GetPlayerVIP(targetid))
	{
		if(count >= MAX_VIP_BUSINESSES)
		{
			format(string, sizeof(string), "ERROR: That player already owns a maximum of x%i business(es).", MAX_VIP_BUSINESSES);
			return SendClientMessage(playerid, RED, string);
		}
	}
	else 
	{
		if(count >= MAX_PLAYER_BUSINESSES)
		{
			format(string, sizeof(string), "ERROR: That player already owns a maximum of x%i business(es).", MAX_PLAYER_BUSINESSES);
			return SendClientMessage(playerid, RED, string);
		}
	}
	
	OwnerData[targetid][owner_salebusiness] = businessid;
	OwnerData[targetid][owner_saleprice] = price;
	OwnerData[targetid][owner_saleowner] = playerid;

	OwnerData[targetid][owner_saleactive] = true;
	
	OwnerData[playerid][owner_saleto] = targetid;
	
	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have offered %s your business for $%i. Please wait for their response.", name, price);
	SendClientMessage(playerid, YELLOW, string);
	
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: %s has offered you their business for $%i. Type /acceptbusiness or /declinebusiness to respond.", name, price);
	return SendClientMessage(targetid, YELLOW, string);
}

YCMD:acceptbusiness(playerid, params[], help)
{
	new Float:pos[3], query[300], string[128], label[64], name[24], businessid = OwnerData[playerid][owner_salebusiness], price = OwnerData[playerid][owner_saleprice], targetid = OwnerData[playerid][owner_saleowner];
	if(OwnerData[playerid][owner_saleactive] == false) return SendClientMessage(playerid, RED, "ERROR: You have not been offered any businesses to purchase.");

	if(targetid == INVALID_PLAYER_ID)
	{
		OwnerData[playerid][owner_saleactive] = false;
		return SendClientMessage(playerid, ORANGE, "NOTICE: The owner of the business has recently disconnected.");
	}
	if(OwnerData[targetid][owner_saleto] != playerid)
	{
		OwnerData[playerid][owner_saleactive] = false;
		return SendClientMessage(playerid, ORANGE, "NOTICE: The owner of the business has offered it to someone else.");
	}
	if(GetPlayerMoneyEx(playerid) < OwnerData[playerid][owner_saleprice]) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to accept the offer.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if(!IsPlayerInRangeOfPoint(targetid, 10.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You must be within 10 metres of the player to use this command.");
	
	GivePlayerMoney(playerid, -price);

	GivePlayerMoney(targetid, price);

	BusinessData[businessid][business_charid] = GetPlayerCharacterID(playerid);
	
	UpdateNearbyCommercialValue(businessid);
	
	OwnerData[playerid][owner_saleactive] = false;
	OwnerData[targetid][owner_saleto] = INVALID_PLAYER_ID;

	GetPlayerName(playerid, name, sizeof(name));
	format(label, sizeof(label), "%s's Business", name);
	BusinessData[businessid][business_name] = label;

	UpdateDynamic3DTextLabelText(BusinessData[businessid][business_label], WHITE, label);

	format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[businessid][business_charid], BusinessData[businessid][business_name], businessid);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have successfully sold your house to %s.", name);
	SendClientMessage(targetid, YELLOW, string);

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have successfully purchased the house off %s.", name);
	SendClientMessage(playerid, YELLOW, string);
	return 1;
}

YCMD:declinebusiness(playerid, params[], help)
{
	new Float:pos[3], string[128], name[24], targetid = OwnerData[playerid][owner_saleowner];
	if(OwnerData[playerid][owner_saleactive] == false) return SendClientMessage(playerid, RED, "ERROR: You have not been offered any businesses to decline.");
	
	if(targetid == INVALID_PLAYER_ID)
	{
		OwnerData[playerid][owner_saleactive] = false;
		return SendClientMessage(playerid, ORANGE, "NOTICE: The owner of the business has recently disconnected.");
	}
	if(OwnerData[targetid][owner_saleto] != playerid)
	{
		OwnerData[playerid][owner_saleactive] = false;
		return SendClientMessage(playerid, ORANGE, "NOTICE: The owner of the business has offered it to someone else.");
	}

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerName(playerid, name, sizeof(name));

	if(!IsPlayerInRangeOfPoint(targetid, 10.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You must be within 10 metres of the player to use this command.");

	OwnerData[playerid][owner_saleactive] = false;
	OwnerData[targetid][owner_saleto] = INVALID_PLAYER_ID;

	format(string, sizeof(string), "NOTICE: %s has declined your offer for the business.", name);
	SendClientMessage(targetid, ORANGE, string);

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have declined %s's offer for the business.", name);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}

YCMD:createbusiness(playerid, params[], help)
{
	new businessid = GetFreeBusinessSlot(), Float:pos[4], query[700], city[4], label[64];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	if(sscanf(params, "s[4]", city)) return SendClientMessage(playerid, RED, "USAGE: /createbusiness [city]");
	if(businessid == -1) return SendClientMessage(playerid, RED, "ERROR: You have reached the max amount of businesses the server can have, increase MAX_BUSINESSES in the script.");
	if(GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, RED, "ERROR: You cannot create businesses inside interiors.");

	if(!strcmp(city, "ls", true))
	{
		BusinessData[businessid][business_city] = LOS_SANTOS;
	}
	else if(!strcmp(city, "sf", true))
	{
		BusinessData[businessid][business_city] = SAN_FIERRO;
	}
	else if(!strcmp(city, "lv", true))
	{
		BusinessData[businessid][business_city] = LAS_VENTURAS;
	}
	else return SendClientMessage(playerid, RED, "ERROR: The city must be either: ls/sf/lv");

	BusinessData[businessid][business_value] = (random(250000) + 250000);

	BusinessData[businessid][business_intx] = -27.3175;
	BusinessData[businessid][business_inty] = -31.7615;
	BusinessData[businessid][business_intz] = 1003.5573;
		
	BusinessData[businessid][business_enterx] = -27.3494;
	BusinessData[businessid][business_entery] = -29.9550;
	BusinessData[businessid][business_enterz] = 1003.5573;
	BusinessData[businessid][business_entera] = 0.7246;
		
	BusinessData[businessid][business_intinterior] = 4;
	BusinessData[businessid][business_intworld] = (businessid + 100);
	
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	
	BusinessData[businessid][business_charid] = 0;
	BusinessData[businessid][business_stock] = 0;
	BusinessData[businessid][business_profit] = 0;
	BusinessData[businessid][business_extx] = pos[0];
	BusinessData[businessid][business_exty] = pos[1];
	BusinessData[businessid][business_extz] = pos[2];
	
	GetXYBehindPlayer(playerid, pos[0], pos[1], 2.0);
	
	BusinessData[businessid][business_exitx] = pos[0];
	BusinessData[businessid][business_exity] = pos[1];
	BusinessData[businessid][business_exitz] = pos[2];
	BusinessData[businessid][business_exita] = (pos[3] + 180);
	
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	Iter_Add(Businesses, businessid);

	format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[businessid][business_value]);

	BusinessData[businessid][business_clerk] = CreateDynamicActor(65, -30.8971, -30.7111, 1003.5573, 359.4400, true, 100.0, BusinessData[businessid][business_intworld], BusinessData[businessid][business_intinterior], -1, 50.0, -1, 0);
	
	BusinessData[businessid][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], -1, -1, -1, 50.0, -1, 0);

	BusinessData[businessid][business_label] = CreateDynamic3DTextLabel(label, WHITE, BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 10.0);
	
	BusinessData[businessid][business_entercp] = CreateDynamicCP(BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], 1.0, 0, 0, -1, 4.0);
	BusinessData[businessid][business_exitcp] = CreateDynamicCP(BusinessData[businessid][business_intx], BusinessData[businessid][business_inty], BusinessData[businessid][business_intz], 1.0, BusinessData[businessid][business_intworld], BusinessData[businessid][business_intinterior], -1, 4.0);

	BusinessData[businessid][business_countercp] = CreateDynamicCP(-30.8866, -29.0168, 1003.5573, 1.0, BusinessData[businessid][business_intworld], BusinessData[businessid][business_intinterior], -1, 4.0);

	format(query, sizeof(query), "INSERT INTO `BUSINESSES` (`BUSINESS_ID`, `CHARACTER_ID`, `NAME`, `CITY`, `VALUE`, `STOCK`, `PROFIT`, `EXTX`, `EXTY`, `EXTZ`, `INTX`, `INTY`, `INTZ`, `ENTERX`, `ENTERY`, `ENTERZ`, `ENTERA`, `EXITX`, `EXITY`, `EXITZ`, `EXITA`, `INTINTERIOR`, `INTWORLD`) VALUES ('%i', '%i', '%q', '%i', '%i', '%i', '%i', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%i', '%i')",
	businessid, BusinessData[businessid][business_charid], label, BusinessData[businessid][business_city], BusinessData[businessid][business_value], BusinessData[businessid][business_stock], BusinessData[businessid][business_profit], BusinessData[businessid][business_extx], BusinessData[businessid][business_exty], BusinessData[businessid][business_extz], BusinessData[businessid][business_intx], BusinessData[businessid][business_inty], BusinessData[businessid][business_intz],
	BusinessData[businessid][business_enterx], BusinessData[businessid][business_entery], BusinessData[businessid][business_enterz], BusinessData[businessid][business_entera], BusinessData[businessid][business_exitx], BusinessData[businessid][business_exity], BusinessData[businessid][business_exitz], BusinessData[businessid][business_exita], BusinessData[businessid][business_intinterior], BusinessData[businessid][business_intworld]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	
	BusinessData[businessid][business_active] = true;
	return 1;
}

YCMD:deletebusiness(playerid, params[], help)
{
	new query[128];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		    if(IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz]))
		  	{
				DestroyDynamicActor(BusinessData[i][business_clerk]);
				DestroyDynamic3DTextLabel(BusinessData[i][business_label]);
				DestroyDynamicPickup(BusinessData[i][business_pickup]);
				DestroyDynamicCP(BusinessData[i][business_entercp]);
				DestroyDynamicCP(BusinessData[i][business_exitcp]);

				Iter_Remove(Businesses, i);

				format(query, sizeof(query), "DELETE FROM `BUSINESSES` WHERE `BUSINESS_ID` = '%i'", i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				BusinessData[i][business_active] = false;
				return 1;
		    }
	    }
	}
	return SendClientMessage(playerid, RED, "ERROR: You must be within 5 metres of a business entrance to delete it.");
}

YCMD:deleteallbusinesses(playerid, params[], help)
{
	new query[128];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
	    	DestroyDynamicActor(BusinessData[i][business_clerk]);
			DestroyDynamic3DTextLabel(BusinessData[i][business_label]);
			DestroyDynamicPickup(BusinessData[i][business_pickup]);
			DestroyDynamicCP(BusinessData[i][business_entercp]);
			DestroyDynamicCP(BusinessData[i][business_exitcp]);

			Iter_Remove(Businesses, i);

			format(query, sizeof(query), "DELETE FROM `BUSINESSES` WHERE `BUSINESS_ID` = '%i'", i);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			BusinessData[i][business_active] = false;
	    }
	}
	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully deleted all businesses.");
}

YCMD:removebusinessowner(playerid, params[], help)
{
	new query[400], label[64];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		    if(IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz]))
		  	{
		      	BusinessData[i][business_charid] = 0;
		      	format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[i][business_value]);
		      	BusinessData[i][business_name] = label;

		     	UpdateDynamic3DTextLabelText(BusinessData[i][business_label], WHITE, label);

		      	DestroyDynamicPickup(BusinessData[i][business_pickup]);
				BusinessData[i][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], -1, -1, -1, 50.0, -1, 0);

				format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_charid], label, i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully removed the business owner.");
			}
		}
	}
	return SendClientMessage(playerid, RED, "ERROR: You must be within 5 metres of a business entrance to remove the owner.");
}

YCMD:removeallbusinessowners(playerid, params[], help)
{
	new query[400], label[64];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		  	BusinessData[i][business_charid] = 0;
			format(label, sizeof(label), "4-Sale: $%i\nType /buybusiness", BusinessData[i][business_value]);
		 	BusinessData[i][business_name] = label;

		 	UpdateDynamic3DTextLabelText(BusinessData[i][business_label], WHITE, label);

		 	DestroyDynamicPickup(BusinessData[i][business_pickup]);
			BusinessData[i][business_pickup] = CreateDynamicPickup(1273, 1, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz], -1, -1, -1, 50.0, -1, 0);

			format(query, sizeof(query), "UPDATE `BUSINESSES` SET `CHARACTER_ID` = '%i', `NAME` = '%q' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_charid], label, i);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
	}
	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully removed all business owners.");
}

YCMD:resetbusinessprice(playerid, params[], help)
{
	new query[300];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		    if(IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][business_extx], BusinessData[i][business_exty], BusinessData[i][business_extz]))
		  	{
				BusinessData[i][business_value] = (random(250000) + 250000);

				format(query, sizeof(query), "UPDATE `BUSINESSES` SET `VALUE` = '%i' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_value], i);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully reset the business's starting price.");
		    }
	    }
	}
	return SendClientMessage(playerid, RED, "ERROR: You must be within 5 metres of a house to reset it's price.");
}

YCMD:resetallbusinessprices(playerid, params[], help)
{
	new query[300];
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	foreach(new i : Businesses)
	{
	    if(BusinessData[i][business_active] == true)
	    {
		    BusinessData[i][business_value] = (random(250000) + 250000);

			format(query, sizeof(query), "UPDATE `BUSINESSES` SET `VALUE` = '%i' WHERE `BUSINESS_ID` = '%i'", BusinessData[i][business_value], i);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
	    }
	}
	return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully reset all business starting prices.");
}
