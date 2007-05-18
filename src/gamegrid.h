/******************************
 * gamegrid.h - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_GAMEGRID_H
#define TB_GAMEGRID_H

#include "state.h"
#include "blocks.h"

namespace TetraBlocks {
    class GameGrid : public State {
    private:
        enum {GRID_WIDTH = Block::WIDTH * 10, GRID_HEIGHT = Block::WIDTH * 20};
        State* nextState();
        bool init();
        SDL_Rect * display(SDL_Surface * screen);
        bool update(Game * game);
        void handle(SDL_Event &event);
    };
};
        
#endif
