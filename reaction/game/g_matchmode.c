#include "g_local.h"
// JBravo: for warnings
int ClientNumberFromString(gentity_t * to, char *s);

gentity_t *refVotes[2];		// refVotes[0] is the clientnumber red team voted 

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

int getNumberOfRefs() {
	gentity_t *ent;
	int i,count;
	count = 0;
	for (i = 0; i < level.maxclients; i++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[i] == NULL) G_Printf("Ln 0030\n");		
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if(ent->client->sess.referee)
			++count;
	}
	return count;
}

gentity_t *getEntByName(char *name)
{
	gentity_t *ent;
	int i;

	for (i = 0; i < level.maxclients; i++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[i] == NULL) G_Printf("Ln 0047\n");
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
		//Blaze: Prit out some Debug info
		if (&g_entities[i] == NULL) G_Printf("Ln 0059\n");		
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
		trap_SendServerCommand(ent - g_entities, va("print \"" MM_DENY_COLOR "You need to be on a team for that\n\""));
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
		trap_SendServerCommand(-1, va("print \"%s" MM_OK_COLOR " is now a Substitute for %s.\n\"",
					      ent->client->pers.netname,
					      ent->client->sess.savedTeam ==
					      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
	} else {
		if(g_RQ3_maxplayers.integer > 0 && (RQ3TeamCount(-1, ent->client->sess.savedTeam) >= g_RQ3_maxplayers.integer)) {
					trap_SendServerCommand(ent - g_entities, va("print \"" MM_DENY_COLOR "Your team is full.\n\""));
					return;
		}
		else {
		ent->client->sess.sub = TEAM_FREE;
		trap_SendServerCommand(-1, va("print \"%s" MM_OK_COLOR " is no longer a Substitute for %s.\n\"",
					      ent->client->pers.netname,
					      ent->client->sess.savedTeam ==
					      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
		}
	}
}

void MM_Captain_f(gentity_t * ent)
{
	if (!g_RQ3_matchmode.integer)
		return;
	if (ent->client->sess.savedTeam == TEAM_SPECTATOR || ent->client->sess.savedTeam == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, va("print \"" MM_DENY_COLOR "You need to be on a team for that\n\""));
		return;
	}
	if (ent->client->sess.captain == TEAM_RED) {
		level.team1ready = qfalse;
		trap_SendServerCommand(-1, va("print \"%s" MM_OK_COLOR " is no longer %s's Captain.\n\"",
					      ent->client->pers.netname, g_RQ3_team1name.string));
		ent->client->sess.captain = TEAM_FREE;
	} else if (ent->client->sess.captain == TEAM_BLUE) {
		level.team2ready = qfalse;
		trap_SendServerCommand(-1, va("print \"%s" MM_OK_COLOR " is no longer %s's Captain.\n\"",
					      ent->client->pers.netname, g_RQ3_team2name.string));
		ent->client->sess.captain = TEAM_FREE;
	} else {
		if (!checkCaptain(ent->client->sess.savedTeam)) {
			ent->client->sess.captain = ent->client->sess.savedTeam;
			trap_SendServerCommand(-1, va("print \"%s" MM_OK_COLOR " is now %s's Captain.\n\"",
						      ent->client->pers.netname,
						      ent->client->sess.savedTeam ==
						      TEAM_BLUE ? g_RQ3_team2name.string : g_RQ3_team1name.string));
		} else
			trap_SendServerCommand(ent - g_entities, va("print \"" MM_DENY_COLOR "Your team already has a Captain\n\""));
	}
}

void MM_Ready_f(gentity_t * ent)
{
	if (!g_RQ3_matchmode.integer)
		return;

	if(level.inGame && (g_RQ3_mmflags.integer & MMF_UNREADY) != MMF_UNREADY) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "This server does not allow you to un-ready your team after the match started\n\""));
		return;
	}

	if (ent->client->sess.captain != TEAM_FREE) {
		if (ent->client->sess.savedTeam == TEAM_RED) {
			trap_SendServerCommand(-1, va("cp \"%s are%s Ready.\n\"",
						      g_RQ3_team1name.string, level.team1ready ? " no longer" : ""));

			if (level.team1ready)
				level.team1ready = qfalse;
			else
				level.team1ready = qtrue;
		} else {
			trap_SendServerCommand(-1, va("cp \"%s are%s Ready.\n\"",
						      g_RQ3_team2name.string, level.team2ready ? " no longer" : ""));

			if (level.team2ready)
				level.team2ready = qfalse;
			else
				level.team2ready = qtrue;
		}
	} else
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "You need to be a captain for that\n\""));
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
		trap_SendServerCommand(ent - g_entities, va("print \"Your current team model is:"MM_OK_COLOR" %s\n\"",
							    ent->client->sess.savedTeam ==
							    TEAM_RED ? g_RQ3_team1model.string : g_RQ3_team2model.
							    string));
		return;
	} else {
		if((g_RQ3_mmflags.integer & MMF_TEAMMODEL) != MMF_TEAMMODEL) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "This server does not allow you to change team model\n\""));
		return;
		}
		if (ent->client->sess.captain == TEAM_FREE) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"You need to be a captain for that\n\""));
			return;
		}

		if (level.team_game_going || level.team_round_going) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_DENY_COLOR"You cannot change your team's model while playing or ready.\n\""));
		}

		trap_Argv(1, buff, sizeof(buff));

		if (team == TEAM_RED) {
			if (level.team1ready) {
				trap_SendServerCommand(ent - g_entities,
						       va("print \"You need to un-ready your team for that..\n\""));
				return;
			}
			trap_Cvar_Set("g_RQ3_team1model", buff);
			trap_SendServerCommand(-1, va("print \"New Team 1 Model: "MM_OK_COLOR"%s\n\"", buff));
		} else {
			if (level.team2ready) {
				trap_SendServerCommand(ent - g_entities,
						       va("print \""MM_DENY_COLOR"You need to un-ready your team for that..\n\""));
				return;
			}
			trap_Cvar_Set("g_RQ3_team2model", buff);
			trap_SendServerCommand(-1, va("print \"New Team 2 Model: "MM_OK_COLOR"%s\n\"", buff));
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
		trap_SendServerCommand(ent - g_entities, va("print \"Your Team Name: " MM_OK_COLOR "%s\n\"",
							    ent->client->sess.savedTeam ==
							    TEAM_RED ? g_RQ3_team1name.string : g_RQ3_team2name.
							    string));
		return;
	} else {

		if((g_RQ3_mmflags.integer & MMF_TEAMNAME) != MMF_TEAMNAME) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "This server does not allow you to change team name\n\""));
		return;
		}
		if (ent->client->sess.captain == TEAM_FREE) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"You need to be a captain for that\n\""));
			return;
		}

		if (level.team_game_going || level.team_round_going) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_DENY_COLOR"You cannot change your team's name while playing or ready.\n\""));
		}

		buff = ConcatArgs(1);

		if (strlen(buff) > TEAM_NAME_SIZE)
			buff[TEAM_NAME_SIZE] = 0;

		if (team == TEAM_RED) {
			if (level.team1ready) {
				trap_SendServerCommand(ent - g_entities,
						       va("print \""MM_DENY_COLOR"You need to un-ready your team for that..\n\""));
				return;
			}
			trap_Cvar_Set("g_RQ3_team1name", buff);
			trap_SendServerCommand(-1, va("print \"New Team 1 Name: %s\n\"", buff));
		} else {
			if (level.team2ready) {
				trap_SendServerCommand(ent - g_entities,
						       va("print \""MM_DENY_COLOR"You need to un-ready your team for that..\n\""));
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
//	gentity_t *ent;
//	char nr[4];

	//G_Printf("Vote Red: %i Vote Blue %i \n", refVotes[0], refVotes[1]);
	if (refVotes[0] == refVotes[1]) {
	//	ent = g_entities + refVotes[0];
		refVotes[0]->client->sess.referee = 1;
		trap_SendServerCommand(-1, va("cp \"%s" MM_OK_COLOR " is now a Referee.\n\"", refVotes[0]->client->pers.netname));
		refVotes[0] = refVotes[1] = NULL;
	}
}

/* Slicer - MM_Referee_f
For captains to vote a referee*/
void MM_Referee_f(gentity_t * ent)
{
	gentity_t *ref;
	char cmd[MAX_TOKEN_CHARS];
	int clientNr;
	team_t captain;

	if (!g_RQ3_matchmode.integer)
		return;

	captain = ent->client->sess.captain;

	if (!g_RQ3_AllowRef.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"No Referee Allowed on this server\n\""));
		return;
	}
	if (captain == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Only captains can vote a referee\n\""));
		return;
	}
	if (trap_Argc() < 2) {
		trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_DENY_COLOR"Use referee <player number> to vote a referee\n\""));
		return;
	}
	trap_Argv(1, cmd, sizeof(cmd));
	clientNr = atoi(cmd);
	if(clientNr < 0 || clientNr > level.maxclients) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Invalid Player Number - use <playerlist>\n\""));
		return;
	}
	ref = &g_entities[clientNr];

	if (!ref->inuse || !ref->client) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Invalid Player Number - use <playerlist>\n\""));
		return;
	}


	if((g_RQ3_mmflags.integer & MMF_VOTEREF) != MMF_VOTEREF) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "This server does not allow captains to vote for a Referee\n\""));
		return;
	}
	if(getNumberOfRefs() == g_RQ3_maxRefs.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Too many referees already on the server\n\""));
		return;
	}

	refVotes[captain - 1] = ref;
		trap_SendServerCommand(-1,va("print \"%s"MM_OK_COLOR" has voted %s"MM_OK_COLOR" for referee\n\"",
					  ent->client->pers.netname, ref->client->pers.netname));
	checkRefVotes();

}
void MM_ClearScores(qboolean clearTeamFlags)
{
	gentity_t *ent;
	int i;

	for (i = 0; i < level.maxclients; i++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[i] == NULL) G_Printf("Ln 1241\n");
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if(clearTeamFlags) {
			ent->client->sess.captain = TEAM_FREE;
			ent->client->sess.sub = TEAM_FREE;
		}
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
/*qboolean Ref_Exists(void)
{

	if (g_RQ3_RefID.integer == -1)
		return qfalse;
	else
		return qtrue;
}
*/
//
//      aasimon: Ref Auth. Do some kind of logging (ip's etc)
//
qboolean Ref_Auth(gentity_t * ent)
{
	char pass[MAX_TOKEN_CHARS];
//	int cn;
//	char teste[2];

	if (!g_RQ3_AllowRef.integer) {
		// No ref allowed on the server - HELLO!!!!! FIREMAN CARS????
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"No Referee Allowed on this server\n\""));
		return qfalse;
	}
	if(!g_RQ3_matchmode.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"This server is not running match mode\n\""));
		return qfalse;
	}

	if (Q_stricmp(g_RQ3_RefPass.string, "") == 0) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"No Referee Password Set on this server\n\""));
		return qfalse;
	}

