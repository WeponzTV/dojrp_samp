#include <YSI_Coding\y_hooks>

enum textdraw_data
{
	//Login Screen
    PlayerText:login_screen,

	//Player HUD
    PlayerText:player_name,

    PlayerText:thirst_bg_1,
    PlayerText:thirst_bg_2,
    PlayerText:thirst_bg_3,
    PlayerText:thirst_icon,
    PlayerText:thirst_value,

    PlayerText:hunger_bg_1,
    PlayerText:hunger_bg_2,
    PlayerText:hunger_bg_3,
    PlayerText:hunger_icon,
    PlayerText:hunger_value,

    PlayerText:health_bg_1,
    PlayerText:health_bg_2,
    PlayerText:health_bg_3,
    PlayerText:health_icon,
    PlayerText:health_value,

    //Vehicle HUD
    PlayerText:vehicle_name,

    PlayerText:fuel_bg_1,
    PlayerText:fuel_bg_2,
    PlayerText:fuel_bg_3,
    PlayerText:fuel_icon,
    PlayerText:fuel_value,

    PlayerText:condition_bg_1,
    PlayerText:condition_bg_2,
    PlayerText:condition_bg_3,
    PlayerText:condition_icon,
    PlayerText:condition_value,

    PlayerText:speed_bg_1,
    PlayerText:speed_bg_2,
    PlayerText:speed_bg_3,
    PlayerText:speed_icon,
    PlayerText:speed_value 
};
new TextdrawData[MAX_PLAYERS][textdraw_data];

