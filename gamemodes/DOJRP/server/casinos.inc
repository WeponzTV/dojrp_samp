#include <YSI_Coding\y_hooks>

enum casino_data
{
	caligulas_ent_cp,
	caligulas_ext_cp,

	caligulas_elev_ent_cp,
	caligulas_elev_ext_cp,

	caligulas_roof1_ent_cp,
	caligulas_roof1_ext_cp,

	caligulas_roof2_ent_cp,
	caligulas_roof2_ext_cp,

	dragons_ent_cp,
	dragons_ext_cp,

	dragons_office_ent_cp,
	dragons_office_ext_cp
};
new CasinoData[casino_data];

hook OnGameModeInit()
{
	CreateDynamicMapIcon(2196.9688, 1677.2032, 12.3672, 25, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Caligula's Casino
	CreateDynamicMapIcon(2019.3152, 1007.7106, 10.8203, 44, -1, 0, 0, -1, 500.0, MAPICON_LOCAL, -1, 0);//Four Dragons Casino

	CasinoData[caligulas_ent_cp] = CreateDynamicCP(2196.9666, 1677.1818, 12.3672, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Casino Entrance
	CasinoData[caligulas_ext_cp] = CreateDynamicCP(2233.9170, 1714.6865, 1012.3828, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Casino Exit

	CasinoData[caligulas_elev_ent_cp] = CreateDynamicCP(2135.6968, 1599.4539, 1008.3560, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Elevator (Bottom)
	CasinoData[caligulas_elev_ext_cp] = CreateDynamicCP(2265.8799, 1647.5100, 1084.2344, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Elevator (Top)

	CasinoData[caligulas_roof1_ent_cp] = CreateDynamicCP(2264.3940, 1675.7527, 1090.4453, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Rooftop Entrance (Left)
	CasinoData[caligulas_roof1_ext_cp] = CreateDynamicCP(2267.9170, 1675.7654, 94.9219, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Rooftop Exit (Left)

	CasinoData[caligulas_roof2_ent_cp] = CreateDynamicCP(2264.4019, 1619.5166, 1090.4453, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Rooftop Entrance (Right)
	CasinoData[caligulas_roof2_ext_cp] = CreateDynamicCP(2267.9717, 1619.5059, 94.9219, 1.0, -1, -1, -1, 5.0, -1, 0);//Caligula's Rooftop Exit (Right)

	CasinoData[dragons_ent_cp] = CreateDynamicCP(2019.3157, 1007.7171, 10.8203, 1.0, -1, -1, -1, 5.0, -1, 0);//Four Dragons Casino Entrance
	CasinoData[dragons_ext_cp] = CreateDynamicCP(2019.0714, 1017.8608, 996.8750, 1.0, -1, -1, -1, 5.0, -1, 0);//Four Dragons Casino Exit

	CasinoData[dragons_office_ent_cp] = CreateDynamicCP(1925.1981, 1017.7599, 994.4688, 1.0, -1, -1, -1, 5.0, -1, 0);//Four Dragons Office Entrance
	CasinoData[dragons_office_ext_cp] = CreateDynamicCP(2134.7419, 1599.5425, 1008.3594, 1.0, -1, -1, -1, 2.0, -1, 0);//Four Dragons Office Exit
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(checkpointid == CasinoData[caligulas_ent_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2233.9163, 1712.5156, 1011.8515);
			SetPlayerFacingAngle(playerid, 179.9613);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_ext_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2195.1106, 1677.1831, 12.3672);
			SetPlayerFacingAngle(playerid, 88.7443);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_elev_ent_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 2267.5278, 1647.4645, 1084.2344);
			SetPlayerFacingAngle(playerid, 269.5737);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_elev_ext_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2137.3157, 1599.4092, 1008.3666);
			SetPlayerFacingAngle(playerid, 267.8326);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_roof1_ent_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2269.5752, 1675.7635, 94.9219);
			SetPlayerFacingAngle(playerid, 268.7239);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_roof1_ext_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 2266.1641, 1675.7577, 1090.4453);
			SetPlayerFacingAngle(playerid, 270.3006);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_roof2_ent_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2269.7434, 1619.5106, 94.9219);
			SetPlayerFacingAngle(playerid, 270.3040);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[caligulas_roof2_ext_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 2266.1580, 1619.5510, 1090.4453);
			SetPlayerFacingAngle(playerid, 269.9944);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[dragons_ent_cp])
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 2017.5292, 1017.8492, 996.8750);
			SetPlayerFacingAngle(playerid, 90.4214);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[dragons_ext_cp])
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, 2021.2345, 1007.7434, 10.8203);
			SetPlayerFacingAngle(playerid, 268.8527);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[dragons_office_ent_cp])
		{
			SetPlayerInterior(playerid, 1);
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerPos(playerid, 2133.3328, 1599.5348, 1008.3594);
			SetPlayerFacingAngle(playerid, 90.2815);
			return SetCameraBehindPlayer(playerid);
		}
		else if(checkpointid == CasinoData[dragons_office_ext_cp])
		{
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid, 1);
			SetPlayerPos(playerid, 1926.6727, 1017.7620, 994.4688);
			SetPlayerFacingAngle(playerid, 270.5047);
			return SetCameraBehindPlayer(playerid);
		}
	}
	return 1;
}
