#include <YSI_Coding\y_hooks>

new DB:server_database;
new DBResult:database_result;

stock OpenDatabase()
{
	if((server_database = db_open(DATABASE_LOCATION)) == DB:0)
	{
		printf("[%s] Failed to connect to SQLite database: scriptfiles/DOJRP/server.db", SERVER_TAG);
		return SendRconCommand("exit");
	}
	else
	{
		printf("[%s] Successfully connected to SQLite database: scriptfiles/DOJRP/server.db", SERVER_TAG);
		CreateTables();
	}
	return 1;
}

stock CloseDatabase()
{
    db_close(server_database);
    return 1;
}

stock CreateTables()
{
	//Player
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `ACCOUNTS` (`MASTER_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `JOIN_NAME`, `PASS`, `IP`, `REGISTERED`, `LOGINS`, `LEVEL`, `VIP`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `CHARACTERS` (`CHARACTER_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `MASTER_ID`, `CHARACTER_NAME`, `SKIN`, `SCORE`, `MONEY`, `JOB`, `WANTED`, `TIME`, `DEPT`, `STYLE`, `HUNGER`, `THIRST`, `HEALTH`, `ARMOUR`, `X`, `Y`, `Z`, `A`, `INT`, `WORLD`, `MUTE`, `ROB`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `WEAPONS` (`CHARACTER_ID` INTEGER PRIMARY KEY, `W1`, `W1A`, `W2`, `W2A`, `W3`, `W3A`, `W4`, `W4A`, `W5`, `W5A`, `W6`, `W6A`, `W7`, `W7A`, `W8`, `W8A`, `W9`, `W9A`, `W10`, `W10A`, `W11`, `W11A`, `W12`, `W12A`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `INVENTORY` (`CHARACTER_ID` INTEGER PRIMARY KEY, `S1`, `S1A`, `S2`, `S2A`, `S3`, `S3A`, `S4`, `S4A`, `S5`, `S5A`, `S6`, `S6A`, `S7`, `S7A`, `S8`, `S8A`, `S9`, `S9A`, `S10`, `S10A`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `STATS` (`CHARACTER_ID` INTEGER PRIMARY KEY, `KILLS`, `DEATHS`, `ARRESTS`, `TICKETS`, `TAKEDOWNS`, `JAILED`, `ROBBERIES`, `SAFES`, `PATIENTS`, `FIRES`, `FLIGHTS`, `HAULS`, `FINES`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `DEGREES` (`CHARACTER_ID` INTEGER PRIMARY KEY, `ENFORCE`, `INTEL`, `DEFENSE`, `MEDICAL`, `RESCUE`, `MINING`, `MECHANIC`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `LICENCES` (`CHARACTER_ID` INTEGER PRIMARY KEY, `GUN`, `CAR`, `TRUCK`, `MOTORCYCLE`, `BOAT`, `PILOT`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `LOTTO` (`CHARACTER_ID` INTEGER PRIMARY KEY, `NUMBER1`, `NUMBER2`, `NUMBER3`, `NUMBER4`, `NUMBER5`, `NUMBER6`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `MINERALS` (`CHARACTER_ID` INTEGER PRIMARY KEY, `STONE`, `GOLD`, `DIAMONDS`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `MEMBERS` (`CHARACTER_ID` INTEGER PRIMARY KEY, `TAG`, `RANK`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `BANK` (`CHARACTER_ID` INTEGER PRIMARY KEY, `BALANCE`, `DEBT`, `TRANSACTIONS`, `WITHDRAWN`, `DEPOSITED`, `TRANSFERRED`, `RECEIVED`, `LOANED`, `REPAID`)");

	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `BANS` (`MASTER_ID` INTEGER PRIMARY KEY, `REASON`, `ADMIN`, `DAYS`, `TIMESTAMP`)");

	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `PHONES` (`USER_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `OWNER`, `NUMBER`, `OWNED`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `CONTACTS` (`CONTACT_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `USER_ID`, `OWNER_ID`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `INBOX` (`INBOX_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `USER_ID`, `RECEIVER_ID`, `READ`, `SUBJECT`, `MESSAGE`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `OUTBOX` (`OUTBOX_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `USER_ID`, `SENDER_ID`, `READ`, `SUBJECT`, `MESSAGE`)");

	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `VEHICLES` (`VEHICLE_ID` INTEGER PRIMARY KEY AUTOINCREMENT, `CHARACTER_ID`, `MODEL`, `COL1`, `COL2`, `PRICE`, `X`, `Y`, `Z`, `A`, `HEALTH`, `PLATE`, `PAINT`, `LOCK`, `FUEL`, `NEONS`, `ENGINE`, `LIGHTS`, `ALARM`, `BONNET`, `BOOT`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `MODS` (`VEHICLE_ID` INTEGER PRIMARY KEY, `M1`, `M2`, `M3`, `M4`, `M5`, `M6`, `M7`, `M8`, `M9`, `M10`, `M11`, `M12`, `M13`, `M14`, `M15`, `M16`, `M17`)");

	new query[300];
	for(new i = 0; i < 10; i++)
	{
		format(query, sizeof(query), "CREATE TABLE IF NOT EXISTS `PLANT%i` (`CHARACTER_ID` INTEGER PRIMARY KEY, `X`, `Y`, `Z`, `STAGE`, `AGE`)", (i + 1));
		db_query@(server_database, query);
	}

	//Server
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `HOUSES` (`HOUSE_ID` INTEGER PRIMARY KEY, `CHARACTER_ID`, `PASS`, `CITY`, `VALUE`, `SAFE`, `EXTX`, `EXTY`, `EXTZ`, `INTX`, `INTY`, `INTZ`, `ENTERX`, `ENTERY`, `ENTERZ`, `ENTERA`, `EXITX`, `EXITY`, `EXITZ`, `EXITA`, `EXTINTERIOR`, `EXTWORLD`, `INTINTERIOR`, `INTWORLD`)");
	db_query@(server_database, "CREATE TABLE IF NOT EXISTS `BUSINESSES` (`BUSINESS_ID` INTEGER PRIMARY KEY, `CHARACTER_ID`, `NAME`, `CITY`, `VALUE`, `STOCK`, `PROFIT`, `EXTX`, `EXTY`, `EXTZ`, `INTX`, `INTY`, `INTZ`, `ENTERX`, `ENTERY`, `ENTERZ`, `ENTERA`, `EXITX`, `EXITY`, `EXITZ`, `EXITA`, `INTINTERIOR`, `INTWORLD`)");
	
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `LSBUS` (`STOP_ID` INTEGER PRIMARY KEY, `NAME`, `X`, `Y`, `Z`, `R`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `SFBUS` (`STOP_ID` INTEGER PRIMARY KEY, `NAME`, `X`, `Y`, `Z`, `R`)");
    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `LVBUS` (`STOP_ID` INTEGER PRIMARY KEY, `NAME`, `X`, `Y`, `Z`, `R`)");

    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `SPRUNKS` (`ID` INTEGER PRIMARY KEY, `X`, `Y`, `Z`, `R`, `INTERIOR`, `WORLD`)");

    db_query@(server_database, "CREATE TABLE IF NOT EXISTS `CLANS` (`TAG` TEXT PRIMARY KEY, `NAME`)");
	return 1;
}
