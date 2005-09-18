#ifndef _G_PARSER_H_
#define _G_PARSER_H_
///////////////////////////////////////////////////////////////


#include "g_local.h"


#define STATE_STACK_SIZE			32
#define SCRIPT_HASH_SIZE			64

typedef struct
{
	int					top;
	void				*states[STATE_STACK_SIZE];
} TStateStack;

typedef int (*TParseFunc)(char **tokens, TStateStack *stack);


typedef struct _TParseRule
{
	const char			*keyword;
	TParseFunc			handler;
	struct _TParseRule	*next;
} TParseRule;

typedef struct
{
	const char	*name;
	void		*data;
	int			initialized;
	TParseRule	*hashTable[SCRIPT_HASH_SIZE];
	TParseRule	rules[];
} TParseState;

#define SCRIPT_STATE(name, data)\
TParseState name = {\
	#name,			/* state name */		\
	data,			/* optional data */		\
	0,				/* uninitialized */		\
	{NULL},			/* hash table */

#define ADD_RULE(exp, func)		{exp, &func, NULL},

#define END_STATE_MARKER		{NULL, NULL, NULL}\
}

#define NO_DATA					NULL


typedef enum
{
	SHOW_ALL,
	SHOW_WARNING,
	SHOW_ERROR,
	SHOW_NONE
} TErrorLevel;

///////////////////////////////////////////////////////////////

extern int SCRIPT_SHOW_LEVEL;

#define SCRIPT_INFO(level)			if (SCRIPT_SHOW_LEVEL <= (level)) {
#define END_SCRIPT_INFO()					}

#define NEEDS_TOKENS(num, name)\
	char *name[num];\
	{\
		int TOKEN_INDEX;\
		for (TOKEN_INDEX=0; TOKEN_INDEX<num; TOKEN_INDEX++)\
		if ( (name[TOKEN_INDEX] = Script_GetToken(SCRIPT_INPUT)) == NULL)\
		{\
			SCRIPT_INFO(SHOW_ERROR)\
				G_Printf("* ERROR: %s requires %d arguments instead of %d.\n", __SCRIPT_FUNC__, num, TOKEN_INDEX);\
			END_SCRIPT_INFO();\
			return 0;\
		}\
	}

#define SCRIPT_FUNC_PROTO(name)		int name(char **SCRIPT_INPUT, TStateStack *SCRIPT_STACK)

#define SCRIPT_FUNC(name)\
	SCRIPT_FUNC_PROTO(name)\
	{\
		const char *__SCRIPT_FUNC__ = #name;

#define END_SCRIPT_FUNC()\
}

#define FOR_EACH_RULE(state, rule)\
{\
	int RULE_INDEX;\
	TParseRule *rule;\
	for (RULE_INDEX=0, rule = &(state).rules[0]; rule->keyword != NULL && rule->handler != NULL; RULE_INDEX++, rule++)

#define END_FOR_RULE()		}

///////////////////////////////////////////////////////////////


__inline int Script_PushState(TStateStack *stack, TParseState *state)
{
	if (stack->top >= STATE_STACK_SIZE)
	{
		SCRIPT_INFO(SHOW_ERROR)
			G_Printf("* ERROR: Stack overflow before %s.\n", (state) ? state->name : "[UNKNOWN]");
		END_SCRIPT_INFO();
		return 0;
	}
	stack->states[stack->top++] = state;

	return 1;
}

__inline int Script_GetTopState(const TStateStack *stack, TParseState **state)
{
	if (!state)
		return 1;
	if (stack->top < 0 || stack->top >= STATE_STACK_SIZE)
	{
		*state = NULL;
		SCRIPT_INFO(SHOW_ERROR)
			G_Printf("* ERROR: Stack index out of bounds (%d).\n", stack->top);
		END_SCRIPT_INFO();
		return 0;
	}

	*state = stack->states[stack->top-1];
	return 1;
}

__inline int Script_PopState(TStateStack *stack, TParseState **state)
{
	stack->top--;
	if (stack->top < 0)
	{
		SCRIPT_INFO(SHOW_ERROR)
			G_Printf("* ERROR: Stack underflow before %s.\n", (stack->states[0]) ? ((TParseState*)stack->states[0])->name : "[UNKNOWN]");
		END_SCRIPT_INFO();
		if (state)
			*state = NULL;
		return 0;
	}
	if (state)
		*state = stack->states[stack->top];
	return 1;
}


char*			Script_GetToken(char **str);
TParseFunc		Script_FindHandler(char *token, TParseState *state);
void			Script_ParseString(char *str, TParseState *baseState);

#define SCRIPT_PUSH_STATE(state)		Script_PushState(SCRIPT_STACK, &state)
#define SCRIPT_POP_STATE()				Script_PopState(SCRIPT_STACK, NULL)

#define SCRIPT_TRANSITION_TO(Dest)			Transition_To_##Dest

#define SCRIPT_TRANSITION_FUNC(Dest)\
	SCRIPT_FUNC(SCRIPT_TRANSITION_TO(Dest))\
	{\
		SCRIPT_PUSH_STATE(Dest);\
		return 0;\
	}\
	END_SCRIPT_FUNC()


SCRIPT_FUNC_PROTO(SFN_SkipComment);
SCRIPT_FUNC_PROTO(SFN_SkipLineComment);
SCRIPT_FUNC_PROTO(SFN_SkipToken);
SCRIPT_FUNC_PROTO(SFN_PopState);


///////////////////////////////////////////////////////////////
#endif //_G_PARSER_H_