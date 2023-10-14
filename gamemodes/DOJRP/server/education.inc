#include <YSI_Coding\y_hooks>

enum uni_data
{
	ls_uni_ent,
	sf_uni_ent,
	lv_uni_ent,
	uni_exit,
	uni_desk,
	uni_pickup
};
new UniversityData[uni_data];

stock ShowUniDialog(playerid)
{
	if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
	{
		return ShowPlayerDialog(playerid, UNIVERSITY_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University", "{FFFFFF}Degrees\nLicenses", "Select", "Cancel");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
	{
		return ShowPlayerDialog(playerid, UNIVERSITY_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University", "{FFFFFF}Degrees\nLicenses", "Select", "Cancel");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
	{
		return ShowPlayerDialog(playerid, UNIVERSITY_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University", "{FFFFFF}Degrees\nLicenses", "Select", "Cancel");
	}
	return 1;
}

stock ShowLicencesDialog(playerid)
{
	new string[300], gun[32], car[32], truck[32], motorcycle[32], boat[32], pilot[32];

	if(LicenceData[playerid][licence_gun] == 1) { format(gun, sizeof(gun), "{808080}Gun License"); }
	else { format(gun, sizeof(gun), "{FFFFFF}Gun License"); }

	if(LicenceData[playerid][licence_car] == 1) { format(car, sizeof(car), "{808080}Car License"); }
	else { format(car, sizeof(car), "{FFFFFF}Car License"); }

	if(LicenceData[playerid][licence_truck] == 1) { format(truck, sizeof(truck), "{808080}Truck License"); }
	else { format(truck, sizeof(truck), "{FFFFFF}Truck License"); }

	if(LicenceData[playerid][licence_motorcycle] == 1) { format(motorcycle, sizeof(motorcycle), "{808080}Motorcycle License"); }
	else { format(motorcycle, sizeof(motorcycle), "{FFFFFF}Motorcycle License"); }

	if(LicenceData[playerid][licence_boat] == 1) { format(boat, sizeof(boat), "{808080}Boat License"); }
	else { format(boat, sizeof(boat), "{FFFFFF}Boat License"); }

	if(LicenceData[playerid][licence_pilot] == 1) { format(pilot, sizeof(pilot), "{808080}Pilot License"); }
	else { format(pilot, sizeof(pilot), "{FFFFFF}Pilot License"); }

	if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s", gun, car, truck, motorcycle, boat, pilot);
		return ShowPlayerDialog(playerid, LICENCES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Licenses", string, "Details", "Back");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s", gun, car, truck, motorcycle, boat, pilot);
		return ShowPlayerDialog(playerid, LICENCES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Licenses", string, "Details", "Back");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s", gun, car, truck, motorcycle, boat, pilot);
		return ShowPlayerDialog(playerid, LICENCES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Licenses", string, "Details", "Back");
	}
	return 1;
}

stock ShowDegreesDialog(playerid)
{
	new string[400], enforcement[32], intelligence[32], defense[32], medical[32], rescue[32], mining[32], mechanical[32];

	if(DegreeData[playerid][degree_enforcement] == 1) { format(enforcement, sizeof(enforcement), "{808080}Enforcement Degree"); }
	else { format(enforcement, sizeof(enforcement), "{FFFFFF}Enforcement Degree"); }

	if(DegreeData[playerid][degree_intelligence] == 1) { format(intelligence, sizeof(intelligence), "{808080}Intelligence Degree"); }
	else { format(intelligence, sizeof(intelligence), "{FFFFFF}Intelligence Degree"); }

	if(DegreeData[playerid][degree_defense] == 1) { format(defense, sizeof(defense), "{808080}Defense Degree"); }
	else { format(defense, sizeof(defense), "{FFFFFF}Defense Degree"); }

	if(DegreeData[playerid][degree_medical] == 1) { format(medical, sizeof(medical), "{808080}Medical Degree"); }
	else { format(medical, sizeof(medical), "{FFFFFF}Medical Degree"); }

	if(DegreeData[playerid][degree_rescue] == 1) { format(rescue, sizeof(rescue), "{808080}Rescue Degree"); }
	else { format(rescue, sizeof(rescue), "{FFFFFF}Rescue Degree"); }

	if(DegreeData[playerid][degree_mining] == 1) { format(mining, sizeof(mining), "{808080}Mining Degree"); }
	else { format(mining, sizeof(mining), "{FFFFFF}Mining Degree"); }

	if(DegreeData[playerid][degree_mechanical] == 1) { format(mechanical, sizeof(mechanical), "{808080}Mechanical Degree"); }
	else { format(mechanical, sizeof(mechanical), "{FFFFFF}Mechanical Degree"); }

	if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s\n%s", enforcement, intelligence, defense, medical, rescue, mining, mechanical);
		return ShowPlayerDialog(playerid, DEGREES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Degrees", string, "Details", "Back");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s\n%s", enforcement, intelligence, defense, medical, rescue, mining, mechanical);
		return ShowPlayerDialog(playerid, DEGREES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Degrees", string, "Details", "Back");
	}
	else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
	{
		format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s\n%s", enforcement, intelligence, defense, medical, rescue, mining, mechanical);
		return ShowPlayerDialog(playerid, DEGREES_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Degrees", string, "Details", "Back");
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(1467.3356, -1009.9203, 26.8438, 36, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS University
	CreateDynamicMapIcon(-1492.1315, 920.0974, 7.1875, 36, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF University
	CreateDynamicMapIcon(2375.6160, 2306.3022, 8.1406, 36, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV University

	UniversityData[uni_pickup] = CreateDynamicPickup(1239, 1, -2033.4341, -117.4742, 1035.1719, -1, -1, -1, 50.0, -1, 0);//University Desk

	UniversityData[ls_uni_ent] = CreateDynamicCP(1467.3356, -1009.9203, 26.8438, 1.0, -1, -1, -1, 5.0, -1, 0);//LS University Entrance
	UniversityData[sf_uni_ent] = CreateDynamicCP(-1492.1315, 920.0974, 7.1875, 1.0, -1, -1, -1, 5.0, -1, 0);//SF University Entrance
	UniversityData[lv_uni_ent] = CreateDynamicCP(2375.6160, 2306.3022, 8.1406, 1.0, -1, -1, -1, 5.0, -1, 0);//LV University Entrance
	UniversityData[uni_exit] = CreateDynamicCP(-2026.9147, -103.6017, 1035.1836, 1.0, -1, -1, -1, 5.0, -1, 0);//University Exit
	UniversityData[uni_desk] = CreateDynamicCP(-2033.4341, -117.4742, 1035.1719, 1.0, -1, -1, -1, 5.0, -1, 0);//University Desk
	return 1;
}

hook OnPlayerConnect(playerid)
{
    if(!IsPlayerNPC(playerid))
    {
		DegreeData[playerid][degree_enforcement] = 0;
		DegreeData[playerid][degree_intelligence] = 0;
		DegreeData[playerid][degree_defense] = 0;
		DegreeData[playerid][degree_medical] = 0;
		DegreeData[playerid][degree_rescue] = 0;
		DegreeData[playerid][degree_mechanical] = 0;
		DegreeData[playerid][degree_mining] = 0;

		LicenceData[playerid][licence_gun] = 0;
		LicenceData[playerid][licence_car] = 0;
		LicenceData[playerid][licence_truck] = 0;
		LicenceData[playerid][licence_motorcycle] = 0;
		LicenceData[playerid][licence_boat] = 0;
		LicenceData[playerid][licence_pilot] = 0;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case UNIVERSITY_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Degrees
					{
						return ShowDegreesDialog(playerid);
					}
					case 1://Licenses
					{
						return ShowLicencesDialog(playerid);
					}
				}
			}
			return 1;
		}
		case DEGREES_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Enforcement Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, ENFORCEMENT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Enforcement Degree", "{FFFFFF}Course: Law Enforcement\nEmployment: Police Officer\nFee: FREE", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, ENFORCEMENT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Enforcement Degree", "{FFFFFF}Course: Law Enforcement\nEmployment: Police Officer\nFee: FREE", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, ENFORCEMENT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Enforcement Degree", "{FFFFFF}Course: Law Enforcement\nEmployment: Police Officer\nFee: FREE", "Apply", "Back");
						}
					}
					case 1://Intelligence Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, INTELLIGENCE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Intelligence Degree", "{FFFFFF}Course: Central Intelligence\nEmployment: CIA Agent\nFee: $100K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, INTELLIGENCE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Intelligence Degree", "{FFFFFF}Course: Central Intelligence\nEmployment: CIA Agent\nFee: $100K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, INTELLIGENCE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Intelligence Degree", "{FFFFFF}Course: Central Intelligence\nEmployment: CIA Agent\nFee: $100K", "Apply", "Back");
						}
					}
					case 2://Defense Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, DEFENSE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Santos University > Defense Degree", "{FFFFFF}Course: Homeland Security\nEmployment: Soldier\nFee: $250K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, DEFENSE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Defense Degree", "{FFFFFF}Course: Homeland Security\nEmployment: Soldier\nFee: $250K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, DEFENSE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Defense Degree", "{FFFFFF}Course: Homeland Security\nEmployment: Soldier\nFee: $250K", "Apply", "Back");
						}
					}
					case 3://Medical Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, MEDICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Medical Degree", "{FFFFFF}Course: Medicine\nEmployment: Paramedic\nFee: $50K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, MEDICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Medical Degree", "{FFFFFF}Course: Medicine\nEmployment: Paramedic\nFee: $50K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, MEDICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Medical Degree", "{FFFFFF}Course: Medicine\nEmployment: Paramedic\nFee: $50K", "Apply", "Back");
						}
					}
					case 4://Rescue Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, RESCUE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Rescue Degree", "{FFFFFF}Course: Fire & Rescue\nEmployment: Firefighter\nFee: $50K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, RESCUE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Rescue Degree", "{FFFFFF}Course: Fire & Rescue\nEmployment: Firefighter\nFee: $50K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, RESCUE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Rescue Degree", "{FFFFFF}Course: Fire & Rescue\nEmployment: Firefighter\nFee: $50K", "Apply", "Back");
						}
					}
					case 5://Mining Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, MINING_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Mining Degree", "{FFFFFF}Course: Earth Minerals\nEmployment: Miner\nFee: FREE", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, MINING_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Mining Degree", "{FFFFFF}Course: Earth Minerals\nEmployment: Miner\nFee: FREE", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, MINING_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Mining Degree", "{FFFFFF}Course: Earth Minerals\nEmployment: Miner\nFee: FREE", "Apply", "Back");
						}
					}
					case 6://Mechanical Degree
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, MECHANICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Mechanical Degree", "{FFFFFF}Course: Mechanical Engineering\nSkill: Repair Vehicles\nFee: $25K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, MECHANICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Mechanical Degree", "{FFFFFF}Course: Mechanical Engineering\nSkill: Repair Vehicles\nFee: $25K", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, MECHANICAL_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Mechanical Degree", "{FFFFFF}Course: Mechanical Engineering\nSkill: Repair Vehicles\nFee: $25K", "Apply", "Back");
						}
					}
				}
				return 1;
			}
			else
			{
				ShowUniDialog(playerid);
			}
			return 1;
		}
		case LICENCES_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Gun License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, GUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Gun License", "{FFFFFF}Course: Weapon Handling\nEmployment: N/A\nFee: $250", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, GUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Gun License", "{FFFFFF}Course: Weapon Handling\nEmployment: N/A\nFee: $250", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, GUN_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Gun License", "{FFFFFF}Course: Weapon Handling\nEmployment: N/A\nFee: $250", "Apply", "Back");
						}
					}
					case 1://Car License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, CAR_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Car License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $500", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, CAR_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Car License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $500", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, CAR_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Car License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $500", "Apply", "Back");
						}
					}
					case 2://Truck License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, TRUCK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Truck License", "{FFFFFF}Course: Heavy Vehicles\nEmployment: Truck Driver\nFee: $1500", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, TRUCK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Truck License", "{FFFFFF}Course: Heavy Vehicles\nEmployment: Truck Driver\nFee: $1500", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, TRUCK_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Truck License", "{FFFFFF}Course: Heavy Vehicles\nEmployment: Truck Driver\nFee: $1500", "Apply", "Back");
						}
					}
					case 3://Motorcycle License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, MOTORCYCLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Motorcyle License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, MOTORCYCLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Motorcyle License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, MOTORCYCLE_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Motorcyle License", "{FFFFFF}Course: Road Safety\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
					}
					case 4://Boat License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, BOAT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Boat License", "{FFFFFF}Course: Maritime Law\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, BOAT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Boat License", "{FFFFFF}Course: Maritime Law\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, BOAT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Boat License", "{FFFFFF}Course: Maritime Law\nEmployment: N/A\nFee: $300", "Apply", "Back");
						}
					}
					case 5://Pilot License
					{
						if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 4)
						{
							return ShowPlayerDialog(playerid, PILOT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Los Santos University > Pilot License", "{FFFFFF}Course: Flight School\nEmployment: Pilot\nFee: $5000", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 5)
						{
							return ShowPlayerDialog(playerid, PILOT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}San Fierro University > Pilot License", "{FFFFFF}Course: Flight School\nEmployment: Pilot\nFee: $5000", "Apply", "Back");
						}
						else if(GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == 6)
						{
							return ShowPlayerDialog(playerid, PILOT_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Las Venturas University > Pilot License", "{FFFFFF}Course: Flight School\nEmployment: Pilot\nFee: $5000", "Apply", "Back");
						}
					}
				}
				return 1;
			}
			else
			{
				ShowUniDialog(playerid);
			}
			return 1;
		}
		case PILOT_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_pilot] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Pilot License.");
				if(GetPlayerMoneyEx(playerid) < 5000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -5000);

				LicenceData[playerid][licence_pilot] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_PILOT);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Pilot License and can pilot aircraft.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case BOAT_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_boat] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Boat License.");
				if(GetPlayerMoneyEx(playerid) < 300) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -300);

				LicenceData[playerid][licence_boat] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_BOAT);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Boat License and can pilot boats.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case MOTORCYCLE_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_motorcycle] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Motorcycle License.");
				if(GetPlayerMoneyEx(playerid) < 300) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -300);

				LicenceData[playerid][licence_motorcycle] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_MOTORCYCLE);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Motorcycle License and can ride motorcycles.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case TRUCK_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_truck] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Truck License.");
				if(GetPlayerMoneyEx(playerid) < 1500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -1500);

				LicenceData[playerid][licence_truck] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_TRUCK);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Truck License and can drive trucks.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case CAR_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_car] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Car License.");
				if(GetPlayerMoneyEx(playerid) < 500) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -500);

				LicenceData[playerid][licence_car] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_CAR);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Car License and can drive cars.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case GUN_DIALOG:
		{
			if(response)
			{
				if(LicenceData[playerid][licence_gun] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Gun License.");
				if(GetPlayerMoneyEx(playerid) < 250) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this license.");

				GivePlayerMoney(playerid, -250);

				LicenceData[playerid][licence_gun] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveLicenceData(playerid, LICENCE_GUN);

				ShowLicencesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You now own a Gun License and can buy weapons.");
			}
			else
			{
				ShowLicencesDialog(playerid);
			}
			return 1;
		}
		case MECHANICAL_DIALOG:
		{
			if(response)
			{
				if(DegreeData[playerid][degree_mechanical] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Mechanical Degree.");
				if(GetPlayerMoneyEx(playerid) < 25000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this degree.");

				GivePlayerMoney(playerid, -25000);

				DegreeData[playerid][degree_mechanical] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_MECHANICAL);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Mechanical Degree, you are now a qualified mechanic.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case MINING_DIALOG:
		{
			if(response)
			{
				if(DegreeData[playerid][degree_mining] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Mining Degree.");

				DegreeData[playerid][degree_mining] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_MINING);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Mining Degree, you are now a qualified miner.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case RESCUE_DIALOG:
		{
			if(response)
			{
				if(DegreeData[playerid][degree_rescue] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Rescue Degree.");
				if(GetPlayerMoneyEx(playerid) < 50000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this degree.");

				GivePlayerMoney(playerid, -50000);

				DegreeData[playerid][degree_rescue] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_RESCUE);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Rescue Degree, you are now a qualified firefighter.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case MEDICAL_DIALOG:
		{
			if(response)
			{
				if(DegreeData[playerid][degree_medical] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Medical Degree.");
				if(GetPlayerMoneyEx(playerid) < 50000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this degree.");

				GivePlayerMoney(playerid, -50000);

				DegreeData[playerid][degree_medical] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_MEDICAL);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Medical Degree, you are now a qualified paramedic.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case DEFENSE_DIALOG:
		{
			if(response)
			{
				if(GetPlayerScore(playerid) < MIN_ARMY_SCORE)
				{
					new string[128];
					format(string, sizeof(string), "ERROR: You need at least %i score to purchase a Defense Degree.", MIN_ARMY_SCORE);
					return SendClientMessage(playerid, RED, string);
				}

				if(DegreeData[playerid][degree_defense] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have a Defense Degree.");
				if(GetPlayerMoneyEx(playerid) < 250000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this degree.");

				GivePlayerMoney(playerid, -250000);

				DegreeData[playerid][degree_defense] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_DEFENSE);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Defense Degree, you are now a qualified soldier.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case INTELLIGENCE_DIALOG:
		{
			if(response)
			{
				if(GetPlayerScore(playerid) < MIN_CIA_SCORE)
				{
					new string[128];
					format(string, sizeof(string), "ERROR: You need at least %i score to purchase an Intelligence Degree.", MIN_CIA_SCORE);
					return SendClientMessage(playerid, RED, string);
				}

				if(DegreeData[playerid][degree_intelligence] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have an Intelligence Degree.");
				if(GetPlayerMoneyEx(playerid) < 100000) return SendClientMessage(playerid, RED, "ERROR: You don't have enough money to purchase this degree.");

				GivePlayerMoney(playerid, -100000);

				DegreeData[playerid][degree_intelligence] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_INTELLIGENCE);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Intelligence Degree, you are now a qualified CIA agent.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
		case ENFORCEMENT_DIALOG:
		{
			if(response)
			{
				if(DegreeData[playerid][degree_enforcement] == 1) return SendClientMessage(playerid, RED, "ERROR: You already have an Enforcement Degree.");

				DegreeData[playerid][degree_enforcement] = 1;

				ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 0, 0, 0, 0, 0);

				SaveDegreeData(playerid, DEGREE_ENFORCEMENT);

				ShowDegreesDialog(playerid);

				return SendClientMessage(playerid, YELLOW, "NOTICE: You passed your Enforcement Degree, you are now a qualified police officer.");
			}
			else
			{
				ShowDegreesDialog(playerid);
			}
			return 1;
		}
	}
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == UniversityData[uni_desk])
	{
		return 1;
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == UniversityData[ls_uni_ent])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 4);
			SetPlayerPos(playerid, -2026.9281, -104.8615, 1035.1719);
			SetPlayerFacingAngle(playerid, 180.2720);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == UniversityData[sf_uni_ent])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 5);
			SetPlayerPos(playerid, -2026.9281, -104.8615, 1035.1719);
			SetPlayerFacingAngle(playerid, 180.2720);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == UniversityData[lv_uni_ent])
		{
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, 6);
			SetPlayerPos(playerid, -2026.9281, -104.8615, 1035.1719);
			SetPlayerFacingAngle(playerid, 180.2720);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == UniversityData[uni_exit])
		{
			if(GetPlayerVirtualWorld(playerid) == 4)//LS University
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 1467.2743, -1011.5594, 26.8438);
				SetPlayerFacingAngle(playerid, 179.5822);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 5)//SF University
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, -1493.7815, 920.1070, 7.1875);
				SetPlayerFacingAngle(playerid, 90.0846);
				return SetCameraBehindPlayer(playerid);
			}
			else if(GetPlayerVirtualWorld(playerid) == 6)//LV University
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, 2375.5913, 2308.0605, 8.1406);
				SetPlayerFacingAngle(playerid, 359.8412);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
		else if(checkpointid == UniversityData[uni_desk])
		{
			return ShowUniDialog(playerid);
		}
	}
	return 1;
}
