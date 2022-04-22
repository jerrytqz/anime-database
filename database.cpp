// database.cpp 

#include "database.h"

using namespace std; 

Database::Database(const string& file_name) 
: data_file(file_name), vec() {
    ifstream file; 
    string field; 
    vector<string> fields; 

    file.open(data_file); 
    while (getline(file, field)) {
        if (field.empty()) {
            Anime a(
                fields[0], 
                fields[1], 
                stoi(fields[2]), 
                stoi(fields[3]), 
                fields[4] == "true", 
                stod(fields[5])
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
    if (index < 0 || index >= vec.size()) throw runtime_error("Database::get: index out of bounds"); 
    return vec[index]; 
}

int Database::get_size() const { 
    return vec.size(); 
}

void Database::add(Anime a) {
    vec.push_back(a);
}

void Database::remove(vector<int>& indices, bool safe, bool copy) {
    if (copy) {
        vector<int> copy = indices; 
        remove(copy, safe, false); 
        return; 
    }
    if (indices.empty()) return; 
    sort(indices.begin(), indices.end());
    if (safe) {
        for (int i = 0; i < indices.size(); i++) {
            if (indices[i] < 0 || indices[i] >= vec.size()) {
                throw runtime_error("Database::remove: index out of bounds"); 
            }
        }
        if (adjacent_find(indices.begin(), indices.end()) != indices.end()) {
            throw runtime_error("Database::remove: indices must not contain duplicates"); 
        }
    }
    for (int i = indices.size() - 1; i >= 0; i--) {
        vec[indices[i]] = vec[vec.size() - 1];
        vec.pop_back(); 
    }
}

void Database::print(int index) const {
    if (index < 0 || index >= vec.size()) {
        throw runtime_error("Database::print: index out of bounds"); 
    }
    cout << vec[index];
}

void Database::println(int index) const {
    if (index < 0 || index >= vec.size()) {
        throw runtime_error("Database::println: index out of bounds"); 
    }
    cout << vec[index] << "\n";
}

void Database::list() const {
    if (vec.size() == 0) {
        cout << "Database is currently empty.\n"; 
        return; 
    }
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "\n"; 
    }
}

void Database::sort_by_studio(bool alphabetical) {
    if (alphabetical) {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_studio() < b.get_studio(); }
        );
    } else {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_studio() > b.get_studio(); }
        );
    }
}

void Database::sort_by_name(bool alphabetical) {
    if (alphabetical) {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_name() < b.get_name(); }
        );
    } else {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_name() > b.get_name(); }
        );
    }
}

void Database::sort_by_score(bool ascending) {
    if (ascending) {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_score() < b.get_score(); }
        );
    } else {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_score() > b.get_score(); }
        );
    }
}

void Database::sort_by_num_episodes(bool ascending) {
    if (ascending) {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_num_episodes() < b.get_num_episodes(); }
        );
    } else {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_num_episodes() > b.get_num_episodes(); }
        );
    }
}

void Database::sort_by_start_year(bool ascending) {
    if (ascending) {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_start_year() < b.get_start_year(); }
        );
    } else {
        sort(
            vec.begin(), 
            vec.end(), 
            [](Anime a, Anime b) { return a.get_start_year() > b.get_start_year(); }
        );
    }
}

vector<int> Database::search_by_name(const string& input, bool exact) const {
    vector<int> result; 
    if (exact) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_name() == input) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_name().find(input) != string::npos) result.push_back(i); 
        }
    }
    return result; 
}

vector<int> Database::search_by_studio(const string& input, bool exact) const {
    vector<int> result; 
    if (exact) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_studio() == input) result.push_back(i); 
        }
    } else {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].get_studio().find(input) != string::npos) result.push_back(i); 
        }
    }
    return result; 
}

vector<int> Database::search_by_num_episodes(int input1, int input2) const {
    if (input1 > input2) throw runtime_error("Database::search_by_num_episodes: invalid range"); 
    vector<int> result; 
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

vector<int> Database::search_by_num_episodes(int input) const {
    return search_by_num_episodes(input, input); 
} 

vector<int> Database::search_by_start_year(int input1, int input2) const {
    if (input1 > input2) throw runtime_error("Database::search_by_start_year: invalid range"); 
    vector<int> result; 
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

vector<int> Database::search_by_start_year(int input) const {
    return search_by_start_year(input, input); 
} 

vector<int> Database::search_by_airing(bool input) const {
    vector<int> result; 
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].get_airing() == input) result.push_back(i); 
    }
    return result; 
} 

vector<int> Database::search_by_score(double input1, double input2) const {
    if (input1 > input2) throw runtime_error("Database::search_by_score: invalid range"); 
    vector<int> result; 
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

vector<int> Database::search_by_score(double input) const {
    return search_by_score(input, input); 
} 

Database::~Database() {
    cout << "Saving...\n"; 

    ofstream file; 
    
    file.open(data_file);
    file << fixed << setprecision(2); 
    for (int i = 0; i < vec.size(); i++) {
        file << vec[i].get_name() << "\n"
            << vec[i].get_studio() << "\n"
            << vec[i].get_num_episodes() << "\n"
            << vec[i].get_start_year() << "\n"
            << (vec[i].get_airing() ? "true" : "false") << "\n"
            << vec[i].get_score() << "\n\n";
    }
    file.close();

    cout << "Quit successfully!\n"; 
}
