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
    class Game;
    class State {
    public:
        State() {};
        virtual State* nextState();
        virtual bool init();
        virtual SDL_Rect * display(SDL_Surface * screen);
        virtual bool update(Game * game);
        virtual void handle(SDL_Event &event);
        virtual ~State(){};
    };
};

#endif // TB_STATE_H
