#include "g_local.h"
// JBravo: for warnings
int ClientNumberFromString(gentity_t * to, char *s);

int refVotes[2];		// refVotes[0] is the clientnumber red team voted 

				//      refVotes[1] is the clientnumber blue team voted 

void SendEndMessage()
{

	int mins, secs;

	mins = (int) floor(level.matchTime / 60.0f);
	secs = level.matchTime - (mins * 60);

	trap_SendServerCommand(-1, "cp \"Match is Over!\n\"");
	trap_SendServerCommand(-1,
			       va("print \"Scores: Team1 [%d]  -  Team2 [%d]  \n\"", level.teamScores[TEAM_RED],
				  level.teamScores[TEAM_BLUE]));
	trap_SendServerCommand(-1, va("print \"Total Match Time: %d:%02d \n\"", mins, secs));
}
gentity_t *getEntByName(char *name)
{
	gentity_t *ent;
	int i;

	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if (!Q_stricmp(ent->client->pers.netname, name))
			return ent;
	}
	return NULL;
}

qboolean checkCaptain(team_t team)
{
	gentity_t *ent;
	int i;

	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if (ent->client->sess.savedTeam == team && ent->client->sess.captain == team)
			return qtrue;
	}
	return qfalse;
}

void MM_RunFrame(void)
{
	int fps;

	fps = trap_Cvar_VariableIntegerValue("sv_fps");

	switch (g_gametype.integer) {
		//Each Type has different ways of dealing things..
	case (GT_TEAMPLAY):
		if (level.team_game_going && level.inGame)
			level.matchTime += 1.0f / (float) fps;
		break;
	}
}

