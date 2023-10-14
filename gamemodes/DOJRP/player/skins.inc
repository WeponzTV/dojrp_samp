//Credits: Kye (Base Code)
#include <YSI_Coding\y_hooks>

#define MAX_LISTITEMS 21

#define DIALOG_BASE_X 80.0
#define DIALOG_BASE_Y 100.0
#define DIALOG_WIDTH 550.0
#define DIALOG_HEIGHT 170.0
#define SPRITE_DIM_X 60.0
#define SPRITE_DIM_Y 70.0

new PlayerText:CurrentPage[MAX_PLAYERS];
new PlayerText:HeaderText[MAX_PLAYERS];
new PlayerText:DialogBackground[MAX_PLAYERS];
new PlayerText:NextButton[MAX_PLAYERS];
new PlayerText:PrevButton[MAX_PLAYERS];
new PlayerText:SelectedItem[MAX_PLAYERS][MAX_LISTITEMS];

new SkinData[MAX_PLAYERS][MAX_LISTITEMS];

new MaxSkins = 276;

new CivilianSkins[276] = 
{
	/*0,*/1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,/*16,*/17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
	51,52,53,54,55,56,57,58,59,60,/*61,*/62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,
	99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,/*165,166,*/167,168,169,170,
	171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,
	207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,
	243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,/*260,*/261,262,263,264,/*265,266,267,*/268,269,270,271,272,273,/*274,275,276,277,
	278,279,280,281,282,283,284,285,286,287,288,*/289,290,291,292,293,294,295,296,297,298,299
};

new PoliceSkins[11] =
{
	265,266,267,280,281,282,283,284,285,286,288
};

new CIASkins[2] =
{
	165,166
};

new ArmySkins[1] =
{
	287
};

new ParamedicSkins[3] =
{
	274,275,276
};

new FireSkins[3] =
{
	277,278,279
};

new WorkerSkins[2] =
{
	16,260
};

new PilotSkins[1] =
{
	61
};

enum request_data
{
	bool:request_civ,
	bool:request_cop,
	bool:request_cia,
	bool:request_army,
	bool:request_ems,
	bool:request_fire,
	bool:request_miner,
	bool:request_pilot,
	bool:request_trucker
};
new RequestData[MAX_PLAYERS][request_data];

stock SetSkinRequest(playerid, type, bool:status)
{
	if(type == REQUEST_TYPE_CIV) return RequestData[playerid][request_civ] = status;
	else if(type == REQUEST_TYPE_COP) return RequestData[playerid][request_cop] = status;
	else if(type == REQUEST_TYPE_CIA) return RequestData[playerid][request_cia] = status;
	else if(type == REQUEST_TYPE_ARMY) return RequestData[playerid][request_army] = status;
	else if(type == REQUEST_TYPE_EMS) return RequestData[playerid][request_ems] = status;
	else if(type == REQUEST_TYPE_FIRE) return RequestData[playerid][request_fire] = status;
	else if(type == REQUEST_TYPE_MINER) return RequestData[playerid][request_miner] = status;
	else if(type == REQUEST_TYPE_PILOT) return RequestData[playerid][request_pilot] = status;
	else if(type == REQUEST_TYPE_TRUCKER) return RequestData[playerid][request_trucker] = status;
	return 1;
}

stock PlayerText:CreateCurrentPageTextDraw(playerid, Float:x, Float:y)
{
	new PlayerText:textdraw;
   	textdraw = CreatePlayerTextDraw(playerid, x, y, "0/0");
   	PlayerTextDrawUseBox(playerid, textdraw, 0);
	PlayerTextDrawLetterSize(playerid, textdraw, 0.4, 1.1);
	PlayerTextDrawFont(playerid, textdraw, 1);
	PlayerTextDrawSetShadow(playerid, textdraw, 0);
    PlayerTextDrawSetOutline(playerid, textdraw, 1);
    PlayerTextDrawColor(playerid, textdraw, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, textdraw);
    return textdraw;
}

