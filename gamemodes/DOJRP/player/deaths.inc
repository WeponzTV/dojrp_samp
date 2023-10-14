#include <YSI_Coding\y_hooks>

forward OnPlayerRespawn(playerid);
forward OnPlayerDie(playerid, weaponid);

forward TriggerPlayerDeath(playerid, killerid, weaponid);

enum death_data
{
	death_issuerid,
	death_injuries,
	death_onwounded,
	death_ondeath,
	death_civkills,
	death_lawkills,
	death_emskills,
	death_teamkills,
	bool:death_iswounded,
	bool:death_canaccept,
	bool:death_alert1,
	bool:death_alert2
};
new DeathData[MAX_PLAYERS][death_data];

stock Send911Message(receiver, colour, message[])
{
	foreach(new i : Player)
	{
	    if(GetPlayerJob(i) == receiver)
	  	{
			SendClientMessage(i, colour, message);
	  	}
	}
	return 1;
}

stock CheckForBadKill(playerid, killerid)
{
	new string[128], name[24], killers_job = GetPlayerJob(killerid), players_job = GetPlayerJob(killerid);
	if(killers_job == POLICE_JOB || killers_job == CIA_JOB || killers_job == ARMY_JOB && 
	players_job == PILOT_JOB || players_job == TRUCKER_JOB || players_job == MINER_JOB || players_job == CIVILIAN_JOB && GetPlayerWantedLevel(playerid) < 4)
	{
		DeathData[killerid][death_civkills]++;
		if(DeathData[killerid][death_civkills] > 3)
		{
			GetPlayerName(killerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Killing Innocent Civilians", name, killerid);
			return KickPlayer(killerid);
		}

		format(string, sizeof(string), "WARNING: DO NOT KILL INNOCENT CIVILIANS! (%i/3 Warnings)", DeathData[playerid][death_civkills]);
		SendClientMessage(killerid, RED, string);
	}
	else if(killers_job == FIRE_JOB || killers_job == EMS_JOB || killers_job == PILOT_JOB || killers_job == TRUCKER_JOB || killers_job == MINER_JOB && 
	players_job == PILOT_JOB || players_job == TRUCKER_JOB || players_job == MINER_JOB || players_job == CIVILIAN_JOB)
	{
		DeathData[killerid][death_civkills]++;
		if(DeathData[killerid][death_civkills] > 3)
		{
			GetPlayerName(killerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Killing Civilians", name, killerid);
			return KickPlayer(killerid);
		}

		format(string, sizeof(string), "WARNING: DO NOT KILL CIVILIANS! (%i/3 Warnings)", DeathData[playerid][death_civkills]);
		SendClientMessage(killerid, RED, string);
	}
	else if(killers_job == EMS_JOB || killers_job == FIRE_JOB || killers_job == PILOT_JOB || killers_job == TRUCKER_JOB || killers_job == MINER_JOB && 
	players_job == POLICE_JOB || players_job == CIA_JOB || players_job == ARMY_JOB)
	{
		DeathData[killerid][death_lawkills]++;
		if(DeathData[killerid][death_lawkills] > 3)
		{
			GetPlayerName(killerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Killing Law Enforcement", name, killerid);
			return KickPlayer(killerid);
		}

		format(string, sizeof(string), "WARNING: DO NOT KILL LAW ENFORCEMENT! (%i/3 Warnings)", DeathData[playerid][death_lawkills]);
		SendClientMessage(killerid, RED, string);
	}
	else if(players_job == EMS_JOB || players_job == FIRE_JOB)
	{
		DeathData[killerid][death_emskills]++;
		if(DeathData[killerid][death_emskills] > 3)
		{
			GetPlayerName(killerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Killing Emergency Workers", name, killerid);
			return KickPlayer(killerid);
		}

		format(string, sizeof(string), "WARNING: DO NOT KILL EMERGENCY WORKERS! (%i/3 Warnings)", DeathData[playerid][death_emskills]);
		SendClientMessage(killerid, RED, string);
	}
	else if(killers_job == POLICE_JOB && players_job == POLICE_JOB || 
	killers_job == CIA_JOB && players_job == CIA_JOB || 
	killers_job == ARMY_JOB && players_job == ARMY_JOB)
	{
		DeathData[killerid][death_teamkills]++;
		if(DeathData[killerid][death_teamkills] > 3)
		{
			GetPlayerName(killerid, name, sizeof(name));
			format(string, sizeof(string), "AUTO: %s (%i) has been kicked from the server for: Killing Colleagues", name, killerid);
			return KickPlayer(killerid);
		}

		format(string, sizeof(string), "WARNING: DO NOT KILL YOUR COLLEAGUES! (%i/3 Warnings)", DeathData[playerid][death_teamkills]);
		SendClientMessage(killerid, RED, string);
	}
	return 1;
}

stock OnPlayerWounded(playerid, issuerid, weaponid)
{
	if(IsPlayerInAnyVehicle(playerid) && DeathData[playerid][death_iswounded] == false)
	{
		RemovePlayerFromVehicle(playerid);
	}

	DeathData[playerid][death_iswounded] = true;
	DeathData[playerid][death_issuerid] = issuerid;

	DeathData[playerid][death_injuries]++;
	
	ApplyAnimation(playerid, "WUZI", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PED", "null", 0.0, 0, 0, 0, 0, 0);

	if(DeathData[playerid][death_injuries] < 4)
	{
		SetPlayerHealth(playerid, 2.0);

		ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 1, 1, 1, 1, 0, 1);

		if(DeathData[playerid][death_alert1] == false)
		{
			DeathData[playerid][death_alert1] = true;

			SendClientMessage(playerid, ORANGE, "NOTICE: You have just been wounded, type /call911 or wait 60 seconds to die.");

			DeathData[playerid][death_onwounded] = SetTimerEx("OnPlayerDie", 60000, false, "ii", playerid, weaponid);
		}
	}
	else
	{
		SetPlayerHealth(playerid, 1.0);

		ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 0, 1);

		if(DeathData[playerid][death_alert2] == false)
		{
			DeathData[playerid][death_canaccept] = true;
			DeathData[playerid][death_alert2] = true;

		 	if(DeathData[playerid][death_onwounded] != -1) { KillTimer(DeathData[playerid][death_onwounded]); }

			SendClientMessage(playerid, ORANGE, "NOTICE: You have just died, type /acceptdeath or wait 60 seconds to respawn.");

			DeathData[playerid][death_ondeath] = SetTimerEx("OnPlayerRespawn", 60000, false, "i", playerid);
		}
	}
	return 0;
}

stock ProcessPlayerDeath(playerid, killerid)
{
	if(killerid != INVALID_PLAYER_ID && killerid != playerid)
	{
		CheckForBadKill(playerid, killerid);

		SetPlayerScore(killerid, GetPlayerScore(killerid) + 1);
		SetPlayerStats(killerid, STATS_TYPE_KILLS, GetPlayerStats(killerid, STATS_TYPE_KILLS) + 1);

		if(GetPlayerJob(playerid) == CIVILIAN_JOB && GetPlayerWantedLevel(playerid) >= 4)
		{
			if(GetPlayerJob(killerid) == POLICE_JOB || GetPlayerJob(killerid) == CIA_JOB || GetPlayerJob(killerid) == ARMY_JOB)
			{
				new string[144], officer[24], offender[24];
				GetPlayerName(killerid, officer, sizeof(officer));
				GetPlayerName(playerid, offender, sizeof(offender));

				format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just taken down Suspect %s (%i) at: %s", ReturnPlayerJob(killerid), officer, killerid, offender, playerid, ReturnPlayerLocation(killerid));
				PoliceRadio(ORANGE, string);

				SetPlayerStats(killerid, STATS_TYPE_TAKEDOWNS, GetPlayerStats(killerid, STATS_TYPE_TAKEDOWNS) + 1);
			}
		}
	}

	SetPlayerScore(playerid, GetPlayerScore(playerid) - 1);
	SetPlayerStats(playerid, STATS_TYPE_DEATHS, GetPlayerStats(playerid, STATS_TYPE_DEATHS) + 1);

	new skin = GetPlayerSkin(playerid);
	SetPlayerSkinEx(playerid, skin);

	new hunger = (random(20) + 80), thirst = (random(20) + 80);
	SetPlayerHunger(playerid, hunger);
	SetPlayerThirst(playerid, thirst);
					
	SetPlayerSkin(playerid, GetPlayerSkinEx(playerid));

	if(!GetPlayerVIP(playerid))
	{
		ResetPlayerWeapons(playerid);

		SetPlayerArmourEx(playerid, 0.0);
		SetPlayerArmour(playerid, GetPlayerArmourEx(playerid));
	}
	else
	{
		SetPlayerArmourEx(playerid, 100.0);
		SetPlayerArmour(playerid, GetPlayerArmourEx(playerid));
	}
					
	SetPlayerHealthEx(playerid, 100.0);
	SetPlayerHealth(playerid, GetPlayerHealthEx(playerid));

	if(GetPlayerJob(playerid) == CIVILIAN_JOB)
	{
		SetPlayerWantedLevelEx(playerid, 0);
	}
	else
	{
		SetPlayerColourEx(playerid, GetPlayerJob(playerid));
	}
	return SpawnAtHospital(playerid);
}

stock ResetPlayerInjuries(playerid)
{
	if(DeathData[playerid][death_iswounded] == true)
	{
		DeathData[playerid][death_iswounded] = false;
		DeathData[playerid][death_issuerid] = INVALID_PLAYER_ID;
		DeathData[playerid][death_injuries] = 0;
		ClearAnimations(playerid);
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		DeathData[playerid][death_issuerid] = INVALID_PLAYER_ID;
		DeathData[playerid][death_injuries] = 0;

		DeathData[playerid][death_civkills] = 0;
		DeathData[playerid][death_lawkills] = 0;
		DeathData[playerid][death_emskills] = 0;
		DeathData[playerid][death_teamkills] = 0;

		DeathData[playerid][death_iswounded] = false;
		DeathData[playerid][death_canaccept] = false;
		DeathData[playerid][death_alert1] = false;
		DeathData[playerid][death_alert2] = false;
	}
	return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(issuerid == INVALID_PLAYER_ID || IsPlayerInjured(playerid) || IsPlayerSafe(playerid) || GetDutyStatus(playerid) == false || GetCameraStatus(playerid) == false) return 0;
	
	if(!IsPlayerNPC(playerid) && !IsPlayerNPC(issuerid))
	{
		new Float:health, Float:armour;
	    GetPlayerHealth(playerid, health);
	    GetPlayerArmour(playerid, armour);

		switch(weaponid)
		{
	      	case 0://Fist
	     	{
	         	if(health >= 3.0)
	         	{
	         		new Float:hp = (health - 5.0);
	         		if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            	SetPlayerHealth(playerid, hp);
	     		}
	          	else
	        	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	        	}
	    	}
	      	case 1://Brass Knuckles
	      	{
	         	if(health >= 3.0)
	         	{
	         		new Float:hp = (health - 10.0);
	         		if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            	SetPlayerHealth(playerid, hp);
	     		}
	          	else
	          	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	          	}
	     	}
	     	case 4://Knife
	     	{
				DeathData[playerid][death_injuries] = 4;
	          	OnPlayerWounded(playerid, issuerid, weaponid);
	      	}
	     	case 8, 9://Deadly Melee
	      	{
	          	if(health >= 3.0)
	          	{
	         		new Float:hp = (health - 50.0);
	         		if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            	SetPlayerHealth(playerid, hp);
	         	}
	         	else
	         	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	         	}
	      	}
	      	case 2, 3, 5, 6, 7, 10, 11, 12, 13, 14, 15, 41://Normal Melee
	      	{
	          	if(health >= 3.0)
	         	{
	         		new Float:hp = (health - 15.0);
	         		if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            	SetPlayerHealth(playerid, hp);
	       		}
	         	else
	         	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	          	}
	     	}
	     	case 22, 23, 24://Handguns
	     	{
	           	if(health >= 3.0)
	        	{
	            	if(bodypart == 9)
	            	{
						PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
						PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);

						DeathData[playerid][death_injuries] = 4;
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	            	else
	            	{
	            		if(bodypart == 3 && armour > 0.0)
			     		{
			     			if(weaponid == 24)
			     			{
			            		SetPlayerArmour(playerid, armour - 35.0);
			            	}
			            	else
			            	{
			            		SetPlayerArmour(playerid, armour - 25.0);
			            	}
			     		}
			     		else
			     		{
		     				if(weaponid == 24)
		     				{
		         				new Float:hp = (health - 35.0);
		         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

		            			SetPlayerHealth(playerid, hp);
		            		}
		            		else
		            		{
		         				new Float:hp = (health - 25.0);
		         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

		            			SetPlayerHealth(playerid, hp);
		            		}
	            		}
	            	}
	          	}
	          	else
	         	{
	         		if(bodypart == 9 && DeathData[playerid][death_iswounded] == false)
	            	{
						PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
						PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);
	            		
						DeathData[playerid][death_injuries] = 4;
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	            	else
	            	{
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	         	}
	      	}
	     	case 25, 26, 27://Shotguns
	     	{
	           	if(health >= 3.0)
	        	{
	            	if(bodypart == 3 && armour > 0.0)
			     	{
			     		if(weaponid == 27)
			     		{
			            	SetPlayerArmour(playerid, armour - 50.0);
			          	}
			          	else
			          	{
			            	SetPlayerArmour(playerid, armour - 35.0);
			         	}
			     	}
			     	else
			     	{
		     			if(weaponid == 27)
		     			{
		         			new Float:hp = (health - 50.0);
		         			if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

			            	SetPlayerHealth(playerid, hp);
			          	}
		            	else
		            	{
		         			new Float:hp = (health - 35.0);
		         			if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

		            		SetPlayerHealth(playerid, hp);
		            	}
	            	}
	          	}
	          	else
	         	{
	         		OnPlayerWounded(playerid, issuerid, weaponid);
	         	}
	      	}
	     	case 28, 29, 32://SMGs
	     	{
	           	if(health >= 3.0)
	        	{
	        		if(armour > 0.0 && bodypart == 3)
		     		{
		            	if(weaponid == 29)
			     		{
			            	SetPlayerArmour(playerid, armour - 35.0);
			          	}
			         	else
			         	{
			            	SetPlayerArmour(playerid, armour - 25.0);
			          	}
		     		}
		     		else
		     		{
		     			if(weaponid == 29)
		     			{
	         				new Float:hp = (health - 35.0);
	         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            			SetPlayerHealth(playerid, hp);
	         			}
	         			else
		     			{
	         				new Float:hp = (health - 25.0);
	         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            			SetPlayerHealth(playerid, hp);
	         			}
	         		}
	         	}
	        	else
	        	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	         	}
	     	}
	     	case 30, 31://Assault Rifles
	     	{
	           	if(health >= 3.0)
	        	{
	        		if(armour > 0.0 && bodypart == 3)
		     		{
		            	if(weaponid == 31)
			     		{
			            	SetPlayerArmour(playerid, armour - 40.0);
			          	}
			         	else
			         	{
			            	SetPlayerArmour(playerid, armour - 30.0);
			          	}
		     		}
		     		else
		     		{
		     			if(weaponid == 31)
		     			{
	         				new Float:hp = (health - 40.0);
	         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            			SetPlayerHealth(playerid, hp);
	         			}
	         			else
		     			{
	         				new Float:hp = (health - 30.0);
	         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            			SetPlayerHealth(playerid, hp);
	         			}
	         		}
	         	}
	        	else
	        	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	         	}
	     	}
	     	case 33, 34://Rifles
	     	{
	           	if(health >= 3.0)
	        	{
	            	if(bodypart == 9)
	            	{
						PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
						PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);

						DeathData[playerid][death_injuries] = 4;
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	            	else
	            	{
	            		if(bodypart == 3 && armour > 0.0)
			     		{
			     			if(weaponid == 34)
			     			{
			            		SetPlayerArmour(playerid, armour - 40.0);
			            	}
			            	else
			            	{
			            		SetPlayerArmour(playerid, armour - 30.0);
			            	}
			     		}
			     		else
			     		{
		     				if(weaponid == 34)
		     				{
		         				new Float:hp = (health - 40.0);
		         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

		            			SetPlayerHealth(playerid, hp);
		            		}
		            		else
		            		{
		         				new Float:hp = (health - 30.0);
		         				if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

		            			SetPlayerHealth(playerid, hp);
		            		}
	            		}
	            	}
	          	}
	          	else
	         	{
	         		if(bodypart == 9 && DeathData[playerid][death_iswounded] == false)
	            	{
						PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
						PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);
	            		
						DeathData[playerid][death_injuries] = 4;
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	            	else
	            	{
	            		OnPlayerWounded(playerid, issuerid, weaponid);
	            	}
	         	}
	      	}
	      	default:
	      	{
	          	if(health >= 3.0)
	         	{
	         		new Float:hp = (health - 50.0);
	         		if(hp <= 2.0) return OnPlayerWounded(playerid, issuerid, weaponid);

	            	SetPlayerHealth(playerid, hp);
	          	}
	          	else
	          	{
	            	OnPlayerWounded(playerid, issuerid, weaponid);
	         	}
	        }
	    }
	}
	return 0;
}

