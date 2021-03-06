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
// Revision 1.3  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_chat.h
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

//
int BotChat_EnterGame(bot_state_t * bs);

//
int BotChat_ExitGame(bot_state_t * bs);

//
int BotChat_StartLevel(bot_state_t * bs);

//
int BotChat_EndLevel(bot_state_t * bs);

//
int BotChat_HitTalking(bot_state_t * bs);

//
int BotChat_HitNoDeath(bot_state_t * bs);

//
int BotChat_HitNoKill(bot_state_t * bs);

//
int BotChat_Death(bot_state_t * bs);

//
int BotChat_Kill(bot_state_t * bs);

//
int BotChat_EnemySuicide(bot_state_t * bs);

//
int BotChat_Random(bot_state_t * bs);

// time the selected chat takes to type in
float BotChatTime(bot_state_t * bs);

// returns true if the bot can chat at the current position
int BotValidChatPosition(bot_state_t * bs);

// test the initial bot chats
void BotChatTest(bot_state_t * bs);
