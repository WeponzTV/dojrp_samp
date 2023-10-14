/*
	> Project: Department of Justice Roleplay aka DOJ:RP (SA-MP)
	> Version: v1.1
	> Credits: Weponz (Developer), realdiegopoptart (Tester), South_Central (Tester), Ebann (Tester)
	> Started: Feb 2022 (Released: Oct 2023)
	
	*** As seen on YouTube: https://www.youtube.com/@WeponzTV ***
	
	> Changelog (v1.0):
	- Added NEW Database System: Implemented a SQLite-based database system.
	- Added NEW Master Account System: Create, load & delete characters.
	- Added NEW Admin System: Fully functional admin system with levels.
	- Added NEW Helper System: Helpers can answer player's questions.
	- Added NEW V.I.P System: Give players special perks & features.
	- Added NEW Safezone System: Hospitals are safe places for players.
	- Added NEW Jail System: Go to jail in a cell at the nearest police dept.
	- Added NEW Police System: Clock-on & off at the nearest police dept.
	- Added NEW CIA System: Clock-on & off at the nearest CIA headquarters.
	- Added NEW Army System: Clock-on & off at area 69, navy base & docks.
	- Added NEW Paramedic System: Become a qualified paramedic & heal players.
	- Added NEW Firefighter System: Fight fires as a qualified firefighter.
	- Added NEW Degree System: Purchase degrees to access special jobs/skills.
	- Added NEW License System: Purchase gun, car, truck, pilot licenses & more.
	- Added NEW Binco System: Select a skin from a list of sprite images.
	- Added NEW Restaurant System: Dine at burger shots, cluckin' bells & more.
	- Added NEW Ammunation System: Purchase weapons, throwables & more.
	- Added NEW Robbery System: Holdup NPC clerks at gunpoint like GTA 5.
	- Added NEW Safe Cracking System: Crack safes at both of the casinos.
	- Added NEW Bus Stop System: Fast travel around each city with ease.
	- Added NEW Airport System: Fast travel between each island with ease.
	- Added NEW Fuel System: Refuel your vehicle at gas stations & more.
	- Added NEW Paycheck System: Receive a pay check or welfare check every hour.
	- Added NEW Tax System: Pay income & wealth taxes after each paycheck.
	- Added NEW Banking System: Apply for loans, transfer money & more.
	- Added NEW ATM System: x6 ATMs can be located around the countryside.
	- Added NEW Item System: Purchase food, drinks, tools & more at 24-7.
	- Added NEW Inventory System: Use & drop items from your inventory.
	- Added NEW Hunger/Thirst System: Players must eat & drink to survive.
	- Added NEW Personal Vehicle System: Purchase used, new & special vehicles.
	- Added NEW Arms Dealer System: Buy gun materials & craft/sell weapons.
	- Added NEW Weed System: Purchase seeds & grow weed to sell by the pound.
	- Added NEW Pilot System: Become a pilot & complete passenger/cargo flights.
	- Added NEW Trucking System: Become a truck driver & haul things around the map.
	- Added NEW Mining System: Become a miner and mine stone/gold/diamonds at the quarry.
	- Added NEW Fight Style System: Learn a range of fighting styles at the gym.
	- Added NEW Speed Camera System: You get fined for driving over the speed limit.
	- Added NEW Spike Strip System: Law enforcement can create spike strips anywhere.
	- Added NEW Road Block System: Law enforcement can create road blocks anywhere.
	- Added NEW Vehicle System: Vehicle engines & lights etc. must be toggled manually.
	- Added NEW RP Death System: Realistic damages + become wounded & accept death.
	- Added NEW Weather/Time System: Server will automatically shift through weather/time.
	- Added NEW Vending Machine System: Create & delete your own sprunk vending machines.
	- Added NEW Housing System: Players can purchase houses, mansions & apartments.
	- Added NEW Business System: Players can purchase value-increasing businesses.
	- Added NEW Clan System: Create, join, and leave clans with a level/ranking system.
	- Added NEW Anticheat System: Running a popular anticheat with up to 53 detections.
	
	> Changelog (v1.1):
	- Major bug fixes to existing systems.
	- Added 5 minute timer to robberies.
	- Added much needed commands.
*/
#define SSCANF_NO_NICE_FEATURES
#include "a_samp.inc"
#include "sqlitei.inc"
#include "samp_bcrypt.inc"
#include "streamer.inc"
#include "sscanf2.inc"
#include "actor_robbery.inc"
native IsValidVehicle(vehicleid);

