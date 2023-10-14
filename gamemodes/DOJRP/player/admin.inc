#include <YSI_Coding\y_hooks>

enum staff_data
{
	Float:staff_lastx,
	Float:staff_lasty,
	Float:staff_lastz,
	Float:staff_lasta,
	Float:staff_lasthealth,
	Float:staff_lastarmour,
	staff_lastinterior,
	staff_lastworld,
	staff_specid,
	staff_giveid,
	staff_giveitem,
	bool:staff_spectating
};
new StaffData[MAX_PLAYERS][staff_data];

enum temp_data
{
	temp_vehicle_id
};
new TempData[MAX_PLAYERS][temp_data];

enum elements_data
{
	server_time
};
new ElementsData[elements_data];

stock ProcessServerElements(bool:rollover)
{
	if(rollover)
	{
		ElementsData[server_time]++;
    	if(ElementsData[server_time] >= 23)
    	{
    		ElementsData[server_time] = 0;
    	}
	}
	else 
	{
		ElementsData[server_time] = random(24);
	}
	SetWorldTime(ElementsData[server_time]);

	new weather = random(20);
	return SetWeather(weather);
}

stock CheckIfAdminOnline(masterid)
{
	foreach(new i : Player)
	{
		if(GetPlayerMasterID(i) == masterid) return i;
	}
	return INVALID_PLAYER_ID;
}

stock ShowAdminDialog(playerid)
{
	return ShowPlayerDialog(playerid, ADMIN_DIALOG, DIALOG_STYLE_MSGBOX,
"{FFFFFF}Admin Commands", "{FFFFFF}/(a)nn /bcmds /duty /kick /(un)ban /warn /(un)mute /(un)spec /get /goto /goback /disarm /emptyinv /time /weather\n/move /cam /tele /a(bike/heli/boat) /set(level/score/skin/money) /(give/remove)vip /give(item/weapon)", "Close", "");
}

stock ShowBuilderDialog(playerid)
{
	return ShowPlayerDialog(playerid, BUILDER_DIALOG, DIALOG_STYLE_MSGBOX,
"{FFFFFF}Building Commands", "{FFFFFF}/create(stop/sprunk/house/business) /delete(stop/sprunk/house/business) /deleteall(houses/businesses)\n/reset(house/business)price /resetall(house/business)prices /remove(house/business)owner /removeall(house/business)owners", "Close", "");
}

