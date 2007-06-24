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
#include<ctime>

#include<SDL/SDL_image.h>

#include "blocks.h"

namespace TetraBlocks {
    class GameGrid;
    class Piece {
        public:
            //height, width in block terms
            enum { PIECE_SIZE = 4, NB_PIECES=7, NB_ROTATIONS=4};
            Block * layout[PIECE_SIZE][PIECE_SIZE];

            static  Piece * createRandomPiece(int x, int y, GameGrid *g) {
                srand(time(0));
                int index = rand()%NB_PIECES;
                return new Piece(x, y, index, COLOURS[index], g);
            };
            
            // NOTE: Called only by colours array to load images
            // this should not be used.
            // instead use the cached surfaces stored in the array
            static SDL_Surface * genImageSurface(char * colour) {
                std::string path = "../data/images/block_";
                path += colour;
                path += ".png";
                return IMG_Load(path.c_str());
            }

            void display(int, int, SDL_Surface * );
            
            void moveDown();

            void handle(SDL_Event &);

            int getX() { return x; };
            int getY() { return y; };
            void setX(int X) { x = X; };
            void setY(int Y) { y = Y; };

            bool bottomCollision();

            void releaseBlocksToGrid();
            int getBottomBound();

        private:
            GameGrid * ggrid;
            
            /**************************************************
             * SHAPES LAYOUT DESCRIPTION BEGINS               *
             * Their are 7 shapes. Each shape has 4 positions.*
             * Each position is represented by a 4x4 array    *
             *************************************************/
            static int SHAPES[NB_PIECES][PIECE_SIZE][PIECE_SIZE];
            
            
            static SDL_Surface * COLOURS[NB_PIECES];
            
            
            int x, y;

            SDL_Surface * colour;
            int shapeMap[NB_ROTATIONS][PIECE_SIZE][PIECE_SIZE];

            short currentOrientation;
            
            Piece(int, int, int, SDL_Surface * , GameGrid *);

            //bound related functions
            int getLeftBound();
            int getRightBound();

            //moving functions
            void movePiece(int, int);
            void moveSideways(int);

            void setNextOrientation();

            bool checkMovement(int, int);
            
    }; // class Piece
}; //namespace TetraBlocks
#endif
