#include <YSI_Coding\y_hooks>

forward OnPlayerKicked(playerid);

stock GetID(name[])
{
	new get_name[24];
    foreach(new i : Player)
    {
    	GetPlayerName(i, get_name, sizeof(get_name));
        if(!strcmp(get_name, name, true)) return i;
    }
    return INVALID_PLAYER_ID;
}

stock KickPlayer(playerid)
{
	return SetTimerEx("OnPlayerKicked", 1000, false, "i", playerid);
}

stock IsPlayerSpawned(playerid)
{
	new pState = GetPlayerState(playerid);
	return 0 <= playerid <= MAX_PLAYERS && pState != PLAYER_STATE_NONE && pState != PLAYER_STATE_WASTED && pState != PLAYER_STATE_SPECTATING;
}

stock IsHoldingWeapon(playerid, weaponid)
{
	new weapon, ammo;
	for(new i = 0; i < 13; i++)
	{
	    GetPlayerWeaponData(playerid, i, weapon, ammo);
	    if(weapon == weaponid) return 1;
	}
	return 0;
}

stock IsHoldingFirearm(playerid)
{
	if(GetPlayerWeapon(playerid) >= 22 && GetPlayerWeapon(playerid) <= 34) return 1;
	return 0;
}

stock IsPointInRangeOfPoint(Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2, Float:range)
{
	x2 -= x;
	y2 -= y;
	z2 -= z;
	return ((x2 * x2) + (y2 * y2) + (z2 * z2)) < (range * range);
}

stock GetXYBehindPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, x, y, a);
	GetPlayerFacingAngle(playerid, a);

	if(GetPlayerVehicleID(playerid))
	{
	    GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	x -= (distance * floatsin(-a, degrees));
	y -= (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, x, y, a);
	GetPlayerFacingAngle(playerid, a);

	if(GetPlayerVehicleID(playerid))
	{
	    GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetClosestPlayerID(playerid, Float:range)
{
	new Float:pos[3];
    foreach(new i : Player)
    {
        if(playerid == i) continue;
        GetPlayerPos(i, pos[0], pos[1], pos[2]);
	    if(IsPlayerInRangeOfPoint(playerid, range, pos[0], pos[1], pos[2]))
	    {
	        return i;
	    }
    }
    return INVALID_PLAYER_ID;
}

stock RemovePlayerWeapon(playerid, weaponid)
{
	new weapon[13], ammo[13];
	for(new slot = 0; slot < 13; slot++)
	{
	    GetPlayerWeaponData(playerid, slot, weapon[slot], ammo[slot]);
	}
	ResetPlayerWeapons(playerid);

	for(new slot; slot < 13; slot++)
	{
		if(weapon[slot] == weaponid || ammo[slot] == 0) continue;
		GivePlayerWeapon(playerid, weapon[slot], ammo[slot]);
	}
	return GivePlayerWeapon(playerid, 0, 1);
}

stock SetPlayerColourEx(playerid, job)
{
	if(job == CIVILIAN_JOB)
	{
		if(GetPlayerWantedLevel(playerid) >= 1 && GetPlayerWantedLevel(playerid) <= 3)
		{
			SetPlayerColor(playerid, YELLOW);
		}
		else if(GetPlayerWantedLevel(playerid) >= 4)
		{
			SetPlayerColor(playerid, RED);
		}
		else
		{
			SetPlayerColor(playerid, WHITE);
		}
	}
	else if(job == CIA_JOB)
	{
		SetPlayerColor(playerid, WHITE);
	}
	else if(job == POLICE_JOB)
	{
		SetPlayerColor(playerid, BLUE);
	}
	else if(job == ARMY_JOB)
	{
		SetPlayerColor(playerid, GREEN);
	}
	else if(job == EMS_JOB || job == FIRE_JOB)
	{
		SetPlayerColor(playerid, PINK);
	}
	else if(job == MINER_JOB || job == PILOT_JOB || job == TRUCKER_JOB)
	{
		SetPlayerColor(playerid, ORANGE);
	}
	return 1;
}

stock GetPlayerID(name[])
{
	new getname[24];
    foreach(new i : Player)
    {
    	GetPlayerName(i, getname, sizeof(getname));
        if(!strcmp(getname, name, true)) return i;
    }
    return INVALID_PLAYER_ID;
}

public OnPlayerKicked(playerid)//Do not hook
{
	return Kick(playerid);
}
