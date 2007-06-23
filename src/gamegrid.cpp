/******************************
 * gamegrid.cpp - State to handle main tetris game
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */
#include<iostream>

#include<SDL/SDL_image.h>

#include "game.h"
#include "gamegrid.h"

//convert integer to character string
const char * itoa(int num) {
    std::string str = "";
    if(num == 0) return "0";
    while(num > 0) {
        str += ('0' + num%10);
        num /= 10;
    }

    //reverse it
    std::string rev = "";
    for(int i = str.length()-1; i >= 0; --i)
        rev += str[i];

    return rev.c_str();
}

namespace TetraBlocks {
    bool GameGrid::init(const Game * game) {
        for(int i = 0; i < GRID_HEIGHT; ++i) {
            for(int j = 0; j < GRID_WIDTH; ++j) {
                grid[i][j] = NULL;
            }
        }
        nextPiece = Piece::createRandomPiece(0, 0, this);
        genNewPieces();
        moveDownTime = SDL_GetTicks();
        downTime = DEFAULT_DOWNTIME;

        gameRef = game;

        score = 0;
        level = 1;
        
        setupSDLText();

        return true;
    }

    void GameGrid::updateScore(int lines) {
        int lineScores[4] = {10, 25, 75, 300};
        score += (level + 1) * 10 * lineScores[lines-1];
    }

    void GameGrid::display(SDL_Surface * screen) { 
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        drawGridOutline(screen);
        displayScore(460, 190, screen);
        nextPiece->display(50, 160, screen);
        for(int i = 0; i < GRID_HEIGHT; ++i) {
            for(int j = 0; j < GRID_WIDTH; ++j) {
                if(grid[i][j] != NULL)
                    grid[i][j]->display(LEFT+j*Block::WIDTH, TOP+i*Block::HEIGHT, screen);
            }
        }
        currentPiece->display(LEFT, TOP, screen);
    }

    bool GameGrid::update() { 
        // TODO: check piece position
        //for now just bottom
        if( currentPiece->bottomCollision() ) {
            std::cout<<"Detected collision\n";
            lockPiece();
        }

        Uint32 now = SDL_GetTicks();
        if(now >= moveDownTime) {
            currentPiece->moveDown();
            //downTime -= 100;
            moveDownTime = SDL_GetTicks() + downTime;
        }

        return true; 
    }
    void GameGrid::handle(SDL_Event &event) {
        currentPiece->handle(event);
        if(event.type == SDL_KEYDOWN) {
           switch(event.key.keysym.sym) {
               case SDLK_SPACE:
                   genNewPieces();
                   downTime = DEFAULT_DOWNTIME;
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

    void GameGrid::displayScore(int offsetX, int offsetY, SDL_Surface *screen) {
        SDL_Surface * textSurf;
        SDL_Color col = {255, 0, 0};
        if(!(textSurf = TTF_RenderText_Solid(scoreFont, itoa(score), col))) {
            std::cerr<<TTF_GetError()<<std::endl;
        }

        SDL_Rect r;
        r.x = offsetX;
        r.y = offsetY;

        SDL_BlitSurface(textSurf, NULL, screen, &r);

        SDL_FreeSurface(textSurf);
    }

    void GameGrid::checkLines() {
        //for each line, if all places are empty, increment line count
        // also mark topmost position. remove all lines from there to line count
        // downwards. then move all blocks above topmost position down by line count
        // if line completely empty then stop checking, since lines above it are empty too
        
        std::cout<<"Checking lines\n";
        bool linesToClear[GRID_HEIGHT];

        for(int i = GRID_HEIGHT-1; i >= 0; --i) {
            bool lineFull = true;
            bool lineTotallyEmpty = true;
            for(int j = 0; j < GRID_WIDTH; ++j) {
                if(grid[i][j] != NULL)
                    lineTotallyEmpty = false;
                    
                if(grid[i][j] == NULL)
                    lineFull = false;
            }
            
            if(lineFull) {
                linesToClear[i] = true;
                clearLine(i);
            }
            else {
                linesToClear[i] = false;
            }

            if(lineTotallyEmpty) {
                break;
            }

            //now if a line has been emptied, move all blocks above it down one
            for(int line = 0; line < GRID_HEIGHT; ++line) {
                if(linesToClear[line] == true) {
                    for(int i = line - 1; i >= 0; --i) {
                        for(int j = 0; j < GRID_WIDTH; ++j) {
                            if(grid[i][j] != NULL)
                                grid[i+1][j] = grid[i][j];
                            grid[i][j] = NULL;
                        }
                    }
                }
            }
        }

        int lineCount = 0;
        //for(int k = GRID_HEIGHT-1; k >= 0; k--) {
        //    if(linesToClear[k] == true) {
        //        clearLine(k);
        //        lineCount++;
        //    }
        //}

        updateScore(lineCount);
    }

    //set all blocks in line to null
    void GameGrid::clearLine(int line) {
        for(int k = 0; k < GRID_WIDTH; ++k)
            grid[line][k] = NULL;

        /*for(int i = line-1; i >= 0; --i) {
            for(int j = 0; j < GRID_WIDTH; j++) {
                if(grid[i][j] != NULL) {
                    grid[i+1][j] = grid[i][j];
                    grid[i][j] = NULL;
                }
            }
        }*/
        std::cout<<"Cleared line "<<line<<std::endl;
    }

    void GameGrid::acceptBlock(int x, int y, Block * block) {
        grid[y][x] = block;
    }

    bool GameGrid::mayPlace(int x, int y) {
        return x >= 0 && x < GRID_WIDTH &&
               y >= 0 && y < GRID_HEIGHT &&
               grid[y][x] == NULL;
    }

    void GameGrid::lockPiece() {
        currentPiece->releaseBlocksToGrid();
        genNewPieces();
        downTime = DEFAULT_DOWNTIME;
        checkLines();
        //printMap();
    }

    void GameGrid::printMap() {
        std::cout<<"-----------------\n";
        std::cout<<"   0 1 2 3 4 5 6 7 8 9"<<std::endl;
        for(int i = 0; i < GRID_HEIGHT; ++i) {
            std::cout<<( i < 10 ? " " : "")<<i<<" ";
            for(int j = 0; j < GRID_WIDTH; ++j) {
                if(grid[i][j] != NULL)
                    std::cout<<"# ";
                else
                    std::cout<<"  ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"-----------------\n";
    }


    void GameGrid::setupSDLText() {
        //try loading SDL_ttf
        if(!TTF_WasInit() && TTF_Init() == -1) {
            std::cerr<<"Error initializing SDL_ttf library, cannot draw text. Error: "<<TTF_GetError()<<std::endl;
        }

        scoreFont = TTF_OpenFont("../data/Vera.ttf", 30);
        if(!scoreFont) {
            std::cerr<<"Error loading font file"<<TTF_GetError()<<"\n";
        }
    }
};