stock ShowTeleportDialog(playerid)
{
	return ShowPlayerDialog(playerid, TELE_MAIN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Teleport > Menu", "{FFFFFF}LS\nSF\nLV", "Select", "Cancel");
}

stock ReturnPlayerLevel(playerid)
{
	new level[16];
	if(GetPlayerLevel(playerid) == HELPER) { level = "Helper"; }
	else if(GetPlayerLevel(playerid) == ADMIN) { level = "Admin"; }
	else if(GetPlayerLevel(playerid) == HEAD) { level = "Head Admin"; }
	else if(GetPlayerLevel(playerid) == MANAGER) { level = "Manager"; }
	else if(GetPlayerLevel(playerid) == OWNER) { level = "Owner"; }
	else
	{
		if(GetPlayerVIP(playerid))
		{
			level = "V.I.P";
		}
		else
		{
			level = "Player";
		}
	}
	return level;
}

stock ReturnLevelName(level)
{
	new name[16];
	if(level == HELPER) { name = "Helper"; }
	else if(level == ADMIN) { name = "Admin"; }
	else if(level == HEAD) { name = "Head Admin"; }
	else if(level == MANAGER) { name = "Manager"; }
	else if(level == OWNER) { name = "Owner"; }
	else
	{
		name = "Player";
	}
	return name;
}

stock StaffRadio(colour, text[])
{
	new string[144];
	foreach(new i : Player)
	{
	    if(GetPlayerLevel(i) > PLAYER)
	    {
	    	format(string, sizeof(string), "%s", text);
	    	SendClientMessage(i, colour, string);
	    }
	}
	return 1;
}

stock OnPlayerSpectate(playerid, targetid)
{
	new Float:pos[4], Float:health, Float:armour;
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot spectate yourself.");
    if(IsPlayerSafe(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot spectate players while you are in a safezone.");
    if(GetDutyStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: You cannot spectate players while you are on duty.");
    if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot spectate players while you are in jail.");
    if(StaffData[targetid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: That player is currently in spectate mode.");

    if(StaffData[playerid][staff_spectating] == false)
    {
        GetPlayerHealth(playerid, health);
        SetStoredHealth(playerid, health);

        GetPlayerArmour(playerid, armour);
        SetStoredArmour(playerid, armour);

        StoreWeaponData(playerid);
        ResetPlayerWeapons(playerid);

	    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	    GetPlayerFacingAngle(playerid, pos[3]);

	    StaffData[playerid][staff_lastx] = pos[0];
	    StaffData[playerid][staff_lasty] = pos[1];
	    StaffData[playerid][staff_lastz] = pos[2];
	    StaffData[playerid][staff_lasta] = pos[3];
	    StaffData[playerid][staff_lastinterior] = GetPlayerInterior(playerid);
	    StaffData[playerid][staff_lastworld] = GetPlayerVirtualWorld(playerid);

		SetStoredWantedLevel(playerid, GetPlayerWantedLevel(playerid));
		SetStoredSkin(playerid, GetPlayerSkin(playerid));
    }
    StaffData[playerid][staff_spectating] = true;
  	StaffData[playerid][staff_specid] = targetid;

	SetPlayerSpectated(targetid, true);

	TogglePlayerHUDTextdraws(playerid, false);

	TogglePlayerSpectating(playerid, true);
	if(IsPlayerInAnyVehicle(targetid))
	{
		SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	  	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	  	return PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
	}
	else
	{
		SetPlayerInterior(playerid, GetPlayerInterior(targetid));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	  	PlayerSpectatePlayer(playerid, targetid);
    }
    return 1;
}

hook OnGameModeInit()
{ 
	ElementsData[server_time] = 12;
	return ProcessServerElements(false);
}

hook OnPlayerSpawn(playerid)
{
	if(StaffData[playerid][staff_spectating] == true)
	{
		SetPlayerHealth(playerid, GetStoredHealth(playerid));
        SetPlayerArmour(playerid, GetStoredArmour(playerid));

		RestoreStoredWeapons(playerid);

	    SetPlayerInterior(playerid, StaffData[playerid][staff_lastinterior]);
	    SetPlayerVirtualWorld(playerid, StaffData[playerid][staff_lastworld]);
	    SetPlayerPos(playerid, StaffData[playerid][staff_lastx], StaffData[playerid][staff_lasty], StaffData[playerid][staff_lastz]);
	    SetPlayerFacingAngle(playerid, StaffData[playerid][staff_lasta]);

		SetPlayerWantedLevel(playerid, GetStoredWantedLevel(playerid));

		SetPlayerSkin(playerid, GetStoredSkin(playerid));

		TogglePlayerHUDTextdraws(playerid, true);
		
		SetPlayerSpectated(StaffData[playerid][staff_specid], false);
		StaffData[playerid][staff_specid] = INVALID_PLAYER_ID;
		StaffData[playerid][staff_spectating] = false;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		StaffData[playerid][staff_lastx] = 0.0;
		StaffData[playerid][staff_lasty] = 0.0;
		StaffData[playerid][staff_lastz] = 0.0;
		StaffData[playerid][staff_lasta] = 0.0;

		StaffData[playerid][staff_lastinterior] = 0;
		StaffData[playerid][staff_lastworld] = 0;

		StaffData[playerid][staff_specid] = 0;

		StaffData[playerid][staff_giveid] = INVALID_PLAYER_ID;
		StaffData[playerid][staff_giveitem] = 0;

		StaffData[playerid][staff_spectating] = false;

		TempData[playerid][temp_vehicle_id] = INVALID_VEHICLE_ID;
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{
		if(TempData[playerid][temp_vehicle_id] != INVALID_VEHICLE_ID)
		{
			DestroyVehicle(TempData[playerid][temp_vehicle_id]);
			TempData[playerid][temp_vehicle_id] = INVALID_VEHICLE_ID;
		}
	}
	return 1;
}

hook OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(GetPlayerLevel(playerid) >= ADMIN && !IsPlayerInjured(playerid))
	{
		if(!IsPlayerNPC(clickedplayerid))
		{
			OnPlayerSpectate(playerid, clickedplayerid);
		}
	}
	return 1;
}

hook OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if(GetPlayerSpectated(playerid) == true)
	{
	    if(newinteriorid != oldinteriorid)
	    {
		    foreach(new i : Player)
			{
				if(StaffData[i][staff_spectating] == true && StaffData[i][staff_specid] == playerid)
				{
					SetPlayerInterior(i, GetPlayerInterior(playerid));
					SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid));
					return 1;
				}
			}
		}
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT && TempData[playerid][temp_vehicle_id] != INVALID_VEHICLE_ID)
	{
		DestroyVehicle(TempData[playerid][temp_vehicle_id]);
		TempData[playerid][temp_vehicle_id] = INVALID_VEHICLE_ID;
		return 1;
	}
	
	if(GetPlayerSpectated(playerid) == true)
	{
	    if(newstate != oldstate)
	    {
		    foreach(new i : Player)
			{
				if(StaffData[i][staff_spectating] == true && StaffData[i][staff_specid] == playerid)
				{
					if(IsPlayerInAnyVehicle(playerid))
					{
						PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
						return 1;
					}
					else
					{
						PlayerSpectatePlayer(i, playerid);
						return 1;
					}
				}
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case TELE_LV_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://LVPD
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 2336.8965, 2456.7803, 14.9688);
						SetPlayerFacingAngle(playerid, 176.4752);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Airport
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1674.5664, 1447.8522, 10.7900);
						SetPlayerFacingAngle(playerid, 269.8492);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Hospital
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1607.4288, 1817.2189, 10.8203);
						SetPlayerFacingAngle(playerid, 359.7627);
						return SetCameraBehindPlayer(playerid);
					}
					case 3://University
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 2375.5913, 2308.0605, 8.1406);
						SetPlayerFacingAngle(playerid, 359.8412);
						return SetCameraBehindPlayer(playerid);
					}
					case 4://Binco
					{
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerInterior(playerid, 0);
						SetPlayerPos(playerid, 1655.6273, 1733.3518, 10.8281);
						SetPlayerFacingAngle(playerid, 91.1724);
						return SetCameraBehindPlayer(playerid);
					}
				}
				return 1;
			}
			else
			{
				ShowTeleportDialog(playerid);
			}
			return 1;
		}
		case TELE_SF_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://SFPD
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1605.5231, 712.1763, 13.8672);
						SetPlayerFacingAngle(playerid, 354.2668);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Airport
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1422.7832, -288.7293, 14.1484);
						SetPlayerFacingAngle(playerid, 136.3390);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Hospital
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -2655.1104, 638.3422, 14.4531);
						SetPlayerFacingAngle(playerid, 180.1129);
						return SetCameraBehindPlayer(playerid);
					}
					case 3://University
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, -1493.7815, 920.1070, 7.1875);
						SetPlayerFacingAngle(playerid, 90.0846);
						return SetCameraBehindPlayer(playerid);
					}
					case 4://Binco
					{
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerInterior(playerid, 0);
						SetPlayerPos(playerid, -2375.7122, 910.1544, 45.4453);
						SetPlayerFacingAngle(playerid, 89.9471);
						return SetCameraBehindPlayer(playerid);
					}
				}
				return 1;
			}
			else
			{
				ShowTeleportDialog(playerid);
			}
			return 1;
		}
		case TELE_LS_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://LSPD
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1553.8295, -1675.6392, 16.1953);
						SetPlayerFacingAngle(playerid, 89.2095);
						return SetCameraBehindPlayer(playerid);
					}
					case 1://Airport
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1642.2411, -2332.7742, 13.5469);
						SetPlayerFacingAngle(playerid, 0.1502);
						return SetCameraBehindPlayer(playerid);
					}
					case 2://Hospital
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 2025.2469, -1403.4918, 17.2098);
						SetPlayerFacingAngle(playerid, 180.7238);
						return SetCameraBehindPlayer(playerid);
					}
					case 3://University
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerPos(playerid, 1467.2743, -1011.5594, 26.8438);
						SetPlayerFacingAngle(playerid, 179.5822);
						return SetCameraBehindPlayer(playerid);
					}
					case 4://Binco
					{
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerInterior(playerid, 0);
						SetPlayerPos(playerid, 2244.6360, -1664.5170, 15.4766);
						SetPlayerFacingAngle(playerid, 346.0298);
						return SetCameraBehindPlayer(playerid);
					}
				}
				return 1;
			}
			else
			{
				ShowTeleportDialog(playerid);
			}
			return 1;
		}
		case TELE_MAIN_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://LS
					{
						ShowPlayerDialog(playerid, TELE_LS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Teleport > LS", "{FFFFFF}LSPD\nAirport\nHospital\nUniversity\nBinco", "Teleport", "Back");
					}
					case 1://SF
					{
						ShowPlayerDialog(playerid, TELE_SF_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Teleport > SF", "{FFFFFF}SFPD\nAirport\nHospital\nUniversity\nBinco", "Teleport", "Back");
					}
					case 2://LV
					{
						ShowPlayerDialog(playerid, TELE_LV_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Teleport > LV", "{FFFFFF}LVPD\nAirport\nHospital\nUniversity\nBinco", "Teleport", "Back");
					}
				}
			}
			return 1;
		}
		case GIVE_ITEM_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Sprunk
					{
						StaffData[playerid][staff_giveitem] = SPRUNK_MODEL;
					}
					case 1://Alcohol
					{
						StaffData[playerid][staff_giveitem] = ALCOHOL_MODEL;
					}
					case 2://Burger
					{
						StaffData[playerid][staff_giveitem] = BURGER_MODEL;
					}
					case 3://Taco
					{
						StaffData[playerid][staff_giveitem] = TACO_MODEL;
					}
					case 4://Pizza
					{
						StaffData[playerid][staff_giveitem] = PIZZA_MODEL;
					}
					case 5://Medikit
					{
						StaffData[playerid][staff_giveitem] = MEDIKIT_MODEL;
					}
					case 6://Toolbox
					{
						StaffData[playerid][staff_giveitem] = TOOLBOX_MODEL;
					}
					case 7://Gun Materials
					{
						StaffData[playerid][staff_giveitem] = MATERIALS_MODEL;
					}
					case 8://Jerrycan
					{
						StaffData[playerid][staff_giveitem] = JERRYCAN_MODEL;
					}
					case 9://Crowbar
					{
						StaffData[playerid][staff_giveitem] = CROWBAR_MODEL;
					}
					case 10://Lotto Ticket
					{
						StaffData[playerid][staff_giveitem] = TICKET_MODEL;
					}
					case 11://Seeds
					{
						StaffData[playerid][staff_giveitem] = SEEDS_MODEL;
					}
					case 12://Weed
					{
						StaffData[playerid][staff_giveitem] = WEED_MODEL;
					}
					case 13://Cell Phone
					{
						StaffData[playerid][staff_giveitem] = PHONE_MODEL;
					}
				}

				new string[200];
				format(string, sizeof(string), "{FFFFFF}How much (%s) would you like to give them?:", ReturnItemName(StaffData[playerid][staff_giveitem]));
				ShowPlayerDialog(playerid, GIVE_AMOUNT_DIALOG, DIALOG_STYLE_INPUT, "{FFFFFF}Give Item", string, "Give", "Cancel");
			}
			return 1;
		}
		case GIVE_AMOUNT_DIALOG:
		{
			if(response)
			{
				new string[300], admin[24], player[24], targetid = StaffData[playerid][staff_giveid], item = StaffData[playerid][staff_giveitem], amount = strval(inputtext);
				if(!IsNumeric(inputtext) || amount < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater that 0.");
				if(amount > 10) return SendClientMessage(playerid, RED, "ERROR: You cannot give them more than x10 items at a time.");
				if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected anymore.");
				if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned anymore.");

				if(GetPlayerVIP(targetid))
				{
					if((ReturnInventoryWeight(targetid) + (ReturnItemWeight(item) * amount)) > MAX_VIP_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The item(s) are too heavy to fit in the player's inventory.");
				}
				else
				{
					if((ReturnInventoryWeight(targetid) + (ReturnItemWeight(item) * amount)) > MAX_PLAYER_WEIGHT) return SendClientMessage(playerid, RED, "ERROR: The item(s) are too heavy to fit in the player's inventory.");
				}

				new slot = CheckInventoryForItem(targetid, item);
				if(slot == 0)
				{
					slot = GetFreeInventorySlot(targetid);
					if(slot == 0) return SendClientMessage(playerid, RED, "ERROR: The player doesn't have any free inventory slots.");
				}

				if(item == TICKET_MODEL)
				{
					if(CheckInventoryForItem(targetid, TICKET_MODEL) != 0) return SendClientMessage(playerid, RED, "ERROR: Players can only hold x1 Lotto Ticket at a time.");
					if(amount > 1) return SendClientMessage(playerid, RED, "ERROR: You cannot give players more than x1 Lotto Ticket.");
					ProcessLottoTicket(targetid);
				}
				else if(item == PHONE_MODEL)
				{
					if(!GetPlayerPhone(targetid))
					{
						GivePlayerPhone(targetid);
					}
				}

				AddItemToInventory(targetid, item, amount, false);

				GetPlayerName(playerid, admin, sizeof(admin));
				GetPlayerName(targetid, player, sizeof(player));

				if(targetid != playerid)
				{
					format(string, sizeof(string), "ADMIN: [%s] %s (%i) has given you x%i %s.", ReturnPlayerLevel(playerid), admin, playerid, amount, ReturnItemName(item));
					SendClientMessage(targetid, YELLOW, string);
				}

				format(string, sizeof(string), "ADMIN: You have given %s (%i) x%i %s.", player, targetid, amount, ReturnItemName(item));
				SendClientMessage(playerid, YELLOW, string);
				return 1;
			}
		}
	}
	return 1;
}

