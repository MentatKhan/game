#ifndef __GLOBALS_H_
#define __GLOBALS_H_

#include <stdio.h>
#include <SDL2/SDL.h>

using namespace std;

//Screen dimension constant
extern const int SCREEN_WIDTH;
//Screen dimension constant
extern const int SCREEN_HEIGHT;

//Screen dimension constants in tiles
extern const int SCREEN_TILE_WIDTH;
//Screen dimention constants in tiles
extern const int SCREEN_TILE_HIGHT;

//Size of tiles in pixels
extern const int TILE_SIZE;

//sprite constants
extern const int DOOD_HIGHT;
//sprite constants
extern const int DOOD_WIDTH;

//Usefull square
extern SDL_Rect SQUARE;


enum levelnames
{
    pallet = 0,
    route1,
    viridian,
    route2,
    forrest,
    pewter
};

//Timer constants
extern int SCREEN_FPS;
extern int SCREEN_TICKS_PER_FRAME;
//asset paths
#define areanum 2
extern const char * area[ areanum ];
extern const char * tile_set_path[ areanum ];
extern const char * MHERO_PATH;
extern const char * TEST_PALLET;
extern const char * PALLET_PATH;
extern const char * NPC_PATH;
extern const char * PALLET;
extern const char * ROUTE1_PATH;

bool loadMedia( char file[], SDL_Surface *& img, SDL_Surface *& screenSurface);

bool checkCollision( SDL_Rect *a, SDL_Rect *b );



#endif
