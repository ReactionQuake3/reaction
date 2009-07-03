//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log: ui_shared.c,v $
// Revision 1.35  2006/07/24 17:16:12  makro
// Got rid of the warnings lcc liked to share with the world
//
// Revision 1.34  2006/04/14 18:02:06  makro
// no message
//
// Revision 1.33  2005/09/18 16:56:45  makro
// no message
//
// Revision 1.32  2005/09/07 20:24:33  makro
// Vector support for most item types
//
// Revision 1.31  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.30  2003/04/19 17:41:26  jbravo
// Applied changes that where in 1.29h -> 1.32b gamecode.
//
// Revision 1.29  2003/04/06 18:31:21  makro
// SSG crosshairs
//
// Revision 1.28  2003/03/31 15:17:58  makro
// Replacements system tweaks.
// Fixed some other bugs.
//
// Revision 1.27  2003/03/31 00:40:54  makro
// Fixed a bug
//
// Revision 1.26  2003/03/31 00:23:18  makro
// Replacements and stuff
//
// Revision 1.25  2003/02/13 21:19:51  makro
// no message
//
// Revision 1.24  2002/11/09 13:05:02  makro
// g_RQ3_teamXname cvars are now used in the join menu
//
// Revision 1.23  2002/09/29 16:06:45  jbravo
// Work done at the HPWorld expo
//
// Revision 1.22  2002/08/26 00:41:53  makro
// Presets menu + editor
//
// Revision 1.21  2002/06/16 20:06:15  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.20  2002/06/12 11:15:31  makro
// Support for changing the SSG crosshair. Some other stuff
//
// Revision 1.19  2002/06/08 11:43:31  makro
// Changed color "lerping" for focused items a bit
//
// Revision 1.18  2002/06/05 19:17:07  makro
// Squashed some bugs :)
//
// Revision 1.17  2002/06/04 11:37:23  makro
// Items that fade out are hidden automatically now
//
// Revision 1.16  2002/06/02 00:15:07  makro
// Small fixes
//
// Revision 1.15  2002/04/30 11:56:54  makro
// Stuff
//
// Revision 1.14  2002/04/20 15:06:28  makro
// Cool stuff :p
//
// Revision 1.13  2002/04/14 21:50:55  makro
// Stuff
//
// Revision 1.12  2002/04/11 20:57:19  makro
// Tweaked onShow script handling; added onFirstShow script
//
// Revision 1.11  2002/03/31 13:23:25  makro
// Cleaned things up a little
//
// Revision 1.10  2002/03/24 21:26:14  makro
// no message
//
// Revision 1.9  2002/03/14 21:52:08  makro
// no message
//
// Revision 1.8  2002/03/10 22:10:10  makro
// no message
//
// Revision 1.7  2002/03/03 21:22:58  makro
// no message
//
// Revision 1.5  2002/02/24 00:54:12  makro
// Even more fixes to the shortcut keys code.
// Added more info to the header, too :)
//
// Revision 1.4  2002/02/23 15:02:22  makro
// Improved the code that checks for shortcut keys, it runs a lot faster now
//
// Revision 1.3  2002/02/21 20:10:16  jbravo
// Converted files back from M$ format and added cvs headers again.
//
// Revision 1.2 makro
// Added support for shortcut keys, 3d model rotation, model origin offset,
// new command to bring up the weapon menu and a cvar to be used in the
// player options menu. Also improved the remapShader command.
//
//
//-----------------------------------------------------------------------------
// 
// string allocation/managment

#include "ui_shared.h"
#include "../game/bg_public.h"

//Makro - avoid warnings
int UI_SelectedQ3Head(qboolean);
qboolean UI_NeedToUpdateModel();

#define SCROLL_TIME_START					500
#define SCROLL_TIME_ADJUST				150
#define SCROLL_TIME_ADJUSTOFFSET	40
#define SCROLL_TIME_FLOOR					20

//Makro - drop shadow size
#define DROP_SHADOW_SIZE	12
#define DROP_SHADOW_OFFSET	4

typedef struct scrollInfo_s {
	int nextScrollTime;
	int nextAdjustTime;
	int adjustValue;
	int scrollKey;
	float xStart;
	float yStart;
	itemDef_t *item;
	qboolean scrollDir;
} scrollInfo_t;

static scrollInfo_t scrollInfo;

static void (*captureFunc) (void *p) = 0; // NULL;
static void *captureData = NULL;
static itemDef_t *itemCapture = NULL;	// item that has the mouse captured ( if any )

displayContextDef_t *DC = NULL;

static qboolean g_waitingForKey = qfalse;
static qboolean g_editingField = qfalse;

static itemDef_t *g_bindItem = NULL;
static itemDef_t *g_editItem = NULL;

menuDef_t Menus[MAX_MENUS];	// defined menus
int menuCount = 0;		// how many

int GMemory()
{
	return sizeof(Menus);
}

menuDef_t *menuStack[MAX_OPEN_MENUS];
int openMenuCount = 0;

//Makro - previous menu
static menuDef_t *prevMenu = NULL;
//Makro - menu to be moved around
menuDef_t *g_anchoredMenu = NULL;
float g_anchorX = 0, g_anchorY = 0;

static qboolean debugMode = qfalse;

#define DOUBLE_CLICK_DELAY 300
static int lastListBoxClickTime = 0;

void Item_RunScript(itemDef_t * item, const char *s);
void Item_SetupKeywordHash(void);
void Menu_SetupKeywordHash(void);
int BindingIDFromName(const char *name);
qboolean Item_Bind_HandleKey(itemDef_t * item, int key, qboolean down);
itemDef_t *Menu_SetPrevCursorItem(menuDef_t * menu);
itemDef_t *Menu_SetNextCursorItem(menuDef_t * menu);
static qboolean Menu_OverActiveItem(menuDef_t * menu, float x, float y);

#ifdef CGAME
#define MEM_POOL_SIZE  128 * 1024
#else
#define MEM_POOL_SIZE  1024 * 1024
#endif

static char memoryPool[MEM_POOL_SIZE];
static int allocPoint, outOfMemory;

/*
===============
UI_Alloc
===============
*/
void *UI_Alloc(int size)
{
	char *p;

	if (allocPoint + size > MEM_POOL_SIZE) {
		outOfMemory = qtrue;
		if (DC->Print) {
			DC->Print("UI_Alloc: Failure. Out of memory!\n");
		}
		//DC->trap_Print(S_COLOR_YELLOW"WARNING: UI Out of Memory!\n");
		return NULL;
	}

	p = &memoryPool[allocPoint];

	allocPoint += (size + 15) & ~15;

	return p;
}

/*
===============
UI_InitMemory
===============
*/
void UI_InitMemory(void)
{
	allocPoint = 0;
	outOfMemory = qfalse;
}

qboolean UI_OutOfMemory()
{
	return outOfMemory;
}

//Makro - data for the shortcut keys

typedef struct {
	char *Name;
	int Value;
} RQ3_keyAlias_t;

static RQ3_keyAlias_t RQ3_KeyAliases[] = {
	{"", -1},
	{"F1", K_F1},
	{"F2", K_F2},
	{"F3", K_F3},
	{"F4", K_F4},
	{"F5", K_F5},
	{"F6", K_F6},
	{"F7", K_F7},
	{"F8", K_F8},
	{"F9", K_F9},
	{"F10", K_F10},
	{"F11", K_F11},
	{"F12", K_F12}
};

//Makro - only check for shortcuts 20 times a second MAX
static int UI_RQ3_lastCheckForShortcuts = 0;
static int UI_RQ3_ShortcutCheckDelay = 50;

//Makro - for shortcut keys
ID_INLINE int UI_RQ3_KeyNumFromChar(const char *keystr)
{
	int i;
	
	if (!keystr || !*keystr)
		return -1;

	for (i = 0; RQ3_KeyAliases[i].Value != K_LAST_KEY; i++) {
		//let's make sure we have valid strings
		if (RQ3_KeyAliases[i].Name[0] && keystr && keystr[0]) {
			if (Q_stricmp(RQ3_KeyAliases[i].Name, keystr) == 0) {
				return RQ3_KeyAliases[i].Value;
			}
		}
	}

	return -1;
}

//Makro - check whether or not a key is MOUSE1/2/3
//No need for a function
#define UI_IsMouse(key) ((key) == K_MOUSE1 || (key) == K_MOUSE2 || (key) == K_MOUSE3)

#define HASH_TABLE_SIZE 2048
/*
================
return a hash value for the string
================
*/
static long hashForString(const char *str)
{
	int i;
	long hash;
	char letter;

	hash = 0;
	i = 0;
	while (str[i] != '\0') {
		letter = tolower(str[i]);
		hash += (long) (letter) * (i + 119);
		i++;
	}
	hash &= (HASH_TABLE_SIZE - 1);
	return hash;
}

typedef struct stringDef_s {
	struct stringDef_s *next;
	const char *str;
} stringDef_t;

static int strPoolIndex = 0;
static char strPool[STRING_POOL_SIZE];

static int strHandleCount = 0;
static stringDef_t *strHandle[HASH_TABLE_SIZE];

const char *String_Alloc(const char *p)
{
	int len;
	long hash;
	stringDef_t *str, *last;
	static const char *staticNULL = "";

	if (p == NULL) {
		return NULL;
	}

	if (*p == 0) {
		return staticNULL;
	}

	hash = hashForString(p);

	str = strHandle[hash];
	while (str) {
		if (strcmp(p, str->str) == 0) {
			return str->str;
		}
		str = str->next;
	}

	len = strlen(p);
	if (len + strPoolIndex + 1 < STRING_POOL_SIZE) {
		int ph = strPoolIndex;

		strcpy(&strPool[strPoolIndex], p);
		strPoolIndex += len + 1;

		str = strHandle[hash];
		last = str;
		while (str && str->next) {
			last = str;
			str = str->next;
		}

		str = UI_Alloc(sizeof(stringDef_t));
		str->next = NULL;
		str->str = &strPool[ph];
		if (last) {
			last->next = str;
		} else {
			strHandle[hash] = str;
		}
		return &strPool[ph];
	}
	return NULL;
}

void String_Report()
{
	float f;

	Com_Printf("Memory/String Pool Info\n");
	Com_Printf("----------------\n");
	f = strPoolIndex;
	f /= STRING_POOL_SIZE;
	f *= 100;
	Com_Printf("String Pool is %.1f%% full, %i bytes out of %i used.\n", f, strPoolIndex, STRING_POOL_SIZE);
	f = allocPoint;
	f /= MEM_POOL_SIZE;
	f *= 100;
	Com_Printf("Memory Pool is %.1f%% full, %i bytes out of %i used.\n", f, allocPoint, MEM_POOL_SIZE);
}

/*
=================
String_Init
=================
*/
void String_Init()
{
	int i;

	for (i = 0; i < HASH_TABLE_SIZE; i++) {
		strHandle[i] = 0;
	}
	strHandleCount = 0;
	strPoolIndex = 0;
	menuCount = 0;
	openMenuCount = 0;
	UI_InitMemory();
	Item_SetupKeywordHash();
	Menu_SetupKeywordHash();
	if (DC && DC->getBindingBuf) {
		Controls_GetConfig();
	}
}

/*
=================
PC_SourceWarning
=================
*/
void PC_SourceWarning(int handle, char *format, ...)
{
	int line;
	char filename[128];
	va_list argptr;
	static char string[4096];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	filename[0] = '\0';
	line = 0;
	trap_PC_SourceFileAndLine(handle, filename, &line);

	Com_Printf(S_COLOR_YELLOW "WARNING: %s, line %d: %s\n", filename, line, string);
}

/*
=================
PC_SourceError
=================
*/
void PC_SourceError(int handle, char *format, ...)
{
	int line;
	char filename[128];
	va_list argptr;
	static char string[4096];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	filename[0] = '\0';
	line = 0;
	trap_PC_SourceFileAndLine(handle, filename, &line);

	Com_Printf(S_COLOR_RED "ERROR: %s, line %d: %s\n", filename, line, string);
}

/*
=================
LerpColor
=================
*/
void LerpColor(vec4_t a, vec4_t b, vec4_t c, float t)
{
	int i;

	// lerp and clamp each component
	for (i = 0; i < 4; i++) {
		c[i] = a[i] + t * (b[i] - a[i]);
		if (c[i] < 0)
			c[i] = 0;
		else if (c[i] > 1.0)
			c[i] = 1.0;
	}
}

/*
=================
Float_Parse
=================
*/
qboolean Float_Parse(char **p, float *f)
{
	char *token;
	qboolean negative = qfalse;

	for (	token = COM_ParseExt(p, qfalse);
			token && *token;
			token = COM_ParseExt(p, qfalse)	)
	{
		if (*token != '-' || token[1] != 0)
			break;

		negative ^= qtrue;
	}

	if (token && token[0] != 0)
	{
		*f = atof(token);
		if (negative)
			*f = -*f;
		return qtrue;
	} else {
		return qfalse;
	}
}

/*
=================
PC_Float_Parse
=================
*/
qboolean PC_Float_Parse(int handle, float *f)
{
	pc_token_t token;
	int negative = qfalse;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;

	while (token.type == TT_PUNCTUATION)
	{
		if (token.string[0] != '-')
		{
			PC_SourceError(handle, "expected float but found %s\n", token.string);
			return qfalse;
		}
		
		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;
		
		negative ^= qtrue;
	}

	if (token.type != TT_NUMBER)
	{
		PC_SourceError(handle, "expected float but found %s\n", token.string);
		return qfalse;
	}
	
	if (negative)
		*f = -Q_fabs(token.floatvalue);
	else
		*f = Q_fabs(token.floatvalue);
	
	return qtrue;
}

/*
=================
Color_Parse
=================
*/
qboolean Color_Parse(char **p, vec4_t * c)
{
	int i;
	float f;

	for (i = 0; i < 4; i++) {
		if (!Float_Parse(p, &f)) {
			return qfalse;
		}
		(*c)[i] = f;
	}
	return qtrue;
}

/*
=================
PC_Color_Parse
=================
*/
qboolean PC_Color_Parse(int handle, vec4_t * c)
{
	int i;
	float f;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		(*c)[i] = f;
	}
	return qtrue;
}

/*
=================
Int_Parse
=================
*/
qboolean Int_Parse(char **p, int *i)
{
	char *token;
	qboolean negative = qfalse;

	for (	token = COM_ParseExt(p, qfalse);
			token && *token;
			token = COM_ParseExt(p, qfalse)	)
	{
		if (*token != '-' || token[1] != 0)
			break;

		negative ^= qtrue;
	}

	if (token && token[0] != 0)
	{
		*i = atoi(token);
		if (negative)
			*i = -*i;
		return qtrue;
	} else {
		return qfalse;
	}
}

/*
=================
PC_Int_Parse
=================
*/
qboolean PC_Int_Parse(int handle, int *i)
{
	pc_token_t token;
	int negative = qfalse;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;

	while (token.type == TT_PUNCTUATION)
	{
		if (token.string[0] != '-')
		{
			PC_SourceError(handle, "expected integer but found %s\n", token.string);
			return qfalse;
		}
		
		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;
		
		negative ^= qtrue;
	}

	if (token.type != TT_NUMBER)
	{
		PC_SourceError(handle, "expected integer but found %s\n", token.string);
		return qfalse;
	}
	
	if (negative)
		*i = -abs(token.intvalue);
	else
		*i = abs(token.intvalue);
	
	return qtrue;
}

/*
=================
Rect_Parse
=================
*/
qboolean Rect_Parse(char **p, rectDef_t * r)
{
	//Makro - this is safer
	r->hasVectors = qfalse;
	if (Float_Parse(p, &r->x)) {
		if (Float_Parse(p, &r->y)) {
			if (Float_Parse(p, &r->w)) {
				if (Float_Parse(p, &r->h)) {
					return qtrue;
				}
			}
		}
	}
	return qfalse;
}

/*
=================
PC_Rect_Parse
=================
*/
qboolean PC_Rect_Parse(int handle, rectDef_t * r)
{
	//Makro - this is safer
	r->hasVectors = qfalse;
	if (PC_Float_Parse(handle, &r->x)) {
		if (PC_Float_Parse(handle, &r->y)) {
			if (PC_Float_Parse(handle, &r->w)) {
				if (PC_Float_Parse(handle, &r->h)) {
					return qtrue;
				}
			}
		}
	}
	return qfalse;
}

/*
=================
String_Parse
=================
*/
qboolean String_Parse(char **p, const char **out)
{
	char *token;

	token = COM_ParseExt(p, qfalse);
	if (token && token[0] != 0) {
		*(out) = String_Alloc(token);
		return qtrue;
	}
	return qfalse;
}

/*
=================
PC_String_Parse
=================
*/
qboolean PC_String_Parse(int handle, const char **out)
{
	pc_token_t token;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;

	*(out) = String_Alloc(token.string);
	return qtrue;
}

/*
=================
PC_Script_Parse
=================
*/
qboolean PC_Script_Parse(int handle, const char **out)
{
	char script[1024];
	pc_token_t token;

	memset(script, 0, sizeof(script));
	// scripts start with { and have ; separated command lists.. commands are command, arg.. 
	// basically we want everything between the { } as it will be interpreted at run time

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (Q_stricmp(token.string, "{") != 0) {
		return qfalse;
	}

	INFINITE_LOOP {
		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;

		if (Q_stricmp(token.string, "}") == 0) {
			*out = String_Alloc(script);
			return qtrue;
		}

		if (token.string[1] != '\0') {
			Q_strcat(script, 1024, va("\"%s\"", token.string));
		} else {
			Q_strcat(script, 1024, token.string);
		}
		Q_strcat(script, 1024, " ");
	}
	//Makro - unreachable
	//return qfalse;		// bk001105 - LCC   missing return value
}

// display, window, menu, item code
// 

/*
==================
Init_Display

Initializes the display with a structure to all the drawing routines
 ==================
*/
void Init_Display(displayContextDef_t * dc)
{
	DC = dc;
}

// type and style painting 

void GradientBar_Paint(rectDef_t * rect, vec4_t color)
{
	// gradient bar takes two paints
	DC->setColor(color);
	DC->drawHandlePic(rect->x, rect->y, rect->w, rect->h, DC->Assets.gradientBar);
	DC->setColor(NULL);
}

/*
==================
Window_Init

Initializes a window structure ( windowDef_t ) with defaults
 
==================
*/
void Window_Init(Window * w)
{
	memset(w, 0, sizeof(windowDef_t));
	w->borderSize = 1;
	w->foreColor[0] = w->foreColor[1] = w->foreColor[2] = w->foreColor[3] = 1.0;
	w->cinematic = -1;
}

void Fade(int *flags, float *f, float clamp, int *nextTime, int offsetTime, qboolean bFlags, float fadeAmount)
{
	if (*flags & (WINDOW_FADINGOUT | WINDOW_FADINGIN)) {
		if (DC->realTime > *nextTime) {
			*nextTime = DC->realTime + offsetTime;
			if (*flags & WINDOW_FADINGOUT) {
				*f -= fadeAmount;
				if (bFlags && *f <= 0.0) {
					*flags &= ~(WINDOW_FADINGOUT | WINDOW_VISIBLE);
				}
			} else {
				*f += fadeAmount;
				if (*f >= clamp) {
					*f = clamp;
					if (bFlags) {
						*flags &= ~WINDOW_FADINGIN;
					}
				}
			}
		}
	}
}

//Makro - new fading method
//TODO: support for border and overlay colors
void UI_RQ3_HandleFading(Window * w)
{
	if (w) {
		if ((w->timeFade.active)) {
			if (DC->realTime > w->timeFade.endTime) {
				w->timeFade.active = qfalse;
				if (FORECOLOR == w->timeFade.colorType) {
					memcpy(w->foreColor, w->timeFade.color2, sizeof(vec4_t));
					//autohide
					if (w->foreColor[3] == 0)
						w->flags &= ~WINDOW_VISIBLE;
				} else {
					memcpy(w->backColor, w->timeFade.color2, sizeof(vec4_t));
					//autohide
					if (w->backColor[3] == 0)
						w->flags &= ~WINDOW_VISIBLE;
				}
			} else {
				if (DC->realTime >= w->timeFade.startTime) {
					float frac =
					    ((float) (DC->realTime - w->timeFade.startTime)) /
					    ((float) (w->timeFade.endTime - w->timeFade.startTime));
					qboolean forecolor = (w->timeFade.colorType == FORECOLOR);
					if (forecolor) {
						LerpColor(w->timeFade.color1, w->timeFade.color2, w->foreColor, frac);
					} else {
						LerpColor(w->timeFade.color1, w->timeFade.color2, w->backColor, frac);
					}
				}
			}
		}
	}
}

void Window_Paint(Window * w, float fadeAmount, float fadeClamp, float fadeCycle)
{
	//float bordersize = 0;
	vec4_t color = {1, 1, 1, 1};
	rectDef_t fillRect = w->rect;

	if (debugMode) {
		//color[0] = color[1] = color[2] = color[3] = 1;
		//Makro - added shader parm
		DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, 1, color, DC->whiteShader);
	}

	if (w == NULL) {
		return;
	}

	//Makro - fade forecolor/backcolor if needed
	UI_RQ3_HandleFading(w);

	//Makro - drawing drop shadow effect
	if (w->shadowStyle == 1) {
		color[0] = color[1] = color[2] = color[3] = 1;
		DC->setColor(color);
		//Top right corner
		DC->drawHandlePic(w->rect.x + w->rect.w, w->rect.y + DROP_SHADOW_OFFSET, DROP_SHADOW_SIZE,
				  DROP_SHADOW_SIZE, DC->Assets.dropShadowCorners[1]);
		//Right side
		DC->drawHandlePic(w->rect.x + w->rect.w, w->rect.y + DROP_SHADOW_OFFSET + DROP_SHADOW_SIZE,
				  DROP_SHADOW_SIZE, w->rect.h - DROP_SHADOW_OFFSET - DROP_SHADOW_SIZE,
				  DC->Assets.dropShadowRight);
		//Bottom right corner
		DC->drawHandlePic(w->rect.x + w->rect.w, w->rect.y + w->rect.h, DROP_SHADOW_SIZE, DROP_SHADOW_SIZE,
				  DC->Assets.dropShadowCorners[2]);
		//Bottom side
		DC->drawHandlePic(w->rect.x + DROP_SHADOW_OFFSET + DROP_SHADOW_SIZE, w->rect.y + w->rect.h,
				  w->rect.w - DROP_SHADOW_OFFSET - DROP_SHADOW_SIZE, DROP_SHADOW_SIZE,
				  DC->Assets.dropShadowBottom);
		//Bottom left corner
		DC->drawHandlePic(w->rect.x + DROP_SHADOW_OFFSET, w->rect.y + w->rect.h, DROP_SHADOW_SIZE,
				  DROP_SHADOW_SIZE, DC->Assets.dropShadowCorners[3]);
	}

	if (w->style == 0 && w->border == 0) {
		return;
	}

	if (w->border != 0) {
		fillRect.x += w->borderSize;
		fillRect.y += w->borderSize;
		fillRect.w -= w->borderSize + 1;
		fillRect.h -= w->borderSize + 1;
	}

	if (w->style == WINDOW_STYLE_FILLED) {
		// box, but possible a shader that needs filled
		if (w->background) {
			Fade(&w->flags, &w->backColor[3], fadeClamp, &w->nextTime, fadeCycle, qtrue, fadeAmount);
			DC->setColor(w->backColor);
			//Makro - angled?
			if (w->rectClient.hasVectors)
			{
				DC->drawAngledPic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->rectClient.u, w->rectClient.v, w->backColor, 0, 0, 1, 1, w->background);
			} else {
				DC->drawHandlePic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->background);
			}
			DC->setColor(NULL);
		} else {
			//angled?
			if (w->rectClient.hasVectors)
			{
				DC->drawAngledPic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->rectClient.u, w->rectClient.v, w->backColor, 0, 0, 1, 1, DC->whiteShader);
			} else {
				DC->fillRect(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->backColor);
			}
		}
	} else if (w->style == WINDOW_STYLE_GRADIENT) {
		GradientBar_Paint(&fillRect, w->backColor);
		// gradient bar
	} else if (w->style == WINDOW_STYLE_SHADER) {
		float coords[4] = {0, 0, 1, 1};
		// randomized texture co-ordinates?
		if (w->flags & WINDOW_RANDOM_TCGEN)
		{
			coords[0] = (rand() % 45) / 90.0f;
			coords[1] = (rand() % 45) / 90.0f;
			coords[2] = coords[0] + 0.5f ;
			coords[3] = coords[1] + 0.5f;
			if (rand() % 2)
			{
				coords[0] = 1 - coords[0];
				coords[2] = 1 - coords[2];
			}
			if (rand() % 2)
			{
				coords[1] = 1 - coords[1];
				coords[3] = 1 - coords[3];
			}
		}
		if (w->flags & WINDOW_FORECOLORSET) {
			DC->setColor(w->foreColor);
			memcpy(&color[0], &w->foreColor[0], sizeof(color));
		}
		//Makro - angled?
		if (w->rectClient.hasVectors)
		{
			DC->drawAngledPic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->rectClient.u, w->rectClient.v, w->foreColor, coords[0], coords[1], coords[2], coords[3], w->background);
		} else {
			//DC->drawHandlePic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->background);
			DC->drawStretchPic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, coords[0], coords[1], coords[2], coords[3], w->background, qtrue);
		}
		DC->setColor(NULL);
	} else if (w->style == WINDOW_STYLE_TEAMCOLOR) {
		if (DC->getTeamColor) {
			DC->getTeamColor(&color);
			DC->fillRect(fillRect.x, fillRect.y, fillRect.w, fillRect.h, color);
		}
	} else if (w->style == WINDOW_STYLE_CINEMATIC) {
		if (w->cinematic == -1) {
			w->cinematic =
				DC->playCinematic(w->cinematicName, fillRect.x, fillRect.y, fillRect.w, fillRect.h);
			if (w->cinematic == -1) {
				w->cinematic = -2;
			}
		}
		if (w->cinematic >= 0) {
			DC->runCinematicFrame(w->cinematic);
			DC->drawCinematic(w->cinematic, fillRect.x, fillRect.y, fillRect.w, fillRect.h);
		}
	}

	if (w->border == WINDOW_BORDER_FULL) {
		// full
		// HACK HACK HACK
		if (w->style == WINDOW_STYLE_TEAMCOLOR)
		{
			if (color[0] > 0) {
				// red
				color[0] = 1;
				color[1] = color[2] = .5;

			} else {
				color[2] = 1;
				color[0] = color[1] = .5;
			}
			color[3] = 1;
			if (w->rectClient.hasVectors)
			{
				//Makro - added shader parm
				DC->drawAngledRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->rect.u, w->rect.v,
					w->borderSize, color, RECT_FULL, DC->whiteShader);
			} else {
				//Makro - added shader parm
				DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, color, DC->whiteShader);
			}
		} else {
			if (w->rectClient.hasVectors)
			{
				//Makro - added shader parm
				DC->drawAngledRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->rect.u, w->rect.v,
					w->borderSize, w->borderColor, RECT_FULL, DC->whiteShader);
			} else {
				//Makro - added shader parm
				DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, w->borderColor, DC->whiteShader);
			}
		}
	} else if (w->border == WINDOW_BORDER_HORZ) {
		// top/bottom
		DC->setColor(w->borderColor);
		//Makro - added shader parm
		DC->drawTopBottom(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, DC->whiteShader);
		DC->setColor(NULL);
	} else if (w->border == WINDOW_BORDER_VERT) {
		// left right
		DC->setColor(w->borderColor);
		//Makro - added shader parm
		DC->drawSides(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, DC->whiteShader);
		DC->setColor(NULL);
	} else if (w->border == WINDOW_BORDER_KCGRADIENT) {
		// this is just two gradient bars along each horz edge
		rectDef_t r = w->rect;

		r.h = w->borderSize;
		GradientBar_Paint(&r, w->borderColor);
		r.y = w->rect.y + w->rect.h - 1;
		GradientBar_Paint(&r, w->borderColor);
	}
}

void Item_SetScreenCoords(itemDef_t * item, float x, float y)
{

	if (item == NULL) {
		return;
	}

	if (item->window.border != 0) {
		if (item->window.rectClient.hasVectors)
		{
			x += item->window.borderSize * (item->window.rectClient.u[0] + item->window.rectClient.v[0]);
			y += item->window.borderSize * (item->window.rectClient.u[1] + item->window.rectClient.v[1]);
		} else {
			x += item->window.borderSize;
			y += item->window.borderSize;
		}
	}

	item->window.rect.x = x + item->window.rectClient.x;
	item->window.rect.y = y + item->window.rectClient.y;
	item->window.rect.w = item->window.rectClient.w;
	item->window.rect.h = item->window.rectClient.h;

	// force the text rects to recompute
	item->textRect.w = 0;
	item->textRect.h = 0;
}

// FIXME: consolidate this with nearby stuff
void Item_UpdatePosition(itemDef_t * item)
{
	float x, y;
	menuDef_t *menu;

	if (item == NULL || item->parent == NULL) {
		return;
	}

	menu = item->parent;

	x = menu->window.rect.x;
	y = menu->window.rect.y;

	if (menu->window.border != 0) {
		//Makro - got vectors?
		if (menu->window.rectClient.hasVectors)
		{
			x += menu->window.borderSize * (menu->window.rectClient.u[0] + menu->window.rectClient.v[0]);
			y += menu->window.borderSize * (menu->window.rectClient.u[1] + menu->window.rectClient.v[1]);
		} else {
			x += menu->window.borderSize;
			y += menu->window.borderSize;
		}
	}

	Item_SetScreenCoords(item, x, y);

}

// menus
void Menu_UpdatePosition(menuDef_t * menu)
{
	int i;
	float x, y;

	if (menu == NULL) {
		return;
	}

	x = menu->window.rect.x;
	y = menu->window.rect.y;
	if (menu->window.border != 0) {
		x += menu->window.borderSize;
		y += menu->window.borderSize;
	}

	for (i = 0; i < menu->itemCount; i++) {
		Item_SetScreenCoords(menu->items[i], x, y);
	}
}

void Menu_PostParse(menuDef_t * menu)
{
	if (menu == NULL) {
		return;
	}
	if (menu->fullScreen) {
		menu->window.rect.x = 0;
		menu->window.rect.y = 0;
		menu->window.rect.w = 640;
		menu->window.rect.h = 480;
	}
	//Makro - timer is disabled by default
	menu->timerEnabled = qfalse;
	menu->nextTimer = 0;
	menu->timerPos = 0;

	Menu_UpdatePosition(menu);
}

itemDef_t *Menu_ClearFocus(menuDef_t * menu)
{
	int i;
	itemDef_t *ret = NULL;

	if (menu == NULL) {
		return NULL;
	}

	for (i = 0; i < menu->itemCount; i++) {
		if (!(menu->items[i]->window.flags & WINDOW_HASFOCUS))
			continue;

		ret = menu->items[i];
		menu->items[i]->window.flags &= ~WINDOW_HASFOCUS;
		if (menu->items[i]->leaveFocus) {
			Item_RunScript(menu->items[i], menu->items[i]->leaveFocus);
		}
	}

	return ret;
}

static qboolean IsVisible(int flags)
{
	return (flags & WINDOW_VISIBLE && !(flags & WINDOW_FADINGOUT));
}

qboolean Rect_ContainsPoint(rectDef_t * rect, float x, float y)
{
	if (rect) {
		float px, py;
		Rect_ToInnerCoords(rect, x, y, &px, &py);
		if (px > 0 && px < rect->w && py > 0 && py < rect->h)
		{
			return qtrue;
		}
	}
	return qfalse;
}

/*
========================================
ItemMatchesString

Returns true if any of the tokens in the
name, group or subgroup fields of the given
items (param #1) matches any of the tokens
in the given string (param #2)

Added by Makro
========================================
*/
ID_INLINE qboolean ItemMatchesString(itemDef_t *item, const char *match)
{
	if (!item || !match)
		return qfalse;
	return
		(item->window.name		&& IdMatchesString(item->window.name, match)) ||
		(item->window.group		&& IdMatchesString(item->window.group, match)) ||
		(item->window.subgroup	&& IdMatchesString(item->window.subgroup, match));
}


int Menu_ItemsMatchingGroup(menuDef_t * menu, const char *name)
{
	int i;
	int count = 0;

	//Makro - added subgroup
	//10-14-2005 - new code
	for (i = 0; i < menu->itemCount; i++)
	{
		if (ItemMatchesString(menu->items[i], name))
			count++;
	}
	return count;
}

itemDef_t *Menu_GetMatchingItemByNumber(menuDef_t * menu, int index, const char *name)
{
	int i;
	int count = 0;

	//Makro - added subgroup
	//10-14-2005 - new code
	for (i = 0; i < menu->itemCount; i++)
	{
		if (ItemMatchesString(menu->items[i], name))
		{
			if (count == index)
				return menu->items[i];
			count++;
		}
	}
	return NULL;
}

//Makro - fade overlay
void Script_FadeOverlay(itemDef_t *item, char **args)
{
	int offset, duration;
	float f;

	//color
	for (offset=0; offset<4; offset++)
	{
		if (!Float_Parse(args, &f))
			return;

		DC->overlayColor[offset] = DC->overlayColor2[offset];
		if (IsBetween(f, 0, 1))
			DC->overlayColor2[offset] = f;
	}

	//offset & duration
	if (!Int_Parse(args, &offset) || !Int_Parse(args, &duration))
		return;

	DC->overlayFadeStart = DC->realTime + offset;
	DC->overlayFadeEnd = DC->overlayFadeStart + duration;
}

