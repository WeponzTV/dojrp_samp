#include <YSI_Coding\y_hooks>

enum anim_data
{
	bool:anim_status
};
new AnimStatus[MAX_PLAYERS][anim_data];

stock bool:GetAnimationStatus(playerid) return AnimStatus[playerid][anim_status];
stock SetAnimationStatus(playerid, bool:status) return AnimStatus[playerid][anim_status] = status;

stock PreloadAnimations(playerid)
{
	ApplyAnimation(playerid, "PARACHUTE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PAULNMAC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MEDIC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PED", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RAPPING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SHOP", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BEACH", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ON_LOOKERS", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DEALER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CRACK", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PARK", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FOOD", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BAR", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BOMBER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SMOKING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CAR", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GYMNASIUM", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CASINO", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ROB_BANK", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COLT45", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SILENCED", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TEC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "UZI", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RIFLE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRENADE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "WUZI", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "VENDING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRAVEYARD", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RAPPING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWEET", "null", 0.0, 0, 0, 0, 0, 0);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		PreloadAnimations(playerid);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetAnimationStatus(playerid) == true)//Enter
  	{
    	SetAnimationStatus(playerid, false);
	  	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	  	ClearAnimations(playerid);
	}
	return 1;
}

YCMD:laugh(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s laughs at %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s laughs...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:piss(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    SetPlayerSpecialAction(playerid, 68);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s pisses on %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s takes a piss...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:chat(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "PED", "IDLE_chat", 4.1, 1, 1, 1, 1, 1);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s chats with %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s chats with themselves...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:fucku(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "PED", "fucku", 4.1, 0, 1, 1, 1, 1);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s tells %s to get fucked...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s says fuck you...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:vomit(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s vomits all over %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s vomits...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:slapass(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s slaps %s's ass...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s slaps their own ass...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:wave(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s waves at %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s waves at nobody...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:deal(playerid, params[], help)
{
    new Float:pos[3], string[128], name1[24], name2[24], targetid = GetClosestPlayerID(playerid, 5.0);
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name1, sizeof(name1));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			if(targetid != INVALID_PLAYER_ID)
			{
    			GetPlayerName(targetid, name2, sizeof(name2));
   				format(string, sizeof(string), "** %s makes a deal with %s...", name1, name2);
				SendClientMessage(i, GREY, string);
			}
			else
			{
   				format(string, sizeof(string), "** %s makes a deal with nobody...", name1);
				SendClientMessage(i, GREY, string);
			}
		}
	}
    return 1;
}

YCMD:cry(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "GRAVEYARD", "mrnF_loop", 4.1, 0, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s cries...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:handsup(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s puts their hands up...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:crack(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s overdoses on crack...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:smoke(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s puffs on a cigarette...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:gsit(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "BEACH", "ParkSit_M_loop", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s sits on the ground...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:sit(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "PED", "SEAT_idle", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s sits down...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:taichi(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "PARK", "Tai_Chi_Loop", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s performs taichi...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:lay(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "BEACH", "bather", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s lays down...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:aim(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "PED", "gang_gunstand", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s takes aim...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:relax(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "BEACH", "Lay_BLoop", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s relaxes...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:cpr(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24];
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 1, 0, 0, 0, 0);

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s performs CPR...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}

YCMD:dance(playerid, params[], help)
{
    new Float:pos[3], string[128], name[24], style;
    if((gettime() - 4) < GetTimerStatus(playerid, TIMER_TYPE_ANIM)) return SendClientMessage(playerid, RED, "ERROR: Please wait 4 seconds before using an animation command again.");
    SetTimerStatus(playerid, TIMER_TYPE_ANIM, gettime());

    if(sscanf(params, "d", style)) return SendClientMessage(playerid, RED, "USAGE: /dance [1-4]");
	if(style < 1 || style > 4) return SendClientMessage(playerid, RED, "ERROR: Invalid style. Must be from: 1-4");

    if(GetAnimationStatus(playerid) == true) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop your current animation before using another.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) return SendClientMessage(playerid, RED, "ERROR: Press ENTER to stop smoking weed before using an animation.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, RED, "ERROR: You must be on foot to use animations.");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are cuffed.");
	if(IsPlayerInjured(playerid)) return SendClientMessage(playerid, RED, "ERROR: You cannot use animations while you are injured/dead.");

    SetAnimationStatus(playerid, true);
    if(style == 1)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
	}
	else if(style == 2)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
	}
	else if(style == 3)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
	}
	else if(style == 4)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
	}

    GetPlayerName(playerid, name, sizeof(name));
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

   	foreach(new i : Player)
   	{
   		if(IsPlayerInRangeOfPoint(i, 15.0, pos[0], pos[1], pos[2]) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
   		{
   			format(string, sizeof(string), "** %s dances...", name);
			SendClientMessage(i, GREY, string);
		}
	}
    return 1;
}
