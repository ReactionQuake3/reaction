//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.13  2005/02/15 16:33:38  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.12  2004/01/26 21:26:08  makro
// no message
//
// Revision 1.11  2002/08/07 04:45:46  niceass
// ctb changes
//
// Revision 1.10  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.9  2002/03/24 22:48:57  niceass
// cg_draw change for scoreboard
//
// Revision 1.8  2002/02/04 00:22:50  niceass
// Added DrawCleanBox for scoreboard
//
// Revision 1.7  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.6  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_drawtools.c -- helper functions called by cg_draw, cg_scoreboard, cg_info, etc
#include "cg_local.h"

/*
================
CG_AdjustFrom640

Adjusted for resolution and screen aspect ratio
================
*/
void CG_AdjustFrom640(float *x, float *y, float *w, float *h)
{
#if 0
	// adjust for wide screens
	if (cgs.glconfig.vidWidth * 480 > cgs.glconfig.vidHeight * 640) {
		*x += 0.5 * (cgs.glconfig.vidWidth - (cgs.glconfig.vidHeight * 640 / 480));
	}
#endif
	// scale for screen sizes
	*x *= cgs.screenXScale;
	*y *= cgs.screenYScale;
	*w *= cgs.screenXScale;
	*h *= cgs.screenYScale;
}

/*
================
CG_FillRect

Coordinates are 640*480 virtual values
=================
*/
void CG_FillRect(float x, float y, float width, float height, const float *color)
{
	trap_R_SetColor(color);

	CG_AdjustFrom640(&x, &y, &width, &height);
	trap_R_DrawStretchPic(x, y, width, height, 0, 0, 0, 0, cgs.media.whiteShader);

	trap_R_SetColor(NULL);
}

