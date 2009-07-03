//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.5  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.4  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.3  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_team.h
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

void BotTeamAI(bot_state_t * bs);
int BotGetTeamMateTaskPreference(bot_state_t * bs, int teammate);
void BotSetTeamMateTaskPreference(bot_state_t * bs, int teammate, int preference);
void BotVoiceChat(bot_state_t * bs, int toclient, char *voicechat);
void BotVoiceChatOnly(bot_state_t * bs, int toclient, char *voicechat);
