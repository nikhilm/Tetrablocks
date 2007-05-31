/******************************
 * menu.h - a menu framework
 * Independent framework. Can be
 * used in other projects.
 *
 * Created - May 26, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include "menu.h"

namespace NMUtils {
    SDL_Color MenuItem::createColor(int r, int g, int b) {
        SDL_Color col;
        col.r = r;
        col.g = g;
        col.b = b;
        return col;
    }

    MenuItem::MenuItem(int x, int y, char * text, void (*callback)(SDL_Event &)) {
        itemText = text;
        actionCallback = callback;

        setX(x);
        setY(y);
        setDimensions(300, 75);

        //foregroundNormal = SDL_MapRGB(
        setBackground(createColor(255, 0, 0));
    }

    void MenuItem::setText(char *text) {
        itemText = text;
    }

    void MenuItem::setAction(void (*callback)(SDL_Event &)) {
        actionCallback = callback;
    }

    void MenuItem::setDimensions(int w, int h) {
        width = w;
        height = h;
    }

    void MenuItem::display(SDL_Surface *screen) {
        SDL_Rect r;
        r.x = oX;
        r.y = oY;
        r.w = width;
        r.h = height;

        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, backgroundNormal.r, backgroundNormal.g, backgroundNormal.b));
    };

};

