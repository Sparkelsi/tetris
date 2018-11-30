/*
Tetris Inspired Game - Project for Data Structures
Kelsi Andrews
Karen Nason
*/

#include "Grid.hpp"
#include "Shapes.hpp"
#include <ncurses.h>
#include <iostream>
#include <random>

int Grid::_score = 0;               //static int to keep track of the score.

//NOTE:
// when changing field size, must change window, insert shape, and move
// specifically the j's in insert shape and move

Grid::Grid()
    {
        for(int i = 0; i < FIELDSIZE; i++) {
            for(int j = 0; j < FIELDSIZE; j++) {
                gridMap[i][j] = 0;
            }
        }
    }

void Grid::createList()
{
    for(int i = 0; i < 5; i++)
    {
        shapelist.push_back(getRandomShape());          // creates list with random shapes
    }
}

Shapes Grid::getRandomShape()
{
    std::random_device placeShape;                      // creates a Shape object with a random shapeID
    std::mt19937 gen(placeShape());
    std::uniform_int_distribution<> distOne(1, 7);
    Shapes tmp(distOne(gen));

    return tmp;
}

void Grid::insertShape(Shapes z, WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions) // will always be inserted at same insertion point
{

    int x;
    int y;                                              // i and j are at insertion point (middle top of grid)
        for(int i = 1; i < 3; i++) {
            for(int j = 10; j < 14; j++) {
                x = i - 1;                              // place holders so i and j aren't affected
                y = j - 10;
                if(gridMap[j][i] == 0) {
                    gridMap[j][i] = z.getShape(y, x);            // copies the shape into the grid
                }else {
                    gameOverDisp(field, nextShapes, score, instructions);     //displays game over window if top pieces hit top of grid
                }
            }
        }
}

void Grid::pullShape(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions)     // make sure to take score out, just testing things
{
    if(shapelist.empty()) {                             // creates list in case one is not already made
        createList();
    }

    insertShape(shapelist.front(), field, nextShapes, score, instructions);       // inserts first shape into the grid
    shapelist.pop_front();                                          // deleting first item in the list
    shapelist.push_back(getRandomShape());                          // adding another random shape to back of list
}

int Grid::getCoord(int y, int x)
{
    return gridMap[y][x];   //returns coordinates of the grid specifically for printing the field
}

void Grid::resetGrid()                                  // testing purposes only
{
    for(int i = 0; i < FIELDSIZE; i++) {               //resets grid, only for testing as of now
        for(int j = 0; j < FIELDSIZE; j++)
        {
            gridMap[i][j] = 0;
        }
    }
}

void Grid::colorParams(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions, WINDOW *menu)
{
    init_pair(1, COLOR_CYAN, COLOR_CYAN);       //shapeID 1
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW);   //shapeID 2
	init_pair(3, COLOR_RED, COLOR_RED);         //shapeID 3
	init_pair(4, COLOR_GREEN, COLOR_GREEN);     //shapeID 4
	init_pair(5, COLOR_WHITE, COLOR_WHITE);     //shapeID 5
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA); //shapeID 6
	init_pair(7, COLOR_BLUE, COLOR_BLUE);       //shapeID 7



	init_pair(10, COLOR_YELLOW, COLOR_BLACK);   //border color
	init_pair(9, COLOR_WHITE, COLOR_BLACK);     //Next Shape and Score text color
	init_pair(12, COLOR_MAGENTA, COLOR_BLACK);	//design color for instruction window
	init_pair(13, COLOR_CYAN, COLOR_BLACK);     //design color for menu, a little splash of color
	init_pair(11, COLOR_BLACK, COLOR_BLACK);    //0's black on black in grid and next shape window
}



