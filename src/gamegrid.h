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
        enum {TOP=50, LEFT = 200, GRID_WIDTH = 10, GRID_HEIGHT = 20};

        Block * grid[GRID_HEIGHT][GRID_WIDTH];

        void drawGridOutline(SDL_Surface * screen);


    public:

        State* nextState();
        bool init();
        SDL_Rect * display(SDL_Surface * screen);
        bool update(Game * game);
        void handle(SDL_Event &event);
    };
};
        
#endif