void Script_SetOverlayColor(itemDef_t *item, char **args)
{
	int i;
	float f;

	for (i=0; i<4; i++)
	{
		if (!Float_Parse(args, &f))
			return;

		if (IsBetween(f, 0, 1))
			DC->overlayColor2[i] = f;
	}
	DC->overlayFadeStart = DC->overlayFadeEnd = 0;
}

void Script_SetColor(itemDef_t * item, char **args)
{
	const char *name;
	int i;
	float f;
	vec4_t *out;

	// expecting type of color to set and 4 args for the color
	if (String_Parse(args, &name)) {
		out = NULL;
		if (Q_stricmp(name, "backcolor") == 0) {
			out = &item->window.backColor;
			item->window.flags |= WINDOW_BACKCOLORSET;
		} else if (Q_stricmp(name, "forecolor") == 0) {
			out = &item->window.foreColor;
			item->window.flags |= WINDOW_FORECOLORSET;
		} else if (Q_stricmp(name, "bordercolor") == 0) {
			out = &item->window.borderColor;
		}

		if (out) {
			for (i = 0; i < 4; i++) {
				if (!Float_Parse(args, &f)) {
					return;
				}
				//Makro - new feature: out of range = ignore
				if (IsBetween(f, 0, 1))
					(*out)[i] = f;
			}
			//Makro - if the item was fading, stop the fading process
			if (item->window.timeFade.active)
				item->window.timeFade.active = qfalse;
		}
	}
}

//Makro - sets random color
//setrandomcolor <color_name> <count> <r1> <g1> <b1> <a1> <r2> <g2>...
void Script_SetRandomColor(itemDef_t * item, char **args)
{
	const char *name;
	int i, count, rnd;
	float f;
	vec4_t *out;

	if (String_Parse(args, &name)) {
		out = NULL;
		if (Q_stricmp(name, "backcolor") == 0) {
			out = &item->window.backColor;
			item->window.flags |= WINDOW_BACKCOLORSET;
		} else if (Q_stricmp(name, "forecolor") == 0) {
			out = &item->window.foreColor;
			item->window.flags |= WINDOW_FORECOLORSET;
		} else if (Q_stricmp(name, "bordercolor") == 0) {
			out = &item->window.borderColor;
		}

		//Makro - if the item was fading, stop the fading process
		if (item->window.timeFade.active) {
			item->window.timeFade.active = qfalse;
		}
		if (!Int_Parse(args, &count)) {
			return;
		}
		rnd = rand() % count;

		for (i=0; i<count; i++)
		{
			if (out) {
				int j;
				for (j = 0; j < 4; j++) {
					if (!Float_Parse(args, &f)) {
						return;
					}
					if (i == rnd)
					{
						//Makro - new feature: out of range = ignore
						if (IsBetween(f, 0, 1))
							(*out)[j] = f;
					}
				}
			}
		}
	}
}

void Script_SetAsset(itemDef_t * item, char **args)
{
	const char *name;

	// expecting name to set asset to
	if (String_Parse(args, &name)) {
		// check for a model 
		if (item->type == ITEM_TYPE_MODEL) {
		}
	}
}

void Script_SetBackground(itemDef_t * item, char **args)
{
	const char *name;

	// expecting name to set asset to
	if (String_Parse(args, &name)) {
		item->window.background = DC->registerShaderNoMip(name);
	}
}

itemDef_t *Menu_FindItemByName(menuDef_t * menu, const char *p)
{
	int i;

	if (menu == NULL || p == NULL) {
		return NULL;
	}

	for (i = 0; i < menu->itemCount; i++)
	{
		//Makro - replaced Q_stricmp
		if (ItemMatchesString(menu->items[i], p)) {
			return menu->items[i];
		}
	}

	return NULL;
}

void Script_SetTeamColor(itemDef_t * item, char **args)
{
	if (DC->getTeamColor) {
		int i;
		vec4_t color;

		DC->getTeamColor(&color);
		for (i = 0; i < 4; i++) {
			item->window.backColor[i] = color[i];
		}
	}
}

//Makro - sets random color
//setrandomitemcolor <item_name> <color_name> <count> <r1> <g1> <b1> <a1> <r2> <g2>...
void Script_SetRandomItemColor(itemDef_t * item, char **args)
{
	const char *itemname;
	const char *name;
	vec4_t tempColor, color;
	int i, colorCount;
	vec4_t *out;

	if (String_Parse(args, &itemname) && String_Parse(args, &name) && Int_Parse(args, &colorCount)) {
		itemDef_t *item2;
		int j, k, rnd = rand() % colorCount;
		int count = Menu_ItemsMatchingGroup(item->parent, itemname);

		for (k=0; k<colorCount; k++)
		{
			if (!Color_Parse(args, &tempColor)) {
				return;
			}
			if (k == rnd) {
				memcpy(color, tempColor, sizeof(color));
			}
		}

		for (j = 0; j < count; j++) {
			item2 = Menu_GetMatchingItemByNumber(item->parent, j, itemname);
			if (item2 != NULL) {
				out = NULL;
				if (Q_stricmp(name, "backcolor") == 0) {
					out = &item2->window.backColor;
				} else if (Q_stricmp(name, "forecolor") == 0) {
					out = &item2->window.foreColor;
					item2->window.flags |= WINDOW_FORECOLORSET;
				} else if (Q_stricmp(name, "bordercolor") == 0) {
					out = &item2->window.borderColor;
				}

				if (out) {
					for (i = 0; i < 4; i++) {
						//Makro - new feature: out of range = ignore
						if (IsBetween(color[i], 0, 1))
							(*out)[i] = color[i];
					}
					//Makro - if the item was fading, stop the fading process
					if (item2->window.timeFade.active)
						item2->window.timeFade.active = qfalse;
				}
			}
		}
	}
}

void Script_SetItemColor(itemDef_t * item, char **args)
{
	const char *itemname;
	const char *name;
	vec4_t color;
	int i;
	vec4_t *out;

	// expecting type of color to set and 4 args for the color
	if (String_Parse(args, &itemname) && String_Parse(args, &name)) {
		itemDef_t *item2;
		int j;
		int count = Menu_ItemsMatchingGroup(item->parent, itemname);

		if (!Color_Parse(args, &color)) {
			return;
		}

		for (j = 0; j < count; j++) {
			item2 = Menu_GetMatchingItemByNumber(item->parent, j, itemname);
			if (item2 != NULL) {
				out = NULL;
				if (Q_stricmp(name, "backcolor") == 0) {
					out = &item2->window.backColor;
				} else if (Q_stricmp(name, "forecolor") == 0) {
					out = &item2->window.foreColor;
					item2->window.flags |= WINDOW_FORECOLORSET;
				} else if (Q_stricmp(name, "bordercolor") == 0) {
					out = &item2->window.borderColor;
				}

				if (out) {
					for (i = 0; i < 4; i++) {
						//Makro - new feature: out of range = ignore
						if (IsBetween(color[i], 0, 1))
							(*out)[i] = color[i];
					}
					//Makro - if the item was fading, stop the fading process
					if (item2->window.timeFade.active)
						item2->window.timeFade.active = qfalse;
				}
			}
		}
	}
}

//Makro - added
void Menu_ShowItem(itemDef_t *item, qboolean bShow)
{
	if (item != NULL) {
		if (bShow) {
			item->window.flags |= WINDOW_VISIBLE;
		} else {
			item->window.flags &= ~WINDOW_VISIBLE;
			// stop cinematics playing in the window
			if (item->window.cinematic >= 0) {
				DC->stopCinematic(item->window.cinematic);
				item->window.cinematic = -1;
			}
		}
	}
}

void Menu_ShowItemByName(menuDef_t * menu, const char *p, qboolean bShow)
{
	itemDef_t *item;
	int i;
	int count = Menu_ItemsMatchingGroup(menu, p);

	for (i = 0; i < count; i++) {
		item = Menu_GetMatchingItemByNumber(menu, i, p);
		Menu_ShowItem(item, bShow);
	}
}

void Menu_FadeItemByName(menuDef_t * menu, const char *p, qboolean fadeOut)
{
	itemDef_t *item;
	int i;
	int count = Menu_ItemsMatchingGroup(menu, p);

	for (i = 0; i < count; i++) {
		item = Menu_GetMatchingItemByNumber(menu, i, p);
		if (item != NULL) {
			if (fadeOut) {
				item->window.flags |= (WINDOW_FADINGOUT | WINDOW_VISIBLE);
				item->window.flags &= ~WINDOW_FADINGIN;
			} else {
				item->window.flags |= (WINDOW_VISIBLE | WINDOW_FADINGIN);
				item->window.flags &= ~WINDOW_FADINGOUT;
			}
		}
	}
}

menuDef_t *Menus_FindByName(const char *p)
{
	int i;

	for (i = 0; i < menuCount; i++) {
		if (Q_stricmp(Menus[i].window.name, p) == 0) {
			return &Menus[i];
		}
	}
	return NULL;
}

void Menus_ShowByName(const char *p)
{
	menuDef_t *menu = Menus_FindByName(p);

	if (menu) {
		Menus_Activate(menu);
	}
}

//Makro - added second parameter
void Menus_OpenByName(const char *p, qboolean special)
{
	Menus_ActivateByName(p, special);
}

static void Menu_RunCloseScript(menuDef_t * menu)
{
	if (menu && menu->window.flags & WINDOW_VISIBLE && menu->onClose) {
		itemDef_t item;

		item.parent = menu;
		Item_RunScript(&item, menu->onClose);
	}
}

//Makro - closes a menu
void Menus_Close(menuDef_t *menu)
{
	int i;

	if (!menu)
		return;

	for (i=0; i<openMenuCount; i++)
	{
		if (menuStack[i] == menu)
		{
			openMenuCount--;
			while (i < openMenuCount)
			{
				menuStack[i] = menuStack[i+1];
				i++;
			}
			break;
		}
	}
	if (g_anchoredMenu == menu)
		g_anchoredMenu = NULL;
	Menu_RunCloseScript(menu);
	menu->window.flags &= ~(WINDOW_HASFOCUS | WINDOW_VISIBLE);
}

void Menus_CloseByName(const char *p)
{
	menuDef_t *menu = Menus_FindByName(p);

	if (menu != NULL) {
		Menus_Close(menu);
	}
}

void Menus_CloseAll()
{
	int i;

	for (i = 0; i < menuCount; i++) {
		Menus_Close(&Menus[i]);
	}
}

void Script_Show(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		//Makro - if name is "_self", show current item
		if (!Q_stricmp(name, "_self")) {
			Menu_ShowItem(item, qtrue);
		} else {
			Menu_ShowItemByName(item->parent, name, qtrue);
		}
	}
}

void Script_Hide(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		//Makro - if name is "_self", hide current item
		if (!Q_stricmp(name, "_self")) {
			Menu_ShowItem(item, qfalse);
		} else {
			Menu_ShowItemByName(item->parent, name, qfalse);
		}
	}
}

//Makro - for the new fading method
void UI_RQ3_TimeFadeItem(itemDef_t * item, vec4_t endColor, int offset, int duration, colorType_t colorType)
{
	int i;

	if (duration <= 0) {
		duration = 1;
	}

	if (colorType == FORECOLOR) {
		memcpy(item->window.timeFade.color1, item->window.foreColor, sizeof(vec4_t));
		item->window.flags |= WINDOW_FORECOLORSET;
	} else {
		memcpy(item->window.timeFade.color1, item->window.backColor, sizeof(vec4_t));
		item->window.flags |= WINDOW_BACKCOLORSET;
	}
	for (i=0; i<4; i++)
	{
		//Makro - new feature: out of range = ignore
		if (IsBetween(endColor[i], 0, 1)) {
			item->window.timeFade.color2[i] = endColor[i];
		} else {
			item->window.timeFade.color2[i] = item->window.timeFade.color1[i];
		}
	}

	item->window.timeFade.active = qtrue;
	item->window.timeFade.colorType = colorType;
	item->window.timeFade.startTime = DC->realTime + offset;
	item->window.timeFade.endTime = item->window.timeFade.startTime + duration;
	/*
	   if (item->window.timeFade.forecolor) {
	   DC->Print(va("^3Fading forecolor %s: src=(%f %f %f %f) dst=(%f %f %f %f) offset=%i duration=%i start=%i end=%i^7\n", item->window.name, item->window.timeFade.color1[0], item->window.timeFade.color1[1], item->window.timeFade.color1[2], item->window.timeFade.color1[3], endColor[0], endColor[1], endColor[2], endColor[3], offset, duration, item->window.timeFade.startTime, item->window.timeFade.endTime));
	   } else {
	   DC->Print(va("^3Fading backcolor %s: src=(%f %f %f %f) dst=(%f %f %f %f) offset=%i duration=%i start=%i end=%i^7\n", item->window.name, item->window.timeFade.color1[0], item->window.timeFade.color1[1], item->window.timeFade.color1[2], item->window.timeFade.color1[3], endColor[0], endColor[1], endColor[2], endColor[3], offset, duration, item->window.timeFade.startTime, item->window.timeFade.endTime));
	   }
	 */
}
void Menu_TimeFadeItemByName(menuDef_t * menu, const char *name, vec4_t endColor, int offset, int duration,
			     colorType_t colorType)
{
	if (menu) {
		int i;

		//if (offset+duration > 0) {

		//Makro - added subgroup
		//10-14-2005 - new code
		for (i = 0; i < menu->itemCount; i++)
		{
			if (ItemMatchesString(menu->items[i], name))
				UI_RQ3_TimeFadeItem(menu->items[i], endColor, offset, duration, colorType);
		}
		//}
	}
}

//Makro - syntax: timeFade <name> { "forecolor" | 'backcolor" } <toColor> <offset> <duration>
void Script_TimeFade(itemDef_t * item, char **args)
{
	const char *name, *isForeColor;
	int offset, duration;
	vec4_t endColor;

	if (String_Parse(args, &name)) {
		if (String_Parse(args, &isForeColor)) {
			if (Color_Parse(args, &endColor)) {
				if (Int_Parse(args, &offset)) {
					if (Int_Parse(args, &duration)) {
						if (!Q_stricmp(isForeColor, "forecolor")) {
							Menu_TimeFadeItemByName(item->parent, name, endColor, offset,
										duration, FORECOLOR);
						} else {
							Menu_TimeFadeItemByName(item->parent, name, endColor, offset,
										duration, BACKCOLOR);
						}
					}
				}
			}
		}
	}
}
void Script_TimeFadeSelf(itemDef_t * item, char **args)
{
	const char *isForeColor;
	int offset, duration;
	vec4_t endColor;

	if (String_Parse(args, &isForeColor)) {
		if (Color_Parse(args, &endColor)) {
			if (Int_Parse(args, &offset)) {
				if (Int_Parse(args, &duration)) {
					if (!Q_stricmp(isForeColor, "forecolor")) {
						UI_RQ3_TimeFadeItem(item, endColor, offset, duration, FORECOLOR);
					} else {
						UI_RQ3_TimeFadeItem(item, endColor, offset, duration, BACKCOLOR);
					}
				}
			}
		}
	}
}

void Script_FadeIn(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		Menu_FadeItemByName(item->parent, name, qfalse);
	}
}

void Script_FadeOut(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		Menu_FadeItemByName(item->parent, name, qtrue);
	}
}

void Script_Open(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		//Makro - previous menu
		if ( (!Q_stricmp(name, "_previous") || !Q_stricmp(name, "_prev")) && prevMenu) {
			Menus_OpenByName(prevMenu->window.name, qfalse);
		} else {
			Menus_OpenByName(name, qfalse);
		}
		prevMenu = (menuDef_t*)item->parent;
	}
}

void Script_ConditionalOpen(itemDef_t * item, char **args)
{
	const char *cvar;
	const char *name1;
	const char *name2;
	float val;

	if (String_Parse(args, &cvar) && String_Parse(args, &name1) && String_Parse(args, &name2)) {
		val = DC->getCVarValue(cvar);
		if (val == 0.f) {
			Menus_OpenByName(name2, qfalse);
		} else {
			Menus_OpenByName(name1, qfalse);
		}
	}
}

void Script_Close(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		//Makro - if name is "_self", close current menu
		if (Q_stricmp(name, "_self") == 0)
		{
			menuDef_t *menu = (menuDef_t*)item->parent;
			Menus_CloseByName(menu->window.name);
		} else {
			Menus_CloseByName(name);
		}
	}
}

//Makro - opens a menu and runs its "special" script
void Script_OpenSpecial(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		//Makro - previous menu
		if ( (!Q_stricmp(name, "_previous") || !Q_stricmp(name, "_prev")) && prevMenu) {
			Menus_OpenByName(prevMenu->window.name, qtrue);
		} else {
			Menus_OpenByName(name, qtrue);
		}
		prevMenu = (menuDef_t*)item->parent;
	}
}

void Menu_TransitionItemByName(menuDef_t * menu, const char *p, rectDef_t rectFrom, rectDef_t rectTo, int time,
			       float amt)
{
	itemDef_t *item;
	int i;
	int count = Menu_ItemsMatchingGroup(menu, p);

	for (i = 0; i < count; i++) {
		item = Menu_GetMatchingItemByNumber(menu, i, p);
		if (item != NULL) {
			item->window.flags |= (WINDOW_INTRANSITION | WINDOW_VISIBLE);
			item->window.offsetTime = time;
			//Makro - copy vector info
			rectFrom.hasVectors = item->window.rect.hasVectors;
			Vector2Copy(item->window.rect.u, rectFrom.u);
			Vector2Copy(item->window.rect.v, rectFrom.v);
			//
			rectTo.hasVectors = rectFrom.hasVectors;
			Vector2Copy(rectFrom.u, rectTo.u);
			Vector2Copy(rectFrom.v, rectTo.v);
			//
			memcpy(&item->window.rectClient, &rectFrom, sizeof(rectDef_t));
			memcpy(&item->window.rectEffects, &rectTo, sizeof(rectDef_t));
			item->window.rectEffects2.x = abs(rectTo.x - rectFrom.x) / amt;
			item->window.rectEffects2.y = abs(rectTo.y - rectFrom.y) / amt;
			item->window.rectEffects2.w = abs(rectTo.w - rectFrom.w) / amt;
			item->window.rectEffects2.h = abs(rectTo.h - rectFrom.h) / amt;

			Item_UpdatePosition(item);
		}
	}
}

void Script_Transition(itemDef_t * item, char **args)
{
	const char *name;
	rectDef_t rectFrom, rectTo;
	int time;
	float amt;

	memset(&rectFrom, 0, sizeof(rectFrom));
	memset(&rectTo, 0, sizeof(rectTo));

	if (String_Parse(args, &name)) {
		if (Rect_Parse(args, &rectFrom) && Rect_Parse(args, &rectTo) && Int_Parse(args, &time)
		    && Float_Parse(args, &amt)) {
			Menu_TransitionItemByName(item->parent, name, rectFrom, rectTo, time, amt);
		}
	}
}

void Menu_OrbitItemByName(menuDef_t * menu, const char *p, float x, float y, float cx, float cy, int time)
{
	itemDef_t *item;
	int i;
	int count = Menu_ItemsMatchingGroup(menu, p);

	for (i = 0; i < count; i++) {
		item = Menu_GetMatchingItemByNumber(menu, i, p);
		if (item != NULL) {
			item->window.flags |= (WINDOW_ORBITING | WINDOW_VISIBLE);
			item->window.offsetTime = time;
			item->window.rectEffects.x = cx;
			item->window.rectEffects.y = cy;
			item->window.rectClient.x = x;
			item->window.rectClient.y = y;
			Item_UpdatePosition(item);
		}
	}
}

void Script_Orbit(itemDef_t * item, char **args)
{
	const char *name;
	float cx, cy, x, y;
	int time;

	if (String_Parse(args, &name)) {
		if (Float_Parse(args, &x) && Float_Parse(args, &y) && Float_Parse(args, &cx) && Float_Parse(args, &cy)
		    && Int_Parse(args, &time)) {
			Menu_OrbitItemByName(item->parent, name, x, y, cx, cy, time);
		}
	}
}

qboolean Item_SetFocus(itemDef_t * item, float x, float y, qboolean forced);

void Script_SetFocus(itemDef_t * item, char **args)
{
	const char *name;
	itemDef_t *focusItem;

	if (String_Parse(args, &name)) {
		focusItem = Menu_FindItemByName(item->parent, name);
		//Makro - removed focus/decoration checks - they're done in Item_SetFocus anyway
		if (focusItem)
			Item_SetFocus(focusItem, 0, 0, qtrue);
	}
}

void Script_SetPlayerModel(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		DC->setCVar("team_model", name);
	}
}

void Script_SetPlayerHead(itemDef_t * item, char **args)
{
	const char *name;

	if (String_Parse(args, &name)) {
		DC->setCVar("team_headmodel", name);
	}
}

void Script_SetCvar(itemDef_t * item, char **args)
{
	const char *cvar, *val;

	if (String_Parse(args, &cvar) && String_Parse(args, &val)) {
		DC->setCVar(cvar, val);
	}

}

void Script_Exec(itemDef_t * item, char **args)
{
	const char *val;

	if (String_Parse(args, &val)) {
		DC->executeText(EXEC_APPEND, va("%s ; ", val));
	}
}

void Script_Play(itemDef_t * item, char **args)
{
	const char *val;

	if (String_Parse(args, &val)) {
		DC->startLocalSound(DC->registerSound(val, qfalse), CHAN_LOCAL_SOUND);
	}
}

void Script_playLooped(itemDef_t * item, char **args)
{
	const char *val;

	if (String_Parse(args, &val)) {
		DC->stopBackgroundTrack();
		DC->startBackgroundTrack(val, val);
	}
}

//Makro - stop background track
void Script_stopMusic(itemDef_t * item, char **args)
{
	DC->stopBackgroundTrack();
}

//Makro - timer scripts
void Script_StartTimer(itemDef_t * item, char **args)
{
	menuDef_t *menu = (menuDef_t *) item->parent;

	if (menu) {
		if (menu->timedItems > 0) {
			menu->timerEnabled = qtrue;
			menu->timerPos = 1;
			if (menu->timerInterval <= 0) {
				menu->timerInterval = 1000;
			}
			//go ahead and show the first item
			menu->nextTimer = 0;
		}
	}
}

void Script_StopTimer(itemDef_t * item, char **args)
{
	menuDef_t *menu = (menuDef_t *) item->parent;

	if (menu) {
		menu->timerEnabled = qfalse;
		menu->timerPos = 0;
	}
}

//Makro - for the exit menu
static const char *quitMessages[] =
{
	"Done playing ?",

	"Out already ?",

	"Going somewhere ?",

	"Bed time already ?",

	"Exit Reaction ?",

	"Back to the\n"
	"real world ?",

	"Action heroes\n"
	"never press 'yes'"
};
static const int quitMessageCount = sizeof(quitMessages) / sizeof(const char*);

void Script_SetQuitText(itemDef_t * item, char **args)
{
	menuDef_t *menu = (menuDef_t *) item->parent;
	const char *val;
	if (menu) {
		if (String_Parse(args, &val))
		{
			itemDef_t *toitem = Menu_FindItemByName(menu, val);
			if (toitem)
			{
				toitem->text = quitMessages[rand() % quitMessageCount];
				toitem->textRect.w = 0;
			}
		}
	}
}

commandDef_t commandList[] = {
	//Makro - for timers
	{"startTimer", &Script_StartTimer},			// group/name
	{"restartTimer", &Script_StartTimer},			// group/name
	{"stopTimer", &Script_StopTimer},			// group/name
	//Makro - for the new fading method
	{"timeFade", &Script_TimeFade},
	{"timeFadeSelf", &Script_TimeFadeSelf},
	{"fadein", &Script_FadeIn},			// group/name
	{"fadeout", &Script_FadeOut},			// group/name
	{"show", &Script_Show},			// group/name
	{"hide", &Script_Hide},			// group/name
	{"setcolor", &Script_SetColor},			// works on this
	//Makro - fade in/out overlay
	{"fadeoverlay", &Script_FadeOverlay},
	{"setoverlaycolor", &Script_SetOverlayColor},
	//Makro - sets random color
	{"setrandomcolor", &Script_SetRandomColor},
	{"open", &Script_Open},			// menu
	{"conditionalopen", &Script_ConditionalOpen},			// menu
	{"close", &Script_Close},			// menu
	//Makro - opens a menu and runs its "special" script
	{"openspecial", &Script_OpenSpecial},
	{"setasset", &Script_SetAsset},			// works on this
	{"setbackground", &Script_SetBackground},			// works on this
	{"setitemcolor", &Script_SetItemColor},			// group/name
	//Makro - sets random color
	{"setrandomitemcolor", &Script_SetRandomItemColor},
	{"setteamcolor", &Script_SetTeamColor},			// sets this background color to team color
	{"setfocus", &Script_SetFocus},			// sets this background color to team color
	{"setplayermodel", &Script_SetPlayerModel},			// sets this background color to team color
	{"setplayerhead", &Script_SetPlayerHead},			// sets this background color to team color
	{"transition", &Script_Transition},			// group/name
	{"setcvar", &Script_SetCvar},			// group/name
	{"exec", &Script_Exec},			// group/name
	{"play", &Script_Play},			// group/name
	{"playlooped", &Script_playLooped},			// group/name
	//Makro - stop background track
	{"stopMusic", &Script_stopMusic},
	{"orbit", &Script_Orbit},	// group/name
	//Makro - for the exit menu
	{"setquittext", &Script_SetQuitText}
};

int scriptCommandCount = sizeof(commandList) / sizeof(commandDef_t);

void Item_RunScript(itemDef_t * item, const char *s)
{
	char script[1024], *p;
	int i;
	qboolean bRan;

	memset(script, 0, sizeof(script));
	if (item && s && s[0]) {
		Q_strcat(script, 1024, s);
		p = script;
		INFINITE_LOOP {
			const char *command;

			// expect command then arguments, ; ends command, NULL ends script
			if (!String_Parse(&p, &command)) {
				return;
			}

			if (command[0] == ';' && command[1] == '\0') {
				continue;
			}

			bRan = qfalse;
			for (i = 0; i < scriptCommandCount; i++) {
				if (Q_stricmp(command, commandList[i].name) == 0) {
					(commandList[i].handler(item, &p));
					bRan = qtrue;
					break;
				}
			}
			// not in our auto list, pass to handler
			if (!bRan) {
				DC->runScript(&p);
			}
		}
	}
}

qboolean Item_EnableShowViaCvar(itemDef_t * item, int flag)
{
	char script[1024], *p;

	memset(script, 0, sizeof(script));
	if (item && item->enableCvar && *item->enableCvar && item->cvarTest && *item->cvarTest) {
		char buff[1024];

		DC->getCVarString(item->cvarTest, buff, sizeof(buff));

		Q_strcat(script, 1024, item->enableCvar);
		p = script;
		INFINITE_LOOP {
			const char *val;

			// expect value then ; or NULL, NULL ends list
			if (!String_Parse(&p, &val)) {
				return (item->cvarFlags & flag) ? qfalse : qtrue;
			}

			if (val[0] == ';' && val[1] == '\0') {
				continue;
			}
			// enable it if any of the values are true
			if (item->cvarFlags & flag) {
				if (Q_stricmp(buff, val) == 0) {
					return qtrue;
				}
			} else {
				// disable it if any of the values are true
				if (Q_stricmp(buff, val) == 0) {
					return qfalse;
				}
			}

		}
		//Makro - unreachable
		//return (item->cvarFlags & flag) ? qfalse : qtrue;
	}
	return qtrue;
}

// will optionaly set focus to this item
qboolean Item_SetFocus(itemDef_t * item, float x, float y, qboolean forced)
{
	int i;
	itemDef_t *oldFocus;
	sfxHandle_t *sfx = &DC->Assets.itemFocusSound;
	qboolean playSound = qfalse;
	menuDef_t *parent;	// bk001206: = (menuDef_t*)item->parent;

	// sanity check, non-null, not a decoration and does not already have the focus
	if (item == NULL || item->window.flags & WINDOW_DECORATION || !(item->window.flags & WINDOW_VISIBLE)) {
		return qfalse;
	}

	//Makro - only check focus if not forced
	if (!forced && item->window.flags & WINDOW_HASFOCUS)
		return qfalse;

	// bk001206 - this can be NULL.
	parent = (menuDef_t *) item->parent;

	// items can be enabled and disabled based on cvars
	if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
		return qfalse;
	}

	if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(item, CVAR_SHOW)) {
		return qfalse;
	}

	oldFocus = Menu_ClearFocus(item->parent);

	if (item->type == ITEM_TYPE_TEXT && !forced) {
		rectDef_t r;

		r = item->textRect;
		r.y -= r.h;
		if (Rect_ContainsPoint(&r, x, y)) {
			item->window.flags |= WINDOW_HASFOCUS;
			if (item->focusSound) {
				sfx = &item->focusSound;
			}
			playSound = qtrue;
		} else {
			if (oldFocus) {
				oldFocus->window.flags |= WINDOW_HASFOCUS;
				if (oldFocus->onFocus) {
					Item_RunScript(oldFocus, oldFocus->onFocus);
				}
			}
		}
	} else {
		item->window.flags |= WINDOW_HASFOCUS;
		if (item->onFocus) {
			Item_RunScript(item, item->onFocus);
		}
		if (item->focusSound) {
			sfx = &item->focusSound;
		}
		playSound = qtrue;
	}

	if (playSound && sfx) {
		DC->startLocalSound(*sfx, CHAN_LOCAL_SOUND);
	}

	for (i = 0; i < parent->itemCount; i++) {
		if (parent->items[i] == item) {
			parent->cursorItem = i;
			break;
		}
	}

	return qtrue;
}

int Item_ListBox_MaxScroll(itemDef_t * item)
{
	listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;
	int count = DC->feederCount(item->special);
	int max;

	if (item->window.flags & WINDOW_HORIZONTAL) {
		max = count - (item->window.rect.w / listPtr->elementWidth) + 1;
	} else {
		max = count - (item->window.rect.h / listPtr->elementHeight) + 1;
	}
	if (max < 0) {
		return 0;
	}
	return max;
}

//returns absolute position
int Item_ListBox_ThumbPosition(itemDef_t * item)
{
	float max, pos, size;
	listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;

	max = Item_ListBox_MaxScroll(item);
	//horizontal
	if (item->window.flags & WINDOW_HORIZONTAL) {
		size = item->window.rect.w - (SCROLLBAR_SIZE * 2) - 2;
		if (max > 0) {
			pos = (size - SCROLLBAR_SIZE) / (float) max;
		} else {
			pos = 0;
		}
		pos *= listPtr->startPos;
		return item->window.rect.x + 1 + SCROLLBAR_SIZE + pos;
	//vertical
	} else {
		size = item->window.rect.h - (SCROLLBAR_SIZE * 2) - 2;
		if (max > 0) {
			pos = (size - SCROLLBAR_SIZE) / (float) max;
		} else {
			pos = 0;
		}
		pos *= listPtr->startPos;
		return item->window.rect.y + 1 + SCROLLBAR_SIZE + pos;
	}
}

//returns absolute position
//TODO: return relative position, convert value in drawing function
int Item_ListBox_ThumbDrawPosition(itemDef_t * item)
{
	int min, max;

	//Makro - added thumb condition
	if (itemCapture == item && item->window.flags & WINDOW_LB_THUMB) {
		//horizontal
		if (item->window.flags & WINDOW_HORIZONTAL) {
			//Makro - vectors?
			float px;

			min = SCROLLBAR_SIZE + 1;
			max = item->window.rect.w - 2 * SCROLLBAR_SIZE - 1;
			if (item->window.rect.hasVectors)
			{
				Rect_ToInnerCoords(&item->window.rect, DC->cursorx, DC->cursory, &px, NULL);
				/*
				if (px >= min + SCROLLBAR_SIZE / 2 && px <= max + SCROLLBAR_SIZE / 2) {
					return item->window.rect.x + px - SCROLLBAR_SIZE / 2;
				}
				*/
			} else {	//no vectors
				px = DC->cursorx - item->window.rect.x;
				/*
				if (DC->cursorx >= min + SCROLLBAR_SIZE / 2 && DC->cursorx <= max + SCROLLBAR_SIZE / 2) {
					return DC->cursorx - SCROLLBAR_SIZE / 2;
				}
				*/
			}
			if (px <= min + SCROLLBAR_SIZE / 2)
				return item->window.rect.x + min;
			else if (px >= max + SCROLLBAR_SIZE / 2)
				return item->window.rect.x + max;
			else
				return item->window.rect.x + px - SCROLLBAR_SIZE / 2;
		//vertical
		} else {
			float py;
			//Makro - vectors?
			if (item->window.rect.hasVectors) {
				
				min = SCROLLBAR_SIZE + 1;
				max = item->window.rect.h - 2 * SCROLLBAR_SIZE - 1;
				/*
				py = (DC->cursorx - item->window.rect.x) * item->window.rect.v[0] + 
					(DC->cursory - item->window.rect.y) * item->window.rect.v[1];
				*/
				Rect_ToInnerCoords(&item->window.rect, DC->cursorx, DC->cursory, NULL, &py);
			} else {
				min = SCROLLBAR_SIZE + 1;
				max = item->window.rect.h - 2 * SCROLLBAR_SIZE - 1;
				py = DC->cursory - item->window.rect.y;
				//if (DC->cursory >= min + SCROLLBAR_SIZE / 2 && DC->cursory <= max + SCROLLBAR_SIZE / 2)
				//	return DC->cursory - SCROLLBAR_SIZE / 2;
				//if (DC->cursory <= min + SCROLLBAR_SIZE / 2)
			}
			if (py <= min + SCROLLBAR_SIZE / 2)
				return item->window.rect.y + min;
			else if (py >= max + SCROLLBAR_SIZE / 2)
				return item->window.rect.y + max;
			else
				return item->window.rect.y + py - SCROLLBAR_SIZE / 2;
		}
	}
	return Item_ListBox_ThumbPosition(item);
}

