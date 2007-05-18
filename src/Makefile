CC=g++
CFLAGS=`sdl-config --cflags --libs`
CCFLAGS=-g -Wall
INCLUDES=state.h gamegrid.h blocks.h
SOURCES=gamegrid.cpp

all:tetrablocks

tetrablocks:$(INCLUDES) $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) main.cpp -o tetrablocks

