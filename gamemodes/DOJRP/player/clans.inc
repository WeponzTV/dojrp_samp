#include <YSI_Coding\y_hooks>

enum clan_data
{
	clan_name[32],
	clan_tag[8],
	clan_rank,
	bool:clan_status
};
new ClanData[MAX_PLAYERS][clan_data];

stock ClanRadio(colour, tag[], text[])
{
    foreach(new i : Player)
    {
        if(ClanData[i][clan_status] == true)
        {
            if(!strcmp(ClanData[i][clan_tag], tag, true))
            {
                SendClientMessage(i, colour, text);
            }
        }
    }
    return 1;
}

stock ReturnRankName(rank)
{
	new string[16];
	if(rank == CLAN_MEMBER)
	{
		format(string, sizeof(string), "Member");
	}
	else if(rank == CLAN_CAPTAIN)
	{
		format(string, sizeof(string), "Captain");
	}
	else if(rank == CLAN_COMMANDER)
	{
		format(string, sizeof(string), "Commander");
	}
	else if(rank == CLAN_COLEADER)
	{
		format(string, sizeof(string), "Co-Leader");
	}
	else if(rank == CLAN_LEADER)
	{
		format(string, sizeof(string), "Leader");
	}
	return string;
}

stock ReturnClanName(tag[])
{
	new query[200], field[32];
	format(query, sizeof(query), "SELECT `NAME` FROM `CLANS` WHERE `TAG` = '%q' COLLATE NOCASE", tag);
 	database_result = db_query@(server_database, query);
  	if(db_num_rows(database_result))
  	{
    	db_get_field_assoc(database_result, "NAME", field, sizeof(field));
    	db_free_result@(database_result);
	}
	return field;
}

stock CheckForClan(type, string[])
{
	new query[128];
	if(type == CLAN_TYPE_NAME)
	{
		format(query, sizeof(query), "SELECT `NAME` FROM `CLANS` WHERE `NAME` = '%q' COLLATE NOCASE", string);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);
			return 1;
		}
		db_free_result@(database_result);
	}
	else if(type == CLAN_TYPE_TAG)
	{
		format(query, sizeof(query), "SELECT `TAG` FROM `CLANS` WHERE `TAG` = '%q' COLLATE NOCASE", string);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			db_free_result@(database_result);
			return 1;
		}
		db_free_result@(database_result);
	}
	return 0;
}

stock GetPlayerClanName(playerid)
{
	new clan[64];
	if(ClanData[playerid][clan_status] == true)
	{
		format(clan, sizeof(clan), "[%s]", ClanData[playerid][clan_tag]);
	}
	else
	{
		format(clan, sizeof(clan), "None");
	}
	return clan;
}

stock LoadPlayerClan(playerid)
{
	new query[200], tag[8];
	format(query, sizeof(query), "SELECT * FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
 	database_result = db_query@(server_database, query);
  	if(db_num_rows(database_result))
  	{
    	db_get_field_assoc@(database_result, "TAG", tag, sizeof(tag));
    	ClanData[playerid][clan_tag] = tag;

    	ClanData[playerid][clan_rank] = db_get_field_assoc_int(database_result, "RANK");

		db_free_result@(database_result);

    	ClanData[playerid][clan_name] = ReturnClanName(tag);

    	ClanData[playerid][clan_status] = true;

    	if(CheckForClan(CLAN_TYPE_TAG, ClanData[playerid][clan_tag]) == 0)
    	{
			format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);

	    	ClanData[playerid][clan_status] = false;

	    	SendClientMessage(playerid, ORANGE, "NOTICE: Your clan no longer exists in the database.");
    	}
    	return 1;
	}
	else
	{
	    ClanData[playerid][clan_status] = false;
	}
	db_free_result@(database_result);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		SetIsInvited(playerid, false);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case CLAN_CREATE_DIALOG:
		{
		    if(response)
		    {
		        new query[600], string[128], tag[8], clan[32];
		        if(strlen(inputtext) < 2 || strlen(inputtext) > 32) return SendClientMessage(playerid, RED, "ERROR: Your clan name must be from 2-32 characters long.");
		        if(CheckForClan(CLAN_TYPE_NAME, inputtext) == 1) return SendClientMessage(playerid, RED, "ERROR: That clan name already exists, please choose another name.");

				format(clan, sizeof(clan), "%s", inputtext);
				ClanData[playerid][clan_name] = clan;

				format(tag, sizeof(tag), "%s", GetClanTag(playerid));
				ClanData[playerid][clan_tag] = tag;

				ClanData[playerid][clan_rank] = CLAN_LEADER;

				ClanData[playerid][clan_status] = true;

				format(query, sizeof(query), "INSERT INTO `MEMBERS` (`CHARACTER_ID`, `TAG`, `RANK`) VALUES ('%i', '%q', '%i')", GetPlayerCharacterID(playerid), ClanData[playerid][clan_tag], ClanData[playerid][clan_rank]);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

		        format(query, sizeof(query), "INSERT INTO `CLANS` (`TAG`, `NAME`) VALUES ('%q', '%q')", ClanData[playerid][clan_tag], ClanData[playerid][clan_name]);
				database_result = db_query@(server_database, query);
				db_free_result@(database_result);

				format(string, sizeof(string), "SERVER: You have successfully created the clan: [%s] %s", ClanData[playerid][clan_tag], ClanData[playerid][clan_name]);
	           	SendClientMessage(playerid, YELLOW, string);
		    }
		    return 1;
		}
	}
	return 1;
}

