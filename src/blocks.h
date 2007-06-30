/******************************
 * blocks.h - Block definition
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_BLOCKS_H
#define TB_BLOCKS_H

#include<iostream>
#include<SDL/SDL.h>


namespace TetraBlocks {
    class Block {
    private:
        SDL_Color colour;

    public:
        enum {WIDTH = 20, HEIGHT = 20};
        
        Block(SDL_Color col) { colour = col; };
        /**
         * Draws the block.
         * offsetX and offsetY should be absolute coordinates.
         * They will be added to the block's absolute positions
         */
        void display(int offsetX, int offsetY, SDL_Surface * screen) {
            SDL_Rect r;
            r.x = offsetX;
            r.y = offsetY;
            r.w = WIDTH-1;
            r.h = HEIGHT-1;
            SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, colour.r, colour.g, colour.b));
        }
    };
};

#endif // TB_BLOCKS_H
