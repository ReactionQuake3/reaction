//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log: ui_shared.h,v $
// Revision 1.22  2006/04/14 18:02:06  makro
// no message
//
// Revision 1.21  2005/09/07 20:24:33  makro
// Vector support for most item types
//
// Revision 1.20  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.19  2003/04/06 21:46:56  makro
// no message
//
// Revision 1.18  2003/04/06 18:31:22  makro
// SSG crosshairs
//
// Revision 1.17  2003/03/31 00:23:18  makro
// Replacements and stuff
//
// Revision 1.16  2003/02/26 18:22:05  makro
// Added an option to change crosshair size in assetGlobalDef's
//
// Revision 1.15  2003/02/13 21:19:51  makro
// no message
//
// Revision 1.14  2002/06/22 19:20:57  makro
// Changed number of custom SSG crosshairs to 6
//
// Revision 1.13  2002/06/16 20:06:15  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.12  2002/06/12 11:15:31  makro
// Support for changing the SSG crosshair. Some other stuff
//
// Revision 1.11  2002/04/11 20:57:19  makro
// Tweaked onShow script handling; added onFirstShow script
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
#ifndef __UI_SHARED_H
#define __UI_SHARED_H

#include "../qcommon/q_shared.h"
#include "../cgame/tr_types.h"
#include "keycodes.h"

#include "menudef.h"

#define MAX_MENUNAME 32
#define MAX_ITEMTEXT 64
#define MAX_ITEMACTION 64
#define MAX_MENUDEFFILE 4096
#define MAX_MENUFILE 32768
#define MAX_MENUS 64
//Makro - changed max item count from 96 to 100
//Makro - changed to 192
#define MAX_MENUITEMS 192
#define MAX_COLOR_RANGES 10
#define MAX_OPEN_MENUS 32

#define WINDOW_MOUSEOVER			0x00000001	// mouse is over it, non exclusive
#define WINDOW_HASFOCUS				0x00000002	// has cursor focus, exclusive
#define WINDOW_VISIBLE				0x00000004	// is visible
#define WINDOW_GREY					0x00000008	// is visible but grey ( non-active )
#define WINDOW_DECORATION			0x00000010	// for decoration only, no mouse, keyboard, etc..
#define WINDOW_FADINGOUT			0x00000020	// fading out, non-active
#define WINDOW_FADINGIN				0x00000040	// fading in
#define WINDOW_MOUSEOVERTEXT		0x00000080	// mouse is over it, non exclusive
#define WINDOW_INTRANSITION			0x00000100	// window is in transition
#define WINDOW_FORECOLORSET			0x00000200	// forecolor was explicitly set ( used to color alpha images or not )
#define WINDOW_HORIZONTAL			0x00000400	// for list boxes and sliders, vertical is default this is set of horizontal
#define WINDOW_LB_LEFTARROW			0x00000800	// mouse is over left/up arrow
#define WINDOW_LB_RIGHTARROW		0x00001000	// mouse is over right/down arrow
#define WINDOW_LB_THUMB				0x00002000	// mouse is over thumb
#define WINDOW_LB_PGUP				0x00004000	// mouse is over page up
#define WINDOW_LB_PGDN				0x00008000	// mouse is over page down
#define WINDOW_ORBITING				0x00010000	// item is in orbit
#define WINDOW_OOB_CLICK			0x00020000	// close on out of bounds click
#define WINDOW_WRAPPED				0x00040000	// manually wrap text
#define WINDOW_AUTOWRAPPED			0x00080000	// auto wrap text
#define WINDOW_FORCED				0x00100000	// forced open
#define WINDOW_POPUP				0x00200000	// popup
#define WINDOW_BACKCOLORSET			0x00400000	// backcolor was explicitly set
#define WINDOW_TIMEDVISIBLE			0x00800000	// visibility timing ( NOT implemented )
//Makro - ugliest hack ever... by far
#define WINDOW_RENDERPOINT			0x01000000
//Makro - forced text color
#define WINDOW_FORCE_TEXT_COLOR		0x02000000
//Makro - randomizes texture co-ordinates (useful for simulating screen static)
#define WINDOW_RANDOM_TCGEN			0x04000000
//Makro - parent is moved around when this item is clicked
#define WINDOW_MENU_ANCHOR			0x08000000
//Makro - window is fullscreen
#define WINDOW_FULLSCREEN			0x10000000