Point Item_Slider_ThumbPosition(itemDef_t * item)
{
	float value, range;
	editFieldDef_t *editDef = item->typeData;
	Point p;

	if (item->text) {
		//Makro - vectors ?
		if (item->textRect.hasVectors)
		{
			float xoffset = item->textRect.w + 8, yoffset = -(item->textRect.h + SLIDER_THUMB_HEIGHT)/2;
			//p.x = item->textRect.x + item->textRect.u[0]*(item->textRect.w + 8) - item->textRect.v[0]*2;
			p.x = item->textRect.x + item->textRect.u[0]*xoffset + item->textRect.v[0]*yoffset;
			//p.y = item->window.rect.y + item->textRect.u[1] * (item->textRect.w + 8) - item->textRect.v[1]*2;
			p.y = item->textRect.y + item->textRect.u[1]*xoffset + item->textRect.v[1]*yoffset;
		} else {
			p.x = item->textRect.x + item->textRect.w + 8;
			p.y = item->textRect.y - (item->textRect.h + SLIDER_THUMB_HEIGHT)/2;
		}
	} else {
		p.x = item->window.rect.x;
		p.y = item->window.rect.y - 2;
	}

	if (editDef == NULL && item->cvar) {
		return p;
	}

	value = DC->getCVarValue(item->cvar);

	if (value < editDef->minVal) {
		value = editDef->minVal;
	} else if (value > editDef->maxVal) {
		value = editDef->maxVal;
	}

	range = editDef->maxVal - editDef->minVal;
	value -= editDef->minVal;
	value /= range;
	//value /= (editDef->maxVal - editDef->minVal);
	value *= SLIDER_WIDTH;
	//vectors
	if (item->textRect.hasVectors)
	{
		p.x += value * item->textRect.u[0];
		p.y += value * item->textRect.u[1];
	} else {
		p.x += value;
	}
	// vm fuckage
	//x = x + (((float)value / editDef->maxVal) * SLIDER_WIDTH);
	return p;
}

int Item_Slider_OverSlider(itemDef_t * item, float x, float y)
{
	rectDef_t r;
	Point p;

	//Makro - copy all info (including vector info)
	//relevant fields will get overwritten
	r = item->textRect;

	//Makro - vectors
	p = Item_Slider_ThumbPosition(item);
	
	if (r.hasVectors)
	{
		r.x = p.x - (SLIDER_THUMB_WIDTH / 2) * r.u[0];
		r.y = p.y - (SLIDER_THUMB_WIDTH / 2) * r.u[1];
	} else {
		r.x = p.x - (SLIDER_THUMB_WIDTH / 2);
		r.y = p.y;
	}
	r.w = SLIDER_THUMB_WIDTH;
	r.h = SLIDER_THUMB_HEIGHT;

	if (Rect_ContainsPoint(&r, x, y)) {
		return WINDOW_LB_THUMB;
	}
	return 0;
}

//Makro - vector support
int Item_ListBox_OverLB(itemDef_t * item, float x, float y)
{
	rectDef_t r;
	listBoxDef_t *listPtr;
	int thumbstart;
	int count;
	float p[2];

	r.hasVectors = item->window.rect.hasVectors;
	Vector2Copy(item->window.rect.u, r.u);
	Vector2Copy(item->window.rect.v, r.v);
	
	count = DC->feederCount(item->special);
	listPtr = (listBoxDef_t *) item->typeData;
	//horizontal
	if (item->window.flags & WINDOW_HORIZONTAL) {
		//vectors?
		if (r.hasVectors) {
			// check if on left arrow
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.h - SCROLLBAR_SIZE, r.v, p);
			r.x = p[0];
			r.y = p[1];
			r.h = r.w = SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_LEFTARROW;
			}
			// check if on right arrow
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE, r.u, p);
			r.x = p[0];
			r.y = p[1];
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_RIGHTARROW;
			}
			// check if on thumb
			thumbstart = Item_ListBox_ThumbPosition(item);
			Vector2MA(p, (thumbstart - item->window.rect.x) - (item->window.rect.w - SCROLLBAR_SIZE), r.u, p);
			r.x = p[0];
			r.y = p[1];
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_THUMB;
			}
			// check if on page down
			Vector2MA(p, SCROLLBAR_SIZE, r.u, p);
			r.x = p[0];
			r.y = p[1];
			r.w = item->window.rect.w - (thumbstart - item->window.rect.x) - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGDN;
			}
			// check if on page up
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.h - SCROLLBAR_SIZE, r.v, p);
			Vector2MA(p, SCROLLBAR_SIZE, r.u, p);
			r.x = p[0];
			r.y = p[1];
			r.w = thumbstart - item->window.rect.x - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGUP;
			}
		//no vectors
		} else {
			// check if on left arrow
			r.x = item->window.rect.x;
			r.y = item->window.rect.y + item->window.rect.h - SCROLLBAR_SIZE;
			r.h = r.w = SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_LEFTARROW;
			}
			// check if on right arrow
			r.x = item->window.rect.x + item->window.rect.w - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_RIGHTARROW;
			}
			// check if on thumb
			thumbstart = Item_ListBox_ThumbPosition(item);
			r.x = thumbstart;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_THUMB;
			}
			r.x = item->window.rect.x + SCROLLBAR_SIZE;
			r.w = thumbstart - r.x;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGUP;
			}
			r.x = thumbstart + SCROLLBAR_SIZE;
			r.w = item->window.rect.x + item->window.rect.w - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGDN;
			}
		}
	//vertical
	} else {
		//vectors?
		if (r.hasVectors) {
			//Makro - TODO: optimize this code
			// check if on left arrow
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE, r.u, p);
			r.h = r.w = SCROLLBAR_SIZE;
			r.x = p[0];
			r.y = p[1];
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_LEFTARROW;
			}
			// check if on right arrow
			Vector2MA(p, item->window.rect.h - SCROLLBAR_SIZE, r.v, p);
			r.x = p[0];
			r.y = p[1];
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_RIGHTARROW;
			}
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE, r.u, p);
			thumbstart = Item_ListBox_ThumbPosition(item);
			Vector2MA(p, thumbstart - item->window.rect.y, r.v, p);
			r.x = p[0];
			r.y = p[1];
			//Com_Printf("Rect: %.1f %.1f %.1f %.1f Point: %.1f %.1f\n", PRINT_RECT(r), x, y);
			//Com_Printf("%.3f %.3f\n", r.w, r.h);
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_THUMB;
			}
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE, r.u, p);
			Vector2MA(p, SCROLLBAR_SIZE, r.v, p);
			r.x = p[0];
			r.y = p[1];
			r.h = thumbstart - item->window.rect.y - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGUP;
			}
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE, r.u, p);
			Vector2MA(p, thumbstart - item->window.rect.y + SCROLLBAR_SIZE, r.v, p);
			r.x = p[0];
			r.y = p[1];
			r.h = item->window.rect.h - (thumbstart - item->window.rect.y) - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGDN;
			}
		//no vectors
		} else {
			r.x = item->window.rect.x + item->window.rect.w - SCROLLBAR_SIZE;
			r.y = item->window.rect.y;
			r.h = r.w = SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_LEFTARROW;
			}
			r.y = item->window.rect.y + item->window.rect.h - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_RIGHTARROW;
			}
			thumbstart = Item_ListBox_ThumbPosition(item);
			r.y = thumbstart;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_THUMB;
			}
			r.y = item->window.rect.y + SCROLLBAR_SIZE;
			r.h = thumbstart - r.y;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGUP;
			}
			r.y = thumbstart + SCROLLBAR_SIZE;
			r.h = item->window.rect.y + item->window.rect.h - SCROLLBAR_SIZE;
			if (Rect_ContainsPoint(&r, x, y)) {
				return WINDOW_LB_PGDN;
			}
		}
	}
	return 0;
}

void Item_ListBox_MouseEnter(itemDef_t * item, float x, float y)
{
	rectDef_t r;
	listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;

	r.hasVectors = item->window.rect.hasVectors;
	Vector2Copy(item->window.rect.u, r.u);
	Vector2Copy(item->window.rect.v, r.v);

	item->window.flags &=
	    ~(WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP | WINDOW_LB_PGDN);
	item->window.flags |= Item_ListBox_OverLB(item, x, y);

	if (item->window.flags & WINDOW_HORIZONTAL) {
		if (!(item->window.flags & (WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP |
			      WINDOW_LB_PGDN))) {
			// check for selection hit as we have exausted buttons and thumb
			if (listPtr->elementStyle == LISTBOX_IMAGE) {
				r.x = item->window.rect.x;
				r.y = item->window.rect.y;
				r.h = item->window.rect.h - SCROLLBAR_SIZE;
				r.w = item->window.rect.w - listPtr->drawPadding;
				if (Rect_ContainsPoint(&r, x, y)) {
					//vectors?
					if (r.hasVectors) {
						float px;
						Rect_ToInnerCoords(&item->window.rect, x, y, &px, NULL);
						listPtr->cursorPos = (int) (px / listPtr->elementWidth) + listPtr->startPos;
					} else {
						listPtr->cursorPos = (int) ((x - r.x) / listPtr->elementWidth) + listPtr->startPos;
					}
					if (listPtr->cursorPos >= listPtr->endPos) {
						listPtr->cursorPos = listPtr->endPos;
					}
					//item->cursorPos = listPtr->cursorPos;
					//DC->feederSelection(item->special, item->cursorPos);
				}
			} else {
				// text hit.. 
			}
		}
	} else {
		if (!(item->window.flags & (WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP |
			WINDOW_LB_PGDN))) {
			r.x = item->window.rect.x;
			r.y = item->window.rect.y;
			r.w = item->window.rect.w - SCROLLBAR_SIZE;
			r.h = item->window.rect.h - listPtr->drawPadding;
			if (Rect_ContainsPoint(&r, x, y)) {
				//vectors?
				if (r.hasVectors) {
					float py;
					Rect_ToInnerCoords(&item->window.rect, x, y, NULL, &py);
					listPtr->cursorPos = (int) ((py - 2) / listPtr->elementHeight) + listPtr->startPos;
				} else {
					listPtr->cursorPos = (int) ((y - 2 - r.y) / listPtr->elementHeight) + listPtr->startPos;
				}
				if (listPtr->cursorPos > listPtr->endPos) {
					listPtr->cursorPos = listPtr->endPos;
				}
			}
		}
	}
}

void Item_MouseEnter(itemDef_t * item, float x, float y)
{
	rectDef_t r;

	if (item) {
		r = item->textRect;
		r.y -= r.h;
		// in the text rect?

		// items can be enabled and disabled based on cvars
		if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
			return;
		}

		if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(item, CVAR_SHOW)) {
			return;
		}

		if (Rect_ContainsPoint(&r, x, y)) {
			if (!(item->window.flags & WINDOW_MOUSEOVERTEXT)) {
				Item_RunScript(item, item->mouseEnterText);
				item->window.flags |= WINDOW_MOUSEOVERTEXT;
			}
			if (!(item->window.flags & WINDOW_MOUSEOVER)) {
				Item_RunScript(item, item->mouseEnter);
				item->window.flags |= WINDOW_MOUSEOVER;
			}

		} else {
			// not in the text rect
			if (item->window.flags & WINDOW_MOUSEOVERTEXT) {
				// if we were
				Item_RunScript(item, item->mouseExitText);
				item->window.flags &= ~WINDOW_MOUSEOVERTEXT;
			}
			if (!(item->window.flags & WINDOW_MOUSEOVER)) {
				Item_RunScript(item, item->mouseEnter);
				item->window.flags |= WINDOW_MOUSEOVER;
			}

			if (item->type == ITEM_TYPE_LISTBOX) {
				Item_ListBox_MouseEnter(item, x, y);
			}
		}
	}
}

void Item_MouseLeave(itemDef_t * item)
{
	if (item) {
		if (item->window.flags & WINDOW_MOUSEOVERTEXT) {
			Item_RunScript(item, item->mouseExitText);
			item->window.flags &= ~WINDOW_MOUSEOVERTEXT;
		}
		Item_RunScript(item, item->mouseExit);
		item->window.flags &= ~(WINDOW_LB_RIGHTARROW | WINDOW_LB_LEFTARROW);
	}
}

itemDef_t *Menu_HitTest(menuDef_t * menu, float x, float y)
{
	int i;

	for (i = 0; i < menu->itemCount; i++) {
		if (Rect_ContainsPoint(&menu->items[i]->window.rect, x, y)) {
			return menu->items[i];
		}
	}
	return NULL;
}

void Item_SetMouseOver(itemDef_t * item, qboolean focus)
{
	if (item) {
		if (focus) {
			item->window.flags |= WINDOW_MOUSEOVER;
		} else {
			item->window.flags &= ~WINDOW_MOUSEOVER;
		}
	}
}

qboolean Item_OwnerDraw_HandleKey(itemDef_t * item, int key)
{
	if (item && DC->ownerDrawHandleKey) {
		return DC->ownerDrawHandleKey(item->window.ownerDraw, item->window.ownerDrawFlags, &item->special, key);
	}
	return qfalse;
}

qboolean Item_ListBox_HandleKey(itemDef_t * item, int key, qboolean down, qboolean force)
{
	listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;
	int count = DC->feederCount(item->special);
	int max, viewmax;
	int ok = force || Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory) ||
		(!UI_IsMouse(key) && item->window.flags & WINDOW_HASFOCUS);
		
	if (!ok)
		return qfalse;

	max = Item_ListBox_MaxScroll(item);
	//horizontal
	if (item->window.flags & WINDOW_HORIZONTAL) {
		viewmax = (item->window.rect.w / listPtr->elementWidth);
		if (key == K_LEFTARROW || key == K_KP_LEFTARROW) {
			if (!listPtr->notselectable) {
				listPtr->cursorPos--;
				if (listPtr->cursorPos < 0) {
					listPtr->cursorPos = 0;
				}
				if (listPtr->cursorPos < listPtr->startPos) {
					//listPtr->startPos = listPtr->cursorPos;
				}
				if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
					//listPtr->startPos = listPtr->cursorPos - viewmax + 1;
				}
				item->cursorPos = listPtr->cursorPos;
				DC->feederSelection(item->special, item->cursorPos);
			} else {
				//listPtr->startPos--;
				if (listPtr->startPos < 0)
					listPtr->startPos = 0;
			}
			return qtrue;
		}
		if (key == K_RIGHTARROW || key == K_KP_RIGHTARROW) {
			if (!listPtr->notselectable) {
				listPtr->cursorPos++;
				if (listPtr->cursorPos < listPtr->startPos) {
					//listPtr->startPos = listPtr->cursorPos;
				}
				if (listPtr->cursorPos >= count) {
					listPtr->cursorPos = count - 1;
				}
				if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
					//listPtr->startPos = listPtr->cursorPos - viewmax + 1;
				}
				item->cursorPos = listPtr->cursorPos;
				DC->feederSelection(item->special, item->cursorPos);
			} else {
				listPtr->startPos++;
				if (listPtr->startPos >= count)
					listPtr->startPos = count - 1;
			}
			return qtrue;
		}
		//vertical
	} else {
		viewmax = (item->window.rect.h / listPtr->elementHeight);
		if (key == K_UPARROW || key == K_KP_UPARROW) {
			if (!listPtr->notselectable) {
				listPtr->cursorPos--;
				if (listPtr->cursorPos < 0) {
					listPtr->cursorPos = 0;
				}
				if (listPtr->cursorPos < listPtr->startPos) {
					listPtr->startPos = listPtr->cursorPos;
				}
				if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
					listPtr->startPos = listPtr->cursorPos - viewmax + 1;
				}
				item->cursorPos = listPtr->cursorPos;
				DC->feederSelection(item->special, item->cursorPos);
			} else {
				listPtr->startPos--;
				if (listPtr->startPos < 0)
					listPtr->startPos = 0;
			}
			return qtrue;
		}
		if (key == K_DOWNARROW || key == K_KP_DOWNARROW) {
			if (!listPtr->notselectable) {
				listPtr->cursorPos++;
				if (listPtr->cursorPos < listPtr->startPos) {
					listPtr->startPos = listPtr->cursorPos;
				}
				if (listPtr->cursorPos >= count) {
					listPtr->cursorPos = count - 1;
				}
				if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
					listPtr->startPos = listPtr->cursorPos - viewmax + 1;
				}
				item->cursorPos = listPtr->cursorPos;
				DC->feederSelection(item->special, item->cursorPos);
			} else {
				listPtr->startPos++;
				if (listPtr->startPos > max)
					listPtr->startPos = max;
			}
			return qtrue;
		}
	}
	// mouse hit
	if (key == K_MOUSE1 || key == K_MOUSE2) {
		if (item->window.flags & WINDOW_LB_LEFTARROW) {
			listPtr->startPos--;
			if (listPtr->startPos < 0) {
				listPtr->startPos = 0;
			}
		} else if (item->window.flags & WINDOW_LB_RIGHTARROW) {
			// one down
			listPtr->startPos++;
			if (listPtr->startPos > max) {
				listPtr->startPos = max;
			}
		} else if (item->window.flags & WINDOW_LB_PGUP) {
			// page up
			listPtr->startPos -= viewmax;
			if (listPtr->startPos < 0) {
				listPtr->startPos = 0;
			}
		} else if (item->window.flags & WINDOW_LB_PGDN) {
			// page down
			listPtr->startPos += viewmax;
			if (listPtr->startPos > max) {
				listPtr->startPos = max;
			}
		} else if (item->window.flags & WINDOW_LB_THUMB) {
			// Display_SetCaptureItem(item);
		} else {
			//Makro - double click only if we didn't select another item
			//Com_Printf("POZ: %d %d / START: %d / END: %d\n", listPtr->cursorPos, item->cursorPos,
			//	listPtr->startPos, listPtr->endPos);
			if (item->cursorPos != listPtr->cursorPos)
			{
				item->cursorPos = listPtr->cursorPos;
				DC->feederSelection(item->special, item->cursorPos);
			} else {
				if (DC->realTime < lastListBoxClickTime && listPtr->doubleClick)
				{
					Item_RunScript(item, listPtr->doubleClick);
				}
			}
			lastListBoxClickTime = DC->realTime + DOUBLE_CLICK_DELAY;
		}
		return qtrue;
	}
	if (key == K_HOME || key == K_KP_HOME) {
		// home
		listPtr->startPos = 0;
		return qtrue;
	}
	if (key == K_END || key == K_KP_END) {
		// end
		listPtr->startPos = max;
		return qtrue;
	}
	//Makro - support for mouse wheel
	if (key == K_PGUP || key == K_KP_PGUP || key == K_MWHEELUP) {
		// page up
		if (!listPtr->notselectable) {
			listPtr->cursorPos -= viewmax;
			if (listPtr->cursorPos < 0) {
				listPtr->cursorPos = 0;
			}
			if (listPtr->cursorPos < listPtr->startPos) {
				listPtr->startPos = listPtr->cursorPos;
			}
			if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
				listPtr->startPos = listPtr->cursorPos - viewmax + 1;
			}
			item->cursorPos = listPtr->cursorPos;
			DC->feederSelection(item->special, item->cursorPos);
		} else {
			listPtr->startPos -= viewmax;
			if (listPtr->startPos < 0) {
				listPtr->startPos = 0;
			}
		}
		return qtrue;
	}
	//Makro - support for mouse wheel
	if (key == K_PGDN || key == K_KP_PGDN || key == K_MWHEELDOWN) {
		// page down
		if (!listPtr->notselectable) {
			listPtr->cursorPos += viewmax;
			if (listPtr->cursorPos < listPtr->startPos) {
				listPtr->startPos = listPtr->cursorPos;
			}
			if (listPtr->cursorPos >= count) {
				listPtr->cursorPos = count - 1;
			}
			if (listPtr->cursorPos >= listPtr->startPos + viewmax) {
				listPtr->startPos = listPtr->cursorPos - viewmax + 1;
			}
			item->cursorPos = listPtr->cursorPos;
			DC->feederSelection(item->special, item->cursorPos);
		} else {
			listPtr->startPos += viewmax;
			if (listPtr->startPos > max) {
				listPtr->startPos = max;
			}
		}
		return qtrue;
	}
	return qfalse;
}

qboolean Item_YesNo_HandleKey(itemDef_t * item, int key)
{
	yesnoDef_t *data = (yesnoDef_t*)item->typeData;
	qboolean ok = qfalse;

	//Makro - an item should react to key presses even if the mouse isn't over it
	if (item->window.flags & WINDOW_HASFOCUS && item->cvar) {
		if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3) {
			if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory)) {
				ok = qtrue;
			}
		} else {
			if (key == K_ENTER || key == K_LEFTARROW || key == K_RIGHTARROW ||
				key == K_MWHEELUP || key == K_MWHEELDOWN) {
				ok = qtrue;
			}
		}
	}

	if (ok) {
		//Makro - grouped checkboxes?
		if (data->groupIndex)
		{
			DC->setCVar(item->cvar, va("%f", data->activeCvarVal));
		} else {
			DC->setCVar(item->cvar, va("%i", !DC->getCVarValue(item->cvar)));
		}
		return qtrue;
	}

	return qfalse;
}

int Item_Multi_CountSettings(itemDef_t * item)
{
	multiDef_t *multiPtr = (multiDef_t *) item->typeData;

	if (multiPtr == NULL) {
		return 0;
	}
	return multiPtr->count;
}

int Item_Multi_FindCvarByValue(itemDef_t * item)
{
	char buff[1024];
	float value = 0;
	int i;
	multiDef_t *multiPtr = (multiDef_t *) item->typeData;

	if (multiPtr) {
		if (multiPtr->strDef) {
			DC->getCVarString(item->cvar, buff, sizeof(buff));
		} else {
			value = DC->getCVarValue(item->cvar);
		}
		for (i = 0; i < multiPtr->count; i++) {
			if (multiPtr->strDef) {
				if (Q_stricmp(buff, multiPtr->cvarStr[i]) == 0) {
					return i;
				}
			} else {
				if (multiPtr->cvarValue[i] == value) {
					return i;
				}
			}
		}
	}
	return 0;
}

const char *Item_Multi_Setting(itemDef_t * item)
{
	char buff[1024];
	float value = 0;
	int i;
	multiDef_t *multiPtr = (multiDef_t *) item->typeData;

	if (multiPtr) {
		if (multiPtr->strDef) {
			DC->getCVarString(item->cvar, buff, sizeof(buff));
		} else {
			value = DC->getCVarValue(item->cvar);
		}
		for (i = 0; i < multiPtr->count; i++) {
			if (multiPtr->strDef) {
				if (Q_stricmp(buff, multiPtr->cvarStr[i]) == 0) {
					return multiPtr->cvarList[i];
				}
			} else {
				if (multiPtr->cvarValue[i] == value) {
					return multiPtr->cvarList[i];
				}
			}
		}
	}
	//Makro - changed from "" to NULL
	return NULL;
}

qboolean Item_Multi_HandleKey(itemDef_t * item, int key)
{
	multiDef_t *multiPtr = (multiDef_t *) item->typeData;

	//Makro - added support for left/right keys
	//made it so that the mouse pointer doesn't have to be over the item
	qboolean ok = qfalse;

	if (multiPtr) {
		if (item->window.flags & WINDOW_HASFOCUS && item->cvar) {
			if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3) {
				if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory)) {
					ok = qtrue;
				}
			} else {
				if (key == K_ENTER || key == K_LEFTARROW || key == K_RIGHTARROW || key == K_HOME
				    || key == K_END || key == K_MWHEELUP || key == K_MWHEELDOWN) {
					ok = qtrue;
				}
			}
		}
	}

	if (ok) {
		int current;
		int max = Item_Multi_CountSettings(item);

		switch (key) {
		case K_LEFTARROW:
		case K_MWHEELDOWN:
		case K_MOUSE2:
			current = Item_Multi_FindCvarByValue(item) - 1;
			break;
		case K_HOME:
			current = 0;
			break;
		case K_END:
			current = max - 1;
			break;
		default:
			current = Item_Multi_FindCvarByValue(item) + 1;
			break;
		}

		if (current < 0) {
			current = max - 1;
		} else {
			if (current >= max) {
				current = 0;
			}
		}

		if (multiPtr->strDef) {
			DC->setCVar(item->cvar, multiPtr->cvarStr[current]);
		} else {
			float value = multiPtr->cvarValue[current];

			if (((float) ((int) value)) == value) {
				DC->setCVar(item->cvar, va("%i", (int) value));
			} else {
				DC->setCVar(item->cvar, va("%f", value));
			}
		}

		return qtrue;
	}

	return qfalse;
}

qboolean Item_TextField_HandleKey(itemDef_t * item, int key)
{
	char buff[1024];
	int len;
	itemDef_t *newItem = NULL;
	editFieldDef_t *editPtr = (editFieldDef_t *) item->typeData;

	if (item->cvar) {

		memset(buff, 0, sizeof(buff));
		DC->getCVarString(item->cvar, buff, sizeof(buff));
		len = strlen(buff);
		if (editPtr->maxChars && len > editPtr->maxChars) {
			len = editPtr->maxChars;
		}
		if (key & K_CHAR_FLAG) {
			key &= ~K_CHAR_FLAG;

			if (key == 'h' - 'a' + 1) {	// ctrl-h is backspace
				if (item->cursorPos > 0) {
					memmove(&buff[item->cursorPos - 1], &buff[item->cursorPos],
						len + 1 - item->cursorPos);
					//Makro - changed from --; doesn't make much sense, but things don't always do
					item->cursorPos -= 1;
					//if (item->cursorPos < editPtr->paintOffset) {
					if (item->cursorPos <= editPtr->paintOffset) {
						//Makro - changed
						//editPtr->paintOffset--;
						if (item->cursorPos > 0)
							editPtr->paintOffset = item->cursorPos - 1;
						else
							editPtr->paintOffset = 0;
					}
				}
				DC->setCVar(item->cvar, buff);
				return qtrue;
			}

			//
			// ignore any non printable chars
			//
			if (key < 32 || !item->cvar) {
				return qtrue;
			}

			if (item->type == ITEM_TYPE_NUMERICFIELD) {
				if (key < '0' || key > '9') {
					return qfalse;
				}
			}

			if (!DC->getOverstrikeMode()) {
				if ((len == MAX_EDITFIELD - 1) || (editPtr->maxChars && len >= editPtr->maxChars)) {
					return qtrue;
				}
				memmove(&buff[item->cursorPos + 1], &buff[item->cursorPos], len + 1 - item->cursorPos);
			} else {
				if (editPtr->maxChars && item->cursorPos >= editPtr->maxChars) {
					return qtrue;
				}
			}

			buff[item->cursorPos] = key;

			DC->setCVar(item->cvar, buff);

			if (item->cursorPos < len + 1) {
				item->cursorPos++;
				if (editPtr->maxPaintChars && item->cursorPos > editPtr->maxPaintChars) {
					editPtr->paintOffset++;
				}
			}

		} else {

			if (key == K_DEL || key == K_KP_DEL) {
				if (item->cursorPos < len) {
					memmove(buff + item->cursorPos, buff + item->cursorPos + 1,
						len - item->cursorPos);
					DC->setCVar(item->cvar, buff);
				}
				return qtrue;
			}

			if (key == K_RIGHTARROW || key == K_KP_RIGHTARROW) {
				if (editPtr->maxPaintChars && item->cursorPos >= editPtr->maxPaintChars
				    && item->cursorPos < len) {
					item->cursorPos++;
					editPtr->paintOffset++;
					return qtrue;
				}
				//int maxChars = Text_maxPaintChars(buff+editPtr->paintOffset, item->textscale, item->window.rect.w+item->textalignx);
				/*
					if (editPtr->maxPaintChars && item->cursorPos >= maxChars
				    && item->cursorPos < len) {
					item->cursorPos++;
					editPtr->paintOffset++;
					return qtrue;
				}
				*/
				if (item->cursorPos < len) {
					item->cursorPos++;
				}
				return qtrue;
			}

			if (key == K_LEFTARROW || key == K_KP_LEFTARROW) {
				if (item->cursorPos > 0) {
					item->cursorPos--;
				}
				if (item->cursorPos < editPtr->paintOffset) {
					editPtr->paintOffset--;
				}
				return qtrue;
			}

			if (key == K_HOME || key == K_KP_HOME) {	// || ( tolower(key) == 'a' && trap_Key_IsDown( K_CTRL ) ) ) {
				item->cursorPos = 0;
				editPtr->paintOffset = 0;
				return qtrue;
			}

			if (key == K_END || key == K_KP_END) {	// ( tolower(key) == 'e' && trap_Key_IsDown( K_CTRL ) ) ) {
				//int maxChars = Text_maxPaintChars(buff+editPtr->paintOffset, item->textscale, item->window.rect.w+item->textalignx);
				item->cursorPos = len;
				if (item->cursorPos > editPtr->maxPaintChars) {
					editPtr->paintOffset = len - editPtr->maxPaintChars;
				}
				/*
				if (item->cursorPos > maxChars) {
					editPtr->paintOffset = len - maxChars;
				}
				*/
				return qtrue;
			}

			if (key == K_INS || key == K_KP_INS) {
				DC->setOverstrikeMode(!DC->getOverstrikeMode());
				return qtrue;
			}
		}

		//Makro - added mousewheel
		if (key == K_TAB || key == K_DOWNARROW || key == K_KP_DOWNARROW || key == K_MWHEELDOWN) {
			newItem = Menu_SetNextCursorItem(item->parent);
			if (newItem
			    && (newItem->type == ITEM_TYPE_EDITFIELD || newItem->type == ITEM_TYPE_NUMERICFIELD)) {
				g_editItem = newItem;
			}
		}

		//Makro - added mousewheel
		if (key == K_UPARROW || key == K_KP_UPARROW || key == K_MWHEELUP) {
			newItem = Menu_SetPrevCursorItem(item->parent);
			if (newItem
			    && (newItem->type == ITEM_TYPE_EDITFIELD || newItem->type == ITEM_TYPE_NUMERICFIELD)) {
				g_editItem = newItem;
			}
		}

		if (key == K_ENTER || key == K_KP_ENTER || key == K_ESCAPE) {
			return qfalse;
		}

		return qtrue;
	}
	return qfalse;

}

static void Scroll_ListBox_AutoFunc(void *p)
{
	scrollInfo_t *si = (scrollInfo_t *) p;

	if (DC->realTime > si->nextScrollTime) {
		// need to scroll which is done by simulating a click to the item
		// this is done a bit sideways as the autoscroll "knows" that the item is a listbox
		// so it calls it directly
		Item_ListBox_HandleKey(si->item, si->scrollKey, qtrue, qfalse);
		si->nextScrollTime = DC->realTime + si->adjustValue;
	}

	if (DC->realTime > si->nextAdjustTime) {
		si->nextAdjustTime = DC->realTime + SCROLL_TIME_ADJUST;
		if (si->adjustValue > SCROLL_TIME_FLOOR) {
			si->adjustValue -= SCROLL_TIME_ADJUSTOFFSET;
		}
	}
}

