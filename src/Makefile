CC=g++
CFLAGS=-g -Wall $(shell sdl-config --cflags)
LDFLAGS=$(shell sdl-config --libs) -lSDL_image -lSDL_ttf
INCLUDES=blocks.h piece.h game.h gamegrid.h
SOURCES=piece.cpp gamegrid.cpp game.cpp

PROGRAMS=../tetrablocks

all:tetrablocks


clean:
	rm -f *.o
	rm -f *.gch

tetrablocks:main.cpp $(INCLUDES) $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(SOURCES) main.cpp -o $(PROGRAMS)

highscores:highscore.h
	$(CC) test_highscore.cpp highscore.h -o test_highscore

menu:menu.h
	$(CC) $(CFLAGS)  menu.h menu.cpp -c
	$(CC) $(LDFLAGS) menu.o test_menu.cpp -o test_menu

