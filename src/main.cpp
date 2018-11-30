/*
Tetris Inspired Game - Project for Data Structures
Kelsi Andrews
Karen Nason

Source file to run simulation of Tetris inspired Game using Ncurses.h for graphics.
*/


#include <iostream>
#include <list>
#include <ncurses.h>
#include <unistd.h>
#include "Shapes.hpp"
#include "Grid.hpp"



int main(int argc, char *argv[]) {
  

	initscr();                                  //ncurses, initialize the main screen

	if (!has_colors()) {
		endwin();
		puts("Your screen can't print colors. Exiting...");
		return(1);
	}
	start_color();
	noecho();
	curs_set(FALSE);



    Grid fieldGrid = Grid();                            // creates grid

    fieldGrid.createList();                             // creates list of shapes



    WINDOW *field = newwin(24, 24, 0, 0);
    WINDOW *nextShapes = newwin(19, 24, 0, 24);
    WINDOW *score = newwin(5, 24, 19, 24);
	WINDOW *instructions = newwin(24, 24, 0, 48);
	WINDOW *menu = newwin(24, 72, 0, 0);


    //keypad(field, true);

	fieldGrid.colorParams(field, nextShapes, score, instructions, menu);

	fieldGrid.printMenu(menu);					//prints beginning window after compiling
	wclear(menu);

    while(1) {

        fieldGrid.runGame(field, nextShapes, score, instructions);

    }
	refresh();


    endwin();

    return 0;
}