stock CreateHUDTextdraws(playerid)
{
	TextdrawData[playerid][thirst_bg_1] = CreatePlayerTextDraw(playerid, 550.500000, 424.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][thirst_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][thirst_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][thirst_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][thirst_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][thirst_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][thirst_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][thirst_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][thirst_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][thirst_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][thirst_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][thirst_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][thirst_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][thirst_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][thirst_bg_1], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][thirst_bg_1], 1, 1);

	TextdrawData[playerid][thirst_bg_2] = CreatePlayerTextDraw(playerid, 567.000000, 430.000000, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][thirst_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][thirst_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][thirst_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][thirst_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][thirst_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][thirst_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][thirst_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][thirst_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][thirst_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][thirst_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][thirst_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][thirst_bg_2], 0);

	TextdrawData[playerid][thirst_bg_3] = CreatePlayerTextDraw(playerid, 610.500000, 418.700012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][thirst_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][thirst_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][thirst_bg_3], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][thirst_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][thirst_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][thirst_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][thirst_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][thirst_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][thirst_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][thirst_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][thirst_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][thirst_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][thirst_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][thirst_bg_3], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][thirst_bg_3], 1, 1);

	TextdrawData[playerid][thirst_icon] = CreatePlayerTextDraw(playerid, 568.000000, 432.000000, "HUD:radar_diner");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][thirst_icon], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][thirst_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][thirst_icon], 10.000000, 10.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][thirst_icon], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][thirst_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][thirst_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][thirst_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][thirst_icon], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][thirst_icon], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][thirst_icon], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][thirst_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][thirst_icon], 0);

	TextdrawData[playerid][thirst_value] = CreatePlayerTextDraw(playerid, 625.000000, 431.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][thirst_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][thirst_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][thirst_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][thirst_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][thirst_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][thirst_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][thirst_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][thirst_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][thirst_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][thirst_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][thirst_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][thirst_value], 0);

	TextdrawData[playerid][hunger_bg_1] = CreatePlayerTextDraw(playerid, 550.000000, 401.700012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][hunger_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][hunger_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][hunger_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][hunger_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][hunger_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][hunger_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][hunger_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][hunger_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][hunger_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][hunger_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][hunger_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][hunger_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][hunger_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][hunger_bg_1], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][hunger_bg_1], 1, 1);

	TextdrawData[playerid][hunger_bg_2] = CreatePlayerTextDraw(playerid, 566.500000, 412.700012, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][hunger_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][hunger_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][hunger_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][hunger_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][hunger_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][hunger_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][hunger_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][hunger_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][hunger_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][hunger_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][hunger_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][hunger_bg_2], 0);

	TextdrawData[playerid][hunger_bg_3] = CreatePlayerTextDraw(playerid, 610.500000, 406.899993, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][hunger_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][hunger_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][hunger_bg_3], 35.000000, 51.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][hunger_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][hunger_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][hunger_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][hunger_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][hunger_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][hunger_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][hunger_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][hunger_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][hunger_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][hunger_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][hunger_bg_3], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][hunger_bg_3], 1, 1);

	TextdrawData[playerid][hunger_icon] = CreatePlayerTextDraw(playerid, 568.000000, 415.000000, "HUD:radar_datefood");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][hunger_icon], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][hunger_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][hunger_icon], 10.000000, 10.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][hunger_icon], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][hunger_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][hunger_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][hunger_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][hunger_icon], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][hunger_icon], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][hunger_icon], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][hunger_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][hunger_icon], 0);

	TextdrawData[playerid][hunger_value] = CreatePlayerTextDraw(playerid, 625.000000, 414.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][hunger_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][hunger_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][hunger_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][hunger_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][hunger_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][hunger_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][hunger_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][hunger_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][hunger_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][hunger_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][hunger_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][hunger_value], 0);

	TextdrawData[playerid][health_bg_1] = CreatePlayerTextDraw(playerid, 550.500000, 390.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][health_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][health_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][health_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][health_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][health_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][health_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][health_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][health_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][health_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][health_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][health_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][health_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][health_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][health_bg_1], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][health_bg_1], 1, 1);

	TextdrawData[playerid][health_bg_2] = CreatePlayerTextDraw(playerid, 567.000000, 395.700012, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][health_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][health_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][health_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][health_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][health_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][health_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][health_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][health_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][health_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][health_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][health_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][health_bg_2], 0);

	TextdrawData[playerid][health_bg_3] = CreatePlayerTextDraw(playerid, 610.500000, 384.200012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][health_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][health_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][health_bg_3], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][health_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][health_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][health_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][health_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][health_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][health_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][health_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][health_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][health_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][health_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][health_bg_3], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][health_bg_3], 1, 1);

	TextdrawData[playerid][health_icon] = CreatePlayerTextDraw(playerid, 567.000000, 398.000000, "HUD:radar_girlfriend");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][health_icon], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][health_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][health_icon], 10.000000, 10.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][health_icon], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][health_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][health_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][health_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][health_icon], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][health_icon], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][health_icon], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][health_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][health_icon], 0);

	TextdrawData[playerid][health_value] = CreatePlayerTextDraw(playerid, 625.000000, 397.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][health_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][health_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][health_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][health_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][health_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][health_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][health_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][health_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][health_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][health_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][health_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][health_value], 0);

	TextdrawData[playerid][player_name] = CreatePlayerTextDraw(playerid, 631.000000, 380.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][player_name], 0);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][player_name], 0.266665, 1.349997);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][player_name], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][player_name], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][player_name], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][player_name], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][player_name], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][player_name], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][player_name], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][player_name], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][player_name], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][player_name], 0);

	TextdrawData[playerid][fuel_bg_1] = CreatePlayerTextDraw(playerid, 533.500000, 424.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][fuel_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][fuel_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][fuel_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][fuel_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][fuel_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][fuel_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][fuel_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][fuel_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][fuel_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][fuel_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][fuel_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][fuel_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][fuel_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][fuel_bg_1], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][fuel_bg_1], 1, 1);

	TextdrawData[playerid][fuel_bg_2] = CreatePlayerTextDraw(playerid, 489.399993, 430.000000, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][fuel_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][fuel_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][fuel_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][fuel_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][fuel_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][fuel_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][fuel_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][fuel_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][fuel_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][fuel_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][fuel_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][fuel_bg_2], 0);

	TextdrawData[playerid][fuel_bg_3] = CreatePlayerTextDraw(playerid, 473.000000, 418.700012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][fuel_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][fuel_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][fuel_bg_3], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][fuel_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][fuel_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][fuel_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][fuel_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][fuel_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][fuel_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][fuel_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][fuel_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][fuel_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][fuel_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][fuel_bg_3], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][fuel_bg_3], 1, 1);

	TextdrawData[playerid][fuel_icon] = CreatePlayerTextDraw(playerid, 487.000000, 428.700012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][fuel_icon], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][fuel_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][fuel_icon], 17.000000, 16.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][fuel_icon], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][fuel_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][fuel_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][fuel_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][fuel_icon], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][fuel_icon], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][fuel_icon], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][fuel_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][fuel_icon], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][fuel_icon], 1650);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][fuel_icon], 0.000000, 0.000000, 0.000000, 1.000000);

	TextdrawData[playerid][fuel_value] = CreatePlayerTextDraw(playerid, 547.000000, 431.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][fuel_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][fuel_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][fuel_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][fuel_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][fuel_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][fuel_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][fuel_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][fuel_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][fuel_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][fuel_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][fuel_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][fuel_value], 0);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][fuel_value], 1, 1);

	TextdrawData[playerid][condition_bg_1] = CreatePlayerTextDraw(playerid, 533.000000, 401.200012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][condition_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][condition_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][condition_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][condition_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][condition_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][condition_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][condition_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][condition_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][condition_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][condition_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][condition_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][condition_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][condition_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][condition_bg_1], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][condition_bg_1], 1, 1);

	TextdrawData[playerid][condition_bg_2] = CreatePlayerTextDraw(playerid, 489.299987, 412.700012, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][condition_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][condition_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][condition_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][condition_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][condition_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][condition_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][condition_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][condition_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][condition_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][condition_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][condition_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][condition_bg_2], 0);

	TextdrawData[playerid][condition_bg_3] = CreatePlayerTextDraw(playerid, 473.000000, 406.899993, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][condition_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][condition_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][condition_bg_3], 35.000000, 51.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][condition_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][condition_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][condition_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][condition_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][condition_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][condition_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][condition_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][condition_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][condition_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][condition_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][condition_bg_3], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][condition_bg_3], 1, 1);

	TextdrawData[playerid][condition_icon] = CreatePlayerTextDraw(playerid, 491.000000, 415.000000, "HUD:radar_girlfriend");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][condition_icon], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][condition_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][condition_icon], 10.000000, 10.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][condition_icon], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][condition_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][condition_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][condition_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][condition_icon], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][condition_icon], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][condition_icon], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][condition_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][condition_icon], 0);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][speed_bg_3], 1, 1);

	TextdrawData[playerid][condition_value] = CreatePlayerTextDraw(playerid, 547.000000, 414.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][condition_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][condition_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][condition_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][condition_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][condition_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][condition_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][condition_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][condition_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][condition_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][condition_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][condition_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][condition_value], 0);

	TextdrawData[playerid][speed_bg_1] = CreatePlayerTextDraw(playerid, 533.000000, 390.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][speed_bg_1], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][speed_bg_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][speed_bg_1], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][speed_bg_1], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][speed_bg_1], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][speed_bg_1], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][speed_bg_1], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][speed_bg_1], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][speed_bg_1], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][speed_bg_1], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][speed_bg_1], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][speed_bg_1], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][speed_bg_1], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][speed_bg_1], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][speed_bg_1], 1, 1);

	TextdrawData[playerid][speed_bg_2] = CreatePlayerTextDraw(playerid, 489.299987, 395.700012, "ld_dual:black");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][speed_bg_2], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][speed_bg_2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][speed_bg_2], 60.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][speed_bg_2], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][speed_bg_2], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][speed_bg_2], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][speed_bg_2], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][speed_bg_2], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][speed_bg_2], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][speed_bg_2], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][speed_bg_2], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][speed_bg_2], 0);

	TextdrawData[playerid][speed_bg_3] = CreatePlayerTextDraw(playerid, 472.500000, 384.200012, "Preview_Model");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][speed_bg_3], 5);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][speed_bg_3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][speed_bg_3], 35.000000, 50.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][speed_bg_3], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][speed_bg_3], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][speed_bg_3], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][speed_bg_3], 255);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][speed_bg_3], 0);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][speed_bg_3], 255);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][speed_bg_3], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][speed_bg_3], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][speed_bg_3], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextdrawData[playerid][speed_bg_3], 1614);
	PlayerTextDrawSetPreviewRot(playerid, TextdrawData[playerid][speed_bg_3], 0.000000, 180.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextdrawData[playerid][speed_bg_3], 1, 1);

	TextdrawData[playerid][speed_value] = CreatePlayerTextDraw(playerid, 547.000000, 397.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][speed_value], 2);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][speed_value], 0.170833, 1.200000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][speed_value], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][speed_value], 0);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][speed_value], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][speed_value], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][speed_value], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][speed_value], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][speed_value], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][speed_value], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][speed_value], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][speed_value], 0);

	TextdrawData[playerid][speed_icon] = CreatePlayerTextDraw(playerid, 491.000000, 397.000000, "HUD:radar_impound");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][speed_icon], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][speed_icon], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][speed_icon], 10.000000, 10.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][speed_icon], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][speed_icon], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][speed_icon], 1);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][speed_icon], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][speed_icon], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][speed_icon], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][speed_icon], 1);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][speed_icon], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][speed_icon], 0);

	TextdrawData[playerid][vehicle_name] = CreatePlayerTextDraw(playerid, 548.000000, 380.000000, " ");
	PlayerTextDrawFont(playerid, TextdrawData[playerid][vehicle_name], 0);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][vehicle_name], 0.266665, 1.349997);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][vehicle_name], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][vehicle_name], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][vehicle_name], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][vehicle_name], 3);
	PlayerTextDrawColor(playerid, TextdrawData[playerid][vehicle_name], -1);
	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][vehicle_name], 255);
	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][vehicle_name], 50);
	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][vehicle_name], 0);
	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][vehicle_name], 1);
	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][vehicle_name], 0);
	return 1;
}