/*
================
CG_DrawSides

Coords are virtual 640x480
================
*/
void CG_DrawSides(float x, float y, float w, float h, float size)
{
	CG_AdjustFrom640(&x, &y, &w, &h);
	size *= cgs.screenXScale;
	trap_R_DrawStretchPic(x, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x + w - size, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
}

void CG_DrawTopBottom(float x, float y, float w, float h, float size)
{
	CG_AdjustFrom640(&x, &y, &w, &h);
	size *= cgs.screenYScale;
	trap_R_DrawStretchPic(x, y, w, size, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x, y + h - size, w, size, 0, 0, 0, 0, cgs.media.whiteShader);
}

/*
================
CG_DrawCleanTopBottom -- Added by NiceAss
"Size" not scaled 

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawCleanSides(float x, float y, float w, float h, float size, const float *color)
{
	CG_AdjustFrom640(&x, &y, &w, &h);
	trap_R_SetColor(color);
	trap_R_DrawStretchPic(x, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x + w - size, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_SetColor(NULL);
}

void CG_DrawCleanLine(float x, float y, float w, float size, const float *color)
{
	float h = 0;

	CG_AdjustFrom640(&x, &y, &w, &h);
	trap_R_SetColor(color);
	trap_R_DrawStretchPic(x, y, w, size, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_SetColor(NULL);
}

/*
================
UI_DrawRect

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawRect(float x, float y, float width, float height, float size, const float *color)
{
	trap_R_SetColor(color);

	CG_DrawTopBottom(x, y, width, height, size);
	CG_DrawSides(x, y, width, height, size);

	trap_R_SetColor(NULL);
}

/*
================
UI_DrawRect -- Added by NiceAss
"Size" not scaled 

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawCleanRect(float x, float y, float width, float height, float size, const float *color)
{
	CG_AdjustFrom640(&x, &y, &width, &height);
	trap_R_SetColor(color);
	trap_R_DrawStretchPic(x, y, size, height, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x + width - size, y, size, height, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x, y, width, size, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x, y + height - size, width, size, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_SetColor(NULL);
}

/*
================
CG_DrawPic

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawPic(float x, float y, float width, float height, qhandle_t hShader)
{
	CG_AdjustFrom640(&x, &y, &width, &height);
	trap_R_DrawStretchPic(x, y, width, height, 0, 0, 1, 1, hShader);
}

/*
===============
CG_DrawChar

Coordinates and size in 640*480 virtual screen size
===============
*/
void CG_DrawChar(int x, int y, int width, int height, int ch)
{
	int row, col;
	float frow, fcol;
	float size;
	float ax, ay, aw, ah;

	ch &= 255;

	if (ch == ' ') {
		return;
	}

	ax = x;
	ay = y;
	aw = width;
	ah = height;
	CG_AdjustFrom640(&ax, &ay, &aw, &ah);

	row = ch >> 4;
	col = ch & 15;

	frow = row * 0.0625;
	fcol = col * 0.0625;
	size = 0.0625;

	trap_R_DrawStretchPic(ax, ay, aw, ah, fcol, frow, fcol + size, frow + size, cgs.media.charsetShader);
}

/*
==================
CG_DrawStringExt

Draws a multi-colored string with a drop shadow, optionally forcing
to a fixed color.

Coordinates are at 640 by 480 virtual resolution
==================
*/
void CG_DrawStringExt(int x, int y, const char *string, const float *setColor,
		      qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars)
{
	//Makro - for underlined chars
	int yoffset = y + charHeight * 0.25f;
	qboolean underlined = qfalse;
	vec4_t color;
	const char *s;
	int xx;
	int cnt;

	if (maxChars <= 0)
		maxChars = 32767;	// do them all!

	// draw the drop shadow
	if (shadow) {
		color[0] = color[1] = color[2] = 0;
		color[3] = setColor[3];
		trap_R_SetColor(color);
		s = string;
		xx = x;
		cnt = 0;
		while (*s && cnt < maxChars) {
			if (Q_IsColorString(s)) {
				s += 2;
				continue;
			}
			CG_DrawChar(xx + 2, y + 2, charWidth, charHeight, *s);
			cnt++;
			xx += charWidth;
			s++;
		}
	}
	// draw the colored text
	s = string;
	xx = x;
	cnt = 0;
	trap_R_SetColor(setColor);
	while (*s && cnt < maxChars) {
		if (Q_IsColorString(s)) {
			if (!forceColor) {
				//Makro - new tricks
				if (*(s+1) == '*')
				{
					memcpy(color, setColor, sizeof(color));
					trap_R_SetColor(color);
				} else if (*(s+1)== '_')
				{
					underlined ^= qtrue;
				} else {
					memcpy(color, g_color_table[ColorIndex(*(s + 1))], sizeof(color));
					color[3] = setColor[3];
					trap_R_SetColor(color);
				}
			}
			s += 2;
			continue;
		}
		CG_DrawChar(xx, y, charWidth, charHeight, *s);
		if (underlined)
		{
			CG_DrawChar(xx, yoffset, charWidth, charHeight, '_');
		}
		xx += charWidth;
		cnt++;
		s++;
	}
	trap_R_SetColor(NULL);
}

void CG_DrawBigString(int x, int y, const char *s, float alpha)
{
	float color[4];

	color[0] = color[1] = color[2] = 1.0;
	color[3] = alpha;
	CG_DrawStringExt(x, y, s, color, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0);
}

void CG_DrawBigStringColor(int x, int y, const char *s, vec4_t color)
{
	CG_DrawStringExt(x, y, s, color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0);
}

void CG_DrawSmallString(int x, int y, const char *s, float alpha)
{
	float color[4];

	color[0] = color[1] = color[2] = 1.0;
	color[3] = alpha;
	CG_DrawStringExt(x, y, s, color, qfalse, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
}

void CG_DrawSmallStringColor(int x, int y, const char *s, vec4_t color)
{
	CG_DrawStringExt(x, y, s, color, qtrue, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
}

/*
=================
CG_DrawStrlen

Returns character count, skiping color escape codes
=================
*/
int CG_DrawStrlen(const char *str)
{
	const char *s = str;
	int count = 0;

	while (*s) {
		if (Q_IsColorString(s)) {
			s += 2;
		} else {
			count++;
			s++;
		}
	}

	return count;
}

/*
=============
CG_TileClearBox

This repeats a 64*64 tile graphic to fill the screen around a sized down
refresh window.
=============
*/
static void CG_TileClearBox(int x, int y, int w, int h, qhandle_t hShader)
{
	float s1, t1, s2, t2;

	s1 = x / 64.0;
	t1 = y / 64.0;
	s2 = (x + w) / 64.0;
	t2 = (y + h) / 64.0;
	trap_R_DrawStretchPic(x, y, w, h, s1, t1, s2, t2, hShader);
}

/*
==============
CG_TileClear

Clear around a sized down screen
==============
*/
void CG_TileClear(void)
{
	int top, bottom, left, right;
	int w, h;

	w = cgs.glconfig.vidWidth;
	h = cgs.glconfig.vidHeight;

	if (cg.refdef.x == 0 && cg.refdef.y == 0 && cg.refdef.width == w && cg.refdef.height == h) {
		return;		// full screen rendering
	}

	top = cg.refdef.y;
	bottom = top + cg.refdef.height - 1;
	left = cg.refdef.x;
	right = left + cg.refdef.width - 1;

	// clear above view screen
	CG_TileClearBox(0, 0, w, top, cgs.media.backTileShader);

	// clear below view screen
	CG_TileClearBox(0, bottom, w, h - bottom, cgs.media.backTileShader);

	// clear left of view screen
	CG_TileClearBox(0, top, left, bottom - top + 1, cgs.media.backTileShader);

	// clear right of view screen
	CG_TileClearBox(right, top, w - right, bottom - top + 1, cgs.media.backTileShader);
}

/*
================
CG_FadeColor
================
*/
float *CG_FadeColor(int startMsec, int totalMsec)
{
	static vec4_t color;
	int t;

	if (startMsec == 0) {
		return NULL;
	}

	t = cg.time - startMsec;

	if (t >= totalMsec) {
		return NULL;
	}
	// fade out
	if (totalMsec - t < FADE_TIME) {
		color[3] = (totalMsec - t) * 1.0 / FADE_TIME;
	} else {
		color[3] = 1.0;
	}
	color[0] = color[1] = color[2] = 1;

	return color;
}

/*
================
CG_TeamColor
================
*/
void CG_TeamColor(int team, float *color)
{
	if ( cgs.gametype == GT_CTF ) {
		switch (team) {
		case TEAM_RED:
			MAKERGBA(color, 0.5f, 0.5f, 0.5f, 1);
			break;
		case TEAM_BLUE:
			MAKERGBA(color, 0, 0, 0, 1);
			break;
		default:
			MAKERGBA(color, 1, 1, 1, 1);
			break;
		}
	}
	else
	{
		switch (team) {
		case TEAM_RED:
			MAKERGBA(color, 1, 0, 0, 1);
			break;
		case TEAM_BLUE:
			MAKERGBA(color, 0, 0, 1, 1);
			break;
		default:
			MAKERGBA(color, 1, 1, 1, 1);
			break;
		}
	}
}

/*
=================
CG_GetColorForHealth
=================
*/
void CG_GetColorForHealth(int health, int armor, vec4_t hcolor)
{
	int count;
	int max;

	// calculate the total points of damage that can
	// be sustained at the current health / armor level
	if (health <= 0) {
		VectorClear(hcolor);	// black
		hcolor[3] = 1;
		return;
	}
	count = armor;
	max = health * ARMOR_PROTECTION / (1.0 - ARMOR_PROTECTION);
	if (max < count) {
		count = max;
	}
	health += count;

	// set the color based on health
	hcolor[0] = 1.0;
	hcolor[3] = 1.0;
	if (health >= 100) {
		hcolor[2] = 1.0;
	} else if (health < 66) {
		hcolor[2] = 0;
	} else {
		hcolor[2] = (health - 66) / 33.0;
	}

	if (health > 60) {
		hcolor[1] = 1.0;
	} else if (health < 30) {
		hcolor[1] = 0;
	} else {
		hcolor[1] = (health - 30) / 30.0;
	}
}

/*
=================
CG_ColorForHealth
=================
*/
void CG_ColorForHealth(vec4_t hcolor)
{

	CG_GetColorForHealth(cg.snap->ps.stats[STAT_HEALTH], cg.snap->ps.stats[STAT_ARMOR], hcolor);
}

// bk001205 - code below duplicated in q3_ui/ui-atoms.c
// bk001205 - FIXME: does this belong in ui_shared.c?
// bk001205 - FIXME: HARD_LINKED flags not visible here
#ifndef Q3_STATIC		// bk001205 - q_shared defines not visible here
/*
=================
UI_DrawProportionalString2
=================
*/
static int propMap[128][3] = {
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},

	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},

	//Makro - new map
	/*
	//Elder: new map

	{0, 0, PROP_SPACE_WIDTH},	// SPACE
	{3, 120, 8},		// !
	{145, 168, 9},		// "
	{38, 120, 15},		// #
	{54, 120, 26},		// $
	{81, 120, 21},		// %
	{138, 120, 26},		// &
	{128, 168, 5},		// '
	{207, 120, 9},		// (
	{228, 120, 9},		// )
	{182, 120, 12},		// *
	{30, 144, 15},		// +
	{74, 168, 7},		// ,
	{37, 96, 10},		// -
	{98, 168, 8},		// .
	{118, 144, 19},		// /

	{230, 72, 25},		// 0
	{1, 72, 21},		// 1
	{26, 72, 25},		// 2
	{52, 72, 25},		// 3
	{78, 72, 24},		// 4
	{102, 72, 26},		// 5
	{128, 72, 25},		// 6
	{153, 72, 25},		// 7
	{178, 72, 26},		// 8
	{204, 72, 25},		// 9
	{55, 168, 8},		// :
	{29, 168, 9},		// ;
	{195, 168, 14},		// <
	{59, 96, 19},		// =
	{219, 168, 14},		// >
	{165, 168, 24},		// ?

	{14, 120, 20},		// @
	{1, 0, 24},		// A
	{26, 0, 24},		// B
	{51, 0, 24},		// C
	{77, 0, 24},		// D
	{103, 0, 24},		// E
	{127, 0, 24},		// F
	{152, 0, 24},		// G
	{178, 0, 24},		// H
	{203, 0, 25},		// I
	{229, 0, 24},		// J

	{1, 24, 25},		// K
	{27, 24, 20},		// L
	{52, 24, 24},		// M
	{78, 24, 24},		// N
	{103, 24, 24},		// O
	{128, 24, 24},		// P
	{153, 24, 24},		// Q
	{179, 24, 24},		// R
	{205, 24, 24},		// S
	{233, 24, 20},		// T

	{1, 48, 25},		// U
	{29, 48, 22},		// V
	{54, 48, 22},		// W
	{77, 48, 25},		// X
	{103, 48, 24},		// Y
	{128, 48, 25},		// Z
	{55, 144, 13},		// [
	{102, 144, 10},		// '\'
	{75, 144, 13},		// ]
	{115, 128, 13},		// ^ Elder: fix me in tga!!
	{2, 144, 15},		// _

	{134, 181, 5},		// '
//Elder: note - lowercase
	{1, 0, 24},		// A
	{26, 0, 24},		// B
	{51, 0, 24},		// C
	{77, 0, 24},		// D
	{103, 0, 24},		// E
	{127, 0, 24},		// F
	{152, 0, 24},		// G
	{178, 0, 24},		// H
	{203, 0, 25},		// I
	{229, 0, 24},		// J

	{1, 24, 25},		// K
	{27, 24, 20},		// L
	{52, 24, 24},		// M
	{78, 24, 24},		// N
	{103, 24, 24},		// O
	{128, 24, 24},		// P
	{153, 24, 24},		// Q
	{179, 24, 24},		// R
	{205, 24, 24},		// S
	{233, 24, 20},		// T

	{1, 48, 25},		// U
	{29, 48, 22},		// V
	{54, 48, 22},		// W
	{77, 48, 25},		// X
	{103, 48, 24},		// Y
	{128, 48, 25},		// Z
	{148, 144, 11},		// {
	{5, 168, 10},		// |
	{169, 144, 11},		// }
	{85, 96, 14},		// ~
	{0, 0, -1}		// DEL
};
*/

{0, 0, PROP_SPACE_WIDTH}, 	// SPACE
{3, 0, 36}, 	// !
{42, 0, 36}, 	// "
{81, 0, 36}, 	// #
{120, 0, 36}, 	// $
{159, 0, 16}, 	// %
{178, 0, 36}, 	// &
{217, 0, 58}, 	// '
{278, 0, 36}, 	// (
{317, 0, 58}, 	// )
{378, 0, 36}, 	// *
{417, 0, 36}, 	// +
{456, 0, 36}, 	// ,
{0, 27, 36}, 	// -
{39, 27, 19}, 	// .
{61, 27, 58}, 	// /
{122, 27, 14}, 	// 0
{139, 27, 8}, 	// 1
{150, 27, 13}, 	// 2
{166, 27, 13}, 	// 3
{182, 27, 14}, 	// 4
{199, 27, 13}, 	// 5
{215, 27, 14}, 	// 6
{232, 27, 12}, 	// 7
{247, 27, 13}, 	// 8
{263, 27, 13}, 	// 9
{279, 27, 11}, 	// :
{293, 27, 58}, 	// ;
{354, 27, 58}, 	// <
{415, 27, 36}, 	// =
{454, 27, 58}, 	// >
{0, 54, 36}, 	// ?
{39, 54, 36}, 	// @
{78, 54, 17}, 	// A
{98, 54, 13}, 	// B
{114, 54, 15}, 	// C
{132, 54, 16}, 	// D
{151, 54, 15}, 	// E
{169, 54, 16}, 	// F
{188, 54, 18}, 	// G
{209, 54, 20}, 	// H
{232, 54, 9}, 	// I
{244, 54, 36}, 	// J
{283, 54, 18}, 	// K
{304, 54, 15}, 	// L
{322, 54, 20}, 	// M
{345, 54, 18}, 	// N
{366, 54, 16}, 	// O
{385, 54, 16}, 	// P
{404, 54, 13}, 	// Q
{420, 54, 18}, 	// R
{441, 54, 14}, 	// S
{458, 54, 16}, 	// T
{477, 54, 18}, 	// U
{498, 54, 14}, 	// V
{0, 81, 18}, 	// W
{21, 81, 13}, 	// X
{37, 81, 16}, 	// Y
{56, 81, 36}, 	// Z
{95, 81, 36}, 	// [
{134, 81, 36}, 	// '\'
{173, 81, 36}, 	// ]
{212, 81, 36}, 	// ^
{251, 81, 36}, 	// _
{290, 81, 36}, 	// `
{329, 81, 18}, 	// a
{350, 81, 13}, 	// b
{366, 81, 15}, 	// c
{384, 81, 16}, 	// d
{403, 81, 15}, 	// e
{421, 81, 14}, 	// f
{438, 81, 17}, 	// g
{458, 81, 18}, 	// h
{479, 81, 11}, 	// i
{0, 108, 36}, 	// j
{39, 108, 20}, 	// k
{62, 108, 15}, 	// l
{80, 108, 19}, 	// m
{102, 108, 16}, 	// n
{121, 108, 14}, 	// o
{138, 108, 17}, 	// p
{158, 108, 13}, 	// q
{174, 108, 18}, 	// r
{195, 108, 13}, 	// s
{211, 108, 16}, 	// t
{230, 108, 15}, 	// u
{248, 108, 13}, 	// v
{264, 108, 18}, 	// w
{285, 108, 14}, 	// x
{302, 108, 16}, 	// y
{321, 108, 36}, 	// z
{360, 108, 36}, 	// {
{399, 108, 36}, 	// |
{438, 108, 36}, 	// }
{0, 135, 36}, 	// ~
{0, 0, -1} 	// DEL
};

/*Elder: old one
{0, 0, PROP_SPACE_WIDTH},		// SPACE
{11, 122, 7},	// !
{154, 181, 14},	// "
{55, 122, 17},	// #
{79, 122, 18},	// $
{101, 122, 23},	// %
{153, 122, 18},	// &
{9, 93, 7},		// '
{207, 122, 8},	// (
{230, 122, 9},	// )
{177, 122, 18},	// *
{30, 152, 18},	// +
{85, 181, 7},	// ,
{34, 93, 11},	// -
{110, 181, 6},	// .
{130, 152, 14},	// /

{22, 64, 17},	// 0
{41, 64, 12},	// 1
{58, 64, 17},	// 2
{78, 64, 18},	// 3
{98, 64, 19},	// 4
{120, 64, 18},	// 5
{141, 64, 18},	// 6
{204, 64, 16},	// 7
{162, 64, 17},	// 8
{182, 64, 18},	// 9
{59, 181, 7},	// :
{35,181, 7},	// ;
{203, 152, 14},	// <
{56, 93, 14},	// =
{228, 152, 14},	// >
{177, 181, 18},	// ?

{28, 122, 22},	// @
{5, 4, 18},		// A
{27, 4, 18},	// B
{48, 4, 18},	// C
{69, 4, 17},	// D
{90, 4, 13},	// E
{106, 4, 13},	// F
{121, 4, 18},	// G
{143, 4, 17},	// H
{164, 4, 8},	// I
{175, 4, 16},	// J
{195, 4, 18},	// K
{216, 4, 12},	// L
{230, 4, 23},	// M
{6, 34, 18},	// N
{27, 34, 18},	// O

{48, 34, 18},	// P
{68, 34, 18},	// Q
{90, 34, 17},	// R
{110, 34, 18},	// S
{130, 34, 14},	// T
{146, 34, 18},	// U
{166, 34, 19},	// V
{185, 34, 29},	// W
{215, 34, 18},	// X
{234, 34, 18},	// Y
{5, 64, 14},	// Z
{60, 152, 7},	// [
{106, 151, 13},	// '\'
{83, 152, 7},	// ]
{128, 122, 17},	// ^
{4, 152, 21},	// _

{134, 181, 5},	// '
{5, 4, 18},		// A
{27, 4, 18},	// B
{48, 4, 18},	// C
{69, 4, 17},	// D
{90, 4, 13},	// E
{106, 4, 13},	// F
{121, 4, 18},	// G
{143, 4, 17},	// H
{164, 4, 8},	// I
{175, 4, 16},	// J
{195, 4, 18},	// K
{216, 4, 12},	// L
{230, 4, 23},	// M
{6, 34, 18},	// N
{27, 34, 18},	// O

{48, 34, 18},	// P
{68, 34, 18},	// Q
{90, 34, 17},	// R
{110, 34, 18},	// S
{130, 34, 14},	// T
{146, 34, 18},	// U
{166, 34, 19},	// V
{185, 34, 29},	// W
{215, 34, 18},	// X
{234, 34, 18},	// Y
{5, 64, 14},	// Z
{153, 152, 13},	// {
{11, 181, 5},	// |
{180, 152, 13},	// }
{79, 93, 17},	// ~
{0, 0, -1}		// DEL
};*/

static int propMapB[26][3] = {
	{11, 12, 33},
	{49, 12, 31},
	{85, 12, 31},
	{120, 12, 30},
	{156, 12, 21},
	{183, 12, 21},
	{207, 12, 32},

	{13, 55, 30},
	{49, 55, 13},
	{66, 55, 29},
	{101, 55, 31},
	{135, 55, 21},
	{158, 55, 40},
	{204, 55, 32},

	{12, 97, 31},
	{48, 97, 31},
	{82, 97, 30},
	{118, 97, 30},
	{153, 97, 30},
	{185, 97, 25},
	{213, 97, 30},

	{11, 139, 32},
	{42, 139, 51},
	{93, 139, 32},
	{126, 139, 31},
	{158, 139, 25},
};

#define PROPB_GAP_WIDTH		4
#define PROPB_SPACE_WIDTH	12
#define PROPB_HEIGHT		36

/*
=================
UI_DrawBannerString
=================
*/
static void UI_DrawBannerString2(int x, int y, const char *str, vec4_t color)
{
	const char *s;
	unsigned char ch;	// bk001204 : array subscript
	float ax;
	float ay;
	float aw;
	float ah;
	float frow;
	float fcol;
	float fwidth;
	float fheight;

	// draw the colored text
	trap_R_SetColor(color);

	ax = x * cgs.screenXScale + cgs.screenXBias;
	ay = y * cgs.screenXScale;

	s = str;
	while (*s) {
		ch = *s & 127;
		if (ch == ' ') {
			ax += ((float) PROPB_SPACE_WIDTH + (float) PROPB_GAP_WIDTH) * cgs.screenXScale;
		} else if (ch >= 'A' && ch <= 'Z') {
			ch -= 'A';
			fcol = (float) propMapB[ch][0] / 256.0f;
			frow = (float) propMapB[ch][1] / 256.0f;
			fwidth = (float) propMapB[ch][2] / 256.0f;
			fheight = (float) PROPB_HEIGHT / 256.0f;
			aw = (float) propMapB[ch][2] * cgs.screenXScale;
			ah = (float) PROPB_HEIGHT *cgs.screenXScale;

			trap_R_DrawStretchPic(ax, ay, aw, ah, fcol, frow, fcol + fwidth, frow + fheight,
					      cgs.media.charsetPropB);
			ax += (aw + (float) PROPB_GAP_WIDTH * cgs.screenXScale);
		}
		s++;
	}

	trap_R_SetColor(NULL);
}

void UI_DrawBannerString(int x, int y, const char *str, int style, vec4_t color)
{
	const char *s;
	int ch;
	int width;
	vec4_t drawcolor;

	// find the width of the drawn text
	s = str;
	width = 0;
	while (*s) {
		ch = *s;
		if (ch == ' ') {
			width += PROPB_SPACE_WIDTH;
		} else if (ch >= 'A' && ch <= 'Z') {
			width += propMapB[ch - 'A'][2] + PROPB_GAP_WIDTH;
		}
		s++;
	}
	width -= PROPB_GAP_WIDTH;

	switch (style & UI_FORMATMASK) {
	case UI_CENTER:
		x -= width / 2;
		break;

	case UI_RIGHT:
		x -= width;
		break;

	case UI_LEFT:
	default:
		break;
	}

	if (style & UI_DROPSHADOW) {
		drawcolor[0] = drawcolor[1] = drawcolor[2] = 0;
		drawcolor[3] = color[3];
		UI_DrawBannerString2(x + 2, y + 2, str, drawcolor);
	}

	UI_DrawBannerString2(x, y, str, color);
}

int UI_ProportionalStringWidth(const char *str)
{
	const char *s;
	int ch;
	int charWidth;
	int width;

	s = str;
	width = 0;
	while (*s) {
		ch = *s & 127;
		charWidth = propMap[ch][2];
		if (charWidth != -1) {
			width += charWidth;
			width += PROP_GAP_WIDTH;
		}
		s++;
	}

	width -= PROP_GAP_WIDTH;
	return width;
}

static void UI_DrawProportionalString2(int x, int y, const char *str, vec4_t color, float sizeScale, qhandle_t charset)
{
	const char *s;
	unsigned char ch;	// bk001204 - unsigned
	float ax;
	float ay;
	float aw;
	float ah;
	float frow;
	float fcol;
	float fwidth;
	float fheight;

	// draw the colored text
	trap_R_SetColor(color);

	ax = x * cgs.screenXScale + cgs.screenXBias;
	// Elder: typo in the mod source
	//ay = y * cgs.screenXScale;
	ay = y * cgs.screenYScale;

	s = str;
	while (*s) {
		ch = *s & 127;
		if (ch == ' ') {
			aw = (float) PROP_SPACE_WIDTH *cgs.screenXScale * sizeScale;
		} else if (propMap[ch][2] != -1) {
			fcol = (float) propMap[ch][0] / 512.0f;
			frow = (float) propMap[ch][1] / 256.0f;
			fwidth = (float) propMap[ch][2] / 512.0f;
			fheight = (float) PROP_HEIGHT / 256.0f;
			aw = (float) propMap[ch][2] * cgs.screenXScale * sizeScale;
			ah = (float) PROP_HEIGHT *cgs.screenXScale * sizeScale;

			trap_R_DrawStretchPic(ax, ay, aw, ah, fcol, frow, fcol + fwidth, frow + fheight, charset);
		} else {
			aw = 0;
		}

		ax += (aw + (float) PROP_GAP_WIDTH * cgs.screenXScale * sizeScale);
		s++;
	}

	trap_R_SetColor(NULL);
}

/*
=================
UI_ProportionalSizeScale
=================
*/
float UI_ProportionalSizeScale(int style)
{
	if (style & UI_SMALLFONT) {
		return 0.75;
	}

	return 1.00;
}

/*
=================
UI_DrawProportionalString
=================
*/
void UI_DrawProportionalString(int x, int y, const char *str, int style, vec4_t color)
{
	vec4_t drawcolor;
	int width;
	float sizeScale;

	sizeScale = UI_ProportionalSizeScale(style);

	switch (style & UI_FORMATMASK) {
	case UI_CENTER:
		width = UI_ProportionalStringWidth(str) * sizeScale;
		x -= width / 2;
		break;

	case UI_RIGHT:
		width = UI_ProportionalStringWidth(str) * sizeScale;
		x -= width;
		break;

	case UI_LEFT:
	default:
		break;
	}

	if (style & UI_DROPSHADOW) {
		drawcolor[0] = drawcolor[1] = drawcolor[2] = 0;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x + 2, y + 2, str, drawcolor, sizeScale, cgs.media.charsetProp);
	}

	if (style & UI_INVERSE) {
		drawcolor[0] = color[0] * 0.8;
		drawcolor[1] = color[1] * 0.8;
		drawcolor[2] = color[2] * 0.8;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x, y, str, drawcolor, sizeScale, cgs.media.charsetProp);
		return;
	}

	if (style & UI_PULSE) {
		drawcolor[0] = color[0] * 0.8;
		drawcolor[1] = color[1] * 0.8;
		drawcolor[2] = color[2] * 0.8;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x, y, str, color, sizeScale, cgs.media.charsetProp);

		drawcolor[0] = color[0];
		drawcolor[1] = color[1];
		drawcolor[2] = color[2];
		drawcolor[3] = 0.5 + 0.5 * sin(cg.time / PULSE_DIVISOR);
		UI_DrawProportionalString2(x, y, str, drawcolor, sizeScale, cgs.media.charsetPropGlow);
		return;
	}

	UI_DrawProportionalString2(x, y, str, color, sizeScale, cgs.media.charsetProp);
}
#endif				// Q3STATIC
