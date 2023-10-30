#include <YSI_Coding\y_hooks>

enum bank_data
{
	ls_bank_ent_cp,
	sf_bank_ent_cp,
	lv_bank_ent_cp,
	bank_exit_cp,
	bank_counter_cp
};
new BankData[bank_data];

enum atm_data
{
	//LS
	palomino_creek_atm,
	blueberry_atm,

	//SF
	angel_pine_atm,

	//LV
	fort_carson_atm,
	el_quebrados_atm,
	bayside_atm
};
new ATMData[atm_data];

enum account_data
{
 	account_balance,
 	account_debt,
 	account_transactions,
 	account_withdrawn,
 	account_deposited,
 	account_transferred,
 	account_received,
 	account_loaned,
 	account_repaid,
 	account_sendto,
};
new AccountData[MAX_PLAYERS][account_data];

stock ShowBankDialog(playerid)
{
	return ShowPlayerDialog(playerid, BANK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bank Menu", "{FFFFFF}Balance\nWithdraw\nDeposit\nTransfer\nDebt\nLoans\nStatement", "Select", "Cancel");
}

stock ShowATMDialog(playerid)
{
	return ShowPlayerDialog(playerid, ATM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}ATM Menu", "{FFFFFF}Balance\nWithdraw\nDeposit\nStatement", "Select", "Cancel");
}

stock SaveBankData(playerid)
{
	new query[600];
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `BANK` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `BANK` SET `BALANCE` = '%i', `DEBT` = '%i', `TRANSACTIONS` = '%i', `WITHDRAWN` = '%i', `DEPOSITED` = '%i', `TRANSFERRED` = '%i', `RECEIVED` = '%i', `LOANED` = '%i', `REPAID` = '%i' WHERE `CHARACTER_ID` = '%i'", 
		AccountData[playerid][account_balance], AccountData[playerid][account_debt], AccountData[playerid][account_transactions], AccountData[playerid][account_withdrawn], AccountData[playerid][account_deposited], AccountData[playerid][account_transferred], AccountData[playerid][account_received], AccountData[playerid][account_loaned], AccountData[playerid][account_repaid], GetPlayerCharacterID(playerid));
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);
		
		format(query, sizeof(query), "INSERT INTO `BANK` (`CHARACTER_ID`, `BALANCE`, `DEBT`, `TRANSACTIONS`, `WITHDRAWN`, `DEPOSITED`, `TRANSFERRED`, `RECEIVED`, `LOANED`, `REPAID`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		GetPlayerCharacterID(playerid), AccountData[playerid][account_balance], AccountData[playerid][account_debt], AccountData[playerid][account_transactions], AccountData[playerid][account_withdrawn], AccountData[playerid][account_deposited], AccountData[playerid][account_transferred], AccountData[playerid][account_received], AccountData[playerid][account_loaned], AccountData[playerid][account_repaid]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	db_free_result@(database_result);
	return 1;
}