task OnElementsUpdate[300000]()
{
	ProcessServerElements(true);
	return 1;
}

YCMD:acmds(playerid, params[], help)
{
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	return ShowAdminDialog(playerid);
}

YCMD:bcmds(playerid, params[], help)
{
	if(GetPlayerLevel(playerid) < OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	return ShowBuilderDialog(playerid);
}

YCMD:a(playerid, params[], help)
{
	new message[100], string[144], name[24];
    if(GetPlayerLevel(playerid) < HELPER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to helpers and up.");
    if(sscanf(params, "s[100]", message)) return SendClientMessage(playerid, RED, "USAGE: /a [message]");
	if(strlen(message) < 1 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-100 characters long.");
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "[%s] %s: %s", ReturnPlayerLevel(playerid), name, message);
    StaffRadio(PINK, string);
	return 1;
}

YCMD:ann(playerid, params[], help)
{
    new message[64], string[128];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "s[64]", message)) return SendClientMessage(playerid, RED, "USAGE: /ann [message]");
	if(strlen(message) < 2 || strlen(message) > 64) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 2-64 characters long.");
	format(string, sizeof(string), "~w~%s", message);
	GameTextForAll(string, 7000, 6);
	return 1;
}

YCMD:tele(playerid, params[], help)
{
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
	return ShowTeleportDialog(playerid);
}

