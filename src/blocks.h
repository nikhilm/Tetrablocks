/******************************
 * blocks.h - Block definition
 * Created - May 18, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef TB_BLOCKS_H
#define TB_BLOCKS_H
#include<SDL/SDL.h>


namespace TetraBlocks {
    class Block {
    private:
        SDL_Surface * image;

    public:
        enum {WIDTH = 20, HEIGHT = 20};
        int x, y;

        Block(SDL_Surface * img) { image = img; };
        /**
         * Draws the block.
         * offsetX and offsetY should be absolute coordinates.
         * They will be added to the block's absolute positions
         */
        void display(int offsetX, int offsetY, SDL_Surface * screen) {
            SDL_Rect r;
            r.x = offsetX + x*WIDTH;
            r.y = offsetY + y*HEIGHT;
            SDL_BlitSurface(image, NULL, screen, &r);
        }
    };
};

#endif // TB_BLOCKS_H