#define __BOOMSTICK_LOGO__	\
	itemDef {	\
	style WINDOW_STYLE_SHADER	\
	rect 276 288 120 120	\
	anglevectors 9 -81	\
	background UI_ASSETS"/logo"	\
	forecolor 1 1 1 0.2	\
	decoration	\
	visible 1	\
	}

#define __REACTION_VERSION__	\
	itemdef {	\
	group main	\
	subgroup "main_title"	\
	text "REACTION v1.0"	\
	forecolor 0 0 .05 1	\
	style WINDOW_STYLE_EMPTY	\
	textalign ITEM_ALIGN_CENTER	\
	textscale .4	\
	textalignx 120	\
	textaligny 24	\
	rect 108 144 240 36	\
	anglevectors 9 -81	\
	visible 1	\
	autowrapped	\
	decoration	\
	}


//Copyright

#define __REACTION_COPYRIGHT__	\
    itemDef {	\
	group main	\
	alignrect "main_title" ITEM_ALIGN_LEFT 0 20 240 36	\
	style WINDOW_STYLE_EMPTY	\
	textalign ITEM_ALIGN_CENTER	\
	textscale .275	\
	textalignx 120	\
	textaligny 24	\
	forecolor 0 0 0.05 1	\
	text "(c) 2000-2010 Boomstick Studios\n\n\n\n\n"	\
	     "http://www.rq3.com"	\
	autowrapped	\
	visible 1	\
	decoration	\
    }

    itemDef {
	name "copyright,_common_"
	autowrapped
	text "Reaction v1.0\n"
	     "Copyright (c) 2000 - 2010 Boomstick Studios\n"
	     "Quake III Arena (c) 1999 - 2000 id Software Inc."
	//style 0
	textstyle 3
	textscale .15
	rect $evalfloat(UI_MAXX - 256) 444 272 28
	textalign 0
	textaligny 8
	textalignx 8
	//forecolor 1 1 1 .5
	forecolor 1 1 1 .75
	visible 1
	decoration
    }

//--------------------------------------------

	// Common stuff //




	//Logo

    itemDef {
	name "rq3_logo,_common_"
	type 1
	background UI_ASSETS"/rq3-title-logo.tga"
	rect $evalfloat(UI_MAXX - 182) 404 176 77
	//vectors 0.988 -0.156 0.156 0.988
	style WINDOW_STYLE_SHADER
	visible 1
	decoration
    }
  
	// CLIPBOARD //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/clipboard/clipboard.md3"
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	model_origin 34 2.6 -0.25
	model_angles 90 -80.5 270
	visible 1
	decoration
	}
  
	// CELL PHONE //

	//itemdef {
	//name "_common_"
	//type ITEM_TYPE_MODEL
	//asset_model UI_ASSETS"/models/phone/phone.md3"
	//rect 0 0 640 480
	//model_fovx 40
	//model_fovy 30
	//model_origin 20 6 5.5
	////model_origin 20 0 0
	//model_angles 90 214 270
	////model_rotation 0
	//visible 1
	//decoration
	//}

	// CELL PHONE //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/phone2/phone.md3"
	rect -216 -316 640 640
	model_fovx 40
	model_fovy 40
	model_origin 20 0 0
	model_angles 90 34 296
	visible 1
	decoration
	}

	// CLOCK //

	itemdef {
	name "clock,_common_"
	ownerdraw UI_CLOCK
	forecolor 1 1 1 1
	textalign 0
	textaligny 20
	textscale .15
	rect 35 64 48 20
	style WINDOW_STYLE_EMPTY
	//style WINDOW_STYLE_FILLED
	//backcolor 0 0 0 1
	visible 1
	//anglevectors 124 36
	anglevectors 122 33
	decoration
	}


	// KEYS //
/*
	itemDef {
	name "_common_"
	type 1
	background "ui/assets/keys.tga"
	rect 440 300 136 92
	//vectors 0.988 -0.156 0.156 0.988
	style WINDOW_STYLE_SHADER
	visible 1
	decoration
	}
	*/

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/keys/keys.md3"
	rect 372 220 256 192
	model_fovx 40
	model_fovy 30
	model_origin 110 0 0
	model_angles 97 -83 270
	visible 1
	decoration
	}	


	// BAKING SODA !!! //

	itemDef {
	name "_common_"
	type 1
	background "ui/assets/snowblind.tga"
	rect 476 182 256 192
	style WINDOW_STYLE_SHADER
	visible 1
	decoration
	}


	// PEN //
/*
	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/pen/pen.md3"
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	model_origin 27 -6 1
	//model_origin 20 0 0
	model_angles 90 133 270
	//model_rotation 0
	visible 1
	decoration
	}
*/

	// ROLLED DOLLAR BILL //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/dollar/dollar1.md3"
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	model_origin 27 -6 1
	model_angles 65 313 270
	visible 1
	decoration
	}
	

	// GUN //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/gun/gun.md3"
	rect -200 160 640 640
	model_fovx 60
	model_fovy 60
	model_angles 90 156 0
	visible 1
	decoration
	}

	// WRINKLED DOLLAR //
	
	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/dollar/dollar2.md3"
	rect 168 -64 640 480
	model_fovx 40
	model_fovy 30
	model_origin 27 -6 1
	model_angles 120 270 270
	visible 1
	decoration
	}

	// BOTTLE //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/bottle/bottle.md3"
	rect 236 -80 640 640
	model_fovx 40
	model_fovy 40
	model_origin 50 0 12
	model_angles 292 198 97
	//model_angles 278 198 97
	visible 1
	decoration
	}

	// WRINKLED DOLLAR 2 //
	
	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/dollar/dollar2.md3"
	rect 144 -40 640 480
	model_fovx 40
	model_fovy 30
	//style WINDOW_STYLE_FILLED
	//backcolor 0 0 0 1
	model_origin 27 -6 1
	model_angles 106 80 270
	visible 1
	decoration
	}
	

//--------------------------------------------
