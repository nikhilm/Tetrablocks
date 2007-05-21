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
            enum { PIECE_SIZE = 4};
            
            /**************************************************
             * SHAPES LAYOUT DESCRIPTION BEGINS               *
             * Their are 7 shapes. Each shape has 4 positions.*
             * Each position is represented by a 4x4 array    *
             *************************************************/
            static int SHAPES[2][4][4][4];
            
            
            static SDL_Surface * COLOURS[7];
            
            
            Block * layout[PIECE_SIZE][PIECE_SIZE];
            int x, y;
            
            Piece(int, int, int [PIECE_SIZE][PIECE_SIZE], SDL_Surface * );
            
            void moveDown();
            
        public:
            static  Piece * createRandomPiece(int x, int y) {
                int index = rand()%2;
                int subIndex = rand()%4;
                std::cout<<index<<" "<<subIndex<<std::endl;
                return new Piece(x, y, SHAPES[index][subIndex], COLOURS[index]);
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
    }; // class Piece
}; //namespace TetraBlocks
#endif