//Makro - vector support
static void Scroll_ListBox_ThumbFunc(void *p)
{
	scrollInfo_t *si = (scrollInfo_t *) p;
	rectDef_t r;
	int pos, max;

	listBoxDef_t *listPtr = (listBoxDef_t *) si->item->typeData;

	r.hasVectors = si->item->window.rect.hasVectors;
	Vector2Copy(si->item->window.rect.u, r.u);
	Vector2Copy(si->item->window.rect.v, r.v);
	
	//horizontal
	if (si->item->window.flags & WINDOW_HORIZONTAL) {
		if (DC->cursorx == si->xStart && DC->cursory == si->yStart) {
			return;
		}
		max = Item_ListBox_MaxScroll(si->item); 
		//vectors?
		if (r.hasVectors) {
			float p[2];
			//Makro - FIXME!!!
			Rect_ToInnerCoords(&si->item->window.rect, DC->cursorx, DC->cursory, &p[0], NULL);
			p[1] = (p[0] - SCROLLBAR_SIZE / 2 - SCROLLBAR_SIZE - 1) / (si->item->window.rect.w - 3 * SCROLLBAR_SIZE - 2);
			pos = (int) (max * p[1]);
		//no vectors
		} else {
			r.x = si->item->window.rect.x + SCROLLBAR_SIZE + 1;
			r.y = si->item->window.rect.y + si->item->window.rect.h - SCROLLBAR_SIZE - 1;
			r.h = SCROLLBAR_SIZE;
			r.w = si->item->window.rect.w - (SCROLLBAR_SIZE * 2) - 2;
			//
			pos = (DC->cursorx - r.x - SCROLLBAR_SIZE / 2) * max / (r.w - SCROLLBAR_SIZE);
		}
		if (pos < 0) {
			pos = 0;
		} else if (pos > max) {
			pos = max;
		}
		listPtr->startPos = pos;
		si->xStart = DC->cursorx;
		si->yStart = DC->cursory;
	//vertical
	} else if (DC->cursory != si->yStart || DC->cursorx != si->xStart) {
		max = Item_ListBox_MaxScroll(si->item);
		//vectors?
		if (r.hasVectors) {
			float p[2];
			Vector2Set(p, DC->cursorx - si->item->window.rect.x, DC->cursory - si->item->window.rect.y);
			
			//projection
			//p[0] = p[0] * si->item->window.rect.v[0] + p[1] * si->item->window.rect.v[1];
			Rect_ToInnerCoords(&si->item->window.rect, DC->cursorx, DC->cursory, NULL, &p[0]);
			//0..1 fraction
			p[1] = (p[0] - SCROLLBAR_SIZE / 2 - SCROLLBAR_SIZE - 1) / (si->item->window.rect.h - 3 * SCROLLBAR_SIZE - 2);
			pos = (int) (max * p[1]);
		//no vectors
		} else {
			r.x = si->item->window.rect.x + si->item->window.rect.w - SCROLLBAR_SIZE - 1;
			r.y = si->item->window.rect.y + SCROLLBAR_SIZE + 1;
			r.h = si->item->window.rect.h - (SCROLLBAR_SIZE * 2) - 2;
			r.w = SCROLLBAR_SIZE;
			//
			pos = (DC->cursory - r.y - SCROLLBAR_SIZE / 2) * max / (r.h - SCROLLBAR_SIZE);
		}
		if (pos < 0) {
			pos = 0;
		} else if (pos > max) {
			pos = max;
		}
		listPtr->startPos = pos;
		si->xStart = DC->cursorx;
		si->yStart = DC->cursory;
	}

	if (DC->realTime > si->nextScrollTime) {
		// need to scroll which is done by simulating a click to the item
		// this is done a bit sideways as the autoscroll "knows" that the item is a listbox
		// so it calls it directly
		Item_ListBox_HandleKey(si->item, si->scrollKey, qtrue, qfalse);
		si->nextScrollTime = DC->realTime + si->adjustValue;
	}

	if (DC->realTime > si->nextAdjustTime) {
		si->nextAdjustTime = DC->realTime + SCROLL_TIME_ADJUST;
		if (si->adjustValue > SCROLL_TIME_FLOOR) {
			si->adjustValue -= SCROLL_TIME_ADJUSTOFFSET;
		}
	}
}

static void Scroll_Slider_ThumbFunc(void *p)
{
	float x, y, value, cursorx, cursory;
	scrollInfo_t *si = (scrollInfo_t *) p;
	editFieldDef_t *editDef = si->item->typeData;

	if (si->item->text) {
		if (si->item->textRect.hasVectors)
		{
			float xoffset = si->item->textRect.w+8, yoffset = -(si->item->textRect.h/2);
			x = si->item->textRect.x + xoffset*si->item->textRect.u[0] + yoffset*si->item->textRect.v[0];
			y = si->item->textRect.y + xoffset*si->item->textRect.u[1] + yoffset*si->item->textRect.v[1];
		} else {
			x = si->item->textRect.x + si->item->textRect.w + 8;
			y = si->item->textRect.y;
		}
	} else {
		x = si->item->window.rect.x;
		y = si->item->window.rect.y;
	}
	//FIXME: there's a -2 offset that should be taken care of
	//too small to fix right now
	//y = si->item->window.rect.y;

	cursorx = DC->cursorx;
	cursory = DC->cursory;
	//vectors
	if (si->item->textRect.hasVectors)
	{
		//Makro - FIXME!!! - use appropriate transformation instead of a simple projection
		value = (cursorx - x) * si->item->textRect.u[0] + (cursory - y) * si->item->textRect.u[1];
		if (value < 0) {
			value = 0;
		} else if (value > SLIDER_WIDTH) {
			value = SLIDER_WIDTH;
		}
	} else {
		if (cursorx < x) {
			cursorx = x;
		} else if (cursorx > x + SLIDER_WIDTH) {
			cursorx = x + SLIDER_WIDTH;
		}
		value = cursorx - x;
	}
	value /= SLIDER_WIDTH;
	value *= (editDef->maxVal - editDef->minVal);
	value += editDef->minVal;
	DC->setCVar(si->item->cvar, va("%f", value));
}

void Item_StartCapture(itemDef_t * item, int key)
{
	int flags;

	switch (item->type) {
	//Makro - not needed, comented out
	/*
	case ITEM_TYPE_EDITFIELD:
	case ITEM_TYPE_NUMERICFIELD:
	*/

	case ITEM_TYPE_LISTBOX:
		{
			flags = Item_ListBox_OverLB(item, DC->cursorx, DC->cursory);
			if (flags & (WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW)) {
				scrollInfo.nextScrollTime = DC->realTime + SCROLL_TIME_START;
				scrollInfo.nextAdjustTime = DC->realTime + SCROLL_TIME_ADJUST;
				scrollInfo.adjustValue = SCROLL_TIME_START;
				scrollInfo.scrollKey = key;
				scrollInfo.scrollDir = (flags & WINDOW_LB_LEFTARROW) ? qtrue : qfalse;
				scrollInfo.item = item;
				captureData = &scrollInfo;
				captureFunc = &Scroll_ListBox_AutoFunc;
				itemCapture = item;
			} else if (flags & WINDOW_LB_THUMB) {
				scrollInfo.scrollKey = key;
				scrollInfo.item = item;
				scrollInfo.xStart = DC->cursorx;
				scrollInfo.yStart = DC->cursory;
				captureData = &scrollInfo;
				captureFunc = &Scroll_ListBox_ThumbFunc;
				itemCapture = item;
			}
			break;
		}
	case ITEM_TYPE_SLIDER:
		{
			flags = Item_Slider_OverSlider(item, DC->cursorx, DC->cursory);
			if (flags & WINDOW_LB_THUMB) {
				scrollInfo.scrollKey = key;
				scrollInfo.item = item;
				scrollInfo.xStart = DC->cursorx;
				scrollInfo.yStart = DC->cursory;
				captureData = &scrollInfo;
				captureFunc = &Scroll_Slider_ThumbFunc;
				itemCapture = item;
			}
			break;
		}
	}
}

void Item_StopCapture(itemDef_t * item)
{

}

qboolean Item_Slider_HandleKey(itemDef_t * item, int key, qboolean down)
{
	float x, y, value, width, work;

	//DC->Print("slider handle key\n");
	if (item->window.flags & WINDOW_HASFOCUS && item->cvar) {
		if (key == K_MOUSE1 || key == K_ENTER || key == K_MOUSE2 || key == K_MOUSE3)
		{
			if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory))
			{
				editFieldDef_t *editDef = item->typeData;

				if (editDef) {
					//Makro - copy all info (including vectors)
					//make sure relevant info is set afterwards
					rectDef_t testRect;

					width = SLIDER_WIDTH;
					if (item->text) {
						//vectors?
						if (item->textRect.hasVectors)
						{
							float xoffset = item->textRect.w+8, yoffset = -(item->textRect.h/2);
							x = item->textRect.x + xoffset*item->textRect.u[0] + yoffset*item->textRect.v[0];
							//y = item->textRect.y + (item->textRect.w + 8) * item->textRect.u[1];
							//y = item->window.rect.y + (item->textRect.w + 8) * item->textRect.u[1];
							y = item->textRect.y + xoffset*item->textRect.u[1] + yoffset*item->textRect.v[1];
						} else {
							x = item->textRect.x + item->textRect.w + 8;
							y = item->textRect.y - item->textRect.h/2;
						}
					} else {
						x = item->window.rect.x;
						y = item->window.rect.y;
						//y = item->textRect.y;
					}

					testRect = item->window.rect;
					testRect.x = x;
					//testRect.y = y;
					value = (float) SLIDER_THUMB_WIDTH / 2;
					//vectors?
					if (testRect.hasVectors)
					{
						testRect.x -= value * testRect.u[0];
						testRect.y -= value * testRect.u[1];
					} else {
						testRect.x -= value;
					}
					//FIXME: ugly code, rewrite some day
					//DC->Print("slider x: %f\n", testRect.x);
					testRect.w = (SLIDER_WIDTH + (float) SLIDER_THUMB_WIDTH / 2);
					//DC->Print("slider w: %f\n", testRect.w);
					if (Rect_ContainsPoint(&testRect, DC->cursorx, DC->cursory)) {
						//Makro - use a dotproduct if using vectors
						if (testRect.hasVectors)
						{
							work = (DC->cursorx - x) * testRect.u[0] + (DC->cursory - y) * testRect.u[1];
						} else {
							work = DC->cursorx - x;
						}
						value = work / width;
						value *= (editDef->maxVal - editDef->minVal);
						// vm fuckage
						// value = (((float)(DC->cursorx - x)/ SLIDER_WIDTH) * (editDef->maxVal - editDef->minVal));
						value += editDef->minVal;
						DC->setCVar(item->cvar, va("%f", value));
						return qtrue;
					}
				}
			}
			//Makro - adding left/right key handling
		} else if (key == K_LEFTARROW || key == K_RIGHTARROW || key == K_MWHEELUP || key == K_MWHEELDOWN
			|| key == K_HOME || key == K_END) {
			editFieldDef_t *editDef = item->typeData;

			//DC->Print("slider LEFT/RIGHT\n");
			if (editDef) {
				value = DC->getCVarValue(item->cvar);
				work = (editDef->maxVal - editDef->minVal) / 10;

				switch (key) {
				case K_RIGHTARROW:
				case K_MWHEELUP:
					value = Com_Clamp(editDef->minVal, editDef->maxVal, value + work);
					break;
				case K_LEFTARROW:
				case K_MWHEELDOWN:
					value = Com_Clamp(editDef->minVal, editDef->maxVal, value - work);
					break;
				case K_HOME:
					value = editDef->minVal;
					break;
				case K_END:
					value = editDef->maxVal;
					break;
				default:
					return qfalse;
				}
				
				//DC->Print("SLIDER: value = %f\n", value);
				DC->setCVar(item->cvar, va("%f", value));
				return qtrue;
			}
		}
	}
	//DC->Print("slider handle key exit\n");
	return qfalse;
}

//Makro - left/right support for inactive numeric fields
qboolean Item_InActiveTextField_HandleKey(itemDef_t * item, int key)
{
	if (!g_editingField) {
		if (item->type == ITEM_TYPE_NUMERICFIELD && item->cvar) {
			if (key == K_LEFTARROW || key == K_RIGHTARROW || key == K_HOME || key == K_PGUP
			    || key == K_PGDN) {
				editFieldDef_t *editPtr = (editFieldDef_t *) item->typeData;
				int current = (int) DC->getCVarValue(item->cvar);

				switch (key) {
				case K_LEFTARROW:
					current--;
					break;
				case K_RIGHTARROW:
					current++;
					break;
				case K_PGUP:
					current += 5;
					break;
				case K_PGDN:
					current -= 5;
					break;
				default:
					current = 0;
					break;
				}

				if (current < 0) {
					current = 0;
				}
				if (strlen(va("%i", current)) <= editPtr->maxChars) {
					DC->setCVar(item->cvar, va("%i", current));
				}

				return qtrue;
			}
		}
	}

	return qfalse;
}

qboolean Item_HandleKey(itemDef_t * item, int key, qboolean down)
{

	if (itemCapture) {
		Item_StopCapture(itemCapture);
		itemCapture = NULL;
		captureFunc = 0;
		captureData = NULL;
	} else {
		// bk001206 - parentheses
		if (down && (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3)) {
			Item_StartCapture(item, key);
		}
	}

	if (!down) {
		return qfalse;
	}

	switch (item->type) {
	case ITEM_TYPE_BUTTON:
		return qfalse;
		break;
	case ITEM_TYPE_RADIOBUTTON:
		return qfalse;
		break;
	case ITEM_TYPE_CHECKBOX:
		return qfalse;
		break;
	case ITEM_TYPE_EDITFIELD:
		//Makro - separated editing fields from numeric fields
		return qfalse;
		break;
	case ITEM_TYPE_NUMERICFIELD:
		/*
		   //return Item_TextField_HandleKey(item, key);
		   return qfalse;
		 */
		//Makro - left/right support
		return Item_InActiveTextField_HandleKey(item, key);
		break;
	case ITEM_TYPE_COMBO:
		return qfalse;
		break;
	case ITEM_TYPE_LISTBOX:
		return Item_ListBox_HandleKey(item, key, down, qfalse);
		break;
	case ITEM_TYPE_YESNO:
		return Item_YesNo_HandleKey(item, key);
		break;
	case ITEM_TYPE_MULTI:
		return Item_Multi_HandleKey(item, key);
		break;
	case ITEM_TYPE_OWNERDRAW:
		return Item_OwnerDraw_HandleKey(item, key);
		break;
	case ITEM_TYPE_BIND:
		return Item_Bind_HandleKey(item, key, down);
		break;
	case ITEM_TYPE_SLIDER:
		return Item_Slider_HandleKey(item, key, down);
		break;
		//case ITEM_TYPE_IMAGE:
		//  Item_Image_Paint(item);
		//  break;
	default:
		return qfalse;
		break;
	}

	//return qfalse;
}

void Item_Action(itemDef_t * item)
{
	if (item) {
		Item_RunScript(item, item->action);
	}
}

itemDef_t *Menu_SetPrevCursorItem(menuDef_t * menu)
{

	int oldCursor = menu->cursorItem;
	int i;

	if (!menu || menu->itemCount <= 0)
		return NULL;

	if (menu->cursorItem > menu->itemCount || menu->cursorItem <= 0)
		menu->cursorItem = menu->itemCount - 1;
	else
		menu->cursorItem--;

	for (i=0; i<menu->itemCount; i++)
	{
		if (Item_SetFocus(menu->items[menu->cursorItem], 0, 0, qtrue))
			return menu->items[menu->cursorItem];
		menu->cursorItem = (menu->cursorItem == 0) ? menu->itemCount - 1 : menu->cursorItem - 1;
	}

	menu->cursorItem = oldCursor;
	return NULL;
}

itemDef_t *Menu_SetNextCursorItem(menuDef_t * menu)
{
	int oldCursor = menu->cursorItem;
	int i;

	if (!menu || menu->itemCount <= 0)
		return NULL;

	if (menu->cursorItem >= menu->itemCount || menu->cursorItem < 0)
		menu->cursorItem = 0;
	else
		menu->cursorItem++;

	for (i=0; i<menu->itemCount; i++)
	{
		if (Item_SetFocus(menu->items[menu->cursorItem], 0, 0, qtrue))
			return menu->items[menu->cursorItem];
		menu->cursorItem = (menu->cursorItem == menu->itemCount) ? 0 : menu->cursorItem + 1;
	}

	menu->cursorItem = oldCursor;
	return NULL;
}

static void Window_CloseCinematic(windowDef_t * window)
{
	if (window->style == WINDOW_STYLE_CINEMATIC && window->cinematic >= 0) {
		DC->stopCinematic(window->cinematic);
		window->cinematic = -1;
	}
}

static void Menu_CloseCinematics(menuDef_t * menu)
{
	if (menu) {
		int i;

		Window_CloseCinematic(&menu->window);
		for (i = 0; i < menu->itemCount; i++) {
			Window_CloseCinematic(&menu->items[i]->window);
			if (menu->items[i]->type == ITEM_TYPE_OWNERDRAW) {
				DC->stopCinematic(0 - menu->items[i]->window.ownerDraw);
			}
		}
	}
}

static void Display_CloseCinematics()
{
	int i;

	for (i = 0; i < menuCount; i++) {
		Menu_CloseCinematics(&Menus[i]);
	}
}

//Makro - select the right player model icon
void UI_RQ3_SelectPlayerIcon(menuDef_t *menu)
{
	int i;

	for (i = 0; i < menu->itemCount; i++) {
		if (menu->items[i]->type == ITEM_TYPE_LISTBOX && menu->items[i]->special == FEEDER_Q3HEADS) {
			//Makro - select the right player model icon
			listBoxDef_t *listPtr = (listBoxDef_t *) menu->items[i]->typeData;
			int size = 2, start = 0, end = 2, pos = UI_SelectedQ3Head(qtrue);

			if (listPtr->elementWidth) {
				size = (int) (menu->items[i]->window.rect.w / listPtr->elementWidth);
				if (size >= 2) {
					start = listPtr->startPos;
					end = listPtr->endPos;
					if (start + size <= pos || pos + size <= end)
						start = ((int) (pos / size)) * size;
					if (start + size > DC->feederCount(FEEDER_Q3HEADS))
						start = DC->feederCount(FEEDER_Q3HEADS) - size;
					if (start < 0)
						start = 0;
					listPtr->startPos = start;
					listPtr->endPos = start + size;
				}
			}
			listPtr->cursorPos = pos;
			menu->items[i]->cursorPos = pos;
		}
	}
}

void Menus_Activate(menuDef_t * menu)
{
	//Makro - it's better to check for this kind of stuff
	if (!menu) {
		return;
	}

	menu->window.flags |= (WINDOW_HASFOCUS | WINDOW_VISIBLE);
	if (menu->onOpen) {
		itemDef_t item;

		item.parent = menu;
		Item_RunScript(&item, menu->onOpen);
	}
	//Makro - set shown to qfalse to allow onShow events to be triggerred
	menu->shown = qfalse;

	if (menu->soundName && *menu->soundName) {
//              DC->stopBackgroundTrack();                                      // you don't want to do this since it will reset s_rawend
		//Makro - check for intro
		if (menu->soundIntro && *menu->soundIntro) {
			DC->startBackgroundTrack(menu->soundIntro, menu->soundName);
		} else {
			DC->startBackgroundTrack(menu->soundName, menu->soundName);
		}

	}
	//Makro - select the right player model icon
	UI_RQ3_SelectPlayerIcon(menu);

	Display_CloseCinematics();
}

int Display_VisibleMenuCount()
{
	int i, count;

	count = 0;
	for (i = 0; i < menuCount; i++) {
		if (Menus[i].window.flags & (WINDOW_FORCED | WINDOW_VISIBLE)) {
			count++;
		}
	}
	return count;
}

void Menus_HandleOOBClick(menuDef_t * menu, int key, qboolean down)
{
	//Makro - moved check up here
	if (menu && down) {
		//int i;

		// basically the behaviour we are looking for is if there are windows in the stack.. see if 
		// the cursor is within any of them.. if not close them otherwise activate them and pass the 
		// key on.. force a mouse move to activate focus and script stuff 
		//Makro - moved check above
		if (menu->window.flags & WINDOW_OOB_CLICK) {
			if (menu->itemCount > 0) {
				Item_RunScript(menu->items[0], menu->onOOBClick);
			}
			//Makro - if this is a popup window, don't broadcast the event
			if (menu->window.flags & WINDOW_POPUP) {
				return;
			}
		}

		//Makro - disabled for now
		/*
		for (i = 0; i < menuCount; i++) {
			if (Menu_OverActiveItem(&Menus[i], DC->cursorx, DC->cursory)) {
				//Makro - I really doubt this was supposed to be duplicated here
				//Menu_RunCloseScript(menu);
				menu->window.flags &= ~(WINDOW_HASFOCUS | WINDOW_VISIBLE);
				Menus_Activate(&Menus[i]);
				Menu_HandleMouseMove(&Menus[i], DC->cursorx, DC->cursory);
				Menu_HandleKey(&Menus[i], key, down);
			}
		}
		*/

		if (Display_VisibleMenuCount() == 0) {
			if (DC->Pause) {
				DC->Pause(qfalse);
			}
		}
		Display_CloseCinematics();
	}
}

static rectDef_t *Item_CorrectedTextRect(itemDef_t * item)
{
	static rectDef_t rect;

	memset(&rect, 0, sizeof(rectDef_t));
	if (item) {
		rect = item->textRect;
		if (rect.w) {
			rect.y -= rect.h;
		}
	}
	return &rect;
}

//Makro - function to determine whether or not an item is visible
qboolean UI_RQ3_IsActiveItem(itemDef_t * item)
{

	if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
		return qfalse;
	}

	if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(item, CVAR_SHOW)) {
		return qfalse;
	}

	return ((item->window.flags & WINDOW_VISIBLE) != 0);
}

//Makro - search for items that have shortcuts
qboolean UI_RQ3_TriggerShortcut(menuDef_t * menu, int key)
{
	int i;

	if (menu == NULL) {
		return qfalse;
	}

	if (DC->realTime >= UI_RQ3_lastCheckForShortcuts + UI_RQ3_ShortcutCheckDelay) {
		UI_RQ3_lastCheckForShortcuts = DC->realTime;
		for (i = 0; i < menu->itemCount; i++) {
			if (UI_RQ3_IsActiveItem(menu->items[i]))
			{
				int j;
				for (j=0; j<MAX_SHORTCUT_KEYS && menu->items[i]->window.shortcutKey[j]; j++)
				{
					if (menu->items[i]->window.shortcutKey[j] == key) {
						Item_HandleKey(menu->items[i], K_ENTER, qtrue);
						Item_Action(menu->items[i]);
						return qtrue;
					}
				}
			}
		}
	}
	return qfalse;
}

void Menu_HandleKey(menuDef_t * menu, int key, qboolean down)
{
	int i;
	itemDef_t *item = NULL;
	qboolean inHandler = qfalse;
	static qboolean shiftPressed = qfalse;

	//Makro - skip check for shortcut keys
	qboolean skipCheck = qfalse;

	if (inHandler) {
		return;
	}

	//Makro - added
	if (key == K_SHIFT)
		shiftPressed = down;

	inHandler = qtrue;
	if (g_waitingForKey && down) {
		Item_Bind_HandleKey(g_bindItem, key, down);
		inHandler = qfalse;
		return;
	}

	if (g_editingField && down) {
		if (!Item_TextField_HandleKey(g_editItem, key)) {
			g_editingField = qfalse;
			g_editItem = NULL;
			inHandler = qfalse;
			return;
		} else if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3) {
			g_editingField = qfalse;
			g_editItem = NULL;
			Display_MouseMove(NULL, DC->cursorx, DC->cursory);
		} else if (key == K_TAB || key == K_UPARROW || key == K_DOWNARROW) {
			return;
		}
	}

	if (menu == NULL) {
		inHandler = qfalse;
		return;
	}

	// see if the mouse is within the window bounds and if so is this a mouse click
	//Makro - changed behaviour; popup windows with OOB click set are closed
	//without broadcasting the event instead of simply ignoring the OOB
	//- removed "!(menu->window.flags & WINDOW_POPUP)" check
	if (down && !Rect_ContainsPoint(&menu->window.rect, DC->cursorx, DC->cursory)) {
		//Makro - commented out
		//static qboolean inHandleKey = qfalse;

		// bk001206 - parentheses
		//if (!inHandleKey && (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3)) {
		if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3) {
			//inHandleKey = qtrue;
			Menus_HandleOOBClick(menu, key, down);
			//inHandleKey = qfalse;
			inHandler = qfalse;
			return;
		}
	}
	// get the item with focus
	for (i = 0; i < menu->itemCount; i++) {
		if (menu->items[i]->window.flags & WINDOW_HASFOCUS) {
			item = menu->items[i];
		}
	}

	if (item != NULL) {
		if (Item_HandleKey(item, key, down)) {
			Item_Action(item);
			inHandler = qfalse;
			return;
		}
	}

	//Makro - menu anchor?
	if (key == K_MOUSE1 && !down && g_anchoredMenu)
	{
		g_anchoredMenu = NULL;
		return;
	}

	if (!down) {
		inHandler = qfalse;
		return;
	}
	//Makro - check for shortcuts
	if (item) {
		if (item->type == ITEM_TYPE_EDITFIELD || item->type == ITEM_TYPE_NUMERICFIELD) {
			skipCheck = g_editingField;
		} else if (item->type == ITEM_TYPE_BIND) {
			skipCheck = g_waitingForKey;
		}
	}
	//skipCheck = skipCheck && down;
	if (!skipCheck) {
		if (UI_RQ3_TriggerShortcut(menu, key)) {
			return;
		}
	}

	// default handling
	switch (key) {

	case K_F11:
		if (DC->getCVarValue("developer")) {
			debugMode ^= 1;
		}
		break;

	case K_F12:
		if (DC->getCVarValue("developer")) {
			DC->executeText(EXEC_APPEND, "screenshot\n");
		}
		break;
	case K_KP_UPARROW:
	case K_UPARROW:
		if (shiftPressed)
			Menu_SetNextCursorItem(menu);
		else
			Menu_SetPrevCursorItem(menu);
		break;

	case K_ESCAPE:
		if (!g_waitingForKey && menu->onESC) {
			itemDef_t it;

			it.parent = menu;
			Item_RunScript(&it, menu->onESC);
		}
		break;
	case K_TAB:
	case K_KP_DOWNARROW:
	case K_DOWNARROW:
		if (shiftPressed)
			Menu_SetPrevCursorItem(menu);
		else
			Menu_SetNextCursorItem(menu);
		break;

	case K_MOUSE1:
	case K_MOUSE2:
		if (item) {
			if (item->type == ITEM_TYPE_TEXT) {
				if (Rect_ContainsPoint(Item_CorrectedTextRect(item), DC->cursorx, DC->cursory)) {
					Item_Action(item);
					return;
				}
			} else if (item->type == ITEM_TYPE_EDITFIELD || item->type == ITEM_TYPE_NUMERICFIELD) {
				if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory)) {
					item->cursorPos = 0;
					g_editingField = qtrue;
					g_editItem = item;
					DC->setOverstrikeMode(qtrue);
					return;
				}
			} else {
				if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory)) {
					Item_Action(item);
					return;
				}
			}
		}
		//Makro - menu anchor?
		if (!g_anchoredMenu && key == K_MOUSE1)
		{
			for (i=0; i<menu->itemCount; i++)
			{
				itemDef_t *pItem = menu->items[i];
				if (pItem && Rect_ContainsPoint(&pItem->window.rect, DC->cursorx, DC->cursory) &&
					(pItem->window.flags & (WINDOW_MENU_ANCHOR|WINDOW_VISIBLE)) == (WINDOW_MENU_ANCHOR|WINDOW_VISIBLE))
				{
					g_anchoredMenu = menu;
					g_anchorX = DC->cursorx;
					g_anchorY = DC->cursory;
					return;
				}
			}
		}
		break;

	case K_JOY1:
	case K_JOY2:
	case K_JOY3:
	case K_JOY4:
	case K_AUX1:
	case K_AUX2:
	case K_AUX3:
	case K_AUX4:
	case K_AUX5:
	case K_AUX6:
	case K_AUX7:
	case K_AUX8:
	case K_AUX9:
	case K_AUX10:
	case K_AUX11:
	case K_AUX12:
	case K_AUX13:
	case K_AUX14:
	case K_AUX15:
	case K_AUX16:
		break;
	case K_KP_ENTER:
	case K_ENTER:
		if (item) {
			if (item->type == ITEM_TYPE_EDITFIELD || item->type == ITEM_TYPE_NUMERICFIELD) {
				item->cursorPos = 0;
				g_editingField = qtrue;
				g_editItem = item;
				DC->setOverstrikeMode(qtrue);
			} else {
				Item_Action(item);
			}
		}
		break;
	}

	inHandler = qfalse;
}

//Makro - transforms a point to relative co-ordinates
void Rect_ToInnerCoords(rectDef_t *rect, float x, float y, float *resx, float *resy)
{
	if (rect)
	{
		//Makro - twisted rectangle?
		if (rect->hasVectors)
		{
			float dx = x - rect->x;
			float dy = y - rect->y;
			float det = rect->u[0] * rect->v[1] - rect->u[1] * rect->v[0];
			if (fabs(det) < 0.001f) {
				//degenerate rect
				if (resx) *resx = 0;
				if (resy) *resy = 0;
				return;
			} else {
				if (resx) *resx = (dx * rect->v[1] - dy * rect->v[0]) / det;
				if (resy) *resy = (- dx * rect->u[1] + dy * rect->u[0]) / det;
			}
		} else {
			if (resx) *resx = x - rect->x;
			if (resy) *resy = y - rect->y;
		}
	}
}

void ToWindowCoords(float *x, float *y, windowDef_t * window)
{
	//Makro - vectors
	if (window->rectClient.hasVectors)
	{
		if (window->border != 0) {
			*x += window->borderSize * (window->rectClient.u[0] + window->rectClient.v[0]);
			*y += window->borderSize * (window->rectClient.u[1] + window->rectClient.v[1]);
		}
		*x += window->rect.x;
		*y += window->rect.y;
	} else {
		if (window->border != 0) {
			*x += window->borderSize;
			*y += window->borderSize;
		}
		*x += window->rect.x;
		*y += window->rect.y;
	}
}

void Rect_ToWindowCoords(rectDef_t * rect, windowDef_t * window)
{
	ToWindowCoords(&rect->x, &rect->y, window);
}

void Item_SetTextExtents(itemDef_t * item, int *width, int *height, const char *text)
{
	const char *textPtr = (text) ? text : item->text;

	if (textPtr == NULL) {
		return;
	}

	*width = item->textRect.w;
	*height = item->textRect.h;

	//TODO: find out where hasVectors gets reset
	//this is a pretty nasty fix
	item->window.rectClient.hasVectors = item->textRect.hasVectors;

	// keeps us from computing the widths and heights more than once
	if (*width == 0 || (item->type == ITEM_TYPE_OWNERDRAW && item->textalignment == ITEM_ALIGN_CENTER)) {
		int originalWidth = DC->textWidth(item->text, item->textscale, 0);

		if (item->type == ITEM_TYPE_OWNERDRAW
		    && (item->textalignment == ITEM_ALIGN_CENTER || item->textalignment == ITEM_ALIGN_RIGHT)) {
			originalWidth += DC->ownerDrawWidth(item->window.ownerDraw, item->textscale);
		} else if (item->type == ITEM_TYPE_EDITFIELD && item->textalignment == ITEM_ALIGN_CENTER && item->cvar) {
			char buff[256];

			DC->getCVarString(item->cvar, buff, 256);
			originalWidth += DC->textWidth(buff, item->textscale, 0);
		}

		*width = DC->textWidth(textPtr, item->textscale, 0);
		*height = DC->textHeight(textPtr, item->textscale, 0);
		item->textRect.w = *width;
		item->textRect.h = *height;
		//Makro - check for vectors
		if (item->textRect.hasVectors)
		{
			item->textRect.x = item->textalignx * item->textRect.u[0] + item->textaligny*item->textRect.v[0];
			item->textRect.y = item->textalignx * item->textRect.u[1] + item->textaligny*item->textRect.v[1];
		} else {
			item->textRect.x = item->textalignx;
			item->textRect.y = item->textaligny;
		}
		if (item->textalignment == ITEM_ALIGN_RIGHT) {
			//Makro - check for vectors
			if (item->textRect.hasVectors)
			{
				item->textRect.x -= originalWidth * item->textRect.u[0];
				item->textRect.y -= originalWidth * item->textRect.u[1];
			} else {
				item->textRect.x = item->textalignx - originalWidth;
			}
		} else if (item->textalignment == ITEM_ALIGN_CENTER) {
			if (item->textRect.hasVectors)
			{
				item->textRect.x -= (originalWidth >> 1) * item->textRect.u[0];
				item->textRect.y -= (originalWidth >> 1) * item->textRect.u[1];
			} else {
				item->textRect.x = item->textalignx - originalWidth / 2;
			}
		}

		ToWindowCoords(&item->textRect.x, &item->textRect.y, &item->window);
	}
}

void Item_TextColor(itemDef_t * item, vec4_t * newColor)
{
	vec4_t lowLight;
	menuDef_t *parent = (menuDef_t *) item->parent;

	Fade(&item->window.flags, &item->window.foreColor[3], parent->fadeClamp, &item->window.nextTime,
	     parent->fadeCycle, qtrue, parent->fadeAmount);

	if (item->window.flags & WINDOW_HASFOCUS) {
		//Makro - changed to fade from normal text color to focus color
		//lowLight[0] = 0.8 * parent->focusColor[0]; 
		//lowLight[1] = 0.8 * parent->focusColor[1]; 
		//lowLight[2] = 0.8 * parent->focusColor[2]; 
		//lowLight[3] = 0.8 * parent->focusColor[3]; 
		memcpy(lowLight, item->window.foreColor, sizeof(vec4_t));
		LerpColor(parent->focusColor, lowLight, *newColor, 0.5 + 0.5 * sin(DC->realTime / (float)PULSE_DIVISOR));
		//LerpColor(parent->focusColor, lowLight, *newColor, SawTooth(DC->realTime, PULSE_SAWTOOTH_PERIOD));
	} else if (item->textStyle == ITEM_TEXTSTYLE_BLINK && !((DC->realTime / BLINK_DIVISOR) & 1)) {
		lowLight[0] = 0.8 * item->window.foreColor[0];
		lowLight[1] = 0.8 * item->window.foreColor[1];
		lowLight[2] = 0.8 * item->window.foreColor[2];
		lowLight[3] = 0.8 * item->window.foreColor[3];
		LerpColor(item->window.foreColor, lowLight, *newColor, 0.5 + 0.5 * sin(DC->realTime / (float)PULSE_DIVISOR));
		//LerpColor(item->window.foreColor, lowLight, *newColor, SawTooth(DC->realTime, PULSE_SAWTOOTH_PERIOD));
	} else {
		memcpy(newColor, item->window.foreColor, sizeof(vec4_t));
		// items can be enabled and disabled based on cvars
	}

	if (item->enableCvar && *item->enableCvar && item->cvarTest && *item->cvarTest) {
		if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
			memcpy(newColor, &parent->disableColor, sizeof(vec4_t));
		}
	}
}

