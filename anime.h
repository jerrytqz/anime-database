// anime.h

#ifndef ANIME_H
#define ANIME_H

#include <iostream> 
#include <string>

class Anime {
private: 
    std::string name; 
    std::string studio; 
    int num_episodes; 
    int start_year; 
    bool airing; 
    double score; 

public: 
    static const int NUM_FIELDS = 6;

    Anime(const std::string& n, const std::string& st, int n_e, int s_y, bool a, double sc);

    std::string get_name() const;

    std::string get_studio() const;

    int get_num_episodes() const;

    int get_start_year() const;

    bool get_airing() const;
    
    double get_score() const; 

    // Returns the score as a string (to exactly 2 decimal places).
    std::string get_score_string() const; 

    std::string string_form() const; 
};

// Prints out a record with its fields separated by commas and spaces.
std::ostream& operator<<(std::ostream& out, const Anime& a); 

#endif