// CGAME cursor type bits
#define CURSOR_NONE					0x00000001
#define CURSOR_ARROW				0x00000002
#define CURSOR_SIZER				0x00000004

#ifdef CGAME
#define STRING_POOL_SIZE 128*1024
#else
#define STRING_POOL_SIZE 384*1024
#endif
#define MAX_STRING_HANDLES 4096

#define MAX_SCRIPT_ARGS 12
#define MAX_EDITFIELD 256

#define ART_FX_BASE			"menu/art/fx_base"
#define ART_FX_BLUE			"menu/art/fx_blue"
#define ART_FX_CYAN			"menu/art/fx_cyan"
#define ART_FX_GREEN		"menu/art/fx_grn"
#define ART_FX_RED			"menu/art/fx_red"
#define ART_FX_TEAL			"menu/art/fx_teal"
#define ART_FX_WHITE		"menu/art/fx_white"
#define ART_FX_YELLOW		"menu/art/fx_yel"

//Makro - removed "ui/assets" from these defines
#define ASSET_GRADIENTBAR				"gradientbar2.tga"
#define ASSET_SCROLLBAR_V				"scrollbar_vert.tga"
//Makro - horizontal scrollbar
#define ASSET_SCROLLBAR_H				"scrollbar_horz.tga"
#define ASSET_SCROLLBAR_ARROWDOWN		"scrollbar_arrow_dwn_a.tga"
#define ASSET_SCROLLBAR_ARROWUP			"scrollbar_arrow_up_a.tga"
#define ASSET_SCROLLBAR_ARROWLEFT		"scrollbar_arrow_left_a.tga"
#define ASSET_SCROLLBAR_ARROWRIGHT		"scrollbar_arrow_right_a.tga"
//Makro - displayed when clicked
#define ASSET_SCROLLBAR_ARROWDOWN2		"scrollbar_arrow_dwn_b.tga"
#define ASSET_SCROLLBAR_ARROWUP2		"scrollbar_arrow_up_b.tga"
#define ASSET_SCROLLBAR_ARROWLEFT2		"scrollbar_arrow_left_b.tga"
#define ASSET_SCROLLBAR_ARROWRIGHT2		"scrollbar_arrow_right_b.tga"
#define ASSET_SCROLL_THUMB				"scrollbar_thumb.tga"
#define ASSET_SLIDER_BAR0				"slider2_0.tga"
#define ASSET_SLIDER_BAR1				"slider2_1.tga"
#define ASSET_SLIDER_THUMB				"sliderbutt_1.tga"
#define SCROLLBAR_SIZE 16.0
#define SLIDER_WIDTH 96.0
#define SLIDER_HEIGHT 16.0
#define SLIDER_THUMB_WIDTH 12.0
#define SLIDER_THUMB_HEIGHT 20.0
//note - duplicated in bg_public.h
#define	NUM_CROSSHAIRS			10
//Makro - moved to bg_public.h
////Makro - for the SSG crosshair preview
//#define	NUM_SSGCROSSHAIRS		6

typedef struct {
	const char *command;
	const char *args[MAX_SCRIPT_ARGS];
} scriptDef_t;

typedef struct {
	float x;		// horiz position
	float y;		// vert position
	float w;		// width
	float h;		// height;
	qboolean hasVectors;
	float u[2], v[2];
} rectDef_t;

typedef rectDef_t Rectangle;

//Makro - point
typedef struct {
	float x;
	float y;
} pointDef_t;
typedef pointDef_t Point;

typedef enum
{
	BACKCOLOR,
	FORECOLOR,
	BORDERCOLOR
} colorType_t;

