#include <YSI_Coding\y_hooks>

#define RED 0xFF0000FF//Changing this colour will change the following colour throughout the whole script. (Default: RED)
#define PINK 0xFFC0CBFF//Changing this colour will change the following colour throughout the whole script. (Default: PINK)
#define ORANGE 0xFFA500FF//Changing this colour will change the following colour throughout the whole script. (Default: ORANGE)
#define YELLOW 0xFFFF00FF//Changing this colour will change the following colour throughout the whole script. (Default: YELLOW)
#define PURPLE 0x800080FF//Changing this colour will change the following colour throughout the whole script. (Default: PURPLE)
#define GREEN 0x008000FF//Changing this colour will change the following colour throughout the whole script. (Default: GREEN)
#define BLUE 0x0000FFFF//Changing this colour will change the following colour throughout the whole script. (Default: BLUE)
#define LIGHTGREEN 0x24FF0AB9//Changing this colour will change the following colour throughout the whole script. (Default: LIGHTGREEN)
#define LIGHTBLUE 0x0080C0FF//Changing this colour will change the following colour throughout the whole script. (Default: LIGHTBLUE)
#define WHITE 0xFFFFFFFF//Changing this colour will change the following colour throughout the whole script. (Default: WHITE)
#define GREY 0x808080FF//Changing this colour will change the following colour throughout the whole script. (Default: GREY)

#define ADMIN_COLOUR 0x800080FF//This is the colour admin markers will be when they are on duty. (Default: PURPLE)

#define DATABASE_LOCATION "DOJRP/server.db"//This is the location of the SQLite database. (Default: scriptfiles/DOJRP/server.db)

#define SERVER_TAG "DOJ:RP"//This will show on global vehicle number plates, gamemode text, and some dialogs. (Default: DOJ:RP)

#define MAP_NAME "mapname San Andreas"//This will show on the client's server list. (Default: San Andreas)
#define SERVER_LANG "language English"//This will show on the client's server list. (Default: English)

#define SHOW_PLAYER_MARKERS 2//Change this to 0 if you do not want player markers to show. (Deault: 2/Showing)
#define SHOW_NAME_TAGS 1//Change this to 0 if you do not want player name tags to show. (Deault: 1/Showing)
#define NAME_TAG_DRAW_DISTANCE 25.0//This is the draw distance for player name tags. (Default: 25 Metres)

//#define USE_MILES//Uncomment this line if you wish to use miles instead of kilometers for vehicle speeds. (Default: KM/H)

#define SPEED_LIMIT 120//This the the speed limit for roadside speed cameras in kilometers. (Default: 120 KM/H)
#define SPEEDING_FINE 5000//Players will pay anywhere from 50% to 100% of this amount. (Default: $5K)

#define FIRST_SPAWN_X 1642.2411//This is the first place players spawn. (Default: LS Airport)
#define FIRST_SPAWN_Y -2332.7742//This is the first place players spawn. (Default: LS Airport)
#define FIRST_SPAWN_Z 13.5469//This is the first place players spawn. (Default: LS Airport)
#define FIRST_SPAWN_A 0.1502//This is the first place players spawn. (Default: LS Airport)

#define FIRST_SPAWN_INT 0//This is the first place players spawn. (Default: LS Airport)
#define FIRST_SPAWN_WORLD 0//This is the first place players spawn. (Default: LS Airport)

#define JAIL_SECS 120//This is how much time prisoners will have to do in jail. (Default: 120 Seconds)

#define SAFE_WAIT_SECS 300//This is how long players have to wait between cracking safes. (Default: 300 Seconds)
#define SAFE_CRACK_CHANCE 5//Increase this number slightly to increase the chance of success. (Default: 5)
#define SAFE_CRACK_SECS 15//This is how long it will take to crack a safe. (Default: 15 Seconds)

#define MATERIALS_COST 500//This is the cost for each box of gun materials purchasable at the arms dealer in the secret shack. (Default: $500)
#define SEEDS_COST 1000//This is the cost for x1 seeds purchasable at the drug dealer in the trap house. (Default: $1000)

