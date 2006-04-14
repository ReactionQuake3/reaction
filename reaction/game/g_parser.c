#include "q_shared.h"
#include "g_parser.h"

char *Script_GetToken(char **str)
{
	const char	*whiteSpace		= " ,;\n\r\t";
	char		*ret			= NULL;
	int			inQuotes		= 0;
	
	if (!str || !*str || !**str)
		return NULL;
	
	//skip whitespace
	while (**str && strchr(whiteSpace, **str) != NULL)
		(*str)++;
	
	//end of string?
	if (!**str)
		return NULL;
	
	if ( (inQuotes = (**str == '\"')) )
		(*str)++;
	ret = *str;

	//get actual token
	for ( ; **str; (*str)++)
	{
		if (inQuotes)
		{
			if (**str == '\"')
				break;
			continue;
		}
		if (strchr(whiteSpace, **str) != NULL)
			break;
	}
	
	//end token
	if (**str)
		*(*str)++ = 0;
	
	return ret;
}


int Script_HashKey(const char *keyword)
{
	int register hash, i;

	hash = 0;
	for (i = 0; keyword[i] != '\0'; i++) {
		if (keyword[i] >= 'A' && keyword[i] <= 'Z')
			hash += (keyword[i] + ('a' - 'A')) * (119 + i);
		else
			hash += keyword[i] * (119 + i);
	}
	hash = (hash ^ (hash >> 10) ^ (hash >> 20)) & (SCRIPT_HASH_SIZE - 1);
	return hash;
}

void Script_InitHashTable(TParseState *state)
{
	if (state->initialized)
		return;

	memset((*state).hashTable, 0, sizeof((*state).hashTable));
	FOR_EACH_RULE(*state, rule)
	{
		int index = Script_HashKey(rule->keyword) % SCRIPT_HASH_SIZE;
		TParseRule *next = (*state).hashTable[index];
		rule->next = next;
		(*state).hashTable[index] = rule;
	}
	END_FOR_RULE();

	state->initialized = 1;
}

TParseFunc Script_FindHandler(char *token, TParseState* state)
{
	TParseRule *ptr;
	int index = Script_HashKey(token) % SCRIPT_HASH_SIZE;

	if (!state->initialized)
		Script_InitHashTable(state);
	
	for (ptr = state->hashTable[index]; ptr; ptr = ptr->next)
	{
		if (Q_stricmp(token, ptr->keyword) == 0)
			return ptr->handler;
	}
	return NULL;
}


ID_INLINE void Script_InitStateStack(TStateStack *stack)
{
	stack->top = 0;
}


int Script_PushState(TStateStack *stack, TParseState *state)
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

int Script_GetTopState(const TStateStack *stack, TParseState **state)
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

int Script_PopState(TStateStack *stack, TParseState **state)
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

void Script_ParseString(char *str, TParseState *baseState)
{
	char *token = NULL;
	TStateStack stateStack;

	Script_InitStateStack(&stateStack);
	Script_PushState(&stateStack, baseState);

	while ( (token = Script_GetToken(&str)) != NULL)
	{
		TParseFunc		handler = NULL;
		TParseState		*state;

		Script_GetTopState(&stateStack, &state);

		if ( (handler = Script_FindHandler(token, state)) != NULL)
		{
			handler(&str, &stateStack);
		} else {
			SCRIPT_INFO(SHOW_WARNING)
				G_Printf(S_COLOR_YELLOW "* Warning: unknown token, '%s'.\n", token);
			END_SCRIPT_INFO();
		}
	}
}



int SCRIPT_SHOW_LEVEL = SHOW_NONE;

///////////////////////////////////////////////////////////////
// SAMPLE FUNCTIONS ///////////////////////////////////////////
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
SCRIPT_FUNC(SFN_SkipComment)
///////////////////////////////////////////////////////////////
{
	char *token;
	while ( (token = Script_GetToken(SCRIPT_INPUT)) != NULL)
	{
		if (Q_stricmp(token, "*/") == 0)
			return 1;
	}
	SCRIPT_INFO(SHOW_ERROR)
		G_Printf(S_COLOR_RED "* ERROR: end of input found in comment.\n");
	END_SCRIPT_INFO();
	return 0;
}
END_SCRIPT_FUNC()

///////////////////////////////////////////////////////////////
SCRIPT_FUNC(SFN_SkipLineComment)
///////////////////////////////////////////////////////////////
{
	char *cursor;
	for (cursor = *SCRIPT_INPUT; *cursor; cursor++)
	{
		if (*cursor == '\n' || *cursor == '\r')
		{
			*SCRIPT_INPUT = cursor + 1;
			return 1;
		}
	}
	SCRIPT_INFO(SHOW_ERROR)
		G_Printf(S_COLOR_RED "* ERROR: end of input found in comment.\n");
	END_SCRIPT_INFO();
	return 0;
}
END_SCRIPT_FUNC()

///////////////////////////////////////////////////////////////
SCRIPT_FUNC(SFN_SkipToken)
///////////////////////////////////////////////////////////////
{
	return 1;
}
END_SCRIPT_FUNC()


///////////////////////////////////////////////////////////////
SCRIPT_FUNC(SFN_PopState)
///////////////////////////////////////////////////////////////
{
	SCRIPT_POP_STATE();
	return 1;
}
END_SCRIPT_FUNC()