void Grid::move(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{
   int z = 0;                                           // i and j are at insertion point
    for(int i = 1; i < 3; i++) {                        // using specific i and j for more efficiency (this is where the shape is inserted)
        for(int j = 10; j < 14; j++) {
            if(gridMap[j][i] != 0 && z == 0) {          // loops through to get coordinates of each piece of the shape
                yOne = i;
                xOne = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] != 0 && z == 1) {
                yTwo = i;
                xTwo = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] != 0 && z == 2) {
                yThree = i;
                xThree = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] != 0 && z == 3) {
                yFour = i;
                xFour = j;
                z++;
                gridMap[j][i] = 0;
            }
        }
    }

    char key;                                           // declaring key that will used by user to move the shape

    nextxOne = 1;                                       // resetting nextx's so that the shape can continue to move
    nextxTwo = 1;
    nextxThree = 1;
    nextxFour = 1;

    incrementNextY();                                   // have to check next space as to not go out of bounds

    if(xOne == xThree && xTwo == xFour) {               // Cube check
        int gridShape = 1;
        while(gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
                decrementNextX();                       // decrements so still able to move left
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
                incrementNextX();                       // increments so still able to move right
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            } else if (key == 'r') {
                rotate(gridShape, field, nextShapes, score);
            }

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

            printField(field);                          // reprints everything out appearing to move down one space
            printNextShapes(nextShapes);
            printScore(score);
            wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
            // sleep(1);
            usleep(150000);
        }
    } else if(xOne == xTwo || xOne == xFour || xOne == xThree) {    // Mirrored L, L, T, S Shape check

        if(xOne == xThree && yTwo == yThree && yThree == yFour) {
            gridShape = 3;
        } else if(xOne == xFour && yOne == yTwo && yThree == yFour) {
            gridShape = 4;
        } else if(xOne == xTwo && yTwo == yThree && yThree == yFour) {
            gridShape = 6;
        } else if(xOne == xFour && yTwo == yThree && yThree == yFour) {
            gridShape = 7;
        }
        while(((gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xOne][nextyOne] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xOne][nextyOne] == 0 &&
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0)) &&
            nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
                decrementNextX();                       // decrements so still able to move left
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
                incrementNextX();                       // increments so still able to move right
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            } else if (key == 'r') {
                rotate(gridShape, field, nextShapes, score);
                // if((xOne == xTwo && xTwo == xFour) ||        // 3 -- shape 3 rotation 1 -- 6 shape rotation 3
                //     (xOne == xThree && xThree == xFour) ||      // 2 -- shape 3 rotation 3 -- 6 shape rotation 1
                //     (xOne == xTwo && xTwo == xThree) ||         // 4 -- shape 7 rotation 1
                //     (xTwo == xThree && xThree == xFour)) //||      // 1 -- shape 7 rotation 3 --
                //     {                                          // still need to finish shape 4 here S shape
                    while(((gridMap[xOne][nextyOne] == 0 &&
                        gridMap[xFour][nextyFour] == 0) ||
                        (gridMap[xThree][nextyThree] == 0 &&
                        gridMap[xFour][nextyFour] == 0) ||
                        (gridMap[xTwo][nextyTwo] == 0 &&
                        gridMap[xFour][nextyFour] == 0) ||
                        (gridMap[xOne][nextyOne] == 0 &&
                        gridMap[xThree][nextyThree] == 0)) &&
                        nextyFour != (FIELDSIZE - 1)) {

                        halfdelay(1);                           // continues if no input is given
                        key = getch();                          // gets users input

                        if(key == 'd') {
                            moveRight(field, nextShapes, score);
                            decrementNextX();                   // decrements so still able to move left
                        } else if (key == 'a') {
                            moveLeft(field, nextShapes, score);
                            incrementNextX();                   // increments so still able to move right
                        } else if (key == 's') {
                            moveDown();
                        } else if (key == ' ') {
                            moveAllDown();
                        } else if (key == 'r') {
                            rotate(gridShape, field, nextShapes, score);
                            break;
                        }
                        if (((gridMap[xOne][nextyOne] == 0 &&
                            gridMap[xFour][nextyFour] == 0) ||
                            (gridMap[xThree][nextyThree] == 0 &&
                            gridMap[xFour][nextyFour] == 0) ||
                            (gridMap[xTwo][nextyTwo] == 0 &&
                            gridMap[xFour][nextyFour] == 0) ||
                            (gridMap[xOne][nextyOne] == 0 &&
                            gridMap[xThree][nextyThree] == 0)) &&
                            nextyFour != (FIELDSIZE - 1)) {

                            makeZero();                             // makes current space of shape all 0's

                            incrementY();                           // increments current space of shape to appear to move down

                            insertNum(gridShape);                   // puts shape into grid after moving down

                            // mvwprintw(score, 4, 4, "%d", shapeRotation);
                            // wrefresh(score);
                            // sleep(1);

                            incrementNextY();                       // have to check next space as to not go out of bounds

                            printField(field);                      // reprints everything out appearing to move down one space
                            printNextShapes(nextShapes);
                            printScore(score);
                            wrefresh(field);
                            wrefresh(nextShapes);
                            wrefresh(score);
                            // sleep(1);
                            usleep(150000);
                        }

                    }
                }
            //}

            if(((gridMap[xTwo][nextyTwo] == 0 &&                    // have to DOUBLE check due to rotation
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xOne][nextyOne] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xOne][nextyOne] == 0 &&
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0)) &&
            nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

                makeZero();                             // makes current space of shape all 0's

                incrementY();                           // increments current space of shape to appear to move down

                insertNum(gridShape);                   // puts shape into grid after moving down

                incrementNextY();                       // have to check next space as to not go out of bounds

                printField(field);                      // reprints everything out appearing to move down one space
                printNextShapes(nextShapes);
                printScore(score);
                wrefresh(field);
                wrefresh(nextShapes);
                wrefresh(score);
                // sleep(1);
                usleep(150000);
            }

        }

    } else if(xTwo == xThree) {                         // Z shape check
        gridShape = 5;                                  // ythree and yfour too i think causes problems
        while(gridMap[xOne][nextyOne] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
                decrementNextX();                       // decrements so still able to move left
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
                incrementNextX();                       // increments so still able to move right
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            } else if (key == 'r') {
                rotate(gridShape, field, nextShapes, score);
                while(gridMap[xThree][nextyThree] == 0 &&
                    gridMap[xFour][nextyFour] == 0 &&
                    nextyFour != (FIELDSIZE - 1)) {

                    halfdelay(1);                               // continues if no input is given
                    key = getch();                              // gets user input

                    if(key == 'd') {
                        moveRight(field, nextShapes, score);
                        decrementNextX();                       // decrements so still able to move left
                    } else if (key == 'a') {
                        moveLeft(field, nextShapes, score);
                        incrementNextX();                       // increments so still able to move right
                    } else if (key == 's') {
                        moveDown();
                    } else if (key == ' ') {
                        moveAllDown();
                    } else if (key == 'r') {
                        rotate(gridShape, field, nextShapes, score);
                        break;
                    }

                    if(gridMap[xThree][nextyThree] == 0 &&              // have to DOUBLE check due to moving left and right
                    gridMap[xFour][nextyFour] == 0 &&
                    nextyFour != (FIELDSIZE - 1)) {

                        makeZero();                             // makes current space of shape all 0's

                        incrementY();                           // increments current space of shape to appear to move down

                        insertNum(gridShape);                   // puts shape into grid after moving down

                        incrementNextY();                       // have to check next space as to not go out of bounds

                        printField(field);                      // reprints everything out appearing to move down one space
                        printNextShapes(nextShapes);
                        printScore(score);
                        wrefresh(field);
                        wrefresh(nextShapes);
                        wrefresh(score);
                        // sleep(1);
                        usleep(150000);
                    }

                }
            }

            if(gridMap[xOne][nextyOne] == 0 &&              // have to DOUBLE check due to rotation
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

                makeZero();                                 // makes current space of shape all 0's

                incrementY();                               // increments current space of shape to appear to move down

                insertNum(gridShape);                       // puts shape into grid after moving down

                incrementNextY();                           // have to check next space as to not go out of bounds

                printField(field);                          // reprints everything out appearing to move down one space
                printNextShapes(nextShapes);
                printScore(score);
                wrefresh(field);
                wrefresh(nextShapes);
                wrefresh(score);
                // sleep(1);
                usleep(150000);
            }

        }
    } else {                                            // Line check
        gridShape = 2;
        while(gridMap[xOne][nextyOne] == 0 &&
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
                decrementNextX();                       // decrements so still able to move left
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
                incrementNextX();                       // increments so still able to move right
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            } else if (key == 'r') {
                rotate(gridShape, field, nextShapes, score);
                    while((gridMap[xOne][nextyOne] == 0 ||
                        gridMap[xFour][nextyFour] == 0) &&
                        nextyOne != (FIELDSIZE - 1) &&
                        nextyFour != (FIELDSIZE - 1)){ // &&
                        halfdelay(1);                           // continues if no input is given
                        key = getch();                          // gets users input

                        if(key == 'd') {
                            moveRight(field, nextShapes, score);
                            decrementNextX();                   // decrements so still able to move left
                        } else if (key == 'a') {
                            moveLeft(field, nextShapes, score);
                            incrementNextX();                   // increments so still able to move right
                        } else if (key == 's') {
                            moveDown();
                        } else if (key == ' ') {
                            moveAllDown();
                        } else if (key == 'r') {
                            rotate(gridShape, field, nextShapes, score);
                            break;
                        }

                        if((gridMap[xOne][nextyOne] == 0 ||         // have to DOUBLE check due to moving left and right
                            gridMap[xFour][nextyFour] == 0) &&
                            nextyOne != (FIELDSIZE - 1) &&
                            nextyFour != (FIELDSIZE - 1)) {

                            makeZero();                             // makes current space of shape all 0's

                            incrementY();                           // increments current space of shape to appear to move down

                            insertNum(gridShape);                   // puts shape into grid after moving down

                            incrementNextY();                       // have to check next space as to not go out of bounds

                            printField(field);                      // reprints everything out appearing to move down one space
                            printNextShapes(nextShapes);
                            printScore(score);
                            wrefresh(field);
                            wrefresh(nextShapes);
                            wrefresh(score);
                            // sleep(1);
                            usleep(150000);
                        }
                    }
                }

            if(gridMap[xOne][nextyOne] == 0 &&          // have to DOUBLE check due to rotation
                gridMap[xTwo][nextyTwo] == 0 &&
                gridMap[xThree][nextyThree] == 0 &&
                gridMap[xFour][nextyFour] == 0 &&
                nextyOne != (FIELDSIZE - 1) &&
                nextyTwo != (FIELDSIZE - 1) &&
                nextyThree != (FIELDSIZE - 1) &&
                nextyFour != (FIELDSIZE - 1)) {

                makeZero();                             // makes current space of shape all 0's

                incrementY();                           // increments current space of shape to appear to move down

                insertNum(gridShape);                   // puts shape into grid after moving down

                incrementNextY();                       // have to check next space as to not go out of bounds

                printField(field);                      // reprints everything out appearing to move down one space
                printNextShapes(nextShapes);
                printScore(score);
                wrefresh(field);
                wrefresh(nextShapes);
                wrefresh(score);
                // sleep(1);
                usleep(150000);
                }

        }
    }

    //cbreak(); // not sure if needed
    shapeRotation = 0;                                  // resets rotation value for next shape
    printField(field);                                  // reprints everything out once the shape can no longer move down
    printNextShapes(nextShapes);
    printScore(score);
    wrefresh(field);
    wrefresh(nextShapes);
    wrefresh(score);
}


