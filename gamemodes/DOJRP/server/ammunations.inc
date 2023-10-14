#include <YSI_Coding\y_hooks>

enum ammu_data
{
	lscity_ammu_ent_cp,
	lscountry_ammu_ent_cp,

	sfcity_ammu_ent_cp,
	sfcountry_ammu_ent_cp,

	lvcity_ammu_ent_cp,
	lvcountry_ammu_ent_cp,

	ammu_exit_cp,
	ammu_counter_cp
};
new AmmuData[ammu_data];

stock ShowAmmuDialog(playerid)
{
	return ShowPlayerDialog(playerid, AMMU_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation", "{FFFFFF}Melee Weapons\nHandgun Weapons\nShotgun Weapons\nSMG Weapons\nAssault Weapons\nRifle Weapons\nThrowables\nConsumables", "Select", "Cancel");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1368.9268, -1279.7855, 13.5469, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Ammunation (City)
	CreateDynamicMapIcon(243.2949, -178.3407, 1.5822, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Ammunation (Country)

	CreateDynamicMapIcon(-2625.8699, 208.2350, 4.8125, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Ammunation (City)
	CreateDynamicMapIcon(-2093.6553, -2464.9480, 30.6250, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Ammunation (Country)

	CreateDynamicMapIcon(2159.5452, 943.2220, 10.8203, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Ammunation (City)
	CreateDynamicMapIcon(-316.1617, 829.8609, 14.2422, 6, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Ammunation (Country)

	//LS
	AmmuData[lscity_ammu_ent_cp] = CreateDynamicCP(1368.9268, -1279.7855, 13.5469, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Ammunation (City)
	AmmuData[lscountry_ammu_ent_cp] = CreateDynamicCP(243.2949, -178.3407, 1.5822, 1.0, -1, -1, -1, 5.0, -1, 0);//LS Ammunation (Country)

	//SF
	AmmuData[sfcity_ammu_ent_cp] = CreateDynamicCP(-2625.8699, 208.2350, 4.8125, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Ammunation (City)
	AmmuData[sfcountry_ammu_ent_cp] = CreateDynamicCP(-2093.6553, -2464.9480, 30.6250, 1.0, -1, -1, -1, 5.0, -1, 0);//SF Ammunation (Country)

	//LV
	AmmuData[lvcity_ammu_ent_cp] = CreateDynamicCP(2159.5452, 943.2220, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Ammunation (City)
	AmmuData[lvcountry_ammu_ent_cp] = CreateDynamicCP(-316.1617, 829.8609, 14.2422, 1.0, -1, -1, -1, 5.0, -1, 0);//LV Ammunation (Country)

	AmmuData[ammu_exit_cp] = CreateDynamicCP(285.8032, -86.7382, 1001.5229, 1.0, -1, -1, -1, 5.0, -1, 0);//Ammunation Exit
	AmmuData[ammu_counter_cp] = CreateDynamicCP(291.8280, -83.5458, 1001.5156, 1.0, -1, -1, -1, 5.0, -1, 0);//Ammunation Counter
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case AMMU_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Melee Weapons
					{
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 1://Handgun Weapons
					{
						return ShowPlayerDialog(playerid, HANDGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Handgun Weapons", "{FFFFFF}9mm: $1500\nSilenced 9mm: $2000\nDesert Eagle: $4000\nHandgun Ammo x50: $1000", "Buy", "Back");
					}
					case 2://Shotgun Weapons
					{
						return ShowPlayerDialog(playerid, SHOTGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Shotgun Weapons", "{FFFFFF}Shotgun: $3000\nSawn-off Shotgun: $4000\nCombat Shotgun: $5000\nShotgun Ammo x50: $2000", "Buy", "Back");
					}
					case 3://SMG Weapons
					{
						return ShowPlayerDialog(playerid, SMG_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > SMG Weapons", "{FFFFFF}Uzi: $6000\nTec-9: $7000\nMP5: $8000\nSMG Ammo x100: $2000", "Buy", "Back");
					}
					case 4://Assault Weapons
					{
						return ShowPlayerDialog(playerid, ASSAULT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Assault Weapons", "{FFFFFF}AK-47: $9000\nM4: $10000\nAssault Ammo x100: $3000", "Buy", "Back");
					}
					case 5://Rifle Weapons
					{
						return ShowPlayerDialog(playerid, RIFLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Rifle Weapons", "{FFFFFF}Country Rifle: $11000\nSniper Rifle: $15000\nRifle Ammo x50: $4000", "Buy", "Back");
					}
					case 6://Throwables
					{
						return ShowPlayerDialog(playerid, THROWABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Throwables", "{FFFFFF}Molotov Cocktails x10: $5000\nGrenades x10: $7000\nSatchel Charges x10: $10000", "Buy", "Back");
					}
					case 7://Consumables
					{
						return ShowPlayerDialog(playerid, CONSUMABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Consumables", "{FFFFFF}Body Armour: $500", "Buy", "Back");
					}
				}
			}
			return 1;
		}
		case CONSUMABLES_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Body Armour
					{
						new Float:armour;
						GetPlayerArmour(playerid, armour);
						if(armour >= 100.0) return SendClientMessage(playerid, RED, "ERROR: You already have full body armour.");
						if(GetPlayerMoneyEx(playerid) < 500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -500);
						SetPlayerArmour(playerid, 100.0);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, CONSUMABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Consumables", "{FFFFFF}Body Armour: $500", "Buy", "Back");
					}
				}
			}
			return 1;
		}
		case THROWABLES_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Molotov Cocktails
					{
						if(GetPlayerMoneyEx(playerid) < 5000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -5000);
						GivePlayerWeapon(playerid, 18, 10);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, THROWABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Throwables", "{FFFFFF}Molotov Cocktails x10: $5000\nGrenades x10: $7000\nSatchel Charges x10: $10000", "Buy", "Back");
					}
					case 1://Grenades
					{
						if(GetPlayerMoneyEx(playerid) < 7000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -7000);
						GivePlayerWeapon(playerid, 16, 10);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, THROWABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Throwables", "{FFFFFF}Molotov Cocktails x10: $5000\nGrenades x10: $7000\nSatchel Charges x10: $10000", "Buy", "Back");
					}
					case 2://Satchel Charges
					{
						if(GetPlayerMoneyEx(playerid) < 10000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -10000);
						GivePlayerWeapon(playerid, 39, 10);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, THROWABLES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Throwables", "{FFFFFF}Molotov Cocktails x10: $5000\nGrenades x10: $7000\nSatchel Charges x10: $10000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case RIFLE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Country Rifle
					{
						if(IsHoldingWeapon(playerid, 33)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 11000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -11000);
						GivePlayerWeapon(playerid, 33, 50);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, RIFLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Rifle Weapons", "{FFFFFF}Country Rifle: $11000\nSniper Rifle: $15000\nRifle Ammo x50: $4000", "Buy", "Back");
					}
					case 1://Sniper Rifle
					{
						if(IsHoldingWeapon(playerid, 34)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 15000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -15000);
						GivePlayerWeapon(playerid, 34, 50);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, RIFLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Rifle Weapons", "{FFFFFF}Country Rifle: $11000\nSniper Rifle: $15000\nRifle Ammo x50: $4000", "Buy", "Back");
					}
					case 2://Rifle Ammo
					{
						if(!IsHoldingWeapon(playerid, 33) && !IsHoldingWeapon(playerid, 34)) return SendClientMessage(playerid, RED, "ERROR: You must be holding a long range rifle to buy this ammo.");
						if(GetPlayerMoneyEx(playerid) < 4000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this ammo.");
						GivePlayerMoney(playerid, -4000);
						GivePlayerWeapon(playerid, GetPlayerWeapon(playerid), 50);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, RIFLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Rifle Weapons", "{FFFFFF}Country Rifle: $11000\nSniper Rifle: $15000\nRifle Ammo x50: $4000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case ASSAULT_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://AK-47
					{
						if(IsHoldingWeapon(playerid, 30)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 9000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -9000);
						GivePlayerWeapon(playerid, 30, 100);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, ASSAULT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Assault Weapons", "{FFFFFF}AK-47: $9000\nM4: $10000\nAssault Ammo x100: $3000", "Buy", "Back");
					}
					case 1://M4
					{
						if(IsHoldingWeapon(playerid, 31)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 10000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -10000);
						GivePlayerWeapon(playerid, 31, 100);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, ASSAULT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Assault Weapons", "{FFFFFF}AK-47: $9000\nM4: $10000\nAssault Ammo x100: $3000", "Buy", "Back");
					}
					case 2://Assault Ammo
					{
						if(!IsHoldingWeapon(playerid, 30) && !IsHoldingWeapon(playerid, 31)) return SendClientMessage(playerid, RED, "ERROR: You must be holding an assault rifle to buy this ammo.");
						if(GetPlayerMoneyEx(playerid) < 3000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this ammo.");
						GivePlayerMoney(playerid, -3000);
						GivePlayerWeapon(playerid, GetPlayerWeapon(playerid), 100);
						ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, ASSAULT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Assault Weapons", "{FFFFFF}AK-47: $9000\nM4: $10000\nAssault Ammo x100: $3000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case SMG_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Uzi
					{
						if(IsHoldingWeapon(playerid, 28)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 6000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -6000);
						GivePlayerWeapon(playerid, 28, 100);
						ApplyAnimation(playerid, "UZI", "uzi_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SMG_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > SMG Weapons", "{FFFFFF}Uzi: $6000\nTec-9: $7000\nMP5: $8000\nSMG Ammo x100: $2000", "Buy", "Back");
					}
					case 1://Tec-9
					{
						if(IsHoldingWeapon(playerid, 32)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 7000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -7000);
						GivePlayerWeapon(playerid, 32, 100);
						ApplyAnimation(playerid, "TEC", "tec_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SMG_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > SMG Weapons", "{FFFFFF}Uzi: $6000\nTec-9: $7000\nMP5: $8000\nSMG Ammo x100: $2000", "Buy", "Back");
					}
					case 2://MP5
					{
						if(IsHoldingWeapon(playerid, 29)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 8000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -8000);
						GivePlayerWeapon(playerid, 29, 100);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SMG_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > SMG Weapons", "{FFFFFF}Uzi: $6000\nTec-9: $7000\nMP5: $8000\nSMG Ammo x100: $2000", "Buy", "Back");
					}
					case 3://SMG Ammo
					{
						if(!IsHoldingWeapon(playerid, 28) && !IsHoldingWeapon(playerid, 29) && !IsHoldingWeapon(playerid, 32)) return SendClientMessage(playerid, RED, "ERROR: You must be holding an SMG to buy this ammo.");
						if(GetPlayerMoneyEx(playerid) < 2000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this ammo.");
						GivePlayerMoney(playerid, -2000);
						GivePlayerWeapon(playerid, GetPlayerWeapon(playerid), 100);
						if(GetPlayerWeapon(playerid) == 28)
						{
							ApplyAnimation(playerid, "UZI", "uzi_reload", 4.1, 0, 0, 0, 0, 0);
						}
						else if(GetPlayerWeapon(playerid) == 29)
						{
							ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						}
						else if(GetPlayerWeapon(playerid) == 32)
						{
							ApplyAnimation(playerid, "TEC", "tec_reload", 4.1, 0, 0, 0, 0, 0);
						}
						return ShowPlayerDialog(playerid, SMG_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > SMG Weapons", "{FFFFFF}Uzi: $6000\nTec-9: $7000\nMP5: $8000\nSMG Ammo x100: $2000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case SHOTGUN_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Shotgun
					{
						if(IsHoldingWeapon(playerid, 25)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 3000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -3000);
						GivePlayerWeapon(playerid, 25, 50);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SHOTGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Shotgun Weapons", "{FFFFFF}Shotgun: $3000\nSawn-off Shotgun: $4000\nCombat Shotgun: $5000\nShotgun Ammo x50: $2000", "Buy", "Back");
					}
					case 1://Sawn-off Shotgun
					{
						if(IsHoldingWeapon(playerid, 26)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 4000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -4000);
						GivePlayerWeapon(playerid, 26, 50);
						ApplyAnimation(playerid, "COLT45", "sawnoff_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SHOTGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Shotgun Weapons", "{FFFFFF}Shotgun: $3000\nSawn-off Shotgun: $4000\nCombat Shotgun: $5000\nShotgun Ammo x50: $2000", "Buy", "Back");
					}
					case 2://Combat Shotgun
					{
						if(IsHoldingWeapon(playerid, 27)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 5000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -5000);
						GivePlayerWeapon(playerid, 27, 50);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, SHOTGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Shotgun Weapons", "{FFFFFF}Shotgun: $3000\nSawn-off Shotgun: $4000\nCombat Shotgun: $5000\nShotgun Ammo x50: $2000", "Buy", "Back");
					}
					case 3://Shotgun Ammo
					{
						if(!IsHoldingWeapon(playerid, 25) && !IsHoldingWeapon(playerid, 26) && !IsHoldingWeapon(playerid, 27)) return SendClientMessage(playerid, RED, "ERROR: You must be holding a shotgun to buy this ammo.");
						if(GetPlayerMoneyEx(playerid) < 2000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this ammo.");
						GivePlayerMoney(playerid, -2000);
						GivePlayerWeapon(playerid, GetPlayerWeapon(playerid), 50);
						if(GetPlayerWeapon(playerid) == 25 || GetPlayerWeapon(playerid) == 27)
						{
							ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						}
						else if(GetPlayerWeapon(playerid) == 26)
						{
							ApplyAnimation(playerid, "COLT45", "sawnoff_reload", 4.1, 0, 0, 0, 0, 0);
						}
						return ShowPlayerDialog(playerid, SHOTGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Shotgun Weapons", "{FFFFFF}Shotgun: $3000\nSawn-off Shotgun: $4000\nCombat Shotgun: $5000\nShotgun Ammo x50: $2000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case HANDGUN_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://9mm
					{
						if(IsHoldingWeapon(playerid, 22)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 1500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -1500);
						GivePlayerWeapon(playerid, 22, 50);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, HANDGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Handgun Weapons", "{FFFFFF}9mm: $1500\nSilenced 9mm: $2000\nDesert Eagle: $4000\nHandgun Ammo x50: $1000", "Buy", "Back");
					}
					case 1://Silenced 9mm
					{
						if(IsHoldingWeapon(playerid, 23)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 2000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -2000);
						GivePlayerWeapon(playerid, 23, 50);
						ApplyAnimation(playerid, "SILENCED", "silence_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, HANDGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Handgun Weapons", "{FFFFFF}9mm: $1500\nSilenced 9mm: $2000\nDesert Eagle: $4000\nHandgun Ammo x50: $1000", "Buy", "Back");
					}
					case 2://Desert Eagle
					{
						if(IsHoldingWeapon(playerid, 24)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 4000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -4000);
						GivePlayerWeapon(playerid, 24, 50);
						ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, HANDGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Handgun Weapons", "{FFFFFF}9mm: $1500\nSilenced 9mm: $2000\nDesert Eagle: $4000\nHandgun Ammo x50: $1000", "Buy", "Back");
					}
					case 3://Handgun Ammo
					{
						if(!IsHoldingWeapon(playerid, 22) && !IsHoldingWeapon(playerid, 23) && !IsHoldingWeapon(playerid, 24)) return SendClientMessage(playerid, RED, "ERROR: You must be holding a handgun to buy this ammo.");
						if(GetPlayerMoneyEx(playerid) < 1000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this ammo.");
						GivePlayerMoney(playerid, -1000);
						GivePlayerWeapon(playerid, GetPlayerWeapon(playerid), 50);
						if(GetPlayerWeapon(playerid) == 22 || GetPlayerWeapon(playerid) == 24)
						{
							ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0);
						}
						else if(GetPlayerWeapon(playerid) == 23)
						{
							ApplyAnimation(playerid, "SILENCED", "silence_reload", 4.1, 0, 0, 0, 0, 0);
						}
						return ShowPlayerDialog(playerid, HANDGUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Handgun Weapons", "{FFFFFF}9mm: $1500\nSilenced 9mm: $2000\nDesert Eagle: $4000\nHandgun Ammo x50: $1000", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
		case MELEE_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Golf Club
					{
						if(IsHoldingWeapon(playerid, 2)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 2, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 1://Knife
					{
						if(IsHoldingWeapon(playerid, 4)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 4, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 2://Baseball Bat
					{
						if(IsHoldingWeapon(playerid, 5)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 5, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 3://Shovel
					{
						if(IsHoldingWeapon(playerid, 6)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 6, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 4://Pool Cue
					{
						if(IsHoldingWeapon(playerid, 7)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 7, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
					case 5://Cane
					{
						if(IsHoldingWeapon(playerid, 15)) return SendClientMessage(playerid, RED, "ERROR: You already have this weapon equipped.");
						if(GetPlayerMoneyEx(playerid) < 50) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to buy this weapon.");
						GivePlayerMoney(playerid, -50);
						GivePlayerWeapon(playerid, 15, 1);
						ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);
						return ShowPlayerDialog(playerid, MELEE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Ammunation > Melee Weapons", "{FFFFFF}Golf Club: $50\nKnife: $50\nBaseball Bat: $50\nShovel: $50\nPool Cue: $50\nCane: $50", "Buy", "Back");
					}
				}
			}
			else
			{
				ShowAmmuDialog(playerid);
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == AmmuData[lscity_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[lscountry_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[sfcity_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 3);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[sfcountry_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 4);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[lvcity_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 5);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[lvcountry_ammu_ent_cp])
		{
			SetPlayerVirtualWorld(playerid, 6);
			SetPlayerInterior(playerid, 4);
			SetPlayerPos(playerid, 285.8208, -84.7823, 1001.5156);
			SetPlayerFacingAngle(playerid, 358.9450);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == AmmuData[ammu_exit_cp])
		{
			if(GetPlayerVirtualWorld(playerid) == 1)//LS Ammunation (City)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, 1367.1692, -1279.7738, 13.5469);
				SetPlayerFacingAngle(playerid, 84.6977);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 2)//LS Ammunation (Country)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, 241.4792, -178.3966, 1.5781);
				SetPlayerFacingAngle(playerid, 90.3940);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 3)//SF Ammunation (City)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, -2625.8767, 210.1473, 4.6167);
				SetPlayerFacingAngle(playerid, 0.9526);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 4)//SF Ammunation (Country)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, -2092.7002, -2463.7639, 30.6250);
				SetPlayerFacingAngle(playerid, 321.3220);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 5)//LV Ammunation (City)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, 2157.7952, 943.2104, 10.8203);
				SetPlayerFacingAngle(playerid, 85.9975);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 6)//LV Ammunation (Country)
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, -313.8401, 829.9031, 14.2422);
				SetPlayerFacingAngle(playerid, 273.1204);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == AmmuData[ammu_counter_cp])
		{
			if(GetPlayerLicence(playerid, LICENCE_GUN) == 0) return SendClientMessage(playerid, RED, "ERROR: You need a Gun License to be able to buy weapons.");
			ShowAmmuDialog(playerid);
		}
		return 1;
	}
	return 1;
}
