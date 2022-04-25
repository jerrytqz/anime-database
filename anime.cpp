// anime.cpp 

#include "anime.h" 

Anime::Anime(const std::string& n, const std::string& st, int n_e, int s_y, bool a, double sc)
: name(n), studio(st), num_episodes(n_e), start_year(s_y), airing(a), score(sc) {}

std::string Anime::get_name() const { return name; }

std::string Anime::get_studio() const { return studio; }

int Anime::get_num_episodes() const { return num_episodes; }

int Anime::get_start_year() const { return start_year; }

bool Anime::get_airing() const { return airing; }

double Anime::get_score() const { return score; }

std::string Anime::get_score_string() const { 
    return (
        score == 10.00 ? std::to_string(score).substr(0, 5) : std::to_string(score).substr(0, 4)
    ); 
}

std::string Anime::string_form() const {
    std::string result = (
        name + ", " 
        + studio + ", " 
        + std::to_string(num_episodes) + ", " 
        + std::to_string(start_year) + ", " 
        + (airing ? "true" : "false") + ", " 
        + Anime::get_score_string()
    ); 
    return result; 
}

std::ostream& operator<<(std::ostream& out, const Anime& a) {
    out << a.get_name() << ", "
        << a.get_studio() << ", "
        << a.get_num_episodes() << ", "
        << a.get_start_year() << ", "
        << (a.get_airing() ? "true" : "false") << ", "
        << a.get_score_string(); 
    return out; 
}