void Grid::moveRight(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{
    incrementNextX();                                   // increments so able to move right properly

    if(yOne == yTwo && yTwo == yThree && yThree == yFour &&     // Line check
    gridMap[nextxFour][yFour] == 0 &&
    nextxFour != (FIELDSIZE - 1)) {

    makeZero();                                         // makes current space of shape all 0's

    incrementX();                                       // increments current space of shape to appear to move right

    insertNum(gridShape);                               // puts shape into grid after moving right

    incrementNextX();                                   // have to check next space as to not go out of bounds

    printField(field);                                  // reprints everything out appearing to move right one space
    printNextShapes(nextShapes);
    printScore(score);
    wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
    // sleep(1);
    usleep(150000);

    } else if(yTwo == yThree && yThree == yFour &&      // Mirrored L, L, T shape check
        gridMap[nextxOne][yOne] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != (FIELDSIZE - 1) &&
        nextxFour != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        // sleep(1);
        usleep(150000);

    } else if(yOne == yTwo && yThree == yFour &&        // Cube, S, Z shape check
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxTwo != (FIELDSIZE - 1) &&
        nextxFour != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        // sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xThree && xThree == xFour &&      // rotation 1 and 2 line check
        gridMap[nextxOne][yOne] == 0 &&
        gridMap[nextxOne][yOne] != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        // sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xFour &&                          // rotation 1 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        gridMap[nextxThree][yThree] != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(yOne == yTwo && yTwo == yThree &&                         // rotation 2 T check
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        gridMap[nextxThree][yThree] != (FIELDSIZE - 1)) {
        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        //sleep(1);
        usleep(150000);
    } else if(xOne == xThree && xThree == xFour &&                          // rotation 3 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        gridMap[nextxOne][yOne] != (FIELDSIZE - 1) &&
        gridMap[nextxThree][yThree] != (FIELDSIZE - 1) &&
        gridMap[nextxFour][yFour] != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xThree == xFour &&       // rotation 1 and 3 S check                   // rotation 3 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        gridMap[nextxThree][yThree] != (FIELDSIZE - 1) &&
        gridMap[nextxFour][yFour] != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xThree && xTwo == xFour &&       // rotation 1 and 3 Z check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxOne][yOne] != (FIELDSIZE - 1) &&
        gridMap[nextxThree][yThree] != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xFour &&          // rotation 3 L check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != (FIELDSIZE - 1) &&
        nextxTwo != (FIELDSIZE - 1) &&
        nextxFour != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xThree &&          // rotation 3 L check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != (FIELDSIZE - 1) &&
        nextxTwo != (FIELDSIZE - 1) &&
        nextxFour != (FIELDSIZE - 1)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementX();                                   // increments current space of shape to appear to move right

        insertNum(gridShape);                           // puts shape into grid after moving right

        incrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    }

    printField(field);                                  // reprints everything out if the shape can't move right
    printNextShapes(nextShapes);
    printScore(score);

}

void Grid::moveLeft(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{
    decrementNextX();                                   // decrements so able to move left properly

     if(yOne == yTwo && yTwo == yThree && yThree == yFour &&     // Line check
        gridMap[nextxOne][yOne] == 0 &&
        nextxOne != 0){

        makeZero();                                     // makes current space of shape all 0's

        decrementX();                                   // decrements current space of shape to appear to move left

        insertNum(gridShape);                           // puts shape into grid after moving left

        decrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(yTwo == yThree && yThree == yFour &&      // Mirrored L, L, T shape check
        gridMap[nextxOne][yOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        nextxOne != 0 &&
        nextxTwo != 0){

        makeZero();                                     // makes current space of shape all 0's

        decrementX();                                   // decrements current space of shape to appear to move left

        insertNum(gridShape);                           // puts shape into grid after moving left

        decrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(yOne == yTwo && yThree == yFour &&        // Cube, S, Z shape check
        gridMap[nextxOne][yOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        nextxOne != 0 &&
        nextxThree != 0){

        makeZero();                                     // makes current space of shape all 0's

        decrementX();                                   // decrements current space of shape to appear to move left

        insertNum(gridShape);                           // puts shape into grid after moving left

        decrementNextX();                               // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);
    } else if(xOne == xTwo && xTwo == xThree && xThree == xFour &&      // rotation 1 and 2 line check
            gridMap[nextxOne][yOne] == 0 &&
            nextxOne != 0) {

            makeZero();                                 // makes current space of shape all 0's

            decrementX();                               // decrements current space of shape to appear to move left

            insertNum(gridShape);                       // puts shape into grid after moving left

            decrementNextX();                           // have to check next space as to not go out of bounds

            printField(field);                          // reprints everything out appearing to move left one space
            printNextShapes(nextShapes);
            printScore(score);
            wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
            //sleep(1);
            usleep(150000);

    } else if(yOne == yTwo && yTwo == yThree &&
        gridMap[nextxOne][yOne] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != 0) {                                    // rotation 2 T check

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xThree && xThree == xFour &&                          // rotation 3 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxFour != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xFour &&                          // rotation 3 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxTwo != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xThree == xFour &&                          // rotation 3 T check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != 0 &&
        nextxTwo != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xThree && xTwo == xFour &&                        // rotation 1 and 3 Z check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxOne != 0 &&
        nextxFour != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xFour &&          // rotation 3 L check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        nextxOne != 0 &&
        nextxTwo != 0 &&
        nextxThree != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    } else if(xOne == xTwo && xTwo == xThree &&          // rotation 3 L check
        gridMap[nextxOne][xOne] == 0 &&
        gridMap[nextxTwo][yTwo] == 0 &&
        gridMap[nextxThree][yThree] == 0 &&
        nextxOne != 0 &&
        nextxTwo != 0 &&
        nextxThree != 0) {

        makeZero();                                 // makes current space of shape all 0's

        decrementX();                               // decrements current space of shape to appear to move left

        insertNum(gridShape);                       // puts shape into grid after moving left

        decrementNextX();                           // have to check next space as to not go out of bounds

        printField(field);                          // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        wrefresh(field);
            wrefresh(nextShapes);
            wrefresh(score);
        //sleep(1);
        usleep(150000);

    }

    printField(field);                              // reprints everything out if the shape can't move left
    printNextShapes(nextShapes);
    printScore(score);

}

void Grid::moveDown()
{

    if(((xOne == xTwo && xTwo == xFour) || (xOne == xThree && xThree == xFour)) &&
        ((gridMap[xThree][nextyThree] == 0 &&
        gridMap[xFour][nextyFour] == 0 &&
        nextxThree != (FIELDSIZE - 2) &&
        nextxFour != (FIELDSIZE - 2)) ||
        (gridMap[nextxThree][yThree] == 0 &&
        gridMap[nextxFour][yFour] == 0 &&
        nextxThree != (FIELDSIZE - 2) &&
        nextxFour != (FIELDSIZE - 2)))) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();

    } else if(xOne == xThree && xTwo == xFour &&               // Cube check
        gridMap[xThree][nextyThree] == 0 &&
        gridMap[xFour][nextyFour] == 0 &&
        nextyThree != (FIELDSIZE - 2) &&
        nextyFour != (FIELDSIZE - 2)) {


        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if(xOne == xTwo && xThree == xFour &&               // S shape 1 and 3 rotation check
        gridMap[xTwo][nextyTwo] == 0 &&
        gridMap[xFour][nextyFour] == 0 &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if((xOne == xTwo || xOne == xFour || xOne == xThree) &&  // Mirrored L, L, T, S shape check
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyTwo != (FIELDSIZE - 2) &&
            nextyThree != (FIELDSIZE - 2) &&
            nextyFour != (FIELDSIZE - 2)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move down twice as fast

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

    } else if(xTwo == xThree &&                         // Z shape check
        gridMap[xOne][nextyOne] == 0 &&
        gridMap[xThree][nextyThree] == 0 &&
        gridMap[xFour][nextyFour] == 0 &&
        nextyOne != (FIELDSIZE - 2) &&
        nextyThree != (FIELDSIZE - 2) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's


        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if (yOne == yTwo && yTwo == yThree && yThree == yFour &&
        gridMap[xOne][nextyOne] == 0 &&          // Line check
        gridMap[xTwo][nextyTwo] == 0 &&
        gridMap[xThree][nextyThree] == 0 &&
        gridMap[xFour][nextyFour] == 0 &&
        nextyOne != (FIELDSIZE - 2) &&
        nextyTwo != (FIELDSIZE - 2) &&
        nextyThree != (FIELDSIZE - 2) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if(xOne == xTwo && xTwo == xThree && xThree == xFour &&  // Line check rotation 1 and 3
        (gridMap[xOne][nextyOne] == 0 ||
        gridMap[xFour][nextyFour] == 0) &&
        nextyOne != (FIELDSIZE - 2) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if(xOne == xTwo && xTwo == xThree &&  // Mirror L check rotation 1
        (gridMap[xThree][nextyThree] == 0 ||
        gridMap[xFour][nextyFour] == 0) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if(xTwo == xThree && xThree == xFour &&  // Mirror L check rotation 1
        (gridMap[xOne][nextyOne] == 0 ||
        gridMap[xFour][nextyFour] == 0) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();                               // have to check next space as to not go out of bounds

    } else if (xThree == xFour &&                       // L rotation 2 check
        (gridMap[xOne][nextyOne] == 0 &&
        gridMap[xTwo][nextyTwo] == 0 &&
        gridMap[xFour][nextyFour] == 0) &&
        nextyFour != (FIELDSIZE - 2)) {

        makeZero();                                     // makes current space of shape all 0's

        incrementY();                                   // increments current space of shape to appear to move down twice as fast

        insertNum(gridShape);                           // puts shape into grid after moving down

        incrementNextY();

    }

    // no need to print out at all this step bc the shape will appear to move two spaces rather than one

}

void Grid::moveAllDown()
{

     if(xOne == xTwo && xTwo == xThree && xThree == xFour) {  // Line check rotation 1 and 3
        while((gridMap[xOne][nextyOne] == 0 ||          // using while loop bc the shape will move all the way down the grid
            gridMap[xFour][nextyFour] == 0) &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds
        }
    } else if(xOne == xThree && xTwo == xFour) {        // Cube check
        while(gridMap[xThree][nextyThree] == 0 &&       // using while loop bc the shape will move all the way down the grid
            gridMap[xFour][nextyFour] == 0 &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

        }
    } else if ((xOne == xTwo && xTwo == xThree) || (xTwo == xThree && xThree == xFour)) {
        while(((gridMap[xOne][nextyOne] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            (gridMap[xOne][nextyOne] == 0 &&
            gridMap[xThree][nextyThree] == 0)) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();
        }
    } else if ((xOne == xThree && xThree == xFour) || (xOne == xTwo && xTwo == xFour)) {
        while(
            //((gridMap[xTwo][nextyTwo] == 0 &&                    // have to DOUBLE check due to rotation
            //gridMap[xThree][nextyThree] == 0 &&
            //gridMap[xFour][nextyFour] == 0) ||
            //(gridMap[xOne][nextyOne] == 0 &&
            ((gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0) ||
            //(gridMap[xOne][nextyOne] == 0 &&
            (gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0)) &&
            //nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();

        }
    }  else if (xOne == xTwo && xThree == xFour) {              // S shape 1 and 3 rotation check
        while(gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyFour != (FIELDSIZE - 2)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();

            }
    } else if (xThree == xFour) {
        while((gridMap[xOne][nextyOne] == 0 &&
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xFour][nextyFour] == 0)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();

            }
    } else if(xOne == xTwo || xOne == xFour || xOne == xThree) {  // Mirrored L, L, T, S shape check
        while((gridMap[xTwo][nextyTwo] == 0 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1))) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

        }

    } else if(xTwo == xThree) {                         // Z shape check
        while(gridMap[xOne][nextyOne] == 0 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

        }
    } else if(yOne == yTwo && yTwo == yThree && yThree == yFour) { // Line check rotation 0 and 4
        while(gridMap[xOne][nextyOne] == 0 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xTwo][nextyTwo] == 0 &&
            gridMap[xThree][nextyThree] == 0 &&
            gridMap[xFour][nextyFour] == 0 &&
            nextyOne != (FIELDSIZE - 1) &&
            nextyTwo != (FIELDSIZE - 1) &&
            nextyThree != (FIELDSIZE - 1) &&
            nextyFour != (FIELDSIZE - 1)) {

            makeZero();                                 // makes current space of shape all 0's

            incrementY();                               // increments current space of shape to appear to move all the way down

            insertNum(gridShape);                       // puts shape into grid after moving down

            incrementNextY();                           // have to check next space as to not go out of bounds

        }
    }

    yOne--;                                             // decrements y because the original move
    yTwo--;                                             // function still needs to finish executing
    yThree--;
    yFour--;

    // no need to print out at all this step bc the shape will appear to move all the way to the bottom of the grid

}

void Grid::rotate(int gridShape, WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{
    makeZero();                                         // makes current space of shape all 0's

    if(gridShape == 2) {
        if(shapeRotation == 0) {                        // position 0 to position 1
            nextxOne += 2;
            nextxTwo++;
            nextxFour--;
            nextyOne--;
            nextyThree++;
            nextyFour += 2;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxTwo][nextyTwo] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne += 2;
                xTwo++;
                xFour--;
                yOne--;
                yThree++;
                yFour += 2;
                shapeRotation++;
            } else {
                nextxOne -= 2;
                nextxTwo--;
                nextxFour++;
                nextyOne++;
                nextyThree--;
                nextyFour -= 2;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxOne -= 2;
            nextxTwo--;
            nextxFour++;
            nextyOne += 2;
            nextyTwo++;
            nextyFour--;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxTwo][nextyTwo] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne -= 2;
                xTwo--;
                xFour++;
                yOne += 2;
                yTwo++;
                yFour--;
                shapeRotation++;
            } else {
                nextxOne += 2;
                nextxTwo++;
                nextxFour--;
                nextyOne -= 2;
                nextyTwo--;
                nextyFour++;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxOne++;
            nextxThree--;
            nextxFour -= 2;
            nextyOne -= 2;
            nextyTwo--;
            nextyFour++;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[xTwo][nextyTwo] == 0) {
                //gridMap[nextxFour][nextyFour] == 0) { // if line rotation has problems, come back to this line
                xOne++;
                xThree--;
                xFour -= 2;
                yOne -= 2;
                yTwo--;
                yFour++;
                shapeRotation++;
            } else {
                nextxOne--;
                nextxThree++;
                nextxFour += 2;
                nextyOne += 2;
                nextyTwo++;
                nextyFour--;
            }
        } else if(shapeRotation == 3) {                 // position 3 to position 0
            nextxOne--;
            nextxThree++;
            nextxFour += 2;
            nextyOne++;
            nextyThree--;
            nextyFour -= 2;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxThree][nextyThree] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne--;
                xThree++;
                xFour += 2;
                yOne++;
                yThree--;
                yFour -= 2;
                shapeRotation = 0;
            } else {
                nextxOne++;
                nextxThree--;
                nextxFour -= 2;
                nextyOne--;
                nextyThree++;
                nextyFour += 2;
            }
        }

    } else if(gridShape == 3) {
        if(shapeRotation == 0) {                        // position 0 to position 1
        nextxTwo++;
        nextxThree++;
        nextxFour--;
        nextyFour++;

            if(gridMap[nextxFour][nextyFour] == 0) {
                xTwo++;
                xThree++;
                xFour--;
                yFour++;
                shapeRotation++;
            } else {
                nextxTwo--;
                nextxThree--;
                nextxFour++;
                nextyFour--;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxOne--;
            nextyOne++;

            if(gridMap[nextxOne][nextyOne] == 0) {
                xOne--;
                yOne++;
                shapeRotation++;
            } else {
                nextxOne++;
                nextyOne--;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxOne++;
            nextxTwo--;
            nextxThree--;
            nextyOne--;

            if(gridMap[nextxOne][nextyOne] == 0) {
                xOne++;
                xTwo--;
                xThree--;
                yOne--;
                shapeRotation++;
            } else {
                nextxOne--;
                nextxTwo++;
                nextxThree++;
                nextyOne++;
            }
        } else if(shapeRotation == 3) {                 //position 3 to position 0
            nextxFour++;
            nextyFour--;

            if(gridMap[nextxFour][nextyFour] == 0) {
                xFour++;
                yFour--;
                shapeRotation = 0;
            } else {
                nextxFour--;
                nextyFour++;
            }
        }

    } else if(gridShape == 4) {
        if(shapeRotation == 0) {                         // position 0 to position 1
            nextxTwo--;
            nextxThree += 2;
            nextxFour++;
            nextyTwo++;
            nextyFour++;

            if(gridMap[nextxThree][yThree] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xTwo--;
                xThree += 2;
                xFour++;
                yTwo++;
                yFour++;
                shapeRotation++;
            } else {
                nextxTwo++;
                nextxThree -= 2;
                nextxFour--;
                nextyTwo--;
                nextyFour--;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxTwo++;
            nextxThree -= 2;
            nextxFour--;
            nextyOne++;
            nextyThree++;

            if(gridMap[nextxThree][nextyThree] == 0 &&
                gridMap[nextxFour][yFour] == 0) {
                xTwo++;
                xThree -= 2;
                xFour--;
                yOne++;
                yThree++;
                shapeRotation++;
            } else {
                nextxTwo--;
                nextxThree += 2;
                nextxFour++;
                nextyOne--;
                nextyThree--;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxOne--;
            nextxTwo -= 2;
            nextxThree++;
            nextyOne--;
            nextyThree--;

            if(gridMap[nextxOne][nextyOne] == 0) {// &&
                //gridMap[nextxTwo][yTwo] == 0) {
                xOne--;
                xTwo -= 2;
                xThree++;
                yOne--;
                yThree--;
                shapeRotation++;
            } else {
                nextxOne++;
                nextxTwo += 2;
                nextxThree--;
                nextyOne++;
                nextyThree++;
            }
        } else if(shapeRotation == 3) {                 // position 3 to position 0
            nextxOne++;
            nextxTwo += 2;
            nextxThree++;
            nextyTwo--;
            nextyFour--;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxTwo][nextyTwo] == 0) {
                xOne++;
                xTwo += 2;
                xThree++;
                yTwo--;
                yFour--;
                shapeRotation = 0;
            } else {
                nextxOne++;
                nextxTwo += 2;
                nextxThree++;
                nextyTwo--;
                nextyFour--;
            }
        }
    } else if(gridShape == 5) {
        if(shapeRotation == 0) {                         // position 0 to position 1
            nextxOne += 2;
            nextxThree++;
            nextxFour--;
            nextyTwo++;
            nextyFour++;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne += 2;
                xThree++;
                xFour--;
                yTwo++;
                yFour++;
                shapeRotation++;
            } else {
                nextxOne -= 2;
                nextxThree--;
                nextxFour++;
                nextyTwo--;
                nextyFour--;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxOne -= 2;
            nextxThree--;
            nextxFour++;
            nextyOne++;
            nextyThree++;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxThree][nextyThree] == 0) {
                xOne -= 2;
                xThree--;
                xFour++;
                yOne++;
                yThree++;
                shapeRotation++;
            } else {
                nextxOne += 2;
                nextxThree++;
                nextxFour--;
                nextyOne--;
                nextyThree--;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxOne++;
            nextxTwo--;
            nextxFour -= 2;
            nextyOne--;
            nextyThree--;

            if(gridMap[nextxOne][nextyOne] == 0) {//} &&
                //gridMap[nextxFour][yFour] == 0) {
                xOne++;
                xTwo--;
                xFour -= 2;
                yOne--;
                yThree--;
                shapeRotation++;
            } else {
                nextxOne--;
                nextxTwo++;
                nextxFour += 2;
                nextyOne++;
                nextyThree++;
            }
        } else if(shapeRotation == 3) {                 // position 3 to position 0
            nextxOne--;
            nextxTwo++;
            nextxFour += 2;
            nextyTwo--;
            nextyFour--;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                nextxOne--;
                nextxTwo++;
                nextxFour += 2;
                nextyTwo--;
                nextyFour--;
                shapeRotation = 0;;
            } else {
                nextxOne++;
                nextxTwo--;
                nextxFour -= 2;
                nextyTwo++;
                nextyFour++;
            }
        }
    } else if(gridShape == 6) {
        if(shapeRotation == 0) {                         // position 0 to position 1
            nextxOne++;
            nextxTwo += 2;
            nextxFour--;
            nextyTwo--;
            nextyFour++;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxTwo][nextyTwo] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne++;
                xTwo += 2;
                xFour--;
                yTwo--;
                yFour++;
                shapeRotation++;
            } else {
                nextxOne--;
                nextxTwo -= 2;
                nextxFour++;
                nextyTwo++;
                nextyFour--;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxOne--;
            nextxTwo--;
            nextxThree++;
            nextxFour++;
            nextyOne++;
            nextyTwo++;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxThree][yThree] == 0 &&
                gridMap[nextxFour][yFour] == 0) {
                xOne--;
                xTwo--;
                xThree++;
                xFour++;
                yOne++;
                yTwo++;
                shapeRotation++;
            } else {
                nextxOne++;
                nextxTwo++;
                nextxThree--;
                nextxFour--;
                nextyOne--;
                nextyTwo--;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxOne++;
            nextxThree -= 2;
            nextxFour--;
            nextyOne--;
            nextyThree++;

            if(gridMap[nextxOne][nextyOne] == 0 &&
                gridMap[nextxThree][nextyThree] == 0 &&
                gridMap[nextxFour][yFour] == 0) {
                xOne++;
                xThree -= 2;
                xFour--;
                yOne--;
                yThree++;
                shapeRotation++;
            } else {
                nextxOne--;
                nextyThree += 2;
                nextxFour++;
                nextyOne++;
                nextyThree--;
            }
        } else if(shapeRotation == 3) {                 // position 3 to position 0
            nextxOne--;
            nextxTwo--;
            nextxThree++;
            nextxFour++;
            nextyThree--;
            nextyFour--;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxTwo][yTwo] == 0 &&
                gridMap[nextxFour][nextyFour] == 0) {
                xOne--;
                xTwo--;
                xThree++;
                xFour++;
                yThree--;
                yFour--;
                shapeRotation = 0;
            } else {
                nextxOne++;
                nextxTwo++;
                nextxThree++;
                nextxFour--;
                nextyThree++;
                nextyFour++;
            }
        }
    } else if(gridShape == 7) {
        if(shapeRotation == 0) {                         // position 0 to position 1
            nextxOne--;
            nextxTwo++;
            nextyThree++;
            nextyFour++;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[xThree][nextyThree] == 0 &&
                gridMap[xFour][nextyFour] == 0) {
                xOne--;
                xTwo++;
                yThree++;
                yFour++;
                shapeRotation++;
            } else {
                nextxOne++;
                nextxTwo--;
                nextyThree--;
                nextyFour--;
            }
        } else if(shapeRotation == 1) {                 // position 1 to position 2
            nextxOne--;
            nextxThree++;
            nextxFour -= 2;
            nextyOne++;
            nextyThree--;

            if(//gridMap[nextxOne][nextyOne] == 0) {//} &&
                gridMap[nextxThree][nextyThree] == 0) {//} &&
                //gridMap[nextxFour][yFour] == 0) {
                xOne--;
                xThree++;
                xFour -= 2;
                yOne++;
                yThree--;
                shapeRotation++;
            } else {
                nextxOne++;
                nextxThree--;
                nextxFour += 2;
                nextyOne--;
                nextyThree++;
            }
        } else if(shapeRotation == 2) {                 // position 2 to position 3
            nextxThree--;
            nextxFour++;
            nextyOne--;
            nextyTwo--;

            if(gridMap[xOne][nextyOne] == 0 &&
                gridMap[nextxTwo][yTwo] == 0 &&
                gridMap[nextxFour][yFour] == 0) {
                xThree--;
                xFour++;
                yOne--;
                yTwo--;
                shapeRotation++;
            } else {
                nextxThree++;
                nextxFour--;
                nextyOne++;
                nextyTwo++;
            }
        } else if(shapeRotation == 3) {                 // position 3 to position 0
            nextxOne += 2;
            nextxTwo--;
            nextxFour++;
            nextyTwo++;
            nextyFour--;

            if(gridMap[nextxOne][yOne] == 0 &&
                gridMap[nextxTwo][nextyTwo] == 0 &&
                gridMap[xFour][nextyFour] == 0) {
                xOne += 2;
                xTwo--;
                xFour++;
                yTwo++;
                yFour--;
                shapeRotation = 0;
            } else {
                nextxOne -= 2;
                nextxTwo++;
                nextxFour--;
                nextyTwo++;
                nextyFour++;
            }
        }
    }

        insertNum(gridShape);                           // sets shape to original spot if not able to be rotated

}

