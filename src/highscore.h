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

#ifndef NMUTILS_HIGHSCORE_H
#define NMUTILS_HIGHSCORE_H

#include<fstream>
#include<iostream>
#include<string>

using namespace std;

namespace NMUtils {
    /*
     * A class to wrap a score, consisting of score and name
     *
     * @version 1.0
     * @author Nikhil Marathe <nsm.nikhil@gmail.com>
     */
    class Score {
    private:
        enum {DELIM=' '};
        int score;
        string name;
    public:
        /**
         * Create a new Score object with score sc and name nam
         *
         * @param sc The score
         * @param nam Name
         */
        Score(int sc, string nam) {
            score = sc;
            name = nam;
        };

        int getScore() { return score; };
        string getName() { return name; };
        
        bool operator==(const Score &other) const {
            return score == other.score;
        };

        bool operator!=(const Score &other) const {
            return !(*this == other);
        };

		friend std::ostream& operator<< (std::ostream& os, const Score &s ) {
			return os<<s.score<<(char)DELIM<<s.name<<endl;
		};

        friend std::istream& operator>> (std::istream& in, Score &s ) {
            return in >> s.score >> s.name;
        };
    };

    class Highscore {
    private:
        fstream  * hs_file;

    public:
        Highscore(const char *);
        bool bad();

    };
};

#endif
