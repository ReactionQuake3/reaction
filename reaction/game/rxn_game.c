#include "g_local.h"

//Elder: someone should comment this b/c it's hard to follow
//Makes the damage "non-instant" like AQ2
void CheckBleeding(gentity_t *targ)
{
	int damage;
	int temp;
	
	if (!(targ->client->bleeding) || (targ->health <=0)) return;	
	
	temp = (int)(targ->client->bleeding * .2);
	targ->client->bleeding -= temp;	
	
	if (temp <= 0) temp = 1;	

	targ->client->bleed_remain += temp;	
	damage = (int)(targ->client->bleed_remain/BLEED_TIME);
	
	if (targ->client->bleed_remain >= BLEED_TIME)
	{
		if ( (targ->client->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK &&
			 targ->client->bleedBandageCount < 1)
		{
			//Elder: skip damage being dealt
		}
		else
		{
			targ->health -= damage;
		}

		//Elder: hack to count off health so we only lose 6 health on a bandage
		if ( (targ->client->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK)
		{
			targ->client->bleedBandageCount--;
		}

		if (targ->health <= 0)
		{
			player_die(targ, &g_entities[targ->client->lasthurt_client], &g_entities[targ->client->lasthurt_client], damage, targ->client->lasthurt_mod);
		}
		else
		{
			targ->client->bleed_remain %= BLEED_TIME;
		}
	}
}

//Elder: apparently does nothing and is unused
void StartBandage(gentity_t *ent)
{
	ent->client->bleeding = 0;
}
/*
  int damage;
  int temp;
  vec3_t norm;
  VectorSet(norm, 0.0, 0.0, 0.0 );
  if ( !(ent->client->bleeding) || (ent->health <= 0)  )
  {
    return;
  }
        
  temp = (int)(ent->client->bleeding * .2);
  ent->client->bleeding -= temp;
  if ( temp <= 0 )
    temp = 1;
  ent->client->bleed_remain += temp;
  damage = (int)(ent->client->bleed_remain/BLEED_TIME);
  if ( ent->client->bleed_remain >= BLEED_TIME )
  {
    ent->health -= damage;
    if ( damage > 1 )
    {
                                // action doens't do this
      //ent->client->damage_blood += damage; // for feedback                                
    }
    if ( ent->health <= 0 )
    {
      meansOfDeath = ent->client->attacker_mod;
      locOfDeath = ent->client->attacker_loc;
      Killed(ent, ent->client->attacker, ent->client->attacker, damage, ent->s.origin);
    }
    else
    {
      ent->client->bleed_remain %= BLEED_TIME;
    }
    if (ent->client->bleeddelay <= level.time)
    {
      vec3_t pos;
      ent->client->bleeddelay = level.time + 2; // 2 seconds
      VectorAdd(ent->client->bleedloc_offset, ent->absmax, pos);
      //gi.cprintf(ent, PRINT_HIGH, "Bleeding now.\n");
      EjectBlooder(ent, pos, pos);
                        
      // do bleeding

    }
                                                
  }
*/                
