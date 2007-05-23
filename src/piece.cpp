/******************************
 * piece.cpp - Piece class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include "piece.h"

namespace TetraBlocks {
     int Piece::SHAPES[NB_PIECES][4][4][4] = {
        // I shape
        {{{0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0}},
        
         {{0, 0, 0, 0},
          {1, 1, 1, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0}},
        
         {{0, 0, 0, 0},
          {0, 0, 0, 0},
          {1, 1, 1, 1},
          {0, 0, 0, 0}}},
        
        // J shape
        {{{0, 1, 1, 1},
          {0, 0, 0, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0}},
        
         {{0, 1, 1, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {1, 0, 0, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0}}},

        // L shape
        {{{1, 1, 1, 0},
          {1, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 1},
          {0, 1, 1, 1}},

         {{0, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 1, 0}},

         {{0, 1, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 0, 0}}},

        // O shape
        {{{0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
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

         {{0, 0, 0, 0},
          {0, 1, 1, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0}}},

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
          {0, 1, 0, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0}}},

        // Z shape
        {{{1, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0}},

         {{0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 1, 0, 0}},

         {{0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 1},
          {0, 0, 0, 0}},

         {{0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 1, 0, 0},
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
    
    Piece::Piece(int X, int Y, int grid[PIECE_SIZE][PIECE_SIZE], SDL_Surface * colour) {
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                layout[i][j] = NULL;
                if(grid[i][j] == 1) {
                    layout[i][j] = new Block(colour);
                    layout[i][j]->x = j;
                    layout[i][j]->y = i;
                }
            }
        }
        x = X;
        y = Y;
    };
    
    void Piece::moveDown() {
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    layout[i][j]->y++;
                }
            }
        }
    }

    // moves all blocks left if number is -ve, right if +ve
    void Piece::moveSideways(int side) {
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    layout[i][j]->x += ( side < 0 ? -1 : 1 );
                }
            }
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
                default:break;
            }
        }
    }


    void Piece::display(int offsetX, int offsetY, SDL_Surface * screen) {
        int drawX = offsetX + x * Block::WIDTH;
        int drawY = offsetY + y * Block::HEIGHT;
        //std::cout<<"Drawing piece at ("<<drawX<<", "<<drawY<<")\n";
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                if(layout[i][j] != NULL) {
                    layout[i][j]->display(drawX, drawY, screen);
                }
            }
        }
    }
}
            