stock DestroyHUDTextdraws(playerid)
{
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][thirst_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][thirst_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][thirst_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][thirst_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][hunger_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][hunger_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][hunger_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][hunger_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][health_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][health_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][health_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][health_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][health_value]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][player_name]);

	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][fuel_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][fuel_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][fuel_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][fuel_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][condition_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][condition_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][condition_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][condition_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][speed_bg_1]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][speed_bg_2]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][speed_bg_3]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][speed_value]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][speed_icon]);
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][vehicle_name]);
	return 1;
}

stock CreateLoginTextdraws(playerid)
{
	TextdrawData[playerid][login_screen] = CreatePlayerTextDraw(playerid, 0.000000, -1.000000, "loadsc3:loadsc3");
 	PlayerTextDrawFont(playerid, TextdrawData[playerid][login_screen], 4);
	PlayerTextDrawLetterSize(playerid, TextdrawData[playerid][login_screen], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextdrawData[playerid][login_screen], 643.000000, 450.500000);
	PlayerTextDrawSetOutline(playerid, TextdrawData[playerid][login_screen], 1);
	PlayerTextDrawSetShadow(playerid, TextdrawData[playerid][login_screen], 0);
	PlayerTextDrawAlignment(playerid, TextdrawData[playerid][login_screen], 2);
 	PlayerTextDrawColor(playerid, TextdrawData[playerid][login_screen], -1);
  	PlayerTextDrawBackgroundColor(playerid, TextdrawData[playerid][login_screen], 255);
  	PlayerTextDrawBoxColor(playerid, TextdrawData[playerid][login_screen], 50);
  	PlayerTextDrawUseBox(playerid, TextdrawData[playerid][login_screen], false);
  	PlayerTextDrawSetProportional(playerid, TextdrawData[playerid][login_screen], true);
 	PlayerTextDrawSetSelectable(playerid, TextdrawData[playerid][login_screen], false);
	return 1;
}