YCMD:cm(playerid, params[], help)
{
	new string[200], message[128], name[24];
	if(ClanData[playerid][clan_status] == false) return SendClientMessage(playerid, RED, "ERROR: You are not a member of any clans.");
	if(sscanf(params, "s[128]", message)) return SendClientMessage(playerid, RED, "USAGE: /cm [message]");
    if(strlen(message) < 1 || strlen(message) > 128) return SendClientMessage(playerid, RED, "ERROR: Your message must be from 1-128 characters long.");

    GetPlayerName(playerid, name, sizeof(name));
    format(string, sizeof(string), "CLAN: [%s] %s (%i) says: %s", ReturnRankName(ClanData[playerid][clan_rank]), name, playerid, message);
	ClanRadio(PINK, ClanData[playerid][clan_tag], string);
	return 1;
}

YCMD:clanlist(playerid, params[], help)
{
	new query[800], tag[6], total = 0, online = 0, string[128], string2[128], field[128], rank, characterid;
	if(sscanf(params, "s[6]", tag)) return SendClientMessage(playerid, RED, "USAGE: /clanlist [tag]");
	if(CheckForClan(CLAN_TYPE_TAG, tag) == 0) return SendClientMessage(playerid, RED, "ERROR: That clan tag does not exist in the database.");

    format(query, sizeof(query), "SELECT `CHARACTER_ID`, `RANK` FROM `MEMBERS` WHERE `TAG` = '%q' COLLATE NOCASE", tag);
    database_result = db_query@(server_database, query);
    if((total = db_num_rows(database_result)))
    {
        query[0] = EOS;
        do
        {
	        characterid = db_get_field_assoc_int(database_result, "CHARACTER_ID");
	        rank = db_get_field_assoc_int(database_result, "RANK");

            if(GetPlayerID(field) != INVALID_PLAYER_ID)
            {
                format(string, sizeof(string), "{FFFFFF}[%s] %s\n", ReturnRankName(rank), ReturnCharacterName(characterid));
                online++;
            }
            else
			{
				format(string, sizeof(string), "{808080}[%s] %s\n", ReturnRankName(rank), ReturnCharacterName(characterid));
			}
			strcat(query, string);
        }
        while(db_next_row(database_result));
    }

    db_free_result@(database_result);

	format(string2, sizeof(string2), "{FFFFFF}[%s] %s (%i/%i Online)", tag, ReturnClanName(tag), online, total);
	ShowPlayerDialog(playerid, CLAN_MEMBERS_DIALOG, DIALOG_STYLE_LIST, string2, query, "Close", "");
	return 1;
}

