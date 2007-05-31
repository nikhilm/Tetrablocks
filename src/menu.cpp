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

    MenuItem::MenuItem(char * text, void (*callback)(SDL_Event &)) {
        itemText = text;
        actionCallback = callback;

        //foregroundNormal = SDL_MapRGB(
    }

    void MenuItem::setText(char *text) {
        itemText = text;
    }

    void MenuItem::setAction(void (*callback)(SDL_Event &)) {
        actionCallback = callback;
    }

};

