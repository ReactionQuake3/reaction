/*
 * Include for base Action game-related things
 */

#define ACTION_VERSION  "1.52"

extern char team1_name[];
extern char team2_name[];
extern char team1_skin[];
extern char team2_skin[];
extern char team1_skin_index[];
extern char team2_skin_index[];
extern char *map_rotation[];
extern int num_maps, cur_map;
extern char *tnames[];
extern int *took_damage;

void ReadConfigFile();
void ReadMOTDFile();
void PrintMOTD(edict_t *);
void stuffcmd(edict_t *, char *);
int KickDoor( trace_t *tr_old, edict_t *ent, vec3_t forward );

// Prototypes of base Q2 functions that weren't included in any Q2 header
qboolean loc_CanSee(edict_t *, edict_t *);
qboolean IsNeutral(edict_t *);
qboolean IsFemale(edict_t *);
void ParseSayText(edict_t *, char *);

// Firing styles (where shots originate from)
#define ACTION_FIRING_CENTER            0
#define ACTION_FIRING_CLASSIC           1
#define ACTION_FIRING_CLASSIC_HIGH      2

// maxs[2] of a player when crouching (we modify it from the normal 4)
// ...also the modified viewheight -FB 7/18/99
#define CROUCHING_MAXS2                 16
#define CROUCHING_VIEWHEIGHT		8