#define POUNDS_PRICE 35000//This is the price the drug dealer will pay for each pound of weed sold at the trap house. (Default: $35K)

#define STONE_ORE_PRICE 50//This is the price per gram paid for stone unloaded by a miner at the quarry. (Default: $50)
#define GOLD_ORE_PRICE 100//This is the price per gram paid for gold unloaded by a miner at the quarry. (Default: $100)
#define DIAMONDS_ORE_PRICE 75//This is the price per gram paid for diamonds unloaded by a miner at the quarry. (Default: $75)

#define USED_BUFFALO_PRICE 25000//This is the price of this vehicle at each car dealership. (Default: $25K)
#define USED_PERENAIL_PRICE 15000//This is the price of this vehicle at each car dealership. (Default: $15K)
#define USED_VOODOO_PRICE 35000//This is the price of this vehicle at each car dealership. (Default: $35K)
#define USED_OCEANIC_PRICE 15000//This is the price of this vehicle at each car dealership. (Default: $15K)
#define USED_BLISTA_PRICE 25000//This is the price of this vehicle at each car dealership. (Default: $25K)
#define USED_CLOVER_PRICE 15000//This is the price of this vehicle at each car dealership. (Default: $15K)
#define USED_HUSTLER_PRICE 35000//This is the price of this vehicle at each car dealership. (Default: $35K)
#define USED_TORNADO_PRICE 15000//This is the price of this vehicle at each car dealership. (Default: $15K)
#define USED_CLUB_PRICE 25000//This is the price of this vehicle at each car dealership. (Default: $25K)

#define NEW_INFERNUS_PRICE 150000//This is the price of this vehicle at each car dealership. (Default: $150K)
#define NEW_CHEETAH_PRICE 120000//This is the price of this vehicle at each car dealership. (Default: $120K)
#define NEW_BANSHEE_PRICE 175000//This is the price of this vehicle at each car dealership. (Default: $175K)
#define NEW_TURISMO_PRICE 120000//This is the price of this vehicle at each car dealership. (Default: $120K)
#define NEW_ZR350_PRICE 150000//This is the price of this vehicle at each car dealership. (Default: $150K)
#define NEW_COMET_PRICE 100000//This is the price of this vehicle at each car dealership. (Default: $100K)
#define NEW_SUPERGT_PRICE 175000//This is the price of this vehicle at each car dealership. (Default: $175K)
#define NEW_BULLET_PRICE 175000//This is the price of this vehicle at each car dealership. (Default: $175K)
#define NEW_SULTAN_PRICE 150000//This is the price of this vehicle at each car dealership. (Default: $150K)

#define SPECIAL_BFINJECTION_PRICE 75000//This is the price of this vehicle at each car dealership. (Default: $75K)
#define SPECIAL_HOTKNIFE_PRICE 60000//This is the price of this vehicle at each car dealership. (Default: $60K)
#define SPECIAL_MONSTER_PRICE 85000//This is the price of this vehicle at each car dealership. (Default: $85K)
#define SPECIAL_NRG500_PRICE 55000//This is the price of this vehicle at each car dealership. (Default: $55K)
#define SPECIAL_PCJ600_PRICE 35000//This is the price of this vehicle at each car dealership. (Default: $35K)
#define SPECIAL_FREEWAY_PRICE 45000//This is the price of this vehicle at each car dealership. (Default: $45K)
#define SPECIAL_SANCHEZ_PRICE 25000//This is the price of this vehicle at each car dealership. (Default: $25K)
#define SPECIAL_QUAD_PRICE 15000//This is the price of this vehicle at each car dealership. (Default: $15K)
#define SPECIAL_MAVERICK_PRICE 250000//This is the price of this vehicle at each car dealership. (Default: $250K)

