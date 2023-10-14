#include <YSI_Coding\y_hooks>

enum gym_data
{
	ls_gym_ent_cp,
	ls_gym_exit_cp,
	ls_gym_ring1_cp,
	ls_gym_ring2_cp,
	ls_gym_mat_cp,
	ls_gym_mat_pickup,

	sf_gym_ent_cp,
	sf_gym_exit_cp,
	sf_gym_mat_cp,
	sf_gym_mat_pickup,

	lv_gym_ent_cp,
	lv_gym_exit_cp,
	lv_gym_ring1_cp,
	lv_gym_ring2_cp,
	lv_gym_mat_cp,
	lv_gym_mat_pickup
};
new GymData[gym_data];

stock ShowGymDialog(playerid, city)
{
	new string[400], normal[32], boxing[32], kungfu[32], knee[32], grab[32], elbow[32];
	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_NORMAL) { format(normal, sizeof(normal), "{808080}Normal Style: FREE"); }
	else { format(normal, sizeof(normal), "{FFFFFF}Normal Style: FREE"); }

	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_BOXING) { format(boxing, sizeof(boxing), "{808080}Boxing Style: $1000"); }
	else { format(boxing, sizeof(boxing), "{FFFFFF}Boxing Style: $1000"); }

	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_KUNGFU) { format(kungfu, sizeof(kungfu), "{808080}Kung Fu Style: $1000"); }
	else { format(kungfu, sizeof(kungfu), "{FFFFFF}Kung Fu Style: $1000"); }

	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_KNEEHEAD) { format(knee, sizeof(knee), "{808080}Knee/Head Style: $500"); }
	else { format(knee, sizeof(knee), "{FFFFFF}Knee/Head Style: $500"); }

	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_GRABKICK) { format(grab, sizeof(grab), "{808080}Grab/Kick Style: $500"); }
	else { format(grab, sizeof(grab), "{FFFFFF}Grab/Kick Style: $500"); }

	if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_ELBOW) { format(elbow, sizeof(elbow), "{808080}Elbow Style: $500"); }
	else { format(elbow, sizeof(elbow), "{FFFFFF}Elbow Style: $500"); }
	
	format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s", normal, boxing, kungfu, knee, grab, elbow);
	if(city == LOS_SANTOS) { ShowPlayerDialog(playerid, GYM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos Gym > Fighting Styles", string, "Learn", "Cancel"); }
	else if(city == SAN_FIERRO) { ShowPlayerDialog(playerid, GYM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro Gym > Fighting Styles", string, "Learn", "Cancel"); }
	else if(city == LAS_VENTURAS) { ShowPlayerDialog(playerid, GYM_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas Gym > Fighting Styles", string, "Learn", "Cancel"); }
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2229.874267, -1721.230224, 13.560964, 54, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Gym
	CreateDynamicMapIcon(-2270.647949, -155.977355, 35.320312, 54, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Gym
	CreateDynamicMapIcon(1968.757324, 2295.873291, 16.455863, 54, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Gym

	GymData[ls_gym_mat_pickup] = CreateDynamicPickup(1239, 1, 772.977966, 5.388990, 1000.780212, -1, -1, -1, 50.0, -1, 0);//LS Gym Mat
	GymData[sf_gym_mat_pickup] = CreateDynamicPickup(1239, 1, 756.380981, -47.988388, 1000.780212, -1, -1, -1, 50.0, -1, 0);//SF Gym Mat
	GymData[lv_gym_mat_pickup] = CreateDynamicPickup(1239, 1, 759.178710, -60.043254, 1000.780212, -1, -1, -1, 50.0, -1, 0);//LV Gym Mat

	GymData[ls_gym_ent_cp] = CreateDynamicCP(2229.874267, -1721.230224, 13.560964, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Gym Entrance
	GymData[ls_gym_exit_cp] = CreateDynamicCP(772.329406, -5.516098, 1000.728515, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Gym Exit
	GymData[ls_gym_ring1_cp] = CreateDynamicCP(764.097473, 9.823188, 1000.712463, 1.0, -1, -1, -1, 3.0, -1, 0);//LS Gym Ring Checkpoint (Entrance)
	GymData[ls_gym_ring2_cp] = CreateDynamicCP(763.300598, 9.823188, 1001.163940, 1.0, -1, -1, -1, 3.0, -1, 0);//LS Gym Ring Checkpoint (Exit)
	GymData[ls_gym_mat_cp] = CreateDynamicCP(772.977966, 5.388990, 1000.780212, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Gym Mat

	GymData[sf_gym_ent_cp] = CreateDynamicCP(-2270.647949, -155.977355, 35.320312, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Gym Entrance
	GymData[sf_gym_exit_cp] = CreateDynamicCP(774.153076, -50.477329, 1000.585937, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Gym Exit
	GymData[sf_gym_mat_cp] = CreateDynamicCP(756.380981, -47.988388, 1000.780212, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Gym Mat

	GymData[lv_gym_ent_cp] = CreateDynamicCP(1968.757324, 2295.873291, 16.455863, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Gym Entrance
	GymData[lv_gym_exit_cp] = CreateDynamicCP(773.933532, -78.846588, 1000.662780, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Gym Exit
	GymData[lv_gym_ring1_cp] = CreateDynamicCP(770.082214, -70.000000, 1000.656250, 1.0, -1, -1, -1, 3.0, -1, 0);//LV Gym Ring Checkpoint (Entrance)
	GymData[lv_gym_ring2_cp] = CreateDynamicCP(769.137451, -70.000000, 1001.569152, 1.0, -1, -1, -1, 3.0, -1, 0);//LV Gym Ring Checkpoint (Exit)
	GymData[lv_gym_mat_cp] = CreateDynamicCP(759.178710, -60.043254, 1000.780212, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Gym Mat
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case GYM_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Normal Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_NORMAL) return SendClientMessage(playerid, RED, "ERROR: You already have a Normal Fighting Style.");

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Normal Fighting Style.");
					}
					case 1://Boxing Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_BOXING) return SendClientMessage(playerid, RED, "ERROR: You already have a Boxing Fighting Style.");
						if(GetPlayerMoneyEx(playerid) < 1000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this fighting style.");

						GivePlayerMoney(playerid, -1000);

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Boxing Fighting Style.");
					}
					case 2://Kung Fu Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_KUNGFU) return SendClientMessage(playerid, RED, "ERROR: You already have a Kung Fu Fighting Style.");
						if(GetPlayerMoneyEx(playerid) < 1000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this fighting style.");

						GivePlayerMoney(playerid, -1000);

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Kung Fu Fighting Style.");
					}
					case 3://Knee/Head Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_KNEEHEAD) return SendClientMessage(playerid, RED, "ERROR: You already have a Knee/Head Fighting Style.");
						if(GetPlayerMoneyEx(playerid) < 500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this fighting style.");

						GivePlayerMoney(playerid, -500);

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Knee/Head Fighting Style.");
					}
					case 4://Grab/Kick Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_GRABKICK) return SendClientMessage(playerid, RED, "ERROR: You already have a Grab/Kick Fighting Style.");
						if(GetPlayerMoneyEx(playerid) < 500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this fighting style.");

						GivePlayerMoney(playerid, -500);

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Grab/Kick Fighting Style.");
					}
					case 5://Elbow Style
					{
						if(GetPlayerFightingStyle(playerid) == FIGHT_STYLE_ELBOW) return SendClientMessage(playerid, RED, "ERROR: You already have an Elbow Fighting Style.");
						if(GetPlayerMoneyEx(playerid) < 500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this fighting style.");

						GivePlayerMoney(playerid, -500);

						SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);

						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully learned the Elbow Fighting Style.");
					}
				}
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == GymData[ls_gym_mat_pickup] || pickupid == GymData[sf_gym_mat_pickup] || pickupid == GymData[lv_gym_mat_pickup])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == GymData[ls_gym_ent_cp])
		{
			SetPlayerInterior(playerid, 5);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 772.297912, -3.932916, 1000.729248);
			SetPlayerFacingAngle(playerid, 1.242852);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[ls_gym_exit_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2228.885742, -1722.161865, 13.562500);
			SetPlayerFacingAngle(playerid, 133.420410);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[ls_gym_ring1_cp])
		{
			SetPlayerPos(playerid, 761.855041, 9.823188, 1001.163940);
			SetPlayerFacingAngle(playerid, 88.611351);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[ls_gym_ring2_cp])
		{
			SetPlayerPos(playerid, 765.302917, 9.823188, 1000.711669);
			SetPlayerFacingAngle(playerid, 268.460662);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[ls_gym_mat_cp])
		{
			return ShowGymDialog(playerid, LOS_SANTOS);
		}
		else if(checkpointid == GymData[sf_gym_ent_cp])
		{
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 774.105407, -49.141838, 1000.585937);
			SetPlayerFacingAngle(playerid, 2.186595);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[sf_gym_exit_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, -2269.235595, -156.009735, 35.320312);
			SetPlayerFacingAngle(playerid, 269.439178);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[sf_gym_mat_cp])
		{
			return ShowGymDialog(playerid, SAN_FIERRO);
		}
		else if(checkpointid == GymData[lv_gym_ent_cp])
		{
			SetPlayerInterior(playerid, 7);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 773.941040, -77.508972, 1000.660827);
			SetPlayerFacingAngle(playerid, 359.562103);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[lv_gym_exit_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 1968.735961, 2294.652832, 16.455863);
			SetPlayerFacingAngle(playerid, 178.492584);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[lv_gym_ring1_cp])
		{
			SetPlayerPos(playerid, 767.989318, -70.000000, 1001.569152);
			SetPlayerFacingAngle(playerid, 90.164955);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[lv_gym_ring2_cp])
		{
			SetPlayerPos(playerid, 771.341491, -70.000000, 1000.656250);
			SetPlayerFacingAngle(playerid, 270.179016);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == GymData[lv_gym_mat_cp])
		{
			ShowGymDialog(playerid, LAS_VENTURAS);
		}
		return 1;
	}
	return 1;
}
