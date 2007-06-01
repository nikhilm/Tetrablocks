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
    MenuItem::MenuItem(int x, int y, char * text, void (*callback)(SDL_Event &)) {
        itemText = text;
        actionCallback = callback;
        currentState = NORMAL;

        setX(x);
        setY(y);
        setDimensions(300, 75);
        setBorderWidth(5);

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

    SDL_Color MenuItem::createColor(int r, int g, int b) {
        SDL_Color col;
        col.r = r;
        col.g = g;
        col.b = b;
        return col;
    }

    SDL_Rect MenuItem::createRect(int x, int y, int w, int h) {
        SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = w;
        r.h = h;
        return r;
    }

    SDL_Rect MenuItem::getBackgroundRect() {
        return createRect(oX + borderWidth, oY + borderWidth, width - 2*borderWidth, height - 2*borderWidth);
    }

    Uint32 MenuItem::getMappedColor(SDL_Color col) {
        return SDL_MapRGB(surf->format, col.r, col.g, col.b);
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
        surf = screen;

        if(currentState == NORMAL)
            displayNormal();
        else if(currentState == HOVER)
            displayHover();
    }

    bool MenuItem::pointInsideThis(int pX, int pY) {
        return ( pX >= oX && pX <= (oX + width) && pY >= oY && pY <= (oY + height) );
    }

    void MenuItem::handle(SDL_Event &event) {
        if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT
                && pointInsideThis(event.button.x, event.button.y)) {
            actionCallback(event);
        }
        else if(event.type == SDL_MOUSEMOTION) {
            if(pointInsideThis(event.motion.x, event.motion.y)) {
                currentState = HOVER;
            }
            else {
                currentState = NORMAL;
            }
        }
    }

    void MenuItem::drawBorder() {
        SDL_FillRect(surf, &createRect(oX, oY, width, height), getMappedColor(borderNormal));
        //fill in the remaining with black
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(createColor(0, 0, 0)));

    }

    void MenuItem::displayNormal() {
        drawBorder();
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(backgroundNormal));
    }

    void MenuItem::displayHover() {
        drawBorder();
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(backgroundHover));
    }

};

