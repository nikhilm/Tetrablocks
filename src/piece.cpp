/******************************
 * piece.cpp - Piece class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include "gamegrid.h"
#include "piece.h"

namespace TetraBlocks {
     int Piece::SHAPES[NB_PIECES][NB_ROTATIONS][PIECE_SIZE][PIECE_SIZE] = {
        // I shape
        {{{0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0}},
        
         {{0, 0, 0, 0},
          {1, 1, 1, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},
        
         {{0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0}},
        
         {{0, 0, 0, 0},
          {1, 1, 1, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0}}},
        
        // J shape
        {{{0, 1, 1, 1},
          {0, 0, 0, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 1, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 1, 1},
          {0, 0, 0, 0}},

         {{0, 0, 0, 1},
          {0, 0, 0, 1},
          {0, 0, 1, 1},
          {0, 0, 0, 0}}},
        

        // L shape
        {{{1, 1, 1, 0},
          {1, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{1, 0, 0, 0},
          {1, 0, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 1, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0}},

         {{0, 1, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 0, 0}}},

        // O shape
        {{{0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0}}},

        // S shape
        {{{0, 0, 1, 1},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 0, 0}},

         {{0, 0, 1, 1},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 0, 0}}},

        // T shape
        {{{0, 1, 1, 1},
          {0, 0, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 1},
          {0, 0, 0, 0}},

         {{0, 0, 0, 1},
          {0, 0, 1, 1},
          {0, 0, 0, 1},
          {0, 0, 0, 0}}},

        // Z shape
        {{{1, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 0, 0},
          {1, 1, 0, 0},
          {1, 0, 0, 0},
          {0, 0, 0, 0}},

         {{1, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 1, 0, 0},
          {1, 1, 0, 0},
          {1, 0, 0, 0},
          {0, 0, 0, 0}}}
    };
    
     SDL_Surface * Piece::COLOURS[NB_PIECES] = {
        // I = red
        genImageSurface("red"),
        // J = yellow
        genImageSurface("yellow"),
        // L = magenta
        genImageSurface("magenta"),
        // O = blue
        genImageSurface("blue"),
        // S = cyan
        genImageSurface("cyan"),
        // T = green
        genImageSurface("green"),
        // Z = orange
        genImageSurface("orange")
    };
    
    Piece::Piece(int X, int Y, int shapeIndex, SDL_Surface * col) {
        for(int k = 0; k < NB_ROTATIONS; ++k)
            for(int i = 0; i < PIECE_SIZE; ++i)
                for(int j = 0; j < PIECE_SIZE; ++j) {
                    shapeMap[k][i][j] = Piece::SHAPES[shapeIndex][k][i][j];
                }
        colour = col;
        currentOrientation = -1;
        x = X;
        y = Y;
        setNextOrientation();
    };

    void Piece::setNextOrientation() {
        currentOrientation = (currentOrientation + 1)%NB_ROTATIONS;
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                layout[i][j] = NULL;
                if(shapeMap[currentOrientation][i][j] == 1) {
                    layout[i][j] = new Block(colour);
                }
            }
        }
    }
    
    void Piece::moveDown() {
        y++;
    }

    int Piece::getLeftBound() {
        int bound = GameGrid::GRID_WIDTH;
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    if(i < bound)
                        bound = i;
                }
            }
        }
        return bound;
    }

    int Piece::getRightBound() {
        int bound = 0;
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    if(i > bound)
                        bound = i;
                }
            }
        }
        return bound;
    }

    int Piece::getBottomBound() {
        int bound = 0;
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    if(j > bound)
                        bound = j;
                }
            }
        }
        return bound+y;
    }

    bool Piece::bottomCollision() {
        return getBottomBound() >= GameGrid::GRID_HEIGHT;
    }

    //handles updating coordinates of piece and its blocks
    void Piece::movePiece(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }

    // moves all blocks left if number is -ve, right if +ve
    void Piece::moveSideways(int side) {
        if( side < 0 && getLeftBound() > 0 ) {
            movePiece(-1, 0);
        }
        else if( side > 0 && getRightBound() < GameGrid::GRID_WIDTH - 1 ) {
            movePiece(1, 0);
        }
    }

    void Piece::handle(SDL_Event &event) {
        if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    moveSideways(-1);
                    break;
                case SDLK_RIGHT:
                    moveSideways(1);
                    break;
                case SDLK_UP:
                    setNextOrientation();
                    break;
                default:break;
            }
        }
    }

    void Piece::display(int offsetX, int offsetY, SDL_Surface * screen) {
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    layout[i][j]->display(offsetX + x*Block::WIDTH + i * Block::WIDTH, offsetY + y*Block::HEIGHT + j * Block::HEIGHT, screen);
                }
            }
        }
    }
}
            
