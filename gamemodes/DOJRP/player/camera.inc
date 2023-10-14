//Credits: h02 (Base Code)
#include <YSI_Coding\y_hooks>

stock GetMoveDirectionFromKeys(ud, lr)
{
	new direction = 0;
    if(lr < 0)
	{
		if(ud < 0)
		{
			direction = MOVE_FORWARD_LEFT;
		}
		else if(ud > 0)
		{
			direction = MOVE_BACK_LEFT;
		}
		else
		{
			direction = MOVE_LEFT;
		}
	}
	else if(lr > 0)
	{
		if(ud < 0)
		{
			direction = MOVE_FORWARD_RIGHT;
		}
		else if(ud > 0)
		{
			direction = MOVE_BACK_RIGHT;
		}
		else
		{
			direction = MOVE_RIGHT;
		}
	}
	else if(ud < 0)
	{
		direction = MOVE_FORWARD;
	}
	else if(ud > 0)
	{
		direction = MOVE_BACK;
	}
	return direction;
}

stock GetNextCameraPosition(move_mode, Float:CP[3], Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
	return 1;
}

stock MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);

	if(CamData[playerid][cam_acceleration] <= 1)
	{
		CamData[playerid][cam_acceleration] += ACCELERATION_RATE;
	}

	new Float:speed = MOVE_SPEED * CamData[playerid][cam_acceleration], Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(CamData[playerid][cam_keys], CP, FV, X, Y, Z);
	MovePlayerObject(playerid, CamData[playerid][cam_flyobject], X, Y, Z, speed);

	CamData[playerid][cam_lastmove] = GetTickCount();
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		CamData[playerid][cam_mode] = CAMERA_MODE_NONE;
		CamData[playerid][cam_leftright] = 0;
		CamData[playerid][cam_updown] = 0;
		CamData[playerid][cam_keys] = 0;
		CamData[playerid][cam_lastmove] = 0;
		CamData[playerid][cam_acceleration] = 0.0;
		CamData[playerid][cam_status] = false;
	}
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		if(CamData[playerid][cam_mode] == CAMERA_MODE_FLY)
		{
			new keys, ud, lr;
			GetPlayerKeys(playerid, keys, ud, lr);
			if(CamData[playerid][cam_keys] && (GetTickCount() - CamData[playerid][cam_lastmove] > 100))
			{
			    MoveCamera(playerid);
			}

			if(CamData[playerid][cam_updown] != ud || CamData[playerid][cam_leftright] != lr)
			{
				if((CamData[playerid][cam_updown] != 0 || CamData[playerid][cam_leftright] != 0) && ud == 0 && lr == 0)
				{
					StopPlayerObject(playerid, CamData[playerid][cam_flyobject]);
					CamData[playerid][cam_keys]      = 0;
					CamData[playerid][cam_acceleration]  = 0.0;
				}
				else
				{
					CamData[playerid][cam_keys] = GetMoveDirectionFromKeys(ud, lr);
					MoveCamera(playerid);
				}
			}

			CamData[playerid][cam_updown] = ud;
			CamData[playerid][cam_leftright] = lr;
			return 0;
		}
	}
	return 1;
}

YCMD:cam(playerid, params[], help)
{
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(GetDutyStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are on duty.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
	
	if(CamData[playerid][cam_status] == true)
	{
		TogglePlayerSpectating(playerid, false);
		DestroyPlayerObject(playerid, CamData[playerid][cam_flyobject]);
		CamData[playerid][cam_mode] = CAMERA_MODE_NONE;
		return 1;
	}
	else
	{
		new Float:x, Float:y, Float:z, Float:health, Float:armour;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerHealth(playerid, health);
		GetPlayerArmour(playerid, armour);

		SetStoredSkin(playerid, GetPlayerSkin(playerid));
		SetStoredWantedLevel(playerid, GetPlayerWantedLevel(playerid));

		SetStoredHealth(playerid, health);
		SetStoredArmour(playerid, armour);
			
		SetPlayerHealth(playerid, MAX_HEALTH);
		SetPlayerArmour(playerid, 0.0);

		StorePlayerPosition(playerid);
		StoreWeaponData(playerid);
		ResetPlayerWeapons(playerid);

		CamData[playerid][cam_flyobject] = CreatePlayerObject(playerid, 19300, x, y, z, 0.0, 0.0, 0.0);

		TogglePlayerSpectating(playerid, true);
		AttachCameraToPlayerObject(playerid, CamData[playerid][cam_flyobject]);

		CamData[playerid][cam_status] = true;
		CamData[playerid][cam_mode] = CAMERA_MODE_FLY;
	}
	return 1;
}
