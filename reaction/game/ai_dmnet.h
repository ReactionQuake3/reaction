//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.6  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.5  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.4  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_dmnet.h
 *
 * desc:		Quake3 bot AI
 *
 * $Archive: /source/code/botai/ai_chat.c $
 * $Author$ 
 * $Revision$
 * $Modtime: 11/10/99 3:30p $
 * $Date$
 *
 *****************************************************************************/

#define MAX_NODESWITCHES	50

void AIEnter_Intermission(bot_state_t * bs, char *s);
void AIEnter_Observer(bot_state_t * bs, char *s);
void AIEnter_Respawn(bot_state_t * bs, char *s);
void AIEnter_Stand(bot_state_t * bs, char *s);
void AIEnter_Seek_ActivateEntity(bot_state_t * bs, char *s);
void AIEnter_Seek_NBG(bot_state_t * bs, char *s);
void AIEnter_Seek_LTG(bot_state_t * bs, char *s);
void AIEnter_Seek_Camp(bot_state_t * bs, char *s);
void AIEnter_Battle_Fight(bot_state_t * bs, char *s);
void AIEnter_Battle_Chase(bot_state_t * bs, char *s);
void AIEnter_Battle_Retreat(bot_state_t * bs, char *s);
void AIEnter_Battle_NBG(bot_state_t * bs, char *s);
int AINode_Intermission(bot_state_t * bs);
int AINode_Observer(bot_state_t * bs);
int AINode_Respawn(bot_state_t * bs);
int AINode_Stand(bot_state_t * bs);
int AINode_Seek_ActivateEntity(bot_state_t * bs);
int AINode_Seek_NBG(bot_state_t * bs);
int AINode_Seek_LTG(bot_state_t * bs);
int AINode_Battle_Fight(bot_state_t * bs);
int AINode_Battle_Chase(bot_state_t * bs);
int AINode_Battle_Retreat(bot_state_t * bs);
int AINode_Battle_NBG(bot_state_t * bs);

void BotResetNodeSwitches(void);
void BotDumpNodeSwitches(bot_state_t * bs);
