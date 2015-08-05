#include "tile.h"

#include "pugixml.hpp"

level::level(int areaid , GameEngine* myengine)
{

	engine = myengine;

    int * mapdata;
    int * lampmap;

    //get level data
    level_in( areaid , mapdata, lampmap, levelx, levely);

    //load pallet town tilest and store in level tileset var
    loadMedia( (char*)PALLET /*tile_set_path[ areaid ]*/ , tileSet, engine->get_screen() );

    LoadLevel( (char*)PALLET );
    
    //mainmap = tilesetup(levelx , levely, mapdata,lampmap );
    spritemap = spritesetup( levelx, levely , mainmap);


}

void level::LoadLevel( char * xmlfile )
{
  //begining xmlreader implementation
  /*
  pugi::xml_document doc;
  
  pugi::xml_parse_result result = doc.load_file("assets/pallet.tmx");
  
  pugi::xml_node spider = doc.child("map");
  std::cout << spider.attribute("height").value();
  spider = spider.child("tileset");
  std::cout << spider.attribute("name").value() << std::endl;
  spider = spider.next_sibling("tileset");
  std::cout << spider.attribute("name").value() << std::endl;
  std::cout  << spider;
  spider = spider.next_sibling("tileset");
  std::cout << spider.attribute("name").value() << std::endl;
  */
  int height, width;
  
  //open file
  pugi::xml_document doc;
  
  //pugi::xml_parse_result result = doc.load_file( xmlfile );
  pugi::xml_parse_result result = doc.load_file("assets/pallet.tmx");
  
  //get width and hight
  //and make layer maps

  pugi::xml_node spider = doc.child("map");
  
  height = spider.attribute("height").as_int();
  width  = spider.attribute( "width").as_int();
  
  std::cout << height << " " << width << std::endl;
  tilesrc temp;
  //create tileset pointers
  pugi::xml_node name;
  for( spider = spider.child("tileset"); spider != 0; spider = spider.next_sibling("tileset") )
    {
      temp.first = spider.attribute("firstgid").as_int();
      
      std::cout << temp.first << std::endl;
      name = spider.child("image");
      
      if( loadMedia( (char*)name.attribute("source").value() , temp.source , engine->get_screen()) )
	{
	  tilesets.push_back(temp);
	}
      else
	{
	cout << "ERROR CREATING TILESET\n";
	exit( 1 );
	}
    }
  
  std::cout << "tilesets created\n";
  //make tile rules
  
  //read in tile layers
  spider = spider.next_sibling("layer");
  name = spider
  bottom = layer_set( name, width, height ); 

  spider = spider.next_sibling("layer");
  name = spider;
  mid = layer_set( name, width, height ); 

  spider = spider.next_sibling("layer");
  name = spider;
  top = layer_set( name, width, height ); 

}

Sprite * level::layer_set( pugi::xml_node  node, int width, int height)
{
  node = node.child("data");
  if(node != 1)
    std::cout << "layerget\n";

  Sprite * vcr = new(nothrow) Sprite*[width];


  if(vcr == nullptr)
    {
      std::cout << "Level Layer dynamic allocation failed, way to fail dicknuts";
      exit(0);
    }

  for(int i = 0; i < width ; i++ )
    {
      vcr[i] = new(nothrow) Sprite[height];

      if(vcr[i] == nullptr)
	{
	  std::cout << "Level Layer dynamic allocation failed, way to fail dicknuts";
	  exit(0);
	}

    }
  node = node.child("tile");
  for( int i = 0; i < width; i++)
    for( int j = 0; j < height; j++)
      {
	vcr[i][j].tile_type = node.attribute("gid").as_int();
	node = node.next_sibling("tile");
	std::cout << vcr[i][j].tiletype;
      }

  return vcr;
}

