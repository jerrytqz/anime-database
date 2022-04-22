// anime.h

#ifndef ANIME_H
#define ANIME_H

#include <iostream> 
#include <string>

using namespace std;

class Anime {
private: 
    string name; 
    string studio; 
    int num_episodes; 
    int start_year; 
    bool airing; 
    double score; 

public: 
    Anime(const string& n, const string& st, int n_e, int s_y, bool a, double sc);

    string get_name() const;

    string get_studio() const;

    int get_num_episodes() const;

    int get_start_year() const;

    bool get_airing() const;
    
    double get_score() const; 

    // Returns the score as a string (to exactly 2 decimal places).
    string get_score_string() const; 

    string string_form() const; 
};

// Prints out a record with its fields separated by commas and spaces.
ostream& operator<<(ostream& out, const Anime& a); 

#endif
