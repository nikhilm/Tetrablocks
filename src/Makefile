CC=g++
CFLAGS=-g -Wall $(shell sdl-config --cflags)
LDFLAGS=-g -Wall $(shell sdl-config --libs) -lSDL_image
INCLUDES=state.h gamegrid.h blocks.h piece.h
SOURCES=gamegrid.cpp piece.cpp

PROGRAMS=tetrablocks

all:$(PROGRAMS)


clean:
	rm -f *.o
	rm -f *.gch

objects:$(INCLUDES) $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -c

tetrablocks:objects main.cpp
	$(CC) $(LDFLAGS) *.o main.cpp -o tetrablocks