bool level::level_in( int areaid ,int * &floor, int * &lamp, int &x , int &y  )
{
    int errnum = 0;
    int temp; // for trash data
    char delim;
    fstream fin;
    fin.open(area[ areaid ]); //get area id from structure and get path to level data


    if(fin)//check if it opened
    {
        fin >> x >> y;//get x y of main level
        //printf("%d\n %d\n",x,y);

	/*
        //if there are
        if(adj)
        {
            //read in the id and xywh of the anchor to the adj
        for(int i = 0; i < adj; i++)
        {
            fin >> adjid[i];
            fin >> anchor[i][0].x;
            fin >> anchor[i][0].y;
            fin >> anchor[i][0].w;
            fin >> anchor[i][0].h;

                //open stream to adjecent level

            next[i].open(area [ adjid[i] ] );

            //if it opens
                if(next[i])
                {
                    //get the x and y values of the adjcent area
                    next[i] >> adj_x[i] >> adj_y[i];
                    printf("Route 1 opened recived x %d, y %d\n", adj_x[i],adj_y[i]);
                    //reads the amount of areas next to ajd area(doesnt matter)

                    next[i] >> temp;
                    if(temp == 0)
                    {
                        printf("Level data error\n");
                    }


                    //reads the id of an adjcent area and checks if its the main area
                    //if not it tests the next one
                    next[i] >> temp;
                    while(temp != areaid)
                    {
                        next[i] >> temp >> temp >> temp >> temp >> temp;
                    }
                    if(temp == areaid)
                    {
                        next[i] >> anchor[i][1].x;
                        next[i] >> anchor[i][1].y;
                        next[i] >> anchor[i][1].w;
                        next[i] >> anchor[i][1].h;
                    }
                    printf("anchor point x %d\ny %d\nw %d\nh %d\n", anchor[i][1].x,anchor[i][1].y,anchor[i][1].w,anchor[i][1].h );

                }
                else
                {
                    printf("Missing Next area!\n");
                    return false;
                }

            next[i].close();

                if( n > ( anchor[i][0].y - anchor[i][1].y ) )
                {
                    n = anchor[i][0].y - anchor[i][1].y;
                }
                if( e < ( anchor[i][0].x - anchor[i][1].x +adj_x[i] ) )
                {
                    e = anchor[i][0].x - anchor[i][1].x + adj_x[i];
                }
                if( s < ( anchor[i][0].y - anchor[i][1].y + adj_y[i] ) )
                {
                    s = anchor[i][0].y - anchor[i][1].y + adj_y[i];
                }
                if( w > ( anchor[i][0].x - anchor[i][1].x ) )
                {
                    w = anchor[i][0].x - anchor[i][1].x;
                }

            printf ("Level params are n = %d, e = %d, s = %d, w = %d\n",n,e,s,w);
            }
            x = -1*w + e;
            y = -1*n + s;
        }


        printf( "estimated level size x = %d, y = %d", x ,y );
*/
	//make floor and lamp pointers
        floor = new (nothrow)int[x*y];
        lamp = new (nothrow)int[x*y];

        if(floor == nullptr)
        {
            printf("Floor did not dynamically allocate correctly\n");
        return false;
        }
        if(lamp == nullptr)
        {
            printf("Lamp did not dynamically allocate correctly\n");
        return false;
        }
	

        //printf("x is %d, y is %d\n",x,y);
        for(int i = 0; i < x*y; i++)
        {
           // if(i%x == 0)
            //printf("\n");
            fin >> floor[i];
           // printf ( "%d",floor[i]);

        }

        for(int i = 0; i < x*y; i++)
        {
                    //if(i%x == 0)
              //  printf("\n");
            fin >> lamp[i];
           // printf ( "%d",lamp[i]);

        }
	
	mainmap = tilesetup(levelx , levely, floor ,lamp);

	//get number of transportign blocks
	int portals;
	fin >> portals;

        coord portalspot;

	for( int i = 0; i < portals; i++)
	  {
	    //read where the portal spot will be
	    fin >> portalspot.x >> portalspot.y;
	    mainmap[portalspot.x][portalspot.y].portal = true;	    


	    //get where the portal will go then place
	    fin >> temp;
	    mainmap[portalspot.x][portalspot.y].world = temp;

	    //get x coord of where we end up
	    fin >> temp;
	    mainmap[portalspot.x][portalspot.y].out.x = temp;
	    
	    //get y coord of where we end up
	    fin >> temp;
	    mainmap[portalspot.x][portalspot.y].out.y = temp;
	  }

        fin.close();

        return true;
        }
    else
    {
     printf("Level FinError!\n");
    return false;
    }
}