YCMD:abike(playerid, params[], help)
{
	new Float:pos[4];
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command inside interiors.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	TempData[playerid][temp_vehicle_id] = CreateVehicle(522, pos[0], pos[1], pos[2], pos[3], random(255), random(255), -1, 0);
	return PutPlayerInVehicle(playerid, TempData[playerid][temp_vehicle_id], 0);
}

YCMD:aheli(playerid, params[], help)
{
	new Float:pos[4];
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command inside interiors.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	TempData[playerid][temp_vehicle_id] = CreateVehicle(469, pos[0], pos[1], pos[2], pos[3], random(255), random(255), -1, 0);
	return PutPlayerInVehicle(playerid, TempData[playerid][temp_vehicle_id], 0);
}

YCMD:aboat(playerid, params[], help)
{
	new Float:pos[4];
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use this command.");
	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command inside interiors.");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	TempData[playerid][temp_vehicle_id] = CreateVehicle(452, pos[0], pos[1], pos[2], pos[3], random(255), random(255), -1, 0);
	return PutPlayerInVehicle(playerid, TempData[playerid][temp_vehicle_id], 0);
}

YCMD:mute(playerid, params[], help)
{
	new targetid, reason[32], string[128], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "us[32]", targetid, reason)) return SendClientMessage(playerid, RED, "USAGE: /mute [player] [reason]");
	if(strlen(reason) < 2 || strlen(reason) > 32) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 2-32 characters long.");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(GetPlayerLevel(targetid) > PLAYER) return SendClientMessage(playerid, RED, "ERROR: You cannot mute other staff members.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot mute yourself.");
    if(GetPlayerMuted(targetid) == true) return SendClientMessage(playerid, RED, "ERROR: That player is already muted.");

    SetPlayerMuted(targetid, true);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	format(string, sizeof(string), "ADMIN: [%s] %s (%i) has muted you.", ReturnPlayerLevel(playerid), admin, playerid);
	SendClientMessage(targetid, ORANGE, string);

	format(string, sizeof(string), "ADMIN: You have muted %s (%i).", player, targetid);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}

CMD:unmute(playerid, params[])
{
	new targetid, string[128], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /unmute [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
    if(GetPlayerMuted(targetid) == false) return SendClientMessage(playerid, RED, "ERROR: That player is not muted.");

	SetPlayerMuted(targetid, false);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	format(string, sizeof(string), "ADMIN: [%s] %s (%i) has unmuted you.", ReturnPlayerLevel(playerid), admin, playerid);
	SendClientMessage(targetid, YELLOW, string);

	format(string, sizeof(string), "ADMIN: You have unmuted %s (%i).", player, targetid);
	SendClientMessage(playerid, YELLOW, string);
	return 1;
}

YCMD:warn(playerid, params[], help)
{
	new targetid, string[144], reason[32], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "us[32]", targetid, reason)) return SendClientMessage(playerid, RED, "USAGE: /warn [player] [reason]");
	if(strlen(reason) < 2 || strlen(reason) > 32) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 2-32 characters long.");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(GetPlayerLevel(targetid) > PLAYER) return SendClientMessage(playerid, RED, "ERROR: You cannot warn other staff members.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot warn yourself.");
	
	SetPlayerWarns(targetid, GetPlayerWarns(targetid) + 1);
	
	if(GetPlayerWarns(targetid) >= MAX_WARNS)
	{
	    GetPlayerName(playerid, admin, sizeof(admin));
		GetPlayerName(targetid, player, sizeof(player));

	    format(string, sizeof(string), "AUTO: %s (%i) has been automatically kicked for: %i/%i Warnings", player, targetid, MAX_WARNS, MAX_WARNS);
	    SendClientMessageToAll(RED, string);
		return KickPlayer(targetid);
	}
	else
	{
	    format(string, sizeof(string), "WARN: [%s] %s (%i) just warned %s (%i) for: %s (%i/%i)", ReturnPlayerLevel(playerid), admin, playerid, player, targetid, reason, GetPlayerWarns(targetid), MAX_WARNS);
	    SendClientMessageToAll(RED, string);
	}
    return 1;
}

YCMD:emptyinv(playerid, params[], help)
{
	new targetid, string[128], empty[32], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /emptyinv [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	format(empty, sizeof(empty), "Empty Slot");

    EmptyPlayerInventory(targetid);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has emptied your inventory.", ReturnPlayerLevel(playerid), admin, playerid);
		SendClientMessage(targetid, ORANGE, string);
	}
	format(string, sizeof(string), "ADMIN: You have emptied %s (%i)'s inventory.", player, targetid);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}

