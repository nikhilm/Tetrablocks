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
    char * MenuItem::fontName = "../data/DejaVuSans.ttf";
    TTF_Font * MenuItem::font = loadFont(MenuItem::fontName, 20);
    
    MenuItem::MenuItem(int x, int y, char * text, void (*callback)(SDL_Event &)) {
        itemText = text;
        actionCallback = callback;
        currentState = NORMAL;

        setX(x);
        setY(y);
        setDimensions(300, 75);
        setBorderWidth(5);

        //default white and black theme
        SDL_Color white = createColor(255, 255, 255);
        SDL_Color black = createColor(0, 0, 0);
        SDL_Color red = createColor(255, 0, 0);
        setForeground(white);
        setBackground(black);
        setBorder(white);

        setForegroundHover(red);
        setBackgroundHover(black);
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

    TTF_Font * MenuItem::loadFont(char * file, int size) {
        //try loading SDL_ttf
        if(!TTF_WasInit() && TTF_Init() == -1) {
            cerr<<"Error initializing SDL_ttf library, cannot draw text. Error: "<<TTF_GetError()<<endl;
        }

        TTF_Font *f = TTF_OpenFont(file, size);
        if(!f) {
            cout<<"Error loading font file"<<TTF_GetError()<<"\n";
        }
        return f;
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
        SDL_FillRect(surf, &createRect(oX, oY, width, height), getMappedColor((currentState == NORMAL ? borderNormal : borderHover)));
        //fill in the remaining with black
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(createColor(0, 0, 0)));

    }

    void MenuItem::displayNormal() {
        drawBorder();
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(backgroundNormal));
        drawText();
    }

    void MenuItem::displayHover() {
        drawBorder();
        SDL_FillRect(surf, &getBackgroundRect(), getMappedColor(backgroundHover));
        drawText();
    }

    void MenuItem::drawText() {
        SDL_Surface * textSurf;
        if(!(textSurf = TTF_RenderText_Solid(font, itemText, ( currentState == NORMAL ? foregroundNormal : foregroundHover ))))
            cout<<TTF_GetError();

        //calculate the centre
        int textSurfWidth = textSurf->w;
        int textSurfHeight = textSurf->h;

        int thisCenterX = oX + width/2;
        int thisCenterY = oY + height/2;

        SDL_Rect r;
        r.x = thisCenterX - textSurfWidth/2;
        r.y = thisCenterY - textSurfHeight/2;
        r.w = textSurfWidth;
        r.h = textSurfHeight;

        SDL_BlitSurface(textSurf, NULL, surf, &r);

        SDL_FreeSurface(textSurf);
    }

};

