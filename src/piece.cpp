
#include "piece.h"
namespace TetraBlocks {
    Piece::SHAPES = {
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
        {{{0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0}},
        
         {{0, 0, 0, 0},
          {0, 1, 1, 1},
          {0, 0, 0, 1},
          {0, 0, 0, 0}},
        
         {{0, 1, 1, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 0, 0, 0}},
        
         {{0, 0, 0, 0},
          {1, 0, 0, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0}}}
    };
    
    Piece::COLOURS [7] = {
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
    
    Piece::Piece(int X, int Y, const int grid[PIECE_SIZE][PIECE_SIZE], SDL_Surface * colour) {
        for(int i = 0; i < PIECE_SIZE; ++i) {
            for(int j = 0; j < PIECE_SIZE; ++j) {
                layout[i][j] = NULL;
                if(grid[i][j] == 1) {
                    layout[i][j] = new Block(colour);
                    layout[i][j]->x = i;
                    layout[i][j]->y = j;
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
    };
}
            