void Item_Text_AutoWrapped_Paint(itemDef_t * item)
{
	char text[1024];
	const char *p, *textPtr, *newLinePtr;
	char buff[1024];
	int width, height, len, textWidth, newLine, newLineWidth;
	float y;
	vec4_t color;

	textWidth = 0;
	newLinePtr = NULL;

	if (item->text == NULL) {
		if (item->cvar == NULL) {
			return;
		} else {
			DC->getCVarString(item->cvar, text, sizeof(text));
			textPtr = text;
		}
	} else {
		textPtr = item->text;
	}
	if (*textPtr == '\0') {
		return;
	}
	Item_TextColor(item, &color);
	Item_SetTextExtents(item, &width, &height, textPtr);

	y = item->textaligny;
	len = 0;
	buff[0] = '\0';
	newLine = 0;
	newLineWidth = 0;
	p = textPtr;
	
	while (p)
	{
		if (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\0') {
			newLine = len;
			newLinePtr = p + 1;
			newLineWidth = textWidth;
		}
		textWidth = DC->textWidth(buff, item->textscale, 0);
		if ((newLine && textWidth > item->window.rect.w) || *p == '\n' || *p == '\0') {
			if (len) {
				//Makro - check for vectors
				if (item->textRect.hasVectors)
				{
					item->textRect.x = item->textalignx * item->textRect.u[0] + y*item->textRect.v[0];
					item->textRect.y = item->textalignx * item->textRect.u[1] + y*item->textRect.v[1];
				} else {
					item->textRect.x = item->textalignx;
					item->textRect.y = y;
				}
				if (item->textalignment == ITEM_ALIGN_RIGHT) {
					//item->textRect.x = item->textalignx - newLineWidth;
					if (item->textRect.hasVectors)
					{
						item->textRect.x -= newLineWidth * item->textRect.u[0];
						item->textRect.y -= newLineWidth * item->textRect.u[1];
					} else {
						item->textRect.x -= newLineWidth;
					}
				} else if (item->textalignment == ITEM_ALIGN_CENTER) {
					//item->textRect.x = item->textalignx - newLineWidth / 2;
					if (item->textRect.hasVectors)
					{
						item->textRect.x -= (newLineWidth >> 1) * item->textRect.u[0];
						item->textRect.y -= (newLineWidth >> 1) * item->textRect.u[1];
					} else {
						item->textRect.x -= newLineWidth >> 1;
					}
				}
				//item->textRect.y = y;
				ToWindowCoords(&item->textRect.x, &item->textRect.y, &item->window);
				//
				buff[newLine] = '\0';
				if (item->textRect.hasVectors)
				{
					DC->drawAngledText(item->textRect.x, item->textRect.y, item->textRect.u, item->textRect.v, item->textscale,
							color, buff, 0, 0, 0, item->textStyle, qfalse);
				} else {
					DC->drawText(item->textRect.x, item->textRect.y, item->textscale, color, buff, 0, 0, 0,
						item->textStyle, qfalse);
				}
			}
			if (*p == '\0') {
				break;
			}
			//Makro - fixed height
			if (item->textHeight) {
				y += (item->textHeight);
			} else {
				y += height + 5;
			}
			p = newLinePtr;
			len = 0;
			newLine = 0;
			newLineWidth = 0;
			continue;
		}
		buff[len++] = *p++;
		buff[len] = '\0';
	}
}

void Item_Text_Wrapped_Paint(itemDef_t * item)
{
	char text[1024];
	const char *p, *start, *textPtr;
	char buff[1024];
	int width, height;
	float x, y;
	vec4_t color;

	// now paint the text and/or any optional images
	// default to left

	if (item->text == NULL) {
		if (item->cvar == NULL) {
			return;
		} else {
			DC->getCVarString(item->cvar, text, sizeof(text));
			textPtr = text;
		}
	} else {
		textPtr = item->text;
	}
	if (*textPtr == '\0') {
		return;
	}

	Item_TextColor(item, &color);
	Item_SetTextExtents(item, &width, &height, textPtr);

	x = item->textRect.x;
	y = item->textRect.y;
	start = textPtr;
	p = strchr(textPtr, '\r');
	while (p && *p) {
		strncpy(buff, start, p - start + 1);
		buff[p - start] = '\0';
		DC->drawText(x, y, item->textscale, color, buff, 0, 0, 0, item->textStyle, qfalse);
		y += height + 5;
		start += p - start + 1;
		p = strchr(p + 1, '\r');
	}
	DC->drawText(x, y, item->textscale, color, start, 0, 0, 0, item->textStyle, qfalse);
}

void Item_Text_Paint(itemDef_t * item)
{
	char text[1024];
	const char *textPtr;
	int height, width;
	vec4_t color;

	if (item->window.flags & WINDOW_WRAPPED) {
		Item_Text_Wrapped_Paint(item);
		return;
	}
	if (item->window.flags & WINDOW_AUTOWRAPPED) {
		Item_Text_AutoWrapped_Paint(item);
		return;
	}

	if (item->text == NULL) {
		if (item->cvar == NULL) {
			return;
		} else {
			DC->getCVarString(item->cvar, text, sizeof(text));
			textPtr = text;
		}
	} else {
		textPtr = item->text;
	}

	// this needs to go here as it sets extents for cvar types as well
	Item_SetTextExtents(item, &width, &height, textPtr);

	if (*textPtr == '\0') {
		return;
	}

	Item_TextColor(item, &color);

	//FIXME: this is a fucking mess
/*
	adjust = 0;
	if (item->textStyle == ITEM_TEXTSTYLE_OUTLINED || item->textStyle == ITEM_TEXTSTYLE_OUTLINESHADOWED) {
		adjust = 0.5;
	}

	if (item->textStyle == ITEM_TEXTSTYLE_SHADOWED || item->textStyle == ITEM_TEXTSTYLE_OUTLINESHADOWED) {
		Fade(&item->window.flags, &DC->Assets.shadowColor[3], DC->Assets.fadeClamp, &item->window.nextTime, DC->Assets.fadeCycle, qfalse);
		DC->drawText(item->textRect.x + DC->Assets.shadowX, item->textRect.y + DC->Assets.shadowY, item->textscale, DC->Assets.shadowColor, textPtr, adjust);
	}
*/

//      if (item->textStyle == ITEM_TEXTSTYLE_OUTLINED || item->textStyle == ITEM_TEXTSTYLE_OUTLINESHADOWED) {
//              Fade(&item->window.flags, &item->window.outlineColor[3], DC->Assets.fadeClamp, &item->window.nextTime, DC->Assets.fadeCycle, qfalse);
//              /*
//              Text_Paint(item->textRect.x-1, item->textRect.y-1, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x, item->textRect.y-1, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x+1, item->textRect.y-1, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x-1, item->textRect.y, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x+1, item->textRect.y, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x-1, item->textRect.y+1, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x, item->textRect.y+1, item->textscale, item->window.foreColor, textPtr, adjust);
//              Text_Paint(item->textRect.x+1, item->textRect.y+1, item->textscale, item->window.foreColor, textPtr, adjust);
//              */
//              DC->drawText(item->textRect.x - 1, item->textRect.y + 1, item->textscale * 1.02, item->window.outlineColor, textPtr, adjust);
//      }

	if (item->window.rectClient.hasVectors)
	{
		DC->drawAngledText(item->textRect.x, item->textRect.y, item->window.rectClient.u, item->window.rectClient.v,
			item->textscale, color, textPtr, 0, 0, 0, item->textStyle, (item->window.flags & WINDOW_FORCE_TEXT_COLOR));
		//debug
		//DC->drawAngledRect(item->textRect.x, item->textRect.y, item->textRect.w, item->textRect.h,
		//	item->textRect.u, item->textRect.v, 2, colorYellow, RECT_FULL);
	} else {
		DC->drawText(item->textRect.x, item->textRect.y, item->textscale, color, textPtr, 0, 0, 0, item->textStyle,
			(item->window.flags & WINDOW_FORCE_TEXT_COLOR));
		//debug
		//DC->drawRect(item->textRect.x, item->textRect.y, item->textRect.w, item->textRect.h, 2, colorYellow);
	}
}

//float                 trap_Cvar_VariableValue( const char *var_name );
//void                  trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );

void Item_TextField_Paint(itemDef_t * item)
{
	char buff[1024];
	vec4_t newColor, lowLight;
	int offset;
	float p[2];
	menuDef_t *parent = (menuDef_t *) item->parent;
	editFieldDef_t *editPtr = (editFieldDef_t *) item->typeData;
	//int maxChars = Text_maxPaintChars(buff+editPtr->paintOffset, item->textscale, item->window.rect.w+item->textalignx);

	Item_Text_Paint(item);

	buff[0] = '\0';

	if (item->cvar) {
		DC->getCVarString(item->cvar, buff, sizeof(buff));
	}

	parent = (menuDef_t *) item->parent;

	if (item->window.flags & WINDOW_HASFOCUS) {
		//Makro - changed to fade from normal text color to focus color
		//lowLight[0] = 0.8 * parent->focusColor[0]; 
		//lowLight[1] = 0.8 * parent->focusColor[1]; 
		//lowLight[2] = 0.8 * parent->focusColor[2]; 
		//lowLight[3] = 0.8 * parent->focusColor[3]; 
		memcpy(lowLight, &item->window.foreColor, sizeof(vec4_t));
		LerpColor(parent->focusColor, lowLight, newColor, 0.5 + 0.5 * sin(DC->realTime / PULSE_DIVISOR));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	offset = (item->text && *item->text) ? 8 : 0;
	Vector2Set(p, item->textRect.x, item->textRect.y);
	if (item->window.rect.hasVectors)
		Vector2MA(p, item->textRect.w + offset, item->window.rect.u, p);
	else
		p[0] += item->textRect.w + offset;
	if (item->window.flags & WINDOW_HASFOCUS && g_editingField) {
		char cursor = DC->getOverstrikeMode()? '_' : '|';

		if (item->window.rect.hasVectors)
			DC->drawAngledTextWithCursor(p[0], p[1],
				item->window.rect.u, item->window.rect.v, item->textscale,
				newColor, buff + editPtr->paintOffset, item->cursorPos - editPtr->paintOffset,
				cursor, editPtr->maxPaintChars, item->textStyle);
		else
			DC->drawTextWithCursor(p[0], p[1], item->textscale,
				newColor, buff + editPtr->paintOffset, item->cursorPos - editPtr->paintOffset,
				cursor, editPtr->maxPaintChars, item->textStyle);
		/*
		DC->drawTextWithCursor(item->textRect.x + item->textRect.w + offset, item->textRect.y, item->textscale,
				       newColor, buff + editPtr->paintOffset, item->cursorPos - editPtr->paintOffset,
				       cursor, maxChars, item->textStyle);
		*/
	} else {
		if (item->window.rect.hasVectors)
			DC->drawAngledText(p[0], p[1],
				item->window.rect.u, item->window.rect.v, item->textscale, newColor,
				buff + editPtr->paintOffset, 0, editPtr->maxPaintChars, 0, item->textStyle, qfalse);
		else
			DC->drawText(p[0], p[1], item->textscale, newColor,
				buff + editPtr->paintOffset, 0, editPtr->maxPaintChars, 0, item->textStyle, qfalse);
		/*
		DC->drawText(item->textRect.x + item->textRect.w + offset, item->textRect.y, item->textscale, newColor,
			     buff + editPtr->paintOffset, 0, maxChars, item->textStyle);
		*/
	}

}




#define YESNO_MARK_FADETIME		150

//Makro - heavily modified
void Item_YesNo_Paint(itemDef_t * item)
{
	vec4_t newColor, lowLight;
	float value;
	menuDef_t *parent = (menuDef_t *) item->parent;
	//Makro - added to simplify the rendering
	float p[2];
	const char *text;
	qboolean on = qfalse;
	yesnoDef_t *data = (yesnoDef_t*)item->typeData;

	//value = (item->cvar) ? DC->getCVarValue(item->cvar) : 0;

	if (item->window.flags & WINDOW_HASFOCUS) {
		//Makro - changed to fade from normal text color to focus color
		//lowLight[0] = 0.8 * parent->focusColor[0]; 
		//lowLight[1] = 0.8 * parent->focusColor[1]; 
		//lowLight[2] = 0.8 * parent->focusColor[2]; 
		//lowLight[3] = 0.8 * parent->focusColor[3]; 
		memcpy(lowLight, &item->window.foreColor, sizeof(vec4_t));
		//Com_Printf("FRAC: %.4f\n", sin((float)DC->realTime / PULSE_DIVISOR));
		LerpColor(parent->focusColor, lowLight, newColor, 0.5 + 0.5 * sin((float)DC->realTime / PULSE_DIVISOR));
		//LerpColor(parent->focusColor, lowLight, newColor, SawTooth(DC->realTime, 1000));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	value = DC->getCVarValue(item->cvar);
	//Makro - grouped checkboxes?
	if (data->groupIndex)
	{
		on = (value == data->activeCvarVal);
	} else {
		on = (value != 0);
	}
	text = (on) ? "Yes" : "No";

	if (item->text) {
		Item_Text_Paint(item);
	}

	if (data->kind == YESNO_TEXT)
	{
		Vector2Set(p, item->textRect.x, item->textRect.y);
		if (item->window.rect.hasVectors)
		{
			if (item->text)
				Vector2MA(p, item->textRect.w + 8, item->window.rect.u, p);

			DC->drawAngledText(p[0], p[1], item->window.rect.u, item->window.rect.v,
				item->textscale, newColor, text, 0, 0, 0, item->textStyle, qfalse);
		} else {
			if (item->text)
				p[0] += item->textRect.w + 8;
			DC->drawText(p[0], p[1], item->textscale, newColor, text,
					 0, 0, 0, item->textStyle, qfalse);
		}
	} else {
		qhandle_t front, back;
		float imgColor[4] = {1, 1, 1, 1};

		if (on != data->wasActive)
			data->lastChangeTime = DC->realTime;
		data->wasActive = on;

		if (on)
		{
			front = DC->Assets.checkBox1;
			back = DC->Assets.checkBox0;
		} else {
			front = DC->Assets.checkBox0;
			back = DC->Assets.checkBox1;
		}

		if (DC->realTime - data->lastChangeTime < YESNO_MARK_FADETIME)
		{
			imgColor[3] = (float) (DC->realTime - data->lastChangeTime) / YESNO_MARK_FADETIME;
		}
		if (item->window.flags & WINDOW_FORECOLORSET)
			imgColor[3] *= item->window.foreColor[3];

		//compute drawing position
		if (data->kind == YESNO_ICON_LEFT)
		{
			if (item->window.rect.hasVectors)
			{
				Vector2Set(p, item->textRect.x, item->textRect.y);
				Vector2MA(p, -item->textRect.h + 0.5f * (item->textRect.h - SCROLLBAR_SIZE), item->window.rect.v, p);
				Vector2MA(p, - SCROLLBAR_SIZE - 8, item->window.rect.u, p);
			} else {
				Vector2Set(p, item->textRect.x - (SCROLLBAR_SIZE + 8),
					item->textRect.y - item->textRect.h + 0.5f * (item->textRect.h - SCROLLBAR_SIZE));
			}
		} else {
			if (item->window.rect.hasVectors)
			{
				Vector2Set(p, item->textRect.x, item->textRect.y);
				Vector2MA(p, -item->textRect.h + 0.5f * (item->textRect.h - SCROLLBAR_SIZE), item->window.rect.v, p);
				Vector2MA(p, item->textRect.w + 8, item->window.rect.u, p);
			} else {
				Vector2Set(p, item->textRect.x + item->textRect.w + 8,
					item->textRect.y - item->textRect.h + 0.5f * (item->textRect.h - SCROLLBAR_SIZE));
			}
		}
		
		if (item->window.rect.hasVectors)
		{
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v,
				imgColor, 0, 0, 1, 1, front);
			imgColor[3] = ((item->window.flags & WINDOW_FORECOLORSET) ? item->window.foreColor[3] : 1.0f) - imgColor[3];
			if (item->window.flags & WINDOW_FORECOLORSET)
				imgColor[3] *= item->window.foreColor[3];
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v,
				imgColor, 0, 0, 1, 1, back);
		} else {
			DC->drawHandlePic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
				 (on) ? DC->Assets.checkBox1 : DC->Assets.checkBox0);
		}
	}
}

