#ifndef __SPRITE_H_
#define __SPRITE_H_

struct Sprite
{
        bool draw;
	SDL_Surface * src;
	//May be able to delete
	SDL_Rect  destloc;
	//
	SDL_Rect camloc;
	SDL_Rect  srcloc;
	int depth;
};

#endif // __SPRITE_H_