/*	if (Ref_Exists()) {
		// One ref per match
		cn = ent - g_entities;

		if (cn == g_RQ3_RefID.integer) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"You are already the referee\n\""));
			return qfalse;
		}

		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Referee already set on this server\n\""));
		return qfalse;
	}*/
	if(getNumberOfRefs() == g_RQ3_maxRefs.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Too many referees already on the server\n\""));
		return qfalse;
	}
	if (ent->client->sess.referee) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"You are already the referee\n\""));
			return qfalse;
	}
	if (trap_Argc() < 2) {
		trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_DENY_COLOR"Use reflogin <password> to become a referee\n\""));
		return qfalse;
	}
	trap_Argv(1, pass, sizeof(pass));
	

	// Does a simple plain text auth 

	if (Q_stricmp(pass, g_RQ3_RefPass.string) == 0) {
		ent->client->sess.referee = 1;
		trap_SendServerCommand(-1,
				       va("print \"%s "MM_OK_COLOR"is now a Referee\n\"",
					  ent->client->pers.netname));
		return qtrue;
	}
/*	if (Q_stricmp(pass, g_RQ3_RefPass.string) == 0) {
		cn = ent - g_entities;
		Com_sprintf(teste, 3, "%i", cn);
		trap_Cvar_Set("g_RQ3_RefID", teste);
		trap_SendServerCommand(-1,
				       va("print \"%s "MM_OK_COLOR"is the new Referee\n\"",
					  ent->client->pers.netname));
		return qtrue;
	}
*/
	trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Invalid Referee Password\n\""));

	return qfalse;
}
// MM_ResetMatch by Slicer
//	Used by admin or rcon to reset Match settings, that is subs, captains, scores, teams's status and game status
//
void MM_ResetMatch() {
		trap_SendServerCommand(-1, va("print \""MM_OK_COLOR" Reseting Server Match Status...\n\""));
		// CleanUp Scores and Team Status
		MM_ClearScores(qtrue);
		// Just in case
		MakeAllLivePlayersObservers();
		level.team1ready = qfalse;
		level.team2ready = qfalse;
		level.inGame = qfalse;
		level.team_game_going = 0;
		level.team_round_going = 0;
		level.team_round_countdown = 0;
		level.matchTime = 0;
}

