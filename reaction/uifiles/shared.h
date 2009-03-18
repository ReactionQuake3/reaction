//--------------------------------------------

	// Common stuff //




//Copyright

    itemDef {
	name "copyright,_common_"
	autowrapped
	text "Reaction v1.0\n"
	     "Copyright (c) 2000 - 2009 Boomstick Studios\n"
	     "Quake III Arena (c) 1999 - 2000 id Software Inc."
	//style 0
	textstyle 3
	textscale .15
	//rect 0 444 272 28
	rect 384 444 272 28
  textalign 0
	textaligny 8
	textalignx 8
	//forecolor 1 1 1 .5
	forecolor 1 1 1 .75
	visible 1
	decoration
    }

	//Logo

    itemDef {
	name "rq3_logo,_common_"
	type 1
	background UI_ASSETS"/rq3-title-logo.tga"
	//rect 458 404 176 72
	rect 458 404 176 77
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
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	//model_origin 20 6 5.5
	model_origin 20 5 5.5
	//model_angles 90 34 270
	model_angles 90 34 280
	visible 1
	decoration
	}

	// CLOCK //

	itemdef {
	name "clock,_common_"
	ownerdraw UI_CLOCK
	forecolor 1 1 1 1
	textalign 0
	//textalignx 16
	//textaligny 5
	//textalignx 16
	textaligny 20
	textscale .15
	rect 40 66 72 20
	style WINDOW_STYLE_EMPTY
	visible 1
	//anglevectors 124 36
	anglevectors 122 33
	decoration
	}


	// KEYS //

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


	// PEN //

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


/*
	itemdef {
	style WINDOW_STYLE_SHADER
	forecolor .75 .75 .75 1
	background UI_ASSETS"/gun_shadow.tga"
	rect 216 572 360 260
	anglevectors 156 66
	visible 1
	decoration
	}
*/

	// GUN //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/gun/gun.md3"
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	model_origin 16 8 -8.5
	//model_origin 40 8 -8.5
	model_angles 90 156 0
	//model_angles 180 90 0
	//model_rotation 90 0 0
	visible 1
	decoration
	}



	// BOTTLE //

	itemdef {
	name "_common_"
	type ITEM_TYPE_MODEL
	asset_model UI_ASSETS"/models/bottle/bottle.md3"
	rect 0 0 640 480
	model_fovx 40
	model_fovy 30
	model_origin 50 -16 12
	model_angles 278 198 97
	//model_angles 270 198 90
	visible 1
	decoration
	}

//--------------------------------------------