#define ONE_NUMBER_WINNINGS 250000//This is how much the player gets if they get x1 lotto number correct. (Default: $250K)
#define TWO_NUMBER_WINNINGS 750000//This is how much the player gets if they get x2 lotto numbers correct. (Default: $750K)
#define THREE_NUMBER_WINNINGS 1000000//This is how much the player gets if they get x3 lotto numbers correct. (Default: $1M)
#define FOUR_NUMBER_WINNINGS 3000000//This is how much the player gets if they get x4 lotto numbers correct. (Default: $3M)
#define FIVE_NUMBER_WINNINGS 5000000//This is how much the player gets if they get x5 lotto numbers correct. (Default: $5M)
#define SIX_NUMBER_WINNINGS 10000000//This is how much the player gets if they get x6 lotto numbers correct. (Default: $10M)

#define MAX_PASSENGER_EARNINGS 50000//Players will get anywhere from 50% to 100% of this amount. (Default: $50k)
#define MAX_CARGO_EARNINGS 30000//Players will get anywhere from 50% to 100% of this amount. (Default: $30k)

#define MAX_HAUL_EARNINGS 75000//Players will get anywhere from 50% to 100% of this amount. (Default: $75k)

#define MAX_CANCEL_FINE 5000//Players will pay anywhere from 50% to 100% of this amount. (Default: $5k)

#define LS_AIRPORT_X 1853.0616//This is the position of LS Airport's flights checkpoint.
#define LS_AIRPORT_Y -2440.9509//This is the position of LS Airport's flights checkpoint.
#define LS_AIRPORT_Z 13.5547//This is the position of LS Airport's flights checkpoint.

#define SF_AIRPORT_X -1301.1484//This is the position of SF Airport's flights checkpoint.
#define SF_AIRPORT_Y -7.3090//This is the position of SF Airport's flights checkpoint.
#define SF_AIRPORT_Z 14.1484//This is the position of SF Airport's flights checkpoint.

#define LV_AIRPORT_X 1550.7661//This is the position of LV Airport's flights checkpoint.
#define LV_AIRPORT_Y 1609.7490//This is the position of LV Airport's flights checkpoint.
#define LV_AIRPORT_Z 10.8203//This is the position of LV Airport's flights checkpoint.

#define CARGO_ONE_X 2618.5696//This is the position of Cargo #1's flights checkpoint.
#define CARGO_ONE_Y 2721.5117//This is the position of Cargo #1's flights checkpoint.
#define CARGO_ONE_Z 36.5386//This is the position of Cargo #1's flights checkpoint.

#define CARGO_TWO_X 365.3387//This is the position of Cargo #2's flights checkpoint.
#define CARGO_TWO_Y 2537.1858//This is the position of Cargo #2's flights checkpoint.
#define CARGO_TWO_Z 16.6649//This is the position of Cargo #2's flights checkpoint.

#define CARGO_THREE_X -2227.4553//This is the position of Cargo #3's flights checkpoint.
#define CARGO_THREE_Y 2326.8008//This is the position of Cargo #3's flights checkpoint.
#define CARGO_THREE_Z 7.5469//This is the position of Cargo #3's flights checkpoint.

#define MAX_HOUSES 500//You should only increase this number if the script tells you to. (Default: 500 Houses)
#define MAX_BUSINESSES 500//You should only increase this number if the script tells you to. (Default: 500 Businesses)
#define MAX_ITEMS 250//This is the max amount of items that can exist before it automatically resets. (Default: 250 Items)
#define MAX_FIRES 5//This is the max amount of house fires that can exist at any given time. (Default: 5 Fires)
#define MAX_SPIKES 25//This is the max amount of spike strips that can exist at any given time. (Default: 25 Spike Strips)
#define MAX_BLOCKS 25//This is the max amount of road blocks that can exist at any given time. (Default: 25 Road Blocks)
#define MAX_SPRUNKS 100//This is the max amount of vending machines that can exist at any given time. (Default: 100 Machines)
#define MAX_FAILS 3//This is the max amount of times a player can get their password incorrect before being kicked. (Default: 3 Times)
#define MAX_WARNS 3//This is the max amount of times a player can be warned before automatically being kicked. (Default: 3 Times)

#define MAX_PLAYER_VEHICLES 2//This is the max amount of vehicles a player can own. (Default: 2 Vehicles)
#define MAX_VIP_VEHICLES 3//This is the max amount of vehicles a V.I.P can own. (Default: 3 Vehicles)

