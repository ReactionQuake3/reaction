#define MM_OK_COLOR		S_COLOR_GREEN
#define MM_DENY_COLOR	S_COLOR_RED	
#define MM_NAMES_COLOR	S_COLOR_BLUE
#define MM_OK_COLOR S_COLOR_GREEN

//g_RQ3_mmflags
#define MMF_TEAMNAME	1
#define MMF_TEAMMODEL	2
#define MMF_UNREADY		4
#define MMF_SETTINGS	8
#define MMF_VOTEREF		16

void MM_RunFrame(void);
void MM_Captain_f(gentity_t *);
void MM_Sub_f(gentity_t *);
void MM_Ready_f(gentity_t *);
void MM_ClearScores(void);
void MM_TeamName_f(gentity_t *);
void MM_TeamModel_f(gentity_t *);
void MM_Referee_f(gentity_t *);
void MM_Settings_f(gentity_t *);
void SendEndMessage();

// aasimon: Declarations for Ref system 
qboolean Ref_Exists(void);
qboolean Ref_Auth(gentity_t *);	// No need to return a boolean in this context
void Ref_Command(gentity_t *);
void Ref_Resign(gentity_t *);
extern int refVotes[2];
