/*
===========================================
	SCROLLING CREDITS CODE
	Author: Iain McGinniss
	Company: AZ Development Team
	
	Produced for Code 3 Arena, feel free
	to use this code in your own projects
	just please remember to give credit
	to AZ Development team for this.
	That should be easy now with this
	new credits system!
===========================================

Elder's modifications
-Letterbox simulation
-Fixed width string drawing
-Movie style "character -- actor" layout
-Configurable fade-to-color sequence
*/

// INCLUDE FILES
#include "ui_local.h"

// CONSTANT DEFINITIONS

#define SCROLLSPEED	2.00 // The scrolling speed in pixels per second.
						  // modify as appropriate for our credits

#define BACKGROUND_SHADER
// uncomment this to use a background shader, otherwise a solid color
// defined in the vec4_t "color_background" is filled to the screen

//Elder: added to choose drawFixed
#define PROPWIDTH	0
#define FIXEDWIDTH	1

#define RIGHT_JUSTIFY_POSITION	310
#define LEFT_JUSTIFY_POSITION	330

//Elder: fader code parameters - plus nicer to access vec4_t with COLOR_*
#define FADE_START_TIME		4000
#define FADE_DURATION		10000
#define COLOR_R 0
#define COLOR_G 1
#define COLOR_B 2
#define COLOR_A 3

// STRUCTURES

typedef struct {
	menuframework_s	menu;
} creditsmenu_t;

static creditsmenu_t	s_credits;

int starttime = 0; // game time at which credits are started
float mvolume; // records the original music volume level, as we will
               // modify it for the credits

//Elder: fader variables
static float fade = 0.00;
//Elder: Fade color - leave alpha component at 0.00
vec4_t color_fader				= {0.00, 0.00, 0.00, 0.00};

vec4_t color_background	        = {0.00, 0.00, 0.00, 1.00};
// these are just example colours that are used in credits[] 
vec4_t color_headertext			= {0.80, 0.00, 0.00, 1.00};
vec4_t color_maintext			= {1.00, 1.00, 1.00, 1.00};

// definition of the background shader pointer
qhandle_t	BackgroundShader; 

/*
Constants to be used for the "style" field of the cr_line credits[] structure...
UI_LEFT - Align to the left of the screen
UI_CENTER - Align to the center
UI_RIGHT - Align to the right of the screen
UI_SMALLFONT - Small font
UI_BIGFONT - Big font
UI_GIANTFONT - Giant font
UI_DROPSHADOW - A drop shadow is created behind the text
UI_BLINK - The text blinks
UI_PULSE - The text pulses
*/

typedef struct
{
	char *string;
	int style;
	vec4_t *colour;
	//Elder: added
	int drawFixed;
} cr_line;

