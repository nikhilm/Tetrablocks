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

        enum State { NORMAL, HOVER};

        State currentState;
        
        char * itemText;
        void (*actionCallback)(SDL_Event &);

        //colours
        SDL_Color foregroundNormal, backgroundNormal, borderNormal, foregroundHover, backgroundHover, borderHover, textNormal, textHover;

        int width, height, borderWidth;

        //X and Y offsets set by Constructor 
        //display surface, set by display before calling other display functions
        int oX, oY;
        SDL_Surface * surf;

    protected:
        void drawBorder();
        void drawText();
        void displayNormal();
        void displayHover();

    public:
        MenuItem(int x, int y, char * , void (*callback)(SDL_Event &));

        SDL_Color createColor(int r, int g, int b);
        void setText(char *);
        void setAction(void (*callback)(SDL_Event &));
        void setDimensions(int, int);

        void display(SDL_Surface *);

        void handle(SDL_Event &);

        bool pointInsideThis(int, int);

        //setters
        void setBackground(SDL_Color col) {
            backgroundNormal = col;
        };

        void setForeground(SDL_Color col) {
            foregroundNormal = col;
        };

        void setBorder(SDL_Color col) {
            borderNormal = col;
        };

        void setBackgroundHover(SDL_Color col) {
            backgroundHover = col;
        };

        void setForegroundHover(SDL_Color col) {
            foregroundHover = col;
        };

        void setBorderHover(SDL_Color col) {
            borderHover = col;
        };

        void setBorderWidth(int width) {
            borderWidth = width;
        };

        void setTextColor(SDL_Color col) {
            textNormal = col;
        };

        void setTextHoverColor(SDL_Color col) {
            textHover = col;
        };

        void setX(int x) {
            oX = x;
        };

        void setY(int y) {
            oY = y;
        };
    };

};

#endif
