/******************************
 * game.cpp - handles SDL initialisation
 * Created - June 24, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include "game.h"
#include "gamegrid.h"

namespace TetraBlocks {
    class GameGrid;
    
    Game::Game() {
        setupSDL();

        loopRunning = true;
        startGame();
    }

    void Game::setupSDL() {
        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout<<"Can't initialize SDL"<<SDL_GetError()<<std::endl;
            exit(1);
        }
        atexit(SDL_Quit);

        screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

        if (screen == NULL) {
            std::cout<<"Unable to set video mode: "<<SDL_GetError()<<std::endl;
            exit(1);
        }

        SDL_WM_SetCaption("TetraBlocks", NULL);


    }

    void Game::startGame() {
        GameGrid *grid = new GameGrid();
        grid->init(this);

        SDL_Event event;
        while(loopRunning)
        {
            while(SDL_PollEvent(&event))
            {
                if (SDL_QUIT == event.type) loopRunning = false;
                if (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym) loopRunning = false;
                
                grid->handle(event);
            }

            grid->update();
            grid->display(screen);
            SDL_Flip(screen);
        }
    }
}