cr_line credits[] = { // edit this as necessary for your credits

{ "CAST", UI_CENTER|UI_BIGFONT, &color_headertext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "GRUNT", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "CYRUS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "KGB", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "M LOWREY", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "MASON", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "MR. TEE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "NUT", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "PSYCHO", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "ROBBER", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SWAT", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

{ "REACTION QUAKE 3 TEAM", UI_CENTER|UI_BIGFONT, &color_headertext, FIXEDWIDTH },

// Programming
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "PROGRAMMING", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "MALCOLM BECHARD (TSUNAMI)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SCOTT BROOKS (BLAZE)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "VICTOR CHOW (ELDER_MMHS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Additional programming -- snippets
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL PROGRAMMING", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "MICHAEL BRUCE (AGTORANGE)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "DAN CHIN (LT. HAWKINS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "MIKE CONNOR (HOMER)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Artwork - models, textures, whatever
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ART", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "LINH NGUYEN (SONIC128)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "IAN MCEACHERN (FROST)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "BRIAN MILLS (BIRDMAN)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "MARK POTNICK (CLOUD)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "RYAN VANCE (BRAGOBLIN)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Additional artwork - a few extra things
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL ART", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "VICTOR CHOW (ELDER_MMHS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "TOMI ISOAHO (T.T.I.)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SHAY MCCARTY (SHAYMON)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "KYLE VANMEURS (R0OK)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Mappers
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "LEVEL DESIGN", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "DAVID COSTELLO (SZE)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "ANDREI DREXLER (MAKRO)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "TOMI ISOAHO (T.T.I.)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SHAY MCCARTY (SHAYMON)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "DAVID PIKE (CENTURION)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "KELLY RUSH (HEXYDES)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "JESSE SMITH (SPYDER)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "WALTER SOMOL (JOHNNY_ROCKET)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Extra mappers/strictly ports
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL LEVEL DESIGN", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "GREGORY SIMMONS (SMOKE)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "JASON IRBY (IRBY)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Sound guys
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "SOUND DESIGN", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "ERWIN PEIL (SPECOPS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Organization -- rare :)
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ORGANIZATION", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "ERWIN PEIL (SPECOPS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Additional organization -- past peeps
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL ORGANIZATION", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "LUCY", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Website
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "WEBSITE DESIGN", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "VICTOR CHOW (ELDER_MMHS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "RICHARD WATT (C00T)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Beta Testers
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "TESTERS AND ADVISORS", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "BLACK MONK", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "FICTION", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SETH CHABOT (WOOK!EBOY)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "STEVE EWALD (PSYCHOTAKES)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "LUKE PAUL (ALICE)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// TBC
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "..TO BE FINISHED..", UI_CENTER|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

{ "REACTION QUAKE 3 CONTRIBUTIONS", UI_CENTER|UI_BIGFONT, &color_headertext, FIXEDWIDTH },

// Additional artwork -- handcannon, hands
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL ARTWORK", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "DWAYNE DOUGLASS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Additional testers -- Elder's test subjects ;)
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ADDITIONAL TESTING", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "WINSTON CHOW", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "STEPHEN LOOI (DUD)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Music Contributions
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "REACTION QUAKE 3 TITLE SCORE", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "JESPER KYD", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

{ "THE REACTION QUAKE 3 TEAM THANKS", UI_CENTER|UI_BIGFONT, &color_headertext, FIXEDWIDTH },

{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "A-TEAM REPRESENTATIVE", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "DWAYNE DOUGLASS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Art resources/etc.
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ART RESOURCES", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "MASTABA SOLUTIONS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "POLYCOUNT", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "QWORKSHOP3", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SHADERLAB", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Coding help/ideas/snippets
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "CODING RESOURCES", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "CODE3ARENA", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "IAIN MCGINNISS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "INOLEN", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "JUZ'S SLIPGATE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "QUAKE3WORLD FORUMS (MOD PROGRAMMING)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "WANG (ATF)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Fex for the public board
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "PRE-RELEASE MESSAGEBOARD GOD", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "THE GREAT FEX", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Groups?
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "GROUPS", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "ABOVE INTELLIGENCE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "ALL THE LITTLE PEOPLE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "FAMILY AND FRIENDS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "FEAR.NET FREQUENTERS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "THE A-TEAM (AQ2 DEVELOPERS)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "THE GRAMMAR RANGERS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Commodities -- food, drugs, you name it
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "COMMODITIES", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "CAFFEINE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "CHEX MIX", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "DR. PEPPER", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "HOME-COOKED MEALS (MM, MM, MMM!)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "HOT POCKETS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "MOUNTAIN DEW", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "PEPSI", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "VARIOUS PIZZA PLACES", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "WACOM TABLETS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Mapping help
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "MAPPING RESOURCES", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "QERADIANT.COM", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "GAMEDESIGN.NET", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "QUAKE3WORLD FORUMS (LEVEL DESIGN)", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// The great webhosts
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "WEB HOSTS", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "TELEFRAGGED AND AFFILIATES", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "FILEPLANET AND AFFILIATES", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },

// Fan sites?


{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

// This point on: id credits -- try to match up with the latest PR
{ "id SOFTWARE", UI_CENTER|UI_BIGFONT, &color_headertext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "PROGRAMMERS", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "JOHN CARMACK", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "ROBERT A. DUFFY", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "JIM DOSE'", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "ART", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "ADRIAN CARMACK", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "KEVIN CLOUD", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "KENNETH SCOTT", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "SENECA MENARD", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "FRED NILSSON", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "GAME DESIGNER", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "GRAEME DEVINE", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "LEVEL DESIGN", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "TIM WILLITS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "CHRISTIAN ANTKOW", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "PAUL JAQUAYS", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "CEO", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "TODD HOLLENSHEAD", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "DIRECTOR OF BUSINESS DEVELOPMENT", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "MARTY STRATTON", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "BIZ ASSIST AND ID MOM", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "DONNA JACKSON", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "DEVELOPMENT ASSISTANCE", UI_RIGHT|UI_SMALLFONT, &color_headertext, FIXEDWIDTH },
{ "ERIC WEBB", UI_LEFT|UI_SMALLFONT, &color_maintext, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

// TODO: make something better
{ "THIS HAS BEEN A REACTION QUAKE 3 TEAM PRODUCTION Copyright 2000 - 2001", UI_CENTER|UI_SMALLFONT, &color_blue, FIXEDWIDTH },

  {NULL}
};

/*
=================
UI_CreditMenu_Key
=================
*/
static sfxHandle_t UI_CreditMenu_Key( int key ) {
	if( key & K_CHAR_FLAG ) {
		return 0;
	}

	// pressing the escape key or clicking the mouse will exit
	// we also reset the music volume to the user's original
	// choice here,  by setting s_musicvolume to the stored var
	
	//Elder: doesn't appear to restore music volume
	//trap_Cmd_ExecuteText( EXEC_APPEND, va("s_musicvolume %f;quit\n", mvolume));
	//trap_Cvar_SetValue( "s_musicvolume", mvolume);
	//trap_S_StopBackgroundTrack();
	trap_Cmd_ExecuteText( EXEC_APPEND, va("s_musicvolume %f\n", mvolume));
	trap_Cmd_ExecuteText( EXEC_APPEND, "quit\n");
	return 0;
}

/*
=================
ScrollingCredits_Draw
This is the main drawing function for the credits.
Most of the code is self-explanatory.
=================
*/
static void ScrollingCredits_Draw(void) {
	int x = 320, y, n, ysize = 0;

  	// ysize is used to determine the entire length 
  	// of the credits in pixels. 
  	// We can then use this in further calculations
  	if(!ysize) { 
  	// ysize not calculated, so calculate it dammit!
        for(n = 0; n <= sizeof(credits) - 1; n++) {
        	//Elder: don't add right-justified stuff to height
        	if (!(credits[n].style & UI_RIGHT)) {
          		// fixed width font
        	  	if(credits[n].drawFixed) {
    	    	  	ysize += SMALLCHAR_HEIGHT;
          		}
          		// it is a small character
          		else if(credits[n].style & UI_SMALLFONT) {
            		// add small character height
            		ysize += PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;
          		}  
          		// it is a big character
          		else if(credits[n].style & UI_BIGFONT) {
            		// add big character size
            		ysize += PROP_HEIGHT;
          		}
          		// it is a huge character
          		else if(credits[n].style & UI_GIANTFONT) {
            		// add giant character size.
            		ysize += PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE); 
          		}
          	}
        }
	}

// first, fill the background with the specified colour/shader
// we are drawing a shader
#ifdef BACKGROUND_SHADER
	UI_DrawHandlePic(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackgroundShader);
  	//Elder: added and then removed for fader
  	//UI_FillRect( 0, 0, 640, 480, color_deepdim );
#else
	// we are just filling a color
	UI_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_background);
#endif
	//Elder: my simple fader code - vec4_t doesn't like var parameters
	//so we'll have to access the alpha channel once it's initialized 
  	if ( (uis.realtime - starttime) >= FADE_START_TIME ) {
		if (fade < 1.00) {
			fade += (1.00 / FADE_DURATION) * 10;
		}
		//safety clamp
		else {
			fade = 1.00;
		}
		color_fader[COLOR_A] = fade;
		UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_fader );
  	}
	
  	// let's draw the stuff
  	// set initial y location
  	y = 480 - SCROLLSPEED * (float)(uis.realtime - starttime) / 100;
  
  	for(n = 0; n <= sizeof(credits) - 1; n++) {
    	// this NULL string marks the end of the credits struct
    	if(credits[n].string == NULL) {
      		// credits sequence is completely off screen
      		if(y < -16) { 
        		trap_Cmd_ExecuteText( EXEC_APPEND, va("s_musicvolume %f; quit\n", mvolume));
        	break; 
        	// end of credits
      		}
      	break;
    	}
		
    	if( strlen(credits[n].string) == 1) // spacer string, no need to draw
			continue;

    	// if the line is within the visible range of the screen
        if( y > -(PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE))) {
          	//Elder: added to support fixed width display and movie-style alignment
    	  	if ( credits[n].drawFixed ) {
    	  		if (credits[n].style & UI_RIGHT) {
    				UI_DrawString(RIGHT_JUSTIFY_POSITION, y, credits[n].string, credits[n].style, *credits[n].colour );
    			}
    			else if (credits[n].style & UI_CENTER) {
    				UI_DrawString(x, y, credits[n].string, credits[n].style, *credits[n].colour );
    			}
    			else {
    				UI_DrawString(LEFT_JUSTIFY_POSITION, y, credits[n].string, credits[n].style, *credits[n].colour );
    			}
    	  	}
    	  	else {
          		UI_DrawProportionalString(x, y, credits[n].string, 
                                    credits[n].style, *credits[n].colour );
    		}
    	}
    	
        // re-adjust y for next line
    	//Elder: right-justified stuff doesn't bump up the line
    	if (!(credits[n].style & UI_RIGHT)) {
        	//Elder: added for fixed width
        	if (credits[n].drawFixed) {
    	    	y += SMALLCHAR_HEIGHT;
    	    }
    	    else if(credits[n].style & UI_SMALLFONT) {
          		y += PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;
        	}
        	else if(credits[n].style & UI_BIGFONT) {
    	      	y += PROP_HEIGHT;
    	    }
    	    else if(credits[n].style & UI_GIANTFONT) {
         		y += PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE);
        	}
        }
    
    	// if y is off the screen, break out of loop
        if (y > 480)
        	break;
	}
	
    //Elder: "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	//Elder: debug information for fader
	//UI_DrawString( 635, 464, va( "Time index: %i", uis.realtime - starttime), UI_RIGHT|UI_SMALLFONT, color_white);
	//UI_DrawString (0, 464, va("Fade alpha: %f", fade), UI_SMALLFONT, color_white);
}

/*
===============
UI_CreditMenu
===============
*/
void UI_CreditMenu( void ) {
	memset( &s_credits, 0 ,sizeof(s_credits) );

	s_credits.menu.draw = ScrollingCredits_Draw;
	s_credits.menu.key = UI_CreditMenu_Key;
	s_credits.menu.fullscreen = qtrue;
	UI_PushMenu ( &s_credits.menu );

	starttime = uis.realtime; // record start time for credits to scroll properly
	mvolume = trap_Cvar_VariableValue( "s_musicvolume" );
	if(mvolume < 0.5)
		trap_Cmd_ExecuteText( EXEC_APPEND, "s_musicvolume 0.5\n" );
	
	//void trap_S_StopBackgroundTrack( void )
	//void trap_S_StartBackgroundTrack( const char *intro, const char *loop) {
	//trap_S_StartBackgroundTrack( "music/win", "music/win");
	
	trap_Cmd_ExecuteText( EXEC_APPEND, "music music/win music/win\n" );

	// load the background shader
#ifdef BACKGROUND_SHADER
	//Elder: changed to rq3 fire
	BackgroundShader = trap_R_RegisterShaderNoMip("rq3-menuback");	
#endif
}
