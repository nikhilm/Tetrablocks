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

        //default red and black theme
        SDL_Color red = createColor(255, 0, 0);
        SDL_Color black = createColor(0, 0, 0);
        setForeground(red);
        setBackground(black);
        setBorder(red);

        setForegroundHover(black);
        setBackgroundHover(red);
        setBorderHover(red);
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
    }

    bool MenuItem::pointInsideThis(int pX, int pY) {
        return ( pX >= oX && pX <= (oX + width) && pY >= oY && pY <= (oY + height) );
    }

    void MenuItem::handle(SDL_Event &event) {
        if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            if(pointInsideThis(event.button.x, event.button.y)) {
                toggleState();
            }
        }
    }

    void MenuItem::toggleState() {
        if(currentState == NORMAL)
            currentState = HOVER;
        else if(currentState == HOVER)
            currentState = NORMAL;
    }
};