void MM_Sub_f(gentity_t * ent)
{
	if (!g_RQ3_matchmode.integer)
		return;
	if (ent->client->sess.savedTeam == TEAM_SPECTATOR || ent->client->sess.savedTeam == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, "print \"You need to be on a team for that\n\"");
		return;
	}
	if (ent->client->sess.sub == TEAM_FREE) {
//                      if (ent->client->ps.pm_type == PM_NORMAL) {
		if (ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
			ent->flags &= ~FL_GODMODE;
			ent->client->ps.stats[STAT_HEALTH] = ent->health = 0;
			player_die(ent, ent, ent, 100000, MOD_SUICIDE);
		}
		ent->client->sess.sub = ent->client->sess.savedTeam;
		trap_SendServerCommand(-1, va("print \"%s^7 is now a Substitute for %s.\n\"",
					      ent->client->pers.netname,
					      ent->client->sess.savedTeam ==
					      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
	} else {
		ent->client->sess.sub = TEAM_FREE;
		trap_SendServerCommand(-1, va("print \"%s^7 is no longer a Substitute for %s.\n\"",
					      ent->client->pers.netname,
					      ent->client->sess.savedTeam ==
					      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
	}
}

void MM_Captain_f(gentity_t * ent)
{
	if (!g_RQ3_matchmode.integer)
		return;
	if (ent->client->sess.savedTeam == TEAM_SPECTATOR || ent->client->sess.savedTeam == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, "print \"You need to be on a team for that\n\"");
		return;
	}
	if (ent->client->sess.captain == TEAM_RED) {
		level.team1ready = qfalse;
		trap_SendServerCommand(-1, va("print \"%s^7 is no longer %s's Captain.\n\"",
					      ent->client->pers.netname, g_RQ3_team1name.string));
		ent->client->sess.captain = TEAM_FREE;
	} else if (ent->client->sess.captain == TEAM_BLUE) {
		level.team2ready = qfalse;
		trap_SendServerCommand(-1, va("print \"%s^7 is no longer %s's Captain.\n\"",
					      ent->client->pers.netname, g_RQ3_team2name.string));
		ent->client->sess.captain = TEAM_FREE;
	} else {
		if (!checkCaptain(ent->client->sess.savedTeam)) {
			ent->client->sess.captain = ent->client->sess.savedTeam;
			trap_SendServerCommand(-1, va("print \"%s^7 is now %s's Captain.\n\"",
						      ent->client->pers.netname,
						      ent->client->sess.savedTeam ==
						      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
		} else
			trap_SendServerCommand(ent - g_entities, "print \"Your team already has a Captain\n\"");
	}
}

void MM_Ready_f(gentity_t * ent)
{
	if (!g_RQ3_matchmode.integer)
		return;

	if (ent->client->sess.captain != TEAM_FREE) {
		if (ent->client->sess.savedTeam == TEAM_RED) {
			trap_SendServerCommand(-1, va("cp \"%s is%s Ready.\n\"",
						      g_RQ3_team1name.string, level.team1ready ? " no longer" : ""));

			if (level.team1ready)
				level.team1ready = qfalse;
			else
				level.team1ready = qtrue;
		} else {
			trap_SendServerCommand(-1, va("cp \"%s is%s Ready.\n\"",
						      g_RQ3_team2name.string, level.team2ready ? " no longer" : ""));

			if (level.team2ready)
				level.team2ready = qfalse;
			else
				level.team2ready = qtrue;
		}
	} else
		trap_SendServerCommand(ent - g_entities, "print \"You need to be a captain for that\n\"");
}

void MM_TeamModel_f(gentity_t * ent)
{
	int args;
	team_t team;
	char buff[MAX_TOKEN_CHARS];

	team = ent->client->sess.savedTeam;
	if (!g_RQ3_matchmode.integer)
		return;
	if (team == TEAM_SPECTATOR) {
		return;
	}

	args = trap_Argc();

	if (args < 2) {
		trap_SendServerCommand(ent - g_entities, va("print \"Your current team model is: %s\n\"",
							    ent->client->sess.savedTeam ==
							    TEAM_RED ? g_RQ3_team1model.string : g_RQ3_team2model.
							    string));
		return;
	} else {
		if (ent->client->sess.captain == TEAM_FREE) {
			trap_SendServerCommand(ent - g_entities, "print \"You need to be a captain for that\n\"");
			return;
		}

		if (level.team_game_going || level.team_round_going) {
			trap_SendServerCommand(ent - g_entities,
					       "print \"You cannot change your team's model while playing or ready.\n\"");
		}

		trap_Argv(1, buff, sizeof(buff));

		if (team == TEAM_RED) {
			if (level.team1ready) {
				trap_SendServerCommand(ent - g_entities,
						       "print \"You need to un-ready your team for that..\n\"");
				return;
			}
			trap_Cvar_Set("g_RQ3_team1model", buff);
			trap_SendServerCommand(-1, va("print \"New Team 1 Model: %s\n\"", buff));
		} else {
			if (level.team2ready) {
				trap_SendServerCommand(ent - g_entities,
						       "print \"You need to un-ready your team for that..\n\"");
				return;
			}
			trap_Cvar_Set("g_RQ3_team2model", buff);
			trap_SendServerCommand(-1, va("print \"New Team 2 Model: %s\n\"", buff));
		}
	}
}

void MM_TeamName_f(gentity_t * ent)
{
	int args;
	team_t team;
	char *buff;

	team = ent->client->sess.savedTeam;
	if (!g_RQ3_matchmode.integer)
		return;
	if (team == TEAM_SPECTATOR) {
		return;
	}

	args = trap_Argc();

	if (args < 2) {
		trap_SendServerCommand(ent - g_entities, va("print \"Your Team Name: %s\n\"",
							    ent->client->sess.savedTeam ==
							    TEAM_RED ? g_RQ3_team1name.string : g_RQ3_team2name.
							    string));
		return;
	} else {
		if (ent->client->sess.captain == TEAM_FREE) {
			trap_SendServerCommand(ent - g_entities, "print \"You need to be a captain for that\n\"");
			return;
		}

		if (level.team_game_going || level.team_round_going) {
			trap_SendServerCommand(ent - g_entities,
					       "print \"You cannot change your team's name while playing or ready.\n\"");
		}

		buff = ConcatArgs(1);

		if (strlen(buff) > TEAM_NAME_SIZE)
			buff[TEAM_NAME_SIZE] = 0;

		if (team == TEAM_RED) {
			if (level.team1ready) {
				trap_SendServerCommand(ent - g_entities,
						       "print \"You need to un-ready your team for that..\n\"");
				return;
			}
			trap_Cvar_Set("g_RQ3_team1name", buff);
			trap_SendServerCommand(-1, va("print \"New Team 1 Name: %s\n\"", buff));
		} else {
			if (level.team2ready) {
				trap_SendServerCommand(ent - g_entities,
						       "print \"You need to un-ready your team for that..\n\"");
				return;
			}
			trap_Cvar_Set("g_RQ3_team2name", buff);
			trap_SendServerCommand(-1, va("print \"New Team 2 Name: %s\n\"", buff));
		}
	}
}

//
//      aasimon: Referee Functions Definition, with some aid functions first
//

void checkRefVotes()
{
	gentity_t *ent;
	char nr[4];

	G_Printf("Vote Red: %i Vote Blue %i \n", refVotes[0], refVotes[1]);
	if (refVotes[0] == refVotes[1]) {
		ent = g_entities + refVotes[0];
		Com_sprintf(nr, sizeof(nr), "%i", refVotes[0]);
		trap_Cvar_Set("g_RQ3_RefID", nr);
		trap_SendServerCommand(-1, va("cp \"%s^7 is the new Referee.\n\"", ent->client->pers.netname));
		refVotes[0] = refVotes[1] = -1;
	}
}

/* Slicer - MM_Referee_f
For captains to vote a referee*/
void MM_Referee_f(gentity_t * ent)
{
	gentity_t *ref;
	char *buff;
	team_t captain;

	if (!g_RQ3_matchmode.integer)
		return;

	captain = ent->client->sess.captain;

	if (!g_RQ3_AllowRef.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"No Referee Allowed on this server\n\"");
		return;
	}
	if (trap_Argc() < 2) {
		if (Ref_Exists()) {
			ref = g_entities + g_RQ3_RefID.integer;
			trap_SendServerCommand(ent - g_entities,
					       va("print \"Current Referee: %s\n\"", ref->client->pers.netname));
		} else
			trap_SendServerCommand(ent - g_entities,
					       "print \"No Referee currently assigned, use referee <name> to assign\n\"");
		return;
	}

	if (captain != TEAM_FREE) {
		buff = ConcatArgs(1);
		if ((ref = getEntByName(buff)) != NULL) {
			refVotes[captain - 1] = ref - g_entities;
			trap_SendServerCommand(-1,
					       va("print \"%s^7 has voted %s^7 for referee\n\"",
						  ent->client->pers.netname, ref->client->pers.netname));
			checkRefVotes();
		} else {
			trap_SendServerCommand(ent - g_entities, "print \"Invalid Player Name\n\"");
			return;
		}
	} else
		trap_SendServerCommand(ent - g_entities, "print \"You need to be a captain to assign a referee\n\"");

}
void MM_ClearScores(void)
{
	gentity_t *ent;
	int i;

	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;

		// aasimon: Clear only PERS info. Lata clear all REC information. See if more info is needed to be clean
		ent->client->ps.persistant[PERS_SCORE] = 0;
		ent->client->ps.persistant[PERS_KILLED] = 0;
		ent->client->ps.persistant[PERS_DAMAGE_DELT] = 0;
	}
	if (g_gametype.integer == GT_TEAMPLAY) {
		level.teamScores[TEAM_RED] = 0;
		level.teamScores[TEAM_BLUE] = 0;
	}
}

// aasimon: checks for a ref
qboolean Ref_Exists(void)
{

	if (g_RQ3_RefID.integer == -1)
		return qfalse;
	else
		return qtrue;
}

//
//      aasimon: Ref Auth. Do some kind of logging (ip's etc)
//
qboolean Ref_Auth(gentity_t * ent)
{
	char pass[MAX_TOKEN_CHARS];
	int cn;
	char teste[2];

	if (!g_RQ3_AllowRef.integer) {
		// No ref allowed on the server - HELLO!!!!! FIREMAN CARS????
		trap_SendServerCommand(ent - g_entities, "print \"No Referee Allowed on this server\n\"");
		return qfalse;
	}

	if (Q_stricmp(g_RQ3_RefPass.string, "") == 0) {
		trap_SendServerCommand(ent - g_entities, "print \"No Referee Password Set on this server\n\"");
		return qfalse;
	}

	if (Ref_Exists()) {
		// One ref per match
		cn = ent - g_entities;

		if (cn == g_RQ3_RefID.integer) {
			trap_SendServerCommand(ent - g_entities, "print \"You are already the referee\n\"");
			return qfalse;
		}

		trap_SendServerCommand(ent - g_entities, "print \"Referee already set on this server\n\"");
		return qfalse;
	}

	trap_Argv(1, pass, sizeof(pass));

	// Does a simple plain text auth 

	if (Q_stricmp(pass, g_RQ3_RefPass.string) == 0) {
		cn = ent - g_entities;
		Com_sprintf(teste, 3, "%i", cn);
		trap_Cvar_Set("g_RQ3_RefID", teste);
		trap_SendServerCommand(-1,
				       va("print \"%s" S_COLOR_WHITE " is the new Referee\n\"",
					  ent->client->pers.netname));
		return qtrue;
	}

	trap_SendServerCommand(ent - g_entities, "print \"Invalid Referee Password\n\"");

	return qfalse;
}

//
//      aasimon: processes comands sent from the referee
//
void Ref_Command(gentity_t * ent)
{
	char com[MAX_TOKEN_CHARS];
	char param[MAX_TOKEN_CHARS];
	int cn;

	cn = ent - g_entities;
	if (cn != g_RQ3_RefID.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"You are not a referee\n\"");
		return;
	}

	trap_Argv(1, com, sizeof(com));

	// nice strcmp for each comand (borring, wheres my beer?)
	if (Q_stricmp(com, "help") == 0) {
		// Theres a clean way to do this - add more help here (this is for example only) 
		trap_SendServerCommand(ent - g_entities, "print \"kick player\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"map_restart\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"clearscores\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"pause\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"cyclemap\n\"");
		trap_SendServerCommand(ent - g_entities, "print\"lockSettings\n\"");
		trap_SendServerCommand(ent - g_entities, "print\"map <map_to_go>\n\"");
		return;
	} else if (Q_stricmp(com, "lockSettings") == 0) {
		if(level.settingsLocked)
			level.settingsLocked = qfalse;
		else
			level.settingsLocked = qtrue;
		return;
	} else if (Q_stricmp(com, "kick") == 0) {	// kick kick kick
		trap_Argv(2, com, sizeof(com));
		if (Q_stricmp(com, "") == 0) {
			trap_SendServerCommand(ent - g_entities,
					       "print \"You must name a player. Use: ref kick <player_name>\n\"");
			return;
		}

		cn = ClientNumberFromString(ent, com);
		if (cn == -1) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \"%s" S_COLOR_WHITE " is not on the server\n\"", com));
			return;
		}
		trap_DropClient(cn, "was kicked by the referee");
	} else if (Q_stricmp(com, "clearscores") == 0) {
		MM_ClearScores();
		return;
	} else if (Q_stricmp(com, "map_restart") == 0) {
		// this is having problems, namely diference from rcon map_restart or using this trap
		// Ok here it goes: doing map_restart with players IN THE GAME forces them to specs but
		// the scoreboard still shows the players in the team.
		// Second thing is: remove the stupid 5-4-3-2-1 if doing map_restart i (with i > 0)

		trap_SendConsoleCommand(EXEC_APPEND, "map_restart 0\n");
		return;
	} else if (Q_stricmp(com, "pause") == 0) {
		if (level.paused) {
			trap_SendServerCommand(-1, "cp \"Game resumed by Referee.\n\"");
			level.paused = qfalse;
		} else {
			if (level.team_game_going) {
				if (level.inGame)
					trap_SendServerCommand(ent - g_entities,
							       "print \"Game will be paused at the end of the round");
				else
					trap_SendServerCommand(-1, va("cp \"Game is now paused by the Referee\""));
				level.paused = qtrue;
			} else
				trap_SendServerCommand(ent - g_entities, "print \"No game is going..");
		}
	} else if (Q_stricmp(com, "cyclemap") == 0){
		BeginIntermission();
	} else if (Q_stricmp(com, "map") == 0){
		// get map name
		trap_Argv(2, param, sizeof(param));
		
		if ( !G_FileExists(va("maps/%s.bsp", param)) ) {
			trap_SendServerCommand(ent - g_entities, va("print \"The map %s does not exist.\n\"", param));
			return;
		}
		else{
			trap_Cvar_Set("g_RQ3_ValidIniFile", "3");
			g_RQ3_ValidIniFile.integer = 3;
			trap_SendServerCommand(-1, va("print \"Referee changed next map to: %s\n\"", param));
			Com_sprintf(level.voteMap, sizeof(level.voteMap), "map %s",param); 
			BeginIntermission();		
		}
	}
	else
		trap_SendServerCommand(ent - g_entities,
				       "print \"Invalid Referee comand. Type ref help to see a list of available commands\n\"");
}

