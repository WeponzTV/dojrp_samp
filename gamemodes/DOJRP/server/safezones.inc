#include <YSI_Coding\y_hooks>

enum safezone_data
{
	ls_safezone,
	ls_gangzone,

	sf_safezone,
	sf_gangzone,

	lv_safezone,
	lv_gangzone
};
new SafezoneData[safezone_data];

hook OnGameModeInit()
{
	SafezoneData[ls_safezone] = CreateDynamicRectangle(1996.8435, -1451.1461, 2102.0012, -1394.8970, 0, 0, -1, 0);//LS Hospital (Safezone)
	SafezoneData[sf_safezone] = CreateDynamicRectangle(-2740.7754, 578.3627, -2536.7644, 698.2106, 0, 0, -1, 0);//SF Hospital (Safezone)
	SafezoneData[lv_safezone] = CreateDynamicRectangle(1578.1887, 1724.0845, 1636.4933, 1862.3687, 0, 0, -1, 0);//LV Hospital (Safezone)

	SafezoneData[ls_gangzone] = GangZoneCreate(1996.8435, -1451.1461, 2102.0012, -1394.8970);//LS Hospital (Safezone)
	SafezoneData[sf_gangzone] = GangZoneCreate(-2740.7754, 578.3627, -2536.7644, 698.2106);//SF Hospital (Safezone)
	SafezoneData[lv_gangzone] = GangZoneCreate(1578.1887, 1724.0845, 1636.4933, 1862.3687);//LV Hospital (Safezone)
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		GangZoneShowForAll(SafezoneData[ls_gangzone], GREEN);
		GangZoneShowForAll(SafezoneData[sf_gangzone], GREEN);
		GangZoneShowForAll(SafezoneData[lv_gangzone], GREEN);
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(areaid == SafezoneData[ls_safezone] || areaid == SafezoneData[sf_safezone] || areaid == SafezoneData[lv_safezone])
	{
		if(GetDutyStatus(playerid) == true || GetCameraStatus(playerid) == true) return 1;
		else if(!IsPlayerSafe(playerid))
		{
			SetPlayerSafe(playerid, true);

			new Float:health, Float:armour;
			GetPlayerHealth(playerid, health);
			GetPlayerArmour(playerid, armour);

			SetStoredHealth(playerid, health);
			SetStoredArmour(playerid, armour);

			StoreWeaponData(playerid);

			SetPlayerHealth(playerid, MAX_HEALTH);
			SetPlayerArmour(playerid, 0.0);

			ResetPlayerWeapons(playerid);
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	if(areaid == SafezoneData[ls_safezone] || areaid == SafezoneData[sf_safezone] || areaid == SafezoneData[lv_safezone])
	{
		if(GetDutyStatus(playerid) == true || GetCameraStatus(playerid) == true) return 1;
		else if(IsPlayerSafe(playerid))
		{
			SetPlayerHealth(playerid, GetStoredHealth(playerid));
			SetPlayerArmour(playerid, GetStoredArmour(playerid));

			RestoreStoredWeapons(playerid);

			SetPlayerSafe(playerid, false);
		}
	}
	return 1;
}
