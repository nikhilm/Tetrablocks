/******************************
 * main.cpp - main class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include<iostream>

#include<SDL/SDL.h>

#include "gamegrid.h"

namespace TetraBlocks {
    class Game {
    private:
        SDL_Surface * screen;
        bool programRunning;
        GameGrid *gameGrid;

    public:
        Game() {
            if(SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cout<<"Can't initialize SDL"<<SDL_GetError()<<std::endl;
                exit(1);
            }
            atexit(SDL_Quit);

            screen = SDL_SetVideoMode(600, 500, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

            if(screen == NULL) {
                std::cout<<"Unable to set video mode "<<SDL_GetError()<<std::endl;
                exit(1);
            }

            SDL_WM_SetCaption("TetraBlocks", NULL);

            SDL_Rect r;
            r.x = r.y = 0;
            r.w = screen->w;
            r.h = screen->h;
            SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0, 0, 0));

            gameGrid = new GameGrid();
            gameGrid->init(this);
            
            gameLoop();
        }
    private:
        void gameLoop() {
            SDL_Event event;
            programRunning = true;
            while(programRunning) {
                while(SDL_PollEvent(&event)) {
                    if(SDL_QUIT == event.type) programRunning = false;
                    if(SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym) programRunning = false;

                    gameGrid->handle(event);
                }

                gameGrid->update();
                gameGrid->display(screen);
                SDL_Flip(screen);
            }
        }
    };
};
int main() {
    new TetraBlocks::Game();
}