public TriggerPlayerDeath(playerid, killerid, weaponid)//Do not hook
{
	DeathData[playerid][death_injuries] = 4;
	return OnPlayerWounded(playerid, killerid, weaponid);
}

public OnPlayerDie(playerid, weaponid)//Do not hook
{
	DeathData[playerid][death_onwounded] = -1;
	DeathData[playerid][death_injuries] = 4;
	return OnPlayerWounded(playerid, DeathData[playerid][death_issuerid], weaponid);
}

public OnPlayerRespawn(playerid)//Do not hook
{
	ProcessPlayerDeath(playerid, DeathData[playerid][death_issuerid]);

	DeathData[playerid][death_ondeath] = -1;
	DeathData[playerid][death_iswounded] = false;
	DeathData[playerid][death_issuerid] = INVALID_PLAYER_ID;
	DeathData[playerid][death_injuries] = 0;
	return SpawnAtHospital(playerid);
}

CMD:acceptdeath(playerid, params[])
{
	if(DeathData[playerid][death_canaccept] == true)
	{
		DeathData[playerid][death_canaccept] = false;

		if(DeathData[playerid][death_ondeath] != -1) { KillTimer(DeathData[playerid][death_ondeath]); }
		return OnPlayerRespawn(playerid);
	}
	return SendClientMessage(playerid, RED, "ERROR: You can only use this command when you die.");
}

CMD:call911(playerid, params[])
{
	new Float:pos[3], department[6], message[100], receiver, string[144], name[24];
    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    if(sscanf(params, "s[6]s[100]", department, message)) return SendClientMessage(playerid, RED, "USAGE: /call911 [department] [message]");
    if(strlen(message) < 3 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 3-100 characters.");

    if(!strcmp(department, "cops", true))
	{
		receiver = POLICE_JOB;
	}
    else if(!strcmp(department, "ems", true))
	{
		receiver = EMS_JOB;
	}
    else if(!strcmp(department, "fire", true))
	{
		receiver = FIRE_JOB;
	}
	else return SendClientMessage(playerid, RED, "ERROR: Invalid department. (Must be: cops/ems/fire)");

    format(string, sizeof(string), "[911 CALL] %s (%i) just rang in saying: %s", name, playerid, message);
   	Send911Message(receiver, ORANGE, string);
    format(string, sizeof(string), "[CALL LOCATION] %s", ReturnPlayerLocation(playerid));
    Send911Message(receiver, ORANGE, string);
    return SendClientMessage(playerid, YELLOW, "OPERATOR: I have notified the right department, please wait for them to arrive... (Hangs Up)");
}
