#include <YSI_Coding\y_hooks>

forward OnPointsReset(playerid);

forward OnCheatDetected(playerid, ip_address[], type, code);

enum anticheat_data
{
	anticheat_points
};
new AntiCheatData[MAX_PLAYERS][anticheat_data];

stock ReturnCheatName(code)
{
	new name[32];
	format(name, sizeof(name), "Unknown Cheat");
    if(code == 0) { format(name, sizeof(name), "AirBreak (On Foot)"); }
	else if(code == 1) { format(name, sizeof(name), "AirBreak (In Vehicle)"); }
	else if(code == 2) { format(name, sizeof(name), "Teleport (On Foot)"); }
	else if(code == 3) { format(name, sizeof(name), "Teleport (In Vehicle)"); }
	else if(code == 4) { format(name, sizeof(name), "Teleport (Vehicle to Vehicle)"); }
	else if(code == 5) { format(name, sizeof(name), "Teleport (Vehicle to Player)"); }
	else if(code == 6) { format(name, sizeof(name), "Teleport (Pickups)"); }
	else if(code == 7) { format(name, sizeof(name), "FlyHack (On Foot)"); }
	else if(code == 8) { format(name, sizeof(name), "FlyHack (In Vehicle)"); }
	else if(code == 9) { format(name, sizeof(name), "SpeedHack (On Foot)"); }
	else if(code == 10) { format(name, sizeof(name), "SpeedHack (In Vehicle)"); }
	else if(code == 11) { format(name, sizeof(name), "Health Hack (In Vehicle)"); }
	else if(code == 12) { format(name, sizeof(name), "Health Hack (On Foot)"); }
	else if(code == 13) { format(name, sizeof(name), "Armour Hack"); }
	else if(code == 14) { format(name, sizeof(name), "Money Hack"); }
	else if(code == 15) { format(name, sizeof(name), "Weapon Hack"); }
	else if(code == 16) { format(name, sizeof(name), "Ammo Hack (Add)"); }
	else if(code == 17) { format(name, sizeof(name), "Ammo Hack (Infinite)"); }
	else if(code == 18) { format(name, sizeof(name), "Special Actions Hack"); }
	else if(code == 19) { format(name, sizeof(name), "GodMode (On Foot)"); }
	else if(code == 20) { format(name, sizeof(name), "GodMode (In Vehicle)"); }
	else if(code == 21) { format(name, sizeof(name), "Invisible Hack"); }
	else if(code == 22) { format(name, sizeof(name), "Lagcomp Spoof"); }
	else if(code == 23) { format(name, sizeof(name), "Tuning Hack"); }
	else if(code == 24) { format(name, sizeof(name), "Parkour Mod"); }
	else if(code == 25) { format(name, sizeof(name), "Quick Turn"); }
	else if(code == 26) { format(name, sizeof(name), "Rapid-Fire"); }
	else if(code == 27) { format(name, sizeof(name), "FakeSpawn"); }
	else if(code == 28) { format(name, sizeof(name), "FakeKill"); }
	else if(code == 29) { format(name, sizeof(name), "Pro Aim"); }
	else if(code == 30) { format(name, sizeof(name), "CJ Run"); }
	else if(code == 31) { format(name, sizeof(name), "CarShot"); }
	else if(code == 32) { format(name, sizeof(name), "CarJack"); }
	else if(code == 33) { format(name, sizeof(name), "UnFreeze"); }
	else if(code == 34) { format(name, sizeof(name), "AFK Ghost"); }
	else if(code == 35) { format(name, sizeof(name), "Full Aiming"); }

	else if(code == 36) { format(name, sizeof(name), "Fake NPC"); }
	else if(code == 37) { format(name, sizeof(name), "Reconnect Flood"); }
	else if(code == 38) { format(name, sizeof(name), "High Ping"); }
	else if(code == 39) { format(name, sizeof(name), "Dialog Hack"); }
	else if(code == 40) { format(name, sizeof(name), "Sandbox"); }
	else if(code == 41) { format(name, sizeof(name), "Invalid Version"); }
	else if(code == 42) { format(name, sizeof(name), "Rcon Hack"); }

	else if(code == 43) { format(name, sizeof(name), "Tuning Crasher"); }
	else if(code == 44) { format(name, sizeof(name), "Invalid Seat Crasher"); }
	else if(code == 45) { format(name, sizeof(name), "Dialog Crasher"); }
	else if(code == 46) { format(name, sizeof(name), "Attached Object Crasher"); }
	else if(code == 47) { format(name, sizeof(name), "Weapon Crasher"); }

	else if(code == 48) { format(name, sizeof(name), "Connection Flood"); }
	else if(code == 49) { format(name, sizeof(name), "Callback Flood"); }
	else if(code == 50) { format(name, sizeof(name), "Seat Changing Flood"); }

	else if(code == 51) { format(name, sizeof(name), "DoS"); }

	else if(code == 52) { format(name, sizeof(name), "NOPs"); }
	return name;
}

stock SendRemoveMessage(playerid, code)
{
	new string[128], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "ANTICHEAT: %s (%d) has been kicked from the server for: %s", name, playerid, ReturnCheatName(code));
	SendClientMessageToAll(RED, string);
	return KickPlayer(playerid);
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		AntiCheatData[playerid][anticheat_points] = 0;
	}
	return 1;
}

public OnCheatDetected(playerid, ip_address[], type, code)
{
	if(GetPlayerLevel(playerid) >= ADMIN) return 1;

	if(IsPlayerSpawned(playerid))
	{
		switch(code)
		{
	 		case 21, 22, 25, 27, 28, 30, 31, 32, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52: return 1;//Disabled
		}
		
	    if(type)
		{
			return SendRemoveMessage(playerid, code);
		}
	    else
	    {   
	        AntiCheatData[playerid][anticheat_points]++;
			if(AntiCheatData[playerid][anticheat_points] >= 6)
			{
			    return SendRemoveMessage(playerid, code);
			}
			else
			{
		    	new string[128], name[MAX_PLAYER_NAME];
				GetPlayerName(playerid, name, sizeof(name));
		        format(string, sizeof(string), "ANTICHEAT: %s (%d) has been detected by the anticheat for: %s", name, playerid, ReturnCheatName(code));
		        StaffRadio(GREY, string);
			}
			
	      	SetTimerEx("OnPointsReset", 5000, false, "i", playerid);
	    }
	}
    return 1;
}

public OnPointsReset(playerid)//Do not hook
{
    AntiCheatData[playerid][anticheat_points] = 0;
	return 1;
}
