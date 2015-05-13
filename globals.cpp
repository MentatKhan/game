#include "globals.h"

const char * MHERO_PATH = "assets/mhero.bmp";
const char * TEST_PALLET = "assets/dirtset.bmp";
//const char * PALLET_PATH = "assets/pallet.txt";
const char * NPC_PATH = "assets/NPC.bmp";
const char * PALLET = "assets/Protopallettown.bmp";
//const char * ROUTE1_PATH =  "assets/route1.txt";

const char * tile_set_path[] =
                        {
                            "assets/Protopallettown.bmp",
                            "assets/Protopallettown.bmp"
                        };


const char * area[]  =
                        { "assets/pallet.txt",
                        "assets/route1.txt"

                        };

//Screen dimension constant
const int SCREEN_WIDTH = 640;
//Screen dimension constant
const int SCREEN_HEIGHT = 480;

//Screen dimension constants in tiles
const int SCREEN_TILE_WIDTH = 15;
//Screen dimention constants in tiles
const int SCREEN_TILE_HIGHT = 11;

//Size of tiles in pixels
const int TILE_SIZE = 16;

//sprite constants
const int DOOD_HIGHT = 20;
//sprite constants
const int DOOD_WIDTH = 16;

//Usefull square
SDL_Rect SQUARE = {0,0,TILE_SIZE,TILE_SIZE};

//dood directional constants
enum  DOOD_DIRECTIONAL_CONSTANTS
{
DOOD_UP = 1,
DOOD_RIGHT,
DOOD_LEFT,
DOOD_DOWN,
DOOD_ACTION,
DOOD_CANCEL,
DOOD_START,
DOOD_SELECT
};

//dood type constant
enum DOODS
{
DOOD_TYPE_HUMAN = 1,
DOOD_TYPE_TEXT,
DOOD_TYPE_MENU
};

//busy animation identifier constatns
enum animations
{
	WALK = 1,
	RUN
};

//Temporary dood animation frame constants
enum DOOD_ANIMATION {
ANI_DOWN_1 = 0,
IDLE_DOWN,
ANI_DOWN_2,
ANI_UP_1,
IDLE_UP,
ANI_UP_2,
ANI_LEFT_1,
IDLE_LEFT,
ANI_LEFT_2,
ANI_RIGHT_1,
IDLE_RIGHT,
ANI_RIGHT_2
};

//Timer constants
int SCREEN_FPS = 30;
int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool loadMedia( char file[], SDL_Surface *& img, SDL_Surface *& screenSurface)
{
	//Loading success flag
	bool success = true;
	img = SDL_LoadBMP( file );
	if( img == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", file, SDL_GetError() );
		success = false;
	}
		else
		{
			//Convert surface to screen format
			img = SDL_ConvertSurface( img, screenSurface->format, NULL );
			//sets color key to white
			SDL_SetColorKey(img,SDL_TRUE, 0xFFFFFF);
			if( img == NULL )
			{
				printf( "Unable to optimize image %s! SDL Error: %s\n", file, SDL_GetError() );
			}
		}
	return success;
}


bool checkCollision( SDL_Rect * a, SDL_Rect *b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