#define DEBUG
#include "nex-ac_en.lang"
#include "nex-ac.inc"

#define CGEN_MEMORY 60000
#define YSI_NO_HEAP_MALLOC

DEFINE_HOOK_REPLACEMENT(Dyn, Dynamic);

#include "YSI_Coding\y_malloc.inc"
#include "YSI_Coding\y_hooks.inc"
#include "YSI_Coding\y_timers.inc"
#include "YSI_Data\y_iterate.inc"
#include "YSI_Visual\y_commands.inc"

#include "DOJRP/core/config.inc"
#include "DOJRP/core/database.inc"
#include "DOJRP/core/anticheat.inc"

#include "DOJRP/player/misc.inc"
#include "DOJRP/player/accounts.inc"
#include "DOJRP/player/animations.inc"
#include "DOJRP/player/chat.inc"
#include "DOJRP/player/locations.inc"
#include "DOJRP/player/clans.inc"
#include "DOJRP/player/stats.inc"
#include "DOJRP/player/skills.inc"
#include "DOJRP/player/weapons.inc"
#include "DOJRP/player/textdraws.inc"
#include "DOJRP/player/inventory.inc"
#include "DOJRP/player/cellphones.inc"
#include "DOJRP/player/lottery.inc"
#include "DOJRP/player/paycheck.inc"
#include "DOJRP/player/wanted.inc"
#include "DOJRP/player/deaths.inc"
#include "DOJRP/player/skins.inc"
#include "DOJRP/player/timers.inc"
#include "DOJRP/player/commands.inc"
#include "DOJRP/player/admin.inc"
#include "DOJRP/player/camera.inc"

#include "DOJRP/server/objects.inc"
#include "DOJRP/server/vehicles.inc"
#include "DOJRP/server/housing.inc"
#include "DOJRP/server/businesses.inc"
#include "DOJRP/server/safezones.inc"
#include "DOJRP/server/transport.inc"
#include "DOJRP/server/education.inc"
#include "DOJRP/server/materials.inc"
#include "DOJRP/server/dealer.inc"
#include "DOJRP/server/enforcement.inc"
#include "DOJRP/server/corrections.inc"
#include "DOJRP/server/services.inc"
#include "DOJRP/server/banking.inc"
#include "DOJRP/server/robberies.inc"
#include "DOJRP/server/safecracking.inc"
#include "DOJRP/server/fuelstations.inc"
#include "DOJRP/server/ammunations.inc"
#include "DOJRP/server/restaurants.inc"
#include "DOJRP/server/stores.inc"
#include "DOJRP/server/retail.inc"
#include "DOJRP/server/casinos.inc"
#include "DOJRP/server/clubs.inc"
#include "DOJRP/server/bars.inc"
#include "DOJRP/server/gyms.inc"
#include "DOJRP/server/pilot.inc"
#include "DOJRP/server/trucking.inc"
#include "DOJRP/server/mining.inc"
#include "DOJRP/server/vending.inc"

main()
{
	SendRconCommand(MAP_NAME);
	SendRconCommand(SERVER_LANG);
}

public OnGameModeInit()
{
	EnableVehicleFriendlyFire();
	DisableInteriorEnterExits();
    EnableStuntBonusForAll(0);
    
    ShowPlayerMarkers(SHOW_PLAYER_MARKERS);
    ShowNameTags(SHOW_NAME_TAGS);
    SetNameTagDrawDistance(NAME_TAG_DRAW_DISTANCE);

	SetGameModeText(SERVER_TAG);

	OpenDatabase();

	LoadSprunkMachines();
	LoadBusStops();
	LoadHouses();
	LoadBusinesses();
	return 1;
}

public OnGameModeExit()
{
	foreach(new i : Player)
	{
		OnPlayerDisconnect(i, 0);
	}

	UnloadSprunkMachines();
	UnloadBusStops();
	UnloadHouses();
	UnloadBusinesses();
	
	CloseDatabase();
	return 1;
}
