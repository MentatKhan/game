#ifndef __TILE_H_
#define __TILE_H_

class dood;
#include "includes.h"
class GameEngine;
struct Sprite;
#include <iostream>
#include <vector>

#include "pugixml.hpp"

struct tile
{
  
  int tile_type;
  bool solid;
  int top_type;
  bool occupied;
  bool portal;
  //int world;
  coord out;
  int height;
  dood * tenent;
  Sprite * Tile_Sprite;
  
};

struct tilesrc
{
  SDL_Surface* source;
  int first;
  
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
	//int n,e,s,w;

protected:
	vector<SDL_Surface*> tilesets;
	vector<tile> prototile;
	tile ** bottom;
	tile ** mid;
	tile ** top;
	Sprite ** misc;
	
	tile ** mainmap;
	Sprite *** spritemap;
	int levelx;
	int levely;
	SDL_Surface * tileSet;
	list<Sprite> tilemap;
	GameEngine * engine;

	void create_tilesets( pugi::xml_node spider);
	tile ** tilesetup( int x ,int y,  int * mapdata, int * lampdata );
	Sprite *** spritesetup( int x ,int y, tile ** mainmap);
	bool level_in(int areaid ,int * &floor, int * &lamp, int &x , int &y );
	void LoadLevel( char* xmlfile);
	tile **layer_set (  pugi::xml_node node, int width, int height);
	tile tile_helper(SDL_Surface * mysurface, int tilesize , int tilenum);
};


#endif