void Item_Multi_Paint(itemDef_t * item)
{
	vec4_t newColor, lowLight;
	const char *text;
	menuDef_t *parent = (menuDef_t *) item->parent;
	float p[2];

	if (item->window.flags & WINDOW_HASFOCUS) {
		//Makro - changed to fade from normal text color to focus color
		//lowLight[0] = 0.8 * parent->focusColor[0]; 
		//lowLight[1] = 0.8 * parent->focusColor[1]; 
		//lowLight[2] = 0.8 * parent->focusColor[2]; 
		//lowLight[3] = 0.8 * parent->focusColor[3]; 
		memcpy(lowLight, &item->window.foreColor, sizeof(vec4_t));
		LerpColor(parent->focusColor, lowLight, newColor, 0.5 + 0.5 * sin(DC->realTime / PULSE_DIVISOR));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	text = Item_Multi_Setting(item);
	//Makro - added check
	if (!text)
		text = "";
	
	if (item->text)
	{
		Item_Text_Paint(item);
		Vector2Set(p, item->textRect.x, item->textRect.y);
		//Makro - vectors?
		if (item->window.rect.hasVectors)
			Vector2MA(p, item->textRect.w + 8, item->textRect.u, p);
		else
			p[0] += item->textRect.w + 8;
	}
	else
		Vector2Set(p, item->textRect.x, item->textRect.y);

	//Makro - vectors?
	if (item->window.rect.hasVectors)
	{
		DC->drawAngledText(p[0], p[1],
				item->window.rect.u, item->window.rect.v, item->textscale, newColor, text,
				 0, 0, 0, item->textStyle, qfalse);
	} else {
		DC->drawText(p[0], p[1], item->textscale, newColor, text,
				 0, 0, 0, item->textStyle, qfalse);
	}
}

typedef struct {
	char *command;
	int id;
	int defaultbind1;
	int defaultbind2;
	int bind1;
	int bind2;
} bind_t;

typedef struct {
	char *name;
	float defaultvalue;
	float value;
} configcvar_t;

static bind_t g_bindings[] = {
	//Makro - 3rd column was filled with -1; adding secondary binds
	//              - also, fixed the tabbing
	//Makro - using scores instead of +scores
	{"scores", K_TAB, -1, -1, -1},
	//Makro - button2 was enter
	{"+button2", -1, -1, -1, -1},
	{"+speed", K_SHIFT, -1, -1, -1},
	{"+forward", K_UPARROW, 'w', -1, -1},
	{"+back", K_DOWNARROW, 's', -1, -1},
	{"+moveleft", ',', 'a', -1, -1},
	{"+moveright", '.', 'd', -1, -1},
	{"+moveup", K_SPACE, -1, -1, -1},
	{"+movedown", 'c', -1, -1, -1},
	{"+left", K_LEFTARROW, -1, -1, -1},
	{"+right", K_RIGHTARROW, -1, -1, -1},
	{"+strafe", K_ALT, -1, -1, -1},
	{"+lookup", K_PGDN, -1, -1, -1},
	{"+lookdown", K_DEL, -1, -1, -1},
	{"+mlook", '/', -1, -1, -1},
	{"centerview", K_END, -1, -1, -1},
	{"+zoom", -1, -1, -1, -1},
//Blaze: Reaction Weapon binds
//Jbravo: order is important.
	{"weapon 1", '1', -1, -1, -1},
	{"weapon 2", '2', -1, -1, -1},
	{"weapon 3", '3', -1, -1, -1},
	{"weapon 4", '4', -1, -1, -1},
	{"weapon 5", '5', -1, -1, -1},
	{"weapon 6", '6', -1, -1, -1},
	{"weapon 7", '7', -1, -1, -1},
	{"weapon 8", '8', -1, -1, -1},
	{"weapon 9", '9', -1, -1, -1},
	{"+attack", K_CTRL, K_MOUSE1, -1, -1},
	{"weapprev", '[', -1, -1, -1},
	{"weapnext", ']', 'q', -1, -1},
	//Makro - button3 was mouse3
	{"+button3", -1, -1, -1, -1},
	{"messagemode", 't', -1, -1, -1},
	{"messagemode2", -1, -1, -1, -1},
	{"messagemode3", -1, -1, -1, -1},
	{"messagemode4", -1, -1, -1, -1},
	{"bandage", 'b', -1, -1, -1},
	//reload
	{"+button5", 'r', -1, -1, -1},
	{"weapon", K_MOUSE3, -1, -1, -1},
	{"opendoor", K_ENTER, -1, -1, -1},
//TTI: replacing "dropweapon" with the newer "drop weapon", the same goes for "dropitem"
	{"drop weapon", 'x', -1, -1, -1},
	{"drop item", 'z', -1, -1, -1},
	{"irvision", 'v', -1, -1, -1},
//Makro - this one was missing
	{"specialweapon", 'e', -1, -1, -1},
//Makro - for the weapon/item, join, presets and tkok menus
	{"ui_RQ3_loadout", 'l', -1, -1, -1},
	{"ui_RQ3_joinTeam", 'j', -1, -1, -1},
	{"ui_RQ3_presets", -1, -1, -1, -1},
	{"ui_RQ3_tkok", -1, -1, -1, -1},
	{"screenshot", -1, -1, -1, -1},
	{"screenshotJPEG", K_F12, -1, -1, -1},
//TTI: more binds
	{"drop case", -1, -1, -1, -1},
	{"+voiprecord", -1, -1, -1, -1}
};

static const int g_bindCount = sizeof(g_bindings) / sizeof(bind_t);

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static configcvar_t g_configcvars[] =
{
	{"cl_run",			0,					0},
	{"m_pitch",			0,					0},
	{"cg_autoswitch",	0,					0},
	{"sensitivity",		0,					0},
	{"in_joystick",		0,					0},
	{"joy_threshold",	0,					0},
	{"m_filter",		0,					0},
	{"cl_freelook",		0,					0},
	{NULL,				0,					0}
};
#endif
*/

/*
=================
Controls_GetKeyAssignment
=================
*/
static void Controls_GetKeyAssignment(char *command, int *twokeys)
{
	int count;
	int j;
	char b[256];

	twokeys[0] = twokeys[1] = -1;
	count = 0;

	for (j = 0; j < 256; j++) {
		DC->getBindingBuf(j, b, 256);
		if (*b == 0) {
			continue;
		}
		if (!Q_stricmp(b, command)) {
			twokeys[count] = j;
			count++;
			if (count == 2) {
				break;
			}
		}
	}
}

/*
=================
Controls_GetConfig
=================
*/
void Controls_GetConfig(void)
{
	int i;
	int twokeys[2];

	// iterate each command, get its numeric binding
	for (i = 0; i < g_bindCount; i++) {

		Controls_GetKeyAssignment(g_bindings[i].command, twokeys);

		g_bindings[i].bind1 = twokeys[0];
		g_bindings[i].bind2 = twokeys[1];
	}

	//s_controls.invertmouse.curvalue  = DC->getCVarValue( "m_pitch" ) < 0;
	//s_controls.smoothmouse.curvalue  = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "m_filter" ) );
	//s_controls.alwaysrun.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_run" ) );
	//s_controls.autoswitch.curvalue   = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cg_autoswitch" ) );
	//s_controls.sensitivity.curvalue  = UI_ClampCvar( 2, 30, Controls_GetCvarValue( "sensitivity" ) );
	//s_controls.joyenable.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "in_joystick" ) );
	//s_controls.joythreshold.curvalue = UI_ClampCvar( 0.05, 0.75, Controls_GetCvarValue( "joy_threshold" ) );
	//s_controls.freelook.curvalue     = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_freelook" ) );
}

/*
=================
Controls_SetConfig
=================
*/
void Controls_SetConfig(qboolean restart)
{
	int i;

	// iterate each command, get its numeric binding
	for (i = 0; i < g_bindCount; i++) {

		if (g_bindings[i].bind1 != -1) {
			DC->setBinding(g_bindings[i].bind1, g_bindings[i].command);

			if (g_bindings[i].bind2 != -1)
				DC->setBinding(g_bindings[i].bind2, g_bindings[i].command);
		}
	}

	//if ( s_controls.invertmouse.curvalue )
	//      DC->setCVar("m_pitch", va("%f),-fabs( DC->getCVarValue( "m_pitch" ) ) );
	//else
	//      trap_Cvar_SetValue( "m_pitch", fabs( trap_Cvar_VariableValue( "m_pitch" ) ) );

	//trap_Cvar_SetValue( "m_filter", s_controls.smoothmouse.curvalue );
	//trap_Cvar_SetValue( "cl_run", s_controls.alwaysrun.curvalue );
	//trap_Cvar_SetValue( "cg_autoswitch", s_controls.autoswitch.curvalue );
	//trap_Cvar_SetValue( "sensitivity", s_controls.sensitivity.curvalue );
	//trap_Cvar_SetValue( "in_joystick", s_controls.joyenable.curvalue );
	//trap_Cvar_SetValue( "joy_threshold", s_controls.joythreshold.curvalue );
	//trap_Cvar_SetValue( "cl_freelook", s_controls.freelook.curvalue );
	DC->executeText(EXEC_APPEND, "in_restart\n");
	//trap_Cmd_ExecuteText( EXEC_APPEND, "in_restart\n" );
}

/*
=================
Controls_SetDefaults
=================
*/
void Controls_SetDefaults(void)
{
	int i;

	// iterate each command, set its default binding
	for (i = 0; i < g_bindCount; i++) {
		g_bindings[i].bind1 = g_bindings[i].defaultbind1;
		g_bindings[i].bind2 = g_bindings[i].defaultbind2;
	}

	//s_controls.invertmouse.curvalue  = Controls_GetCvarDefault( "m_pitch" ) < 0;
	//s_controls.smoothmouse.curvalue  = Controls_GetCvarDefault( "m_filter" );
	//s_controls.alwaysrun.curvalue    = Controls_GetCvarDefault( "cl_run" );
	//s_controls.autoswitch.curvalue   = Controls_GetCvarDefault( "cg_autoswitch" );
	//s_controls.sensitivity.curvalue  = Controls_GetCvarDefault( "sensitivity" );
	//s_controls.joyenable.curvalue    = Controls_GetCvarDefault( "in_joystick" );
	//s_controls.joythreshold.curvalue = Controls_GetCvarDefault( "joy_threshold" );
	//s_controls.freelook.curvalue     = Controls_GetCvarDefault( "cl_freelook" );
}

int BindingIDFromName(const char *name)
{
	int i;

	for (i = 0; i < g_bindCount; i++) {
		if (Q_stricmp(name, g_bindings[i].command) == 0) {
			return i;
		}
	}
	return -1;
}

char g_nameBind1[32];
char g_nameBind2[32];

void BindingFromName(const char *cvar)
{
	int i, b1, b2;

	// iterate each command, set its default binding
	for (i = 0; i < g_bindCount; i++) {
		if (Q_stricmp(cvar, g_bindings[i].command) == 0) {
			b1 = g_bindings[i].bind1;
			if (b1 == -1) {
				break;
			}
			DC->keynumToStringBuf(b1, g_nameBind1, 32);
			Q_strupr(g_nameBind1);

			b2 = g_bindings[i].bind2;
			if (b2 != -1) {
				DC->keynumToStringBuf(b2, g_nameBind2, 32);
				Q_strupr(g_nameBind2);
				strcat(g_nameBind1, " or ");
				strcat(g_nameBind1, g_nameBind2);
			}
			return;
		}
	}
	strcpy(g_nameBind1, "[ not assigned ]");
}

void Item_Slider_Paint(itemDef_t * item)
{
	vec4_t newColor;
	float x, y, value;
	menuDef_t *parent = (menuDef_t *) item->parent;
	float frac;
	editFieldDef_t *editDef = item->typeData;
	Point pt;

	if (!editDef)
		return;

	value = (item->cvar) ? DC->getCVarValue(item->cvar) : 0;
	if (value > editDef->maxVal)
		value = editDef->maxVal;
	else if (value < editDef->minVal)
		value = editDef->minVal;
	frac = (editDef->maxVal > editDef->minVal) ? (value - editDef->minVal)/(editDef->maxVal - editDef->minVal) : 0;

	Item_TextColor(item, &newColor);

	if (item->text) {
		Item_Text_Paint(item);
		//Makro - vectors?
		if (item->textRect.hasVectors)
		{
			float xoffset = item->textRect.w + 8, yoffset = -(item->textRect.h + SLIDER_HEIGHT)/2;
			x = item->textRect.x + xoffset*item->textRect.u[0] + yoffset*item->textRect.v[0];
			y = item->textRect.y + xoffset*item->textRect.u[1] + yoffset*item->textRect.v[1];
		} else {
			x = item->textRect.x + item->textRect.w + 8;
			y = item->textRect.y - (item->textRect.h + SLIDER_HEIGHT)/2;
		}
	} else {
		x = item->window.rect.x;
		y = item->window.rect.y;
	}
	//paint the slider
	if (item->textRect.hasVectors)
	{
		DC->drawAngledPic(x, y, SLIDER_WIDTH, SLIDER_HEIGHT, item->textRect.u, item->textRect.v, 
			item->window.foreColor, 0, 0, 1, 1, DC->Assets.sliderBar0);
		//paint the partial selection
		if (frac > 0)
			DC->drawAngledPic(x, y, SLIDER_WIDTH * frac, SLIDER_HEIGHT, item->textRect.u, item->textRect.v, 
				newColor, 0, 0, frac, 1, DC->Assets.sliderBar1);
	} else {
		DC->setColor(item->window.foreColor);
		DC->drawHandlePic(x, y, SLIDER_WIDTH, SLIDER_HEIGHT, DC->Assets.sliderBar0);
		//paint the partial selection
		DC->setColor(newColor);
		if (frac > 0)
			DC->drawStretchPic(x, y, SLIDER_WIDTH * frac, 0, 0, frac, 1, SLIDER_HEIGHT, DC->Assets.sliderBar1, qtrue);
	}
	DC->setColor(NULL);

	pt = Item_Slider_ThumbPosition(item);
	//paint the thumb
	if (item->textRect.hasVectors)
	{
		float srx = pt.x - (SLIDER_THUMB_WIDTH / 2) * item->textRect.u[0];
		float sry = pt.y - (SLIDER_THUMB_WIDTH / 2) * item->textRect.u[1];
		DC->drawAngledPic(srx, sry, SLIDER_THUMB_WIDTH, SLIDER_THUMB_HEIGHT, item->textRect.u, item->textRect.v, 
			newColor, 0, 0, 1, 1, DC->Assets.sliderThumb);
	} else {
		pt.x -= (SLIDER_THUMB_WIDTH / 2);
		DC->setColor(newColor);
		DC->drawHandlePic(pt.x, pt.y, SLIDER_THUMB_WIDTH, SLIDER_THUMB_HEIGHT, DC->Assets.sliderThumb);
	}
}

void Item_Bind_Paint(itemDef_t * item)
{
	vec4_t newColor, lowLight;
	float value;
	int maxChars = 0;
	menuDef_t *parent = (menuDef_t *) item->parent;
	editFieldDef_t *editPtr = (editFieldDef_t *) item->typeData;

	if (editPtr) {
		maxChars = editPtr->maxPaintChars;
	}

	value = (item->cvar) ? DC->getCVarValue(item->cvar) : 0;

	if (item->window.flags & WINDOW_HASFOCUS) {
		//Makro - if you bind a key, the item shouldn't keep flashing when you're done
		if (g_bindItem == item && g_waitingForKey) {
			lowLight[0] = 0.8f * 1.0f;
			lowLight[1] = 0.8f * 0.0f;
			lowLight[2] = 0.8f * 0.0f;
			lowLight[3] = 0.8f * 1.0f;
		} else {
			//Makro - changed to use item forecolor
			//lowLight[0] = 0.8f * parent->focusColor[0]; 
			//lowLight[1] = 0.8f * parent->focusColor[1]; 
			//lowLight[2] = 0.8f * parent->focusColor[2]; 
			//lowLight[3] = 0.8f * parent->focusColor[3]; 
			memcpy(lowLight, &item->window.foreColor, sizeof(item->window.foreColor));
		}
		LerpColor(parent->focusColor, lowLight, newColor, 0.5 + 0.5 * sin(DC->realTime / (float)PULSE_DIVISOR));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	if (item->text) {
		Item_Text_Paint(item);
		BindingFromName(item->cvar);
		//Makro - vectors
		if (item->window.rect.hasVectors)
		{
			DC->drawAngledText(item->textRect.x + (item->textRect.w + 8) * item->window.rect.u[0],
				item->textRect.y + (item->textRect.w + 8) * item->window.rect.u[1],
				item->window.rect.u, item->window.rect.v, item->textscale, newColor,
				     g_nameBind1, 0, maxChars, 0, item->textStyle, qfalse);
		} else {
			DC->drawText(item->textRect.x + item->textRect.w + 8, item->textRect.y, item->textscale, newColor,
				     g_nameBind1, 0, maxChars, 0, item->textStyle, qfalse);
		}
	} else {
		DC->drawText(item->textRect.x, item->textRect.y, item->textscale, newColor,
			     (value != 0) ? "FIXME" : "FIXME", 0, maxChars, 0, item->textStyle, qfalse);
	}
}

qboolean Display_KeyBindPending()
{
	return g_waitingForKey;
}

void UI_ClearBind(const char *cvar)
{
	int id;

	id = BindingIDFromName(cvar);
	if (id != -1) {
		if (g_bindings[id].bind1 != -1) {
			DC->setBinding(g_bindings[id].bind1, "");
			g_bindings[id].bind1 = -1;
		}
		if (g_bindings[id].bind2 != -1) {
			DC->setBinding(g_bindings[id].bind2, "");
			g_bindings[id].bind2 = -1;
		}
	}

	Controls_SetConfig(qtrue);
	g_waitingForKey = qfalse;
	g_bindItem = NULL;

}

qboolean Item_Bind_HandleKey(itemDef_t * item, int key, qboolean down)
{
	int id;
	int i;
	qboolean ok, returnVal;

	//Makro - the mouse doesn't have to be over the item unless we're clicking on it instead of using the keyboard
	ok = (item->window.flags & WINDOW_HASFOCUS) &&
		(Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory) || !UI_IsMouse(key));

	if (ok && !g_waitingForKey) {
		returnVal = qfalse;
		if (down && (key == K_MOUSE1 || key == K_ENTER)) {
			g_waitingForKey = qtrue;
			g_bindItem = item;
			returnVal = qtrue;
			//Makro - moved backspace code here; added up/down functionality (wtf was this missing?)
		} else if (key == K_BACKSPACE) {
			UI_ClearBind(item->cvar);
			returnVal = qtrue;
		}
		return returnVal;
	} else {
		if (!g_waitingForKey || g_bindItem == NULL) {
			return qfalse;
		}

		if (key & K_CHAR_FLAG) {
			return qfalse;
		}

		switch (key) {
		case K_ESCAPE:
			g_waitingForKey = qfalse;
			return qtrue;
			/* Makro - moved this
			   case K_BACKSPACE:
			   UI_ClearBind
			   return qtrue;
			 */
		case '`':
			return qtrue;
		}
	}

	if (key != -1) {

		for (i = 0; i < g_bindCount; i++) {

			if (g_bindings[i].bind2 == key) {
				g_bindings[i].bind2 = -1;
			}

			if (g_bindings[i].bind1 == key) {
				g_bindings[i].bind1 = g_bindings[i].bind2;
				g_bindings[i].bind2 = -1;
			}
		}
	}

	id = BindingIDFromName(item->cvar);

	if (id != -1) {
		if (key == -1) {
			if (g_bindings[id].bind1 != -1) {
				DC->setBinding(g_bindings[id].bind1, "");
				g_bindings[id].bind1 = -1;
			}
			if (g_bindings[id].bind2 != -1) {
				DC->setBinding(g_bindings[id].bind2, "");
				g_bindings[id].bind2 = -1;
			}
		} else if (g_bindings[id].bind1 == -1) {
			g_bindings[id].bind1 = key;
		} else if (g_bindings[id].bind1 != key && g_bindings[id].bind2 == -1) {
			g_bindings[id].bind2 = key;
		} else {
			DC->setBinding(g_bindings[id].bind1, "");
			DC->setBinding(g_bindings[id].bind2, "");
			g_bindings[id].bind1 = key;
			g_bindings[id].bind2 = -1;
		}
	}

	Controls_SetConfig(qtrue);
	g_waitingForKey = qfalse;

	return qtrue;
}

void AdjustFrom640(float *x, float *y, float *w, float *h)
{
	*x = *x * DC->xscale + DC->bias;
	*y *= DC->yscale;
	*w *= DC->xscale;
	*h *= DC->yscale;
}

void Item_Model_Paint(itemDef_t * item)
{
	float x, y, w, h;
	refdef_t refdef;
	refEntity_t ent;
	vec3_t mins, maxs, origin;
	vec3_t angles;
	modelDef_t *modelPtr = (modelDef_t *) item->typeData;

	if (modelPtr == NULL) {
		return;
	}
	// setup the refdef
	memset(&refdef, 0, sizeof(refdef));
	refdef.rdflags = RDF_NOWORLDMODEL;
	AxisClear(refdef.viewaxis);
	//Makro - removed +1 / -2 offsets
	//this way, clipping is done exactly at the specifiend co-ordinates
	x = item->window.rect.x; //+1
	y = item->window.rect.y; //+1
	w = item->window.rect.w; //-2
	h = item->window.rect.h; //-2

	AdjustFrom640(&x, &y, &w, &h);

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	DC->modelBounds(item->asset, mins, maxs);

	origin[2] = -0.5 * (mins[2] + maxs[2]);
	origin[1] = 0.5 * (mins[1] + maxs[1]);

	// calculate distance so the model nearly fills the box
	// Makro - note - this doesn't seem right to me
	if (qtrue) {
		float len = 0.5 * (maxs[2] - mins[2]);

		origin[0] = len / 0.268;	// len / tan( fov/2 )
		//origin[0] = len / tan(w/2);
	} else {
		origin[0] = item->textscale;
	}
	refdef.fov_x = (modelPtr->fov_x) ? modelPtr->fov_x : w;
	refdef.fov_y = (modelPtr->fov_y) ? modelPtr->fov_y : h;

	//refdef.fov_x = (int)((float)refdef.width / 640.0f * 90.0f);
	//xx = refdef.width / tan( refdef.fov_x / 360 * M_PI );
	//refdef.fov_y = atan2( refdef.height, xx );
	//refdef.fov_y *= ( 360 / M_PI );

	DC->clearScene();

	refdef.time = DC->realTime;

	// add the model

	memset(&ent, 0, sizeof(ent));

	//adjust = 5.0 * sin( (float)uis.realtime / 500 );
	//adjust = 360 % (int)((float)uis.realtime / 1000);
	//VectorSet( angles, 0, 0, 1 );

	// use item storage to track
	if (modelPtr->rotationSpeed) {
		if (DC->realTime > item->window.nextTime) {
			item->window.nextTime = DC->realTime + modelPtr->rotationSpeed;
			//Makro - now we're using 3 angles, not just one
			//modelPtr->angle = (int)(modelPtr->angle + 1) % 360;
			modelPtr->angles[0] = (int) (modelPtr->angles[0] + 1) % 360;
		}
	}
	//Makro - now we're using 3 angles, not just one
	//VectorSet( angles, 0, modelPtr->angle, 0 );
	angles[YAW] = modelPtr->angles[0];
	angles[PITCH] = modelPtr->angles[1];
	angles[ROLL] = modelPtr->angles[2];
	AnglesToAxis(angles, ent.axis);

	//Makro - maybe this will fix the origin bug (model_origin not being taken into account)
	origin[0] += modelPtr->origin[0];
	origin[1] += modelPtr->origin[1];
	origin[2] += modelPtr->origin[2];

	ent.hModel = item->asset;
	VectorCopy(origin, ent.origin);
	VectorCopy(origin, ent.lightingOrigin);
	ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy(ent.origin, ent.oldorigin);

	DC->addRefEntityToScene(&ent);
	DC->renderScene(&refdef);

}

void Item_Image_Paint(itemDef_t * item)
{
	if (item == NULL) {
		return;
	}
	DC->drawHandlePic(item->window.rect.x + 1, item->window.rect.y + 1, item->window.rect.w - 2,
			  item->window.rect.h - 2, item->asset);
}

//Makro - added vector support
void Item_ListBox_Paint(itemDef_t * item)
{
	float x, y, size, count, i, thumb;
	qhandle_t image;
	qhandle_t optionalImage;
	listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;

	// the listbox is horizontal or vertical and has a fixed size scroll bar going either direction
	// elements are enumerated from the DC and either text or image handles are acquired from the DC as well
	// textscale is used to size the text, textalignx and textaligny are used to size image elements
	// there is no clipping available so only the last completely visible item is painted
	count = DC->feederCount(item->special);
	// default is vertical if horizontal flag is not here

	//Makro - added just in case
	DC->setColor(colorWhite);

	
	// HORIZONTAL //

	if (item->window.flags & WINDOW_HORIZONTAL) {
		//vectors?
		if (item->window.rect.hasVectors) {
			float p[2];
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, 1, item->window.rect.u, p);
			Vector2MA(p, item->window.rect.h - SCROLLBAR_SIZE - 1, item->window.rect.v, p);
			// draw scrollbar in bottom of the window
			// bar
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_LEFTARROW)
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
					item->window.rect.u, item->window.rect.v, item->window.foreColor, 0, 0, 1, 1,
					DC->Assets.scrollBarArrowLeft2);
			else
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
					item->window.rect.u, item->window.rect.v, item->window.foreColor, 0, 0, 1, 1,
					DC->Assets.scrollBarArrowLeft);
			Vector2MA(p, SCROLLBAR_SIZE - 1, item->window.rect.u, p);
			size = item->window.rect.w - (SCROLLBAR_SIZE * 4);
			//start
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
				item->window.rect.u, item->window.rect.v, item->window.foreColor, 0, 0, 0.25f, 1,
				DC->Assets.scrollBarH);
			Vector2MA(p, SCROLLBAR_SIZE, item->window.rect.u, p);
			//middle
			DC->drawAngledPic(p[0], p[1], size, SCROLLBAR_SIZE,
				item->window.rect.u, item->window.rect.v, item->window.foreColor, 0.25f, 0, 0.75f, 1,
				DC->Assets.scrollBarH);
			Vector2MA(p, size, item->window.rect.u, p);
			//end
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
				item->window.rect.u, item->window.rect.v, item->window.foreColor, 0.75f, 0, 1, 1,
				DC->Assets.scrollBarH);
			Vector2MA(p, SCROLLBAR_SIZE, item->window.rect.u, p);
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_RIGHTARROW)
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
					item->window.rect.u, item->window.rect.v, item->window.foreColor, 0, 0, 1, 1,
					DC->Assets.scrollBarArrowRight2);
			else
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
					item->window.rect.u, item->window.rect.v, item->window.foreColor, 0, 0, 1, 1,
					DC->Assets.scrollBarArrowRight);
			// thumb
			thumb = Item_ListBox_ThumbDrawPosition(item);	//Item_ListBox_ThumbPosition(item);
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.h - SCROLLBAR_SIZE - 1, item->window.rect.v, p);
			Vector2MA(p, thumb - item->window.rect.x, item->window.rect.u, p);
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v, 
				item->window.foreColor, 0, 0, 1, 1, DC->Assets.scrollBarThumb);
		//no vectors?
		} else {
			// draw scrollbar in bottom of the window
			// bar
			x = item->window.rect.x + 1;
			y = item->window.rect.y + item->window.rect.h - SCROLLBAR_SIZE - 1;
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_LEFTARROW)
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowLeft2);
			else
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowLeft);
			x += SCROLLBAR_SIZE - 1;
			size = item->window.rect.w - (SCROLLBAR_SIZE * 4);
			//start
			DC->drawStretchPic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, 0, 0, 0.25f, 1, DC->Assets.scrollBarH, qtrue);
			x += SCROLLBAR_SIZE;
			//middle
			DC->drawStretchPic(x, y, size, SCROLLBAR_SIZE, 0.25f, 0, 0.75f, 1, DC->Assets.scrollBarH, qtrue);
			x += size;
			//start
			DC->drawStretchPic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, 0.75f, 0, 1, 1, DC->Assets.scrollBarH, qtrue);
			x += SCROLLBAR_SIZE;
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_RIGHTARROW)
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowRight2);
			else
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowRight);
			// thumb
			thumb = Item_ListBox_ThumbDrawPosition(item);	//Item_ListBox_ThumbPosition(item);
			if (thumb > x - SCROLLBAR_SIZE - 1) {
				thumb = x - SCROLLBAR_SIZE - 1;
			}
			DC->drawHandlePic(thumb, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarThumb);
		}
		//
		listPtr->endPos = listPtr->startPos;
		size = item->window.rect.w - 2;
		// items
		// size contains max available space
		if (listPtr->elementStyle == LISTBOX_IMAGE) {
			//vectors?
			if (item->window.rect.hasVectors)
			{
				float p[2];
				Vector2Set(p, item->window.rect.x, item->window.rect.y);
				Vector2MA(p, 1, item->window.rect.u, p);
				Vector2MA(p, 1, item->window.rect.v, p);
				for (i = listPtr->startPos; i < count; i++) {
					// always draw at least one
					// which may overdraw the box if it is too small for the element
					image = DC->feederItemImage(item->special, i);

					//Makro - added background
					if (i == item->cursorPos) {
						DC->drawAngledPic(p[0], p[1], listPtr->elementWidth - 2,
							listPtr->elementHeight - 2, item->window.rect.u, item->window.rect.v,
							item->window.outlineColor, 0, 0, 1, 1, DC->whiteShader);
						//Makro - add a render point here; hackish, but it gets things done
						if (DC->pendingPolys)
						{
							UI_Render2DScene();
						}
					}
					
					if (image) {
						DC->drawAngledPic(p[0], p[1], listPtr->elementWidth - 2,
							listPtr->elementHeight - 2, item->window.rect.u, item->window.rect.v,
							item->window.foreColor, 0, 0, 1, 1, image);
					}
					
					if (i == item->cursorPos) {
						//Makro - add a render point here; hackish, but it gets things done
						if (DC->pendingPolys)
						{
							UI_Render2DScene();
						}
						DC->drawAngledRect(p[0], p[1], listPtr->elementWidth - 1, listPtr->elementHeight - 1,
							item->window.rect.u, item->window.rect.v,
							item->window.borderSize, item->window.borderColor, RECT_FULL, DC->whiteShader);
					}
					
					size -= listPtr->elementWidth;
					if (size < listPtr->elementWidth) {
						listPtr->drawPadding = size;	//listPtr->elementWidth - size;
						break;
					}
					Vector2MA(p, listPtr->elementWidth, item->window.rect.u, p);
					listPtr->endPos++;
					// fit++;
				}
			//no vectors
			} else {
				// fit = 0;
				x = item->window.rect.x + 1;
				y = item->window.rect.y + 1;
				for (i = listPtr->startPos; i < count; i++) {
					// always draw at least one
					// which may overdraw the box if it is too small for the element
					//Makro - added background
					if (i == item->cursorPos)
					{
						DC->setColor(item->window.outlineColor);
						DC->drawHandlePic(x + 1, y + 1, listPtr->elementWidth - 2,
							listPtr->elementHeight - 2, DC->whiteShader);
						DC->setColor(item->window.foreColor);
					}

					image = DC->feederItemImage(item->special, i);
					if (image) {
						DC->drawHandlePic(x + 1, y + 1, listPtr->elementWidth - 2,
							listPtr->elementHeight - 2, image);
					}
					
					if (i == item->cursorPos) {
						//Makro - added shader parm
						DC->drawRect(x, y, listPtr->elementWidth - 1, listPtr->elementHeight - 1,
							item->window.borderSize, item->window.borderColor, DC->whiteShader);
					}
					
					size -= listPtr->elementWidth;
					if (size < listPtr->elementWidth) {
						listPtr->drawPadding = size;	//listPtr->elementWidth - size;
						break;
					}
					x += listPtr->elementWidth;
					listPtr->endPos++;
					// fit++;
				}
			}
		} else {
			//
		}
	
	
	// VERTICAL //


	} else {
		//vectors?
		if (item->window.rect.hasVectors) {
			float p[2];
			// draw scrollbar to right side of the window
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE - 1, item->window.rect.u, p);
			Vector2MA(p, 1, item->window.rect.v, p);
			
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_LEFTARROW)
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
				item->window.rect.u, item->window.rect.v, colorWhite, 0, 0, 1, 1, DC->Assets.scrollBarArrowUp2);
			else
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE,
				item->window.rect.u, item->window.rect.v, colorWhite, 0, 0, 1, 1, DC->Assets.scrollBarArrowUp);
			
			Vector2MA(p, SCROLLBAR_SIZE - 1, item->window.rect.v, p);
			

			listPtr->endPos = listPtr->startPos;
			size = item->window.rect.h - (SCROLLBAR_SIZE * 4);
			
			//start
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v,
				colorWhite, 0, 0, 1, 0.25f, DC->Assets.scrollBarV);
			//middle
			Vector2MA(p, SCROLLBAR_SIZE, item->window.rect.v, p);
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, size, item->window.rect.u, item->window.rect.v,
				colorWhite, 0, 0.25f, 1, 0.75f, DC->Assets.scrollBarV);
			//end
			Vector2MA(p, size, item->window.rect.v, p);
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v,
				colorWhite, 0, 0.75f, 1, 1, DC->Assets.scrollBarV);
			Vector2MA(p, SCROLLBAR_SIZE, item->window.rect.v, p);

			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_RIGHTARROW)
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v, 
				colorWhite, 0, 0, 1, 1, DC->Assets.scrollBarArrowDown2);
			else
				DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v, 
				colorWhite, 0, 0, 1, 1, DC->Assets.scrollBarArrowDown);
			
			// thumb
			thumb = Item_ListBox_ThumbDrawPosition(item);	//Item_ListBox_ThumbPosition(item);
			Vector2Set(p, item->window.rect.x, item->window.rect.y);
			Vector2MA(p, item->window.rect.w - SCROLLBAR_SIZE - 1, item->window.rect.u, p);
			Vector2MA(p, thumb - item->window.rect.y, item->window.rect.v, p);
			DC->drawAngledPic(p[0], p[1], SCROLLBAR_SIZE, SCROLLBAR_SIZE, item->window.rect.u, item->window.rect.v, 
				colorWhite, 0, 0, 1, 1, DC->Assets.scrollBarThumb);
		//no vectors?
		} else {
			// draw scrollbar to right side of the window
			x = item->window.rect.x + item->window.rect.w - SCROLLBAR_SIZE - 1;
			y = item->window.rect.y + 1;
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_LEFTARROW)
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowUp2);
			else
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowUp);
			y += SCROLLBAR_SIZE - 1;
		
			listPtr->endPos = listPtr->startPos;
			size = item->window.rect.h - (SCROLLBAR_SIZE * 4);
			//start
			DC->drawStretchPic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, 0, 0, 1, 0.25f, DC->Assets.scrollBarV, qtrue);
			y += SCROLLBAR_SIZE;
			//middle
			DC->drawStretchPic(x, y, SCROLLBAR_SIZE, size, 0, 0.25f, 1, 0.75f, DC->Assets.scrollBarV, qtrue);
			y += size;
			//end
			DC->drawStretchPic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, 0, 0.75f, 1, 1, DC->Assets.scrollBarV, qtrue);
			y += SCROLLBAR_SIZE;
			
			//clicked?
			if (itemCapture == item && item->window.flags & WINDOW_LB_RIGHTARROW)
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowDown2);
			else
				DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowDown);
			// thumb
			thumb = Item_ListBox_ThumbDrawPosition(item);	//Item_ListBox_ThumbPosition(item);
			if (thumb > y - SCROLLBAR_SIZE - 1) {
				thumb = y - SCROLLBAR_SIZE - 1;
			}
			DC->drawHandlePic(x, thumb, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarThumb);
		}
		// adjust size for item painting
		size = item->window.rect.h - 2;
		if (listPtr->elementStyle == LISTBOX_IMAGE) {
			// fit = 0;
			x = item->window.rect.x + 1;
			y = item->window.rect.y + 1;
			for (i = listPtr->startPos; i < count; i++) {
				// always draw at least one
				// which may overdraw the box if it is too small for the element
				image = DC->feederItemImage(item->special, i);
				if (image) {
					DC->drawHandlePic(x + 1, y + 1, listPtr->elementWidth - 2,
							  listPtr->elementHeight - 2, image);
				}

				if (i == item->cursorPos) {
					//Makro - added shader parm
					DC->drawRect(x, y, listPtr->elementWidth - 1, listPtr->elementHeight - 1,
						     item->window.borderSize, item->window.borderColor, DC->whiteShader);
				}

				listPtr->endPos++;
				size -= listPtr->elementWidth;
				if (size < listPtr->elementHeight) {
					listPtr->drawPadding = listPtr->elementHeight - size;
					break;
				}
				y += listPtr->elementHeight;
				// fit++;
			}
		} else {
			x = item->window.rect.x + 1;
			y = item->window.rect.y + 1;
			for (i = listPtr->startPos; i < count; i++) {
				const char *text;

				// always draw at least one
				// which may overdraw the box if it is too small for the element

				if (listPtr->numColumns > 0) {
					int j;

					for (j = 0; j < listPtr->numColumns; j++) {
						text = DC->feederItemText(item->special, i, j, &optionalImage);
						if (optionalImage >= 0) {
							//TODO: vectors
							DC->drawHandlePic(x + 4 + listPtr->columnInfo[j].pos,
									  y - 1 + listPtr->elementHeight / 2,
									  listPtr->columnInfo[j].width,
									  listPtr->columnInfo[j].width, optionalImage);
						} else if (text) {
							if (item->window.rect.hasVectors) {
								float p[2];
								Vector2Set(p, x, y);
								Vector2MA(p, 4 + listPtr->columnInfo[j].pos, item->window.rectClient.u, p);
								Vector2MA(p, listPtr->elementHeight, item->window.rectClient.v, p);
								DC->drawAngledText(p[0], p[1],
									item->window.rectClient.u, item->window.rectClient.v, item->textscale,
									item->window.foreColor, text, 0,
									listPtr->columnInfo[j].maxChars, listPtr->columnInfo[j].width,
									item->textStyle, (item->window.flags & WINDOW_FORCE_TEXT_COLOR));
							} else {
								DC->drawText(x + 4 + listPtr->columnInfo[j].pos,
									y + listPtr->elementHeight, item->textscale,
									item->window.foreColor, text, 0,
									listPtr->columnInfo[j].maxChars, listPtr->columnInfo[j].width,
									item->textStyle, (item->window.flags & WINDOW_FORCE_TEXT_COLOR));
							}
						}
					}
				} else {
					text = DC->feederItemText(item->special, i, 0, &optionalImage);
					if (optionalImage >= 0) {
						//DC->drawHandlePic(x + 4 + listPtr->elementHeight, y, listPtr->columnInfo[j].width, listPtr->columnInfo[j].width, optionalImage);
					} else if (text) {
						//vectors?
						if (item->window.rect.hasVectors) {
							float p[2];
							Vector2Set(p, x, y);
							Vector2MA(p, 4, item->window.rectClient.u, p);
							Vector2MA(p, listPtr->elementHeight, item->window.rectClient.v, p);
							DC->drawAngledText(p[0], p[1],
								item->window.rectClient.u, item->window.rectClient.v, item->textscale,
								item->window.foreColor, text, 0, 0, 0, item->textStyle, qfalse);
						} else {
							DC->drawText(x + 4, y + listPtr->elementHeight, item->textscale,
								item->window.foreColor, text, 0, 0, 0, item->textStyle, qfalse);
						}
					}
				}

				//selected item?
				if (i == item->cursorPos) {
					//vectors?
					if (item->window.rect.hasVectors) {
						float p[2];
						Vector2Set(p, x, y);
						Vector2MA(p, 2, item->window.rectClient.u, p);
						Vector2MA(p, 2, item->window.rectClient.v, p);
						DC->drawAngledPic(p[0], p[1],
							item->window.rect.w - SCROLLBAR_SIZE - 4, listPtr->elementHeight,
							item->window.rectClient.u, item->window.rectClient.v,
							item->window.outlineColor, 0, 0, 1, 1, DC->whiteShader);
					} else {
						DC->fillRect(x + 2, y + 2, item->window.rect.w - SCROLLBAR_SIZE - 4,
							listPtr->elementHeight, item->window.outlineColor);
					}
				}

				size -= listPtr->elementHeight;
				if (size < listPtr->elementHeight) {
					listPtr->drawPadding = listPtr->elementHeight - size;
					break;
				}
				listPtr->endPos++;
				//vectors?
				if (item->window.rect.hasVectors) {
					x += listPtr->elementHeight * item->window.rect.v[0];
					y += listPtr->elementHeight * item->window.rect.v[1];
				} else {
					y += listPtr->elementHeight;
				}
				// fit++;
			}
		}
	}
}

void Item_OwnerDraw_Paint(itemDef_t * item)
{
	menuDef_t *parent;

	if (item == NULL) {
		return;
	}
	parent = (menuDef_t *) item->parent;

	if (DC->ownerDrawItem) {
		vec4_t color, lowLight;
		menuDef_t *parent = (menuDef_t *) item->parent;

		Fade(&item->window.flags, &item->window.foreColor[3], parent->fadeClamp, &item->window.nextTime,
		     parent->fadeCycle, qtrue, parent->fadeAmount);
		memcpy(&color, &item->window.foreColor, sizeof(color));
		if (item->numColors > 0 && DC->getValue) {
			// if the value is within one of the ranges then set color to that, otherwise leave at default
			int i;
			float f = DC->getValue(item->window.ownerDraw);

			for (i = 0; i < item->numColors; i++) {
				if (f >= item->colorRanges[i].low && f <= item->colorRanges[i].high) {
					memcpy(&color, &item->colorRanges[i].color, sizeof(color));
					break;
				}
			}
		}

		if (item->window.flags & WINDOW_HASFOCUS) {
			//Makro - changed to fade from normal text color to focus color
			//lowLight[0] = 0.8 * parent->focusColor[0]; 
			//lowLight[1] = 0.8 * parent->focusColor[1]; 
			//lowLight[2] = 0.8 * parent->focusColor[2]; 
			//lowLight[3] = 0.8 * parent->focusColor[3]; 
			memcpy(lowLight, &item->window.foreColor, sizeof(vec4_t));
			LerpColor(parent->focusColor, lowLight, color, 0.5 + 0.5 * sin(DC->realTime / PULSE_DIVISOR));
		} else if (item->textStyle == ITEM_TEXTSTYLE_BLINK && !((DC->realTime / BLINK_DIVISOR) & 1)) {
			lowLight[0] = 0.8 * item->window.foreColor[0];
			lowLight[1] = 0.8 * item->window.foreColor[1];
			lowLight[2] = 0.8 * item->window.foreColor[2];
			lowLight[3] = 0.8 * item->window.foreColor[3];
			LerpColor(item->window.foreColor, lowLight, color,
				  0.5 + 0.5 * sin(DC->realTime / PULSE_DIVISOR));
		}

		if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
			memcpy(color, parent->disableColor, sizeof(vec4_t));	// bk001207 - FIXME: Com_Memcpy
		}

		if (item->text) {
			float p[2];
			
			p[0] = item->textRect.x;
			p[1] = item->window.rect.y;
			Item_Text_Paint(item);

			// +8 is an offset kludge to properly align owner draw items that have text combined with them
			if (item->window.rectClient.hasVectors) {
				if (item->text[0]) {
					Vector2MA(p, item->textRect.w+8, item->window.rectClient.u, p);
				} else {
					Vector2MA(p, item->textRect.w, item->window.rectClient.u, p);
				}
			} else {
				if (item->text[0]) {
					p[0] += item->textRect.w + 8;
				} else {
					p[0] += item->textRect.w;
				}
			}
			DC->ownerDrawItem(item, p[0], p[1],
				item->window.rect.w, item->window.rect.h, 0, item->textaligny,
				item->window.ownerDraw, item->window.ownerDrawFlags, item->alignment,
				item->special, item->textscale, color, item->window.background,
				item->textStyle);
		} else {
			DC->ownerDrawItem(item, item->window.rect.x, item->window.rect.y, item->window.rect.w,
					  item->window.rect.h, item->textalignx, item->textaligny,
					  item->window.ownerDraw, item->window.ownerDrawFlags, item->alignment,
					  item->special, item->textscale, color, item->window.background,
					  item->textStyle);
		}
	}
}

void Item_Paint(itemDef_t * item)
{
	vec4_t red;
	menuDef_t *parent = (menuDef_t *) item->parent;

	red[0] = red[3] = 1;
	red[1] = red[2] = 0;

	if (item == NULL) {
		return;
	}

	if (item->window.flags & WINDOW_RENDERPOINT)
	{
		if (DC->pendingPolys)
		{
			UI_Render2DScene();
		}
	}

	//Makro - debug
	/*
	if (0)
	{
		if (item->text && item->textRect.w)
		{
			if (Rect_ContainsPoint(&item->textRect, DC->cursorx, DC->cursory))
			{
				DC->drawText(DC->cursorx, DC->cursory, 0.3f, colorYellow,
					va("%.0f %.0f %.0f %.0f", item->textRect.x, item->textRect.y, item->textRect.w, item->textRect.h),
					0, 0, ITEM_TEXTSTYLE_SHADOWED);
			}
		}
	}
	*/

	if (item->window.flags & WINDOW_ORBITING) {
		if (DC->realTime > item->window.nextTime) {
			float rx, ry, a, c, s, w, h;

			item->window.nextTime = DC->realTime + item->window.offsetTime;
			// translate
			w = item->window.rectClient.w / 2;
			h = item->window.rectClient.h / 2;
			rx = item->window.rectClient.x + w - item->window.rectEffects.x;
			ry = item->window.rectClient.y + h - item->window.rectEffects.y;
			a = 3 * M_PI / 180;
			c = cos(a);
			s = sin(a);
			item->window.rectClient.x = (rx * c - ry * s) + item->window.rectEffects.x - w;
			item->window.rectClient.y = (rx * s + ry * c) + item->window.rectEffects.y - h;
			Item_UpdatePosition(item);

		}
	}

	if (item->window.flags & WINDOW_INTRANSITION) {
		if (DC->realTime > item->window.nextTime) {
			int done = 0;

			item->window.nextTime = DC->realTime + item->window.offsetTime;
			// transition the x,y
			if (item->window.rectClient.x == item->window.rectEffects.x) {
				done++;
			} else {
				if (item->window.rectClient.x < item->window.rectEffects.x) {
					item->window.rectClient.x += item->window.rectEffects2.x;
					if (item->window.rectClient.x > item->window.rectEffects.x) {
						item->window.rectClient.x = item->window.rectEffects.x;
						done++;
					}
				} else {
					item->window.rectClient.x -= item->window.rectEffects2.x;
					if (item->window.rectClient.x < item->window.rectEffects.x) {
						item->window.rectClient.x = item->window.rectEffects.x;
						done++;
					}
				}
			}
			if (item->window.rectClient.y == item->window.rectEffects.y) {
				done++;
			} else {
				if (item->window.rectClient.y < item->window.rectEffects.y) {
					item->window.rectClient.y += item->window.rectEffects2.y;
					if (item->window.rectClient.y > item->window.rectEffects.y) {
						item->window.rectClient.y = item->window.rectEffects.y;
						done++;
					}
				} else {
					item->window.rectClient.y -= item->window.rectEffects2.y;
					if (item->window.rectClient.y < item->window.rectEffects.y) {
						item->window.rectClient.y = item->window.rectEffects.y;
						done++;
					}
				}
			}
			if (item->window.rectClient.w == item->window.rectEffects.w) {
				done++;
			} else {
				if (item->window.rectClient.w < item->window.rectEffects.w) {
					item->window.rectClient.w += item->window.rectEffects2.w;
					if (item->window.rectClient.w > item->window.rectEffects.w) {
						item->window.rectClient.w = item->window.rectEffects.w;
						done++;
					}
				} else {
					item->window.rectClient.w -= item->window.rectEffects2.w;
					if (item->window.rectClient.w < item->window.rectEffects.w) {
						item->window.rectClient.w = item->window.rectEffects.w;
						done++;
					}
				}
			}
			if (item->window.rectClient.h == item->window.rectEffects.h) {
				done++;
			} else {
				if (item->window.rectClient.h < item->window.rectEffects.h) {
					item->window.rectClient.h += item->window.rectEffects2.h;
					if (item->window.rectClient.h > item->window.rectEffects.h) {
						item->window.rectClient.h = item->window.rectEffects.h;
						done++;
					}
				} else {
					item->window.rectClient.h -= item->window.rectEffects2.h;
					if (item->window.rectClient.h < item->window.rectEffects.h) {
						item->window.rectClient.h = item->window.rectEffects.h;
						done++;
					}
				}
			}

			Item_UpdatePosition(item);

			if (done == 4) {
				item->window.flags &= ~WINDOW_INTRANSITION;
			}

		}
	}

	if (item->window.ownerDrawFlags && DC->ownerDrawVisible) {
		if (!DC->ownerDrawVisible(item->window.ownerDrawFlags)) {
			item->window.flags &= ~WINDOW_VISIBLE;
		} else {
			item->window.flags |= WINDOW_VISIBLE;
		}
	}

	if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE)) {
		if (!Item_EnableShowViaCvar(item, CVAR_SHOW)) {
			return;
		}
	}

	if (item->window.flags & WINDOW_TIMEDVISIBLE) {

	}

	if (!(item->window.flags & WINDOW_VISIBLE)) {
		return;
	}

	// paint the rect first.. 
	Window_Paint(&item->window, parent->fadeAmount, parent->fadeClamp, parent->fadeCycle);

	if (debugMode) {
		vec4_t color;
		rectDef_t *r = Item_CorrectedTextRect(item);

		color[1] = color[3] = 1;
		color[0] = color[2] = 0;
		//Makro - added shader parm
		DC->drawRect(r->x, r->y, r->w, r->h, 1, color, DC->whiteShader);
	}
	//DC->drawRect(item->window.rect.x, item->window.rect.y, item->window.rect.w, item->window.rect.h, 1, red);

	switch (item->type) {
	case ITEM_TYPE_OWNERDRAW:
		Item_OwnerDraw_Paint(item);
		break;
	case ITEM_TYPE_TEXT:
	case ITEM_TYPE_BUTTON:
		Item_Text_Paint(item);
		break;
	case ITEM_TYPE_RADIOBUTTON:
		break;
	case ITEM_TYPE_CHECKBOX:
		break;
	case ITEM_TYPE_EDITFIELD:
	case ITEM_TYPE_NUMERICFIELD:
		Item_TextField_Paint(item);
		break;
	case ITEM_TYPE_COMBO:
		break;
	case ITEM_TYPE_LISTBOX:
		Item_ListBox_Paint(item);
		break;
		//case ITEM_TYPE_IMAGE:
		//  Item_Image_Paint(item);
		//  break;
	case ITEM_TYPE_MODEL:
		Item_Model_Paint(item);
		break;
	case ITEM_TYPE_YESNO:
		Item_YesNo_Paint(item);
		break;
	case ITEM_TYPE_MULTI:
		Item_Multi_Paint(item);
		break;
	case ITEM_TYPE_BIND:
		Item_Bind_Paint(item);
		break;
	case ITEM_TYPE_SLIDER:
		Item_Slider_Paint(item);
		break;
	default:
		break;
	}
}

