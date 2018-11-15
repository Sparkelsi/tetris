#include <iostream>
#include <list>
#include <stdlib.h> //srand, random
#include <time.h>   //time
#include <ncurses.h>
//#include <curses.h>
#include <unistd.h>
#include "Shapes.hpp"
#include "Grid.hpp"


void draw_borders(WINDOW *screen);
void printField(WINDOW *field, WINDOW *nextShapes, WINDOW *score, Grid grid); // might not need to be a function due to efficiency reasons

int main(int argc, char *argv[]) {
    int parent_x, parent_y, new_x, new_y;
    //int new_y;
   // int score_size = 3;
    int next_y = 0;
    int max_y = 24;
    int y = 1;
    int x = 10;
    int direction = 1;
    int coord;

    initscr();
    noecho();
    curs_set(FALSE);

    Grid fieldGrid = Grid();
    //Grid nextShapesGrid = Grid();
    //std::list<Shapes> list;

    fieldGrid.createList();

    // fieldGrid.pullShape();
    // fieldGrid.printGrid();
    // fieldGrid.addShape();


    // set up initial windows
    getmaxyx(stdscr, parent_y, parent_x);

    //WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
    WINDOW *field = newwin(24, 24, 0, 0);
    //WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
    WINDOW *nextShapes = newwin(19, 24, 0, 24);
    WINDOW *score = newwin(5, 24, 19, 24);


    draw_borders(field);
    draw_borders(nextShapes);
    draw_borders(score);

    while(1) {
        getmaxyx(stdscr, new_y, new_x);


        // if (new_y != parent_y || new_x != parent_x) {                        //for resizing window -> will visit later
        //   parent_x = new_x;
        //   parent_y = new_y;

        //   wresize(field, new_y - score_size, new_x);
        //   wresize(score, score_size, new_x);
        //   mvwin(score, new_y - score_size, 0);

           wclear(stdscr);
        //   wclear(field);
        //   wclear(nextShapes);
        //   wclear(score);


        //   draw_borders(field);
        //   draw_borders(nextShapes);
        //   draw_borders(score);
        // }



        printField(field, nextShapes, score, fieldGrid);

        wclear(nextShapes);
        wclear(score);
        draw_borders(nextShapes);
        draw_borders(score);
        mvwprintw(nextShapes, 1, 1, "Next Shape: ");
        mvwprintw(score, 1, 1, "Score: ");

        //must be in separate function to cycle through shape list
        fieldGrid.pullShape(score);
        fieldGrid.printList(nextShapes);

        wrefresh(score);
        wrefresh(nextShapes);
        wclear(field);
        wclear(nextShapes);
        wclear(score);
        draw_borders(nextShapes);
        draw_borders(field);
        printField(field, nextShapes, score, fieldGrid);
    // grid.pullShape();
    // wrefresh(nextShapes);
        sleep(2);




            // x = i;
            // y = j;
            // wclear(field);
            // draw_borders(field);
            // draw_borders(nextShapes);
            // draw_borders(score);
            // mvwprintw(nextShapes, 1, 1, "Next Shape: ");
            // mvwprintw(score, 1, 1, "Score");
            // //coord = fieldGrid.getCoord(j, i);
            // // draw to our windows
            // // mvwprintw(field, 1, 1, "Field");
            // mvwprintw(field, y, x, "%d", fieldGrid.getCoord(j, i)); //can potentially be made as draw border grid function
            // wrefresh(field);
            // wrefresh(nextShapes);
            // wrefresh(score);
            // usleep(100000);
        }

        //coord = fieldGrid.getCoord(y, x);
        // draw to our windows
       // mvwprintw(field, 1, 1, "Field");
        //mvwprintw(field, x, y, "%d", coord);
        // mvwprintw(nextShapes, 1, 1, "Next Shape: ");
        // mvwprintw(score, 1, 1, "Score");

        //window.delch([y, x]);
        //delch();
       // wclear(field);
        //draw_borders(field);
        //wclrtoeol(field);
        //mvwprintw(field, y, x, "o");    // prints o to screen at (x,y) position
        //wclrtoeol(field);
        // refresh();

        //sleep(1);

        //usleep(100000);          // shorter delay between movements

        // next_y = y + direction;

        // if (next_y < max_y - 1 && next_y >= 0) {
        //     y += direction;
        // }

        // refresh each window
        // wrefresh(field);
        // wrefresh(nextShapes);
        // wrefresh(score);

    endwin();

    return 0;
}




    /*int _rando;
    srand(time(NULL));
    _rando = rand() % 7 + 1;    //between 1 and 7

    Shapes empty = Shapes();
    Shapes cube = Shapes(1);
    Shapes line = Shapes(2);
    Shapes Tshape = Shapes(3);
    Shapes Sshape = Shapes(4);
    Shapes Zshape = Shapes(5);
    Shapes Lshape = Shapes(6);
    Shapes mirroredL = Shapes(7);

    mirroredL.printShape();

    std::cout << "shape^^ \n\n";

    fieldGrid.insertShape(mirroredL);

    fieldGrid.printGrid();

    list.push_back(cube);
    list.push_back(line);
    list.push_back(Lshape);*/

    /*int i = 0;
    Shapes tmp;
    for(auto it : list)
    {
        ++i;
        tmp = it;
    }
    tmp.printShape();

    fieldGrid.insertShape(tmp);
    fieldGrid.printGrid();


    Shapes temp = _rando;
    fieldGrid.insertShape(temp);
    fieldGrid.printGrid();
    std::cout << std::endl;*/


//}

void draw_borders(WINDOW *screen) {
    int x, y, i;

  getmaxyx(screen, y, x);

  // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");

  // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
}

void printField(WINDOW *field, WINDOW *nextShapes, WINDOW *score, Grid grid) {
    int x, y;

    for(int i = 1; i < FIELDSIZE - 1; i++) {                                  // successfully prints starting grid (as of now 11/14)
        for(int j = 1; j < FIELDSIZE - 1; j++) {
            x = i;
            y = j;
            //wclear(field);
            draw_borders(field);
            mvwprintw(field, y, x, "%d", grid.getCoord(i, j)); //can potentially be made as draw border grid function
            wrefresh(field);                                                // steps in order

        }                                            // load in first shape
    }                                                                    // shift next shapes
    wclear(field);
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
