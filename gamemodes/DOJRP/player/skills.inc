#include <YSI_Coding\y_hooks>

enum degree_data
{
	//Jobs
	degree_enforcement,
	degree_intelligence,
	degree_defense,
	degree_medical,
	degree_rescue,
	degree_mining,

	//Skills
	degree_mechanical
};
new DegreeData[MAX_PLAYERS][degree_data];

enum licence_data
{
	licence_gun,
	licence_car,
	licence_truck,
	licence_motorcycle,
	licence_boat,
	licence_pilot
};
new LicenceData[MAX_PLAYERS][licence_data];

stock GetPlayerLicence(playerid, licence)
{
	if(licence == LICENCE_GUN) return LicenceData[playerid][licence_gun];
	else if(licence == LICENCE_CAR) return LicenceData[playerid][licence_car];
	else if(licence == LICENCE_TRUCK) return LicenceData[playerid][licence_truck];
	else if(licence == LICENCE_MOTORCYCLE) return LicenceData[playerid][licence_motorcycle];
	else if(licence == LICENCE_BOAT) return LicenceData[playerid][licence_boat];
	else if(licence == LICENCE_PILOT) return LicenceData[playerid][licence_pilot];
	return 1;
}

stock SetPlayerLicence(playerid, licence, status)
{
	if(licence == LICENCE_GUN) return LicenceData[playerid][licence_gun] = status;
	else if(licence == LICENCE_CAR) return LicenceData[playerid][licence_car] = status;
	else if(licence == LICENCE_TRUCK) return LicenceData[playerid][licence_truck] = status;
	else if(licence == LICENCE_MOTORCYCLE) return LicenceData[playerid][licence_motorcycle] = status;
	else if(licence == LICENCE_BOAT) return LicenceData[playerid][licence_boat] = status;
	else if(licence == LICENCE_PILOT) return LicenceData[playerid][licence_pilot] = status;
	return 1;
}

stock GetPlayerDegree(playerid, degree)
{
	if(degree == DEGREE_ENFORCEMENT) return DegreeData[playerid][degree_enforcement];
	else if(degree == DEGREE_INTELLIGENCE) return DegreeData[playerid][degree_intelligence];
	else if(degree == DEGREE_DEFENSE) return DegreeData[playerid][degree_defense];
	else if(degree == DEGREE_MEDICAL) return DegreeData[playerid][degree_medical];
	else if(degree == DEGREE_RESCUE) return DegreeData[playerid][degree_rescue];
	else if(degree == DEGREE_MINING) return DegreeData[playerid][degree_mining];
	else if(degree == DEGREE_MECHANICAL) return DegreeData[playerid][degree_mechanical];
	return 1;
}

stock SetPlayerDegree(playerid, degree, status)
{
	if(degree == DEGREE_ENFORCEMENT) return DegreeData[playerid][degree_enforcement] = status;
	else if(degree == DEGREE_INTELLIGENCE) return DegreeData[playerid][degree_intelligence] = status;
	else if(degree == DEGREE_DEFENSE) return DegreeData[playerid][degree_defense] = status;
	else if(degree == DEGREE_MEDICAL) return DegreeData[playerid][degree_medical] = status;
	else if(degree == DEGREE_RESCUE) return DegreeData[playerid][degree_rescue] = status;
	else if(degree == DEGREE_MINING) return DegreeData[playerid][degree_mining] = status;
	else if(degree == DEGREE_MECHANICAL) return DegreeData[playerid][degree_mechanical] = status;
	return 1;
}

