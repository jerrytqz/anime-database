// database.cpp 

#include "database.h"

Database::Database(const std::string& file_name) 
: data_file(file_name), vec() {
    std::ifstream file; 
    std::string field; 
    std::vector<std::string> fields; 

    file.open(data_file); 
    while (std::getline(file, field)) {
        if (field.empty()) {
            Anime a(
                fields[0], 
                fields[1], 
                std::stoi(fields[2]), 
                std::stoi(fields[3]), 
                fields[4] == "true", 
                std::stod(fields[5])
            ); 
            vec.push_back(a);
            fields.clear();
        } else {
            fields.push_back(field); 
        } 
    }
    file.close(); 
}

Anime Database::get(int index) const {
    if (index < 0 || index >= vec.size()) {
        throw std::runtime_error("Database::get: index out of bounds"); 
    }
    return vec[index]; 
}

int Database::get_size() const { 
    return vec.size(); 
}

void Database::add(Anime a) {
    vec.push_back(a);
}

void Database::remove(std::vector<int>& indices, bool safe, bool copy) {
    if (copy) {
        std::vector<int> copy = indices; 
        remove(copy, safe, false); 
        return; 
    }
    if (indices.empty()) return; 
    std::sort(indices.begin(), indices.end());
    if (safe) {
        for (int i = 0; i < indices.size(); i++) {
            if (indices[i] < 0 || indices[i] >= vec.size()) {
                throw std::runtime_error("Database::remove: index out of bounds"); 
            }
        }
        if (std::adjacent_find(indices.begin(), indices.end()) != indices.end()) {
            throw std::runtime_error("Database::remove: indices must not contain duplicates"); 
        }
    }
    for (int i = indices.size() - 1; i >= 0; i--) {
        vec[indices[i]] = vec[vec.size() - 1];
        vec.pop_back(); 
    }
}

void Database::print(int index) const {
    if (index < 0 || index >= vec.size()) {
        throw std::runtime_error("Database::print: index out of bounds"); 
    }
    std::cout << vec[index];
}

void Database::println(int index) const {
    if (index < 0 || index >= vec.size()) {
        throw std::runtime_error("Database::println: index out of bounds"); 
    }
    std::cout << vec[index] << "\n";
}

void Database::list() const {
    if (vec.size() == 0) {
        std::cout << "Database is currently empty.\n"; 
        return; 
    }
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << "\n"; 
    }
}

void Database::sort_by_name(bool alphabetical) {
    if (alphabetical) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_name() < b.get_name(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_name() > b.get_name(); }
        );
    }
}

void Database::sort_by_studio(bool alphabetical) {
    if (alphabetical) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_studio() < b.get_studio(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_studio() > b.get_studio(); }
        );
    }
}

void Database::sort_by_num_episodes(bool ascending) {
    if (ascending) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_num_episodes() < b.get_num_episodes(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_num_episodes() > b.get_num_episodes(); }
        );
    }
}

void Database::sort_by_start_year(bool ascending) {
    if (ascending) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_start_year() < b.get_start_year(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_start_year() > b.get_start_year(); }
        );
    }
}

void Database::sort_by_airing(bool airing_first) {
    if (airing_first) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_airing() && !b.get_airing(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return !a.get_airing() && b.get_airing(); }
        );
    }
}

void Database::sort_by_score(bool ascending) {
    if (ascending) {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_score() < b.get_score(); }
        );
    } else {
        std::sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_score() > b.get_score(); }
        );
    }
}

std::vector<int> Database::search_by_name(const std::string& input, bool exact) const {
    std::vector<int> result; 
    if (exact) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_name() == input) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_name().find(input) != std::string::npos) result.push_back(i); 
        }
    }
    return result; 
}

std::vector<int> Database::search_by_studio(const std::string& input, bool exact) const {
    std::vector<int> result; 
    if (exact) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_studio() == input) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_studio().find(input) != std::string::npos) result.push_back(i); 
        }
    }
    return result; 
}

std::vector<int> Database::search_by_num_episodes(int input1, int input2) const {
    if (input1 > input2) {
        throw std::runtime_error("Database::search_by_num_episodes: invalid range"); 
    } 
    std::vector<int> result; 
    if (input1 == input2) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_num_episodes() == input1) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (input1 <= vec[i].get_num_episodes() && vec[i].get_num_episodes() <= input2) {
                result.push_back(i); 
            }
        }
    }
    return result; 
}

std::vector<int> Database::search_by_num_episodes(int input) const {
    return search_by_num_episodes(input, input); 
} 

std::vector<int> Database::search_by_start_year(int input1, int input2) const {
    if (input1 > input2) throw std::runtime_error("Database::search_by_start_year: invalid range"); 
    std::vector<int> result; 
    if (input1 == input2) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_start_year() == input1) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (input1 <= vec[i].get_start_year() && vec[i].get_start_year() <= input2) {
                result.push_back(i); 
            }
        }
    }
    return result; 
}

std::vector<int> Database::search_by_start_year(int input) const {
    return search_by_start_year(input, input); 
} 

std::vector<int> Database::search_by_airing(bool input) const {
    std::vector<int> result; 
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].get_airing() == input) result.push_back(i); 
    }
    return result; 
} 

std::vector<int> Database::search_by_score(double input1, double input2) const {
    if (input1 > input2) throw std::runtime_error("Database::search_by_score: invalid range"); 
    std::vector<int> result; 
    if (input1 == input2) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_score() == input1) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (input1 <= vec[i].get_score() && vec[i].get_score() <= input2) {
                result.push_back(i); 
            }
        }
    }
    return result; 
}

std::vector<int> Database::search_by_score(double input) const {
    return search_by_score(input, input); 
} 

Database::~Database() {
    std::cout << "Saving...\n"; 

    std::ofstream file; 
    
    file.open(data_file);
    file << std::fixed << std::setprecision(2); 
    for (int i = 0; i < vec.size(); i++) {
        file << vec[i].get_name() << "\n"
            << vec[i].get_studio() << "\n"
            << vec[i].get_num_episodes() << "\n"
            << vec[i].get_start_year() << "\n"
            << (vec[i].get_airing() ? "true" : "false") << "\n"
            << vec[i].get_score() << "\n\n";
    }
    file.close();

    std::cout << "Saved and quit successfully!\n"; 
}
