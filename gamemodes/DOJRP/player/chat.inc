#include <YSI_Coding\y_hooks>

hook OnPlayerText(playerid, text[])
{
	new Float:pos[3], string[144], name[24];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerName(playerid, name, sizeof(name));

	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 25.0, pos[0], pos[1], pos[2]) && GetPlayerInterior(i) == GetPlayerInterior(playerid) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
	 	{
			format(string, sizeof(string), "%s: {FFFFFF}%s (Local)", name, text);
		 	SendClientMessage(i, GetPlayerColor(playerid), string);
	    }
	}

	SetPlayerChatBubble(playerid, text, WHITE, 15.0, 5000);
	return 0;
}

YCMD:g(playerid, params[], help)
{
	new message[100], name[24], string[144];
	if(GetPlayerMuted(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: You cannot use this command while you are muted.");
	if(sscanf(params, "s[100]", message)) return SendClientMessage(playerid, RED, "USAGE: /g [message]");
	if(strlen(message) < 1 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-100 characters long.");

	if((gettime() - 3) < GetTimerStatus(playerid, TIMER_TYPE_GLOBAL)) return SendClientMessage(playerid, RED, "ERROR: Please wait 3 seconds before using this command again.");
	SetTimerStatus(playerid, TIMER_TYPE_GLOBAL, gettime());

    GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "CHAT(/g): %s: %s (Global)", name, message);
	return SendClientMessageToAll(LIGHTGREEN, string);
}

YCMD:s(playerid, params[], help)
{
	new Float:pos[3], message[100], name[24], string[144];
	if(sscanf(params, "s[100]", message)) return SendClientMessage(playerid, RED, "USAGE: /s [message]");
	if(strlen(message) < 1 || strlen(message) > 100) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-100 characters long.");

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 50.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			format(string, sizeof(string), "%s shouts: %s!", name, message);
			SendClientMessage(i, WHITE, string);
		}
	}
	return 1;
}

YCMD:me(playerid, params[], help)
{
	new Float:pos[3], action[100], name[24], string[144];
	if(sscanf(params, "s[100]", action)) return SendClientMessage(playerid, RED, "USAGE: /me [action]");
	if(strlen(action) < 1 || strlen(action) > 100) return SendClientMessage(playerid, RED, "ERROR: Your action must be from 1-100 characters long.");

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 25.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			format(string, sizeof(string), "%s %s", name, action);
			SendClientMessage(i, WHITE, string);
		}
	}
	return 1;
}

YCMD:ooc(playerid, params[], help)
{
	new Float:pos[3], text[100], name[24], string[144];
	if(sscanf(params, "s[100]", text)) return SendClientMessage(playerid, RED, "USAGE: /ooc [text]");
	if(strlen(text) < 1 || strlen(text) > 100) return SendClientMessage(playerid, RED, "ERROR: Your text must be from 1-100 characters long.");

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 25.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			format(string, sizeof(string), "[OOC] %s: (( %s ))", name, text);
			SendClientMessage(i, GREY, string);
		}
	}
	return 1;
}

YCMD:b(playerid, params[], help)
{
	new Float:pos[3], action[100], name[24], string[144];
	if(sscanf(params, "s[100]", action)) return SendClientMessage(playerid, RED, "USAGE: /b [action]");
	if(strlen(action) < 1 || strlen(action) > 100) return SendClientMessage(playerid, RED, "ERROR: Your action must be from 1-100 characters long.");

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 25.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			format(string, sizeof(string), "(( %s says: %s ))", name, action);
			SendClientMessage(i, GREY, string);
		}
	}
	return 1;
}

YCMD:do(playerid, params[], help)
{
	new Float:pos[3], action[100], name[24], string[144];
	if(sscanf(params, "s[100]", action)) return SendClientMessage(playerid, RED, "USAGE: /do [action]");
	if(strlen(action) < 1 || strlen(action) > 100) return SendClientMessage(playerid, RED, "ERROR: Your action must be from 1-100 characters long.");

	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	foreach(new i : Player)
	{
	    if(IsPlayerInRangeOfPoint(i, 25.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			format(string, sizeof(string), "%s ((%s))", name, action);
			SendClientMessage(i, GREY, string);
		}
	}
	return 1;
}