void Grid::clearRow()                                   // clears row if it's full
{
    int rowFull = 0;                                    // counter that adds by one and if it
        for(int i = 1; i < FIELDSIZE - 1; i++) {       // equals row size, it means row is full
            for(int j = 1; j < FIELDSIZE - 1; j++) {
                if(gridMap[j][i] != 0) {                //as long as it doesn't equal 0, increment
                rowFull++;
                }
            }
            if(rowFull == FIELDSIZE - 2) {             // checks to see if row is full
                    whichRow = i;
                    for(int z = 1; z < FIELDSIZE - 1; z++) {
                        gridMap[z][i] = 0;
                    }
                    shiftRow();
                    _score += 20;
            }                                           // resets counter back to zero after checking a row
             rowFull = 0;
        }
    refresh();

}

void Grid::shiftRow()
{

    for(int i = whichRow; i >= 0; i--) {
        for(int j = 0; j < FIELDSIZE - 1; j++) {
            gridMap[j][i] = gridMap[j][i - 1];
        }
    }
}

void Grid::draw_borders(WINDOW *screen) {               // draws borders for each window
    int x, y, i;

  getmaxyx(screen, y, x);
  wattron(screen, COLOR_PAIR(10));                      //starts the borders printing yellow
  mvwprintw(screen, 0, 0, "+");                         // makes the 4 corners of the map
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");


  for (i = 1; i < (y - 1); i++) {                       // makes the sides of the map
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }

  for (i = 1; i < (x - 1); i++) {                       // makes the top and bottom of the map
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
  wattroff(screen, COLOR_PAIR(10));                     //ends the borders printing yellow

}

void Grid::printMenu(WINDOW *menu)
{
    char ch;


    keypad(menu, true);
    do{
        draw_borders(menu);
        wattron(menu, A_BOLD);
        mvwprintw(menu, 4, 3, "K-TRIS: A TETRIS INSPIRED GAME");
        mvwprintw(menu, 5, 3, "Press  'k'  to begin.");
        wattroff(menu, A_BOLD);

        wattron(menu, COLOR_PAIR(13));
        mvwprintw(menu, 2, 2, "/ / / / / / / / / / / / / / / / / / / / / / / / /");
        mvwprintw(menu, 7, 2, "/ / / / / / / / / / / / / / / / / / / / / / / / /");


        touchwin(menu);
        wrefresh(menu);
        sleep(1);
    }while ((ch = getch()) != 'k');

}

void Grid::printField(WINDOW *field)                    // prints full field window
{
    wclear(field);
    //wattron(field, A_BOLD);                                //brightens the shapes so you can see the grid better for testing.
	for (int i = 1; i < FIELDSIZE - 1; i++) {
		for (int j = 1; j < FIELDSIZE - 1; j++) {
			draw_borders(field);

			if (gridMap[i][j] == 0)
			{
			    wattron(field, COLOR_PAIR(11));                     //prints the 0s in black
				mvwprintw(field, j, i, "%d", getCoord(i, j));
            } else {
				wattron(field, COLOR_PAIR(gridMap[i][j]));          //gets color from insertShape function
				mvwprintw(field, j, i, "%d", getCoord(i, j));
			}
		}
	}

    touchwin(field);                                    //this is just to makes sure that changes are made to the field window.
	wrefresh(field);
}

void Grid::printNextShapes(WINDOW *nextShapes)          // prints full nextShapes window
{
    wclear(nextShapes);

    draw_borders(nextShapes);

    mvwprintw(nextShapes, 1, 1, "Next Shape: ");
    int y = 3;                                          // coordinates for where shape is printed
    int x = 10;                                         // coordinates for where shape is printed
    int i = 0;                                          // for range based for loop
    Shapes tmp;
    for(auto it : shapelist) {
        tmp = it.getShapeID();
        tmp.printShape(nextShapes, y, x);
        y += 3;                                         // so that there's spaces between the shapes
        i++;
    }
    touchwin(nextShapes);
    wrefresh(nextShapes);

}

void Grid::printScore(WINDOW *score)                    // prints full score window
{
    wclear(score);
    draw_borders(score);
    wattron(score, A_BOLD);
    mvwprintw(score,1, 1, "Score: ");
    mvwprintw(score, 1, 8, "%d", _score);
    wattroff(score, A_BOLD);
    wrefresh(score);
}

void Grid::printInstructions(WINDOW *instructions)
{
    wclear(instructions);
    draw_borders(instructions);
    wattron(instructions, A_BOLD);
    wattron(instructions, COLOR_PAIR(12));
    mvwprintw(instructions, 1, 3, " < < < < < < < < < ");
    wattroff(instructions, COLOR_PAIR(12));
    mvwprintw(instructions, 2, 3, " ");
    mvwprintw(instructions, 3, 3, "Keys to Play:");
    mvwprintw(instructions, 4, 3, " ");
    mvwprintw(instructions, 5, 3, "'a' - Left");
    mvwprintw(instructions, 6, 3, " ");
    mvwprintw(instructions, 7, 3, "'d' - Right");
    mvwprintw(instructions, 8, 1, " ");
    mvwprintw(instructions, 9, 3, "'s' - Down");
    mvwprintw(instructions, 10, 1, " ");
    mvwprintw(instructions, 11, 3, "'r' - Rotate");
    mvwprintw(instructions, 12, 1, " ");
    mvwprintw(instructions, 13, 3, "Spacebar - All Down");
    mvwprintw(instructions, 14, 1, " ");
    wattron(instructions, COLOR_PAIR(12));
    mvwprintw(instructions, 15, 3, "> > > > > > > > >");
    wattroff(instructions, COLOR_PAIR(12));
    wattroff(instructions, A_BOLD);
    wrefresh(instructions);


}

void Grid::gameOverDisp(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions)   // creates/prints full gameOverDisp window
{
    wclear(field);                                      // still need to find a way to delete windows
    wclear(nextShapes);                                 // probs can throw an exception
    wclear(score);
    wclear(instructions);
    wrefresh(field);
    wrefresh(nextShapes);
    wrefresh(score);
    wrefresh(instructions);


    WINDOW *gameOver = newwin(24, 48, 0, 0);
    while(1)
    {
    draw_borders(gameOver);
    mvwprintw(gameOver, 4, 8, "G A M E  O V E R");
    mvwprintw(gameOver, 6, 8, "Please click 'ctrl+c' to exit");
    mvwprintw(gameOver, 10, 14, "SCORE: ");
    mvwprintw(gameOver, 10, 21, "%d", _score);
    wattron(gameOver, COLOR_PAIR(13));
    mvwprintw(gameOver, 8, 12, "* * * * * * * * *");
    mvwprintw(gameOver, 12, 12, "* * * * * * * * *");
    wattroff(gameOver, COLOR_PAIR(13));
    wrefresh(gameOver);
    sleep(10);
    }

}

void Grid::runGame(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions)
{

        printField(field);

        printNextShapes(nextShapes);

        printScore(score);

        printInstructions(instructions);


        pullShape(field, nextShapes, score, instructions);

        wclear(field);
        wclear(nextShapes);
        wclear(score);

        draw_borders(nextShapes);
        draw_borders(field);

        printField(field);
        sleep(1);

        move(field, nextShapes, score);   // takes care of moving shape

        printField(field);


        /*fillRow();                    testing score and collision detection
        printField(field);
        wrefresh(field);*/

        clearRow();
        wrefresh(field);
        printField(field);
        wrefresh(field);

        sleep(1);


}

void Grid::fillRow()                                    // for testing purposes
{
    for(int j = 1; j < FIELDSIZE - 1; j++) {
        gridMap[j][8] = 1;
        gridMap[j][4] = 1;
    }
}

void Grid::insertNum(int gridShape) {
    switch(gridShape) {
        case 1:
            gridMap[xOne][yOne] = 1;                    // puts 1's
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;
            break;
        case 2:
            gridMap[xOne][yOne] = 2;                    // puts 2's
            gridMap[xTwo][yTwo] = 2;
            gridMap[xThree][yThree] = 2;
            gridMap[xFour][yFour] = 2;
            break;
        case 3:
            gridMap[xOne][yOne] = 3;                    // puts 3's
            gridMap[xTwo][yTwo] = 3;
            gridMap[xThree][yThree] = 3;
            gridMap[xFour][yFour] = 3;
            break;
        case 4:
            gridMap[xOne][yOne] = 4;                    // puts 4's
            gridMap[xTwo][yTwo] = 4;
            gridMap[xThree][yThree] = 4;
            gridMap[xFour][yFour] = 4;
            break;
        case 5:
            gridMap[xOne][yOne] = 5;                    // puts 5's
            gridMap[xTwo][yTwo] = 5;
            gridMap[xThree][yThree] = 5;
            gridMap[xFour][yFour] = 5;
            break;
        case 6:
            gridMap[xOne][yOne] = 6;                    // puts 6's
            gridMap[xTwo][yTwo] = 6;
            gridMap[xThree][yThree] = 6;
            gridMap[xFour][yFour] = 6;
            break;
        case 7:
            gridMap[xOne][yOne] = 7;                    // puts 7's
            gridMap[xTwo][yTwo] = 7;
            gridMap[xThree][yThree] = 7;
            gridMap[xFour][yFour] = 7;
            break;
    }
}

void Grid::incrementNextX() {
    nextxOne = xOne + 1;
    nextxTwo = xTwo + 1;
    nextxThree = xThree + 1;
    nextxFour = xFour + 1;
}

void Grid::incrementNextY() {
    nextyOne = yOne + 1;
    nextyTwo = yTwo + 1;
    nextyThree = yThree + 1;
    nextyFour = yFour + 1;
}

void Grid::decrementNextX() {
    nextxOne = xOne - 1;
    nextxTwo = xTwo - 1;
    nextxThree = xThree - 1;
    nextxFour = xFour - 1;
}

void Grid::incrementX() {
    xOne++;
    xTwo++;
    xThree++;
    xFour++;
}

void Grid::incrementY() {
    yOne++;
    yTwo++;
    yThree++;
    yFour++;
}

void Grid::decrementX() {
    xOne--;
    xTwo--;
    xThree--;
    xFour--;
}

void Grid::makeZero() {
    gridMap[xOne][yOne] = 0;
    gridMap[xTwo][yTwo] = 0;
    gridMap[xThree][yThree] = 0;
    gridMap[xFour][yFour] = 0;
}
