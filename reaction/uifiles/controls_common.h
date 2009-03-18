
#define __CONTROLS_WINDOW_DEF__	\
	focusColor RQ3_MAIN_FOCUSCOLOR	\
	rect 140 80 300 348	\
	anglevectors 5 -85	\
	style WINDOW_STYLE_EMPTY	\
	popup


#define __CONTROLS_PAPER__	\
	itemDef {	\
	menuAnchor	\
	renderpoint	\
	name "paper"	\
	subgroup "fade_alpha"	\
	style WINDOW_STYLE_SHADER	\
	background UI_ASSETS"/paper_1"	\
	forecolor MENUCOLOR_CONTROLS 1	\
	rect 0 -20 320 420	\
	anglevectors 5 -85	\
	visible 1	\
	decoration	\
    }


#define __CONTROLS_TITLE__	\
	itemdef {	\
	renderpoint	\
	name "title"	\
	subgroup "fade_alpha"	\
	text "Controls:"	\
	forecolor .6 .0 .0 1	\
	style WINDOW_STYLE_EMPTY	\
	textalign ITEM_ALIGN_LEFT	\
	textalignx 4	\
	textaligny 24	\
	textscale RQ3_MAIN_TEXTSIZE	\
	alignrect paper ITEM_ALIGN_LEFT 32 40 240 36 	\
	visible 1	\
	autowrapped	\
	decoration	\
    }

#define __CONTROLS_LINE__	\
	itemDef {	\
	name "line"	\
	subgroup "fade_alpha"	\
	style WINDOW_STYLE_FILLED	\
	backcolor .25 .25 .25 LINE_ALPHA	\
	alignrect "title" ITEM_ALIGN_LEFT 0 48 LINE_WIDTH 2	\
	visible 1	\
	decoration	\
	}

#define __CONTROLS_ICON__(ICON_SHADER, ICON_GROUP)	\
	itemdef {	\
	name "icon,allgroups,group"#ICON_GROUP	\
	background ICON_SHADER	\
	forecolor 1 1 1 ICON_ALPHA	\
	alignrect "line" ITEM_ALIGN_RIGHT 0 -36 32 32	\
	style WINDOW_STYLE_SHADER	\
	visible 1	\
	decoration	\
	}

#define BEGIN_HINT(HINT_NAME)\
	itemdef {	\
	name HINT_NAME	\
	autowrapped	\
	group "hints"	\
	subgroup "fade_alpha"	\
	forecolor HINT_COLOR 1	\
	textalign ITEM_ALIGN_LEFT	\
	textalignx 6	\
	textaligny 10	\
	textscale .2	\
	alignrect "line" ITEM_ALIGN_LEFT 0 8 220 40	\
	style WINDOW_STYLE_EMPTY	\
	visible 0	\
	decoration

#define END_HINT\
    }

#define __CONTROLS_HINTS__	\
	BEGIN_HINT(keyBindStatus)	\
		ownerdraw UI_KEYBINDSTATUS	\
	END_HINT	\
	BEGIN_HINT(YesNoMessage)	\
		text "Click to toggle Yes/No"	\
	END_HINT	\
	BEGIN_HINT(SliderMessage)	\
		text "Drag the slider to increase/decrease"	\
	END_HINT

//#define ASSIGN_HINT(HINT_NAME)\
//	onFocus { show HINT_NAME ; timeFade HINT_NAME forecolor 5 5 5 1 0 HINT_FADE_TIME }	\
//	leaveFocus { timeFade HINT_NAME forecolor 5 5 5 0 0 HINT_FADE_TIME }