void Ref_Resign(gentity_t * ent)
{
	if (ent - g_entities != g_RQ3_RefID.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"You are not a referee\n\"");
		return;
	}

	trap_Cvar_Set("g_RQ3_RefID", "-1");
	trap_SendServerCommand(ent - g_entities, "print \"You resign from your referee status\n\"");
}

/*
Timelimit
RoundLimit
RoundTimeLimit
Fraglimit
Max Players <- TO BE IMPLEMENTED
Friendly Fire
Chase Cam
Team Grenades
---> Irvision Doesnt Exist.
Force Team Talk
*/
#define NR_SETTVARS 9

const char *settings[] = {"timelimit","g_RQ3_roundlimit","g_RQ3_roundtimelimit","fraglimit","g_RQ3_maxplayers","g_RQ3_forceteamtalk",
								"g_RQ3_limchasecam","g_RQ3_tgren","g_friendlyFire"};

void MM_Settings_f(gentity_t * ent) {
	int i;
	char str[MAX_TOKEN_CHARS];

	if (!g_RQ3_matchmode.integer)
		return;

	//Invalid Data SENT
	if(trap_Argc()!= NR_SETTVARS)
		return;
	if(ent->client->sess.captain == TEAM_FREE && ent - g_entities != g_RQ3_RefID.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"Only Captains and Referees can change match Settings\n\"");
		return;
	}
	//Game has begun
	if(level.inGame) {
		trap_SendServerCommand(ent - g_entities, "print \"Settings can only be changed before a game starts\n\"");
		return;
	}
	//Referee locked settings
	if(level.settingsLocked) {
			trap_SendServerCommand(ent - g_entities, "print \"Settings are currently locked, only Referee can unlock them\n\"");
			return;
	}

	for(i = 0; i < NR_SETTVARS; ++i) {
		trap_Argv(i+1, str, sizeof(str));
		trap_Cvar_Set(settings[i],str);
	}

	trap_SendServerCommand(-1,va("print \"Match Settings have been changed by %s\n\"",ent->client->pers.netname));

}