stock PlayerText:CreatePlayerDialogButton(playerid, Float:x, Float:y, Float:width, Float:height, text[])
{
 	new PlayerText:textdraw;
   	textdraw = CreatePlayerTextDraw(playerid, x, y, text);
   	PlayerTextDrawUseBox(playerid, textdraw, 1);
   	PlayerTextDrawBoxColor(playerid, textdraw, 0x000000FF);
   	PlayerTextDrawBackgroundColor(playerid, textdraw, 0x000000FF);
	PlayerTextDrawLetterSize(playerid, textdraw, 0.2, 1.0);
	PlayerTextDrawFont(playerid, textdraw, 1);
	PlayerTextDrawSetShadow(playerid, textdraw, 0);
    PlayerTextDrawSetOutline(playerid, textdraw, 0);
    PlayerTextDrawColor(playerid, textdraw, 0x4A5A6BFF);
    PlayerTextDrawSetSelectable(playerid, textdraw, 1);
    PlayerTextDrawAlignment(playerid, textdraw, 2);
    PlayerTextDrawTextSize(playerid, textdraw, height, width);
    PlayerTextDrawShow(playerid, textdraw);
    return textdraw;
}

stock PlayerText:CreatePlayerHeaderTextDraw(playerid, Float:x, Float:y, text[])
{
	new PlayerText:textdraw;
   	textdraw = CreatePlayerTextDraw(playerid, x, y, text);
   	PlayerTextDrawUseBox(playerid, textdraw, 0);
	PlayerTextDrawLetterSize(playerid, textdraw, 1.25, 3.0);
	PlayerTextDrawFont(playerid, textdraw, 0);
	PlayerTextDrawSetShadow(playerid, textdraw, 0);
    PlayerTextDrawSetOutline(playerid, textdraw, 1);
    PlayerTextDrawColor(playerid, textdraw, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, textdraw);
    return textdraw;
}

stock PlayerText:CreatePlayerBackgroundTextDraw(playerid, Float:x, Float:y, Float:width, Float:height)
{
	new PlayerText:background = CreatePlayerTextDraw(playerid, x, y, 
	"                                                        ~n~");
    PlayerTextDrawUseBox(playerid, background, 1);
    PlayerTextDrawBoxColor(playerid, background, 0x4A5A6BBB);
	PlayerTextDrawLetterSize(playerid, background, 5.0, 5.0);
	PlayerTextDrawFont(playerid, background, 0);
	PlayerTextDrawSetShadow(playerid, background, 0);
    PlayerTextDrawSetOutline(playerid, background, 0);
    PlayerTextDrawColor(playerid, background,0x000000FF);
    PlayerTextDrawTextSize(playerid, background, width, height);
   	PlayerTextDrawBackgroundColor(playerid, background, 0x4A5A6BBB);
    PlayerTextDrawShow(playerid, background);
    return background;
}

stock PlayerText:CreateModelPreviewTextDraw(playerid, modelindex, Float:x, Float:y, Float:width, Float:height)
{
    new PlayerText:sprite = CreatePlayerTextDraw(playerid, x, y, "");
    PlayerTextDrawFont(playerid, sprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, sprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, sprite, 0x88888899);
    PlayerTextDrawTextSize(playerid, sprite, width, height);
    PlayerTextDrawSetPreviewModel(playerid, sprite, modelindex);
    PlayerTextDrawSetSelectable(playerid, sprite, 1);
    PlayerTextDrawShow(playerid,sprite);
    return sprite;
}

stock UpdatePageTextDraw(playerid)
{
	new text[64+1], skins = 0;

	if(MaxSkins >= MAX_LISTITEMS && MaxSkins % MAX_LISTITEMS == 0)
	{
		skins = (MaxSkins / MAX_LISTITEMS);
	}
	else
	{
		skins = (MaxSkins / MAX_LISTITEMS) + 1;
	}

	format(text, sizeof(text), "%i/%i", GetPVarInt(playerid,"skin_page") + 1, skins);
	PlayerTextDrawSetString(playerid, CurrentPage[playerid], text);
	return 1;
}