//
//      aasimon: processes comands sent from the referee
//
void Ref_Command(gentity_t * ent)
{
	char com[MAX_TOKEN_CHARS];
	char param[MAX_TOKEN_CHARS];
	char arg2[MAX_STRING_CHARS];
	int cn, i;
	gentity_t *p;

	//cn = ent - g_entities;
	if (!ent->client->sess.referee) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"You are not a referee\n\""));
		return;
	}

	trap_Argv(1, com, sizeof(com));

	// nice strcmp for each comand (borring, wheres my beer?)
	if (Q_stricmp(com, "help") == 0) {
		// Theres a clean way to do this - add more help here (this is for example only) 
		trap_SendServerCommand(ent - g_entities, "print \"kick <player number>\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"map_restart\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"clearscores\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"pause\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"cyclemap\n\"");
		trap_SendServerCommand(ent - g_entities, "print\"lockSettings\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"resetMatch\n\"");
		trap_SendServerCommand(ent - g_entities, "print\"map <map_to_go>\n\"");
		trap_SendServerCommand(ent - g_entities, "print\"say <text>\n\"");
		return;
	} else if (Q_stricmp(com, "resetMatch") == 0) {
		MM_ResetMatch();
		return;
	} else if (Q_stricmp(com, "lockSettings") == 0) {
		if(level.settingsLocked) {
			level.settingsLocked = qfalse;
			trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_OK_COLOR"Settings are now unLocked\n\""));
		}
		else {
			level.settingsLocked = qtrue;
			trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_OK_COLOR"Settings are now Locked\n\""));
		}
		return;
	} else if (Q_stricmp(com, "kick") == 0) {	// kick kick kick
		trap_Argv(2, com, sizeof(com));
		if (Q_stricmp(com, "") == 0) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \""MM_DENY_COLOR"You must specify a player number - use <playerlist>\n\""));
			return;
		}

		/*cn = ClientNumberFromString(ent, com);
		if (cn == -1) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \"%s "MM_DENY_COLOR"is not on the server\n\"", com));
			return;
		}
		trap_DropClient(cn, "was kicked by the referee");*/
		cn = atoi(com);
		if(cn < 0 || cn > level.maxclients) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Invalid Player Number - use <playerlist>\n\""));
			return;
		}
		p = &g_entities[cn];

		if (!p->inuse || !p->client) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Invalid Player Number - use <playerlist>\n\""));
		return;
		}
		trap_DropClient(p - g_entities,"was kicked by the referee");

	} else if (Q_stricmp(com, "clearscores") == 0) {
		MM_ClearScores(qfalse);
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
							       va("print \""MM_OK_COLOR"Game will be paused at the end of the round"));
				else
					trap_SendServerCommand(-1, va("cp \"Game is now paused by the Referee\""));
				level.paused = qtrue;
			} else
				trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"No game is going.."));
		}
	} else if (Q_stricmp(com, "cyclemap") == 0){
		BeginIntermission();
	} else if (Q_stricmp(com, "map") == 0){
		// get map name
		trap_Argv(2, param, sizeof(param));
		
		if ( !G_FileExists(va("maps/%s.bsp", param)) ) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"The map %s does not exist.\n\"", param));
			return;
		}
		else{
			trap_Cvar_Set("g_RQ3_ValidIniFile", "3");
			g_RQ3_ValidIniFile.integer = 3;
			trap_SendServerCommand(-1, va("print \""MM_OK_COLOR"Referee changed next map to: %s\n\"", param));
			Com_sprintf(level.voteMap, sizeof(level.voteMap), "map %s",param); 
			BeginIntermission();		
		}
	}
	else if (Q_stricmp(com, "say") == 0) {
		arg2[0] = '\0';
		for (i = 2; i < trap_Argc(); i++) {
			if (i > 2)
				strcat(arg2, " ");
			trap_Argv(i, &arg2[strlen(arg2)], sizeof(arg2) - strlen(arg2));
		}

		G_Say(ent, NULL, SAY_REF, arg2);
	}
	else
		trap_SendServerCommand(ent - g_entities,
				       va("print \""MM_DENY_COLOR"Invalid Referee comand. Type ref help to see a list of available commands\n\""));
}

