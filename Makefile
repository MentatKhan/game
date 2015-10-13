

OBJS=dood.o doodad.o engine.o globals.o  tile.o main.o pugixml.o

LFLAGS=

CFLAGS= -std=c++11 -lSDL2 -lSDL2_image

BFLAGS= -lSDL2

alpha: $(OBJS)
	g++ $(BFLAGS) -g -o $@ $(OBJS) 

.cpp.o:
	g++ $(CFLAGS) -g -c  $<

clean:
	rm -f *.o *~ alpha tmp.data
