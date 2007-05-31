/******************************
 * highscore.h - manages high scores
 * Independent framework. Can be
 * used in other projects.
 *
 * Created - May 26, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#ifndef NMUTILS_MENUITEM_H
#define NMUTILS_MENUITEM_H

#include<iostream>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>

using namespace std;

namespace NMUtils {
    class MenuItem {
    private:
        char * itemText;
        void (*actionCallback)(SDL_Event &);

        //colours
        SDL_Color foregroundNormal, backgroundNormal, borderNormal, foregroundHover, backgroundHover, borderHover;

        int width, height;


    public:
        SDL_Color createColor(int r, int g, int b);
        MenuItem(char * text, void (*callback)(SDL_Event &));
        void setText(char *text);
        void setAction(void (*callback)(SDL_Event &));
        void setDimensions(int, int);

        void display(int, int, SDL_Surface * screen);
    };

};

#endif
