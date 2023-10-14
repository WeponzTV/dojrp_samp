#include <YSI_Coding\y_hooks>

stock ShowCommandsDialog(playerid)
{
	return ShowPlayerDialog(playerid, CMDS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Server Commands", "{FFFFFF}General Commands\nChat Commands\nAnimation Commands\nVehicle Commands\nJob Commands\nProperty Commands\nClan Commands", "Select", "Cancel");
}

public e_COMMAND_ERRORS:OnPlayerCommandPerformed(playerid, cmdtext[], e_COMMAND_ERRORS:success)
{
    if(success == COMMAND_UNDEFINED)
    {
        SendClientMessage(playerid, RED, "ERROR: Invalid command. Type /cmds for the list of server commands."); 
        return COMMAND_UNDEFINED;
    }
    return COMMAND_OK;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case CMDS_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						ShowPlayerDialog(playerid, GENERAL_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > General", "{FFFFFF}/rules /admins /vip /stats /changepass /h /report /pc /pay /loc /escape /break /payticket /harvest /phone /inventory /call911 /acceptdeath /acmds", "Back", "Close");
					}
					case 1:
					{
						ShowPlayerDialog(playerid, CHAT_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Chat", "{FFFFFF}/g /ooc /s /b /do /me", "Back", "Close");
					}
					case 2:
					{
						ShowPlayerDialog(playerid, ANIMATION_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Animations", "{FFFFFF}/dance /laugh /piss /chat /fucku /vomit /slapass /wave /handsup\n/deal /(g)sit /lay /taichi /cry /smoke /crack /aim /relax /cpr", "Back", "Close");
					}
					case 3:
					{
						ShowPlayerDialog(playerid, VEHICLE_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Vehicles", "{FFFFFF}/park /lock /engine /lights /trunk /hood /alarm /torch /findcars", "Back", "Close");
					}
					case 4:
					{
						ShowPlayerDialog(playerid, JOB_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Jobs", "{FFFFFF}/ar /cf /tk /r /e /bail /(d)strip /(d)block /confiscate /heal /fires /flight /haul", "Back", "Close");
					}
					case 5:
					{
						ShowPlayerDialog(playerid, PROPERTY_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Properties", "{FFFFFF}/hmenu /bmenu /buybusiness /sell(house/business) /accept(house/business) /decline(house/business)", "Back", "Close");
					}
					case 6:
					{
						ShowPlayerDialog(playerid, CLAN_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}Server Commands > Clans", "{FFFFFF}/cm /createclan /leaveclan /clankick /offlinekick /clanrank /clanlist /claninvite /clanaccept", "Back", "Close");
					}
				}
			}
			return 1;
		}
		case VEHICLE_DIALOG, GENERAL_DIALOG, CHAT_DIALOG, ANIMATION_DIALOG, JOB_DIALOG, PROPERTY_DIALOG, CLAN_DIALOG:
		{
			if(response)
			{
				ShowCommandsDialog(playerid);
			}
			return 1;
		}
	}
	return 1;
}

YCMD:cmds(playerid, params[], help)
{
	return ShowCommandsDialog(playerid);
}

YCMD:pc(playerid, params[], help)
{
	return ShowPlayerDialog(playerid, COLOURS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Player Colors", "{FFFFFF}Civilians/CIA Agents (White)\n{FFFF00}Offenders (Yellow)\n{FF0000}Suspects (Red)\n{0000FF}Police Officers (Blue)\n{008000}Army Soldiers (Green)\n{808080}Prisoners (Grey)\n{FFC0CB}Emergency Services (Pink)\n{800080}Admins (Purple)\n{FFA500}Workers (Orange)", "Close", "");
}

YCMD:rules(playerid, params[], help)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}%s Server Rules", SERVER_TAG);
	ShowPlayerDialog(playerid, RULES_DIALOG, DIALOG_STYLE_LIST, string, "{FFFFFF}Rule #1: No spamming, flooding, or advertising things.\nRule #2: No trolling, racism, or hate speech is aloud.\nRule #3: No bug abusing aloud + avoiding arrest/death.\nRule #4: No driving damaged vehicles, you must fix it.\nRule #5: No abusing help chat for normal communcation.\nRule #6: No using symbols or unrealistic character names.", "Close", "");
	return 1;
}

YCMD:report(playerid, params[], help)
{
	new targetid, reporter[24], reportee[24], reason[64], string[144];
	if(GetPlayerMuted(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are muted.");
	if(sscanf(params, "us[64]", targetid, reason)) return SendClientMessage(playerid, RED, "USAGE: /report [player] [reason]");
	if(strlen(reason) < 1 || strlen(reason) > 64) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 1-64 characters long.");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
    if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not spawned.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot report yourself.");

	if((gettime() - 30) < GetTimerStatus(playerid, TIMER_TYPE_REPORT)) return SendClientMessage(playerid, RED, "ERROR: Please wait 30 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_REPORT, gettime());

    GetPlayerName(playerid, reporter, sizeof(reporter));
    GetPlayerName(targetid, reportee, sizeof(reportee));

	format(string, sizeof(string), "REPORT: %s (%i) just reported %s (%i) for: %s", reporter, playerid, reportee, targetid, reason);
	StaffRadio(RED, string);

	format(string, sizeof(string), "NOTICE: You have just reported %s (%i) for: %s (DO NOT SPAM /REPORT!)", reportee, targetid, reason);
	return SendClientMessage(playerid, ORANGE, string);
}

YCMD:pay(playerid, params[], help)
{
	new string[128], name[24], targetid, amount, Float:pos[3];
    if(sscanf(params, "ui", targetid, amount)) return SendClientMessage(playerid, RED, "USAGE: /pay [player] [amount]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot heal yourself.");
	if(amount < 1) return SendClientMessage(playerid, RED, "ERROR: You must input a number greater than 0.");
	if(GetPlayerMoneyEx(playerid) < amount) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money on you.");

    GetPlayerPos(targetid, pos[0], pos[1], pos[2]);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return SendClientMessage(playerid, RED, "ERROR: You must be within 5 metres of the player to pay them.");

    GivePlayerMoney(playerid, -amount);
    GivePlayerMoney(targetid, amount);

    ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
    ApplyAnimation(targetid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    format(string, sizeof(string), "SERVER: %s (%i) has just paid you $%i.", name, playerid, amount);
    SendClientMessage(targetid, YELLOW, string);

	GetPlayerName(targetid, name, sizeof(name));
    format(string, sizeof(string), "SERVER: You have just paid %s (%i) $%i.", name, targetid, amount);
    SendClientMessage(playerid, ORANGE, string);
	return 1;
}

YCMD:changepass(playerid, params[], help)
{
	if(!IsPlayerLogged(playerid)) return SendClientMessage(playerid, RED, "ERROR: You must be logged in to use this command.");
	return ShowPasswordDialog(playerid);
}

YCMD:vip(playerid, params[], help)
{
	return ShowPlayerDialog(playerid, VIP_DIALOG, DIALOG_STYLE_MSGBOX, "{FFFFFF}V.I.P Features", "{FFFFFF}#1: Bypass all score restrictions!\n#2: Never lose your weapons upon death!\n#3: Spawn at hospitals with full armour!\n#4: Access to full weapon skills!\n#5: More inventory slots and max weight!\n#6: Own more properties and vehicles!", "Close", "");
}
