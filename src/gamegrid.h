/******************************
 * gamegrid.h - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_GAMEGRID_H
#define TB_GAMEGRID_H

#include <SDL/SDL_ttf.h>

#include "blocks.h"
#include "piece.h"


namespace TetraBlocks {
    class Game;
    class GameGrid {
    public:
        enum {TOP=50, LEFT = 200, GRID_WIDTH = 10, GRID_HEIGHT = 20, START_X=3, START_Y=0, DEFAULT_DOWNTIME=1000};
    private:

        Block * grid[GRID_HEIGHT][GRID_WIDTH];

        void drawGridOutline(SDL_Surface * screen);

        Piece * currentPiece, * nextPiece;

        Uint32 moveDownTime;

        //starting downTime, is decremented later
        Uint32 downTime;

        const Game * gameRef;

        TTF_Font *scoreFont;

        bool gameOver;

        //score related stuff
        int score;
        int level;
        void updateScore(int);
        void displayScore(int, int, SDL_Surface *);

        void checkLevelUpdate();

        void genNewPieces() {
            currentPiece = nextPiece;
            currentPiece->setX(START_X);
            currentPiece->setY(START_Y);
            nextPiece = Piece::createRandomPiece(0, 0, this);
        };

        void printMap();

        void checkLines();
        void clearLine(int);

        void setupSDLText();


    public:
        GameGrid(const Game *);
        void display(SDL_Surface * screen);
        bool update();
        void handle(SDL_Event &event);
        void acceptBlock(int, int, Block*);
        bool mayPlace(int, int);
        void lockPiece();
    };
};
        
#endif