YCMD:createclan(playerid, params[], help)
{
	new tag[8], string[128], string2[8];
 	if(ClanData[playerid][clan_status] == true) return SendClientMessage(playerid, RED, "ERROR: You are already in a clan, use /leaveclan before creating another one.");
 	if(GetPlayerScore(playerid) < MIN_SCORE_CREATE_CLAN && !GetPlayerVIP(playerid))
 	{
		format(string, sizeof(string), "ERROR: You need at least %i score to be able to create a clan.", MIN_SCORE_CREATE_CLAN);
		return SendClientMessage(playerid, RED, string);
 	}
	if(sscanf(params, "s[8]", tag)) return SendClientMessage(playerid, RED, "USAGE: /createclan [tag]");
	if(strlen(tag) < 2 || strlen(tag) > 5) return SendClientMessage(playerid, RED, "ERROR: Your clan tag must be from 2-5 characters long.");
	if(strfind(tag, "[", true) != -1 || strfind(tag, "]", true) != -1 || strfind(tag, "(", true) != -1 || strfind(tag, ")", true) != -1) return SendClientMessage(playerid, RED, "ERROR: Your clan tag must not contain any brackets.");
	if(CheckForClan(CLAN_TYPE_TAG, tag) == 1) return SendClientMessage(playerid, RED, "ERROR: That clan tag already exists, please choose another tag.");

	format(string2, sizeof(string2), "%s", tag);
	SetClanTag(playerid, string2);

	format(string, sizeof(string), "{FFFFFF}Create Clan > [%s]", tag);
    return ShowPlayerDialog(playerid, CLAN_CREATE_DIALOG, DIALOG_STYLE_INPUT, string, "{FFFFFF}Please enter a name for your clan below:", "Create", "Cancel");
}

YCMD:leaveclan(playerid, params[], help)
{
	new query[200], string[128], name[24];
	if(ClanData[playerid][clan_status] == false) return SendClientMessage(playerid, RED, "ERROR: You are not a member of any clans.");
    if(ClanData[playerid][clan_rank] == CLAN_LEADER)
    {
        format(query, sizeof(query), "DELETE FROM `CLANS` WHERE `TAG` = '%q' COLLATE NOCASE", ClanData[playerid][clan_tag]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `TAG` = '%q' COLLATE NOCASE", ClanData[playerid][clan_tag]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

   		ClanData[playerid][clan_status] = false;

        SendClientMessage(playerid, ORANGE, "CLAN: You have left your clan, all members have been removed from the database.");

		foreach(new i : Player)
		{
		    if(ClanData[i][clan_status] == true && playerid != i)
		    {
		        if(!strcmp(ClanData[i][clan_tag], ClanData[playerid][clan_tag], true))
		        {
        			ClanData[i][clan_status] = false;
        			SendClientMessage(i, ORANGE, "CLAN: The leader of your clan has left, the clan no longer exists.");
		        }
		    }
		}
        return 1;
    }
    else
	{
        format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);

		GetPlayerName(playerid, name, sizeof(name));
		format(string, sizeof(string), "CLAN: [%s] %s (%i) has left the clan.", ReturnRankName(ClanData[playerid][clan_rank]), name, playerid);
		ClanRadio(PINK, ClanData[playerid][clan_tag], string);

   		ClanData[playerid][clan_status] = false;
	}
	return 1;
}

YCMD:clankick(playerid, params[], help)
{
	new targetid, query[128], string[128], reason[64], name[24];
	if(ClanData[playerid][clan_status] == false) return SendClientMessage(playerid, RED, "ERROR: You are not a member of any clans.");
	if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");
	if(sscanf(params, "us[64]", targetid, reason)) return SendClientMessage(playerid, RED, "USAGE: /clankick [player] [reason]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(ClanData[targetid][clan_status] == false) return SendClientMessage(playerid, RED, "ERROR: That player is not a member of any clans.");
	if(strcmp(ClanData[targetid][clan_tag], ClanData[playerid][clan_tag], true)) return SendClientMessage(playerid, RED, "ERROR: That player is not a member of your clan.");
	if(strlen(reason) < 1 || strlen(reason) > 64) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 1-64 characters long.");
	if(ClanData[targetid][clan_rank] == CLAN_LEADER || ClanData[targetid][clan_rank] == CLAN_COLEADER) return SendClientMessage(playerid, RED, "ERROR: You cannot kick a Leader/Co-Leader from the clan.");

	format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(targetid));
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

    GetPlayerName(targetid, name, sizeof(name));
    format(string, sizeof(string), "CLAN: [%s] %s (%i) has been kicked from the clan.", ReturnRankName(ClanData[targetid][clan_rank]), name, targetid);
	ClanRadio(PINK, ClanData[playerid][clan_tag], string);

	ClanData[targetid][clan_status] = false;
	return 1;
}

