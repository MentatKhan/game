#include "engine.h"


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


bool Comparedepth(Sprite*& t1, Sprite*& t2){	return t1->depth < t2->depth?true:false;};

GameEngine::GameEngine()
{

    int * floor;
    int *  lamp;
    list<int*> adj;
    int x,y;

    //if (level_in( pallet , floor, lamp, x , y, adj ))
    //{


	quit = false;

	//Set size of small screen rect
	screenBuffer.x = 0;
	screenBuffer.y = 0;
	screenBuffer.w = SCREEN_TILE_WIDTH*TILE_SIZE;
	screenBuffer.h = SCREEN_TILE_HIGHT*TILE_SIZE;

	//create surface for small screen
	screenSurface = SDL_CreateRGBSurface( 0 ,SCREEN_TILE_WIDTH*TILE_SIZE,SCREEN_TILE_HIGHT*TILE_SIZE,32, 0,0,0,0);

	//create camera
	camera.h = SCREEN_TILE_HIGHT*TILE_SIZE;
	camera.w = SCREEN_TILE_WIDTH*TILE_SIZE;
	camera.x = 0;
	camera.y = 0;

	loadMedia((char*)PALLET, img, screenSurface);



	cur = new (nothrow)level( pallet, this);

	hero =  new (nothrow) dood( 1, MHERO_PATH,12,2, this);

	inputTarget = hero;

	camfocus = hero;

}

/*bool GameEngine::level_in( int areaid ,int * &floor, int * &lamp, int &x , int &y , list<int*> adj )
{
fstream fin;
    fin.open(area[ areaid ]);

    if(fin)
    {
    fin >> x >> y;

    floor = new (nothrow)int[x*y];
    lamp = new (nothrow)int[x*y];

    if(floor == nullptr)
    {
        printf("Floor did not dynamically allocate correctly");
    return false;
    }
    if(lamp == nullptr)
    {
        printf("Lamp did not dynamically allocate correctly");
    return false;
    }

    int temp;
    fin >> temp >> temp>> temp >> temp >> temp >> temp;


    //printf("x is %d, y is %d\n",x,y);
    for(int i = 0; i < x*y; i++)
    {
        if(i%x == 0)
        printf("\n");
        fin >> floor[i];
        printf ( "%d",floor[i]);

    }
    for(int i = 0; i < x*y; i++)
    {
                //if(i%x == 0)
          //  printf("\n");
        fin >> lamp[i];
       // printf ( "%d",lamp[i]);

    }
    fin.close();
    return true;
    }
    return false;

}*/

void GameEngine::changeState()
{
  //fade to black

  //get relevant info

  //delete old level

  //load new level

  //place hero

  
}

SDL_Rect* GameEngine::get_camera()
{
    return &camera;
}

SDL_Surface *& GameEngine::get_screen()
{
    return *&screenSurface;
}

level * GameEngine::get_level()
{
    return cur;
}

list<dood> * GameEngine::get_npcs()
{
    return &actors;

}

list<Sprite*> * GameEngine::get_batch()
{
    return &batch;
}

void GameEngine::gameloop(SDL_Window * window)
{
	screen = SDL_GetWindowSurface( window );

	//Start cap timer
	int timer = SDL_GetTicks();
	int frameTicks;
	while(!quit)
	{
		timer = SDL_GetTicks();

		gameinput();
		gamelogic();

		if(transition)
		  {
		    changeState();
		  }
		gamedisplay( window );


		
		//bufferflush
		fflush(stdout);
		
		frameTicks = SDL_GetTicks() - timer;
		if( frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );

		}
	}

}

void GameEngine::gamelogic()
{
	list<dood>::iterator it = actors.begin();

	hero -> update();

	while (it != actors.end())
	{
		it->update();
	it++;
	}
	cur -> update();

}

void GameEngine::gameinput()
{
	//npc ->set_move(DOOD_LEFT);
	SDL_Event e;
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}

		if(e.type == SDL_KEYDOWN)
		{
			if(e.key.keysym.sym == SDLK_UP )
			{
				inputTarget ->set_move(DOOD_UP);
			}
			if(e.key.keysym.sym == SDLK_DOWN)
			{
				inputTarget ->set_move(DOOD_DOWN);
			}
			if(e.key.keysym.sym == SDLK_LEFT)
			{
				inputTarget ->set_move(DOOD_LEFT);
			}
			if(e.key.keysym.sym == SDLK_RIGHT)
			{
				inputTarget ->set_move(DOOD_RIGHT);
			}
			if(e.key.keysym.sym == SDLK_z)
			{
				inputTarget -> set_move(DOOD_ACTION);
			}
			if(e.key.keysym.sym == SDLK_x)
			{
				inputTarget -> set_move(DOOD_CANCEL);
			}
			if(e.key.keysym.sym == SDLK_TAB)
			{
				inputTarget -> set_move(DOOD_START);
			}
			if(e.key.keysym.sym == SDLK_q)
			{
				inputTarget -> set_move(DOOD_SELECT);
			}
            if(e.key.keysym.sym == SDLK_ESCAPE )
            {
                quit = true;
            }
		}
	}
}

void GameEngine::gamedisplay( SDL_Window * window )
{
	////clear screen
	SDL_FillRect ( screenSurface, &screenBuffer, 0x000000/*black*/);

	list<dood>::iterator it = actors.begin();
	set_camera();

	cur -> show();
	hero -> show();
	while (it != actors.end())
	{
		it->show();
	it++;
	}

	batch.sort( Comparedepth );
	while(!batch.empty())
	{
	   // printf( "body dest loc w = %d, h = %d, y =%d, x = %d\n", batch.front()->srcloc.w , batch.front()->srcloc.h , batch.front()->srcloc.y , batch.front()->srcloc.x);
	    //printf( "body dest loc w = %d, h = %d, y =%d, x = %d\n", batch.front()->camloc.w , batch.front()->camloc.h , batch.front()->camloc.y , batch.front()->camloc.x);
		SDL_BlitSurface(batch.front()->src, &batch.front()->srcloc , screenSurface, &batch.front()->camloc);
		batch.pop_front();
	}
    //SDL_Delay(1000);
	//SDL_BlitSurface(screenSurface, NULL, screen, NULL);
	SDL_BlitScaled( screenSurface, NULL, screen, NULL);
	SDL_UpdateWindowSurface( window );

}

void GameEngine::set_camera()
{
	camera.x = (( camfocus->getpos().x + DOOD_WIDTH / 2 ) - SCREEN_TILE_WIDTH*TILE_SIZE / 2);
	camera.y = (( camfocus->getpos().y + DOOD_HIGHT / 2 ) - SCREEN_TILE_HIGHT*TILE_SIZE / 2);
}

void GameEngine::consoled_display()
{

	for(int i = 0; i < cur->get_x(); i++)
		{
			for(int j = 0; j < cur->get_y(); j++)
			{
				if(1)
				{
					printf(" P");
				}
				else
				{
					if(cur->get_map()[i][j].tile_type <= 9)
					{
						printf(" %d", cur->get_map()[i][j].tile_type);
					}
					else
					printf("%d", cur->get_map()[i][j].tile_type);
				}
			}
		printf("\n");
		}
}