stock DestroyLoginTextdraws(playerid)
{
	PlayerTextDrawDestroy(playerid, TextdrawData[playerid][login_screen]);
	return 1;
}

stock TogglePlayerHUDTextdraws(playerid, bool:show)
{
	if(show == true)
	{
		CreateHUDTextdraws(playerid);

		//Name
		PlayerTextDrawShow(playerid, TextdrawData[playerid][player_name]);

		//Thirst
		PlayerTextDrawShow(playerid, TextdrawData[playerid][thirst_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][thirst_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][thirst_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][thirst_icon]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][thirst_value]);

		//Hunger
		PlayerTextDrawShow(playerid, TextdrawData[playerid][hunger_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][hunger_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][hunger_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][hunger_icon]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][hunger_value]);

		//Health
		PlayerTextDrawShow(playerid, TextdrawData[playerid][health_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][health_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][health_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][health_icon]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][health_value]);
	}
	else 
	{
		//Name
		PlayerTextDrawHide(playerid, TextdrawData[playerid][player_name]);

		//Thirst
		PlayerTextDrawHide(playerid, TextdrawData[playerid][thirst_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][thirst_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][thirst_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][thirst_icon]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][thirst_value]);

		//Hunger
		PlayerTextDrawHide(playerid, TextdrawData[playerid][hunger_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][hunger_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][hunger_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][hunger_icon]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][hunger_value]);

		//Health
		PlayerTextDrawHide(playerid, TextdrawData[playerid][health_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][health_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][health_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][health_icon]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][health_value]);

		DestroyHUDTextdraws(playerid);
	}
	return 1;
}