#define MAX_PLAYER_HOUSES 1//This is the max amount of houses a player can own. (Default: 1 House)
#define MAX_VIP_HOUSES 2//This is the max amount of houses a V.I.P can own. (Default: 2 Houses)

#define MAX_PLAYER_BUSINESSES 1//This is the max amount of businesses a player can own. (Default: 1 Business)
#define MAX_VIP_BUSINESSES 2//This is the max amount of businesses a V.I.P can own. (Default: 2 Businesses)

#define MAX_PLAYER_WEIGHT 30//This is the max weight for each player's inventory. (Default: 30 Pounds)
#define MAX_VIP_WEIGHT 50//This is the max weight for each V.I.P's inventory. (Default: 50 Pounds)

#define MAX_LS_STOPS 25//You should only increase this number if the script tells you to. (Default: 25 Bus Stops)
#define MAX_SF_STOPS 25//You should only increase this number if the script tells you to. (Default: 25 Bus Stops)
#define MAX_LV_STOPS 25//You should only increase this number if the script tells you to. (Default: 25 Bus Stops)

#define MAX_STORE_ROBBERY 25000//Players will get anywhere from 50% to 100% of this amount. (Default: $25K)
#define MAX_BANK_ROBBERY 75000//Players will get anywhere from 50% to 100% of this amount. (Default: $75K)
#define MAX_SAFE_ROBBERY 150000//Players will get anywhere from 50% to 100% of this amount. (Default: $150K)

#define MAX_ARREST_PAY 20000//Players will get anywhere from 50% to 100% of this amount. (Default: $20K)
#define MAX_HEAL_PAY 50000//Players will get anywhere from 50% to 100% of this amount. (Default: $50K)
#define MAX_FIRE_PAY 30000//Players will get anywhere from 50% to 100% of this amount. (Default: $30K)

#define MAX_UNEMPLOYED_PAYCHECK 10000//Players will get anywhere from 50% to 100% of this amount. (Default: $10K)
#define MAX_POLICE_PAYCHECK 50000//Players will get anywhere from 50% to 100% of this amount. (Default: $50K)
#define MAX_CIA_PAYCHECK 100000//Players will get anywhere from 50% to 100% of this amount. (Default: $100K)
#define MAX_ARMY_PAYCHECK 100000//Players will get anywhere from 50% to 100% of this amount. (Default: $100K)
#define MAX_EMS_PAYCHECK 50000//Players will get anywhere from 50% to 100% of this amount. (Default: $50K)
#define MAX_FIRE_PAYCHECK 50000//Players will get anywhere from 50% to 100% of this amount. (Default: $50K)
#define MAX_MINER_PAYCHECK 30000//Players will get anywhere from 50% to 100% of this amount. (Default: $30K)
#define MAX_PILOT_PAYCHECK 30000//Players will get anywhere from 50% to 100% of this amount. (Default: $30K)
#define MAX_TRUCKER_PAYCHECK 30000//Players will get anywhere from 50% to 100% of this amount. (Default: $30K)

#define MAX_MEDICAL_FEE 2000//Players will pay anywhere from 50% to 100% of this amount. (Default: $2K)
#define MAX_FINE_FEE 3000//Players will pay anywhere from 50% to 100% of this amount. (Default: $3K)
#define MAX_BAIL_FEE 4000//Players will pay anywhere from 50% to 100% of this amount. (Default: $4K)

#define MIN_CIA_SCORE 50//This is the minimum score required to become a CIA agent.
#define MIN_ARMY_SCORE 100//This is the minimum score required to become an Army Soldier.

#define MIN_SCORE_CREATE_CLAN 250//This is the minimum amount of score a player needs to be able to create a clan. (Default: 250 Score)
#define MIN_SCORE_TORCH_VEHICLES 250//This is the minimum amount of score a player needs to be able to torch vehicles. (Default: 250 Score)

#define MAX_STOCK 500//This is the max amount of stock the business owner can hold at any given time. (Default: 500 Stock)
#define STOCK_PRICE 25//This is the amount each stock will cost when ordering stock via the business menu. (Default: $25/Stock)

