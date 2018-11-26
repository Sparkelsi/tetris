#include <iostream>
#include <list>
#include <stdlib.h> //srand, random
#include <time.h>   //time
#include <ncurses.h>
#include <unistd.h>
#include "Shapes.hpp"
#include "Grid.hpp"


// void draw_borders(WINDOW *screen);
//void printField(WINDOW *field, Grid grid); // might not need to be a function due to efficiency reasons
//void moveDown(WINDOW *field, Grid grid);
// void moveRight();
// void moveLeft();

int main(int argc, char *argv[]) {
    int parent_x, parent_y, new_x, new_y;
    //int new_y;
   // int score_size = 3;
    int next_y = 0;
    int max_y = 24;
    int y = 1;
    int x = 10;

    int coord;

	initscr();

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
    getmaxyx(stdscr, parent_y, parent_x);

    //WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
    WINDOW *field = newwin(24, 24, 0, 0);
    //WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
    WINDOW *nextShapes = newwin(19, 24, 0, 24);
    WINDOW *score = newwin(5, 24, 19, 24);
    WINDOW *instructions = newwin(10,10,0,48);

   // wattron(field, COLOR_PAIR(1));
    fieldGrid.draw_borders(field);
    fieldGrid.draw_borders(nextShapes);
    fieldGrid.draw_borders(score);
    
    keypad(field, true);

    while(1) {
        getmaxyx(stdscr, new_y, new_x);


        // if (new_y != parent_y || new_x != parent_x) {                        //for resizing window -> will visit later
        //   parent_x = new_x;
        //   parent_y = new_y;

        //   wresize(field, new_y - score_size, new_x);
        //   wresize(score, score_size, new_x);
        //   mvwin(score, new_y - score_size, 0);

        //   wclear(stdscr);
        //   wclear(field);
        //   wclear(nextShapes);
        //   wclear(score);


        //   draw_borders(field);
        //   draw_borders(nextShapes);
        //   draw_borders(score);
        // }

        fieldGrid.draw_borders(instructions);
        wrefresh(instructions);
        

        fieldGrid.printField(field);

        //wattron(nextShapes, COLOR_PAIR(2));
        fieldGrid.printNextShapes(nextShapes);

        //wattron(score, COLOR_PAIR(4));
        fieldGrid.printScore(score);


        fieldGrid.pullShape(field, nextShapes, score);

        wclear(field);
        wclear(nextShapes);
        wclear(score);

        fieldGrid.draw_borders(nextShapes);
        fieldGrid.draw_borders(field);

        fieldGrid.printField(field);
        sleep(1);

        fieldGrid.move(field, nextShapes, score);   // takes care of moving shape

        // fieldGrid.fillRow();
        // fieldGrid.printField(field);
        // sleep(1);
        fieldGrid.clearRow();                       // make sure you add a shift row
        //fieldGrid.printField(field);
        //sleep(1);
        //fieldGrid.shiftRow();
        //fieldGrid.printField(field);
        //sleep(1);
        fieldGrid.printField(field);
        sleep(1);

        //sleep(1);

        // remeber usleep

        }

    endwin();

    return 0;
}

//how to get an object to move on its own

// int main(int argc, char *argv[]) {
//     int x = 0;          // setting coordinates
//     int y = 0;
//     int max_x = 0;
//     int max_y = 0;
//     int next_x = 0;
//     int direction = 1;

//     initscr();          // initializes the window
//     noecho();           // don't echo any keypresses
//     curs_set(FALSE);    // don't display a cursor

//     //getmaxyx(stdscr, max_x, max_y);     // global variable 'stdscr' is created in 'initscr()'
//                                         //getmaxyx() is a macro (predetermined function)

//     while(1) {
//        // getmaxyx(stdscr, max_x, max_y);       // resests walls if user changes size of
//                                                 // window since it's in the loop

//         clear();                // clears screen of previously printed characters
//         mvprintw(y, x, "o");    // prints o to screen at (x,y) position


//     //  mvprintw(0, 0, "Hello World!");
//         refresh();                          // characters are buffered before they're displayed so
//                                         // we need to refresh window to see them
//                                         // NEED refresh before displaying anything or text won't be updated

//         //sleep(1);             // shows full screen display for a moment before executing next command

//         usleep(30000);          // shorter delay between movements

//         next_x = x + direction;

//         if (next_x >= max_x || next_x < 0) {
//             direction *= -1;
//         } else {
//             x += direction;
//         }
//         //x++;                    // advances o to the right
//     }

//     endwin();               // restores normal terminal behavior
//}
