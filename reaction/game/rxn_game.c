//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.15  2002/06/23 19:24:19  niceass
// bandage bug fix
//
// Revision 1.14  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.13  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.12  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.11  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
#include "g_local.h"

//Elder: someone should comment this b/c it's hard to follow
//Makes the damage "non-instant" like AQ2
void CheckBleeding(gentity_t * targ)
{
	int damage;
	int temp;
	int realBleedTime;
	gentity_t *tent;

	// Elder: use the server's FPS as a basis for bleed time
	realBleedTime = trap_Cvar_VariableIntegerValue("sv_fps");
	// just safety check it
	if (realBleedTime <= 0)
		realBleedTime = BLEED_TIME;

	if (!(targ->client->bleeding) || (targ->health <= 0))
		return;

	// NiceAss: (10.0f / realBleedTime) is just (Q2 FPS / Q3 FPS)
	temp = (int) (targ->client->bleeding * 0.2f * (10.0f / realBleedTime));
	targ->client->bleeding -= temp;

	if (temp <= 0)
		temp = 1;

	targ->client->bleed_remain += temp;
	damage = (int) (targ->client->bleed_remain / realBleedTime);

	if (targ->client->bleed_remain >= realBleedTime) {
		//G_Printf("Bleed Remain: %i Server Time: %i\n", targ->client->bleed_remain, level.time);
		//      if ( (targ->client->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK &&
		targ->health -= damage;

		if (targ->health <= 0) {
			player_die(targ, &g_entities[targ->client->lasthurt_client],
				   &g_entities[targ->client->lasthurt_client], damage, targ->client->lasthurt_mod);
		} else {
			targ->client->bleed_remain %= realBleedTime;
		}

		if (g_RQ3_ejectBlood.integer && targ->client->bleed_delay <= level.time) {
			vec3_t bleedOrigin;

			targ->client->bleed_delay = level.time + 2000;	// 2 seconds
			VectorAdd(targ->client->bleedloc_offset, targ->client->ps.origin, bleedOrigin);
			//gi.cprintf(ent, PRINT_HIGH, "Bleeding now.\n");
			//EjectBlooder(ent, pos, pos);

			// do bleeding
			tent = G_TempEntity(bleedOrigin, EV_EJECTBLOOD);
			tent->s.otherEntityNum = targ->s.clientNum;
		}
	}
}

//Elder: apparently does nothing and is unused
void StartBandage(gentity_t * ent)
{
	ent->client->bleeding = 0;
}