YCMD:disarm(playerid, params[], help)
{
	new targetid, string[128], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /disarm [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

    ResetPlayerWeapons(targetid);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has disarmed you.", ReturnPlayerLevel(playerid), admin, playerid);
		SendClientMessage(targetid, ORANGE, string);
	}
	format(string, sizeof(string), "ADMIN: You have disarmed %s (%i).", player, targetid);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}

YCMD:setmoney(playerid, params[], help)
{
	new string[128], admin[24], player[24], targetid, money;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "ud", targetid, money)) return SendClientMessage(playerid, RED, "USAGE: /setmoney [player] [amount]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(money < 0) return SendClientMessage(playerid, RED, "ERROR: The amount must be at least 0.");

	ResetPlayerMoney(targetid);
	GivePlayerMoney(targetid, money);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has set your money to: $%i", ReturnPlayerLevel(playerid), admin, playerid, money);
		SendClientMessage(targetid, YELLOW, string);
	}
	format(string, sizeof(string), "ADMIN: You have set %s (%i)'s money to: $%i", player, targetid, money);
	SendClientMessage(playerid, YELLOW, string);
    return 1;
}

YCMD:setskin(playerid, params[], help)
{
	new string[128], admin[24], player[24], targetid, skinid;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "ud", targetid, skinid)) return SendClientMessage(playerid, RED, "USAGE: /setskin [player] [skin]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(skinid < 1 || skinid > 299 || skinid == 74) return SendClientMessage(playerid, RED, "ERROR: Invalid skin id. Must be from: 1-299 (Excluding 74)");

	SetPlayerSkin(targetid, skinid);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has set your skin id to: %i", ReturnPlayerLevel(playerid), admin, playerid, skinid);
		SendClientMessage(targetid, YELLOW, string);
	}
	format(string, sizeof(string), "ADMIN: You have set %s (%i)'s skin id to: %i", player, targetid, skinid);
	SendClientMessage(playerid, YELLOW, string);
    return 1;
}

YCMD:setscore(playerid, params[], help)
{
	new string[128], admin[24], player[24], targetid, score;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "ud", targetid, score)) return SendClientMessage(playerid, RED, "USAGE: /setscore [player] [score]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	SetPlayerScore(targetid, score);

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has set your score to: %i", ReturnPlayerLevel(playerid), admin, playerid, score);
		SendClientMessage(targetid, YELLOW, string);
	}

	format(string, sizeof(string), "ADMIN: You have set %s (%i)'s score to: %i", player, targetid, score);
	SendClientMessage(playerid, YELLOW, string);
    return 1;
}