#define INCOME_TAX_PERCENT 10//This is the percentage of income tax the player will pay. (Default: 10%)
#define WEALTH_TAX_PERCENT 5//This is the percentage of wealth tax the player will pay. (Default: 5%)

#define SPRUNK_PRICE 1//This is the price for each sprunk purchased while using the vending machine system. (Default: $1)
#define SPRUNK_HEALTH 10.0//This is the health each sprunk with give when using the vending machine system. (Default: 10.0)
#define SPRUNK_KEY KEY_SECONDARY_ATTACK//This is the key used for interacting with the vending machine system. (Default: Enter)

#define BASE_BUS_FAIR 1//Increase this number slightly to increase the total bus fare amount. (Default: $1)
#define BUS_ZONE_DIST 100.0//This is how large each zone is for each bus route. (Default: 100 Metres)

#define BASE_PLANE_FAIR 100//Increase this number slightly to increase the total plane fare amount. (Default: $100)
#define PLANE_ZONE_DIST 500.0//This is how large each zone is for each plane route. (Default: 500 Metres)

#define PLAYER_STARTING_MONEY 50000//This is how much money each player will start with after registering. (Default: $50k)

#define LAND_VALUE_PERCENT 6//This is the percentage the house value will grow when a house sells nearby. (Default: 6%)
#define COMMERCIAL_VALUE_PERCENT 3//This is the percentage the business value will grow when a business sells nearby. (Default: 3%)

#define BUSINESS_VALUE_PERCENT 6//This is the percentage the business value will grow when a business sells nearby. (Default: 6%)
#define BUSINESS_PROFIT_PERCENT 3//The business value will grow by this percent each time the business sells an item. (Default: 3%)

