#ifndef __DOOD_H_
#define __DOOD_H_

class GameEngine;
#include <SDL2/SDL.h>
class tile;
#include "sprite.h"
#include "globals.h"
#include "tile.h"

class dood
{
public:
	dood(int,const char*,int,int,GameEngine*);
	void update( );
	void set_move( int direction);
	void portal();
	void change_face();
	void show();
	void animate();
	bool check_front();
	void reserve_next();
	void free_prev();
	SDL_Rect getpos();

private:
	//
    int x,y;
	Sprite body;
	Sprite head;

	void walkframe();
	//rect used for interacting and next space collision
	GameEngine * engine;

    char ** speaking;


	int uframe, dframe, lframe, rframe;
	int frame;

	//key'd direction
	int keydir;
	int face;
	//
	int busy;
	int walkcount;
	int runcount;


};




#endif
