#ifndef __ENGINE_H_
#define __ENGINE_H_

class doodad;
class dood;
class level;
#include "tile.h"
#include <SDL2/SDL.h>
#include <list>
#include "sprite.h"
#include <fstream>


class GameEngine {

public:
	GameEngine();
	void gameloop( SDL_Window * window);
	SDL_Rect * get_camera();
	SDL_Surface *& get_screen();
	level * get_level();
	list<Sprite*> * get_batch();
	list<dood> * get_npcs();
	bool transition;
private:
	//game data no one has access to shit
	bool quit;
	SDL_Rect screenBuffer;
	SDL_Surface * screenSurface;
	SDL_Rect camera;
	SDL_Surface * screen;
	SDL_Surface * img;

	dood * inputTarget;
	dood * camfocus;

	dood * hero;

	level * cur;

	list<dood> actors;

	list<Sprite*>  batch;

	//engine functions
	void gamelogic();
	void gamedisplay(SDL_Window * window);
	void gameinput();
	void changeState();
	void set_camera();
	void consoled_display();
	//bool level_in( int areaid ,int * &floor, int * &lamp , int &x, int &y, list<int*> adj);



};


#endif