YCMD:offlinekick(playerid, params[], help)
{
	new query[128], string[128], name[24], reason[64], field[6], rank, characterid;
	if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");
	if(sscanf(params, "s[24]s[64]", name, reason)) return SendClientMessage(playerid, RED, "USAGE: /offlinekick [name] [reason]");
	if(strlen(reason) < 1 || strlen(reason) > 64) return SendClientMessage(playerid, RED, "ERROR: Your reason must be from 1-64 characters long.");
	if(ReturnCharacterID(name) == 0) return SendClientMessage(playerid, RED, "ERROR: That name does not exist in the database.");

	format(query, sizeof(query), "SELECT * FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", ReturnCharacterID(name));
 	database_result = db_query@(server_database, query);
  	if(db_num_rows(database_result))
  	{
    	characterid = db_get_field_assoc_int(database_result, "CHARACTER_ID");

    	rank = db_get_field_assoc_int(database_result, "RANK");
    	if(strval(field) == CLAN_LEADER || strval(field) == CLAN_COLEADER) return SendClientMessage(playerid, RED, "ERROR: You cannot kick a Leader/Co-Leader from the clan.");

    	db_get_field_assoc(database_result, "TAG", field, sizeof(field));
		
		db_free_result@(database_result);

    	if(!strcmp(ClanData[playerid][clan_tag], field, true))
    	{
			format(query, sizeof(query), "DELETE FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", characterid);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
			
    		format(string, sizeof(string), "CLAN: [%s] %s has been offline kicked from the clan.", ReturnRankName(rank), ReturnCharacterName(characterid));
			ClanRadio(PINK, ClanData[playerid][clan_tag], string);
    	}
		else
		{
 			SendClientMessage(playerid, RED, "ERROR: That player is not a member of your clan.");
		}
		return 1;
	}
	else
	{
	    SendClientMessage(playerid, RED, "ERROR: That player is not a member of any clans.");
	}
	db_free_result@(database_result);
	return 1;
}

YCMD:clanrank(playerid, params[], help)
{
	new targetid, query[300], string[128], rank[16], name[24], new_rank[16], tag[8], clan[32];
	if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");

	if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) { if(sscanf(params, "us[16]", targetid, rank)) return SendClientMessage(playerid, RED, "USAGE: /clanrank [player] [member/captain]"); }
	else if(ClanData[playerid][clan_rank] == CLAN_COLEADER) { if(sscanf(params, "us[16]", targetid, rank)) return SendClientMessage(playerid, RED, "USAGE: /clanrank [player] [member/captain/commander]"); }
	else if(ClanData[playerid][clan_rank] == CLAN_LEADER) { if(sscanf(params, "us[16]", targetid, rank)) return SendClientMessage(playerid, RED, "USAGE: /clanrank [player] [member/captain/commander/coleader]"); }

	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(strcmp(ClanData[targetid][clan_tag], ClanData[playerid][clan_tag], true)) return SendClientMessage(playerid, RED, "ERROR: That player is not a member of your clan.");
	if(targetid == playerid) return SendClientMessage(playerid, RED, "ERROR: You cannot set your own clan rank.");
	if(ClanData[playerid][clan_rank] != CLAN_LEADER && ClanData[targetid][clan_rank] == CLAN_LEADER || ClanData[targetid][clan_rank] == CLAN_COLEADER) return SendClientMessage(playerid, RED, "ERROR: You cannot promote/demote a Leader/Co-Leader of the clan.");

	format(tag, sizeof(tag), "%s", ClanData[playerid][clan_tag]);
	format(clan, sizeof(clan), "%s", ClanData[playerid][clan_name]);

	if(!strcmp(rank, "member", true))
	{
		if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");
	 	ClanData[targetid][clan_rank] = CLAN_MEMBER;
    	format(new_rank, sizeof(new_rank), "Member");
    }
    else if(!strcmp(rank, "captain", true))
	{
		if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");
	 	ClanData[targetid][clan_rank] = CLAN_CAPTAIN;
    	format(new_rank, sizeof(new_rank), "Captain");
    }
    else if(!strcmp(rank, "commander", true))
	{
		if(ClanData[playerid][clan_rank] < CLAN_COLEADER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Co-Leaders and above.");
	 	ClanData[targetid][clan_rank] = CLAN_COMMANDER;
    	format(new_rank, sizeof(new_rank), "Commander");
    }
    else if(!strcmp(rank, "coleader", true))
	{
		if(ClanData[playerid][clan_rank] != CLAN_LEADER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to the Leader only.");
	 	ClanData[targetid][clan_rank] = CLAN_COLEADER;
    	format(new_rank, sizeof(new_rank), "Co-Leader");
    }
    else return SendClientMessage(playerid, RED, "ERROR: Invalid rank.");

	ClanData[targetid][clan_name] = clan;
	ClanData[targetid][clan_tag] = tag;
	ClanData[targetid][clan_status] = true;

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "CLAN: %s (%i) is now ranked as a: %s", name, targetid, new_rank);
	ClanRadio(PINK, ClanData[playerid][clan_tag], string);

	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `MEMBERS` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(targetid));
 	database_result = db_query@(server_database, query);
  	if(db_num_rows(database_result))
  	{
		db_free_result@(database_result);

		format(query, sizeof(query), "UPDATE `MEMBERS` SET RANK = '%i' WHERE `CHARACTER_ID` = '%i'", ClanData[targetid][clan_rank], GetPlayerCharacterID(targetid));
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `MEMBERS` (`CHARACTER_ID`, `TAG`, `RANK`) VALUES ('%i', '%q', '%i')", GetPlayerCharacterID(targetid), ClanData[targetid][clan_tag], ClanData[playerid][clan_rank]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	return 1;
}

