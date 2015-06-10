#ifndef __TILE_H_
#define __TILE_H_

class dood;
#include "includes.h"
class GameEngine;
struct Sprite;

struct tile
{
  
  int tile_type;
  bool solid;
  int top_type;
  bool occupied;
  bool portal;
  int world;
  coord out;
  int height;
  dood * tenent;
  
};

class level
{
public:
	level(int,GameEngine*);
	void update();
	void show(SDL_Rect & camera, SDL_Surface *& screenSurface);
	void show();
	tile ** get_map();
	int get_x(){return levelx;};
	int get_y(){return levely;};
	int n,e,s,w;

protected:
	tile ** mainmap;
	Sprite *** spritemap;
	int levelx;
	int levely;
	SDL_Surface * tileSet;
	list<Sprite> tilemap;
	GameEngine * engine;
	tile ** tilesetup( int x ,int y,  int * mapdata, int * lampdata );
	Sprite *** spritesetup( int x ,int y, tile ** mainmap);
	bool level_in(int areaid ,int * &floor, int * &lamp, int &x , int &y );


};


#endif