stock ToggleVehicleHUDTextdraws(playerid, bool:show)
{
	if(show == true)
	{
		//Name
		PlayerTextDrawShow(playerid, TextdrawData[playerid][vehicle_name]);

		//Fuel
		PlayerTextDrawShow(playerid, TextdrawData[playerid][fuel_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][fuel_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][fuel_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][fuel_icon]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][fuel_value]);

		//Condition
		PlayerTextDrawShow(playerid, TextdrawData[playerid][condition_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][condition_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][condition_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][condition_icon]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][condition_value]);

		//Speed
		PlayerTextDrawShow(playerid, TextdrawData[playerid][speed_bg_1]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][speed_bg_2]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][speed_bg_3]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][speed_value]);
		PlayerTextDrawShow(playerid, TextdrawData[playerid][speed_icon]);
	}
	else 
	{
		//Name
		PlayerTextDrawHide(playerid, TextdrawData[playerid][vehicle_name]);

		//Fuel
		PlayerTextDrawHide(playerid, TextdrawData[playerid][fuel_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][fuel_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][fuel_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][fuel_icon]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][fuel_value]);

		//Condition
		PlayerTextDrawHide(playerid, TextdrawData[playerid][condition_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][condition_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][condition_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][condition_icon]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][condition_value]);

		//Speed
		PlayerTextDrawHide(playerid, TextdrawData[playerid][speed_bg_1]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][speed_bg_2]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][speed_bg_3]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][speed_value]);
		PlayerTextDrawHide(playerid, TextdrawData[playerid][speed_icon]);
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		CreateHUDTextdraws(playerid);
		CreateLoginTextdraws(playerid);

		PlayerTextDrawShow(playerid, TextdrawData[playerid][login_screen]);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{
		DestroyHUDTextdraws(playerid);
		DestroyLoginTextdraws(playerid);
	}
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
  		TogglePlayerHUDTextdraws(playerid, true);

  		PlayerTextDrawHide(playerid, TextdrawData[playerid][login_screen]);
  	}
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{
		TogglePlayerHUDTextdraws(playerid, false);
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	//Drivers
	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	{
	  	return ToggleVehicleHUDTextdraws(playerid, false);
	}
	else if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	{
	 	ToggleVehicleHUDTextdraws(playerid, true);
	}

	//Passengers
	else if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)
	{
		return ToggleVehicleHUDTextdraws(playerid, false);
	}
	else if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_PASSENGER)
	{
		return ToggleVehicleHUDTextdraws(playerid, true);
	}
    return 1;
}

