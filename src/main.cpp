/******************************
 * main.cpp - main class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include<iostream>

#include<SDL/SDL.h>

#include<state.h>

namespace TetraBlocks {
    class Game {
    private:
        SDL_Surface * screen;
        bool programRunning;
        State * currentState;

    public:
        void Game() {
            if(SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cout<<"Can't initialize SDL"<<SDL_GetError()<<std::endl;
                exit(1);
            }
            atexit(SDL_Quit);

            screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

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

            currentState = new MenuState();
            currentState->init();
            
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

                    currentState->handle(event);
                }

                currentState->update(this);
                SDL_Rect * updates = currentState->display(screen);
                SDL_Flip();
            }
        }
    };
};
int main() {
    new TetraBlocks::Game();
}

