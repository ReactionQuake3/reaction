////////////////////////////////////
//
// TAB-RELATED MACROS
//
//


#define ACTIVE_TAB_PROPS\
	forecolor Tab_Color1	\
	textalign 0	\
	textalignx 4	\
	textaligny 12	\
	textscale 0.2	\
	style WINDOW_STYLE_EMPTY	\
	type ITEM_TYPE_BUTTON	\
	visible 1


#define INACTIVE_TAB_PROPS\
	forecolor Tab_Color2	\
	textalign 0	\
	textalignx 4	\
	textaligny 12	\
	textscale 0.2	\
	style WINDOW_STYLE_EMPTY	\
	type ITEM_TYPE_BUTTON	\
	visible 1	\
	decoration

#define ACTIVATE_TAB(num)	hide "allgroups" ; show "group"#num ; hide "hints" ; setfocus "gr"#num"_ctrl1"

#define ADD_HINT(HINT_NAME, HINT_TEXT, HINT_GROUPS)\
    itemdef {	\
	text HINT_TEXT	\
	name HINT_NAME",allgroups,"HINT_GROUPS",hints,fade_alpha"	\
	autowrapped	\
	forecolor HINT_COLOR 1	\
	textalign ITEM_ALIGN_LEFT	\
	textalignx 6	\
	textaligny 10	\
	textscale .2	\
	alignrect "line" ITEM_ALIGN_LEFT 0 8 $evalint(LINE_WIDTH - 12) 40	\
	style WINDOW_STYLE_EMPTY	\
	visible 0	\
	decoration	\
    }

#define ASSIGN_HINT(HINT_NAME)\
	onFocus { show HINT_NAME ; timeFade HINT_NAME forecolor 5 5 5 1 0 HINT_FADE_TIME }	\
	leaveFocus { timeFade HINT_NAME forecolor 5 5 5 0 0 HINT_FADE_TIME }

#define OPTION_BELOW(ITEM_NAME)\
	alignrect ITEM_NAME ITEM_ALIGN_LEFT 0 VSPACE 112 VSIZE

#define BEGIN_SIMPLE_OPTION(ITEM_NR, ITEM_GROUP)\
    itemdef {	\
	name "allgroups,group"#ITEM_GROUP",gr"#ITEM_GROUP"_ctrl"#ITEM_NR",fade_alpha"
	

#define BEGIN_OPTION(ITEM_TEXT, ITEM_CVAR, ITEM_TYPE, ITEM_NR, ITEM_GROUP)\
	BEGIN_SIMPLE_OPTION(ITEM_NR, ITEM_GROUP)\
	type ITEM_TYPE	\
	text ITEM_TEXT":"	\
	cvar ITEM_CVAR

#define BEGIN_SLIDER(ITEM_TEXT, ITEM_CVAR, ITEM_CVAR_DEFAULT, ITEM_CVAR_MIN, ITEM_CVAR_MAX, ITEM_NR, ITEM_GROUP)\
	BEGIN_SIMPLE_OPTION(ITEM_NR, ITEM_GROUP)\
	type ITEM_TYPE_SLIDER	\
	text ITEM_TEXT":"	\
	cvarfloat ITEM_CVAR ITEM_CVAR_DEFAULT ITEM_CVAR_MIN ITEM_CVAR_MAX

#define END_OPTION\
	textalign ITEM_ALIGN_RIGHT	\
	textalignx 0	\
	textaligny 14	\
	textscale .225	\
	forecolor OPTION_COLOR	\
	visible 1	\
    }


#define ADD_TAB(TAB_TEXT, TAB_SHORTCUT, TAB_INDEX, TAB_OTHER_GROUPS, TAB_ALIGN)\
    itemdef {	\
	cleantext TAB_TEXT	\
	name "alltabs,tab"#TAB_INDEX"_0,fade_alpha,allgroups,group"#TAB_INDEX	\
	INACTIVE_TAB_PROPS	\
	TAB_ALIGN	\
    }	\
    itemdef {	\
	text TAB_TEXT	\
	name "alltabs,tab"#TAB_INDEX",fade_alpha,allgroups,"TAB_OTHER_GROUPS	\
	shortcutKey TAB_SHORTCUT	\
	shortcutKey #TAB_INDEX	\
	ACTIVE_TAB_PROPS	\
	action { ACTIVATE_TAB(TAB_INDEX) }	\
	ASSIGN_HINT("hint_tab"#TAB_INDEX)	\
	TAB_ALIGN	\
    }


#define ADD_TITLE_ICON(ASSET, GROUP)\
    itemdef {	\
	name "icon,allgroups,"GROUP	\
	background ASSET	\
	forecolor 1 1 1 ICON_ALPHA	\
	alignrect "line" ITEM_ALIGN_RIGHT 0 -36 32 32	\
	style WINDOW_STYLE_SHADER	\
	visible 1	\
	decoration	\
	}