stock LoadBankData(playerid)
{
	new query[200];
	format(query, sizeof(query), "SELECT * FROM `BANK` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		AccountData[playerid][account_balance] = db_get_field_assoc_int(database_result, "BALANCE");
		AccountData[playerid][account_debt] = db_get_field_assoc_int(database_result, "DEBT");
		AccountData[playerid][account_transactions] = db_get_field_assoc_int(database_result, "TRANSACTIONS");
		AccountData[playerid][account_withdrawn] = db_get_field_assoc_int(database_result, "WITHDRAWN");
		AccountData[playerid][account_deposited] = db_get_field_assoc_int(database_result, "DEPOSITED");
		AccountData[playerid][account_transferred] = db_get_field_assoc_int(database_result, "TRANSFERRED");
		AccountData[playerid][account_received] = db_get_field_assoc_int(database_result, "RECEIVED");
		AccountData[playerid][account_loaned] = db_get_field_assoc_int(database_result, "LOANED");
		AccountData[playerid][account_repaid] = db_get_field_assoc_int(database_result, "REPAID");
	}
	db_free_result@(database_result);
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1481.0503, -1772.3138, 18.7958, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Bank
	CreateDynamicMapIcon(-1581.2631, 867.9344, 7.6953, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Bank
	CreateDynamicMapIcon(2364.8967, 2377.6042, 10.8203, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Bank

	CreateDynamicMapIcon(2302.9165, -10.5198, 26.4844, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Palomino Creek ATM (LS)
	CreateDynamicMapIcon(157.8285, -202.8627, 1.5781, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Blueberry ATM (LS)

	CreateDynamicMapIcon(-2169.7627, -2424.5488, 30.6250, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Angel Pine ATM (SF)

	CreateDynamicMapIcon(-177.6265, 1139.1924, 19.7500, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Fort Carson ATM (LV)
	CreateDynamicMapIcon(-1460.3394, 2592.2424, 55.8359, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//El Quebrados ATM (LV)
	CreateDynamicMapIcon(-2530.6741, 2340.1477, 4.9844, 52, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Bayside ATM (LV)

	BankData[ls_bank_ent_cp] = CreateDynamicCP(1481.0503, -1772.3138, 18.7958, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Bank Entrance
	BankData[sf_bank_ent_cp] = CreateDynamicCP(-1581.2631, 867.9344, 7.6953, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Bank Entrance
	BankData[lv_bank_ent_cp] = CreateDynamicCP(2364.8967, 2377.6042, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Bank Entrance
	BankData[bank_exit_cp] = CreateDynamicCP(2304.6865, -16.1609, 26.7422, 1.0, -1, -1, -1, 5.0, -1, 0);//Bank Exit
	BankData[bank_counter_cp] = CreateDynamicCP(2316.6213, -7.3550, 26.7422, 1.0, -1, -1, -1, 5.0, -1, 0);//Bank Counter

	ATMData[palomino_creek_atm] = CreateDynamicCP(2302.9165, -10.5198, 26.4844, 1.0, -1, -1, -1, 5.0, -1, 0);//Palomino Creek ATM (LS)
	ATMData[blueberry_atm] = CreateDynamicCP(157.8285, -202.8627, 1.5781, 1.0, -1, -1, -1, 5.0, -1, 0);//Blueberry ATM (LS)

	ATMData[angel_pine_atm] = CreateDynamicCP(-2169.7627, -2424.5488, 30.6250, 1.0, -1, -1, -1, 5.0, -1, 0);//Angel Pine ATM (SF)

	ATMData[fort_carson_atm] = CreateDynamicCP(-177.6265, 1139.1924, 19.7500, 1.0, -1, -1, -1, 5.0, -1, 0);//Fort Carson ATM (LV)
	ATMData[el_quebrados_atm] = CreateDynamicCP(-1460.3394, 2592.2424, 55.8359, 1.0, -1, -1, -1, 5.0, -1, 0);//El Quebrados ATM (LV)
	ATMData[bayside_atm] = CreateDynamicCP(-2530.6741, 2340.1477, 4.9844, 1.0, -1, -1, -1, 5.0, -1, 0);//Bayside ATM (LV)

	CreateDynamicObject(2942, 2303.5791000, -10.5000000, 26.1000000, 0.0000000, 0.0000000, 270.0000000, -1, -1, -1, 250.0);//Palomino Creek ATM (LS)
	CreateDynamicObject(2942, 157.8000000, -202.2000000, 1.2000000, 0.0000000, 0.0000000, 0.0000000, -1, -1, -1, 250.0);//Blueberry ATM (LS)

	CreateDynamicObject(2942, -2170.3000000, -2424.1599000, 30.2600000, 0.0000000, 0.0000000, 52.0000000, -1, -1, -1, 250.0);//Angel Pine ATM (SF)

	CreateDynamicObject(2942, -177.6000100, 1138.5300000, 19.3800000, 0.0000000, 0.0000000, 180.0000000, -1, -1, -1, 250.0);//Fort Carson ATM (LV)
	CreateDynamicObject(2942, -1460.3101000, 2591.5801000, 55.4800000, 0.0000000, 0.0000000, 180.0000000, -1, -1, -1, 250.0);//El Quebrados ATM (LV)
	CreateDynamicObject(2942, -2530.7000000, 2340.8101000, 4.6000000, 0.0000000, 0.0000000, 0.0000000, -1, -1, -1, 250.0);//Bayside ATM (LV)
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		AccountData[playerid][account_balance] = 0;
		AccountData[playerid][account_debt] = 0;
		AccountData[playerid][account_transactions] = 0;
		AccountData[playerid][account_withdrawn] = 0;
		AccountData[playerid][account_deposited] = 0;
		AccountData[playerid][account_transferred] = 0;
		AccountData[playerid][account_received] = 0;
		AccountData[playerid][account_loaned] = 0;
		AccountData[playerid][account_repaid] = 0;
		AccountData[playerid][account_sendto] = INVALID_PLAYER_ID;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case ATM_DIALOG:
		{
		    if(response)
		    {
		    	switch(listitem)
		    	{
				    case 0://Balance
				    {
				    	new string[64];
			        	format(string, sizeof(string), "{FFFFFF}Balance: $%i", AccountData[playerid][account_balance]);
			        	return ShowPlayerDialog(playerid, ATM_BAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}ATM Menu > Balance", string, "Close", "Back");
				    }
				    case 1://Withdraw
				    {
				        return ShowPlayerDialog(playerid, ATM_WIT_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}ATM Menu > Withdraw", "{FFFFFF}Please enter the amount you want to withdraw below:", "Withdraw", "Back");
				    }
				    case 2://Deposit
				    {
				        return ShowPlayerDialog(playerid, ATM_DEP_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}ATM Menu > Deposit", "{FFFFFF}Please enter the amount you want to deposit below:", "Deposit", "Back");
				    }
				    case 3://Statement
				    {
				    	new string[300];
				    	format(string, sizeof(string), "{FFFFFF}Deposited: $%i\nWithdrawn: $%i\nTransferred: $%i\nReceived: $%i\nLoaned: $%i\nRepaid: $%i\nTransactions: %i", 
				    	AccountData[playerid][account_deposited], AccountData[playerid][account_withdrawn], AccountData[playerid][account_transferred], AccountData[playerid][account_received], AccountData[playerid][account_loaned], AccountData[playerid][account_repaid], AccountData[playerid][account_transactions]);
				    	return ShowPlayerDialog(playerid, ATM_STA_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}ATM Menu > Statement", string, "Close", "Back");
				    }
				}
		    }
		    return 1;
		}
		case ATM_BAL_DIALOG:
		{
		    if(!response)
		    {
		        ShowATMDialog(playerid);
		    }
			return 1;
		}
		case ATM_WIT_DIALOG:
		{
		    if(response)
		    {
		        new string[128], balance = AccountData[playerid][account_balance];
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        if(strval(inputtext) > balance) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your bank account.");

		        new amount = strval(inputtext);
		        AccountData[playerid][account_balance] -= amount;
		        AccountData[playerid][account_withdrawn] += amount;
		        AccountData[playerid][account_transactions]++;

				GivePlayerMoney(playerid, amount);

				format(string, sizeof(string), "NOTICE: You have successfully withdrawn $%i from your bank account.", amount);
				SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    }
		    else
		    {
		        ShowATMDialog(playerid);
		    }
			return 1;
		}
		case ATM_DEP_DIALOG:
		{
		    if(response)
		    {
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        if(strval(inputtext) > GetPlayerMoneyEx(playerid)) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money on you.");

		        new string[128], amount = strval(inputtext);
		        AccountData[playerid][account_balance] += amount;
		        AccountData[playerid][account_deposited] += amount;
		        AccountData[playerid][account_transactions]++;

				GivePlayerMoney(playerid, -amount);

				format(string, sizeof(string), "NOTICE: You have successfully deposited $%i into your bank account.", amount);
				SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    }
		    else
		    {
		        ShowATMDialog(playerid);
		    }
			return 1;
		}
		case ATM_STA_DIALOG:
		{
			if(!response)
			{
				ShowATMDialog(playerid);
			}
			return 1;
		}
		case BANK_DIALOG:
		{
		    if(response)
		    {
		    	switch(listitem)
		    	{
				    case 0://Balance
				    {
				    	new string[64];
			        	format(string, sizeof(string), "{FFFFFF}Balance: $%i", AccountData[playerid][account_balance]);
			        	return ShowPlayerDialog(playerid, BALANCE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bank Menu > Balance", string, "Close", "Back");
				    }
				    case 1://Withdraw
				    {
				        return ShowPlayerDialog(playerid, WITHDRAW_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Bank Menu > Withdraw", "{FFFFFF}Please enter the amount you want to withdraw below:", "Withdraw", "Back");
				    }
				    case 2://Deposit
				    {
				        return ShowPlayerDialog(playerid, DEPOSIT_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Bank Menu > Deposit", "{FFFFFF}Please enter the amount you want to deposit below:", "Deposit", "Back");
				    }
				    case 3://Transfer
				    {
				        return ShowPlayerDialog(playerid, TRANSFER_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Bank Menu > Transfer", "{FFFFFF}Please enter the id of the player you want to transfer money to:", "Enter", "Back");
				    }
				    case 4://Debt
				    {
				    	new string[64];
				        format(string, sizeof(string), "{FFFFFF}Debt: $%i", AccountData[playerid][account_debt]);
				        return ShowPlayerDialog(playerid, DEBT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bank Menu > Debt", string, "Pay", "Back");
				    }
				    case 5://Loans
				    {
				        return ShowPlayerDialog(playerid, LOANS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bank Menu > Loans", "{FFFFFF}Budget Loan ($500K)\nEconomy Loan ($1M)\nBusiness Loan ($5M)\nInvestment Loan ($10M)", "Apply", "Back");
				    }
				    case 6://Statement
				    {
				    	new string[300];
				    	format(string, sizeof(string), "{FFFFFF}Deposited: $%i\nWithdrawn: $%i\nTransferred: $%i\nReceived: $%i\nLoaned: $%i\nRepaid: $%i\nTransactions: %i", 
				    	AccountData[playerid][account_deposited], AccountData[playerid][account_withdrawn], AccountData[playerid][account_transferred], AccountData[playerid][account_received], AccountData[playerid][account_loaned], AccountData[playerid][account_repaid], AccountData[playerid][account_transactions]);
				    	return ShowPlayerDialog(playerid, STATEMENT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Bank Menu > Statement", string, "Close", "Back");
				    }
				}
		    }
		    return 1;
		}
		case STATEMENT_DIALOG:
		{
			if(!response)
			{
				ShowBankDialog(playerid);
			}
			return 1;
		}
		case TRANSFER_DIALOG:
		{
			if(response)
			{
		        if(!IsNumeric(inputtext)) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");

		        new targetid = strval(inputtext);
				if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
				if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
				if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");
				if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot transfer money to yourself.");
				
				AccountData[playerid][account_sendto] = targetid;

				new string[128], name[24];
				GetPlayerName(targetid, name, sizeof(name));
				format(string, sizeof(string), "{FFFFFF}Please enter the amount you want to transfer to '%s' below:", name);
				return ShowPlayerDialog(playerid, SEND_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Bank Menu > Transfer", string, "Transfer", "Cancel");
			}
			else
			{
				ShowBankDialog(playerid);
			}
			return 1;
		}
		case SEND_DIALOG:
		{
			if(response)
			{
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        
		        new string[128], name[24], targetid = AccountData[playerid][account_sendto], amount = strval(inputtext), balance = AccountData[playerid][account_balance];
		        if(amount > balance) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your bank account.");
				if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: The player has disconnected during transfer.");
		        
		        AccountData[playerid][account_balance] -= amount;
		        AccountData[playerid][account_transferred] += amount;
		        AccountData[playerid][account_transactions]++;

		        AccountData[targetid][account_balance] += amount;
		        AccountData[targetid][account_received] += amount;
		        AccountData[targetid][account_transactions]++;

				GetPlayerName(playerid, name, sizeof(name));
		        format(string, sizeof(string), "NOTICE: %s has just transferred $%i into your bank account.", name, amount);
		        SendClientMessage(targetid, YELLOW, string);

				GetPlayerName(targetid, name, sizeof(name));
		        format(string, sizeof(string), "NOTICE: You have successfully transferred $%i into %s's bank account.", amount, name);
		        SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
			}
			else
			{
				ShowBankDialog(playerid);
			}
			return 1;
		}
		case BALANCE_DIALOG:
		{
		    if(!response)
		    {
		        ShowBankDialog(playerid);
		    }
			return 1;
		}
		case WITHDRAW_DIALOG:
		{
		    if(response)
		    {
		        new string[128], balance = AccountData[playerid][account_balance];
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        if(strval(inputtext) > balance) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your bank account.");

		        new amount = strval(inputtext);
		        AccountData[playerid][account_balance] -= amount;
		        AccountData[playerid][account_withdrawn] += amount;
		        AccountData[playerid][account_transactions]++;

				GivePlayerMoney(playerid, amount);

				format(string, sizeof(string), "NOTICE: You have successfully withdrawn $%i from your bank account.", amount);
				SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    }
		    else
		    {
		        ShowBankDialog(playerid);
		    }
			return 1;
		}
		case DEPOSIT_DIALOG:
		{
		    if(response)
		    {
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        if(strval(inputtext) > GetPlayerMoneyEx(playerid)) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money on you.");

		        new string[128], amount = strval(inputtext);
		        AccountData[playerid][account_balance] += amount;
		        AccountData[playerid][account_deposited] += amount;
		        AccountData[playerid][account_transactions]++;

				GivePlayerMoney(playerid, -amount);

				format(string, sizeof(string), "NOTICE: You have successfully deposited $%i into your bank account.", amount);
				SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    }
		    else
		    {
		        ShowBankDialog(playerid);
		    }
			return 1;
		}
		case DEBT_DIALOG:
		{
		    if(response)
		    {
		    	if(AccountData[playerid][account_debt] == 0) return SendClientMessage(playerid, RED, "ERROR: You don't owe any money to the bank.");
				return ShowPlayerDialog(playerid, PAYOFF_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Bank Menu > Debt", "{FFFFFF}Please enter the amount you want to pay back below:", "Enter", "Back");
			}
		    else
		    {
		        ShowBankDialog(playerid);
		    }
			return 1;
		}
		case PAYOFF_DIALOG:
		{
		    if(response)
		    {
		        new string[128], amount = strval(inputtext);
		        if(!IsNumeric(inputtext) || strlen(inputtext) < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
		        if(strval(inputtext) > GetPlayerMoneyEx(playerid)) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money on you.");
		        if(amount > AccountData[playerid][account_debt]) return SendClientMessage(playerid, RED, "ERROR: You do not owe that much money to the bank.");

		        AccountData[playerid][account_debt] -= amount;
		        AccountData[playerid][account_repaid] += amount;
		        AccountData[playerid][account_transactions]++;

				GivePlayerMoney(playerid, -amount);

				format(string, sizeof(string), "NOTICE: You have successfully payed off $%i of your debt.", amount);
				SendClientMessage(playerid, YELLOW, string);

				return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
		    }
		    else
		    {
		        ShowBankDialog(playerid);
		    }
		    return 1;
		}
		case LOANS_DIALOG:
		{
		    if(response)
		    {
		    	switch(listitem)
		    	{
				    case 0://Budget Loan ($500K)
				    {
						new string[128], amount = 500000, interest = (amount / 8), funds = AccountData[playerid][account_balance], rating = (amount / 2);
						if(AccountData[playerid][account_debt] > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot apply for any more loans until your debt is payed off.");
						if(funds < rating)
						{
							format(string, sizeof(string), "ERROR: You need at least $%i in your bank to apply for a Budget Loan.", rating);
							return SendClientMessage(playerid, RED, string);
						}

						AccountData[playerid][account_debt] += (amount + interest);
		        		AccountData[playerid][account_loaned] += amount;
		        		AccountData[playerid][account_transactions]++;

						GivePlayerMoney(playerid, amount);

						SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully applied for the loan and was approved for $500000.");
						
						return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				    }
				    case 1://Economy Loan ($1M)
				    {
						new string[128], amount = 1000000, interest = (amount / 8), funds = AccountData[playerid][account_balance], rating = (amount / 2);
						if(AccountData[playerid][account_debt] > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot apply for anymore loans until your debt is payed off.");
						if(funds < rating)
						{
							format(string, sizeof(string), "ERROR: You need at least $%i in your bank to apply for an Economy Loan.", rating);
							return SendClientMessage(playerid, RED, string);
						}

						AccountData[playerid][account_debt] += (amount + interest);
		        		AccountData[playerid][account_loaned] += amount;
		        		AccountData[playerid][account_transactions]++;

						GivePlayerMoney(playerid, amount);

						SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully applied for the loan and was approved for $1000000.");
						
						return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				    }
				    case 2://Business Loan ($5M)
				    {
						new string[128], amount = 5000000, interest = (amount / 8), funds = AccountData[playerid][account_balance], rating = (amount / 2);
						if(AccountData[playerid][account_debt] > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot apply for anymore loans until your debt is payed off.");
						if(funds < rating)
						{
							format(string, sizeof(string), "ERROR: You need at least $%i in your bank to apply for a Business Loan.", rating);
							return SendClientMessage(playerid, RED, string);
						}

						AccountData[playerid][account_debt] += (amount + interest);
		        		AccountData[playerid][account_loaned] += amount;
		        		AccountData[playerid][account_transactions]++;

						GivePlayerMoney(playerid, amount);

						SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully applied for the loan and was approved for $5000000.");
						
						return ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				    }
				    case 3://Investment Loan ($10M)
				    {
						new string[128], amount = 10000000, interest = (amount / 8), funds = AccountData[playerid][account_balance], rating = (amount / 2);
						if(AccountData[playerid][account_debt] > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot apply for anymore loans until your debt is payed off.");
						if(funds < rating)
						{
							format(string, sizeof(string), "ERROR: You need at least $%i in your bank to apply for an Investment Loan.", rating);
							return SendClientMessage(playerid, RED, string);
						}

						AccountData[playerid][account_debt] += (amount + interest);
		        		AccountData[playerid][account_loaned] += amount;
		        		AccountData[playerid][account_transactions]++;

						GivePlayerMoney(playerid, amount);

						SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully applied for the loan and was approved for $10000000.");
						
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				    }
				}
			    return 1;
		    }
		    else
		    {
		        ShowBankDialog(playerid);
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
		if(checkpointid == BankData[ls_bank_ent_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 2306.8186, -16.1437, 26.7496);
			SetPlayerFacingAngle(playerid, 269.4367);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BankData[sf_bank_ent_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 2306.8186, -16.1437, 26.7496);
			SetPlayerFacingAngle(playerid, 269.4367);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BankData[lv_bank_ent_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerPos(playerid, 2306.8186, -16.1437, 26.7496);
			SetPlayerFacingAngle(playerid, 269.4367);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == BankData[bank_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS Bank
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1481.0778, -1770.1561, 18.7958);
				SetPlayerFacingAngle(playerid, 359.2755);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//SF Bank
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -1581.1808, 865.5189, 7.5936);
				SetPlayerFacingAngle(playerid, 182.4476);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//LV Bank
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2362.6709, 2377.6509, 10.8203);
				SetPlayerFacingAngle(playerid, 93.8895);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == BankData[bank_counter_cp])
		{
			return ShowBankDialog(playerid);
		}
		else if(checkpointid == ATMData[palomino_creek_atm] || checkpointid == ATMData[blueberry_atm] || checkpointid == ATMData[angel_pine_atm] || checkpointid == ATMData[fort_carson_atm] || checkpointid == ATMData[el_quebrados_atm] || checkpointid == ATMData[bayside_atm])
		{
			return ShowATMDialog(playerid);
		}
	}
	return 1;
}
