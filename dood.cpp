#include "dood.h"


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

dood::dood( int type, const char * path ,int myx , int myy, GameEngine * myengine)
{
		SDL_Surface * sheet;

		x= myx;
		y = myy;

        engine = myengine;

        engine->get_level()->get_map()[x][y].occupied = true;

		loadMedia( (char*)path , sheet , engine->get_screen() );

		body.src = sheet;
		head.src = sheet;
		body.srcloc.x=head.srcloc.x = IDLE_DOWN*TILE_SIZE;

		head.camloc = SQUARE;
		head.camloc.h = TILE_SIZE / 4;
		body.camloc = SQUARE;



		uframe = dframe= lframe= rframe = 0;
		frame = -1;

		keydir = 0;
		face = DOOD_DOWN;
		busy = 0;

			body.depth = 2;
	//setting the body's tileset
	//body.src = sheet;
	//sprite source size

	body.srcloc.w = TILE_SIZE;
	body.srcloc.h = TILE_SIZE;
	body.srcloc.y = TILE_SIZE/4;
	body.srcloc.x = 0;


	//sprite destination size
	body.destloc.w = TILE_SIZE;
	body.destloc.h = TILE_SIZE;


	//Head sprite parama
	head.depth = 3;
	//setting the job's tileset
	//sprite source size
	head.srcloc.w = TILE_SIZE;
	head.srcloc.h = TILE_SIZE/4;
	head.srcloc.y = 0;
	head.srcloc.x = 0;
	//sprite destination size
	head.destloc.w = TILE_SIZE;
	head.destloc.h = TILE_SIZE/4;
    //printf( "body dest loc w = %d, h = %d, y =%d, x = %d", body.destloc.w , body.destloc.h , body.destloc.y , body.destloc.x);
    body.srcloc.x=head.srcloc.x = IDLE_DOWN*TILE_SIZE;
}

SDL_Rect dood::getpos()
	{
		SDL_Rect pos = body.destloc;
		pos.x = x*TILE_SIZE+rframe-lframe;
		pos.y = y*TILE_SIZE+dframe-uframe;
		return pos;
	}

void dood::update( )
{
  if(busy)
    switch(busy)
      {
      case WALK:
	walkframe();
	break;
      case RUN:
	break;
      }
  else
    {
      if( engine->get_level()->get_map()[x][y].portal == true)
	{
	  engine -> transition = true;
	}
      if(keydir == DOOD_ACTION)
	{
	  printf("Im at %d,%d\n",x,y);
	}
      if(keydir == DOOD_START)
	{
	  printf("start\n");
	}
      if(keydir == face && !check_front() ) // new input matches current direction
	{
	  walkcount = 0;
	  reserve_next();
	  busy = true;
	}
      else // new input is diffrent
	{
	  //change direction
	  change_face();
	}
    }
}

bool dood::check_front()
{
	switch (face)
			{
			case DOOD_UP:
				return engine->get_level()->get_map()[x][y-1].solid || engine->get_level()->get_map()[x][y-1].occupied;
				break;
			case DOOD_DOWN:
				return engine->get_level()->get_map()[x][y+1].solid || engine->get_level()->get_map()[x][y+1].occupied;
				break;
			case DOOD_LEFT:
				return engine->get_level()->get_map()[x-1][y].solid || engine->get_level()->get_map()[x-1][y].occupied;
				break;
			case DOOD_RIGHT:
				return engine->get_level()->get_map()[x+1][y].solid || engine->get_level()->get_map()[x+1][y].occupied;
				break;
			default:
				return false;
				break;
		}
}

void dood::reserve_next()
{
		switch (face)
			{
			case DOOD_UP:
				engine->get_level()->get_map()[x][y-1].occupied = true;
				break;
			case DOOD_DOWN:
				engine->get_level()->get_map()[x][y+1].occupied = true;
				break;
			case DOOD_LEFT:
				engine->get_level()->get_map()[x-1][y].occupied = true;
				break;
			case DOOD_RIGHT:
				engine->get_level()->get_map()[x+1][y].occupied = true;
				break;
			default:
				break;
		}
}

void dood::free_prev()
{
		switch (face)
			{
			case DOOD_UP:
				engine->get_level()->get_map()[x][y+1].occupied = false;
				break;
			case DOOD_DOWN:
				engine->get_level()->get_map()[x][y-1].occupied = false;
				break;
			case DOOD_LEFT:
				engine->get_level()->get_map()[x+1][y].occupied = false;
				break;
			case DOOD_RIGHT:
				engine->get_level()->get_map()[x-1][y].occupied = false;
				break;
			default:
				break;
		}

}

void dood::change_face( )
{
	switch (keydir)
	{
	case DOOD_UP:
		face = DOOD_UP;
		body.srcloc.x=head.srcloc.x = IDLE_UP*TILE_SIZE;
		break;
	case DOOD_DOWN:
		face = DOOD_DOWN;
		body.srcloc.x=head.srcloc.x = IDLE_DOWN*TILE_SIZE;
		break;
	case DOOD_LEFT:
		face = DOOD_LEFT;
				body.srcloc.x=head.srcloc.x = IDLE_LEFT*TILE_SIZE;
		break;
	case DOOD_RIGHT:
		face = DOOD_RIGHT;
		body.srcloc.x=head.srcloc.x = IDLE_RIGHT*TILE_SIZE;
		break;
	}
	keydir = 0;
	//face = keydir;
	//keydir = 100;
}

void dood::animate()
{//32343
	body.srcloc.x += DOOD_WIDTH*frame;
	head.srcloc.x += DOOD_WIDTH*frame;
}

void dood::walkframe()
{
	if(walkcount % 3 == 0)
	{
		switch (face)
			{
			case DOOD_UP:
				uframe+=4;
				break;
			case DOOD_DOWN:
				dframe+=4;
				break;
			case DOOD_LEFT:
				lframe+=4;
				break;
			case DOOD_RIGHT:
				rframe+=4;
				break;
			default:
				break;
		}

		//animate();

		if(rframe+dframe+lframe+uframe > 16)
		{
			busy = false;
			y += dframe/16 - uframe/16;
			x += rframe/16 - lframe/16;
			free_prev();
			rframe = dframe = lframe = uframe = 0;
			keydir = 0;

		}
	}
	walkcount++;

}

void dood::set_move( int direction)
{

	keydir = direction;
}

void dood::show()
{
	//body sprite parameters

	body.destloc.x = x*TILE_SIZE+rframe-lframe;
	body.destloc.y = y*TILE_SIZE+dframe-uframe;

	////Head sprite parama
	head.destloc.x = x*TILE_SIZE +rframe-lframe;
	head.destloc.y = (y*TILE_SIZE +dframe-uframe) -TILE_SIZE/4;
	//body sprite parameters

	if( checkCollision( &body.destloc , engine->get_camera()) || checkCollision( &head.destloc , engine->get_camera())  )
	{
		head.camloc.x = head.destloc.x - engine->get_camera()->x;
		head.camloc.y = head.destloc.y - engine->get_camera()->y;
		body.camloc.x = body.destloc.x - engine->get_camera()->x;
		body.camloc.y = body.destloc.y - engine->get_camera()->y;
		engine->get_batch()->push_front(&body);
		engine->get_batch()->push_front(&head);
	}

}
