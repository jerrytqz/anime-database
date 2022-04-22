// database.h

#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <algorithm> 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <iomanip>
#include <stdexcept>

#include "anime.h" 

using namespace std; 

class Database {
private: 
    string data_file; 
    vector<Anime> vec; 

public: 
    // Constructor that initializes a Database object by reading the data from a file. An entry in
    // the file should be formatted like so: 
    // The name of the anime 
    // The studio that created the anime 
    // Current number of episodes
    // Year the anime started airing
    // Whether the anime is still airing ("true" or "false")
    // Score of the anime on MyAnimeList
    // EMPTY LINE
    Database(const string& file_name); 

    // Returns a copy of the record at index. Throws an error if index is out of bounds. 
    Anime get(int index) const; 

    int get_size() const; 

    void add(Anime a); 

    // Removes the records at the indices specified in the vector. If indices is not in ascending
    // order, it will be modified to be so, unless copy is true. If safe is true, an error will be 
    // thrown if any index is out of bounds or if there are any duplicates in indices. 
    void remove(vector<int>& indices, bool safe = true, bool copy = false); 

    // Prints out the record at index using cout. Throws an error if index is out of bounds. 
    void print(int index) const; 

    // Prints out the record at index using cout and adds \n at the end. Throws an error if index 
    // is out of bounds. 
    void println(int index) const; 

    // Prints out all records in the database using cout, one per line. If the database is empty, 
    // a message indicating so is printed. 
    void list() const;

    // Sorts the database by the name of each anime. This will be done alphabetically if 
    // alphabetical is true, otherwise it will be done reverse alphabetically. 
    void sort_by_name(bool alphabetical); 

    // Sorts the database by the studio name of each anime. This will be done alphabetically if 
    // alphabetical is true, otherwise it will be done reverse alphabetically. 
    void sort_by_studio(bool alphabetical);

    // Sorts the database by the number of episodes of each anime. This will be done in ascending 
    // order if ascending is true, otherwise it will be done in descending order. 
    void sort_by_num_episodes(bool ascending); 

    // Sorts the database by the start year of each anime. This will be done in ascending 
    // order if ascending is true, otherwise it will be done in descending order. 
    void sort_by_start_year(bool ascending);

    // Sorts the database by whether or not the anime are currently airing. If airing_first is true, 
    // the anime that are currently airing will be placed first, last otherwise. 
    void sort_by_airing(bool airing_first); 

    // Sorts the database by the score of each anime. This will be done in ascending order if 
    // ascending is true, otherwise it will be done in descending order. 
    void sort_by_score(bool ascending);

    // Searches the database by name and returns a vector of the indices of all matching records. 
    // If exact is true, the search will only find records with a name matching input exactly. 
    // Otherwise, it will find records with a name that input is a substring of. 
    vector<int> search_by_name(const string& input, bool exact) const;

    // Searches the database by studio name and returns a vector of the indices of all matching 
    // records. If exact is true, the search will only find records with a studio name matching 
    // input exactly. Otherwise, it will find records with a studio name that input is a substring 
    // of. 
    vector<int> search_by_studio(const string& input, bool exact) const;

    // Returns a vector of the indices of all records with a number of episodes in the range of 
    // [input1, input2]. Throws an error if input1 > input2.
    vector<int> search_by_num_episodes(int input1, int input2) const; 

    // Returns a vector of the indices of all records with a number of episodes equal to input. 
    vector<int> search_by_num_episodes(int input) const; 

    // Returns a vector of the indices of all records with a start year in the range of 
    // [input1, input2]. Throws an error if input1 > input2.
    vector<int> search_by_start_year(int input1, int input2) const; 

    // Returns a vector of the indices of all records with a start year equal to input. 
    vector<int> search_by_start_year(int input) const; 

    // Returns a vector of the indices of all records with an airing boolean equal to input. 
    vector<int> search_by_airing(bool input) const; 

    // Returns a vector of the indices of all records with a score in the range of 
    // [input1, input2]. Throws an error if input1 > input2.
    vector<int> search_by_score(double input1, double input2) const; 

    // Returns a vector of the indices of all records with a score equal to input. 
    vector<int> search_by_score(double input) const; 

    // Destructor updates the data file with any changes made to the database. 
    ~Database(); 
};

#endif
