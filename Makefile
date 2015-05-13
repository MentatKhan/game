

OBJS=dood.o doodad.o engine.o globals.o  tile.o main.o

LFLAGS=

CFLAGS= -std=c++11 -lSDL2

BFLAGS= -lSDL2

alpha: $(OBJS)
	g++ $(BFLAGS) -o $@ $(OBJS) 

.cpp.o:
	g++ $(CFLAGS) -c  $<

clean:
	rm -f *.o *~ alpha tmp.data