void Ref_Resign(gentity_t * ent)
{
	if (ent->client->sess.referee) {
		ent->client->sess.referee = 0;
		trap_SendServerCommand(ent - g_entities, va("print \""MM_OK_COLOR"You resign from your referee status\n\""));
	}
}

/*
Timelimit
RoundLimit
RoundTimeLimit
Fraglimit
Max Players
Friendly Fire
Chase Cam
Team Grenades
---> Irvision Doesnt Exist.
Force Team Talk
*/
#define NR_SETTVARS 9

const char *settings[] = {"timelimit", "g_RQ3_roundlimit", "g_RQ3_roundtimelimit", "fraglimit", "g_RQ3_maxplayers",
				"g_RQ3_forceteamtalk", "g_RQ3_limchasecam","g_RQ3_tgren","g_friendlyFire"};
// JBravo: adding settings2 for cvars to set in the client for the MM ingame menu.
const char *settings2[] = {"cg_RQ3_timelimit", "cg_RQ3_roundlimit", "cg_RQ3_roundtimelimit", "cg_RQ3_fraglimit",
				"cg_RQ3_maxplayers", "cg_RQ3_forceteamtalk", "cg_RQ3_limchasecam", "cg_RQ3_tgren", "cg_RQ3_friendlyFire"};

