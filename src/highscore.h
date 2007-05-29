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
#include<vector>

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

        /**
         * Creates an empty score object.
         * You should use operator>> to write to this
         *
         * @see operator>>
         */
        Score() {
            score = 0;
            name = "";
        }

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
        fstream hsFile;
        vector <Score> scoreList;
        
        int limit;

        void readIntoMemory() {
            hsFile.seekg(ios::beg);
            while(!hsFile.eof()) {
                if(hsFile.eof()) break;
                Score s;
                hsFile >> s;
                scoreList.push_back(s);
            }
            //last entry is empty, remove it
            scoreList.pop_back();
        };

    public:

        Highscore(const char * filename) {
            hsFile.open(filename);
            limit = -1;
            readIntoMemory();
        };

        void setLimit(int lim) {
            if(lim <= 0 && lim != -1) return;
            
            limit = lim;
        };

        vector<Score> getScores() { return vector<Score>(scoreList); };

    };
};

#endif