//Makro - for the new fading method
typedef struct {
	vec4_t color1;
	vec4_t color2;
	qboolean active;
	colorType_t colorType;
	int startTime, endTime;
} timeFade_t;

#define MAX_SHORTCUT_KEYS 8

//-----------------------------------------------


// FIXME: do something to separate text vs window stuff
typedef struct {
	Rectangle rect;		// client coord rectangle
	Rectangle rectClient;	// screen coord rectangle
	const char *name;	//
	//Makro - adding support for shortcut keys
	//const char *shortcutKey;
	int shortcutKey[MAX_SHORTCUT_KEYS];
	//Makro - drop shadow effect
	int shadowStyle;
	const char *group;	// if it belongs to a group
	//Makro - added
	const char *subgroup;	// if it belongs to a subgroup
	const char *cinematicName;	// cinematic name
	int cinematic;		// cinematic handle
	int style;		//
	int border;		//
	int ownerDraw;		// ownerDraw style
	int ownerDrawFlags;	// show flags for ownerdraw items
	float borderSize;	// 
	int flags;		// visible, focus, mouseover, cursor
	Rectangle rectEffects;	// for various effects
	Rectangle rectEffects2;	// for various effects
	int offsetTime;		// time based value for various effects
	int nextTime;		// time next effect should cycle
	//Makro - for the new fading method
	timeFade_t timeFade;
	vec4_t foreColor;	// text color
	vec4_t backColor;	// border color
	vec4_t borderColor;	// border color
	vec4_t outlineColor;	// border color
	qhandle_t background;	// background asset
} windowDef_t;

typedef windowDef_t Window;

typedef struct {
	vec4_t color;
	float low;
	float high;
} colorRangeDef_t;

// FIXME: combine flags into bitfields to save space
// FIXME: consolidate all of the common stuff in one structure for menus and items
// THINKABOUTME: is there any compelling reason not to have items contain items
// and do away with a menu per say.. major issue is not being able to dynamically allocate 
// and destroy stuff.. Another point to consider is adding an alloc free call for vm's and have 
// the engine just allocate the pool for it based on a cvar
// many of the vars are re-used for different item types, as such they are not always named appropriately
// the benefits of c++ in DOOM will greatly help crap like this
// FIXME: need to put a type ptr that points to specific type info per type
// 
#define MAX_LB_COLUMNS 16

typedef struct columnInfo_s {
	int pos;
	int width;
	int maxChars;
} columnInfo_t;

typedef struct listBoxDef_s {
	int startPos;
	int endPos;
	int drawPadding;
	int cursorPos;
	float elementWidth;
	float elementHeight;
	int elementStyle;
	int numColumns;
	columnInfo_t columnInfo[MAX_LB_COLUMNS];
	const char *doubleClick;
	qboolean notselectable;
} listBoxDef_t;

typedef struct editFieldDef_s {
	float minVal;		//     edit field limits
	float maxVal;		//
	float defVal;		//
	float range;		// 
	int maxChars;		// for edit fields
	int maxPaintChars;	// for edit fields
	int paintOffset;	// 
} editFieldDef_t;

#define MAX_MULTI_CVARS 32

typedef struct multiDef_s {
	const char *cvarList[MAX_MULTI_CVARS];
	const char *cvarStr[MAX_MULTI_CVARS];
	float cvarValue[MAX_MULTI_CVARS];
	int count;
	qboolean strDef;
} multiDef_t;

typedef struct modelDef_s {
	//Makro - adding full rotation
	//int angle;
	vec3_t angles;
	vec3_t origin;
	float fov_x;
	float fov_y;
	int rotationSpeed;
} modelDef_t;

#define CVAR_ENABLE		0x00000001
#define CVAR_DISABLE	0x00000002
#define CVAR_SHOW			0x00000004
#define CVAR_HIDE			0x00000008


//Makro - added for YES/NO items

#define YESNO_TEXT			0
#define YESNO_ICON_LEFT		1
#define YESNO_ICON_RIGHT	2