void Menu_Init(menuDef_t * menu)
{
	memset(menu, 0, sizeof(menuDef_t));
	menu->cursorItem = -1;
	menu->fadeAmount = DC->Assets.fadeAmount;
	menu->fadeClamp = DC->Assets.fadeClamp;
	menu->fadeCycle = DC->Assets.fadeCycle;
	//Makro - ensure that onShow events are triggerred
	menu->shown = qfalse;
	menu->showCount = 0;
	Window_Init(&menu->window);
}

itemDef_t *Menu_GetFocusedItem(menuDef_t * menu)
{
	int i;

	if (menu) {
		for (i = 0; i < menu->itemCount; i++) {
			if (menu->items[i]->window.flags & WINDOW_HASFOCUS) {
				return menu->items[i];
			}
		}
	}
	return NULL;
}

menuDef_t *Menu_GetFocused()
{
	int i;

	for (i = 0; i < menuCount; i++) {
		if (Menus[i].window.flags & WINDOW_HASFOCUS && Menus[i].window.flags & WINDOW_VISIBLE) {
			return &Menus[i];
		}
	}
	return NULL;
}

void Menu_ScrollFeeder(menuDef_t * menu, int feeder, qboolean down)
{
	if (menu) {
		int i;

		for (i = 0; i < menu->itemCount; i++) {
			if (menu->items[i]->special == feeder) {
				Item_ListBox_HandleKey(menu->items[i], (down) ? K_DOWNARROW : K_UPARROW, qtrue, qtrue);
				return;
			}
		}
	}
}

void Menu_SetFeederSelection(menuDef_t * menu, int feeder, int index, const char *name)
{
	if (menu == NULL) {
		if (name == NULL) {
			menu = Menu_GetFocused();
		} else {
			menu = Menus_FindByName(name);
		}
	}

	if (menu) {
		int i;

		for (i = 0; i < menu->itemCount; i++) {
			if (menu->items[i]->special == feeder) {
				if (index == 0) {
					listBoxDef_t *listPtr = (listBoxDef_t *) menu->items[i]->typeData;

					listPtr->cursorPos = 0;
					listPtr->startPos = 0;
				}
				menu->items[i]->cursorPos = index;
				DC->feederSelection(menu->items[i]->special, menu->items[i]->cursorPos);
				return;
			}
		}
	}
}

qboolean Menus_AnyFullScreenVisible()
{
	int i;

	for (i = 0; i < menuCount; i++) {
		if (Menus[i].window.flags & WINDOW_VISIBLE && Menus[i].fullScreen) {
			return qtrue;
		}
	}
	return qfalse;
}

//Makro - added second parameter
menuDef_t *Menus_ActivateByName(const char *p, qboolean special)
{
	int i;
	menuDef_t *m = NULL;
	menuDef_t *focus = Menu_GetFocused();

	for (i = 0; i < menuCount; i++) {
		if (Q_stricmp(Menus[i].window.name, p) == 0) {
			int j;
			qboolean alreadyActive = qfalse;

			m = &Menus[i];
			Menus_Activate(m);
			
			//Makro - if special is true, run onOpenSpecial
			if (special && m->onOpenSpecial && m->itemCount > 0)
				Item_RunScript(m->items[0], m->onOpenSpecial);
			
			//Makro - this code didn't do anything useful
			//if (openMenuCount < MAX_OPEN_MENUS && focus != NULL) {
			//	menuStack[openMenuCount++] = focus;
			
			for (j = 0; j < openMenuCount; j++) {
				if (menuStack[j] == m) {
					alreadyActive = qtrue;
					//move to the top of the stack
					if (j != openMenuCount - 1) {
						menuStack[j] = menuStack[openMenuCount-1];
						menuStack[openMenuCount-1] = m;
					}
					break;
				}
			}
			if (!alreadyActive && openMenuCount < MAX_OPEN_MENUS) {
				menuStack[openMenuCount++] = m;
			}
		} else {
			Menus[i].window.flags &= ~WINDOW_HASFOCUS;
		}
	}
	Display_CloseCinematics();
	return m;
}

void Item_Init(itemDef_t * item)
{
	memset(item, 0, sizeof(itemDef_t));
	item->textscale = 0.55f;
	Window_Init(&item->window);
}

void Menu_HandleMouseMove(menuDef_t * menu, float x, float y)
{
	int i, pass;
	qboolean focusSet = qfalse;

	itemDef_t *overItem;

	if (menu == NULL) {
		return;
	}

	if (!(menu->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
		return;
	}

	if (itemCapture) {
		//Item_MouseMove(itemCapture, x, y);
		return;
	}

	if (g_waitingForKey || g_editingField) {
		return;
	}
	// FIXME: this is the whole issue of focus vs. mouse over.. 
	// need a better overall solution as i don't like going through everything twice
	for (pass = 0; pass < 2; pass++) {
		for (i = 0; i < menu->itemCount; i++) {
			// turn off focus each item
			// menu->items[i].window.flags &= ~WINDOW_HASFOCUS;

			if (!(menu->items[i]->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
				continue;
			}
			// items can be enabled and disabled based on cvars
			if (menu->items[i]->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE)
			    && !Item_EnableShowViaCvar(menu->items[i], CVAR_ENABLE)) {
				continue;
			}

			if (menu->items[i]->cvarFlags & (CVAR_SHOW | CVAR_HIDE)
			    && !Item_EnableShowViaCvar(menu->items[i], CVAR_SHOW)) {
				continue;
			}

			if (menu->items[i]->type == ITEM_TYPE_LISTBOX) {
				rectDef_t *r = &menu->items[i]->window.rect;
				//Com_Printf("Listbox: %d\n", r->hasVectors);
				//DC->drawAngledPic(r->x, r->y, r->w, r->h, r->u, r->v, colorYellow, 0, 0, 1, 1, DC->whiteShader);
			}
			if (Rect_ContainsPoint(&menu->items[i]->window.rect, x, y)) {
				if (pass == 1) {
					overItem = menu->items[i];
					if (overItem->type == ITEM_TYPE_TEXT && overItem->text) {
						if (!Rect_ContainsPoint(Item_CorrectedTextRect(overItem), x, y)) {
							continue;
						}
					}
					// if we are over an item
					if (IsVisible(overItem->window.flags)) {
						// different one
						Item_MouseEnter(overItem, x, y);
						// Item_SetMouseOver(overItem, qtrue);

						// if item is not a decoration see if it can take focus
						if (!focusSet) {
							focusSet = Item_SetFocus(overItem, x, y, qfalse);
						}
					}
					if (menu->items[i]->type == ITEM_TYPE_LISTBOX) {
						//Com_Printf("Listbox: %.1f %.1f %.1f %.1f / %.1f %.1f %.1f %.1f / %d %d %d IN\n", PRINT_RECT(menu->items[i]->window.rect), menu->items[i]->window.rectClient.u[0], menu->items[i]->window.rectClient.u[1], menu->items[i]->window.rectClient.v[0], menu->items[i]->window.rectClient.v[1], menu->items[i]->window.rectClient.hasVectors, DC->cursorx, DC->cursory);
					}
				}
			} else if (menu->items[i]->window.flags & WINDOW_MOUSEOVER) {
				Item_MouseLeave(menu->items[i]);
				Item_SetMouseOver(menu->items[i], qfalse);
				if (menu->items[i]->type == ITEM_TYPE_LISTBOX) {
					//Com_Printf("Listbox: %.1f %.1f %.1f %.1f / %.1f %.1f %.1f %.1f / %d %d %d OUT\n", PRINT_RECT(menu->items[i]->window.rect), menu->items[i]->window.rectClient.u[0], menu->items[i]->window.rectClient.u[1], menu->items[i]->window.rectClient.v[0], menu->items[i]->window.rectClient.v[1], menu->items[i]->window.rect.hasVectors, DC->cursorx, DC->cursory);
				}
			}
		}
	}

}

//Makro - let's make things easier
int UI_GetIndexInTimer(itemDef_t *item)
{
	if (!item)
		return 0;
	if (!item->window.name)
		return 0;
	if (Q_stricmpn(item->window.name, "timer", 5) != 0)
		return 0;
	return atoi(item->window.name+5);
}


//Makro - timer actions
void UI_RQ3_HandleTimer(menuDef_t * menu)
{
	if (menu) {
		if (menu->timerEnabled) {
			if (DC->realTime > menu->nextTimer) {
				if (menu->timerPos > menu->timedItems) {
					menu->timerEnabled = qfalse;
					if (menu->onFinishTimer && menu->itemCount > 0) {
						Item_RunScript(menu->items[0], menu->onFinishTimer);
					}
				} else {
					int i;
					int toShow = menu->timerPos;
					int toHide = menu->timerPos - menu->timerMaxDisplay;

					menu->nextTimer = DC->realTime + menu->timerInterval;

					for (i = 0; i < menu->itemCount; i++) {
						itemDef_t *item = menu->items[i];
						if (!Q_stricmp(item->window.group, "timer")) {
							int tIndex = UI_GetIndexInTimer(item);

							//item to be shown
							if ( tIndex == toShow ) {
								//manual show
								if (item->onTimerShow) {
									Item_RunScript(item, item->onTimerShow);
								//menu default
								} else if (menu->onTimerShow) {
									Item_RunScript(item, menu->onTimerShow);
								//simply hide
								} else {
									item->window.flags |= WINDOW_VISIBLE;
								}
							//item to be hidden
							} else if ( toHide > 0 && tIndex == toHide) {
								//manual hide
								if (item->onTimerHide) {
									Item_RunScript(item, item->onTimerHide);
								//menu default
								} else if (menu->onTimerHide) {
									Item_RunScript(item, menu->onTimerHide);
								//simply hide
								} else {
									item->window.flags &= ~WINDOW_VISIBLE;
								}
							} else {
								//hide all items between those two
								if (tIndex < toHide || tIndex > toShow)
									menu->items[i]->window.flags &= ~WINDOW_VISIBLE;
							}
						}
					}
					menu->timerPos++;
				}
			}
		}
	}
}

void Menu_Paint(menuDef_t * menu, qboolean forcePaint)
{
	int i;

	if (menu == NULL) {
		return;
	}

	if (menu->window.flags & WINDOW_RENDERPOINT)
	{
		if (DC->pendingPolys)
		{
			UI_Render2DScene();
		}
	}

	if (!(menu->window.flags & WINDOW_VISIBLE) && !forcePaint) {
		return;
	}

	if (menu->window.ownerDrawFlags && DC->ownerDrawVisible && !DC->ownerDrawVisible(menu->window.ownerDrawFlags)) {
		return;
	}

	if (forcePaint) {
		menu->window.flags |= WINDOW_FORCED;
	}
	//Makro - kinda hackish; oh well...
	//if (UI_NeedToUpdateModel())
		//UI_RQ3_SelectPlayerIcon(menu);
	//Makro - see if we have any onShow script
	if (!(menu->shown)) {
		//If it's the first time a menu is shown, look for a onFirstShow script
		if (menu->showCount == 0) {
			if (menu->onFirstShow) {
				if (menu->itemCount > 0) {
					//Found onFirstShow script; item count > 0
					Item_RunScript(menu->items[0], menu->onFirstShow);
				}
			} else if (menu->onShow) {
				if (menu->itemCount > 0) {
					//onFirstShow script not found, using onShow instead
					Item_RunScript(menu->items[0], menu->onShow);
				}
			}
		} else if (menu->itemCount > 0) {
			Item_RunScript(menu->items[0], menu->onShow);
		}

		menu->shown = qtrue;
		menu->showCount++;
	}
	// draw the background if necessary
	if (menu->fullScreen) {
		// implies a background shader
		// FIXME: make sure we have a default shader if fullscreen is set with no background

		float sx = DC->glconfig.vidWidth / (float) SCREEN_WIDTH;
		float sy = DC->glconfig.vidHeight / (float) SCREEN_HEIGHT;

		float tex[2];

		if (sx >= sy)
		{
			tex[0] = 0.f;
			tex[1] = 0.5f * (1.f - sy / sx);
			
		}
		else
		{
			tex[0] = 0.5f * (1.f - sx / sy);
			tex[1] = 0.f;
		}

		DC->drawStretchPic(0, 0, DC->glconfig.vidWidth, DC->glconfig.vidHeight, tex[0], tex[1], 1.f - tex[0], 1.f - tex[1], menu->window.background, qfalse);
	} else if (menu->window.background) {
		// this allows a background shader without being full screen
		//UI_DrawHandlePic(menu->window.rect.x, menu->window.rect.y, menu->window.rect.w, menu->window.rect.h, menu->backgroundShader);
	}
	//Makro - handle timers
	UI_RQ3_HandleTimer(menu);

	// paint the background and or border
	Window_Paint(&menu->window, menu->fadeAmount, menu->fadeClamp, menu->fadeCycle);

	for (i = 0; i < menu->itemCount; i++) {
		Item_Paint(menu->items[i]);
	}

	if (debugMode) {
		vec4_t color;

		color[0] = color[2] = color[3] = 1;
		color[1] = 0;
		//Makro - added shader parm
		DC->drawRect(menu->window.rect.x, menu->window.rect.y, menu->window.rect.w, menu->window.rect.h, 1,
			     color, DC->whiteShader);
	}
}

/*
===============
Item_ValidateTypeData
===============
*/
void Item_ValidateTypeData(itemDef_t * item)
{
	if (item->typeData) {
		return;
	}

	if (item->type == ITEM_TYPE_LISTBOX) {
		item->typeData = UI_Alloc(sizeof(listBoxDef_t));
		memset(item->typeData, 0, sizeof(listBoxDef_t));
	//Makro - moved YES/NO items out of here
	} else if (item->type == ITEM_TYPE_EDITFIELD || item->type == ITEM_TYPE_NUMERICFIELD
		   || item->type == ITEM_TYPE_BIND || item->type == ITEM_TYPE_SLIDER
		   || item->type == ITEM_TYPE_TEXT) {
		item->typeData = UI_Alloc(sizeof(editFieldDef_t));
		memset(item->typeData, 0, sizeof(editFieldDef_t));
		if (item->type == ITEM_TYPE_EDITFIELD) {
			if (!((editFieldDef_t *) item->typeData)->maxPaintChars) {
				((editFieldDef_t *) item->typeData)->maxPaintChars = MAX_EDITFIELD;
			}
		}
	} else if (item->type == ITEM_TYPE_MULTI) {
		item->typeData = UI_Alloc(sizeof(multiDef_t));
	} else if (item->type == ITEM_TYPE_MODEL) {
		item->typeData = UI_Alloc(sizeof(modelDef_t));
	//Makro - special code for YES/NO items
	} else if (item->type == ITEM_TYPE_YESNO) {
		item->typeData = UI_Alloc(sizeof(yesnoDef_t));
	}
}

/*
===============
Keyword Hash
===============
*/

#define KEYWORDHASH_SIZE	512

typedef struct keywordHash_s {
	char *keyword;
	 qboolean(*func) (itemDef_t * item, int handle);
	struct keywordHash_s *next;
} keywordHash_t;

int KeywordHash_Key(const char *keyword)
{
	int register hash, i;

	hash = 0;
	for (i = 0; keyword[i] != '\0'; i++) {
		if (keyword[i] >= 'A' && keyword[i] <= 'Z')
			hash += (keyword[i] + ('a' - 'A')) * (119 + i);
		else
			hash += keyword[i] * (119 + i);
	}
	hash = (hash ^ (hash >> 10) ^ (hash >> 20)) & (KEYWORDHASH_SIZE - 1);
	return hash;
}

void KeywordHash_Add(keywordHash_t * table[], keywordHash_t * key)
{
	int hash;

	hash = KeywordHash_Key(key->keyword);
/*
	if (table[hash]) {
		int collision = qtrue;
	}
*/
	key->next = table[hash];
	table[hash] = key;
}

keywordHash_t *KeywordHash_Find(keywordHash_t * table[], char *keyword)
{
	keywordHash_t *key;
	int hash;

	hash = KeywordHash_Key(keyword);
	for (key = table[hash]; key; key = key->next) {
		if (!Q_stricmp(key->keyword, keyword))
			return key;
	}
	return NULL;
}

/*
===============
Item Keyword Parse functions
===============
*/

// name <string>
qboolean ItemParse_name(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->window.name)) {
		return qfalse;
	}
	return qtrue;
}

// Makro - shortcutKey <key>
qboolean ItemParse_shortcutKey(itemDef_t * item, int handle)
{
	const char *temp;

	if (PC_String_Parse(handle, &temp))
	{
		int c, i;

		//key buffer already full?
		for (i=0; i<MAX_SHORTCUT_KEYS && item->window.shortcutKey[i]; i++);
		if (i == MAX_SHORTCUT_KEYS)
			return qfalse;

		c = (strlen(temp) == 1) ? temp[0] : UI_RQ3_KeyNumFromChar(temp);
		if (c <= 0)
			return qfalse;
		if (c>='A' && c<='Z')
			c -= 'A'-'a';
		item->window.shortcutKey[i] = c;
		return qtrue;
	}
	return qfalse;
}

//Makro - fixed height for autowrapped text
qboolean ItemParse_textHeight(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->textHeight)) {
		return qfalse;
	}
	return qtrue;
}

// name <string>
qboolean ItemParse_focusSound(itemDef_t * item, int handle)
{
	const char *temp;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->focusSound = DC->registerSound(temp, qfalse);
	return qtrue;
}

// text <string>
qboolean ItemParse_text(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->text)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - cleanText <string>
qboolean ItemParse_cleanText(itemDef_t * item, int handle)
{
	const char *tmp = NULL;
	char *s = NULL;
	if (!PC_String_Parse(handle, &tmp)) {
		return qfalse;
	}
	if ( !(s = UI_Alloc(strlen(tmp) + 1)) )
		return qfalse;
	item->text = Q_CleanStr(strcpy(s, tmp));
	return qtrue;
}

// group <string>
qboolean ItemParse_group(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->window.group)) {
		return qfalse;
	}
	return qtrue;
}


//Makro - subgroup <string>
qboolean ItemParse_subgroup(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->window.subgroup)) {
		return qfalse;
	}
	return qtrue;
}

// asset_model <string>
qboolean ItemParse_asset_model(itemDef_t * item, int handle)
{
	const char *temp;
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->asset = DC->registerModel(temp);
	//Makro - we're using 3 angles now, not just one
	//modelPtr->angle = rand() % 360;
	modelPtr->angles[0] = rand() % 360;
	return qtrue;
}

// asset_shader <string>
qboolean ItemParse_asset_shader(itemDef_t * item, int handle)
{
	const char *temp;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->asset = DC->registerShaderNoMip(temp);
	return qtrue;
}

// model_origin <number> <number> <number>
qboolean ItemParse_model_origin(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (PC_Float_Parse(handle, &modelPtr->origin[0])) {
		if (PC_Float_Parse(handle, &modelPtr->origin[1])) {
			if (PC_Float_Parse(handle, &modelPtr->origin[2])) {
				return qtrue;
			}
		}
	}
	return qfalse;
}

// model_fovx <number>
qboolean ItemParse_model_fovx(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (!PC_Float_Parse(handle, &modelPtr->fov_x)) {
		return qfalse;
	}
	return qtrue;
}

// model_fovy <number>
qboolean ItemParse_model_fovy(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (!PC_Float_Parse(handle, &modelPtr->fov_y)) {
		return qfalse;
	}
	return qtrue;
}

// model_rotation <integer>
qboolean ItemParse_model_rotation(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (!PC_Int_Parse(handle, &modelPtr->rotationSpeed)) {
		return qfalse;
	}
	return qtrue;
}

// Makro - rotate models around all 3 axis
// model_angle <integer> - old one
qboolean ItemParse_model_angle(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	//Makro - changed from Int to Float
	if (!PC_Float_Parse(handle, &modelPtr->angles[0])) {
		return qfalse;
	}
	return qtrue;
}

//Makro - angled items
//vectors <u1> <u2> <v1> <v2>
qboolean ItemParse_vectors(itemDef_t *item, int handle)
{
	float u[2], v[2];
	if (PC_Float_Parse(handle, &u[0]))
	{
		if (PC_Float_Parse(handle, &u[1]))
		{
			if (PC_Float_Parse(handle, &v[0]))
			{
				if (PC_Float_Parse(handle, &v[1]))
				{
					Vector2Copy(u, item->window.rectClient.u);
					Vector2Copy(v, item->window.rectClient.v);
					Vector2Copy(u, item->window.rect.u);
					Vector2Copy(v, item->window.rect.v);
					Vector2Copy(u, item->textRect.u);
					Vector2Copy(v, item->textRect.v);
					item->window.rectClient.hasVectors=qtrue;
					item->window.rect.hasVectors=qtrue;
					item->textRect.hasVectors=qtrue;
					return qtrue;
				}
			}
		}
	}
	return qfalse;
}

//alignrect <item_name> <alignment_type> <h_distance> <v_distance> <width> <height>
qboolean ItemParse_alignrect(itemDef_t *item, int handle)
{
	int w, h, align, vdist, hdist;
	const char *to;
	if (PC_String_Parse(handle, &to))
	{
		if (PC_Int_Parse(handle, &align))
		{
			if (PC_Int_Parse(handle, &hdist))
			{
				if (PC_Int_Parse(handle, &vdist))
				{
					if (PC_Int_Parse(handle, &w))
					{
						if (PC_Int_Parse(handle, &h))
						{
							itemDef_t *toitem = (itemDef_t*)Menu_GetMatchingItemByNumber((menuDef_t*)item->parent,0, to);
							if (toitem)
							{
								//got milk... err, vectors?
								if (toitem->window.rectClient.hasVectors)
								{
									//set co-ords
									float p[2];

									p[0] = toitem->window.rectClient.x;
									p[1] = toitem->window.rectClient.y;
									Vector2MA(p, vdist, toitem->window.rectClient.v, p);
									if (align == ITEM_ALIGN_RIGHT) {
										Vector2MA(p, (toitem->window.rectClient.w - w) - hdist, toitem->window.rectClient.u, p);
									} else if (align == ITEM_ALIGN_CENTER) {
										Vector2MA(p, (toitem->window.rectClient.w - w)/2 + hdist, toitem->window.rectClient.u, p);
									} else {
										Vector2MA(p, hdist, toitem->window.rectClient.u, p);
									}
									item->window.rectClient.x = p[0];
									item->window.rectClient.y = p[1];
									item->window.rectClient.w = w;
									item->window.rectClient.h = h;
									//copy vector info
									Vector2Copy(toitem->window.rect.u, item->window.rect.u);
									Vector2Copy(toitem->window.rect.v, item->window.rect.v);
									item->window.rect.hasVectors = qtrue;
									Vector2Copy(toitem->window.rect.u, item->window.rectClient.u);
									Vector2Copy(toitem->window.rect.v, item->window.rectClient.v);
									item->window.rectClient.hasVectors = qtrue;
									Vector2Copy(toitem->window.rect.u, item->textRect.u);
									Vector2Copy(toitem->window.rect.v, item->textRect.v);
									item->textRect.hasVectors = qtrue;
								} else {
									int x = toitem->window.rectClient.x, y = toitem->window.rectClient.y + vdist;
									if (align == ITEM_ALIGN_RIGHT)
									{
										x += toitem->window.rectClient.w - w - hdist;
									} else if (align == ITEM_ALIGN_CENTER) {
										x += (toitem->window.rectClient.w - w) / 2 + hdist;
									} else {
										x += hdist;
									}
									item->window.rectClient.x = x;
									item->window.rectClient.y = y;
									item->window.rectClient.w = w;
									item->window.rectClient.h = h;
								}
							}
							return qtrue;
						}
					}
				}
			}
		}
	}
	return qfalse;
}

//normalizevectors
qboolean ItemParse_normalizevectors(itemDef_t *item, int handle)
{
	float norm;
	
	if (!item->window.rectClient.hasVectors)
		return qtrue;

	norm = Vector2Norm2(item->window.rectClient.u);
	if (!norm)
		return qtrue;
	Vector2Scale(item->window.rectClient.u, 1.0f/norm, item->window.rectClient.u);
	Vector2Copy(item->window.rectClient.u, item->window.rect.u);
	Vector2Copy(item->window.rectClient.u, item->textRect.u);

	norm = Vector2Norm2(item->window.rectClient.v);
	if (!norm)
		return qtrue;
	Vector2Scale(item->window.rectClient.v, 1.0f/norm, item->window.rectClient.v);
	Vector2Copy(item->window.rectClient.v, item->window.rect.u);
	Vector2Copy(item->window.rectClient.v, item->textRect.u);
	return qtrue;
}

//anglevectors <u_angle> <v_angle>
qboolean ItemParse_anglevectors(itemDef_t *item, int handle)
{
	float u, v;
	if (PC_Float_Parse(handle, &u))
	{
		if (PC_Float_Parse(handle, &v))
		{
			u = DEG2RAD(-u);
			v = DEG2RAD(-v);
			Vector2Set(item->window.rectClient.u, cos(u), sin(u));
			Vector2Set(item->window.rectClient.v, cos(v), sin(v));
			Vector2Copy(item->window.rectClient.u, item->window.rect.u);
			Vector2Copy(item->window.rectClient.v, item->window.rect.v);
			Vector2Copy(item->window.rectClient.u, item->textRect.u);
			Vector2Copy(item->window.rectClient.v, item->textRect.v);
			item->window.rectClient.hasVectors=qtrue;
			item->window.rect.hasVectors=qtrue;
			item->textRect.hasVectors=qtrue;
			return qtrue;
		}
	}
	return qfalse;
}

//adjustrect
qboolean ItemParse_adjustrect(itemDef_t * item, int handle)
{
	if (item && item->parent)
	{
		menuDef_t *menu = (menuDef_t*)item->parent;
		if (menu->window.rect.hasVectors)
		{
			int ox = item->window.rectClient.x, oy = item->window.rectClient.y;
			//copy vector info
			Vector2Copy(menu->window.rect.u, item->window.rect.u);
			Vector2Copy(menu->window.rect.v, item->window.rect.v);
			item->window.rect.hasVectors = qtrue;
			Vector2Copy(menu->window.rect.u, item->window.rectClient.u);
			Vector2Copy(menu->window.rect.v, item->window.rectClient.v);
			item->window.rectClient.hasVectors = qtrue;
			Vector2Copy(menu->window.rect.u, item->textRect.u);
			Vector2Copy(menu->window.rect.v, item->textRect.v);
			item->textRect.hasVectors = qtrue;
			//adjust co-ords
			item->window.rectClient.x = ox * item->window.rectClient.u[0] + oy * item->window.rectClient.v[0];
			item->window.rectClient.y = ox * item->window.rectClient.u[1] + oy * item->window.rectClient.v[1];
		}
	}
	return qtrue;
}

// model_angles <yaw> <pitch> <roll>
qboolean ItemParse_model_angles(itemDef_t * item, int handle)
{
	modelDef_t *modelPtr;

	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t *) item->typeData;

	if (PC_Float_Parse(handle, &modelPtr->angles[0])) {
		if (PC_Float_Parse(handle, &modelPtr->angles[1])) {
			if (PC_Float_Parse(handle, &modelPtr->angles[2])) {
				return qtrue;
			}
		}
	}
	return qfalse;
}

//Makro - forced text color
qboolean ItemParse_forceTextColor(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_FORCE_TEXT_COLOR;
	return qtrue;
}

//Makro - randomized texture co-ordinates for stretched shaders
qboolean ItemParse_randomizeTexCoords(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_RANDOM_TCGEN;
	return qtrue;
}

//Makro - menu anchor
qboolean ItemParse_menuAnchor(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_MENU_ANCHOR;
	return qtrue;
}


qboolean ItemParse_renderpoint(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_RENDERPOINT;
	return qtrue;
}

// rect <rectangle>
qboolean ItemParse_rect(itemDef_t * item, int handle)
{
	if (!PC_Rect_Parse(handle, &item->window.rectClient)) {
		return qfalse;
	}
	return qtrue;
}

// style <integer>
qboolean ItemParse_style(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->window.style)) {
		return qfalse;
	}
	return qtrue;
}

// decoration
qboolean ItemParse_decoration(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_DECORATION;
	return qtrue;
}

// notselectable
qboolean ItemParse_notselectable(itemDef_t * item, int handle)
{
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	listPtr = (listBoxDef_t *) item->typeData;
	if (item->type == ITEM_TYPE_LISTBOX && listPtr) {
		listPtr->notselectable = qtrue;
	}
	return qtrue;
}

// manually wrapped
qboolean ItemParse_wrapped(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_WRAPPED;
	return qtrue;
}

// auto wrapped
qboolean ItemParse_autowrapped(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_AUTOWRAPPED;
	return qtrue;
}

// horizontalscroll
qboolean ItemParse_horizontalscroll(itemDef_t * item, int handle)
{
	item->window.flags |= WINDOW_HORIZONTAL;
	return qtrue;
}

// type <integer>
qboolean ItemParse_type(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->type)) {
		return qfalse;
	}
	Item_ValidateTypeData(item);
	return qtrue;
}

// elementwidth, used for listbox image elements
// uses textalignx for storage
qboolean ItemParse_elementwidth(itemDef_t * item, int handle)
{
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	listPtr = (listBoxDef_t *) item->typeData;
	if (!PC_Float_Parse(handle, &listPtr->elementWidth)) {
		return qfalse;
	}
	return qtrue;
}

// elementheight, used for listbox image elements
// uses textaligny for storage
qboolean ItemParse_elementheight(itemDef_t * item, int handle)
{
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	listPtr = (listBoxDef_t *) item->typeData;
	if (!PC_Float_Parse(handle, &listPtr->elementHeight)) {
		return qfalse;
	}
	return qtrue;
}

// feeder <float>
qboolean ItemParse_feeder(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->special)) {
		return qfalse;
	}
	return qtrue;
}

// elementtype, used to specify what type of elements a listbox contains
// uses textstyle for storage
qboolean ItemParse_elementtype(itemDef_t * item, int handle)
{
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	listPtr = (listBoxDef_t *) item->typeData;
	if (!PC_Int_Parse(handle, &listPtr->elementStyle)) {
		return qfalse;
	}
	return qtrue;
}

// columns sets a number of columns and an x pos and width per.. 
qboolean ItemParse_columns(itemDef_t * item, int handle)
{
	int num, i;
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	listPtr = (listBoxDef_t *) item->typeData;
	if (PC_Int_Parse(handle, &num)) {
		if (num > MAX_LB_COLUMNS) {
			num = MAX_LB_COLUMNS;
		}
		listPtr->numColumns = num;
		for (i = 0; i < num; i++) {
			int pos, width, maxChars;

			if (PC_Int_Parse(handle, &pos) && PC_Int_Parse(handle, &width)
			    && PC_Int_Parse(handle, &maxChars)) {
				listPtr->columnInfo[i].pos = pos;
				listPtr->columnInfo[i].width = width;
				listPtr->columnInfo[i].maxChars = maxChars;
			} else {
				return qfalse;
			}
		}
	} else {
		return qfalse;
	}
	return qtrue;
}

// columndef sets a number of columns and an x pos and width per
qboolean ItemParse_columndef(itemDef_t * item, int handle)
{
	int num, i;
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	listPtr = (listBoxDef_t *) item->typeData;
	if (PC_Int_Parse(handle, &num))
	{
		int total = 0;
		//int max = (int)item->window.rect.w;
		if (num > MAX_LB_COLUMNS)
		{
			num = MAX_LB_COLUMNS;
		}
		listPtr->numColumns = num;
		for (i = 0; i < num; i++)
		{
			int pos, width;

			if (PC_Int_Parse(handle, &pos) && PC_Int_Parse(handle, &width))
			{
				listPtr->columnInfo[i].pos = pos + total;
				listPtr->columnInfo[i].width = width;
				listPtr->columnInfo[i].maxChars = 0;
				total += pos + width;
				//if (total > max)
				//{
				//	PC_SourceWarning(handle, "Column %d extends past window bounds by %d units", i+1, total - max);
				//}
			} else {
				return qfalse;
			}
		}
	} else {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_border(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->window.border)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_bordersize(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->window.borderSize)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - for drop shadow effects
qboolean ItemParse_shadowStyle(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->window.shadowStyle)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_visible(itemDef_t * item, int handle)
{
	int i;

	if (!PC_Int_Parse(handle, &i)) {
		return qfalse;
	}
	if (i) {
		item->window.flags |= WINDOW_VISIBLE;
	}
	return qtrue;
}

qboolean ItemParse_ownerdraw(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->window.ownerDraw)) {
		return qfalse;
	}
	item->type = ITEM_TYPE_OWNERDRAW;
	return qtrue;
}

