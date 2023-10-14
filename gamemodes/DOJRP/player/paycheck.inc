#include <YSI_Coding\y_hooks>

stock ReturnTaxPercent(amount, percent)
{
	return (amount / 100 * percent);
}

stock ProcessPlayerTaxes(playerid, income)
{
	new income_tax = ReturnTaxPercent(income, INCOME_TAX_PERCENT);
	new wealth_tax = ReturnTaxPercent(GetPlayerMoneyEx(playerid), WEALTH_TAX_PERCENT);
	new total_tax = (income_tax + wealth_tax);
	
	GivePlayerMoney(playerid, -total_tax);

	new string[128];
	format(string, sizeof(string), "NOTICE: You have paid $%i in income and wealth taxes.", total_tax);
	return SendClientMessage(playerid, ORANGE, string);
}

task OnPlayerGetPaid[3600000]()
{
	new string[128], pay = MAX_UNEMPLOYED_PAYCHECK;
	foreach(new i : Player)
	{
	    if(IsPlayerLogged(i))
	    {
	    	new job = GetPlayerJob(i);
	    	if(job == POLICE_JOB)
	    	{
	    		new high = (MAX_POLICE_PAYCHECK - (MAX_POLICE_PAYCHECK / 2)), low = (MAX_POLICE_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Officer)", pay);
	    	}
	    	else if(job == CIA_JOB)
	    	{
	    		new high = (MAX_CIA_PAYCHECK - (MAX_CIA_PAYCHECK / 2)), low = (MAX_CIA_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Agent)", pay);
	    	}
	    	else if(job == ARMY_JOB)
	    	{
	    		new high = (MAX_ARMY_PAYCHECK - (MAX_ARMY_PAYCHECK / 2)), low = (MAX_ARMY_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Soldier)", pay);
	    	}
	    	else if(job == EMS_JOB)
	    	{
	    		new high = (MAX_EMS_PAYCHECK - (MAX_EMS_PAYCHECK / 2)), low = (MAX_EMS_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Paramedic)", pay);
	    	}
	    	else if(job == FIRE_JOB)
	    	{
	    		new high = (MAX_FIRE_PAYCHECK - (MAX_FIRE_PAYCHECK / 2)), low = (MAX_FIRE_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Firefighter)", pay);
	    	}
	    	else if(job == MINER_JOB)
	    	{
	    		new high = (MAX_MINER_PAYCHECK - (MAX_MINER_PAYCHECK / 2)), low = (MAX_MINER_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Miner)", pay);
	    	}
	    	else if(job == PILOT_JOB)
	    	{
	    		new high = (MAX_PILOT_PAYCHECK - (MAX_PILOT_PAYCHECK / 2)), low = (MAX_PILOT_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Pilot)", pay);
	    	}
	    	else if(job == TRUCKER_JOB)
	    	{
	    		new high = (MAX_TRUCKER_PAYCHECK - (MAX_TRUCKER_PAYCHECK / 2)), low = (MAX_TRUCKER_PAYCHECK / 2);
	    		pay = (random(high) + low);

	    		format(string, sizeof(string), "PAYCHECK: You have received your paycheck: $%i (Trucker)", pay);
	    	}
	    	else
	    	{
	    		new high = (MAX_UNEMPLOYED_PAYCHECK - (MAX_UNEMPLOYED_PAYCHECK / 2)), low = (MAX_UNEMPLOYED_PAYCHECK / 2);
		   		pay = (random(high) + low);

		    	format(string, sizeof(string), "PAYCHECK: You have received your welfare check: $%i (Unemployed)", pay);
	    	}

	    	GivePlayerMoney(i, pay);

	    	SendClientMessage(i, YELLOW, string);

	    	ProcessPlayerTaxes(i, pay);
	    }
	}
	return 1;
}
