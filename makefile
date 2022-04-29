CPPFLAGS = -std=c++17 -Wall -Wextra -Wno-sign-compare 

main_run: main.o anime.o database.o menu.o
	g++ -o main_run main.o anime.o database.o menu.o -lncurses

main:
	g++ -c $(CPPFLAGS) main.cpp

anime:
	g++ -c $(CPPFLAGS) anime.cpp

database:
	g++ -c $(CPPFLAGS) database.cpp

menu:
	g++ -c $(CPPFLAGS) menu.cpp

clean: 
	rm -f main_run main.o anime.o database.o menu.o 
