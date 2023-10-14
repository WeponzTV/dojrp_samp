#include <YSI_Coding\y_hooks>

stock SetPlayerWantedLevelEx(playerid, level)
{			
	if(level > 0)
	{
		if(level >= 1 && level <= 3)
		{
			SetPlayerColor(playerid, YELLOW);
		}
		else
		{
			SetPlayerColor(playerid, RED);
		}
	}
	else
	{
		SetPlayerColor(playerid, WHITE);
	}
	return SetPlayerWantedLevel(playerid, level);
}

task OnPlayerLoseWanted[90000]()
{
	foreach(new i : Player)
	{
	    if(IsPlayerSpawned(i) && !IsPlayerInjured(i) && GetDutyStatus(i) == false && GetCameraStatus(i) == false && GetPlayerJob(i) == CIVILIAN_JOB && GetPlayerWantedLevel(i) > 0)
		{
			if(!IsPlayerRobbing(i) && !IsPlayerEvading(i) && !IsPlayerCracking(i, CALIGULAS_CASINO) && !IsPlayerCracking(i, FOUR_DRAGONS_CASINO))
			{
				if(GetPlayerWantedLevel(i) > 6) { SetPlayerWantedLevel(i, 6); }

				SetPlayerWantedLevel(i, GetPlayerWantedLevel(i) - 1);
					
				if(GetPlayerWantedLevel(i) >= 1 && GetPlayerWantedLevel(i) <= 3)
				{
					SetPlayerColor(i, YELLOW);
				}
				else if(GetPlayerWantedLevel(i) >= 4)
				{
					SetPlayerColor(i, RED);
				}
				else
				{
					SetPlayerColor(i, WHITE);
				}
			}
		}
	}
	return 1;
}
