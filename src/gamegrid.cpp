/******************************
 * gamegrid.cpp - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include<SDL/SDL_image.h>
#include "gamegrid.h"

namespace TetraBlocks {
    State* GameGrid::nextState() {
        return 0;
    }
    bool GameGrid::init() { 
        block = new Block(IMG_Load("../images/block_red.png"));
        return true;
    }
    SDL_Rect * GameGrid::display(SDL_Surface * screen) { 
        drawGridOutline(screen);

        block->display(LEFT, TOP, screen);
        return 0;
    }

    bool GameGrid::update(Game * game) { return true; }
    void GameGrid::handle(SDL_Event &event) {}

    void GameGrid::drawGridOutline(SDL_Surface * screen) {
        SDL_Rect r;
        r.x = LEFT-1;
        r.y = TOP-1;
        r.w = GRID_WIDTH*Block::WIDTH+2;
        r.h = GRID_HEIGHT*Block::HEIGHT+2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 255, 255, 255));
        r.x++;
        r.y++;
        r.w-=2;
        r.h-=2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0, 0, 0));

    }
};