YCMD:goback(playerid, params[], help)
{
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(StaffData[playerid][staff_lastx] == 0.0) return SendClientMessage(playerid, RED, "ERROR: You must go to someone before using this command.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

	SetPlayerInterior(playerid, StaffData[playerid][staff_lastinterior]);
    SetPlayerVirtualWorld(playerid, StaffData[playerid][staff_lastworld]);

    SetPlayerPos(playerid, StaffData[playerid][staff_lastx], StaffData[playerid][staff_lasty], StaffData[playerid][staff_lastz]);
    SetPlayerFacingAngle(playerid, StaffData[playerid][staff_lasta]);

    StaffData[playerid][staff_lastx] = 0.0;
	StaffData[playerid][staff_lasty] = 0.0;
	StaffData[playerid][staff_lastz] = 0.0;
	StaffData[playerid][staff_lasta] = 0.0;

	StaffData[playerid][staff_lastinterior] = 0;
	StaffData[playerid][staff_lastworld] = 0;
	return 1;
}

YCMD:goto(playerid, params[], help)
{
	new targetid, Float:pos[3], Float:get[4];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /goto [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot go to yourself.");
    if(GetPlayerJailTime(targetid) > 0) return SendClientMessage(playerid, RED, "ERROR: That player is currently in jail.");
    if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in jail.");
    if(StaffData[playerid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are spectating someone.");
    if(StaffData[targetid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: That player is currently in spectate mode.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

    GetPlayerPos(playerid, get[0], get[1], get[2]);
    GetPlayerFacingAngle(playerid, get[3]);

	StaffData[playerid][staff_lastx] = get[0];
	StaffData[playerid][staff_lasty] = get[1];
	StaffData[playerid][staff_lastz] = get[2];
	StaffData[playerid][staff_lasta] = get[3];

	StaffData[playerid][staff_lastinterior] = GetPlayerInterior(playerid);
	StaffData[playerid][staff_lastworld] = GetPlayerVirtualWorld(playerid);

    GetPlayerPos(targetid, pos[0], pos[1], pos[2]);

	if(IsPlayerInAnyVehicle(playerid))
    {
        if(GetPlayerInterior(targetid) == 0 && GetPlayerVirtualWorld(targetid) == 0)
        {
			SetVehiclePos(GetPlayerVehicleID(playerid), pos[0], pos[1], pos[2]);
		}
		else
		{
    		SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
    		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    	}
    	return 1;
	}
	else
	{
    	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
    	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	}
	return 1;
}

YCMD:get(playerid, params[], help)
{
	new targetid, Float:pos[3];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /get [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot get yourself.");
    if(GetPlayerJailTime(targetid) > 0) return SendClientMessage(playerid, RED, "ERROR: That player is currently in jail.");
    if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in jail.");
    if(StaffData[playerid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are spectating someone.");
    if(StaffData[targetid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: That player is currently in spectate mode.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if(IsPlayerInAnyVehicle(targetid))
    {
        if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
		{
	    	SetVehiclePos(GetPlayerVehicleID(targetid), pos[0], pos[1], pos[2]);
	    }
	    else
	    {
	    	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	    	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	    	SetPlayerPos(targetid, pos[0], pos[1], pos[2]);
	    }
	    return 1;
    }
    else
    {
	    SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	    SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	    SetPlayerPos(targetid, pos[0], pos[1], pos[2]);
    }
	return 1;
}

YCMD:unban(playerid, params[], help)
{
	new query[300], name[24], id;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "s[24]", name)) return SendClientMessage(playerid, RED, "USAGE: /unban [name]");

    format(query, sizeof(query), "SELECT `MASTER_ID` FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		id = db_get_field_assoc_int(database_result, "MASTER_ID");
		db_free_result@(database_result);

		format(query, sizeof(query), "SELECT `MASTER_ID` FROM `BANS` WHERE `MASTER_ID` = '%i'", id);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);

			format(query, sizeof(query), "DELETE FROM `BANS` WHERE `MASTER_ID` = '%i'", id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			return SendClientMessage(playerid, YELLOW, "SERVER: You have successfully unbanned the player.");
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: That character name is not banned.");
		}
		db_free_result@(database_result);
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: That character name is not connected to any master accounts.");
	}
	db_free_result@(database_result);
	return 1;
}

YCMD:ban(playerid, params[], help)
{
	new query[600], string[144], targetid, days, reason[32], admin[24], player[24], timestamp = 0;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "uds[32]", targetid, days, reason)) return SendClientMessage(playerid, RED, "USAGE: /ban [player] [days] [reason]");
	if(strlen(reason) < 2 || strlen(reason) > 32) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 2-32 characters long.");
	if(days < 0 || days > 365) return SendClientMessage(playerid, RED, "ERROR: Invalid days. Must be from: 0-365");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot ban yourself.");
	if(GetPlayerLevel(targetid) > PLAYER) return SendClientMessage(playerid, RED, "ERROR: You cannot ban other staff members.");

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	if(days > 0)
	{
		timestamp = gettime() + (86400 * days);
		format(string, sizeof(string), "BAN: [%s] %s (%i) has temp-banned %s (%i) for %i day(s) for: %s", ReturnPlayerLevel(playerid), admin, playerid, player, targetid, days, reason);
	}
	else
	{
		format(string, sizeof(string), "BAN: [%s] %s (%i) has perm-banned %s (%i) for: %s", ReturnPlayerLevel(playerid), admin, playerid, player, targetid, reason);
	}
	SendClientMessageToAll(RED, string);

	format(query, sizeof(query), "INSERT INTO `BANS` (`MASTER_ID`, `REASON`, `ADMIN`, `DAYS`, `TIMESTAMP`) VALUES ('%i', '%q', '%q', '%i', '%i')", GetPlayerMasterID(targetid), reason, admin, days, timestamp);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	return KickPlayer(targetid);
}

YCMD:kick(playerid, params[], help)
{
	new targetid, reason[32], string[144], admin[24], player[24];
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "us[32]", targetid, reason)) return SendClientMessage(playerid, RED, "USAGE: /kick [player] [reason]");
	if(strlen(reason) < 2 || strlen(reason) > 32) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 2-32 characters long.");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot kick yourself.");
	if(GetPlayerLevel(playerid) > PLAYER) return SendClientMessage(playerid, RED, "ERROR: You cannot kick other staff members.");

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	format(string, sizeof(string), "KICK: [%s] %s (%i) has kicked %s (%i) for: %s", ReturnPlayerLevel(playerid), admin, playerid, player, targetid, reason);
	SendClientMessageToAll(RED, string);
	return KickPlayer(targetid);
}

YCMD:spec(playerid, params[], help)
{
	new targetid;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /spec [player]");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
	OnPlayerSpectate(playerid, targetid);
	return 1;
}

YCMD:unspec(playerid, params[], help)
{
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(StaffData[playerid][staff_spectating] == false) return SendClientMessage(playerid, RED, "ERROR: You are currently not spectating anyone.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");
    TogglePlayerSpectating(playerid, false);
    return SpawnPlayer(playerid);
}

YCMD:duty(playerid, params[], help)
{
	new string[128], name[24], Float:pos[3], Float:health, Float:armour;
    if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
    if(IsPlayerSafe(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in a safezone.");
    if(GetPlayerJailTime(playerid) > 0) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in jail.");
    if(GetCameraStatus(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are in camera mode.");
    if(StaffData[playerid][staff_spectating] == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are spectating.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are injured/dead.");

    GetPlayerName(playerid, name, sizeof(name));

	if(GetDutyStatus(playerid) == false)
    {
    	SetDutyStatus(playerid, true);

		GetPlayerHealth(playerid, health);
		SetStoredHealth(playerid, health);
		if(GetPlayerVIP(playerid)) { GetPlayerArmour(playerid, armour); SetStoredArmour(playerid, armour); }

        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

        SetPlayerColor(playerid, ADMIN_COLOUR);

        SetPlayerHealth(playerid, MAX_HEALTH);
        SetPlayerArmour(playerid, 0.0);

        SetStoredWantedLevel(playerid, GetPlayerWantedLevel(playerid));
	
		StoreWeaponData(playerid);
		ResetPlayerWeapons(playerid);

        format(string, sizeof(string), "DUTY: [%s] %s (%i) has clocked-on duty. [WORKING]", ReturnPlayerLevel(playerid), name, playerid);
        return SendClientMessageToAll(GREY, string);
    }
    else if(GetDutyStatus(playerid) == true)
    {
        SetPlayerColourEx(playerid, GetPlayerJob(playerid));

        SetPlayerHealth(playerid, GetStoredHealth(playerid));
        SetPlayerArmour(playerid, GetStoredArmour(playerid));

        SetPlayerWantedLevel(playerid, GetStoredWantedLevel(playerid));

		RestoreStoredWeapons(playerid);

        SetDutyStatus(playerid, false);

       	format(string, sizeof(string), "DUTY: [%s] %s (%i) has clocked-off duty. [PLAYING]", ReturnPlayerLevel(playerid), name, playerid);
        SendClientMessageToAll(GREY, string);
    }
	return 1;
}

YCMD:h(playerid, params[], help)
{
	new question[100], name[24], string[144];
	if(GetPlayerMuted(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are muted.");
	if(sscanf(params, "s[100]", question)) return SendClientMessage(playerid, RED, "USAGE: /help [question]");
	if(strlen(question) < 1 || strlen(question) > 100) return SendClientMessage(playerid, RED, "ERROR: Your question must be from 1-100 characters long.");

	if((gettime() - 3) < GetTimerStatus(playerid, TIMER_TYPE_HELP)) return SendClientMessage(playerid, RED, "ERROR: Please wait 3 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_HELP, gettime());

    GetPlayerName(playerid, name, sizeof(name));
	if(GetPlayerLevel(playerid) > PLAYER) { format(string, sizeof(string), "HELP(/h) [%s] %s: %s", ReturnPlayerLevel(playerid), name, question); }
	else { format(string, sizeof(string), "HELP(/h): [%s] %s: %s", ReturnPlayerStatus(playerid), name, question); }
	return SendClientMessageToAll(LIGHTBLUE, string);
}

YCMD:givevip(playerid, params[], help)
{
	new query[300], string[200], player[24], admin[24], targetid, id, vip;
	if(GetPlayerLevel(playerid) < OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /givevip [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
    if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	GetPlayerName(targetid, player, sizeof(player));

	format(query, sizeof(query), "SELECT * FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", player);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		id = db_get_field_assoc_int(database_result, "MASTER_ID");
		vip = db_get_field_assoc_int(database_result, "VIP");
		db_free_result@(database_result);

		if(vip == 1) return SendClientMessage(playerid, RED, "ERROR: That player is already a V.I.P.");

		format(query, sizeof(query), "SELECT `VIP` FROM `ACCOUNTS` WHERE `MASTER_ID` = '%i'", id);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);

			format(query, sizeof(query), "UPDATE `ACCOUNTS` SET VIP = '1' WHERE `MASTER_ID` = '%i'", id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			GetPlayerName(playerid, admin, sizeof(admin));

			SetPlayerVIP(targetid, true);

			format(string, sizeof(string), "ADMIN: %s %s (%i) has given %s V.I.P status.", ReturnPlayerLevel(playerid), admin, playerid, player, targetid);
			return SendClientMessageToAll(YELLOW, string);
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: That player does not exist in the accounts table.");
		}
		db_free_result@(database_result);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: That player does not exist in the character table.");
	}
	db_free_result@(database_result);
	return 1;
}

YCMD:removevip(playerid, params[], help)
{
	new query[300], string[200], player[24], admin[24], targetid, id, vip;
	if(GetPlayerLevel(playerid) < OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /removevip [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
    if(!IsPlayerLogged(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not logged in.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	GetPlayerName(targetid, player, sizeof(player));

	format(query, sizeof(query), "SELECT * FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", player);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		id = db_get_field_assoc_int(database_result, "MASTER_ID");
		vip = db_get_field_assoc_int(database_result, "VIP");
		db_free_result@(database_result);

		if(vip == 0) return SendClientMessage(playerid, RED, "ERROR: That player doesn't have V.I.P.");

		format(query, sizeof(query), "SELECT `VIP` FROM `ACCOUNTS` WHERE `MASTER_ID` = '%i'", id);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);

			format(query, sizeof(query), "UPDATE `ACCOUNTS` SET VIP = '0' WHERE `MASTER_ID` = '%i'", id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			GetPlayerName(playerid, admin, sizeof(admin));

			SetPlayerVIP(targetid, false);

			format(string, sizeof(string), "ADMIN: %s %s (%i) has removed %s's V.I.P status.", ReturnPlayerLevel(playerid), admin, playerid, player, targetid);
			return SendClientMessageToAll(YELLOW, string);
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: That player does not exist in the accounts table.");
		}
		db_free_result@(database_result);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: That player does not exist in the character table.");
	}
	db_free_result@(database_result);
	return 1;
}

YCMD:setlevel(playerid, params[], help)
{
	new query[300], string[128], name[24], admin[24], level[16], id, promotion;
	if(!IsPlayerAdmin(playerid))
	{
		if(GetPlayerLevel(playerid) != OWNER && GetPlayerLevel(playerid) != MANAGER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners, managers, and RCON admins only.");
	}
	if(sscanf(params, "s[24]s[16]", name, level)) return SendClientMessage(playerid, RED, "USAGE: /setlevel [name] [player/helper/admin/head/manager/owner]");

	if(!strcmp(level, "player", true)) { promotion = PLAYER; }
	else if(!strcmp(level, "helper", true)) { promotion = HELPER; }
	else if(!strcmp(level, "admin", true)) { promotion = ADMIN; }
	else if(!strcmp(level, "head", true)) { promotion = HEAD; }
	else if(!strcmp(level, "manager", true)) { if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be logged in as RCON admin to set owner & manager levels."); promotion = MANAGER; }
	else if(!strcmp(level, "owner", true)) { if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be logged in as RCON admin to set owner & manager levels."); promotion = OWNER; }
	else return SendClientMessage(playerid, RED, "ERROR: Invalid level. Must be: player/helper/admin/head/manager/owner");

	format(query, sizeof(query), "SELECT `MASTER_ID` FROM `CHARACTERS` WHERE `CHARACTER_NAME` = '%q' COLLATE NOCASE", name);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		id = db_get_field_assoc_int(database_result, "MASTER_ID");
		db_free_result@(database_result);

		format(query, sizeof(query), "SELECT `LEVEL` FROM `ACCOUNTS` WHERE `MASTER_ID` = '%i'", id);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);

			format(query, sizeof(query), "UPDATE `ACCOUNTS` SET LEVEL = '%i' WHERE `MASTER_ID` = '%i'", promotion, id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

			GetPlayerName(playerid, admin, sizeof(admin));

			new targetid = GetID(name);
			if(targetid != INVALID_PLAYER_ID)
			{
				SetPlayerLevel(targetid, promotion);
			}
			
			format(string, sizeof(string), "ADMIN: %s %s (%i) has set %s's level to: %s", ReturnPlayerLevel(playerid), admin, playerid, name, ReturnLevelName(promotion));
			return SendClientMessageToAll(YELLOW, string);
		}
		else
		{
			SendClientMessage(playerid, RED, "ERROR: That name does not exist in the accounts table.");
		}
		db_free_result@(database_result);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, RED, "ERROR: That name does not exist in the character table.");
	}
	db_free_result@(database_result);
	return 1;
}

YCMD:move(playerid, params[], help)
{
	new direction[16], Float:distance, Float:pos[3];
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(sscanf(params, "s[16]f", direction, distance)) return SendClientMessage(playerid, RED, "USAGE: /move [north/south/east/west/up/down] [distance]");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    if(!strcmp(direction, "north", true)) { SetPlayerPos(playerid, pos[0], pos[1] + distance, pos[2]); }
    else if(!strcmp(direction, "south", true)) { SetPlayerPos(playerid, pos[0], pos[1] - distance, pos[2]); }
    else if(!strcmp(direction, "east", true)) { SetPlayerPos(playerid, pos[0] + distance, pos[1], pos[2]); }
    else if(!strcmp(direction, "west", true)) { SetPlayerPos(playerid, pos[0] - distance, pos[1], pos[2]); }
    else if(!strcmp(direction, "up", true)) { SetPlayerPos(playerid, pos[0], pos[1], pos[2] + distance); }
    else if(!strcmp(direction, "down", true)) { SetPlayerPos(playerid, pos[0], pos[1], pos[2] - distance); }
	else
	{
		SendClientMessage(playerid, RED, "ERROR: Invalid direction. Must be: north/south/east/west/up/down");
	}
	return 1;
}

YCMD:admins(playerid, params[], help)
{
	new query[800], total = 0, online = 0, string[200], name[24], level = PLAYER, id;
    format(query, sizeof(query), "SELECT * FROM `ACCOUNTS` WHERE `LEVEL` > '%i'", PLAYER);
    database_result = db_query@(server_database, query);
    if((total = db_num_rows(database_result)))
    {
        query[0] = EOS;
        do
        {
	        db_get_field_assoc@(database_result, "JOIN_NAME", name, sizeof(name));
	        
	      	id = db_get_field_assoc_int(database_result, "MASTER_ID");
	      	level = db_get_field_assoc_int(database_result, "LEVEL");

            if(CheckIfAdminOnline(id) != INVALID_PLAYER_ID)
            {
                format(string, sizeof(string), "{FFFFFF}[%s] %s\n", ReturnLevelName(level), name);
                online++;
            }
            else
			{
				format(string, sizeof(string), "{808080}[%s] %s\n", ReturnLevelName(level), name);
			}
			strcat(query, string);
        }
        while(db_next_row(database_result));
    }
    db_free_result@(database_result);

    if(total == 0) return SendClientMessage(playerid, RED, "ERROR: There are no admins in the database.");

	format(string, sizeof(string), "{FFFFFF}%s Admins (%i/%i Online)", SERVER_TAG, online, total);
	return ShowPlayerDialog(playerid, LIST_DIALOG, DIALOG_STYLE_LIST, string, query, "Close", "");
}

YCMD:time(playerid, params[], help)
{
	new string[128], name[24], time;
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(sscanf(params, "i", time)) return SendClientMessage(playerid, RED, "USAGE: /time [0-23]");
	if(time < 0 || time > 23) return SendClientMessage(playerid, RED, "ERROR: Invalid time. Must be from: 0-23");

	GetPlayerName(playerid, name, sizeof(name));

	format(string, sizeof(string), "TIME: %s %s (%i) has changed the time.", ReturnPlayerLevel(playerid), name, playerid);
	SendClientMessageToAll(WHITE, string);

	ElementsData[server_time] = time;
	return SetWorldTime(ElementsData[server_time]);
}

YCMD:weather(playerid, params[], help)
{
	new string[128], name[24], weather;
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(sscanf(params, "i", weather)) return SendClientMessage(playerid, RED, "USAGE: /weather [0-20]");
	if(weather < 0 || weather > 20) return SendClientMessage(playerid, RED, "ERROR: Invalid weather id. Must be from: 0-20");

	GetPlayerName(playerid, name, sizeof(name));

	format(string, sizeof(string), "WEATHER: %s %s (%i) has changed the weather.", ReturnPlayerLevel(playerid), name, playerid);
	SendClientMessageToAll(WHITE, string);

	return SetWeather(weather);
}

YCMD:giveitem(playerid, params[], help)
{
	new targetid;
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /giveitem [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	StaffData[playerid][staff_giveid] = targetid;

	return ShowPlayerDialog(playerid, GIVE_ITEM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Give Item", "{FFFFFF}Sprunk\nAlcohol\nBurger\nTaco\nPizza\nMedikit\nToolbox\nGun Materials\nJerrycan\nCrowbar\nLotto Ticket\nSeeds\nWeed\nCell Phone", "Give", "Cancel");
}

YCMD:giveweapon(playerid, params[], help)
{
	new string[200], admin[24], player[24], name[32], targetid, weapon, ammo;
	if(GetPlayerLevel(playerid) < ADMIN) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to admins and up.");
	if(sscanf(params, "uii", targetid, weapon, ammo)) return SendClientMessage(playerid, RED, "USAGE: /giveweapon [player] [weapon] [ammo]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");

	if(ammo < 1 || ammo > 5000) return SendClientMessage(playerid, RED, "ERROR: Invalid ammo amount. Must be from: 1-5000");

	for(new w; w < sizeof(BannableWeapons); w++)
  	{
    	if(weapon == BannableWeapons[w])
   		{
        	 return SendClientMessage(playerid, RED, "ERROR: That weapon id is banned.");
   		}
	}

	GetPlayerName(playerid, admin, sizeof(admin));
	GetPlayerName(targetid, player, sizeof(player));

	GetWeaponName(weapon, name, sizeof(name));

	if(targetid != playerid)
	{
		format(string, sizeof(string), "ADMIN: [%s] %s (%i) has given you a %s with %i ammo.", ReturnPlayerLevel(playerid), admin, playerid, name, ammo);
		SendClientMessage(targetid, YELLOW, string);
	}

	format(string, sizeof(string), "ADMIN: You have given %s (%i) a %s with %i ammo.", player, targetid, name, ammo);
	SendClientMessage(playerid, YELLOW, string);
	return GivePlayerWeapon(targetid, weapon, ammo);
}