typedef struct yesnoDef_s
{
	int groupIndex;
	float activeCvarVal;
	char activeCvarStr[128];
	int kind;	//text / icon_left / icon_right
	qboolean strDef;
	qboolean wasActive;
	int lastChangeTime;
} yesnoDef_t;

//


typedef struct itemDef_s {
	Window window;		// common positional, border, style, layout info
	Rectangle textRect;	// rectangle the text ( if any ) consumes
	int type;		// text, button, radiobutton, checkbox, textfield, listbox, combo
	int alignment;		// left center right
	int textalignment;	// ( optional ) alignment for text within rect based on text width
	float textalignx;	// ( optional ) text alignment x coord
	float textaligny;	// ( optional ) text alignment x coord
	float textscale;	// scale percentage from 72pts
	//Makro - fixed height for autowrapped text
	float textHeight;

	int textStyle;		// ( optional ) style, normal and shadowed are it for now
	const char *text;	// display text
	void *parent;		// menu owner
	qhandle_t asset;	// handle to asset
	const char *mouseEnterText;	// mouse enter script
	const char *mouseExitText;	// mouse exit script
	const char *mouseEnter;	// mouse enter script
	const char *mouseExit;	// mouse exit script 
	const char *action;	// select script
	const char *onFocus;	// select script
	const char *leaveFocus;	// select script
	//Makro - action executed when the timer shows/hides this item
	const char *onTimerShow, *onTimerHide;
	const char *cvar;	// associated cvar 
	const char *cvarTest;	// associated cvar for enable actions
	const char *enableCvar;	// enable, disable, show, or hide based on value, this can contain a list
	int cvarFlags;		//     what type of action to take on cvarenables
	sfxHandle_t focusSound;
	int numColors;		// number of color ranges
	colorRangeDef_t colorRanges[MAX_COLOR_RANGES];
	float special;		// used for feeder id's etc.. diff per type
	int cursorPos;		// cursor position in characters
	
	void *typeData;		// type specific data ptr's
	//Makro - color to fade when 
} itemDef_t;

typedef struct {
	Window window;
	const char *font;	// font
	qboolean fullScreen;	// covers entire screen 
	int itemCount;		// number of items;
	int fontIndex;		// 
	int cursorItem;		// which item as the cursor
	int fadeCycle;		//
	float fadeClamp;	//
	float fadeAmount;	//
	const char *onOpen;	// run when the menu is first opened
	const char *onClose;	// run when the menu is closed
	const char *onESC;	// run when the menu is closed
//Makro - executed when all the items in a timed sequence have been shown
	const char *onFinishTimer;
//Makro - extra action to be executed on shown/hidden timer items
	const char *onTimerShow, *onTimerHide;
//Makro - executed when the menu is shown
	const char *onShow;
	const char *onFirstShow;
	//Makro - executed when the user clicks outside the active area
	const char *onOOBClick;
	//Makro - special script to be executed when the menu is opened with "openspecial"
	const char *onOpenSpecial;
	qboolean shown;
	int showCount;
	const char *soundName;	// background loop sound for menu
//Makro - music intro  
	const char *soundIntro;

	vec4_t focusColor;	// focus color for items
	vec4_t disableColor;	// focus color for items
	itemDef_t *items[MAX_MENUITEMS];	// items this menu contains   

	//Makro - timer is on/off
	qboolean timerEnabled;
	int nextTimer, timerInterval, timedItems, timerPos, timerMaxDisplay;
} menuDef_t;

