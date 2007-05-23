/******************************
 * gamegrid.cpp - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */
#include<iostream>

#include<SDL/SDL_image.h>
#include "gamegrid.h"

namespace TetraBlocks {
    State* GameGrid::nextState() {
        return 0;
    }
    bool GameGrid::init() {
        for(int i = 0; i < GRID_HEIGHT; ++i) {
            for(int j = 0; j < GRID_WIDTH; ++j) {
                grid[i][j] = NULL;
            }
        }
        currentPiece = Piece::createRandomPiece(START_X, START_Y);
        moveDownTime = SDL_GetTicks();
        downTime = 1000;
        
        return true;
    }
    SDL_Rect * GameGrid::display(SDL_Surface * screen) { 
        drawGridOutline(screen);
        for(int i = 0; i < GRID_HEIGHT; ++i) {
            for(int j = 0; j < GRID_WIDTH; ++j) {
                if(grid[i][j] != NULL)
                    grid[i][j]->display(LEFT, TOP, screen);
            }
        }
        currentPiece->display(LEFT, TOP, screen);
        return 0;
    }

    bool GameGrid::update(Game * game) { 

        Uint32 now = SDL_GetTicks();
        if(now >= moveDownTime) {
            currentPiece->moveDown();
            downTime -= 100;
            moveDownTime = SDL_GetTicks() + downTime;
        }
        return true; 
    }
    void GameGrid::handle(SDL_Event &event) {
        if(event.type == SDL_KEYDOWN) {
           switch(event.key.keysym.sym) {
               case SDLK_SPACE:
                   currentPiece = Piece::createRandomPiece(START_X, START_Y);
                   break;
               case SDLK_DOWN:
                   currentPiece->moveDown();
                   break;
               default:break;
           }
        }
    }

    void GameGrid::drawGridOutline(SDL_Surface * screen) {
        SDL_Rect r;
        r.x = LEFT-1;
        r.y = TOP-1;
        r.w = GRID_WIDTH*Block::WIDTH+2;
        r.h = GRID_HEIGHT*Block::HEIGHT+2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 255, 255, 255));
        r.x++;
        r.y++;
        r.w-=2;
        r.h-=2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0, 0, 0));

    }
};

