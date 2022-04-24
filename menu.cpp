// menu.cpp 

#include "menu.h"

using namespace std; 

namespace {
    const int MAX_GENERAL_INPUT_LENGTH = 50; 
    const int MAX_NAME_LENGTH = 50;
    const int MAX_STUDIO_LENGTH = 25;
    const int MAX_NUM_EPISODES_DIGITS = 4; 
    const int MAX_START_YEAR_DIGITS = 4;
    const int MAX_AIRING_LENGTH = 5; 
    const int MAX_SCORE_LENGTH = 5;  

    const int MAX_START_YEAR = 2022; 
    const int MIN_START_YEAR = 1900; 
}

Menu::Menu(Database* datab) 
: database(datab), window(nullptr) {}

void Menu::init() {
    window = initscr();
    Menu::home(); 
}

void Menu::home() {
    Menu::print_home_page(); 

    char input = getch(); 
    while (input != 'Q') {
        switch (input) {
            case 'L': 
                Menu::list(); 
                erase();
                Menu::print_home_page(); 
                break;
            case 'S':
                Menu::search();
                erase();
                Menu::print_home_page(); 
                break; 
            case 'A':
                Menu::add();
                erase();
                Menu::print_home_page(); 
                break;
            case 'R':
                Menu::remove();
                erase();
                Menu::print_home_page(); 
                break; 
            default: 
                Menu::print_next_line("Please enter a valid choice: "); 
                break; 
        }
        input = getch(); 
    }
}

