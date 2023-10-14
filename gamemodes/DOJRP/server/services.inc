#include <YSI_Coding\y_hooks>

new Iterator:Fires<MAX_FIRES>;

enum fire_data
{
	fire_houseid,
	fire_object,
	fire_smoke,
	fire_icon,
	Float:fire_health,
	Text3D:fire_label,
	bool:fire_active
};
new FireData[MAX_FIRES][fire_data];

enum services_data
{
	ls_hosp_pickup,
	ls_hosp_cp,
	ls_fire_pickup,
	ls_fire_cp,

	sf_hosp_pickup,
	sf_hosp_cp,
	sf_fire_pickup,
	sf_fire_cp,

	lv_hosp_pickup,
	lv_hosp_cp,
	lv_fire_pickup,
	lv_fire_cp
};
new ServicesData[services_data];

stock ReturnHospitalName(city)
{
	new name[32];
	if(city == LOS_SANTOS)
	{
		format(name, sizeof(name), "Los Santos Hospital");
	}
	else if(city == SAN_FIERRO)
	{
		format(name, sizeof(name), "San Fierro Hospital");
	}
	else
	{
		format(name, sizeof(name), "Las Venturas Hospital");
	}
	return name;
}

stock ReturnFireStationName(city)
{
	new name[32];
	if(city == LOS_SANTOS)
	{
		format(name, sizeof(name), "Los Santos Fire Station");
	}
	else if(city == SAN_FIERRO)
	{
		format(name, sizeof(name), "San Fierro Fire Station");
	}
	else
	{
		format(name, sizeof(name), "Las Venturas Fire Station");
	}
	return name;
}