task OnPlayerLoseStats[45000]()
{
	foreach(new i : Player)
	{
	    if(IsPlayerSpawned(i) && GetPlayerJailTime(i) == 0 && IsPlayerSafe(i) == false && GetDutyStatus(i) == false && GetCameraStatus(i) == false && !IsPlayerInjured(i))
	    {
			//Hunger
			SetPlayerHunger(i, GetPlayerHunger(i) - 1);
			if(GetPlayerHunger(i) > 0)
			{
				if(GetPlayerHunger(i) <= 5)
				{
			  		SendClientMessage(i, ORANGE, "NOTICE: You are about to die of hunger, eat something fast!");
				}
			}
			else
			{
			 	TriggerPlayerDeath(i, INVALID_PLAYER_ID, 255);
			  	SendClientMessage(i, RED, "NOTICE: You have just died of hunger.");
			  	continue;
			}

			//Thirst
			SetPlayerThirst(i, GetPlayerThirst(i) - 1);
			if(GetPlayerThirst(i) > 0)
			{
				if(GetPlayerThirst(i) <= 5)
				{
			  		SendClientMessage(i, ORANGE, "NOTICE: You are about to die of thirst, drink something fast!");
				}
			}
			else
			{
			 	TriggerPlayerDeath(i, INVALID_PLAYER_ID, 255);
			  	SendClientMessage(i, RED, "NOTICE: You have just died of thirst.");
			  	continue;
			}
		}
	}
	return 1;
}

task OnPlayerHUDUpdate[500]()
{
	foreach(new i : Player)
	{
	    if(IsPlayerSpawned(i))
	    {
	    	//Vehicle
	    	if(IsPlayerInAnyVehicle(i))
	    	{
	    		new name[32], vehicleid = GetPlayerVehicleID(i);

	    		//Name
	    		GetVehicleModelName(GetVehicleModel(vehicleid), name, sizeof(name));
	    		PlayerTextDrawSetString(i, TextdrawData[i][vehicle_name], name);

	    		//Speed
	    		new string[64];
	    		#if defined USE_MILES
	    			format(string, sizeof(string), "%i MPH", (GetVehicleSpeed(vehicleid) * 0.62137));
	    		#else
	    			format(string, sizeof(string), "%i KM/H", GetVehicleSpeed(vehicleid));
	    		#endif
	    		PlayerTextDrawSetString(i, TextdrawData[i][speed_value], string);

	    		//Condition
	    		new Float:health;
	    		GetVehicleHealth(vehicleid, health);
	    		format(string, sizeof(string), "%0.0f%", health);
	    		PlayerTextDrawSetString(i, TextdrawData[i][condition_value], string);

	    		//Fuel
	    		format(string, sizeof(string), "%i%", GetVehicleFuel(vehicleid));
	    		PlayerTextDrawSetString(i, TextdrawData[i][fuel_value], string);
	    	}

	    	//Name
	    	new name[24];
	    	GetPlayerName(i, name, sizeof(name));
	    	PlayerTextDrawSetString(i, TextdrawData[i][player_name], name);

	    	//Health
	    	new string[64], Float:health;
	    	GetPlayerHealth(i, health);
	    	format(string, sizeof(string), "%0.0f%", health);
	    	PlayerTextDrawSetString(i, TextdrawData[i][health_value], string);

	    	//Thirst
	    	format(string, sizeof(string), "%i%", GetPlayerThirst(i));
	    	PlayerTextDrawSetString(i, TextdrawData[i][thirst_value], string);

	    	//Hunger
	   		format(string, sizeof(string), "%i%", GetPlayerHunger(i));
	    	PlayerTextDrawSetString(i, TextdrawData[i][hunger_value], string);
	    }
	}
	return 1;
}
