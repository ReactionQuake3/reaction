#include "g_local.h"

/* Slicer - This will work on all MatchMode Aspects..
timers, votes, etc etc. Called on each Frame*/
qboolean checkCaptain(team_t team) {
	gentity_t *ent;
	int i;
	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if(ent->client->sess.sessionTeam == team && ent->client->pers.captain == team)
			return qtrue;	
	}
	return qfalse;
}
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
void MM_Captain_f( gentity_t *ent ) {
	
	if(ent->client->sess.sessionTeam == TEAM_FREE) {
		trap_SendServerCommand(ent-g_entities, "print \"You need to be on a team for that\n\"");
		return;
	}

	if(ent->client->pers.captain != TEAM_FREE) {

		if(ent->client->sess.sessionTeam == TEAM_RED) {
			level.team1ready = qfalse;
			trap_SendServerCommand( -1, va("print \"%s is no longer %s's Captain!\n\"",
				ent->client->pers.netname,"Red Team"));// Teams will have names in the future..
		}
		else {
			level.team2ready = qfalse;
			trap_SendServerCommand( -1, va("print \"%s is no longer %s's Captain!\n\"",
				ent->client->pers.netname,"Blue Team"));// Teams will have names in the future..
		}
		ent->client->pers.captain = TEAM_FREE;
	}

	if(checkCaptain(ent->client->sess.sessionTeam)) {
		trap_SendServerCommand(ent-g_entities, va("print \"Your team already has a Captain\n\""));
		return;
	}


}