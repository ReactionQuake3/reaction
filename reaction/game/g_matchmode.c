#include "g_local.h"

/* Slicer - This will work on all MatchMode Aspects..
timers, votes, etc etc. Called on each Frame*/
void MM_RunFrame(void) {
	int fps;
	
	fps = trap_Cvar_VariableIntegerValue( "sv_fps" );

	switch(g_gametype.integer) {
	//Each Type has different ways of dealing things..
	case(GT_TEAMPLAY):
		if(level.team_game_going) // This will need changes..
			level.matchTime += 1/fps;
		break;

	}

}