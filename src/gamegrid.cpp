/******************************
 * gamegrid.cpp - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */


#include "gamegrid.h"

namespace TetraBlocks {
    State* GameGrid::nextState() {
        return 0;
    }
    bool GameGrid::init() { return true; }
    SDL_Rect * GameGrid::display(SDL_Surface * screen) { return 0;}
    bool GameGrid::update(Game * game) { return true; }
    void GameGrid::handle(SDL_Event &event) {}
    
};