typedef struct {
	const char *fontStr;
	const char *cursorStr;
	const char *gradientStr;
	//Makro - this allows us to have more than one UI dir
	const char *assetsPath;
	fontInfo_t textFont;
	fontInfo_t smallFont;
	fontInfo_t bigFont;
	qhandle_t cursor;
	qhandle_t gradientBar;
	qhandle_t scrollBarArrowUp;
	qhandle_t scrollBarArrowDown;
	qhandle_t scrollBarArrowLeft;
	qhandle_t scrollBarArrowRight;
	//Makro - shown when clicked
	qhandle_t scrollBarArrowUp2;
	qhandle_t scrollBarArrowDown2;
	qhandle_t scrollBarArrowLeft2;
	qhandle_t scrollBarArrowRight2;
	//Makro - two separate backgrounds
	qhandle_t scrollBarH;
	qhandle_t scrollBarV;
	qhandle_t scrollBarThumb;
	qhandle_t buttonMiddle;
	qhandle_t buttonInside;
	qhandle_t solidBox;
	qhandle_t sliderBar0, sliderBar1;
	qhandle_t sliderThumb;
	// Makro - precache this instead of loading it per frame
	qhandle_t defaultLevelshot;
	sfxHandle_t menuEnterSound;
	sfxHandle_t menuExitSound;
	sfxHandle_t menuBuzzSound;
	sfxHandle_t itemFocusSound;
	float fadeClamp;
	int fadeCycle;
	float fadeAmount;
	float shadowX;
	float shadowY;
	vec4_t shadowColor;
	float shadowFadeClamp;
	qboolean fontRegistered;

	// player settings
	qhandle_t fxBasePic;
	qhandle_t fxPic[7];
	qhandle_t crosshairShader[NUM_CROSSHAIRS];
	//Makro - for the SSG crosshair preview
	qhandle_t SSGcrosshairShader;
	//Makro - for drop shadow effects
	qhandle_t dropShadowCorners[4];
	qhandle_t dropShadowRight, dropShadowBottom;
	//Makro - for grouped checkboxes
	qhandle_t checkBox0, checkBox1;

} cachedAssets_t;

typedef struct {
	const char *name;
	void (*handler) (itemDef_t * item, char **args);
} commandDef_t;


//Makro - added for packing bits
#define GETBIT(intvec, pos)			( ( ((intvec)[(pos)>>5]) & (1<<((pos) & 31)) ) != 0 )
#define SETBIT(intvec, pos, bit)	if (bit)\
										(intvec)[(pos)>>5] |= (1 << ((pos) & 31));\
									else\
										(intvec)[(pos)>>5] &= ~(1 << ((pos) & 31))\
										

#define MAX_NUM_GL_EXTENSIONS		128
#define MAX_NUM_SUPPORTED_MODES		256

typedef struct {
	unsigned int width;
	unsigned int height;
} resolution_t;

