#include <YSI_Coding\y_hooks>

forward OnPlayerUseMachine(playerid);

new Iterator:Sprunks<MAX_SPRUNKS>;

enum sprunk_data
{
	sprunk_object,
	sprunk_area,
	sprunk_interior,
	sprunk_world,
	Float:sprunk_x,
	Float:sprunk_y,
	Float:sprunk_z,
	Float:sprunk_r
};
new SprunkData[MAX_SPRUNKS][sprunk_data];

stock LoadSprunkMachines()
{
	new query[200];
    for(new i = 0; i < MAX_SPRUNKS; i++)
    {
    	format(query, sizeof(query), "SELECT * FROM `SPRUNKS` WHERE `ID` = %i", i);
		database_result = db_query@(server_database, query);
		if(db_num_rows(database_result))
		{
			SprunkData[i][sprunk_x] = db_get_field_assoc_float(database_result, "X");
			SprunkData[i][sprunk_y] = db_get_field_assoc_float(database_result, "Y");
			SprunkData[i][sprunk_z] = db_get_field_assoc_float(database_result, "Z");
			SprunkData[i][sprunk_r] = db_get_field_assoc_float(database_result, "R");

			SprunkData[i][sprunk_interior] = db_get_field_assoc_int(database_result, "INTERIOR");
			SprunkData[i][sprunk_world] = db_get_field_assoc_int(database_result, "WORLD");

			SprunkData[i][sprunk_object] = CreateDynamicObject(1775, SprunkData[i][sprunk_x], SprunkData[i][sprunk_y], SprunkData[i][sprunk_z], 0.0, 0.0, SprunkData[i][sprunk_r], SprunkData[i][sprunk_world], SprunkData[i][sprunk_interior], -1, 100.0);
			SprunkData[i][sprunk_area] = CreateDynamicSphere(SprunkData[i][sprunk_x], SprunkData[i][sprunk_y], SprunkData[i][sprunk_z], 1.5, SprunkData[i][sprunk_world], SprunkData[i][sprunk_interior], -1, 0);

			Iter_Add(Sprunks, i);
		}
		db_free_result@(database_result);
    }
    return 1;
}

stock UnloadSprunkMachines()
{
	foreach(new i : Sprunks)
	{
		DestroyDynamicObject(SprunkData[i][sprunk_object]);
		DestroyDynamicArea(SprunkData[i][sprunk_area]);

		Iter_Remove(Sprunks, i);
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		RemoveBuildingForPlayer(playerid, 955, 0.0, 0.0, 0.0, 6000.0);//Sprunk Vending Machine #1
		RemoveBuildingForPlayer(playerid, 1775, 0.0, 0.0, 0.0, 6000.0);//Sprunk Vending Machine #2

		RemoveBuildingForPlayer(playerid, 956, 0.0, 0.0, 0.0, 6000.0);//Normal Vending Machine #1
		RemoveBuildingForPlayer(playerid, 1776, 0.0, 0.0, 0.0, 6000.0);//Normal Vending Machine #2
		
		RemoveBuildingForPlayer(playerid, 1209, 0.0, 0.0, 0.0, 6000.0);//Soda Vending Machine #1
		RemoveBuildingForPlayer(playerid, 1302, 0.0, 0.0, 0.0, 6000.0);//Soda Vending Machine #2
	}
	return 1;
}

public OnPlayerUseMachine(playerid)//Do not hook
{
	SetPlayerThirst(playerid, GetPlayerThirst(playerid) + 25);
	if(GetPlayerThirst(playerid) > 100) { SetPlayerThirst(playerid, 100); }
	return ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 4.1, 0, 0, 0, 0, 0);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerNPC(playerid)) return 1;

	if((((newkeys & (KEY_SECONDARY_ATTACK)) == (KEY_SECONDARY_ATTACK)) && ((oldkeys & (KEY_SECONDARY_ATTACK)) != (KEY_SECONDARY_ATTACK))))
	{
		if(IsPlayerInAnyDynamicArea(playerid, 0))
		{
			foreach(new i : Sprunks)
			{
				if(IsPlayerInDynamicArea(playerid, SprunkData[i][sprunk_area], 0))
				{
					if(GetPlayerMoneyEx(playerid) < 1) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money for the drink.");
					if(GetPlayerThirst(playerid) >= 100) return SendClientMessage(playerid, RED, "ERROR: You are currently not thirsty.");
					
					new Float:x = SprunkData[i][sprunk_x], Float:y = SprunkData[i][sprunk_y];
					x -= (1.0 * floatsin(-SprunkData[i][sprunk_r], degrees));
					y -= (1.0 * floatcos(-SprunkData[i][sprunk_r], degrees));

					SetPlayerPos(playerid, x, y, SprunkData[i][sprunk_z]);
					SetPlayerFacingAngle(playerid, SprunkData[i][sprunk_r]);
					SetCameraBehindPlayer(playerid);

					GivePlayerMoney(playerid, -1);

					ApplyAnimation(playerid, "VENDING", "VEND_Use", 4.1, 0, 0, 0, 0, 0);
					return SetTimerEx("OnPlayerUseMachine", 2600, false, "d", playerid);
				}
			}
		}
	}
	return 1;
}