stock DestroySkinMenu(playerid)
{
	new i = 0;
	while(i != MAX_LISTITEMS)
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	PlayerTextDrawDestroy(playerid, HeaderText[playerid]);
	PlayerTextDrawDestroy(playerid, DialogBackground[playerid]);
	PlayerTextDrawDestroy(playerid, CurrentPage[playerid]);
	PlayerTextDrawDestroy(playerid, NextButton[playerid]);
	PlayerTextDrawDestroy(playerid, PrevButton[playerid]);

	HeaderText[playerid] = PlayerText:INVALID_TEXT_DRAW;
    DialogBackground[playerid] = PlayerText:INVALID_TEXT_DRAW;
    CurrentPage[playerid] = PlayerText:INVALID_TEXT_DRAW;
    NextButton[playerid] = PlayerText:INVALID_TEXT_DRAW;
    PrevButton[playerid] = PlayerText:INVALID_TEXT_DRAW;

    SetPVarInt(playerid, "skin_page", 0);

    if(IsPlayerNew(playerid))
    {
    	SetPlayerNew(playerid, false);
    	SetPlayerHealth(playerid, 100.0);

		SendClientMessage(playerid, YELLOW, "NOTE: Not sure how to play? Type /h to ask a question and someone will assist you.");
    }
    return 1;
}

