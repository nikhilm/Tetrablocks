/******************************
 * state.cpp - base state class
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include <iostream>

#include "state.h"

namespace TetraBlocks {
    State* State::nextState() {
        return NULL;
    }
    bool State::init() { return true; }
    SDL_Rect * State::display(SDL_Surface * screen) { }
    bool State::update(Game * game) { return true; }
    void State::handle(SDL_Event &event) {}
    
};