void Menu::list() const {
    erase(); 
    Menu::print_list_page(); 
   
    int input2 = 0;

    char input1 = getch();  
    while (input1 != 'R') {
        switch (input1) {
            case '1': 
                Menu::print_next_line("(a) Alphabetical or (b) Reverse Alphabetical: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_name(input2); 
                Menu::print_database(); 
                return; 
            case '2':
                Menu::print_next_line("(a) Alphabetical or (b) Reverse Alphabetical: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_studio(input2); 
                Menu::print_database(); 
                return; 
            case '3':
                Menu::print_next_line("(a) Ascending or (b) Descending: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_num_episodes(input2); 
                Menu::print_database(); 
                return; 
            case '4':
                Menu::print_next_line("(a) Ascending or (b) Descending: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_start_year(input2); 
                Menu::print_database(); 
                return; 
            case '5': 
                Menu::print_next_line("(a) Airing First or (b) Not Airing First: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_airing(input2); 
                Menu::print_database(); 
                return; 
            case '6': 
                Menu::print_next_line("(a) Ascending or (b) Descending: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return; 
                database->sort_by_score(input2); 
                Menu::print_database(); 
                return; 
            default: 
                Menu::print_next_line("Please enter a valid choice: "); 
                break; 
        }
        input1 = getch(); 
    } 
}

void Menu::search() const {
    erase();
    Menu::print_search_page();
    
    vector<int> result;
    if (Menu::search(result) == -1) return; 

    print_database_portion(result);
}

int Menu::search(vector<int>& search_result) const {
    int input2 = 0; 
    char input3[MAX_GENERAL_INPUT_LENGTH + 1];

    char input1 = getch(); 
    while (input1 != 'R') {
        switch (input1) {
            case '1': 
                Menu::print_next_line("(a) Exact or (b) Contains: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1; 
                Menu::print_next_line("Enter name: ");
                getnstr(input3, MAX_NAME_LENGTH);
                search_result = database->search_by_name(string(input3), input2);
                return 1; 
            case '2':
                Menu::print_next_line("(a) Exact or (b) Contains: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1; 
                Menu::print_next_line("Enter studio: ");
                getnstr(input3, MAX_STUDIO_LENGTH);
                search_result = database->search_by_studio(string(input3), input2);
                return 1; 
            case '3':
                Menu::print_next_line("(a) Exact or (b) Range: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1; 
                try {
                    if (input2 == 1) {
                        Menu::print_next_line("Enter number: ");
                        getnstr(input3, MAX_NUM_EPISODES_DIGITS);
                        search_result = database->search_by_num_episodes(stoi(string(input3)));
                    } else {
                        char input4[MAX_GENERAL_INPUT_LENGTH + 1];
                        Menu::print_next_line("Enter lower bound: ");
                        getnstr(input3, MAX_NUM_EPISODES_DIGITS);
                        printw("Enter upper bound: ");
                        getnstr(input4, MAX_NUM_EPISODES_DIGITS); 
                        search_result = database->search_by_num_episodes(
                            stoi(string(input3)), 
                            stoi(string(input4))
                        );
                    }
                } catch (...) {
                    printw("Please enter valid input!");
                    Menu::print_next_line(); 
                    Menu::print_next_line("Enter your choice: ");
                    break; 
                }
                return 1; 
            case '4':
                Menu::print_next_line("(a) Exact or (b) Range: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1; 
                try {
                    if (input2 == 1) {
                        Menu::print_next_line("Enter number: ");
                        getnstr(input3, MAX_START_YEAR_DIGITS);
                        search_result = database->search_by_start_year(stoi(string(input3)));
                    } else {
                        char input4[MAX_GENERAL_INPUT_LENGTH + 1];
                        Menu::print_next_line("Enter lower bound: ");
                        getnstr(input3, MAX_START_YEAR_DIGITS);
                        printw("Enter upper bound: ");
                        getnstr(input4, MAX_START_YEAR_DIGITS); 
                        search_result = database->search_by_start_year(
                            stoi(string(input3)), 
                            stoi(string(input4))
                        );
                    }
                } catch (...) {
                    printw("Please enter valid input!");
                    Menu::print_next_line(); 
                    Menu::print_next_line("Enter your choice: ");
                    break; 
                }
                return 1; 
            case '5': 
                Menu::print_next_line("(a) Airing or (b) Not Airing: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1;
                search_result = database->search_by_airing(input2 == 1); 
                return 1; 
            case '6':
                Menu::print_next_line("(a) Exact or (b) Range: ");
                input2 = Menu::get_sub_choice();
                if (input2 == -1) return -1; 
                try {
                    if (input2 == 1) {
                        Menu::print_next_line("Enter number: ");
                        getnstr(input3, MAX_SCORE_LENGTH);
                        search_result = database->search_by_score(stod(string(input3)));
                    } else {
                        char input4[MAX_GENERAL_INPUT_LENGTH + 1];
                        Menu::print_next_line("Enter lower bound: ");
                        getnstr(input3, MAX_SCORE_LENGTH);
                        printw("Enter upper bound: ");
                        getnstr(input4, MAX_SCORE_LENGTH); 
                        search_result = database->search_by_score(
                            stod(string(input3)), 
                            stod(string(input4))
                        );
                    }
                } catch (...) {
                    printw("Please enter valid input!");
                    Menu::print_next_line(); 
                    Menu::print_next_line("Enter your choice: ");
                    break; 
                }
                return 1; 
            default: 
                Menu::print_next_line("Please enter a valid choice: "); 
                break; 
        }
        input1 = getch(); 
    } 
    return -1; 
}

void Menu::add() {
    erase(); 
    Menu::print_add_page(); 

    if (getch() == 'R') return; 

    int overwrite = 0; 
    char name[MAX_NAME_LENGTH + 1]; 
    char studio[MAX_STUDIO_LENGTH + 1];
    char num_episodes[MAX_NUM_EPISODES_DIGITS + 1];
    char start_year[MAX_START_YEAR_DIGITS + 1];
    int airing = 0; 
    char score[MAX_SCORE_LENGTH + 1]; 

    Menu::print_next_line();
    Menu::print_next_line("Enter name of anime: ");
    getnstr(name, MAX_NAME_LENGTH);
    while (string(name).empty() || Menu::needs_trim(string(name))) {
        printw("Please enter a name at least one character long without hanging whitespace: ");
        getnstr(name, MAX_NAME_LENGTH);
    }
    vector<int> existing = database->search_by_name(string(name), true); 
    if (existing.size() > 0) {
        string overwrite_message = (
            "An anime called " + string(name) + " already exists. (a) Overwrite or (b) Stop: "
        );
        printw(overwrite_message.c_str());
        overwrite = Menu::get_sub_choice();
        if (overwrite != 1) return; 
        Menu::print_next_line();  
    }

    Menu::print_next_line("Enter studio that produced the anime: "); 
    getnstr(studio, MAX_STUDIO_LENGTH); 
    while (string(studio).empty() || Menu::needs_trim(string(studio))) {
        printw("Please enter a name at least one character long without hanging whitespace: ");
        getnstr(studio, MAX_STUDIO_LENGTH);
    }

    Menu::print_next_line("Enter the number of episodes the anime has: ");
    getnstr(num_episodes, MAX_NUM_EPISODES_DIGITS);
    while (!confirm_int(string(num_episodes))) {
        string error = (
            "Please enter a whole number with at most " + to_string(MAX_NUM_EPISODES_DIGITS) 
            + " digits: "
        );
        printw(error.c_str());
        getnstr(num_episodes, MAX_NUM_EPISODES_DIGITS);
    }

    Menu::print_next_line("Enter the year the anime started airing: ");
    getnstr(start_year, MAX_START_YEAR_DIGITS);
    while (
        !confirm_int(string(start_year)) 
        || stoi(string(start_year)) < MIN_START_YEAR 
        || stoi(string(start_year)) > MAX_START_YEAR
    ) {
        string error = (
            "Please enter an integer between " + to_string(MIN_START_YEAR) + " and " 
            + to_string(MAX_START_YEAR) + " inclusive: "
        );
        printw(error.c_str());
        getnstr(start_year, MAX_START_YEAR_DIGITS);
    }

    Menu::print_next_line("Enter whether the anime is currently (a) Airing or (b) Not Airing: ");
    airing = Menu::get_sub_choice();
    while (airing == -1) {
        Menu::print_next_line("Please enter a valid choice: "); 
        airing = Menu::get_sub_choice(); 
    }
    Menu::print_next_line(); 

    Menu::print_next_line("Enter the score of the anime: ");
    getnstr(score, MAX_SCORE_LENGTH);
    while (!confirm_score_format(string(score))) {
        string error = (
            "Please enter a number between 1.00 and 10.00 inclusive, to exactly 2 decimal places: "
        );
        printw(error.c_str());
        getnstr(score, MAX_SCORE_LENGTH);
    }

    Anime to_be_added(
        string(name),
        string(studio),
        stoi(string(num_episodes)),
        stoi(string(start_year)),
        airing,
        stod(string(score))
    );

    if (overwrite == 1) {
        database->remove(existing); 
        database->add(to_be_added); 
        Menu::print_next_line("Overwritten successfully. Press any key to return: ");
    } else {
        database->add(to_be_added); 
        Menu::print_next_line("Added successfully. Press any key to return: ");
    }
    getch(); 
}

void Menu::remove() {
    erase();
    Menu::print_remove_page();
    
    vector<int> to_be_removed; 
    if (Menu::search(to_be_removed) == -1) return; 
    if (to_be_removed.empty()) {
        print_database_portion(to_be_removed); 
        return; 
    }

    print_database_portion(to_be_removed, false); 
    Menu::print_next_line();
    Menu::print_next_line("(a) Confirm Removal or (b) Cancel: "); 
    int confirm = Menu::get_sub_choice();

    if (confirm != 1) return;
    database->remove(to_be_removed); 
    Menu::print_next_line("Removal successful. Press any key to return: ");
    getch(); 
}

void Menu::print_home_page() const {
    const vector<string> options = {
        "(L)ist anime",
        "(S)earch for an anime",
        "(A)dd an anime",
        "(R)emove anime",
        "(Q)uit"
    };
    int y = 0; 

    Menu::print_header(y, 0, "Welcome to the Anime Database!");

    y += 3; 
    for (string s : options) {
        mvprintw(y += 1, 0, s.c_str()); 
    }
    
    mvprintw(y += 3, 0, "Enter the letter of your choice: "); 
}

void Menu::print_list_page() const {
    const vector<string> options = {
        "(1) Name",
        "(2) Studio",
        "(3) Number of episodes",
        "(4) Year airing began",
        "(5) Currently airing or not",
        "(6) Score"
    };
    int y = 0; 

    Menu::print_header(y, 0, "List Anime");

    mvprintw(y += 2, 0, "You can list by:"); 

    y += 2; 
    for (string s : options) {
        mvprintw(y += 1, 0, s.c_str()); 
    }

    mvprintw(y += 3, 0, "(R)eturn to main menu"); 

    mvprintw(y += 3, 0, "Enter your choice: "); 
}

void Menu::print_search_page() const {
    const vector<string> options = {
        "(1) Name",
        "(2) Studio",
        "(3) Number of episodes",
        "(4) Year airing began",
        "(5) Currently airing or not",
        "(6) Score"
    };
    int y = 0; 

    Menu::print_header(y, 0, "Search for an Anime");

    mvprintw(y += 2, 0, "You can search by:"); 

    y += 2; 
    for (string s : options) {
        mvprintw(y += 1, 0, s.c_str()); 
    }

    mvprintw(y += 3, 0, "(R)eturn to main menu"); 

    mvprintw(y += 3, 0, "Enter your choice: "); 
}

void Menu::print_add_page() const {
    Menu::print_header(0, 0, "Add an Anime");
    Menu::print_next_line("(R)eturn to main menu, or press any other key to start adding: "); 
}

void Menu::print_remove_page() const {
    const vector<string> options = {
        "(1) Name",
        "(2) Studio",
        "(3) Number of episodes",
        "(4) Year airing began",
        "(5) Currently airing or not",
        "(6) Score"
    };
    int y = 0; 

    Menu::print_header(y, 0, "Remove Anime");

    mvprintw(y += 2, 0, "You can remove by:"); 

    y += 2; 
    for (string s : options) {
        mvprintw(y += 1, 0, s.c_str()); 
    }

    mvprintw(y += 3, 0, "(R)eturn to main menu"); 

    mvprintw(y += 3, 0, "Enter your choice: "); 
}

void Menu::print_header(int y, int x, const string& title) const {
    string underline(title.size(), '-'); 

    mvprintw(y, x, title.c_str()); 
    mvprintw(y += 1, x, underline.c_str()); 
}

void Menu::print_next_line(const string& line, bool left_align) const {
    int cur_y, cur_x; 
    getyx(window, cur_y, cur_x);
    if (left_align) cur_x = 0; 
    mvprintw(cur_y += 1, cur_x, line.c_str());
}

void Menu::print_database() const {
    erase();
    if (database->get_size() == 0) printw("Database is currently empty!"); 
    else {
        Menu::print_database_label(); 
        int y = 1; int x = 0; 
        for (int i = 0; i < database->get_size(); i++) {
            Anime a = database->get(i); 
            mvprintw(y, x, a.get_name().c_str()); 
            mvprintw(y, x += MAX_NAME_LENGTH + 5, a.get_studio().c_str()); 
            mvprintw(y, x += MAX_STUDIO_LENGTH + 5, to_string(a.get_num_episodes()).c_str()); 
            mvprintw(y, x += MAX_NUM_EPISODES_DIGITS + 5, to_string(a.get_start_year()).c_str()); 
            mvprintw(y, x += MAX_START_YEAR_DIGITS + 5, a.get_airing() ? "True" : "False"); 
            mvprintw(y, x += MAX_AIRING_LENGTH + 5, a.get_score_string().c_str()); 
            y++; x = 0; 
        }
    }
    Menu::print_next_line();
    Menu::print_next_line("Press any key to return: "); 
    getch();
}

void Menu::print_database_portion(const vector<int>& indices, bool key_return) const {
    erase(); 
    if (indices.size() == 0) printw("No matching anime!"); 
    else {
        Menu::print_database_label(); 
        int y = 1; int x = 0; 
        for (int i = 0; i < indices.size(); i++) {
            Anime a = database->get(indices[i]);
            mvprintw(y, x, a.get_name().c_str()); 
            mvprintw(y, x += MAX_NAME_LENGTH + 5, a.get_studio().c_str()); 
            mvprintw(y, x += MAX_STUDIO_LENGTH + 5, to_string(a.get_num_episodes()).c_str()); 
            mvprintw(y, x += MAX_NUM_EPISODES_DIGITS + 5, to_string(a.get_start_year()).c_str()); 
            mvprintw(y, x += MAX_START_YEAR_DIGITS + 5, a.get_airing() ? "True" : "False"); 
            mvprintw(y, x += MAX_AIRING_LENGTH + 5, a.get_score_string().c_str());
            y++; x = 0; 
        }
    }
    if (key_return) {
        Menu::print_next_line();
        Menu::print_next_line("Press any key to return: "); 
        getch();
    }
}

void Menu::print_database_label() const {
    int x = 0; 
    mvprintw(0, x, "NAME"); 
    mvprintw(0, x += MAX_NAME_LENGTH + 5, "STUDIO"); 
    mvprintw(0, x += MAX_STUDIO_LENGTH + 5, "# EPS"); 
    mvprintw(0, x += MAX_NUM_EPISODES_DIGITS + 5, "YEAR"); 
    mvprintw(0, x += MAX_START_YEAR_DIGITS + 5, "AIRING"); 
    mvprintw(0, x += MAX_AIRING_LENGTH + 5, "SCORE"); 
}

int Menu::get_sub_choice() const {
    char input = getch(); 
    while (input != 'R') {
        switch (input) {
            case 'a':
                return 1;  
            case 'b':
                return 0; 
            default:
                Menu::print_next_line("Please enter a valid choice: "); 
                break; 
        }
        input = getch(); 
    }
    return -1;   
}

bool Menu::confirm_int(string input) const {
    if (input.empty()) return false; 
    for (int i = 0; i < input.size(); i++) {
        if (input[i] < '0' || input[i] > '9') return false; 
    }
    return true; 
}

bool Menu::confirm_score_format(string input) const {
    if (input == "10.00") return true; 
    if (input.size() != MAX_SCORE_LENGTH - 1) return false; 
    for (int i = 2; i < input.size(); i++) {
        if (input[i] < '0' || input[i] > '9') return false; 
    }
    return ('1' <= input[0] && input[0] <= '9') && input[1] == '.'; 
}

bool Menu::needs_trim(string input) const {
    if (input.empty()) return false; 
    return input[0] == ' ' || input[input.size() - 1] == ' ';
}

Menu::~Menu() {
    endwin(); 
}
