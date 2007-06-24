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
    GameGrid::GameGrid(const Game * game) {
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

        gameOver = false;
        
        setupSDLText();

        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

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
        if(gameOver) {
            SDL_Color red = {255, 0, 0};
            SDL_Surface * gameOverText = drawText("Game Over", red);

            SDL_Rect r;
            r.x = 213;
            r.y = 75;

            SDL_BlitSurface(gameOverText, NULL, screen, &r);

            SDL_FreeSurface(gameOverText);
        }
    }

    bool GameGrid::update() { 
        // TODO: check piece position
        //for now just bottom
        if( currentPiece->bottomCollision() ) {
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
        if(gameOver) return;
        currentPiece->handle(event);
        if(event.type == SDL_KEYDOWN) {
           switch(event.key.keysym.sym) {
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
        SDL_Color red = {255, 0, 0};
        SDL_Surface * scoreText = drawText(itoa(score), red);

        SDL_Rect r;
        r.x = offsetX;
        r.y = offsetY;

        SDL_BlitSurface(scoreText, NULL, screen, &r);

        SDL_FreeSurface(scoreText);
    }

    void GameGrid::checkLines() {
        // check the 4 lines covered by the piece, if any is full move all lines above
        // down 1 step
        int lineCount = 0;
        for(int i = currentPiece->getY(); i <= currentPiece->getBottomBound(); ++i) {
            bool lineFull = true;
            for(int j = 0; j < GRID_WIDTH; ++j) {
                if(grid[i][j] == NULL)
                    lineFull = false;
            }

            if(lineFull) {
                lineCount++;
                clearLine(i);
            }

            if(lineCount > 0)
                updateScore(lineCount);
        }
    }

    //set all blocks in line to null and move above lines
    void GameGrid::clearLine(int line){
        for(int j = 0; j < GRID_WIDTH; ++j)
            grid[line][j] = NULL;
        for(int i = line; i > 0; --i) {
            for(int j = 0; j < GRID_WIDTH; ++j) {
                grid[i][j] = grid[i-1][j];
            }
        }
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
        //if the currentPiece y position is too high up then game over
        if(currentPiece->getY() <= 2) {
            gameOver = true;
        }
        else {
            currentPiece->releaseBlocksToGrid();
            checkLines();
            genNewPieces();
            downTime = DEFAULT_DOWNTIME;
        }
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

    SDL_Surface * GameGrid::drawText(const char * text, SDL_Color col) {
        SDL_Surface * textSurf;
        if(!(textSurf = TTF_RenderText_Solid(scoreFont, text, col))) {
            std::cerr<<TTF_GetError()<<std::endl;
        }
        return textSurf;
    }
};

