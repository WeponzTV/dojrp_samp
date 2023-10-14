#include <YSI_Coding\y_hooks>

enum timer_data
{
	timer_global,
	timer_radio,
	timer_help,
	timer_report,
	timer_escape,
	timer_breakout,
	timer_animation,
	timer_heal
};
new TimerData[MAX_PLAYERS][timer_data];

stock GetTimerStatus(playerid, type)
{
	if(type == TIMER_TYPE_GLOBAL) return TimerData[playerid][timer_global];
	else if(type == TIMER_TYPE_RADIO) return TimerData[playerid][timer_radio];
	else if(type == TIMER_TYPE_HELP) return TimerData[playerid][timer_help];
	else if(type == TIMER_TYPE_REPORT) return TimerData[playerid][timer_report];
	else if(type == TIMER_TYPE_ESCAPE) return TimerData[playerid][timer_escape];
	else if(type == TIMER_TYPE_BREAKOUT) return TimerData[playerid][timer_breakout];
	else if(type == TIMER_TYPE_ANIM) return TimerData[playerid][timer_animation];
	else if(type == TIMER_TYPE_HEAL) return TimerData[playerid][timer_heal];
	return 1;
}

stock SetTimerStatus(playerid, type, status)
{
	if(type == TIMER_TYPE_GLOBAL) return TimerData[playerid][timer_global] = status;
	else if(type == TIMER_TYPE_RADIO) return TimerData[playerid][timer_radio] = status;
	else if(type == TIMER_TYPE_HELP) return TimerData[playerid][timer_help] = status;
	else if(type == TIMER_TYPE_REPORT) return TimerData[playerid][timer_report] = status;
	else if(type == TIMER_TYPE_ESCAPE) return TimerData[playerid][timer_escape] = status;
	else if(type == TIMER_TYPE_BREAKOUT) return TimerData[playerid][timer_breakout] = status;
	else if(type == TIMER_TYPE_ANIM) return TimerData[playerid][timer_animation] = status;
	else if(type == TIMER_TYPE_HEAL) return TimerData[playerid][timer_heal] = status;
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
    	TimerData[playerid][timer_global] = 0;
		TimerData[playerid][timer_radio] = 0;
		TimerData[playerid][timer_help] = 0;
		TimerData[playerid][timer_report] = 0;
		TimerData[playerid][timer_escape] = 0;
		TimerData[playerid][timer_breakout] = 0;
		TimerData[playerid][timer_animation] = 0;
		TimerData[playerid][timer_heal] = 0;
	}
	return 1;
}