#define REGISTER_DIALOG 0//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LOGIN_DIALOG 1//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CMDS_DIALOG 2//Change this dialog id if it clashes with other dialog ids in other scripts.
#define STATS_DIALOG 3//Change this dialog id if it clashes with other dialog ids in other scripts.
#define POLICE_DIALOG 4//Change this dialog id if it clashes with other dialog ids in other scripts.
#define FIRE_STATION_DIALOG 5//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GARAGE_DIALOG 6//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GENERAL_DIALOG 7//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAT_DIALOG 8//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ANIMATION_DIALOG 9//Change this dialog id if it clashes with other dialog ids in other scripts.
#define JOB_DIALOG 10//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CELL_DIALOG 11//Change this dialog id if it clashes with other dialog ids in other scripts.
#define AMMU_DIALOG 12//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MELEE_DIALOG 13//Change this dialog id if it clashes with other dialog ids in other scripts.
#define HANDGUN_DIALOG 14//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SHOTGUN_DIALOG 15//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SMG_DIALOG 16//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ASSAULT_DIALOG 17//Change this dialog id if it clashes with other dialog ids in other scripts.
#define RIFLE_DIALOG 18//Change this dialog id if it clashes with other dialog ids in other scripts.
#define THROWABLES_DIALOG 19//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CONSUMABLES_DIALOG 20//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_BUS_DIALOG 21//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_BUS_DIALOG 22//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_BUS_DIALOG 23//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LSPD_FIRE_DIALOG 24//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SFPD_FIRE_DIALOG 25//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LVPD_FIRE_DIALOG 26//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PILOT_DESK_DIALOG 27//Change this dialog id if it clashes with other dialog ids in other scripts.
#define HOSPITAL_DIALOG 28//Change this dialog id if it clashes with other dialog ids in other scripts.
#define HEAL_DIALOG 29//Change this dialog id if it clashes with other dialog ids in other scripts.
#define AIRPORT_DIALOG 30//Change this dialog id if it clashes with other dialog ids in other scripts.
#define INVENTORY_DIALOG 31//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ACTION_DIALOG 32//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CALIGULAS_SAFE_DIALOG 33//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DRAGONS_SAFE_DIALOG 34//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CIA_DIALOG 35//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ARMY_DIALOG 36//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEPOT_DESK_DIALOG 37//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BANK_DIALOG 38//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BALANCE_DIALOG 39//Change this dialog id if it clashes with other dialog ids in other scripts.
#define WITHDRAW_DIALOG 40//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEPOSIT_DIALOG 41//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEBT_DIALOG 42//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LOANS_DIALOG 43//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PAYOFF_DIALOG 44//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TRANSFER_DIALOG 45//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SEND_DIALOG 46//Change this dialog id if it clashes with other dialog ids in other scripts.
#define STATEMENT_DIALOG 47//Change this dialog id if it clashes with other dialog ids in other scripts.
#define UNIVERSITY_DIALOG 48//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ENFORCEMENT_DIALOG 49//Change this dialog id if it clashes with other dialog ids in other scripts.
#define INTELLIGENCE_DIALOG 50//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEFENSE_DIALOG 51//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MEDICAL_DIALOG 52//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUY_DIALOG 53//Change this dialog id if it clashes with other dialog ids in other scripts.
#define VERIFY_DIALOG 54//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ACCESS_DIALOG 55//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MENU_DIALOG 56//Change this dialog id if it clashes with other dialog ids in other scripts.
#define VALUE_DIALOG 57//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PASS_DIALOG 58//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SAFE_DIALOG 59//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SAFE_BALANCE_DIALOG 60//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SAFE_WITHDRAW_DIALOG 61//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SAFE_DEPOSIT_DIALOG 62//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SELL_DIALOG 63//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MECHANICAL_DIALOG 64//Change this dialog id if it clashes with other dialog ids in other scripts.
#define STORE_DIALOG 65//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LOTTO_DIALOG 66//Change this dialog id if it clashes with other dialog ids in other scripts.
#define COLOURS_DIALOG 67//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_MOTORS_DIALOG 68//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_LIST_DIALOG 69//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_USED_DIALOG 70//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_NEW_DIALOG 71//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_SPECIAL_DIALOG 72//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LS_VERIFY_DIALOG 73//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_MOTORS_DIALOG 74//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_LIST_DIALOG 75//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_USED_DIALOG 76//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_NEW_DIALOG 77//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_SPECIAL_DIALOG 78//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SF_VERIFY_DIALOG 79//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_MOTORS_DIALOG 80//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_LIST_DIALOG 81//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_USED_DIALOG 82//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_NEW_DIALOG 83//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_SPECIAL_DIALOG 84//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LV_VERIFY_DIALOG 85//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BAR_DIALOG 86//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PROPERTY_DIALOG 87//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CLAN_DIALOG 88//Change this dialog id if it clashes with other dialog ids in other scripts.
#define RESCUE_DIALOG 89//Change this dialog id if it clashes with other dialog ids in other scripts.
#define FIRES_DIALOG 90//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEALER_ASK_DIALOG 91//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEALER_AMOUNT_DIALOG 92//Change this dialog id if it clashes with other dialog ids in other scripts.
#define FUEL_STATION_DIALOG 93//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUY_NEONS_DIALOG 94//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SELLGUN_DIALOG 95//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SELLTO_DIALOG 96//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SELLFOR_DIALOG 97//Change this dialog id if it clashes with other dialog ids in other scripts.
#define SELLVERIFY_DIALOG 98//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TRAP_MAIN_DIALOG 99//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TRAP_SELL_DIALOG 100//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TRAP_BUY_DIALOG 101//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DEGREES_DIALOG 102//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LICENCES_DIALOG 103//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GUN_DIALOG 104//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CAR_DIALOG 105//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TRUCK_DIALOG 106//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MOTORCYCLE_DIALOG 107//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BOAT_DIALOG 108//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PILOT_DIALOG 109//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GYM_DIALOG 110//Change this dialog id if it clashes with other dialog ids in other scripts.
#define VEHICLE_DIALOG 111//Change this dialog id if it clashes with other dialog ids in other scripts.
#define MINING_DIALOG 112//Change this dialog id if it clashes with other dialog ids in other scripts.
#define QUARRY_OFFICE_DIALOG 113//Change this dialog id if it clashes with other dialog ids in other scripts.
#define QUARRY_UNLOAD_DIALOG 114//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ATM_DIALOG 115//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ATM_BAL_DIALOG 116//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ATM_WIT_DIALOG 117//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ATM_DEP_DIALOG 118//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ATM_STA_DIALOG 119//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAR_MAIN_DIALOG 120//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAR_CREATE_DIALOG 121//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAR_LOAD_DIALOG 122//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAR_DELETE_DIALOG 123//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHAR_VERIFY_DIALOG 124//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_SHOW_HOMEPAGE_DIALOG 125//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_SHOW_CONTACTS_DIALOG 126//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_SHOW_MESSAGES_DIALOG 127//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_LIST_CONTACTS_DIALOG 128//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_ADD_CONTACTS_DIALOG 129//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_DELETE_CONTACTS_DIALOG 130//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_VERIFY_ADD_DIALOG 131//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_VERIFY_DELETE_DIALOG 132//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_LIST_MESSAGES_DIALOG 133//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_SEND_MESSAGES_DIALOG 134//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_WRITE_MESSAGES_DIALOG 135//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_INBOX_MESSAGES_DIALOG 136//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_OUTBOX_MESSAGES_DIALOG 137//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_INBOX_READ_DIALOG 138//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_INBOX_DELETE_DIALOG 139//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_OUTBOX_READ_DIALOG 140//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PHONE_OUTBOX_DELETE_DIALOG 141//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_MAIN_DIALOG 142//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_ITEM_DIALOG 143//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_WEAPON_DIALOG 144//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_MENU_DIALOG 145//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_VALUE_DIALOG 146//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_PROFIT_DIALOG 147//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_STOCK_DIALOG 148//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_ORDER_DIALOG 149//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_SELL_DIALOG 150//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_NAME_DIALOG 151//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUSINESS_VERIFY_DIALOG 152//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CLAN_CREATE_DIALOG 153//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CLAN_MEMBERS_DIALOG 154//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CLUB_DIALOG 155//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BURGER_DIALOG 156//Change this dialog id if it clashes with other dialog ids in other scripts.
#define PIZZA_DIALOG 157//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CLUCK_DIALOG 158//Change this dialog id if it clashes with other dialog ids in other scripts.
#define ADMIN_DIALOG 159//Change this dialog id if it clashes with other dialog ids in other scripts.
#define RULES_DIALOG 160//Change this dialog id if it clashes with other dialog ids in other scripts.
#define CHANGEPASS_DIALOG 161//Change this dialog id if it clashes with other dialog ids in other scripts.
#define LIST_DIALOG 162//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GIVE_ITEM_DIALOG 163//Change this dialog id if it clashes with other dialog ids in other scripts.
#define GIVE_AMOUNT_DIALOG 164//Change this dialog id if it clashes with other dialog ids in other scripts.
#define VIP_DIALOG 165//Change this dialog id if it clashes with other dialog ids in other scripts.
#define DROP_AMOUNT_DIALOG 166//Change this dialog id if it clashes with other dialog ids in other scripts.
#define BUILDER_DIALOG 167//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TELE_MAIN_DIALOG 168//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TELE_LS_DIALOG 169//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TELE_SF_DIALOG 170//Change this dialog id if it clashes with other dialog ids in other scripts.
#define TELE_LV_DIALOG 171//Change this dialog id if it clashes with other dialog ids in other scripts.

