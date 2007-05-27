/******************************
 * highscore.cpp - manages high scores
 * Independent framework. Can be
 * used in other projects.
 *
 * Created - May 26, 2007
 *
 * (C) Nikhil Marathe <nsm.nikhil@gmail.com>
 * Licensed under the GNU GPL
 */

#include "highscore.h"

namespace NMUtils {
    /**
     * Creates a new Highscore service to
     * read and write from file filename.
     * You should call Highscore::bad()
     * before attempting IO operations.
     *
     * @param filename The filename to read and write highscores from
     */
    Highscore::Highscore(const char * filename) {
        hs_file = new fstream(filename); 
    }

    bool Highscore::bad() { return hs_file->bad(); }

};