stock SaveLicenceData(playerid, licence)
{
	new query[300], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `LICENCES` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		if(licence == LICENCE_GUN)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `GUN` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_gun], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(licence == LICENCE_CAR)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `CAR` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_car], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(licence == LICENCE_TRUCK)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `TRUCK` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_truck], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(licence == LICENCE_MOTORCYCLE)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `MOTORCYCLE` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_motorcycle], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(licence == LICENCE_BOAT)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `BOAT` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_boat], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(licence == LICENCE_PILOT)
		{
			format(query, sizeof(query), "UPDATE `LICENCES` SET `PILOT` = '%i' WHERE `CHARACTER_ID` = '%i'", LicenceData[playerid][licence_pilot], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `LICENCES` (`CHARACTER_ID`, `GUN`, `CAR`, `TRUCK`, `MOTORCYCLE`, `BOAT`, `PILOT`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		id, LicenceData[playerid][licence_gun], LicenceData[playerid][licence_car], LicenceData[playerid][licence_truck], LicenceData[playerid][licence_motorcycle], LicenceData[playerid][licence_boat], LicenceData[playerid][licence_pilot]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	return 1;
}

stock LoadLicenceData(playerid)
{
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `LICENCES` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		LicenceData[playerid][licence_gun] = db_get_field_assoc_int(database_result, "GUN");
		LicenceData[playerid][licence_car] = db_get_field_assoc_int(database_result, "CAR");
		LicenceData[playerid][licence_truck] = db_get_field_assoc_int(database_result, "TRUCK");
		LicenceData[playerid][licence_motorcycle] = db_get_field_assoc_int(database_result, "MOTORCYCLE");
		LicenceData[playerid][licence_boat] = db_get_field_assoc_int(database_result, "BOAT");
		LicenceData[playerid][licence_pilot] = db_get_field_assoc_int(database_result, "PILOT");
	}
	db_free_result@(database_result);
	return 1;
}

stock SaveDegreeData(playerid, degree)
{
	new query[300], id = GetPlayerCharacterID(playerid);
	format(query, sizeof(query), "SELECT `CHARACTER_ID` FROM `DEGREES` WHERE `CHARACTER_ID` = '%i'", id);
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		db_free_result@(database_result);

		if(degree == DEGREE_ENFORCEMENT)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `ENFORCE` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_enforcement], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_INTELLIGENCE)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `INTEL` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_intelligence], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_DEFENSE)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `DEFENSE` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_defense], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_MEDICAL)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `MEDICAL` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_medical], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_RESCUE)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `RESCUE` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_rescue], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_MECHANICAL)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `MECHANIC` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_mechanical], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
		else if(degree == DEGREE_MINING)
		{
			format(query, sizeof(query), "UPDATE `DEGREES` SET `MINING` = '%i' WHERE `CHARACTER_ID` = '%i'", DegreeData[playerid][degree_mining], id);
			database_result = db_query@(server_database, query);
			db_free_result@(database_result);
		}
	}
	else
	{
		db_free_result@(database_result);

		format(query, sizeof(query), "INSERT INTO `DEGREES` (`CHARACTER_ID`, `ENFORCE`, `INTEL`, `DEFENSE`, `MEDICAL`, `RESCUE`, `MINING`, `MECHANIC`) VALUES ('%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')", 
		id, DegreeData[playerid][degree_enforcement], DegreeData[playerid][degree_intelligence], DegreeData[playerid][degree_defense], DegreeData[playerid][degree_medical], DegreeData[playerid][degree_rescue], DegreeData[playerid][degree_mining], DegreeData[playerid][degree_mechanical]);
		database_result = db_query@(server_database, query);
		db_free_result@(database_result);
	}
	return 1;
}

stock LoadDegreeData(playerid)
{
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `DEGREES` WHERE `CHARACTER_ID` = '%i'", GetPlayerCharacterID(playerid));
	database_result = db_query@(server_database, query);
	if(db_num_rows(database_result))
	{
		DegreeData[playerid][degree_enforcement] = db_get_field_assoc_int(database_result, "ENFORCE");
		DegreeData[playerid][degree_intelligence] = db_get_field_assoc_int(database_result, "INTEL");
		DegreeData[playerid][degree_defense] = db_get_field_assoc_int(database_result, "DEFENSE");
		DegreeData[playerid][degree_medical] = db_get_field_assoc_int(database_result, "MEDICAL");
		DegreeData[playerid][degree_rescue] = db_get_field_assoc_int(database_result, "RESCUE");
		DegreeData[playerid][degree_mining] = db_get_field_assoc_int(database_result, "MINING");
		DegreeData[playerid][degree_mechanical] = db_get_field_assoc_int(database_result, "MECHANIC");
	}
	db_free_result@(database_result);
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
		DegreeData[playerid][degree_mining] = 0;
		DegreeData[playerid][degree_mechanical] = 0;

		LicenceData[playerid][licence_gun] = 0;
		LicenceData[playerid][licence_car] = 0;
		LicenceData[playerid][licence_truck] = 0;
		LicenceData[playerid][licence_motorcycle] = 0;
		LicenceData[playerid][licence_boat] = 0;
		LicenceData[playerid][licence_pilot] = 0;
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(IsVehicleBoat(vehicleid) && LicenceData[playerid][licence_boat] == 0)
		{
		    RemovePlayerFromVehicle(playerid);
			return SendClientMessage(playerid, RED, "ERROR: You need to have a Boat License to be able to pilot boats.");
		}
		else if(IsVehicleAircraft(vehicleid) && LicenceData[playerid][licence_pilot] == 0)
		{
		    RemovePlayerFromVehicle(playerid);
			return SendClientMessage(playerid, RED, "ERROR: You need to have a Pilot License to be able to pilot aircraft.");
		}
		else if(IsVehicleMotorcycle(vehicleid) && LicenceData[playerid][licence_motorcycle] == 0)
		{
		    RemovePlayerFromVehicle(playerid);
			return SendClientMessage(playerid, RED, "ERROR: You need to have a Motorcycle License to be able to ride motorcycles.");
		}
		else if(IsVehicleTruck(vehicleid) && LicenceData[playerid][licence_truck] == 0)
		{
		    RemovePlayerFromVehicle(playerid);
			return SendClientMessage(playerid, RED, "ERROR: You need to have a Truck License to be able to drive trucks.");
		}
		else
		{
			switch(GetVehicleModel(vehicleid))
			{
				case 432, 457, 485, 530, 531, 571, 572, 574, 583:
				{
					//Bypass Non-Car Vehicles
				}
				default:
				{
					if(!IsVehicleBicycle(vehicleid) && !IsVehicleBoat(vehicleid) && !IsVehicleAircraft(vehicleid) && !IsVehicleMotorcycle(vehicleid) && !IsVehicleTruck(vehicleid))
					{
						if(LicenceData[playerid][licence_car] == 0)
						{
		    				RemovePlayerFromVehicle(playerid);
							return SendClientMessage(playerid, RED, "ERROR: You need to have a Car License to be able to drive cars.");
						}
					}
				}
			}
		}
	}
	return 1;
}
