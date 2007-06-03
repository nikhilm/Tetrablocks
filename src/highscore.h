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

        /**
         * Returns instance's score.
         */
        int getScore() { return score; };
        /**
         * Returns instance's name.
         */
        string getName() { return name; };
        
        bool operator==(const Score &other) const {
            return score == other.score;
        };

        bool operator!=(const Score &other) const {
            return !(*this == other);
        };

        bool operator<(const Score &other) const {
            return other.score < score;
        };

		friend std::ostream& operator<< (std::ostream& os, const Score &s ) {
			return os<<s.score<<(char)DELIM<<s.name<<endl;
		};

        friend std::istream& operator>> (std::istream& in, Score &s ) {
            return in >> s.score >> s.name;
        };
    };

    /**
     * A Highscore is a utility class to manage high scores lists.
     */
    class Highscore {
    private:
        vector <Score> scoreList;
        const char * fileName;
        
        int limit;

        void readIntoMemory() {
            ifstream hsFileRead(fileName);
            if(hsFileRead.bad()) 
                cout<<"Error opening file for reading\n";
            hsFileRead.seekg(ios::beg);
            while(!hsFileRead.eof()) {
                if(hsFileRead.eof()) break;
                Score s;
                hsFileRead >> s;
                scoreList.push_back(s);
            }
            //last entry is empty, remove it
            scoreList.pop_back();
            hsFileRead.close();
        };

    public:

        /**
         * Creates a new Highscore. Any existing scores
         * are read in from the file filename.
         *
         * @param filename The file to read/write to
         */
        Highscore(const char * filename) {
            fileName = filename;
            limit = -1;
            readIntoMemory();
        };

        /**
         * Sets a limit on the number of highscores stored.
         * If you want to keep no limit, then pass -1 (default).
         *
         * Note: Setting a limit will not immediately wipe lower
         * scores from the list. The limit is obeyed only on the
         * call to write()
         *
         * @see write
         *
         * @param limit The limit
         */
        void setLimit(int lim) {
            if(lim <= 0 && lim != -1) return;
            
            limit = lim;
        };

        /**
         * Returns a vector with all the current scores
         */
        vector<Score> getScores() { return vector<Score>(scoreList); };

        /**
         * Adds a new score to the list.
         *
         * @param score The score
         * @param name The scorers name
         */
        void addScore(int score, string name) {
            addScore(Score(score, name));
        };

        /**
         * Adds the Score object to the list
         */
        void addScore(Score s) {
            scoreList.push_back(s);
        };

        /**
         * Removes the Score where score matches a Score's score.
         */
        bool removeScore(int score) {
            return removeScore(Score(score, ""));
        };

        bool removeScore(Score score) {
            vector<Score>::iterator it = find(scoreList.begin(), scoreList.end(), score);
            cout<<*scoreList.erase(it);
        };

        /**
         * Returns the Score with the highest score
         */
        Score getHighestScore() {
            sort(scoreList.begin(), scoreList.end());
            return scoreList[0];
        };

        /**
         * Writes out the new scores to the file.
         * You should call close to commit changes.
         */
        void write() {
            ofstream hsFileWrite(fileName);
            if(hsFileWrite.bad())
                cout<<"Could not open file for writing\n";
            for(int i = 0; i < scoreList.size(); ++i) {
                if(limit != -1 && i > limit-1) break;
                hsFileWrite<<scoreList[i];
            }
            hsFileWrite.close();
        };

    };
};

#endif
