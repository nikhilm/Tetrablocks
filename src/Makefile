CC=g++
CFLAGS=-g -Wall $(shell sdl-config --cflags)
LDFLAGS=-g -Wall $(shell sdl-config --libs) -lSDL_image -lSDL_ttf
INCLUDES=blocks.h piece.h gamegrid.h
SOURCES=piece.cpp gamegrid.cpp

PROGRAMS=tetrablocks

all:$(PROGRAMS)


clean:
	rm -f *.o
	rm -f *.gch

tetrablocks:main.cpp $(INCLUDES) $(SOURCES)
	$(CC) $(LDFLAGS) $(INCLUDES) $(SOURCES) main.cpp -o tetrablocks

highscores:highscore.h
	$(CC) test_highscore.cpp highscore.h -o test_highscore

menu:menu.h
	$(CC) $(CFLAGS)  menu.h menu.cpp -c
	$(CC) $(LDFLAGS) menu.o test_menu.cpp -o test_menu

