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
    /**
     * MenuItem is a class implementing a menu item in SDL.
     * It requires the SDL and SDL_ttf libraries to be installed.
     *
     * MenuItem can be used independently or through the Menu class.
     * MenuItem is quite customisable and allows inheritance to add custom behaviour
     * such as the use of images or fancy effects.
     *
     * Most commonly you will just want to use MenuItem as is, specifying only the text
     * and the callback.
     * The callback should be a function with the following prototype
     * <code>
     * void <function name>(SDL_Event &)
     * </code>
     *
     * If using MenuItem on its own you should ensure that your event loop passes
     * all events to its handle() method and that you call MenuItem's display() method.
     *
     * Here is an example
     * <code>
     * //other includes
     * #include "menu.h"
     *
     * void main() {
     *     ... initialization code...
     *     MenuItem item(100, 50, "Click Here", helloWorld);
     *     
     *     //begin loop
     *     while(true) {
     *     while(SDL_PollEvent(&event)) {
     *         item.handle(event);
     *         item2.handle(event);
     *        
     *     }
     *     item.display(screen);
     *     ... more code...
     * }
     * </code>
     *
     * To customise the Look 'N' Feel of the MenuItem reimplement the
     * displayNormal() and displayHover() methods.
     * Draw on the SDL_Surface surf which is a class member.
     */         
    class MenuItem {
    private:

        enum State { NORMAL, HOVER};

        State currentState;
        
        char * itemText;
        void (*actionCallback)(SDL_Event &);

        //colours
        SDL_Color foregroundNormal, backgroundNormal, borderNormal, foregroundHover, backgroundHover, borderHover;

        int width, height, borderWidth;

        static char * fontName;
        static TTF_Font * font;

        //X and Y offsets set by Constructor 
        //display surface, set by display before calling other display functions
        int oX, oY;
        SDL_Surface * surf;

        Uint32 getMappedColor(SDL_Color);

        SDL_Rect getBackgroundRect();

        static TTF_Font *loadFont(char *, int);

    protected:
        /**
         * Draws the border around the MenuItem
         */
        void drawBorder();
        /**
         * Draws the text
         */
        void drawText();
        /**
         * Draws the menu item in the 'normal' state when the mouse is not over it.
         */
        void displayNormal();
        /**
         * Draws the menu item in the 'hover' state when the mouse is over it.
         */
        void displayHover();

    public:
        MenuItem(int x, int y, char * , void (*callback)(SDL_Event &));

        static SDL_Color createColor(int r, int g, int b);
        static SDL_Rect createRect(int, int, int, int);

        void setText(char *);
        void setAction(void (*callback)(SDL_Event &));
        void setDimensions(int, int);

        void display(SDL_Surface *);

        void handle(SDL_Event&);

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

        void setX(int x) {
            oX = x;
        };

        void setY(int y) {
            oY = y;
        };

        void setWidth(int w) {
            width = w;
        };

        void setHeight(int h) {
            height = h;
        };

        int getWidth() {
            return width;
        };

        int getHeight() {
            return height;
        };

        void setFontSize(int size) {
            font = loadFont(fontName, size);
        };
    };


    class Menu {
    private:
        vector<MenuItem> menuItems;
        int x, int y;

        int paddingY;

    public:
        Menu(int X, int Y) {
            x = X;
            y = Y;
            paddingX = 10;
        };

        void addItem(char * text, void (*callback)(SDL_Event &)) {
            addItem(0, 0, text, callback);
        };

        void addItem(MenuItem m) {
            m.setX(x);
            menuItems.push_back(m);
        };

        void removeItem(int index) {
            if(index < 0 || index >= menuItems.size()) return;
            
            menuItems.remove(index);
        };

        void display(SDL_Surface * surf) {
            int dispY = y;
            for(int i = 0; i < menuItems.size(); ++i) {
                menuItems[i].setY(dispY);
                menuItems[i].display(surf);

                dispY += menuItems[i].getHeight() + padding;
            }
        };

        void handle(SDL_Event & event) {
            for(int i = 0; i < menuItems.size(); ++i) {
                menuItems[i].handle(event);
            }
        };
    };
};

#endif
