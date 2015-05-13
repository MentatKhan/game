#ifndef __DOODAD_H_
#define __DOODAD_H_

#include <SDL2/SDL.h>
#include "globals.h"

class doodad {

public:
	doodad();
	void show( SDL_Rect camera, SDL_Surface *& area);
	void show();



protected:
	int x,y;
	//Sprite body;
	//Sprite head;

};



#endif
