// menu.h

#ifndef MENU_H
#define MENU_H

#include <string> 
#include <vector>

#include "anime.h"
#include "database.h"
#include "ncurses.h"

using namespace std; 

class Menu {
private: 
    Database* database; 
    WINDOW* window; 

    // Shows the home page and implements the associated functionalities.
    void home();

    // Shows the page to list records and implements the associated functionalities.
    void list() const; 

    // Shows the page to search for records and implements the associated functionalities. 
    void search() const;

    // Populates search_result with the records the user searched for. This does not show the front
    // page nor does it print the records. It is meant to be used in conjunction with a function
    // that needs the user to search for records before doing something, such as remove(). 1 is 
    // returned if the user searched for something, -1 is returned otherwise (i.e. user wanted to
    // go back to the home page).
    int search(vector<int>& search_result) const; 

    // Shows the page to add records and implements the associated functionalities. 
    void add(); 

    // Shows the page to remove records and implements the associated functionalities. 
    void remove();

    void print_home_page() const; 

    void print_list_page() const; 

    void print_search_page() const; 

    void print_add_page() const; 

    void print_remove_page() const; 

    // Prints title at (x, y) and underlines it. 
    void print_header(int y, int x, const string& title) const;  

    // Prints the string line on line below the current one. If left_align is true, the line will 
    // be printed starting from the left of the screen. 
    void print_next_line(const string& line = "", bool left_align = true) const; 

    // Prints a table of all records in database on a fresh page. 
    void print_database() const; 

    // Prints all records in database at the given indices on a fresh page. If key_return is true,
    // the function will only return once the user presses a key. 
    void print_database_portion(const vector<int>& indices, bool key_return = true) const;

    // Labels each column of the database with its respective description
    void print_database_label() const;

    // Determines and returns the user input for the sub choice of a menu. The sub choice is one
    // of two choices. For example, for the searching menu, this function determines whether the 
    // user is searching exactly (returns 1) or not (returns 0). If the user chooses to return to 
    // the home page, -1 is returned. 
    int get_sub_choice() const; 

    // Returns true if every character in input is a digit, false otherwise. 
    bool confirm_int(string input) const; 

    // Returns true if input is a properly formatted score (a number between 1.00 and 10.00 
    // inclusive to exactly 2 decimal places), false otherwise. 
    bool confirm_score_format(string input) const; 

    // Determines if input has whitespace at the beginning or end. 
    bool needs_trim(string input) const;
public: 
    Menu(Database* datab);

    // Initializes the menu and opens the home page.
    void init(); 

    ~Menu(); 
};

#endif
