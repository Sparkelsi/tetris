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
    // int parent_x, parent_y, new_x, new_y;
    // int next_y = 0;
    // int max_y = 24;
    // int y = 1;
    // int x = 10;

	initscr();                                  //ncurses, initialize the main screen

	if (!has_colors()) {
		endwin();
		puts("Your screen can't print colors. Exiting...");
		return(1);
	}
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_CYAN);       //shapeID 1
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW);   //shapeID 2
	init_pair(3, COLOR_RED, COLOR_RED);         //shapeID 3
	init_pair(4, COLOR_GREEN, COLOR_GREEN);     //shapeID 4
	init_pair(5, COLOR_WHITE, COLOR_WHITE);     //shapeID 5
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA); //shapeID 6
	init_pair(7, COLOR_BLUE, COLOR_BLUE);       //shapeID 7



	init_pair(10, COLOR_YELLOW, COLOR_BLACK);   //border color
	init_pair(9, COLOR_WHITE, COLOR_BLACK);     //Next Shape and Score text color
	init_pair(11, COLOR_BLACK, COLOR_BLACK);    //0's black on black in grid and next shape window
	//keypad(stdscr, true);
	noecho();
	curs_set(FALSE);



    Grid fieldGrid = Grid();                            // creates grid

    fieldGrid.createList();                             // creates list of shapes

    // set up initial windows
    //getmaxyx(stdscr, parent_y, parent_x);

    WINDOW *field = newwin(24, 24, 0, 0);
    WINDOW *nextShapes = newwin(19, 24, 0, 24);
    WINDOW *score = newwin(5, 24, 19, 24);


    keypad(field, true);

    while(1) {
        //getmaxyx(stdscr, new_y, new_x);

        fieldGrid.runGame(field, nextShapes, score);

    }

    endwin();

    return 0;
}
