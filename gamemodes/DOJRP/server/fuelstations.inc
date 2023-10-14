#include <YSI_Coding\y_hooks>

new NonNeonVehicles[9] =
{
	424,434,444,461,463,468,471,487,522
};

enum fuel_station_data
{
	fuel_mul_cp,
	fuel_idle_cp,
	fuel_mont_cp,
	fuel_dill_cp,
	fuel_juniper_cp,
	fuel_easter_cp,
	fuel_whet_cp,
	fuel_flint_cp,
	fuel_venturas_cp,
	fuel_redsands_cp,
	fuel_bone_cp,
	fuel_tierra_cp,
	fuel_que_cp,
	fuel_isle_cp,
	fuel_pine_cp,

	fuel_mul_pickup,
	fuel_idle_pickup,
	fuel_mont_pickup,
	fuel_dill_pickup,
	fuel_juniper_pickup,
	fuel_easter_pickup,
	fuel_whet_pickup,
	fuel_flint_pickup,
	fuel_venturas_pickup,
	fuel_redsands_pickup,
	fuel_bone_pickup,
	fuel_tierra_pickup,
	fuel_que_pickup,
	fuel_isle_pickup,
	fuel_pine_pickup
};
new FuelStationData[fuel_station_data];

stock ShowGasStationDialog(playerid)
{
	return ShowPlayerDialog(playerid, FUEL_STATION_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Gas Station", "{FFFFFF}Refuel Vehicle: $60\nRepair Vehicle: $2000\nBuy Neons: $10000", "Select", "Cancel");
}

stock ShowNeonDialog(playerid)
{
	return ShowPlayerDialog(playerid, BUY_NEONS_DIALOG, DIALOG_STYLE_LIST, "{FFFFFF}Gas Station > Buy Neons", "{FFFFFF}Blue Neons: $10000\nRed Neons: $10000\nGreen Neons: $10000\nYellow Neons: $10000\nPink Neons: $10000", "Buy", "Remove");
}

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2202.1926, 2474.4617, 10.8203, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City Gas Station (The Emerald Isle)
	CreateDynamicMapIcon(-2416.3938, 976.3057, 45.2969, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City Gas Station (Juniper Hollow)
	CreateDynamicMapIcon(-1675.8083, 413.1061, 7.1797, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF City Gas Station (Easter Basin)
	CreateDynamicMapIcon(-1606.4551, -2713.7610, 48.5335, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Country Gas Station (Whetstone)
	CreateDynamicMapIcon(-91.1844, -1169.3796, 2.4227, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//SF Country (Flint County)
	CreateDynamicMapIcon(1006.5514, -933.2178, 42.1797, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Gas Station (Mulholland)
	CreateDynamicMapIcon(1938.5087, -1772.8875, 13.3828, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS City Gas Station (Idlewood)
	CreateDynamicMapIcon(1383.3386, 462.3893, 20.1441, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Country Gas Station (Montgomery)
	CreateDynamicMapIcon(658.9343, -564.9854, 16.3359, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LS Country Gas Station (Dillimore)
	CreateDynamicMapIcon(2114.7568, 920.1763, 10.8203, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City Gas Station (Las Venturas)
	CreateDynamicMapIcon(1595.9623, 2199.2573, 10.8203, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV City Gas Station (Redsands West)
	CreateDynamicMapIcon(611.8824, 1694.8765, 6.9922, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Gas Station (Bone County)
	CreateDynamicMapIcon(-1471.5056, 1863.8700, 32.6328, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Gas Station (Tierra Robada)
	CreateDynamicMapIcon(-1328.7943, 2677.6191, 50.0625, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Gas Station (El Quebrados)
	CreateDynamicMapIcon(2147.7903, 2748.0503, 10.8203, 27, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//LV Country Gas Station (Prickle Pine)

	FuelStationData[fuel_mul_cp] = CreateDynamicCP(1006.5514, -933.2178, 42.1797, 3.0, -1, -1, -1, 15.0, -1, 0);//LS City Gas Station (Mulholland)
	FuelStationData[fuel_idle_cp] = CreateDynamicCP(1938.5087, -1772.8875, 13.3828, 3.0, -1, -1, -1, 15.0, -1, 0);//LS City Gas Station (Idlewood)
	FuelStationData[fuel_mont_cp] = CreateDynamicCP(1383.3386, 462.3893, 20.1441, 3.0, -1, -1, -1, 15.0, -1, 0);//LS Country Gas Station (Montgomery)
	FuelStationData[fuel_dill_cp] = CreateDynamicCP(658.9343, -564.9854, 16.3359, 3.0, -1, -1, -1, 15.0, -1, 0);//LS Country Gas Station (Dillimore)
	FuelStationData[fuel_juniper_cp] = CreateDynamicCP(-2416.3938, 976.3057, 45.2969, 3.0, -1, -1, -1, 15.0, -1, 0);//SF City Gas Station (Juniper Hollow)
	FuelStationData[fuel_easter_cp] = CreateDynamicCP(-1675.8083, 413.1061, 7.1797, 3.0, -1, -1, -1, 15.0, -1, 0);//SF City Gas Station (Easter Basin)
	FuelStationData[fuel_whet_cp] = CreateDynamicCP(-1606.4551, -2713.7610, 48.5335, 3.0, -1, -1, -1, 15.0, -1, 0);//SF Country Gas Station (Whetstone)
	FuelStationData[fuel_flint_cp] = CreateDynamicCP(-91.1844, -1169.3796, 2.4227, 3.0, -1, -1, -1, 15.0, -1, 0);//SF Country (Flint County)
	FuelStationData[fuel_venturas_cp] = CreateDynamicCP(2114.7568, 920.1763, 10.8203, 3.0, -1, -1, -1, 15.0, -1, 0);//LV City Gas Station (Las Venturas)
	FuelStationData[fuel_redsands_cp] = CreateDynamicCP(1595.9623, 2199.2573, 10.8203, 3.0, -1, -1, -1, 15.0, -1, 0);//LV City Gas Station (Redsands West)
	FuelStationData[fuel_bone_cp] = CreateDynamicCP(611.8824, 1694.8765, 6.9922, 3.0, -1, -1, -1, 15.0, -1, 0);//LV Country Gas Station (Bone County)
	FuelStationData[fuel_tierra_cp] = CreateDynamicCP(-1471.5056, 1863.8700, 32.6328, 3.0, -1, -1, -1, 15.0, -1, 0);//LV Country Gas Station (Tierra Robada)
	FuelStationData[fuel_que_cp] = CreateDynamicCP(-1328.7943, 2677.6191, 50.0625, 3.0, -1, -1, -1, 15.0, -1, 0);//LV Country Gas Station (El Quebrados)
	FuelStationData[fuel_isle_cp] = CreateDynamicCP(2202.1926, 2474.4617, 10.8203, 3.0, -1, -1, -1, 15.0, -1, 0);//LV City Gas Station (The Emerald Isle)
	FuelStationData[fuel_pine_cp] = CreateDynamicCP(2147.7903, 2748.0503, 10.8203, 3.0, -1, -1, -1, 15.0, -1, 0);//LV City Gas Station (Prickle Pine)

	FuelStationData[fuel_mul_pickup] = CreateDynamicPickup(1318, 1, 1006.5514, -933.2178, 42.179, -1, -1, -1, 100.0, -1, 0);//LS City Gas Station (Mulholland)
	FuelStationData[fuel_idle_pickup] = CreateDynamicPickup(1318, 1, 1938.5087, -1772.8875, 13.3828, -1, -1, -1, 100.0, -1, 0);//LS City Gas Station (Idlewood)
	FuelStationData[fuel_mont_pickup] = CreateDynamicPickup(1318, 1, 1383.3386, 462.3893, 20.1441, -1, -1, -1, 100.0, -1, 0);//LS Country Gas Station (Montgomery)
	FuelStationData[fuel_dill_pickup] = CreateDynamicPickup(1318, 1, 658.9343, -564.9854, 16.3359, -1, -1, -1, 100.0, -1, 0);//LS Country Gas Station (Dillimore)
	FuelStationData[fuel_juniper_pickup] = CreateDynamicPickup(1318, 1, -2416.3938, 976.3057, 45.2969, -1, -1, -1, 100.0, -1, 0);//SF City Gas Station (Juniper Hollow)
	FuelStationData[fuel_easter_pickup] = CreateDynamicPickup(1318, 1, -1675.8083, 413.1061, 7.1797, -1, -1, -1, 100.0, -1, 0);//SF City Gas Station (Easter Basin)
	FuelStationData[fuel_whet_pickup] = CreateDynamicPickup(1318, 1, -1606.4551, -2713.7610, 48.5335, -1, -1, -1, 100.0, -1, 0);//SF Country Gas Station (Whetstone)
	FuelStationData[fuel_flint_pickup] = CreateDynamicPickup(1318, 1, -91.1844, -1169.3796, 2.4227, -1, -1, -1, 100.0, -1, 0);//SF Country (Flint County)
	FuelStationData[fuel_venturas_pickup] = CreateDynamicPickup(1318, 1, 2114.7568, 920.1763, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV City Gas Station (Las Venturas)
	FuelStationData[fuel_redsands_pickup] = CreateDynamicPickup(1318, 1, 1595.9623, 2199.2573, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV City Gas Station (Redsands West)
	FuelStationData[fuel_bone_pickup] = CreateDynamicPickup(1318, 1, 611.8824, 1694.8765, 6.9922, -1, -1, -1, 100.0, -1, 0);//LV Country Gas Station (Bone County)
	FuelStationData[fuel_tierra_pickup] = CreateDynamicPickup(1318, 1, -1471.5056, 1863.8700, 32.6328, -1, -1, -1, 100.0, -1, 0);//LV Country Gas Station (Tierra Robada)
	FuelStationData[fuel_que_pickup] = CreateDynamicPickup(1318, 1, -1328.7943, 2677.6191, 50.0625, -1, -1, -1, 100.0, -1, 0);//LV Country Gas Station (El Quebrados)
	FuelStationData[fuel_isle_pickup] = CreateDynamicPickup(1318, 1, 2202.1926, 2474.4617, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV City Gas Station (The Emerald Isle)
	FuelStationData[fuel_pine_pickup] = CreateDynamicPickup(1318, 1, 2147.7903, 2748.0503, 10.8203, -1, -1, -1, 100.0, -1, 0);//LV City Gas Station (Prickle Pine)
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	if(pickupid == FuelStationData[fuel_mul_pickup] || pickupid == FuelStationData[fuel_idle_pickup] || pickupid == FuelStationData[fuel_mont_pickup] || 
	pickupid == FuelStationData[fuel_dill_pickup] || pickupid == FuelStationData[fuel_juniper_pickup] || pickupid == FuelStationData[fuel_easter_pickup] || 
	pickupid == FuelStationData[fuel_whet_pickup] || pickupid == FuelStationData[fuel_flint_pickup] || pickupid == FuelStationData[fuel_venturas_pickup] || 
	pickupid == FuelStationData[fuel_redsands_pickup] || pickupid == FuelStationData[fuel_bone_pickup] || pickupid == FuelStationData[fuel_tierra_pickup] || 
	pickupid == FuelStationData[fuel_que_pickup] || pickupid == FuelStationData[fuel_isle_pickup] || pickupid == FuelStationData[fuel_pine_pickup]) return 1;
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsVehicleBicycle(GetPlayerVehicleID(playerid)))
	{
		if(checkpointid == FuelStationData[fuel_mul_cp] ||
		checkpointid == FuelStationData[fuel_idle_cp] ||
		checkpointid == FuelStationData[fuel_mont_cp] ||
		checkpointid == FuelStationData[fuel_dill_cp] ||
		checkpointid == FuelStationData[fuel_juniper_cp] ||
		checkpointid == FuelStationData[fuel_easter_cp] ||
		checkpointid == FuelStationData[fuel_whet_cp] ||
		checkpointid == FuelStationData[fuel_flint_cp] ||
		checkpointid == FuelStationData[fuel_venturas_cp] ||
		checkpointid == FuelStationData[fuel_redsands_cp] ||
		checkpointid == FuelStationData[fuel_bone_cp] ||
		checkpointid == FuelStationData[fuel_tierra_cp] ||
		checkpointid == FuelStationData[fuel_que_cp] ||
		checkpointid == FuelStationData[fuel_isle_cp])
		{
			ShowGasStationDialog(playerid);
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case FUEL_STATION_DIALOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0://Refuel Vehicle
					{
						if(GetPlayerMoneyEx(playerid) < 60) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");

						new string[128], name[24], Float:pos[3];
						foreach(new v : Vehicle)
						{
							GetVehiclePos(v, pos[0], pos[1], pos[2]);
							if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
							{
								if(GetVehicleFuel(v) >= 100) return SendClientMessage(playerid, RED, "ERROR: That vehicle currently has 100 percent fuel.");

							 	GivePlayerMoney(playerid, -60);

								SetVehicleFuel(v, 100);

								PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

								GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
								GetPlayerName(playerid, name, sizeof(name));

								foreach(new i : Player)
								{
									if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
									{
										format(string, sizeof(string), "** %s refuels their vehicle...", name);
										SendClientMessage(i, GREY, string);
									}
								}
								return ShowGasStationDialog(playerid);
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to refuel.");
					}
					case 1://Repair Vehicle
					{
						if(GetPlayerMoneyEx(playerid) < 2000) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");

						new string[128], name[24], Float:pos[3];
						foreach(new v : Vehicle)
						{
							GetVehiclePos(v, pos[0], pos[1], pos[2]);
							if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
							{
								GivePlayerMoney(playerid, -2000);

								RepairVehicle(v);

								PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

								GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
								GetPlayerName(playerid, name, sizeof(name));

								foreach(new i : Player)
								{
									if(IsPlayerInRangeOfPoint(i, 10.0, pos[0], pos[1], pos[2]))
									{
										format(string, sizeof(string), "** %s repairs their vehicle...", name);
										SendClientMessage(i, GREY, string);
									}
								}
								return ShowGasStationDialog(playerid);
							}
						}
						return SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to repair.");
					}
					case 2://Buy Neons
					{
						return ShowNeonDialog(playerid);
					}
				}
			}
			return 1;
		}
		case BUY_NEONS_DIALOG:
		{
			if(response)
			{
				new neons = NO_NEONS;
				switch(listitem)
				{
					case 0://Blue Neons
					{
						neons = BLUE_NEONS;
					}
					case 1://Red Neons
					{
						neons = RED_NEONS;
					}
					case 2://Green Neons
					{
						neons = GREEN_NEONS;
					}
					case 3://Yellow Neons
					{
						neons = YELLOW_NEONS;
					}
					case 4://Pink Neons
					{
						neons = PINK_NEONS;
					}
				}

				new Float:pos[3], characterid = GetPlayerCharacterID(playerid);
				foreach(new v : Vehicle)
				{
					GetVehiclePos(v, pos[0], pos[1], pos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
					{
						if(characterid != GetVehicleCharacterID(v)) return SendClientMessage(playerid, RED, "ERROR: You can only add neons to vehicles you own.");
						if(GetVehicleNeons(v) != NO_NEONS) return SendClientMessage(playerid, RED, "ERROR: This vehicle already has neons, remove the olds ones first.");

						for(new check = 0; check < sizeof(NonNeonVehicles); check++)
						{
							if(GetVehicleModel(v) == NonNeonVehicles[check]) return SendClientMessage(playerid, RED, "ERROR: You cannot add neons to this vehicle.");
						}
						
						if(GetPlayerMoneyEx(playerid) < 10000) return SendClientMessage(playerid, RED, "ERROR: You don't have that much money in your pocket.");
						GivePlayerMoney(playerid, -10000);

						SetVehicleNeons(v, neons);

						CreateVehicleNeons(v);
							
						return PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					}
				}

				SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to add neons to.");
				return 1;
			}
			else
			{
				new Float:pos[3], name[24], characterid = GetPlayerCharacterID(playerid);
				GetPlayerName(playerid, name, sizeof(name));
				foreach(new v : Vehicle)
				{
					GetVehiclePos(v, pos[0], pos[1], pos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 10.0, pos[0], pos[1], pos[2]))
					{
						if(characterid != GetVehicleCharacterID(v)) return SendClientMessage(playerid, RED, "ERROR: You can only remove neons from vehicles you own.");
						if(GetVehicleNeons(v) == NO_NEONS) return SendClientMessage(playerid, RED, "ERROR: This vehicle does not have any neons.");

						SetVehicleNeons(v, NO_NEONS);

						DestroyVehicleNeons(v);
							
						return PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					}
				}
				
				SendClientMessage(playerid, RED, "ERROR: There are no vehicles nearby to remove neons from.");
			}
			return 1;
		}
	}
	return 1;
}