Sprite ***  level::spritesetup(int x ,int y,  tile ** tilemap )
{
    Sprite *** retsprite = new (nothrow) Sprite **[x];

	//map = makesprites()

    	for(int i = 0; i < x; i++)
	{
		retsprite[i] = new (nothrow) Sprite*[y];
	}
		for(int i = 0; i < x; i++)
			for(int j = 0; j < y; j++)
			{
			retsprite[i][j] = new (nothrow) Sprite[2];
			}



    //printf("tile size = %d, square params are %d,%d,%d,%d",TILE_SIZE,SQUARE.w,SQUARE.h,SQUARE.y,SQUARE.x);
	for(int i = 0; i < x ; i++)
		for( int j = 0; j < y; j++)
		{

			retsprite[i][j][0].depth = 1;
			//setting the job's tileset
			retsprite[i][j][0].src = tileSet;
			//sprite source size
			retsprite[i][j][0].srcloc = SQUARE;
			retsprite[i][j][0].srcloc.y = 0;
			retsprite[i][j][0].srcloc.x = TILE_SIZE * (mainmap[i][j].tile_type-1);
			//sprite destination size
			retsprite[i][j][0].destloc = SQUARE;
			retsprite[i][j][0].destloc.x = TILE_SIZE * i;
			retsprite[i][j][0].destloc.y = TILE_SIZE * j;
			//destination on camera size
			retsprite[i][j][0].camloc.w = TILE_SIZE;
			retsprite[i][j][0].camloc.h = TILE_SIZE;
            retsprite[i][j][0].draw = true;
            //printf("spite map params src whxy= %d,%d,%d,%d",retsprite[i][j][0].destloc.w,retsprite[i][j][0].destloc.h,retsprite[i][j][0].destloc.x,retsprite[i][j][0].destloc.y);
			//top layer jobs
		retsprite[i][j][1].depth = 2;
			if(mainmap[i][j].top_type >= 1)
			{
			retsprite[i][j][1].src = tileSet;
			retsprite[i][j][1].srcloc = SQUARE;
			retsprite[i][j][1].srcloc.y = TILE_SIZE;
			retsprite[i][j][1].srcloc.x = TILE_SIZE * (mainmap[i][j].top_type-1);
			//sprite destination size
			retsprite[i][j][1].destloc = SQUARE;
			retsprite[i][j][1].destloc.x = TILE_SIZE * i;
			retsprite[i][j][1].destloc.y = TILE_SIZE * j;
			//destination on camera size
			retsprite[i][j][1].camloc.w = TILE_SIZE;
			retsprite[i][j][1].camloc.h = TILE_SIZE;
			retsprite[i][j][1].draw = true;
			}
			else
            {
                retsprite[i][j][1].draw = false;
            }
		}

    return retsprite;
}

tile ** level::tilesetup( int x ,int y, int * mapdata, int * lampmap )
{

    tile ** retmap = new (nothrow) tile *[x];
    	for(int i = 0; i < x; i++)
	{
		retmap[i] = new (nothrow) tile[y];

	if (retmap[i] == nullptr)
		{
			printf("could not load map");
		}
	}

		int k = 0;
	for(int i = 0; i < y; i++)
		for(int j = 0; j < x; j++,k++)
		{
			if(mapdata[k] > 14)
			{
				retmap[j][i].solid = true;
			}
			else
			{
				retmap[j][i].solid = false;
			}
			retmap[j][i].tile_type = mapdata[k];
			retmap[j][i].occupied = false;
			retmap[j][i].portal = false;
			retmap[j][i].top_type = lampmap[k];
		}

    return retmap;
}


tile ** level::get_map()
{
	return mainmap;
}


void level::show()
{

	for(int i = 0; i < levelx ; i++)
		for( int j = 0; j < levely; j++)
		{
			if( checkCollision( &spritemap[i][j][0].destloc , engine->get_camera()) )
			{
				spritemap[i][j][0].camloc.x = spritemap[i][j][0].destloc.x - engine->get_camera()->x;
				spritemap[i][j][0].camloc.y = spritemap[i][j][0].destloc.y - engine->get_camera()->y;
				engine->get_batch()->push_front(&spritemap[i][j][0]);
				//printf( "floor  w = %d, h = %d, y =%d, x = %d\n", engine->get_batch()->front()->srcloc.w , engine->get_batch()->front()->srcloc.h , engine->get_batch()->front()->srcloc.y , engine->get_batch()->front()->srcloc.x);
			}
			if( spritemap[i][j][1].draw && checkCollision(  &spritemap[i][j][1].destloc , engine->get_camera()) )
			{
				spritemap[i][j][1].camloc.x = spritemap[i][j][1].destloc.x - engine->get_camera()->x;
				spritemap[i][j][1].camloc.y = spritemap[i][j][1].destloc.y - engine->get_camera()->y;
				engine->get_batch()->push_front(&spritemap[i][j][1]);
               // printf( "lamp w = %d, h = %d, y =%d, x = %d\n", engine->get_batch()->front()->srcloc.w , engine->get_batch()->front()->srcloc.h , engine->get_batch()->front()->srcloc.y , engine->get_batch()->front()->srcloc.x);
			}
		}
}


void level::update()
{




}