typedef struct {
	qhandle_t(*registerShaderNoMip) (const char *p);
	void (*setColor) (const vec4_t v);
	void (*drawHandlePic) (float x, float y, float w, float h, qhandle_t asset);
	//Makro - added "adjust"
	void (*drawStretchPic) (float x, float y, float w, float h, float s1, float t1, float s2, float t2,
				qhandle_t hShader, qboolean adjust);
	//Makro - angled pictures
	void (*drawAngledPic) (float x, float y, float w, float h, const float *u, const float *v, const float *color, float s1, float t1, float s2, float t2,
				qhandle_t hShader);
	//Makro - added forceColor and maxwidth
	void (*drawText) (float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit,
			  float maxwidth, int style, qboolean forceColor);
	//Makro - angled text
	void (*drawAngledText) (float x, float y, const float *u, const float *v, float scale, vec4_t color, const char *text, float adjust, int limit,
			  float maxwidth, int style, qboolean forceColor);
	int (*textWidth) (const char *text, float scale, int limit);
	int (*textHeight) (const char *text, float scale, int limit);
	 qhandle_t(*registerModel) (const char *p);
	void (*modelBounds) (qhandle_t model, vec3_t min, vec3_t max);
	void (*fillRect) (float x, float y, float w, float h, const vec4_t color);
	//Makro - added shader parm
	void (*drawRect) (float x, float y, float w, float h, float size, const vec4_t color, qhandle_t shader);
	void (*drawSides) (float x, float y, float w, float h, float size, qhandle_t shader);
	void (*drawAngledRect) (float x, float y, float w, float h, const float *u, const float *v, float size, const float *color, unsigned char type, qhandle_t shader);
	void (*drawTopBottom) (float x, float y, float w, float h, float size, qhandle_t shader);
	void (*clearScene) ( void );
	void (*addRefEntityToScene) (const refEntity_t * re);
	void (*renderScene) (const refdef_t * fd);
	void (*registerFont) (const char *pFontname, int pointSize, fontInfo_t * font);
	//Makro - aded item
	void (*ownerDrawItem) (itemDef_t *item, float x, float y, float w, float h, float text_x, float text_y, int ownerDraw,
			       int ownerDrawFlags, int align, float special, float scale, vec4_t color,
			       qhandle_t shader, int textStyle);
	float (*getValue) (int ownerDraw);
	 qboolean(*ownerDrawVisible) (int flags);
	void (*runScript) (char **p);
	void (*getTeamColor) (vec4_t * color);
	void (*getCVarString) (const char *cvar, char *buffer, int bufsize);
	float (*getCVarValue) (const char *cvar);
	void (*setCVar) (const char *cvar, const char *value);
	void (*drawTextWithCursor) (float x, float y, float scale, vec4_t color, const char *text, int cursorPos,
				    char cursor, int limit, int style);
	//Makro - vector items
	void (*drawAngledTextWithCursor) (float x, float y, const float *u, const float *v, float scale, vec4_t color, const char *text, int cursorPos,
				    char cursor, int limit, int style);
	void (*setOverstrikeMode) (qboolean b);
	 qboolean(*getOverstrikeMode) ( void );
	void (*startLocalSound) (sfxHandle_t sfx, int channelNum);
	 qboolean(*ownerDrawHandleKey) (int ownerDraw, int flags, float *special, int key);
	int (*feederCount) (float feederID);
	const char *(*feederItemText) (float feederID, int index, int column, qhandle_t * handle);
	 qhandle_t(*feederItemImage) (float feederID, int index);
	void (*feederSelection) (float feederID, int index);
	void (*keynumToStringBuf) (int keynum, char *buf, int buflen);
	void (*getBindingBuf) (int keynum, char *buf, int buflen);
	void (*setBinding) (int keynum, const char *binding);
	void (*executeText) (int exec_when, const char *text);
	void (*Error) (int level, const char *error, ...);
	void (*Print) (const char *msg, ...);
	void (*Pause) (qboolean b);
	int (*ownerDrawWidth) (int ownerDraw, float scale);
	 sfxHandle_t(*registerSound) (const char *name, qboolean compressed);
	void (*startBackgroundTrack) (const char *intro, const char *loop);
	void (*stopBackgroundTrack) ( void );
	int (*playCinematic) (const char *name, float x, float y, float w, float h);
	void (*stopCinematic) (int handle);
	void (*drawCinematic) (int handle, float x, float y, float w, float h);
	void (*runCinematicFrame) (int handle);

	float yscale;
	float xscale;
	float bias;
	int realTime;
	int frameTime;
	int cursorx;
	int cursory;
	//Makro - added cursor size
	int cursorSize;
	//Makro - mouse down
	qboolean mouseDown[3];
	int mouseDownPos[2];
	//Makro - last time the cursor was moved
	int mouseMoveTime;

	qboolean debug;

	cachedAssets_t Assets;

	glconfig_t glconfig;
	qhandle_t whiteShader;
	qhandle_t gradientImage;
	qhandle_t cursor;
	//Makro - added; almost useless
	qhandle_t selectShader;
	float FPS;
	//Makro - added
	int smoothFPS;
	//Makro - vector items speed hack
	int pendingPolys;
	//and a z-order hack
	float polyZ;
	refdef_t scene2D;
	//Makro - fade in/out
	float overlayColor[4], overlayColor2[4];
	int overlayFadeStart, overlayFadeEnd;
	//Makro - keep track of key presses
	int keysStatus[1024/(8*sizeof(int))];

	//Makro - gl extensions
	const char *glExtensions[MAX_NUM_GL_EXTENSIONS];
	int numGlExtensions;

	// Makro - total screen extents (which can go outside 0,0-640,480 for wide screens)
	float min[2];
	float max[2];

	// Makro - supported resolutions
	resolution_t supportedMode[MAX_NUM_SUPPORTED_MODES];
	int numSupportedModes;
	int selectedMode;
} displayContextDef_t;

