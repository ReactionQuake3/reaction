//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.12  2002/04/26 03:39:34  jbravo
// added tkok, fixed players always leaving zcam modes when player thats
// beeing tracked dies
//
// Revision 1.11  2002/04/07 12:49:10  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.10  2002/04/03 09:26:47  jbravo
// New FF system. Warns and then finally kickbans teamwounders and
// teamkillers
//
// Revision 1.9  2002/04/01 02:56:50  jbravo
// Some sourcecode reformatting
//
// Revision 1.8  2002/03/31 23:41:45  jbravo
// Added the use command
//
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
//Slicer TeamName Size.
#define TEAM_NAME_SIZE 30

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
void RQ3_Cmd_Use_f(gentity_t *ent);
void RQ3_Cmd_Drop_f(gentity_t *ent);
void UnstickPlayer(gentity_t *ent);
void MakeSpectator(gentity_t *ent);
qboolean OKtoFollow(int clientnum);
void RQ3_Cmd_Radio_f (gentity_t *ent);
void RQ3_Cmd_Radio_power_f (gentity_t *ent);
void RQ3_Cmd_Radiogender_f (gentity_t *ent);
void ParseSayText (gentity_t * ent, char *text);
void RQ3_SpectatorMode(gentity_t *ent);
void Add_TeamKill(gentity_t *attacker);
void RQ3_Cmd_TKOk(gentity_t *ent);
void Add_TeamWound(gentity_t *attacker, gentity_t *victim, int mod);
void setFFState(gentity_t *ent);