YCMD:createsprunk(playerid, params[], help)
{
	new query[400], Float:pos[4], direction[8], id = Iter_Free(Sprunks);
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");
	if(id == INVALID_ITERATOR_SLOT) return SendClientMessage(playerid, RED, "ERROR: You have reached the max aloud sprunk machines. (Increase MAX_SPRUNKS in sprunk.pwn)");
	if(sscanf(params, "s[8]", direction)) return SendClientMessage(playerid, RED, "USAGE: /createsprunk [north/south/east/west]");
	
	if(!strcmp(direction, "north", true)) { SprunkData[id][sprunk_r] = 180.0; }
	else if(!strcmp(direction, "south", true)) { SprunkData[id][sprunk_r] = 0.0; }
	else if(!strcmp(direction, "east", true)) { SprunkData[id][sprunk_r] = 90.0; }
	else if(!strcmp(direction, "west", true)) { SprunkData[id][sprunk_r] = -90.0; }
	else return SendClientMessage(playerid, -1, "SERVER: Invalid direction. Must be: north/south/east/west");
	
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);

	SprunkData[id][sprunk_x] = pos[0];
	SprunkData[id][sprunk_y] = pos[1];
	SprunkData[id][sprunk_z] = pos[2];

	SprunkData[id][sprunk_interior] = GetPlayerInterior(playerid);
	SprunkData[id][sprunk_world] = GetPlayerVirtualWorld(playerid);
	
	SprunkData[id][sprunk_object] = CreateDynamicObject(1775, SprunkData[id][sprunk_x], SprunkData[id][sprunk_y], SprunkData[id][sprunk_z], 0.0, 0.0, SprunkData[id][sprunk_r], SprunkData[id][sprunk_world], SprunkData[id][sprunk_interior], -1, 100.0);
	SprunkData[id][sprunk_area] = CreateDynamicSphere(SprunkData[id][sprunk_x], SprunkData[id][sprunk_y], SprunkData[id][sprunk_z], 1.5, SprunkData[id][sprunk_world], SprunkData[id][sprunk_interior], -1, 0);

	format(query, sizeof(query), "INSERT INTO `SPRUNKS` (`ID`, `X`, `Y`, `Z`, `R`, `INTERIOR`, `WORLD`) VALUES ('%i', '%f', '%f', '%f', '%f', '%i', '%i')", id, SprunkData[id][sprunk_x], SprunkData[id][sprunk_y], SprunkData[id][sprunk_z], SprunkData[id][sprunk_r], SprunkData[id][sprunk_interior], SprunkData[id][sprunk_world]);
	database_result = db_query@(server_database, query);
	db_free_result@(database_result);

	Iter_Add(Sprunks, id);

	pos[0] -= (1.5 * floatsin(-pos[3], degrees));
	pos[1] -= (1.5 * floatcos(-pos[3], degrees));

	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	format(query, sizeof(query), "SERVER: Sprunk Machine Created! (%i/%i Created)", Iter_Count(Sprunks), MAX_SPRUNKS);
	return SendClientMessage(playerid, YELLOW, query);
}

YCMD:deletesprunk(playerid, params[], help)
{
	new query[200], interior = GetPlayerInterior(playerid), world = GetPlayerVirtualWorld(playerid);
	if(GetPlayerLevel(playerid) != OWNER) return SendClientMessage(playerid, RED, "ERROR: This command is restricted to owners only.");

	foreach(new i : Sprunks)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, SprunkData[i][sprunk_x], SprunkData[i][sprunk_y], SprunkData[i][sprunk_z]) && interior == SprunkData[i][sprunk_interior] && world == SprunkData[i][sprunk_world])
		{
			DestroyDynamicObject(SprunkData[i][sprunk_object]);
			DestroyDynamicArea(SprunkData[i][sprunk_area]);

			Iter_Remove(Sprunks, i);

			format(query, sizeof(query), "DELETE FROM `SPRUNKS` WHERE `ID` = %i", i);
		    database_result = db_query@(server_database, query);
		 	db_free_result@(database_result);

			format(query, sizeof(query), "SERVER: Sprunk Machine Deleted! (%i/%i Left)", Iter_Count(Sprunks), MAX_SPRUNKS);
			return SendClientMessage(playerid, ORANGE, query);
		}
	}
	return SendClientMessage(playerid, RED, "ERROR: There are no sprunk machines nearby to delete.");
}
