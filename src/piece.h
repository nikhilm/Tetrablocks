/******************************
 * piece.h - Piece class
 * Created - May 15, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_PIECE_H
#define TB_PIECE_H

#include<iostream>
#include<string>
#include<cstdlib>

#include<SDL/SDL_image.h>

#include "blocks.h"

namespace TetraBlocks {
    class Piece {
        private:
            //height, width in block terms
            enum { PIECE_SIZE = 4, NB_PIECES=7};
            
            /**************************************************
             * SHAPES LAYOUT DESCRIPTION BEGINS               *
             * Their are 7 shapes. Each shape has 4 positions.*
             * Each position is represented by a 4x4 array    *
             *************************************************/
            static int SHAPES[NB_PIECES][4][4][4];
            
            
            static SDL_Surface * COLOURS[NB_PIECES];
            
            
            Block * layout[PIECE_SIZE][PIECE_SIZE];
            int x, y;
            
            Piece(int, int, int [PIECE_SIZE][PIECE_SIZE], SDL_Surface * );
            
        public:
            static  Piece * createRandomPiece(int x, int y) {
                int index = rand()%NB_PIECES;
                return new Piece(x, y, SHAPES[index][0], COLOURS[index]);
            };
            
            // NOTE: Called only by colours array to load images
            // this should not be used.
            // instead use the cached surfaces stored in the array
            static SDL_Surface * genImageSurface(char * colour) {
                std::string path = "../images/block_";
                path += colour;
                path += ".png";
                return IMG_Load(path.c_str());
            }

            void display(int, int, SDL_Surface * );
            
            void moveDown();
    }; // class Piece
}; //namespace TetraBlocks
#endif
