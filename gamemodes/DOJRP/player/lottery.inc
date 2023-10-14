#include <YSI_Coding\y_hooks>

enum lotto_data
{
	lotto_number1,
	lotto_number2,
	lotto_number3,
	lotto_number4,
	lotto_number5,
	lotto_number6
};
new LottoData[MAX_PLAYERS][lotto_data];

stock SaveLottoData(playerid)
{
	new query[300], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT * FROM `LOTTO` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `LOTTO` SET `NUMBER1` = '%i', `NUMBER2` = '%i', `NUMBER3` = '%i', `NUMBER4` = '%i', `NUMBER5` = '%i', `NUMBER6` = '%i' WHERE `CHARACTER_ID` = '%i'", 
		LottoData[playerid][lotto_number1], LottoData[playerid][lotto_number2], LottoData[playerid][lotto_number3], LottoData[playerid][lotto_number4], LottoData[playerid][lotto_number5], LottoData[playerid][lotto_number6], id);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `LOTTO` (`CHARACTER_ID`, `NUMBER1`, `NUMBER2`, `NUMBER3`, `NUMBER4`, `NUMBER5`, `NUMBER6`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		id, LottoData[playerid][lotto_number1], LottoData[playerid][lotto_number2], LottoData[playerid][lotto_number3], LottoData[playerid][lotto_number4], LottoData[playerid][lotto_number5], LottoData[playerid][lotto_number6]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}	
	return 1;
}

stock LoadLottoData(playerid)
{
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `LOTTO` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		LottoData[playerid][lotto_number1] = db_get_field_assoc_int(database_result, "NUMBER1");
		LottoData[playerid][lotto_number2] = db_get_field_assoc_int(database_result, "NUMBER2");
		LottoData[playerid][lotto_number3] = db_get_field_assoc_int(database_result, "NUMBER3");
		LottoData[playerid][lotto_number4] = db_get_field_assoc_int(database_result, "NUMBER4");
		LottoData[playerid][lotto_number5] = db_get_field_assoc_int(database_result, "NUMBER5");
		LottoData[playerid][lotto_number6] = db_get_field_assoc_int(database_result, "NUMBER6");
	}
	db_free_result@(database_result);
	return 1;
}

stock ProcessLottoTicket(playerid)
{
	if(LottoData[playerid][lotto_number1] == 0)
	{
		LottoData[playerid][lotto_number1] = (random(98) + 1);
		LottoData[playerid][lotto_number2] = (random(98) + 1);
		LottoData[playerid][lotto_number3] = (random(98) + 1);
		LottoData[playerid][lotto_number4] = (random(98) + 1);
		LottoData[playerid][lotto_number5] = (random(98) + 1);
		LottoData[playerid][lotto_number6] = (random(98) + 1);
	}
	return 1;
}

stock ShowLottoNumbers(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Your lotto numbers are: %i, %i, %i, %i, %i, %i", LottoData[playerid][lotto_number1], LottoData[playerid][lotto_number2], LottoData[playerid][lotto_number3], LottoData[playerid][lotto_number4], LottoData[playerid][lotto_number5], LottoData[playerid][lotto_number6]);
	return ShowPlayerDialog(playerid, LOTTO_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Lotto Ticket", string, "Close", "");
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		LottoData[playerid][lotto_number1] = 0;
		LottoData[playerid][lotto_number2] = 0;
		LottoData[playerid][lotto_number3] = 0;
		LottoData[playerid][lotto_number4] = 0;
		LottoData[playerid][lotto_number5] = 0;
		LottoData[playerid][lotto_number6] = 0;
	}
	return 1;
}

task OnPlayerWinLotto[2700000]()
{
	new string[128], name[24], winners = 0, correct = 0, n1 = (random(98) + 1), n2 = (random(98) + 1), n3 = (random(98) + 1), n4 = (random(98) + 1), n5 = (random(98) + 1), n6 = (random(98) + 1);
	format(string, sizeof(string), "DRAW: The winning lotto numbers are: %i, %i, %i, %i, %i, %i", n1, n2, n3, n4, n5, n6);
	SendClientMessageToAll(LIGHTGREEN, string);

	foreach(new i : Player)
	{
	    if(IsPlayerLogged(i))
	    {
	    	new slot = CheckInventoryForItem(i, TICKET_MODEL);
	    	if(slot > 0 && LottoData[i][lotto_number1] > 0)
	    	{
	    		if(LottoData[i][lotto_number1] == n1) { correct++; }
	    		else if(LottoData[i][lotto_number2] == n2) { correct++; }
	    		else if(LottoData[i][lotto_number3] == n3) { correct++; }
	    		else if(LottoData[i][lotto_number4] == n4) { correct++; }
	    		else if(LottoData[i][lotto_number5] == n5) { correct++; }
	    		else if(LottoData[i][lotto_number6] == n6) { correct++; }

	    		LottoData[i][lotto_number1] = 0;
	    		LottoData[i][lotto_number2] = 0;
	    		LottoData[i][lotto_number3] = 0;
	    		LottoData[i][lotto_number4] = 0;
	    		LottoData[i][lotto_number5] = 0;
	    		LottoData[i][lotto_number6] = 0;

	    		RemoveItemFromInventory(i, slot, 1, false);
				
				GetPlayerName(i, name, sizeof(name));

	    		if(correct > 0)
	    		{
	    			if(correct == 1)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x1 correct number! (Winnings: $%i)", name, i, ONE_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, ONE_NUMBER_WINNINGS);
	    			}
	    			else if(correct == 2)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x2 correct numbers! (Winnings: $%i)", name, i, TWO_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, TWO_NUMBER_WINNINGS);
	    			}
	    			else if(correct == 3)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x3 correct numbers! (Winnings: $%i)", name, i, THREE_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, THREE_NUMBER_WINNINGS);
	    			}
	    			else if(correct == 4)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x4 correct numbers! (Winnings: $%i)", name, i, FOUR_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, FOUR_NUMBER_WINNINGS);
	    			}
	    			else if(correct == 5)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x5 correct numbers! (Winnings: $%i)", name, i, FIVE_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, FIVE_NUMBER_WINNINGS);
	    			}
	    			else if(correct == 6)
	    			{
	    				format(string, sizeof(string), "WINNER: %s (%i) has won the lottery with x6 correct numbers! (Winnings: $%i MAX WIN)", name, i, SIX_NUMBER_WINNINGS);
	    				GivePlayerMoney(i, SIX_NUMBER_WINNINGS);
	    			}

	    			SendClientMessageToAll(YELLOW, string);

	    			winners++;
	    		}
	    		else
	    		{
	    			SendClientMessage(i, WHITE, "SERVER: You have failed to win the lottery with 0 numbers correct.");
	    		}
	    	}
	    }
	}

	if(winners == 0)
	{
		SendClientMessageToAll(ORANGE, "LOTTO: There were no winners for this lottery, better luck next time.");
	}
	return 1;
}
