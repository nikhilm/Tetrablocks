/******************************
 * state.h - base state class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_STATE_H
#define TB_STATE_H
#include<SDL/SDL.h>

namespace TetraBlocks {
    class State {
    public:
        State* nextState();
        bool init();
        SDL_Rect [] display(SDL_Surface * screen);
        bool update(Game * game);
        void handle(SDL_Event &event);
    };
};

#endif // TB_STATE_H
