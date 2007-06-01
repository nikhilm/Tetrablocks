CC=g++
CFLAGS=-g -Wall $(shell sdl-config --cflags)
LDFLAGS=-g -Wall $(shell sdl-config --libs) -lSDL_image -lSDL_ttf
INCLUDES=state.h gamegrid.h blocks.h piece.h
SOURCES=gamegrid.cpp piece.cpp

PROGRAMS=tetrablocks

all:$(PROGRAMS)


clean:
	rm -f *.o
	rm -f *.gch

objects:$(INCLUDES) $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -c

tetrablocks:objects main.cpp highscores
	$(CC) $(LDFLAGS) *.o main.cpp -o tetrablocks

highscores:highscore.h
	$(CC) test_highscore.cpp highscore.h -o test_highscore

menu:menu.h
	$(CC) $(CFLAGS)  menu.h menu.cpp -c
	$(CC) $(LDFLAGS) menu.o test_menu.cpp -o test_menu

