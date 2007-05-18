CC=g++
CFLAGS=`sdl-config --cflags --libs`
INCLUDES=state.h
SOURCES=state.cpp

all:tetrablocks

tetrablocks:$(INCLUDES) $(SOURCES) main.cpp
	$(CC) $(INCLUDES) $(SOURCES) $(CFLAGS) main.cpp -o tetrablocks