//DO NOT EDIT BELOW THIS LINE!

#define MAX_HEALTH (Float:0x7F800000)

#define PLAYER 0
#define HELPER 1
#define ADMIN 2
#define HEAD 3
#define MANAGER 4
#define OWNER 5

#define CIVILIAN_JOB 0
#define POLICE_JOB 1
#define CIA_JOB 2
#define ARMY_JOB 3
#define EMS_JOB 4
#define FIRE_JOB 5
#define MINER_JOB 6
#define PILOT_JOB 7
#define TRUCKER_JOB 8

#define CLAN_MEMBER 0
#define CLAN_CAPTAIN 1
#define CLAN_COMMANDER 2
#define CLAN_COLEADER 3
#define CLAN_LEADER 4

#define NO_CITY 0
#define LOS_SANTOS 1
#define SAN_FIERRO 2
#define LAS_VENTURAS 3

#define DESERT_AIRPORT 4

#define CALIGULAS_CASINO 1
#define FOUR_DRAGONS_CASINO 2

#define LSPD_GATE 0
#define SFPD_GATE 1
#define LVPD1_GATE 2
#define LVPD2_GATE 3

#define NO_NEONS 0
#define BLUE_NEONS 18648
#define RED_NEONS 18647
#define GREEN_NEONS 18649
#define YELLOW_NEONS 18650
#define PINK_NEONS 18651

