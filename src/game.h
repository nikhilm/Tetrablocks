/******************************
 * game.h - handles SDL initialisation
 * Created - June 24, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_GAME_H
#define TB_GAME_H

#include<SDL/SDL.h>


namespace TetraBlocks {
    class GameGrid;
    class Game{
        public:
            Game();

        private:
            bool loopRunning;
            SDL_Surface * screen;
            void setupSDL();
            void startGame();
    };
};

#endif