stock ShowCivilianModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = GetPVarInt(playerid, "skin_page") * MAX_LISTITEMS;
	
	while(i != MAX_LISTITEMS)
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != MAX_LISTITEMS && itemid < sizeof(CivilianSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, CivilianSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = CivilianSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowPoliceModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(PoliceSkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(PoliceSkins) && itemid < sizeof(PoliceSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, PoliceSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = PoliceSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowCIAModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(CIASkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(CIASkins) && itemid < sizeof(CIASkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, CIASkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = CIASkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowArmyModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(ArmySkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(ArmySkins) && itemid < sizeof(ArmySkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, ArmySkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = ArmySkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowParamedicModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(ParamedicSkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(ParamedicSkins) && itemid < sizeof(ParamedicSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, ParamedicSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = ParamedicSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowFirefighterModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(FireSkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(FireSkins) && itemid < sizeof(FireSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, FireSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = FireSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowWorkerModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(WorkerSkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(WorkerSkins) && itemid < sizeof(WorkerSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, WorkerSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = WorkerSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowPilotModelPreviews(playerid)
{
    new l = 0, i = 0, linetracker = 0, Float:x = DIALOG_BASE_X, Float:y = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33);
	new itemid = 0;
	
	while(i != sizeof(PilotSkins))
	{
		if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
			SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		i++;
	}

	while(l != sizeof(PilotSkins) && itemid < sizeof(PilotSkins))
	{
	    if(linetracker == 0)
	    {
	        x = DIALOG_BASE_X + 25.0;
	        y += SPRITE_DIM_Y + 1.0;
		}

		SelectedItem[playerid][l] = CreateModelPreviewTextDraw(playerid, PilotSkins[itemid], x, y, SPRITE_DIM_X, SPRITE_DIM_Y);
		SkinData[playerid][l] = PilotSkins[itemid];

		x += SPRITE_DIM_X + 1.0;
		linetracker++;

		if(linetracker == 7)
		{
			linetracker = 0;
		}

		itemid++;
		l++;
	}
	return 1;
}

stock ShowPoliceSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Police Skins");

	ShowPoliceModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowCIASkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "CIA Skins");

	ShowCIAModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowArmySkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Army Skins");

	ShowArmyModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowParamedicSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Paramedic Skins");

	ShowParamedicModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowFirefighterSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Firefighter Skins");

	ShowFirefighterModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowWorkerSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Worker Skins");

	ShowWorkerModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowPilotSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Pilot Skins");

	ShowPilotModelPreviews(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

stock ShowCivilianSkinMenu(playerid)
{
	//if(GetPVarInt(playerid, "skin_active") == 1) { DestroySkinMenu(playerid); }
		
	SetPVarInt(playerid, "skin_active", 1);

	TogglePlayerHUDTextdraws(playerid, false);
	    
	DialogBackground[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
	HeaderText[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, "Civilian Skins");
	CurrentPage[playerid] = CreateCurrentPageTextDraw(playerid, DIALOG_WIDTH - 30.0, DIALOG_BASE_Y + 15.0);
	NextButton[playerid] = CreatePlayerDialogButton(playerid, DIALOG_WIDTH - 30.0, DIALOG_BASE_Y + DIALOG_HEIGHT + 100.0, 50.0, 10.0, "Next");
	PrevButton[playerid] = CreatePlayerDialogButton(playerid, DIALOG_WIDTH - 90.0, DIALOG_BASE_Y + DIALOG_HEIGHT + 100.0, 50.0, 10.0, "Prev");

	ShowCivilianModelPreviews(playerid);
	UpdatePageTextDraw(playerid);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(!IsPlayerNPC(playerid))
    {
		RequestData[playerid][request_civ] = false;
		RequestData[playerid][request_cop] = false;
		RequestData[playerid][request_cia] = false;
		RequestData[playerid][request_army] = false;
		RequestData[playerid][request_ems] = false;
		RequestData[playerid][request_fire] = false;
		RequestData[playerid][request_miner] = false;
		RequestData[playerid][request_pilot] = false;
		RequestData[playerid][request_trucker] = false;

		new i = 0;
		while(i != MAX_LISTITEMS)
		{
			if(SelectedItem[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, SelectedItem[playerid][i]);
				SelectedItem[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}
			i++;
		}

		PlayerTextDrawDestroy(playerid, HeaderText[playerid]);
		PlayerTextDrawDestroy(playerid, DialogBackground[playerid]);
		PlayerTextDrawDestroy(playerid, CurrentPage[playerid]);
		PlayerTextDrawDestroy(playerid, NextButton[playerid]);
		PlayerTextDrawDestroy(playerid, PrevButton[playerid]);

		HeaderText[playerid] = PlayerText:INVALID_TEXT_DRAW;
	    DialogBackground[playerid] = PlayerText:INVALID_TEXT_DRAW;
	    CurrentPage[playerid] = PlayerText:INVALID_TEXT_DRAW;
	    NextButton[playerid] = PlayerText:INVALID_TEXT_DRAW;
	    PrevButton[playerid] = PlayerText:INVALID_TEXT_DRAW;

	    SetPVarInt(playerid, "skin_page", 0);
	    SetPVarInt(playerid, "skin_active", 0);
	}
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)//hooking does not work..
{
   	if(GetPVarInt(playerid, "skin_active") == 0) return 0;

	if(clickedid == Text:INVALID_TEXT_DRAW)//ESC
	{
		if(RequestData[playerid][request_civ] == false)
		{
			new job = GetPlayerJob(playerid);
			if(job == POLICE_JOB || RequestData[playerid][request_cop] == true)
	        {
	        	ShowPoliceSkinMenu(playerid);
	        }
	        else if(job == CIA_JOB || RequestData[playerid][request_cia] == true)
	        {
	        	ShowCIASkinMenu(playerid);
	        }
	        else if(job == ARMY_JOB || RequestData[playerid][request_army] == true)
	        {
	        	ShowArmySkinMenu(playerid);
	        }
	        else if(job == EMS_JOB || RequestData[playerid][request_ems] == true)
	        {
	        	ShowParamedicSkinMenu(playerid);
	        }
	        else if(job == FIRE_JOB || RequestData[playerid][request_fire] == true)
	        {
	        	ShowFirefighterSkinMenu(playerid);
	        }
	        else if(job == MINER_JOB || RequestData[playerid][request_miner] == true)
	        {
	        	ShowWorkerSkinMenu(playerid);
	        }
	        else if(job == PILOT_JOB || RequestData[playerid][request_pilot] == true)
	        {
	        	ShowPilotSkinMenu(playerid);
	        }
	        else if(job == TRUCKER_JOB || RequestData[playerid][request_trucker] == true)
	        {
	        	ShowWorkerSkinMenu(playerid);
	        }
	        else
	        {
	        	ShowCivilianSkinMenu(playerid);
	        }
    	}
	 	else
		{
	   		ShowCivilianSkinMenu(playerid);
	 	}
	}
	return 0;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)//hooking does not work..
{
	if(GetPVarInt(playerid, "skin_active") == 0) return 0;

	new page = GetPVarInt(playerid, "skin_page"), skins = 0;

	if(MaxSkins >= MAX_LISTITEMS && MaxSkins % MAX_LISTITEMS == 0)
	{
		skins = (MaxSkins / MAX_LISTITEMS);
	}
	else
	{
		skins = (MaxSkins / MAX_LISTITEMS) + 1;
	}
	
	if(playertextid == NextButton[playerid])
	{
	    if(page < (skins - 1))
	    {
	        SetPVarInt(playerid, "skin_page", page + 1);
	        ShowCivilianModelPreviews(playerid);
         	UpdatePageTextDraw(playerid);
         	PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		}
		else
		{
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
	
	if(playertextid == PrevButton[playerid])
	{
	    if(page > 0)
	    {
	    	SetPVarInt(playerid, "skin_page", page - 1);
	    	ShowCivilianModelPreviews(playerid);
	    	UpdatePageTextDraw(playerid);
	    	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		}
		else
		{
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
	
	new i = 0;
	while(i != MAX_LISTITEMS)
	{
	    if(playertextid == SelectedItem[playerid][i])
	    {
	 		new job = CIVILIAN_JOB;
	    	if(RequestData[playerid][request_cop] == true || RequestData[playerid][request_cia] == true || RequestData[playerid][request_army] == true)
	    	{
	    		if(RequestData[playerid][request_cop] == true)
	    		{
	    			RequestData[playerid][request_cop] = false;
	    			job = POLICE_JOB;
	    		}
	    		else if(RequestData[playerid][request_cia] == true)
	    		{
	    			RequestData[playerid][request_cia] = false;
	    			job = CIA_JOB;
	    		}
	    		else if(RequestData[playerid][request_army] == true)
	    		{
	    			RequestData[playerid][request_army] = false;
	    			job = ARMY_JOB;
	    		}

	    		SetPlayerJob(playerid, job);
	    		SetPlayerColourEx(playerid, job);
	    		
	    		new string[144], name[24];
	    		GetPlayerName(playerid, name, sizeof(name));
				format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just clocked-on duty.", ReturnPlayerJob(playerid), name, playerid);
				PoliceRadio(ORANGE, string);
	    	}
	    	else if(RequestData[playerid][request_ems] == true || RequestData[playerid][request_fire] == true)
	    	{
	    		if(RequestData[playerid][request_ems] == true)
	    		{
	    			RequestData[playerid][request_ems] = false;
	    			job = EMS_JOB;
	    		}
	    		else if(RequestData[playerid][request_fire] == true)
	    		{
	    			RequestData[playerid][request_fire] = false;
	    			job = FIRE_JOB;
	    		}

	    		SetPlayerJob(playerid, job);
	    		SetPlayerColourEx(playerid, job);

	    		SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully clocked-on duty.");
	    	}
	    	else if(RequestData[playerid][request_miner] == true || RequestData[playerid][request_pilot] == true || RequestData[playerid][request_trucker] == true)
	    	{
	    		if(RequestData[playerid][request_miner] == true)
	    		{
	    			RequestData[playerid][request_miner] = false;
	    			job = MINER_JOB;
	    		}
	    		else if(RequestData[playerid][request_pilot] == true)
	    		{
	    			RequestData[playerid][request_pilot] = false;
	    			job = PILOT_JOB;
	    		}
	    		else if(RequestData[playerid][request_trucker] == true)
	    		{
	    			RequestData[playerid][request_trucker] = false;
	    			job = TRUCKER_JOB;
	    		}

	    		SetPlayerJob(playerid, job);
	    		SetPlayerColourEx(playerid, job);

	    		SendClientMessage(playerid, YELLOW, "NOTICE: You have successfully clocked-on duty.");
	    	}
	    	else if(RequestData[playerid][request_civ] == true)
	    	{
	    		job = GetPlayerJob(playerid);
	    		if(job == POLICE_JOB || job == CIA_JOB || job == ARMY_JOB)
	    		{
	    			new string[144], name[24];
	    			GetPlayerName(playerid, name, sizeof(name));
					format(string, sizeof(string), "RADIO(/r): %s %s (%i) has just clocked-off duty.", ReturnPlayerJob(playerid), name, playerid);
					PoliceRadio(ORANGE, string);
				}
				else if(job == EMS_JOB || job == FIRE_JOB || job == MINER_JOB || job == PILOT_JOB || job == TRUCKER_JOB)
				{
					if(job == FIRE_JOB)
					{
						RemovePlayerWeapon(playerid, 42);
					}
	    			SendClientMessage(playerid, ORANGE, "NOTICE: You have successfully clocked-off duty.");
	    		}

	    		RequestData[playerid][request_civ] = false;

	    		SetPlayerJob(playerid, CIVILIAN_JOB);
	    		SetPlayerColourEx(playerid, CIVILIAN_JOB);
	    	}

		 	SetPlayerSkin(playerid, SkinData[playerid][i]);

	        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
	        DestroySkinMenu(playerid);
	        CancelSelectTextDraw(playerid);
        	SetPVarInt(playerid, "skin_active", 0);
        	return TogglePlayerHUDTextdraws(playerid, true);
		}
		i++;
	}
	return 0;
}
