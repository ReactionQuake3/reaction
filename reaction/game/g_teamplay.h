//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.7  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.6  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.5  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.4  2002/02/09 00:10:12  jbravo
// Fixed spectator follow and free and updated zcam to 1.04 and added the
// missing zcam files.
//
// Revision 1.3  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.2  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.1  2002/01/11 20:23:41  jbravo
// Added the two new files for TP I forgot during the main TP commit
//
//
//-----------------------------------------------------------------------------

#define WINNER_NONE	0
#define WINNER_TEAM1	1
#define WINNER_TEAM2	2
#define WINNER_TIE	3

void CheckTeamRules();
void StartLCA();
void ContinueLCA();
qboolean BothTeamsHavePlayers();
void MakeAllLivePlayersObservers();
int CheckForWinner();
int CheckForForcedWinner();
int WonGame(int winner);
team_t RQ3TeamCount(int ignoreClientNum, int team);
void SpawnPlayers();
void CleanLevel();
void CheckForUnevenTeams(gentity_t *player);
void EquipPlayer (gentity_t *ent);
void RQ3_Cmd_Choose_f(gentity_t *ent);
void RQ3_Cmd_Drop_f( gentity_t *ent );
void UnstickPlayer( gentity_t *ent );
void MakeSpectator( gentity_t *ent );
qboolean OKtoFollow( int clientnum );
void RQ3_Cmd_Radio_f ( gentity_t *ent );
void RQ3_Cmd_Radio_power_f ( gentity_t *ent );
void RQ3_Cmd_Radiogender_f ( gentity_t *ent );
void ParseSayText (gentity_t * ent, char *text);
void RQ3_SpectatorMode(gentity_t *ent);