const char *String_Alloc(const char *p);
void String_Init( void );
void String_Report( void );
void Init_Display(displayContextDef_t * dc);
void Display_ExpandMacros(char *buff);
void Menu_Init(menuDef_t * menu);
void Item_Init(itemDef_t * item);
void Menu_PostParse(menuDef_t * menu);
menuDef_t *Menu_GetFocused( void );
void Menu_HandleKey(menuDef_t * menu, int key, qboolean down);
void Menu_HandleMouseMove(menuDef_t * menu, float x, float y);
void Menu_ScrollFeeder(menuDef_t * menu, int feeder, qboolean down);
qboolean Float_Parse(char **p, float *f);
qboolean Color_Parse(char **p, vec4_t * c);
qboolean Int_Parse(char **p, int *i);
qboolean Rect_Parse(char **p, rectDef_t * r);
qboolean String_Parse(char **p, const char **out);
qboolean Script_Parse(char **p, const char **out);
qboolean PC_Float_Parse(int handle, float *f);
qboolean PC_Color_Parse(int handle, vec4_t * c);
qboolean PC_Int_Parse(int handle, int *i);
qboolean PC_Rect_Parse(int handle, rectDef_t * r);
qboolean PC_String_Parse(int handle, const char **out);
qboolean PC_Script_Parse(int handle, const char **out);
int Menu_Count( void );
void Menu_New(int handle);
void Menu_PaintAll( void );
//Makro - added second parameter
menuDef_t *Menus_ActivateByName(const char *p, qboolean special);
void Menu_Reset( void );
qboolean Menus_AnyFullScreenVisible( void );
void Menus_Activate(menuDef_t * menu);
//Makro - select the right player model icon
void UI_RQ3_SelectPlayerIcon(menuDef_t *menu);
//Makro - added
int Text_maxPaintChars(char *text, float scale, float width);

displayContextDef_t *Display_GetContext( void );
void *Display_CaptureItem(int x, int y);
qboolean Display_MouseMove(void *p, int x, int y);
int Display_CursorType(int x, int y);
qboolean Display_KeyBindPending( void );
//Makro - added second parameter
void Menus_OpenByName(const char *p, qboolean special);
menuDef_t *Menus_FindByName(const char *p);
void Menus_ShowByName(const char *p);
void Menus_CloseByName(const char *p);
void Display_HandleKey(int key, qboolean down, int x, int y);
void LerpColor(vec4_t a, vec4_t b, vec4_t c, float t);
void Menus_CloseAll( void );
void Menu_Paint(menuDef_t * menu, qboolean forcePaint);
void Menu_SetFeederSelection(menuDef_t * menu, int feeder, int index, const char *name);
void Display_CacheAll( void );

void *UI_Alloc(int size);
void UI_InitMemory(void);
qboolean UI_OutOfMemory( void );

void Controls_GetConfig(void);
void Controls_SetConfig(qboolean restart);
void Controls_SetDefaults(void);

int trap_PC_AddGlobalDefine(char *define);
int trap_PC_LoadSource(const char *filename);
int trap_PC_FreeSource(int handle);
int trap_PC_ReadToken(int handle, pc_token_t * pc_token);
int trap_PC_SourceFileAndLine(int handle, char *filename, int *line);

//Makro - new rendering stuff
void UI_AddQuadToScene(qhandle_t hShader, const polyVert_t *verts);
void UI_Render2DScene( void );
void Rect_ToInnerCoords(rectDef_t *rect, float x, float y, float *resx, float *resy);

#define UI_POLY_Z_OFFSET -0.00001f
//Makro - for all the lazy people
#define IsBetween(a, min, max) ( (a) >= (min) && (a) <= (max) )
#define PRINT_RECT(r) (r).x, (r).y, (r).w, (r).h

#define RECT_SIDES		1
#define RECT_TOPBOTTOM	2
#define RECT_FULL		3

#endif