#define FIRE_OBJECT 18691
#define SMOKE_OBJECT 18715

#define SPRUNK_MODEL 1546
#define ALCOHOL_MODEL 19823
#define BURGER_MODEL 19811
#define TACO_MODEL 2769
#define PIZZA_MODEL 2814
#define MEDIKIT_MODEL 11738
#define TOOLBOX_MODEL 19921
#define MATERIALS_MODEL 3013
#define JERRYCAN_MODEL 1650
#define CROWBAR_MODEL 18634
#define TICKET_MODEL 19792
#define SEEDS_MODEL 2709
#define WEED_MODEL 1575
#define PHONE_MODEL 2967

#define ORE_TYPE_STONE 0
#define ORE_TYPE_GOLD 1
#define ORE_TYPE_DIAMOND 2

#define DEGREE_ENFORCEMENT 0
#define DEGREE_INTELLIGENCE 1
#define DEGREE_DEFENSE 2
#define DEGREE_MEDICAL 3
#define DEGREE_RESCUE 4
#define DEGREE_MECHANICAL 5
#define DEGREE_MINING 6

#define LICENCE_GUN 0
#define LICENCE_CAR 1
#define LICENCE_TRUCK 2
#define LICENCE_MOTORCYCLE 3
#define LICENCE_BOAT 4
#define LICENCE_PILOT 5

#define CLAN_TYPE_NAME 0
#define CLAN_TYPE_TAG 1

#define STATS_TYPE_KILLS 0
#define STATS_TYPE_DEATHS 1
#define STATS_TYPE_ARRESTS 2
#define STATS_TYPE_TICKETS 3
#define STATS_TYPE_TAKEDOWNS 4
#define STATS_TYPE_JAILED 5
#define STATS_TYPE_ROBBERIES 6
#define STATS_TYPE_SAFES 7
#define STATS_TYPE_PATIENTS 8
#define STATS_TYPE_FIRES 9
#define STATS_TYPE_FLIGHTS 10
#define STATS_TYPE_HAULS 11
#define STATS_TYPE_FINES 12

#define REQUEST_TYPE_CIV 0
#define REQUEST_TYPE_COP 1
#define REQUEST_TYPE_CIA 2
#define REQUEST_TYPE_ARMY 3
#define REQUEST_TYPE_EMS 4
#define REQUEST_TYPE_FIRE 5
#define REQUEST_TYPE_MINER 6
#define REQUEST_TYPE_PILOT 7
#define REQUEST_TYPE_TRUCKER 8

#define TIMER_TYPE_GLOBAL 0
#define TIMER_TYPE_RADIO 1
#define TIMER_TYPE_HELP 2
#define TIMER_TYPE_REPORT 3
#define TIMER_TYPE_ESCAPE 4
#define TIMER_TYPE_BREAKOUT 5
#define TIMER_TYPE_ANIM 6
#define TIMER_TYPE_HEAL 7

#define MOVE_SPEED 100.0
#define ACCELERATION_RATE 0.03

#define MOVE_FORWARD 1
#define MOVE_BACK 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define MOVE_FORWARD_LEFT 5
#define MOVE_FORWARD_RIGHT 6
#define MOVE_BACK_LEFT 7
#define MOVE_BACK_RIGHT 8

#define CAMERA_MODE_NONE 0
#define CAMERA_MODE_FLY 1

#define OFFSET_X (FV[0]*6000.0)
#define OFFSET_Y (FV[1]*6000.0)
#define OFFSET_Z (FV[2]*6000.0)