stock ShowHospitalDialog(playerid, city)
{
	new string[128], info[64], job = GetPlayerJob(playerid);
	format(info, sizeof(info), "{FFFFFF}%s", ReturnHospitalName(city));

	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_medical] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Medical Degree to clock-on as a paramedic.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a paramedic while you are wanted.");
		return ShowPlayerDialog(playerid, HOSPITAL_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-on as a paramedic?", "Yes", "No");
	}
	else if(job == EMS_JOB)
	{
		return ShowPlayerDialog(playerid, HOSPITAL_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-off as a paramedic?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a paramedic while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock ShowFireStationDialog(playerid, city)
{
	new string[128], info[64], job = GetPlayerJob(playerid);
	format(info, sizeof(info), "{FFFFFF}%s", ReturnFireStationName(city));

	if(job == CIVILIAN_JOB)
	{
		if(DegreeData[playerid][degree_rescue] == 0) return SendClientMessage(playerid, ORANGE, "SERVER: You need a Rescue Degree to clock-on as a firefighter.");
		if(GetPlayerWantedLevel(playerid) > 0) return SendClientMessage(playerid, ORANGE, "SERVER: You cannot clock-on as a firefighter while you are wanted.");
		return ShowPlayerDialog(playerid, FIRE_STATION_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-on as a firefighter?", "Yes", "No");
	}
	else if(job == FIRE_JOB)
	{
		return ShowPlayerDialog(playerid, FIRE_STATION_DIALOG, DIALOG_STYLE_MSGBOX, info, "{FFFFFF}Would you like to clock-off as a firefighter?", "Yes", "No");
	}
	else
	{
		format(string, sizeof(string), "ERROR: You cannot become a firefighter while you are employed as a: %s", ReturnPlayerJob(playerid));
		SendClientMessage(playerid, RED, string);
	}
	return 1;
}

stock GetOnlineFirefighters()
{
	new count = 0;
	foreach(new i : Player)
	{
		if(GetPlayerJob(i) == FIRE_JOB)
		{
			count++;
		}
	}
	return count;
}

stock PayNearbyFirefighters(Float:x, Float:y, Float:z, pay)
{
	new string[128];
	foreach(new i : Player)
	{
		if(GetPlayerJob(i) == FIRE_JOB)
		{
			if(IsPlayerInRangeOfPoint(i, 40.0, x, y, z))
			{
				GivePlayerMoney(i, pay);

				SetPlayerScore(i, GetPlayerScore(i) + 1);

				SetPlayerStats(i, STATS_TYPE_FIRES, GetPlayerStats(i, STATS_TYPE_FIRES) + 1);

				format(string, sizeof(string), "NOTICE: You have been paid a $%i bonus for extinguishing the fire.", pay);
				SendClientMessage(i, YELLOW, string);
			}
		}
	}
	return 1;
}

stock Float:DistanceCameraTargetToLocation(Float:camX, Float:camY, Float:camZ, Float:objX, Float:objY, Float:objZ, Float:frX, Float:frY, Float:frZ)
{
	new Float:dist;
	dist = floatsqroot((camX - objX) * (camX - objX) + (camY - objY) * (camY - objY) + (camZ - objZ) * (camZ - objZ));

	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = frX * dist + camX;
	tmpY = frY * dist + camY;
	tmpZ = frZ * dist + camZ;

	return floatsqroot((tmpX - objX) * (tmpX - objX) + (tmpY - objY) * (tmpY - objY) + (tmpZ - objZ) * (tmpZ - objZ));
}

stock Float:GetPointAngleToPoint(Float:x1, Float:y1, Float:x2, Float:y2)
{
   new Float:dx, Float:dy;
   new Float:angle;

   dx = floatabs(floatsub(x1, x2));
   dy = floatabs(floatsub(y1, y2));

   if(dy == 0.0 || dx == 0.0)
   {
       if(dy == 0 && dx > 0) angle = 0.0;
       else if(dy == 0 && dx < 0) angle = 180.0;
       else if(dy > 0 && dx == 0) angle = 90.0;
       else if(dy < 0 && dx == 0) angle = 270.0;
       else if(dy == 0 && dx == 0) angle = 0.0;
   }
   else
   {
       angle = atan(dx / dy);
       if(x2 > x1 && y2 <= y1) angle += 90.0;
       else if(x2 <= x1 && y2 < y1) angle = floatsub(90.0, angle);
       else if(x2 < x1 && y2 >= y1) angle -= 90.0;
       else if(x2 >= x1 && y2 > y1) angle = floatsub(270.0, angle);
   }
   return floatadd(angle, 90.0);
}

stock GetXYInFrontOfPoint(&Float:x, &Float:y, Float:angle, Float:distance)
{
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}

stock IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius)
{
   	new Float:cam_x, Float:cam_y, Float:cam_z, Float:vec_x, Float:vec_y, Float:vec_z, Float:vertical, Float:horizontal;

   	GetPlayerCameraPos(playerid, cam_x, cam_y, cam_z);
   	GetPlayerCameraFrontVector(playerid, vec_x, vec_y, vec_z);

	switch (GetPlayerWeapon(playerid))
	{
	    case 34,35,36:
	    {
	    	if(DistanceCameraTargetToLocation(cam_x, cam_y, cam_z, x, y, z, vec_x, vec_y, vec_z) < radius) return true;
	    	return false;
	    }
	    case 30,31:
	    {
	    	vertical = 4.0;
	    	horizontal = -1.6;
	    }
	    case 33:
	    {
	    	vertical = 2.7;
	    	horizontal = -1.0;
	    }
	    default:
	    {
	    	vertical = 6.0;
	    	horizontal = -2.2;
	    }
	}

   	new Float:angle = GetPointAngleToPoint(0, 0, floatsqroot(vec_x * vec_x + vec_y * vec_y), vec_z) - 270.0;
   	new Float:resize_x, Float:resize_y, Float:resize_z = floatsin(angle + vertical, degrees);
   	GetXYInFrontOfPoint(resize_x, resize_y, GetPointAngleToPoint(0, 0, vec_x, vec_y) + horizontal, floatcos(angle + vertical, degrees));
   	if(DistanceCameraTargetToLocation(cam_x, cam_y, cam_z, x, y, z, resize_x, resize_y, resize_z) < radius) return true;
	return false;
}

stock EMSRadio(colour, text[])
{
	new string[144];
	foreach(new i : Player)
	{
		new job = GetPlayerJob(i);
	 	if(job == EMS_JOB || job == FIRE_JOB)
	 	{
	   		format(string, sizeof(string), "%s", text);
	    	SendClientMessage(i, colour, string);
		}
	}
	return 1;
}

stock RemoveAllFires()
{
	foreach(new i : Fires)
	{
		if(FireData[i][fire_active] == true)
		{
			DestroyDynamicObject(FireData[i][fire_object]);
			DestroyDynamicObject(FireData[i][fire_smoke]);
			DestroyDynamic3DTextLabel(FireData[i][fire_label]);
			DestroyDynamicMapIcon(FireData[i][fire_icon]);

			new houseid = FireData[i][fire_houseid];
			SetHouseFireStatus(houseid, false);

			FireData[i][fire_houseid] = -1;
			FireData[i][fire_active] = false;

			Iter_Remove(Fires, i);
		}
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2025.2137, -1401.6699, 17.2095, 22, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Hospital
	CreateDynamicMapIcon(-2655.1042, 640.1654, 14.4545, 22, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Hospital
	CreateDynamicMapIcon(1607.4126, 1815.2407, 10.8203, 22, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Hospital

	CreateDynamicMapIcon(1743.1572, -1453.2560, 13.5363, 20, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Fire Station
	CreateDynamicMapIcon(-2024.3024, 67.1473, 28.4459, 20, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Fire Station
	CreateDynamicMapIcon(1746.4425, 2080.6411, 10.8203, 20, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Fire Station

	ServicesData[ls_hosp_pickup] = CreateDynamicPickup(1239, 1, 2025.2137, -1401.6699, 17.2095, -1, -1, -1, 100.0, -1, 0);//LS Hospital
	ServicesData[sf_hosp_pickup] = CreateDynamicPickup(1239, 1, -2655.1042, 640.1654, 14.4545, -1, -1, -1, 100.0, -1, 0);//SF Hospital
	ServicesData[lv_hosp_pickup] = CreateDynamicPickup(1239, 1, 1607.4126, 1815.2407, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV Hospital

	ServicesData[ls_fire_pickup] = CreateDynamicPickup(1239, 1, 1743.1572, -1453.2560, 13.5363, -1, -1, -1, 100.0, -1, 0);//LS Fire Station
	ServicesData[sf_fire_pickup] = CreateDynamicPickup(1239, 1, -2024.3024, 67.1473, 28.4459, -1, -1, -1, 100.0, -1, 0);//SF Fire Station
	ServicesData[lv_fire_pickup] = CreateDynamicPickup(1239, 1, 1746.4425, 2080.6411, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV Fire Station

	ServicesData[ls_hosp_cp] = CreateDynamicCP(2025.2137, -1401.6699, 17.2095, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Hospital
	ServicesData[sf_hosp_cp] = CreateDynamicCP(-2655.1042, 640.1654, 14.4545, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Hospital
	ServicesData[lv_hosp_cp] = CreateDynamicCP(1607.4126, 1815.2407, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Hospital

	ServicesData[ls_fire_cp] = CreateDynamicCP(1743.1572, -1453.2560, 13.5363, 2.0, -1, -1, -1, 10.0, -1, 0);//LS Fire Station
	ServicesData[sf_fire_cp] = CreateDynamicCP(-2024.3024, 67.1473, 28.4459, 2.0, -1, -1, -1, 10.0, -1, 0);//SF Fire Station
	ServicesData[lv_fire_cp] = CreateDynamicCP(1746.4425, 2080.6411, 10.8203, 2.0, -1, -1, -1, 10.0, -1, 0);//LV Fire Station
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case HOSPITAL_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_EMS, true);
		    		ShowParamedicSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a paramedic skin to clock-on as a paramedic.");
		    	}
		    	else if(job == EMS_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a civilian skin to clock-off as a paramedic.");
		    	}
		    }
		    return 1;
		}
		case FIRE_STATION_DIALOG:
		{
		    if(response)
		    {
		    	new job = GetPlayerJob(playerid);
		    	if(job == CIVILIAN_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_FIRE, true);
		    		ShowFirefighterSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a firefighter skin to clock-on as a firefighter.");
		    	}
		    	else if(job == FIRE_JOB)
		    	{
		    		SetSkinRequest(playerid, REQUEST_TYPE_CIV, true);
		    		ShowCivilianSkinMenu(playerid);
		    		return SendClientMessage(playerid, WHITE, "SERVER: Please choose a firefighter skin to clock-off as a firefighter.");
		    	}
		    }
		    return 1;
		}
		case HEAL_DIALOG:
		{
			if(response)
			{
				new string[128], name[24], paramedic = GetPlayerParamedic(playerid);
				GetPlayerName(playerid, name, sizeof(name));

				if(IsPlayerConnected(paramedic))
				{
					new high = (MAX_HEAL_PAY - (MAX_HEAL_PAY / 2)), low = (MAX_HEAL_PAY / 2), pay = (random(high) + low);
					GivePlayerMoney(paramedic, pay);

					SetPlayerScore(paramedic, GetPlayerScore(playerid) + 1);
					SetPlayerStats(paramedic, STATS_TYPE_PATIENTS, GetPlayerStats(paramedic, STATS_TYPE_PATIENTS) + 1);

					format(string, sizeof(string), "NOTICE: %s (%i) accepted your request resulting in a $%i bonus for healing the patient.", name, playerid, pay);
					SendClientMessage(paramedic, YELLOW, string);

					ApplyAnimation(paramedic, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
				}

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SetPlayerLastHeal(playerid, gettime());

				SetPlayerParamedic(playerid, INVALID_PLAYER_ID);

				ResetPlayerInjuries(playerid);
				return SetPlayerHealth(playerid, 100.0);
			}
			else
			{
				new string[128], name[24], paramedic = GetPlayerParamedic(playerid);
				GetPlayerName(playerid, name, sizeof(name));

				if(IsPlayerConnected(paramedic))
				{
					format(string, sizeof(string), "NOTICE: %s (%i) rejected your request for medical assistance.", name, playerid);
					SendClientMessage(paramedic, ORANGE, string);
				}

				SetPlayerParamedic(playerid, INVALID_PLAYER_ID);
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == ServicesData[ls_hosp_pickup] || pickupid == ServicesData[sf_hosp_pickup] || pickupid == ServicesData[lv_hosp_pickup])
	{
		return 1;
	}
	else if(pickupid == ServicesData[ls_fire_pickup] || pickupid == ServicesData[sf_fire_pickup] || pickupid == ServicesData[lv_fire_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == ServicesData[ls_hosp_cp])
		{
			return ShowHospitalDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == ServicesData[sf_hosp_cp])
		{
			return ShowHospitalDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == ServicesData[lv_hosp_cp])
		{
			return ShowHospitalDialog(playerid, LAS_VENTURAS);
		}
		else if(checkpointid == ServicesData[ls_fire_cp])
		{
			return ShowFireStationDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == ServicesData[sf_fire_cp])
		{
			return ShowFireStationDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == ServicesData[lv_fire_cp])
		{
			return ShowFireStationDialog(playerid, LAS_VENTURAS);
		}
	}
	return 1;
}

task OnFireCreate[600000]()
{
	if(GetOnlineFirefighters() > 0)
	{
		new text[32];
		for(new i = 0; i < MAX_FIRES; i++)
		{
			if(FireData[i][fire_active] == false)
			{
				new houseid = GetRandomHouseID();
				if(houseid == -1) return 1;

				new Float:x = GetHouseExtX(houseid), Float:y = GetHouseExtY(houseid), Float:z = GetHouseExtZ(houseid);

				FireData[i][fire_object] = CreateDynamicObject(FIRE_OBJECT, x, y, z - 2.5, 0.0, 0.0, 0.0, 0, 0, -1, 100.0);
				FireData[i][fire_smoke] = CreateDynamicObject(SMOKE_OBJECT, x, y, z + 2.5, 0.0, 0.0, 0.0, 0, 0, -1, 100.0);

				FireData[i][fire_health] = 500.0;

				format(text, sizeof(text), "%0.0f/500", FireData[i][fire_health]);
				FireData[i][fire_label] = CreateDynamic3DTextLabel(text, WHITE, x, y, z, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0, -1, 0);
					
				FireData[i][fire_icon] = CreateDynamicMapIcon(x, y, z, 0, RED, -1, -1, -1, 250.0, MAPICON_LOCAL, -1, 0);

				FireData[i][fire_active] = true;

				FireData[i][fire_houseid] = houseid;

				SetHouseFireStatus(i, true);

				Iter_Add(Fires, i);
			}
		}
	}
	else
	{
		RemoveAllFires();
	}
	return 1;
}

task OnFireUpdate[1000]()
{
	if(GetOnlineFirefighters() > 0)
	{
		foreach(new i : Player)
		{
			if(GetPlayerJob(i) == FIRE_JOB)
			{
				new in_firetruck = GetVehicleModel(GetPlayerVehicleID(i)) == 407;
				if(in_firetruck || GetPlayerWeapon(i) == 42)
				{
					new keys, tmp;
					GetPlayerKeys(i, keys, tmp, tmp);
	    			if((keys & KEY_FIRE) || (keys & KEY_WALK))
	    			{
						foreach(new f : Fires)
						{
							if(FireData[f][fire_active] == true)
							{
								new Float:pos[3];
								GetDynamicObjectPos(FireData[f][fire_object], pos[0], pos[1], pos[2]);
								if(IsPlayerAimingAt(i, pos[0], pos[1], pos[2], (in_firetruck ? 8.0 : 4.0)))
								{
									new text[32], Float:take_health = (2.0) * (in_firetruck ? 3.0 : 1.0);

									FireData[f][fire_health] -= take_health;

									format(text, sizeof(text), "%0.0f/500", FireData[f][fire_health]);
							     	UpdateDynamic3DTextLabelText(FireData[f][fire_label], WHITE, text);

									if(FireData[f][fire_health] <= 0.0)
									{
										DestroyDynamicObject(FireData[f][fire_object]);
										DestroyDynamicObject(FireData[f][fire_smoke]);
										DestroyDynamic3DTextLabel(FireData[f][fire_label]);
										DestroyDynamicMapIcon(FireData[f][fire_icon]);

										new houseid = FireData[f][fire_houseid];
										SetHouseFireStatus(houseid, false);

										FireData[f][fire_houseid] = -1;
										FireData[f][fire_active] = false;

										Iter_Remove(Fires, f);

										new high = (MAX_FIRE_PAY - (MAX_FIRE_PAY / 2)), low = (MAX_FIRE_PAY / 2), pay = (random(high) + low);
										return PayNearbyFirefighters(pos[0], pos[1], pos[2], pay);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

YCMD:e(playerid, params[], help)
{
	new string[144], name[24], message[100], job = GetPlayerJob(playerid);
	if(job != EMS_JOB && job != FIRE_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to emergency services only.");
	if(sscanf(params, "s[100]", message)) return SendClientMessage(playerid, RED, "USAGE: /e [message]");
	if(strlen(message) < 1 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-100 characters long.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	if((gettime() - 3) < GetTimerStatus(playerid, TIMER_TYPE_RADIO)) return SendClientMessage(playerid, RED, "ERROR: Please wait 3 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_RADIO, gettime());

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "RADIO(/e): %s %s: %s", ReturnPlayerJob(playerid), name, message);
	return EMSRadio(ORANGE, string);
}

YCMD:fires(playerid, params[], help)
{
	if(GetPlayerJob(playerid) != FIRE_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to firefighters only.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	new count = 0, string[128], query[800], Float:pos[3];
	for(new i = 0; i < MAX_FIRES; i++)
	{
		if(FireData[i][fire_active] == true)
		{
			GetDynamicObjectPos(FireData[i][fire_object], pos[0], pos[1], pos[2]);
			for(new zone = 0; zone < sizeof(sa_zones); zone++)
			{
				if(pos[0] >= sa_zones[zone][zone_area][0] && pos[0] <= sa_zones[zone][zone_area][3] && pos[1] >= sa_zones[zone][zone_area][1] && pos[1] <= sa_zones[zone][zone_area][4])
				{
					new Float:dist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);
					format(string, sizeof(string), "{FFFFFF}Location: %s - Distance: %0.0f Metres Away\n", sa_zones[zone][zone_name], dist);
					strcat(query, string);
					count++;
					break;
				}
			}
		}
	}
	if(count == 0) return SendClientMessage(playerid, ORANGE, "NOTICE: Please wait, there are currently no fires to put out.");
	return ShowPlayerDialog(playerid, FIRES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Current Fires", query, "Close", "");
}

YCMD:heal(playerid, params[], help)
{
	new string[128], name[24], Float:pos[3], Float:health, targetid;
	if(GetPlayerJob(playerid) != EMS_JOB) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to paramedics only.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to be able to heal someone.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /heal [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot heal yourself.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	GetPlayerPos(targetid, pos[0], pos[1], pos[2]);
	GetPlayerHealth(targetid, health);

	if(!IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You must be within 10 metres of the player to be able to heal them.");
	if(health >= 100) return SendClientMessage(playerid, RED, "ERROR: That player already has maximum health.");
	if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: The player must be on foot to be able to heal them.");
	if(IsPlayerSafe(targetid)) return SendClientMessage(playerid, RED, "ERROR: You cannot heal players inside the safezone.");
	if((gettime() - 300) < GetPlayerLastHeal(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player has been healed in the last 5 minutes, please wait.");

	SetPlayerParamedic(targetid, playerid);

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "{FFFFFF}Paramedic %s has offered to heal you free of charge, do you accept?", name);
	ShowPlayerDialog(targetid, HEAL_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Paramedic Request", string, "Yes", "No");

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "NOTICE: You have requested to heal %s, please wait nearby for their response.", name);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}
