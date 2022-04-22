// main.cpp

#include "database.h"
#include "menu.h"

using namespace std;

int main() {
    Database my_database("database.txt");
    Menu my_menu(&my_database); 

    my_menu.init(); 

    return 0; 
}