qboolean ItemParse_align(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->alignment)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_textalign(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->textalignment)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_textalignx(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->textalignx)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_textaligny(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->textaligny)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_textscale(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->textscale)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_textstyle(itemDef_t * item, int handle)
{
	if (!PC_Int_Parse(handle, &item->textStyle)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_backcolor(itemDef_t * item, int handle)
{
	int i;
	float f;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		item->window.backColor[i] = f;
	}
	return qtrue;
}

qboolean ItemParse_forecolor(itemDef_t * item, int handle)
{
	int i;
	float f;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		item->window.foreColor[i] = f;
		item->window.flags |= WINDOW_FORECOLORSET;
	}
	return qtrue;
}

qboolean ItemParse_bordercolor(itemDef_t * item, int handle)
{
	int i;
	float f;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		item->window.borderColor[i] = f;
	}
	return qtrue;
}

qboolean ItemParse_outlinecolor(itemDef_t * item, int handle)
{
	if (!PC_Color_Parse(handle, &item->window.outlineColor)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_background(itemDef_t * item, int handle)
{
	const char *temp;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->window.background = DC->registerShaderNoMip(temp);
	return qtrue;
}

qboolean ItemParse_cinematic(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->window.cinematicName)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_doubleClick(itemDef_t * item, int handle)
{
	listBoxDef_t *listPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData) {
		return qfalse;
	}

	listPtr = (listBoxDef_t *) item->typeData;

	if (!PC_Script_Parse(handle, &listPtr->doubleClick)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_onFocus(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->onFocus)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_leaveFocus(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->leaveFocus)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - extra action executed when the timer shows this item
qboolean ItemParse_onTimerShow(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->onTimerShow)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - extra action executed when the timer hides this item
qboolean ItemParse_onTimerHide(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->onTimerHide)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_mouseEnter(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->mouseEnter)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_mouseExit(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->mouseExit)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_mouseEnterText(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->mouseEnterText)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_mouseExitText(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->mouseExitText)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_action(itemDef_t * item, int handle)
{
	if (!PC_Script_Parse(handle, &item->action)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_special(itemDef_t * item, int handle)
{
	if (!PC_Float_Parse(handle, &item->special)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_cvarTest(itemDef_t * item, int handle)
{
	if (!PC_String_Parse(handle, &item->cvarTest)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_cvar(itemDef_t * item, int handle)
{
	editFieldDef_t *editPtr;

	Item_ValidateTypeData(item);
	if (!PC_String_Parse(handle, &item->cvar)) {
		return qfalse;
	}
	//Makro - not for yes/no items
	if (item->typeData && item->type != ITEM_TYPE_YESNO) {
		editPtr = (editFieldDef_t *) item->typeData;
		editPtr->minVal = -1;
		editPtr->maxVal = -1;
		editPtr->defVal = -1;
	}
	return qtrue;
}


//Makro - for grouped checkboxes
qboolean ItemParse_groupIndex(itemDef_t * item, int handle)
{
	yesnoDef_t *data = (yesnoDef_t*)item->typeData;
	if (!PC_Int_Parse(handle, &data->groupIndex)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_activeCvarValue(itemDef_t * item, int handle)
{
	yesnoDef_t *data = (yesnoDef_t*)item->typeData;
	if (!PC_Float_Parse(handle, &data->activeCvarVal)) {
		return qfalse;
	}
	return qtrue;
}

qboolean ItemParse_kind(itemDef_t * item, int handle)
{
	yesnoDef_t *data = (yesnoDef_t*)item->typeData;
	if (!PC_Int_Parse(handle, &data->kind)) {
		return qfalse;
	}
	return qtrue;
}

//

qboolean ItemParse_maxChars(itemDef_t * item, int handle)
{
	editFieldDef_t *editPtr;
	int maxChars;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;

	if (!PC_Int_Parse(handle, &maxChars)) {
		return qfalse;
	}
	editPtr = (editFieldDef_t *) item->typeData;
	editPtr->maxChars = maxChars;
	return qtrue;
}

qboolean ItemParse_maxPaintChars(itemDef_t * item, int handle)
{
	editFieldDef_t *editPtr;
	int maxChars;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;

	if (!PC_Int_Parse(handle, &maxChars)) {
		return qfalse;
	}
	editPtr = (editFieldDef_t *) item->typeData;
	editPtr->maxPaintChars = maxChars;
	return qtrue;
}

qboolean ItemParse_cvarFloat(itemDef_t * item, int handle)
{
	editFieldDef_t *editPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	editPtr = (editFieldDef_t *) item->typeData;
	if (PC_String_Parse(handle, &item->cvar) &&
	    PC_Float_Parse(handle, &editPtr->defVal) &&
	    PC_Float_Parse(handle, &editPtr->minVal) && PC_Float_Parse(handle, &editPtr->maxVal)) {
		return qtrue;
	}
	return qfalse;
}

qboolean ItemParse_cvarStrList(itemDef_t * item, int handle)
{
	pc_token_t token;
	multiDef_t *multiPtr;
	int pass;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	multiPtr = (multiDef_t *) item->typeData;
	multiPtr->count = 0;
	multiPtr->strDef = qtrue;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}

	pass = 0;
	INFINITE_LOOP {
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu item\n");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		if (*token.string == ',' || *token.string == ';') {
			continue;
		}

		if (pass == 0) {
			multiPtr->cvarList[multiPtr->count] = String_Alloc(token.string);
			pass = 1;
		} else {
			multiPtr->cvarStr[multiPtr->count] = String_Alloc(token.string);
			pass = 0;
			multiPtr->count++;
			if (multiPtr->count >= MAX_MULTI_CVARS) {
				return qfalse;
			}
		}

	}
	//Makro - unreachable
	//return qfalse;		// bk001205 - LCC missing return value
}

qboolean ItemParse_cvarFloatList(itemDef_t * item, int handle)
{
	pc_token_t token;
	multiDef_t *multiPtr;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	multiPtr = (multiDef_t *) item->typeData;
	multiPtr->count = 0;
	multiPtr->strDef = qfalse;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}

	INFINITE_LOOP {
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu item\n");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		if (*token.string == ',' || *token.string == ';') {
			continue;
		}

		multiPtr->cvarList[multiPtr->count] = String_Alloc(token.string);
		if (!PC_Float_Parse(handle, &multiPtr->cvarValue[multiPtr->count])) {
			return qfalse;
		}

		multiPtr->count++;
		if (multiPtr->count >= MAX_MULTI_CVARS) {
			return qfalse;
		}

	}
	//Makro - unreachable
	//return qfalse;		// bk001205 - LCC missing return value
}

qboolean ItemParse_addColorRange(itemDef_t * item, int handle)
{
	colorRangeDef_t color;

	if (PC_Float_Parse(handle, &color.low) &&
	    PC_Float_Parse(handle, &color.high) && PC_Color_Parse(handle, &color.color)) {
		if (item->numColors < MAX_COLOR_RANGES) {
			memcpy(&item->colorRanges[item->numColors], &color, sizeof(color));
			item->numColors++;
		}
		return qtrue;
	}
	return qfalse;
}

qboolean ItemParse_ownerdrawFlag(itemDef_t * item, int handle)
{
	int i;

	if (!PC_Int_Parse(handle, &i)) {
		return qfalse;
	}
	item->window.ownerDrawFlags |= i;
	return qtrue;
}

qboolean ItemParse_enableCvar(itemDef_t * item, int handle)
{
	if (PC_Script_Parse(handle, &item->enableCvar)) {
		item->cvarFlags = CVAR_ENABLE;
		return qtrue;
	}
	return qfalse;
}

qboolean ItemParse_disableCvar(itemDef_t * item, int handle)
{
	if (PC_Script_Parse(handle, &item->enableCvar)) {
		item->cvarFlags = CVAR_DISABLE;
		return qtrue;
	}
	return qfalse;
}

qboolean ItemParse_showCvar(itemDef_t * item, int handle)
{
	if (PC_Script_Parse(handle, &item->enableCvar)) {
		item->cvarFlags = CVAR_SHOW;
		return qtrue;
	}
	return qfalse;
}

qboolean ItemParse_hideCvar(itemDef_t * item, int handle)
{
	if (PC_Script_Parse(handle, &item->enableCvar)) {
		item->cvarFlags = CVAR_HIDE;
		return qtrue;
	}
	return qfalse;
}


#define ADD_HASH_FUNC(keyword, func)	\
	{keyword, func, NULL},

keywordHash_t itemParseKeywords[] = {
	{"name", ItemParse_name, NULL},
	//Makro - support for shortcut keys
	{"shortcutkey", ItemParse_shortcutKey, NULL},
	//Makro - fixed text height for autowrapped items
	{"textHeight", ItemParse_textHeight, NULL},
	{"text", ItemParse_text, NULL},
	ADD_HASH_FUNC("cleanText", ItemParse_cleanText)
	{"group", ItemParse_group, NULL},
	//Makro - added subgroup
	{"subgroup", ItemParse_subgroup, NULL},
	{"asset_model", ItemParse_asset_model, NULL},
	{"asset_shader", ItemParse_asset_shader, NULL},
	{"model_origin", ItemParse_model_origin, NULL},
	{"model_fovx", ItemParse_model_fovx, NULL},
	{"model_fovy", ItemParse_model_fovy, NULL},
	{"model_rotation", ItemParse_model_rotation, NULL},
	{"model_angle", ItemParse_model_angle, NULL},
	//{"model_adjustable", ItemParse_model_adjustable, NULL},
	//Makro - support for 3 angles
	{"model_angles", ItemParse_model_angles, NULL},
	{"rect", ItemParse_rect, NULL},
	//Makro - ugliest hack ever... by far
	{"renderpoint", ItemParse_renderpoint, NULL},
	//Makro - forced text color
	{"forceTextColor", ItemParse_forceTextColor, NULL},
	//Makro - angled items
	{"alignrect", ItemParse_alignrect, NULL},
	{"adjustrect", ItemParse_adjustrect, NULL},
	{"vectors", ItemParse_vectors, NULL},
	{"anglevectors", ItemParse_anglevectors, NULL},
	{"normalizevectors", ItemParse_normalizevectors, NULL},
	//Makro - randomized texture co-ordinates for stretched shaders
	{"randomizeTexCoords", ItemParse_randomizeTexCoords, NULL},
	//Makro - menu anchor
	{"menuAnchor", ItemParse_menuAnchor, NULL},
	{"style", ItemParse_style, NULL},
	{"decoration", ItemParse_decoration, NULL},
	{"notselectable", ItemParse_notselectable, NULL},
	{"wrapped", ItemParse_wrapped, NULL},
	{"autowrapped", ItemParse_autowrapped, NULL},
	{"horizontalscroll", ItemParse_horizontalscroll, NULL},
	{"type", ItemParse_type, NULL},
	{"elementwidth", ItemParse_elementwidth, NULL},
	{"elementheight", ItemParse_elementheight, NULL},
	{"feeder", ItemParse_feeder, NULL},
	{"elementtype", ItemParse_elementtype, NULL},
	{"columns", ItemParse_columns, NULL},
	{"columndef", ItemParse_columndef, NULL},
	{"border", ItemParse_border, NULL},
	//Makro - for drop shadow effects
	{"shadowStyle", ItemParse_shadowStyle, NULL},
	{"bordersize", ItemParse_bordersize, NULL},
	{"visible", ItemParse_visible, NULL},
	{"ownerdraw", ItemParse_ownerdraw, NULL},
	{"align", ItemParse_align, NULL},
	{"textalign", ItemParse_textalign, NULL},
	{"textalignx", ItemParse_textalignx, NULL},
	{"textaligny", ItemParse_textaligny, NULL},
	{"textscale", ItemParse_textscale, NULL},
	{"textstyle", ItemParse_textstyle, NULL},
	{"backcolor", ItemParse_backcolor, NULL},
	{"forecolor", ItemParse_forecolor, NULL},
	{"bordercolor", ItemParse_bordercolor, NULL},
	{"outlinecolor", ItemParse_outlinecolor, NULL},
	{"background", ItemParse_background, NULL},
	{"onFocus", ItemParse_onFocus, NULL},
	{"leaveFocus", ItemParse_leaveFocus, NULL},
	//Makro - for timers
	{"onTimerShow", ItemParse_onTimerShow, NULL},
	{"onTimerHide", ItemParse_onTimerHide, NULL},
	{"mouseEnter", ItemParse_mouseEnter, NULL},
	{"mouseExit", ItemParse_mouseExit, NULL},
	{"mouseEnterText", ItemParse_mouseEnterText, NULL},
	{"mouseExitText", ItemParse_mouseExitText, NULL},
	{"action", ItemParse_action, NULL},
	{"special", ItemParse_special, NULL},
	{"cvar", ItemParse_cvar, NULL},

	//Makro - for checkboxes
	{"groupIndex", ItemParse_groupIndex, NULL},
	{"activeCvarValue", ItemParse_activeCvarValue, NULL},
	{"kind", ItemParse_kind, NULL},

	{"maxChars", ItemParse_maxChars, NULL},
	{"maxPaintChars", ItemParse_maxPaintChars, NULL},
	{"focusSound", ItemParse_focusSound, NULL},
	{"cvarFloat", ItemParse_cvarFloat, NULL},
	{"cvarStrList", ItemParse_cvarStrList, NULL},
	{"cvarFloatList", ItemParse_cvarFloatList, NULL},
	{"addColorRange", ItemParse_addColorRange, NULL},
	{"ownerdrawFlag", ItemParse_ownerdrawFlag, NULL},
	{"enableCvar", ItemParse_enableCvar, NULL},
	{"cvarTest", ItemParse_cvarTest, NULL},
	{"disableCvar", ItemParse_disableCvar, NULL},
	{"showCvar", ItemParse_showCvar, NULL},
	{"hideCvar", ItemParse_hideCvar, NULL},
	{"cinematic", ItemParse_cinematic, NULL},
	{"doubleclick", ItemParse_doubleClick, NULL},
	{NULL, 0, NULL}
};

keywordHash_t *itemParseKeywordHash[KEYWORDHASH_SIZE];

/*
===============
Item_SetupKeywordHash
===============
*/
void Item_SetupKeywordHash(void)
{
	int i;

	memset(itemParseKeywordHash, 0, sizeof(itemParseKeywordHash));
	for (i = 0; itemParseKeywords[i].keyword; i++) {
		KeywordHash_Add(itemParseKeywordHash, &itemParseKeywords[i]);
	}
}

/*
===============
Item_Parse
===============
*/
qboolean Item_Parse(int handle, itemDef_t * item)
{
	pc_token_t token;
	keywordHash_t *key;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}
	INFINITE_LOOP {
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu item\n");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		key = KeywordHash_Find(itemParseKeywordHash, token.string);
		if (!key) {
			PC_SourceError(handle, "unknown menu item keyword %s", token.string);
			continue;
		}
		if (!key->func(item, handle)) {
			PC_SourceError(handle, "couldn't parse menu item keyword %s", token.string);
			return qfalse;
		}
	}
	//Makro - unreachable
	//return qfalse;		// bk001205 - LCC missing return value
}

// Item_InitControls
// init's special control types
void Item_InitControls(itemDef_t * item)
{
	if (item == NULL) {
		return;
	}
	if (item->type == ITEM_TYPE_LISTBOX) {
		listBoxDef_t *listPtr = (listBoxDef_t *) item->typeData;

		item->cursorPos = 0;
		if (listPtr) {
			listPtr->cursorPos = 0;
			listPtr->startPos = 0;
			listPtr->endPos = 0;
			//Makro - set twice
			//listPtr->cursorPos = 0;
		}
	}
}

/*
===============
Menu Keyword Parse functions
===============
*/

qboolean MenuParse_font(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &menu->font)) {
		return qfalse;
	}
	if (!DC->Assets.fontRegistered) {
		DC->registerFont(menu->font, 48, &DC->Assets.textFont);
		DC->Assets.fontRegistered = qtrue;
	}
	return qtrue;
}

qboolean MenuParse_name(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &menu->window.name)) {
		return qfalse;
	}
	if (Q_stricmp(menu->window.name, "main") == 0) {
		// default main as having focus
		//menu->window.flags |= WINDOW_HASFOCUS;
	}
	return qtrue;
}

qboolean MenuParse_fullscreen(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, (int *) &menu->fullScreen)) {	// bk001206 - cast qboolean
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_renderpoint(itemDef_t *item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;
	menu->window.flags |= WINDOW_RENDERPOINT;
	return qtrue;
}

qboolean MenuParse_rect(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Rect_Parse(handle, &menu->window.rect)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - angled items
qboolean MenuParse_vectors(itemDef_t *item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;
	float u[2], v[2];
	if (PC_Float_Parse(handle, &u[0]))
	{
		if (PC_Float_Parse(handle, &u[1]))
		{
			if (PC_Float_Parse(handle, &v[0]))
			{
				if (PC_Float_Parse(handle, &v[1]))
				{
					Vector2Copy(u, menu->window.rectClient.u);
					Vector2Copy(v, menu->window.rectClient.v);
					Vector2Copy(u, menu->window.rect.u);
					Vector2Copy(v, menu->window.rect.v);
					menu->window.rectClient.hasVectors=qtrue;
					menu->window.rect.hasVectors=qtrue;
					return qtrue;
				}
			}
		}
	}
	return qfalse;
}

qboolean MenuParse_normalizevectors(itemDef_t *item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;
	float norm;
	
	if (!menu->window.rectClient.hasVectors)
		return qfalse;

	norm = Vector2Norm2(menu->window.rectClient.u);
	if (!norm)
		return qfalse;
	Vector2Scale(menu->window.rectClient.u, 1.0f/norm, menu->window.rectClient.u);
	Vector2Copy(menu->window.rectClient.u, menu->window.rect.u);

	norm = Vector2Norm2(menu->window.rectClient.v);
	if (!norm)
		return qfalse;
	Vector2Scale(menu->window.rectClient.v, 1.0f/norm, menu->window.rectClient.v);
	Vector2Copy(menu->window.rectClient.v, menu->window.rect.u);
	return qtrue;
}

qboolean MenuParse_anglevectors(itemDef_t *item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;
	float u, v;
	if (PC_Float_Parse(handle, &u))
	{
		if (PC_Float_Parse(handle, &v))
		{
			u = DEG2RAD(-u);
			v = DEG2RAD(-v);
			Vector2Set(menu->window.rectClient.u, cos(u), sin(u));
			Vector2Set(menu->window.rectClient.v, cos(v), sin(v));
			Vector2Copy(menu->window.rectClient.u, menu->window.rect.u);
			Vector2Copy(menu->window.rectClient.v, menu->window.rect.v);
			menu->window.rectClient.hasVectors=qtrue;
			menu->window.rect.hasVectors=qtrue;
			return qtrue;
		}
	}
	return qfalse;
}

qboolean MenuParse_style(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->window.style)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_visible(itemDef_t * item, int handle)
{
	int i;
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &i)) {
		return qfalse;
	}
	if (i) {
		menu->window.flags |= WINDOW_VISIBLE;
	}
	return qtrue;
}

qboolean MenuParse_onOpen(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onOpen)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - executed when the menu is shown
qboolean MenuParse_onShow(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onShow)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_onFirstShow(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onFirstShow)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - executed when the item is shown with openSpecial
qboolean MenuParse_onOpenSpecial(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onOpenSpecial)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - executed when the user clicks outside the active area
qboolean MenuParse_onOOBClick(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onOOBClick)) {
		return qfalse;
	}
	menu->window.flags |= WINDOW_OOB_CLICK;
	return qtrue;
}

//Makro - executed in addition to the item script
qboolean MenuParse_onTimerShow(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onTimerShow)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - executed in addition to the item script
qboolean MenuParse_onTimerHide(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onTimerHide)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_onClose(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onClose)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_onESC(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onESC)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - executed when all the items in a timed sequence have been shown
qboolean MenuParse_onFinishTimer(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Script_Parse(handle, &menu->onFinishTimer)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - timer interval
qboolean MenuParse_timerInterval(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->timerInterval)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - total items in timed sequence
qboolean MenuParse_timedItems(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->timedItems)) {
		return qfalse;
	}
	return qtrue;
}

//number of items to be shown at a time
qboolean MenuParse_timerMaxDisplay(itemDef_t *item, int handle)
{
	menuDef_t *menu = (menuDef_t*) item;
	if (!PC_Int_Parse(handle, &menu->timerMaxDisplay)) {
		menu->timerMaxDisplay = 1;
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_border(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->window.border)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - for drop shadow effects
qboolean MenuParse_shadowStyle(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->window.shadowStyle)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_borderSize(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Float_Parse(handle, &menu->window.borderSize)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_backcolor(itemDef_t * item, int handle)
{
	int i;
	float f;
	menuDef_t *menu = (menuDef_t *) item;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		menu->window.backColor[i] = f;
	}
	return qtrue;
}

qboolean MenuParse_forecolor(itemDef_t * item, int handle)
{
	int i;
	float f;
	menuDef_t *menu = (menuDef_t *) item;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		menu->window.foreColor[i] = f;
		menu->window.flags |= WINDOW_FORECOLORSET;
	}
	return qtrue;
}

qboolean MenuParse_bordercolor(itemDef_t * item, int handle)
{
	int i;
	float f;
	menuDef_t *menu = (menuDef_t *) item;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		menu->window.borderColor[i] = f;
	}
	return qtrue;
}

qboolean MenuParse_focuscolor(itemDef_t * item, int handle)
{
	int i;
	float f;
	menuDef_t *menu = (menuDef_t *) item;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		menu->focusColor[i] = f;
	}
	return qtrue;
}

qboolean MenuParse_disablecolor(itemDef_t * item, int handle)
{
	int i;
	float f;
	menuDef_t *menu = (menuDef_t *) item;

	for (i = 0; i < 4; i++) {
		if (!PC_Float_Parse(handle, &f)) {
			return qfalse;
		}
		menu->disableColor[i] = f;
	}
	return qtrue;
}

qboolean MenuParse_outlinecolor(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Color_Parse(handle, &menu->window.outlineColor)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_background(itemDef_t * item, int handle)
{
	const char *buff;
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &buff)) {
		return qfalse;
	}
	menu->window.background = DC->registerShaderNoMip(buff);
	return qtrue;
}

qboolean MenuParse_cinematic(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &menu->window.cinematicName)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_ownerdrawFlag(itemDef_t * item, int handle)
{
	int i;
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &i)) {
		return qfalse;
	}
	menu->window.ownerDrawFlags |= i;
	return qtrue;
}

qboolean MenuParse_ownerdraw(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->window.ownerDraw)) {
		return qfalse;
	}
	return qtrue;
}

// decoration
qboolean MenuParse_popup(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	menu->window.flags |= WINDOW_POPUP;
	return qtrue;
}

//Makro - obsolete
/*
qboolean MenuParse_outOfBounds(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	menu->window.flags |= WINDOW_OOB_CLICK;
	return qtrue;
}
*/
qboolean MenuParse_soundLoop(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &menu->soundName)) {
		return qfalse;
	}
	return qtrue;
}

//Makro - support for music with intro
qboolean MenuParse_soundIntro(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_String_Parse(handle, &menu->soundIntro)) {
		return qfalse;
	}

	return qtrue;
}

qboolean MenuParse_fadeClamp(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Float_Parse(handle, &menu->fadeClamp)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_fadeAmount(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Float_Parse(handle, &menu->fadeAmount)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_fadeCycle(itemDef_t * item, int handle)
{
	menuDef_t *menu = (menuDef_t *) item;

	if (!PC_Int_Parse(handle, &menu->fadeCycle)) {
		return qfalse;
	}
	return qtrue;
}

qboolean MenuParse_itemDef( itemDef_t *item, int handle ) {
	menuDef_t *menu = (menuDef_t*)item;
	if (menu->itemCount < MAX_MENUITEMS) {
		menu->items[menu->itemCount] = UI_Alloc(sizeof(itemDef_t));
		Item_Init(menu->items[menu->itemCount]);
		//was below
		menu->items[menu->itemCount]->parent = menu;
		if (!Item_Parse(handle, menu->items[menu->itemCount])) {
			return qfalse;
		}
		Item_InitControls(menu->items[menu->itemCount]);
		//Makro - moved above
		//menu->items[menu->itemCount++]->parent = menu;
		menu->itemCount++;
	}
	return qtrue;
}

keywordHash_t menuParseKeywords[] = {
	{"font", MenuParse_font, NULL},
	{"name", MenuParse_name, NULL},
	{"fullscreen", MenuParse_fullscreen, NULL},
	{"rect", MenuParse_rect, NULL},
	//Makro - ugliest hack ever... by far
	{"renderpoint", MenuParse_renderpoint, NULL},
	//Makro - angled items
	{"vectors", MenuParse_vectors, NULL},
	{"anglevectors", MenuParse_anglevectors, NULL},
	{"normalizevectors", MenuParse_normalizevectors, NULL},
	{"style", MenuParse_style, NULL},
	{"visible", MenuParse_visible, NULL},
	{"onOpen", MenuParse_onOpen, NULL},
	//Makro - executed when the menu is shown
	{"onShow", MenuParse_onShow, NULL},
	{"onFirstShow", MenuParse_onFirstShow, NULL},
	//Makro - executed when the user clicks outside the active area
	{"onOOBClick", MenuParse_onOOBClick, NULL},
	//Makro - executed when the menu is shown with showSpecial
	{"onOpenSpecial", MenuParse_onOpenSpecial, NULL},
	{"onShowSpecial", MenuParse_onOpenSpecial, NULL},
	{"onClose", MenuParse_onClose, NULL},
	{"onESC", MenuParse_onESC, NULL},
	//Makro - executed when all the items in a timed sequence have been shown
	{"onFinishTimer", MenuParse_onFinishTimer, NULL},
	//Makro - executed in addition to the item script
	{"onTimerShow", MenuParse_onTimerShow},
	{"onTimerHide", MenuParse_onTimerHide},
	//Makro - timer interval
	{"timerInterval", MenuParse_timerInterval, NULL},
	//Makro - total items in timed sequence
	{"timedItems", MenuParse_timedItems, NULL},
	//number of items to be shown at a time
	{"timermaxdisplay", MenuParse_timerMaxDisplay, NULL},
	{"border", MenuParse_border, NULL},
	//Makro - for drop shadow effects
	{"shadowStyle", MenuParse_shadowStyle, NULL},
	{"dropShadowStyle", MenuParse_shadowStyle, NULL},
	{"borderSize", MenuParse_borderSize, NULL},
	{"backcolor", MenuParse_backcolor, NULL},
	{"forecolor", MenuParse_forecolor, NULL},
	{"bordercolor", MenuParse_bordercolor, NULL},
	{"focuscolor", MenuParse_focuscolor, NULL},
	{"disablecolor", MenuParse_disablecolor, NULL},
	{"outlinecolor", MenuParse_outlinecolor, NULL},
	{"background", MenuParse_background, NULL},
	{"ownerdraw", MenuParse_ownerdraw, NULL},
	{"ownerdrawFlag", MenuParse_ownerdrawFlag, NULL},
	//Makro - obsolete
	//{"outOfBoundsClick", MenuParse_outOfBounds, NULL},
	{"soundLoop", MenuParse_soundLoop, NULL},
	//Makro - support for music with intro
	{"soundIntro", MenuParse_soundIntro, NULL},
	{"itemDef", MenuParse_itemDef, NULL},
	{"cinematic", MenuParse_cinematic, NULL},
	{"popup", MenuParse_popup, NULL},
	{"fadeClamp", MenuParse_fadeClamp, NULL},
	{"fadeCycle", MenuParse_fadeCycle, NULL},
	{"fadeAmount", MenuParse_fadeAmount, NULL},
	{NULL, 0, NULL}
};

keywordHash_t *menuParseKeywordHash[KEYWORDHASH_SIZE];

/*
===============
Menu_SetupKeywordHash
===============
*/
void Menu_SetupKeywordHash(void)
{
	int i;

	memset(menuParseKeywordHash, 0, sizeof(menuParseKeywordHash));
	for (i = 0; menuParseKeywords[i].keyword; i++) {
		KeywordHash_Add(menuParseKeywordHash, &menuParseKeywords[i]);
	}
}

/*
===============
Menu_Parse
===============
*/
qboolean Menu_Parse(int handle, menuDef_t * menu)
{
	pc_token_t token;
	keywordHash_t *key;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}

	INFINITE_LOOP {

		memset(&token, 0, sizeof(pc_token_t));
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu\n");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		key = KeywordHash_Find(menuParseKeywordHash, token.string);
		if (!key) {
			PC_SourceError(handle, "unknown menu keyword %s", token.string);
			continue;
		}
		if (!key->func((itemDef_t *) menu, handle)) {
			PC_SourceError(handle, "couldn't parse menu keyword %s", token.string);
			return qfalse;
		}
	}
	//Makro - unreachable
	//return qfalse;		// bk001205 - LCC missing return value
}

/*
===============
Menu_New
===============
*/
void Menu_New(int handle)
{
	menuDef_t *menu = &Menus[menuCount];

	if (menuCount < MAX_MENUS) {
		Menu_Init(menu);
		if (Menu_Parse(handle, menu)) {
			Menu_PostParse(menu);
			menuCount++;
		}
	}
}

int Menu_Count()
{
	return menuCount;
}

void Menu_PaintAll()
{
	int i;

	if (captureFunc) {
		captureFunc(captureData);
	}

	//Makro - using menu stack now
	//for (i = 0; i < Menu_Count(); i++) {
	//	Menu_Paint(&Menus[i], qfalse);
	//}
	for (i = 0; i < openMenuCount; i++) {
		Menu_Paint(menuStack[i], qfalse);
	}

	if (debugMode) {
		vec4_t v = { 1, 1, 1, 1 };

		DC->drawText(5, 25, .5, v, va("fps: %f", DC->FPS), 0, 0, 0, 0, qfalse);
	}
}

void Menu_Reset()
{
	menuCount = 0;
}

displayContextDef_t *Display_GetContext()
{
	return DC;
}

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static float captureX;
static float captureY;
#endif
*/

void *Display_CaptureItem(int x, int y)
{
	int i;

	for (i = 0; i < menuCount; i++) {
		// turn off focus each item
		// menu->items[i].window.flags &= ~WINDOW_HASFOCUS;
		if (Rect_ContainsPoint(&Menus[i].window.rect, x, y)) {
			return &Menus[i];
		}
	}
	return NULL;
}

// FIXME:
//Makro - fixed :) 
qboolean Display_MouseMove(void *p, int x, int y)
{
	int i;
	menuDef_t *menu = p;

	if (menu == NULL) {
		menu = Menu_GetFocused();
		if (menu) {
			if (menu->window.flags & WINDOW_POPUP) {
				Menu_HandleMouseMove(menu, x, y);
				return qtrue;
			}
		}
		for (i = 0; i < menuCount; i++) {
			Menu_HandleMouseMove(&Menus[i], x, y);
		}
	} else {
		menu->window.rect.x += x - g_anchorX;
		menu->window.rect.y += y - g_anchorY;
		g_anchorX = x;
		g_anchorY = y;
		Menu_UpdatePosition(menu);
	}
	return qtrue;

}

int Display_CursorType(int x, int y)
{
	int i;

	for (i = 0; i < menuCount; i++) {
		rectDef_t r2;

		r2.x = Menus[i].window.rect.x - 3;
		r2.y = Menus[i].window.rect.y - 3;
		r2.w = r2.h = 7;
		if (Rect_ContainsPoint(&r2, x, y)) {
			return CURSOR_SIZER;
		}
	}
	return CURSOR_ARROW;
}

void Display_HandleKey(int key, qboolean down, int x, int y)
{
	menuDef_t *menu = Display_CaptureItem(x, y);

	if (menu == NULL) {
		menu = Menu_GetFocused();
	}
	if (menu) {
		Menu_HandleKey(menu, key, down);
	}
}

static void Window_CacheContents(windowDef_t * window)
{
	if (window) {
		if (window->cinematicName) {
			int cin = DC->playCinematic(window->cinematicName, 0, 0, 0, 0);

			DC->stopCinematic(cin);
		}
	}
}

static void Item_CacheContents(itemDef_t * item)
{
	if (item) {
		Window_CacheContents(&item->window);
	}

}

static void Menu_CacheContents(menuDef_t * menu)
{
	if (menu) {
		int i;

		Window_CacheContents(&menu->window);
		for (i = 0; i < menu->itemCount; i++) {
			Item_CacheContents(menu->items[i]);
		}

		if (menu->soundName && *menu->soundName) {
			DC->registerSound(menu->soundName, qfalse);
		}
		//Makro - caching sound intro
		if (menu->soundIntro && *menu->soundIntro) {
			DC->registerSound(menu->soundIntro, qfalse);
		}
	}

}

void Display_CacheAll()
{
	int i;

	for (i = 0; i < menuCount; i++) {
		Menu_CacheContents(&Menus[i]);
	}
}

static qboolean Menu_OverActiveItem(menuDef_t * menu, float x, float y)
{
	if (menu && menu->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED)) {
		if (Rect_ContainsPoint(&menu->window.rect, x, y)) {
			int i;

			for (i = 0; i < menu->itemCount; i++) {
				// turn off focus each item
				// menu->items[i].window.flags &= ~WINDOW_HASFOCUS;

				if (!(menu->items[i]->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
					continue;
				}

				if (menu->items[i]->window.flags & WINDOW_DECORATION) {
					continue;
				}

				if (Rect_ContainsPoint(&menu->items[i]->window.rect, x, y)) {
					itemDef_t *overItem = menu->items[i];

					if (overItem->type == ITEM_TYPE_TEXT && overItem->text) {
						if (Rect_ContainsPoint(Item_CorrectedTextRect(overItem), x, y)) {
							return qtrue;
						} else {
							continue;
						}
					} else {
						return qtrue;
					}
				}
			}

		}
	}
	return qfalse;
}