void MM_Settings_f(gentity_t * ent) {
	int i;
	char str[MAX_TOKEN_CHARS];

	if (!g_RQ3_matchmode.integer)
		return;

	//Invalid Data SENT
	if (trap_Argc() -1 != NR_SETTVARS) {
		return;
	}

	if ((g_RQ3_mmflags.integer & MMF_SETTINGS) != MMF_SETTINGS) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR "This server does not allow you to change settings\n\""));
		return;
	}
	if (ent->client->sess.captain == TEAM_FREE && !ent->client->sess.referee) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Only Captains and Referees can change match Settings\n\""));
		return;
	}
	//Game has begun
	if (level.inGame) {
		trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Settings can only be changed before a game starts\n\""));
		return;
	}
	//Referee locked settings
	if (level.settingsLocked) {
			trap_SendServerCommand(ent - g_entities, va("print \""MM_DENY_COLOR"Settings are currently locked, only Referee can unlock them\n\""));
			return;
	}

	for (i = 0; i < NR_SETTVARS; ++i) {
		trap_Argv(i+1, str, sizeof(str));
		trap_Cvar_Set(settings[i],str);
		// JBravo: setting the cvars in cgame now.
		trap_SendServerCommand(-1, va("rq3_cmd %i %s %s", CVARSET, settings2[i], str));
	}

	trap_SendServerCommand(-1,va("print \""MM_OK_COLOR"Match Settings have been changed by %s\n\"",ent->client->pers.netname));

}
