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
        // TODO:Add real logic this is test code
        int coords[][2] = {{2,5}, {5,6}, {9, 3}};
        for(int i = 0; i < 3; i++) {
            grid[coords[i][0]][coords[i][1]] = new Block(IMG_Load("../images/block_blue.png"));
            grid[coords[i][0]][coords[i][1]]->x = coords[i][0];
            grid[coords[i][0]][coords[i][1]]->y = coords[i][1];
        }
        
        currentPiece = Piece::createRandomPiece(6, 10);
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

    bool GameGrid::update(Game * game) { return true; }
    void GameGrid::handle(SDL_Event &event) {}

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