YCMD:claninvite(playerid, params[], help)
{
	new targetid, string[128], string2[8], name[24];
	if(ClanData[playerid][clan_rank] < CLAN_COMMANDER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to Commanders and above.");
	if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, RED, "USAGE: /claninvite [player]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is not connected.");
	if(IsPlayerNPC(targetid)) return SendClientMessage(playerid, RED, "ERROR: That player is an NPC.");
	if(ClanData[targetid][clan_status] == true) return SendClientMessage(playerid, RED, "ERROR: That player is in another clan, ask them to /leaveclan first.");

	format(string2, sizeof(string2), "%s", ClanData[playerid][clan_tag]);
	SetClanInvite(playerid, string2);

	SetIsInvited(targetid, true);

	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "CLAN: %s (%i) has invited you to join their clan. Type /clanaccept to accept their offer.", name, playerid);
	SendClientMessage(targetid, ORANGE, string);

	GetPlayerName(targetid, name, sizeof(name));
	format(string, sizeof(string), "CLAN: You have offered %s (%i) a position in your clan, wait for their response.", name, targetid);
	SendClientMessage(playerid, ORANGE, string);
	return 1;
}

YCMD:clanaccept(playerid, params[], help)
{
	new query[300], string[128], tag[8], field[32], name[24];
	if(GetIsInvited(playerid) == false) return SendClientMessage(playerid, RED, "ERROR: You have not been invited to any clans.");
	if(CheckForClan(CLAN_TYPE_TAG, GetClanInvite(playerid)) == 0) return SendClientMessage(playerid, RED, "ERROR: The clan no longer exists.");

	format(query, sizeof(query), "SELECT `NAME` FROM `CLANS` WHERE `TAG` = '%q' COLLATE NOCASE", GetClanInvite(playerid));
 	database_result = db_query@(server_database, query);
  	if(db_num_rows(database_result))
  	{
    	db_get_field_assoc(database_result, "NAME", field, sizeof(field));
    	ClanData[playerid][clan_name] = field;
   	}
	db_free_result@(database_result);

	format(tag, sizeof(tag), "%s", GetClanInvite(playerid));
    ClanData[playerid][clan_tag] = tag;
    ClanData[playerid][clan_rank] = CLAN_MEMBER;
	ClanData[playerid][clan_status] = true;

	SetIsInvited(playerid, false);

	format(query, sizeof(query), "INSERT INTO `MEMBERS` (`CHARACTER_ID`, `TAG`, `RANK`) VALUES ('%i', '%q', '%i')", GetPlayerCharacterID(playerid), ClanData[playerid][clan_tag], ClanData[playerid][clan_rank]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);
	
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "CLAN: [%s] %s (%i) has just joined the clan.", ReturnRankName(ClanData[playerid][clan_rank]), name, playerid);
	ClanRadio(PINK, ClanData[playerid][clan_tag], string);
	return 1;
}
