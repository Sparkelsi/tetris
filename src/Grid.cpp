#include "Grid.hpp"
#include "Shapes.hpp"
#include <ncurses.h>
#include <iostream>
#include <random>



Grid::Grid()
    {
        for(int i = 0; i < FIELDSIZEY; i++) {
            for(int j = 0; j < FIELDSIZEX; j++) {
                gridMap[i][j] = 0; //nullptr
            }
        }
    }

void Grid::printGrid()                                  // prints entire grid's data
{

    for(int i = 1; i < FIELDSIZEY - 1; i++) {
        for(int j = 1; j < FIELDSIZEX - 1; j++) {
            if(gridMap[i][j] == 0) {
        
                printw("%d", gridMap[i][j]);
            }
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

void Grid::insertShape(Shapes z, WINDOW *field, WINDOW *nextShapes, WINDOW *score) // will always be inserted at same insertion point
{

    int x;
    int y;                                              // i and j are at insertion point (middle top of grid)
        for(int i = 1; i < 3; i++) {
            for(int j = 6; j < 10; j++) {
                x = i - 1;                              // place holders so i and j aren't affected
                y = j - 6;
                if(gridMap[j][i] == 1) {
                    gameOverDisp(field, nextShapes, score);     //displays game over window if top pieces hit top of grid
                } else {

                    gridMap[j][i] = z.getShape(y, x);           // copies the shape into the grid
                }
            }
        }
}

void Grid::pullShape(WINDOW *field, WINDOW *nextShapes, WINDOW *score)     // make sure to take score out, just testing things
{
    if(shapelist.empty()) {                             // creates list in case one is not already made
        createList();
    }

    insertShape(shapelist.front(), field, nextShapes, score);       // inserts first shape into the grid
    shapelist.pop_front();                                          // deleting first item in the list
    shapelist.push_back(getRandomShape());                          // adding another random shape to back of list
   // printField(field);                                            // prints list at the end
}

int Grid::getCoord(int y, int x)
{
    return gridMap[y][x];   //returns coordinates of the grid specifically for printing the field
}

void Grid::resetGrid()                                  // testing purposes only
{
    for(int i = 0; i < FIELDSIZEY; i++) {               //resets grid, only for testing as of now
        for(int j = 0; j < FIELDSIZEX; j++)
        {
            gridMap[i][j] = 0;
        }
    }
}


void Grid::move(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{

   int z = 0;                                           // i and j are at insertion point
    for(int i = 1; i < 3; i++) {                        // using specific i and j for more efficiency (this is where the shape is inserted)
        for(int j = 6; j < 10; j++) {
            if(gridMap[j][i] == 1 && z == 0) {          // loops through to get coordinates of each piece of the shape
                yOne = i;
                xOne = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] == 1 && z == 1) {
                yTwo = i;
                xTwo = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] == 1 && z == 2) {
                yThree = i;
                xThree = j;
                z++;
                gridMap[j][i] = 0;
            } else if (gridMap[j][i] == 1 && z == 3) {
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

    nextyOne = yOne + 1;                                // have to check next space as to not go out of bounds
    nextyTwo = yTwo + 1;
    nextyThree = yThree + 1;
    nextyFour = yFour + 1;

    if(xOne == xThree && xTwo == xFour) {               // Cube check
        while(gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            }

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyThree = yThree + 1;                    // have to check next space as to not go out of bounds
            nextyFour = yFour + 1;

            printField(field);                          // reprints everything out appearing to move down one space
            printNextShapes(nextShapes);
            printScore(score);
            sleep(1);
        }
    } else if(xOne == xTwo || xOne == xFour || xOne == xThree) {    // Mirrored L, L, T, S Shape check
        while(gridMap[xTwo][nextyTwo] != 1 &&
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyTwo != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            }

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyTwo = yTwo + 1;                        // have to check next space as to not go out of bounds
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;


            printField(field);                          // reprints everything out appearing to move down one space
            printNextShapes(nextShapes);
            printScore(score);
            sleep(1);

        }

    } else if(xTwo == xThree) {                         // Z shape check
        while(gridMap[xOne][nextyOne] != 1 &&
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyOne != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            }

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyOne = yOne + 1;                        // have to check next space as to not go out of bounds
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

            printField(field);                          // reprints everything out appearing to move down one space
            printNextShapes(nextShapes);
            printScore(score);
            sleep(1);

        }
    } else {                                            // Line check
        while(gridMap[xOne][nextyOne] != 1 &&
            gridMap[xTwo][nextyTwo] != 1 &&
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyOne != (FIELDSIZEY - 1) &&
            nextyTwo != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            halfdelay(1);                               // continues if no input is given
            key = getch();                              // gets user input

            if(key == 'd') {
                moveRight(field, nextShapes, score);
            } else if (key == 'a') {
                moveLeft(field, nextShapes, score);
            } else if (key == 's') {
                moveDown();
            } else if (key == ' ') {
                moveAllDown();
            }

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move down
            yTwo++;
            yThree++;
            yFour++;

            attron(COLOR_PAIR(2));
            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyOne = yOne + 1;                        // have to check next space as to not go out of bounds
            nextyTwo = yTwo + 1;
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

            printField(field);                          // reprints everything out appearing to move down one space
            printNextShapes(nextShapes);
            printScore(score);
            sleep(1);

        }

    }

    // gridMap[xOne][yOne] = 1;                         // reassigns 1's to where the shape was if it can't move
    // gridMap[xTwo][yTwo] = 1;                         // bc previously the shape was made into 0's
    // gridMap[xThree][yThree] = 1;                     // testing to see if arbitray, take out if nothing breaks
    // gridMap[xFour][yFour] = 1;

    //cbreak(); // not sure if needed

    printField(field);                                  // reprints everything out once the shape can no longer move down
    printNextShapes(nextShapes);
    printScore(score);

}


void Grid::moveRight(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{

    if(yOne == yTwo && yTwo == yThree && yThree == yFour &&     // Line check
        gridMap[nextxFour][yFour] != 1 &&
        nextxFour != (FIELDSIZEX - 1)) {

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne++;                                         // increments current space of shape to appear to move right
        xTwo++;
        xThree++;
        xFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving right
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxFour = xFour + 1;                          // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

    } else if(yTwo == yThree && yThree == yFour &&      // Mirrored L, L, T shape check
        gridMap[nextxOne][yOne] != 1 &&
        gridMap[nextxFour][yFour] != 1 &&
        nextxOne != (FIELDSIZEX - 1) &&
        nextxFour != (FIELDSIZEX - 1)) {

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne++;                                         // increments current space of shape to appear to move right
        xTwo++;
        xThree++;
        xFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving right
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxOne = xOne + 1;                            // have to check next space as to not go out of bounds
        nextxFour = xFour + 1;

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

    } else if(yOne == yTwo && yThree == yFour &&        // Cube, S, Z shape check
        gridMap[nextxTwo][yTwo] != 1 &&
        gridMap[nextxFour][yFour] != 1 &&
        nextxTwo != (FIELDSIZEX - 1) &&
        nextxFour != (FIELDSIZEX - 1)) {

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne++;                                         // increments current space of shape to appear to move right
        xTwo++;
        xThree++;
        xFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving right
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxTwo = xTwo + 1;                            // have to check next space as to not go out of bounds
        nextxFour = xFour + 1;

        printField(field);                              // reprints everything out appearing to move right one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

        }

    // gridMap[xOne][yOne] = 1;                         // reassigns 1's to where the shape was if it can't move
    // gridMap[xTwo][yTwo] = 1;                         // bc previously the shape was made into 0's
    // gridMap[xThree][yThree] = 1;                     // testing to see if arbitray, take out if nothing breaks
    // gridMap[xFour][yFour] = 1;

    printField(field);                                  // reprints everything out if the shape can't move right
    printNextShapes(nextShapes);
    printScore(score);

}

void Grid::moveLeft(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
{
    if(yOne == yTwo && yTwo == yThree && yThree == yFour &&     // Line check
        gridMap[nextxOne][yOne] != 1 &&
        nextxOne != 0){

    gridMap[xOne][yOne] = 0;                            // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne--;                                         // decrements current space of shape to appear to move left
        xTwo--;
        xThree--;
        xFour--;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving left
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxOne = xOne - 1;                            // have to check next space as to not go out of bounds

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

    } else if(yTwo == yThree && yThree == yFour &&      // Mirrored L, L, T shape check
        gridMap[nextxOne][yOne] != 1 &&
        gridMap[nextxTwo][yTwo] != 1 &&
        nextxOne != 0 &&
        nextxTwo != 0){

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne--;                                         // decrements current space of shape to appear to move left
        xTwo--;
        xThree--;
        xFour--;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving left
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxOne = xOne - 1;                            // have to check next space as to not go out of bounds
        nextxTwo = xTwo - 1;

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

    } else if(yOne == yTwo && yThree == yFour &&        // Cube, S, Z shape check
        gridMap[nextxOne][yOne] != 1 &&
        gridMap[nextxThree][yThree] != 1 &&
        nextxOne != 0 &&
        nextxThree != 0){

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        xOne--;                                         // decrements current space of shape to appear to move left
        xTwo--;
        xThree--;
        xFour--;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving left
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextxOne = xOne - 1;                            // have to check next space as to not go out of bounds
        nextxThree = xThree - 1;

        printField(field);                              // reprints everything out appearing to move left one space
        printNextShapes(nextShapes);
        printScore(score);
        sleep(1);

    }

    // gridMap[xOne][yOne] = 1;                         // reassigns 1's to where the shape was if it can't move
    // gridMap[xTwo][yTwo] = 1;                         // bc previously the shape was made into 0's
    // gridMap[xThree][yThree] = 1;                     // testing to see if arbitray, take out if nothing breaks
    // gridMap[xFour][yFour] = 1;

    printField(field);                                  // reprints everything out if the shape can't move left
    printNextShapes(nextShapes);
    printScore(score);

}

void Grid::moveDown()
{
    if(xOne == xThree && xTwo == xFour &&               // Cube check
        gridMap[xThree][nextyThree] != 1 &&
        gridMap[xFour][nextyFour] != 1 &&
        nextyThree != (FIELDSIZEY - 2) &&
        nextyFour != (FIELDSIZEY - 2)) {


        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        yOne++;                                         // increments current space of shape to appear to move down twice as fast
        yTwo++;
        yThree++;
        yFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving down twice as fast
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextyThree = yThree + 1;                        // have to check next space as to not go out of bounds
        nextyFour = yFour + 1;

    } else if((xOne == xTwo || xOne == xFour || xOne == xThree) &&  // Mirrored L, L, T, S shape check
            gridMap[xTwo][nextyTwo] != 1 &&
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyTwo != (FIELDSIZEY - 2) &&
            nextyThree != (FIELDSIZEY - 2) &&
            nextyFour != (FIELDSIZEY - 2)) {

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move down twice as fast
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down twice as fast
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyTwo = yTwo + 1;                        // have to check next space as to not go out of bounds
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

    } else if(xTwo == xThree &&                         // Z shape check
        gridMap[xOne][nextyOne] != 1 &&
        gridMap[xThree][nextyThree] != 1 &&
        gridMap[xFour][nextyFour] != 1 &&
        nextyOne != (FIELDSIZEY - 2) &&
        nextyThree != (FIELDSIZEY - 2) &&
        nextyFour != (FIELDSIZEY - 2)) {

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        yOne++;                                         // increments current space of shape to appear to move down twice as fast
        yTwo++;
        yThree++;
        yFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving down twice as fast
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextyOne = yOne + 1;                            // have to check next space as to not go out of bounds
        nextyThree = yThree + 1;
        nextyFour = yFour + 1; ;

    } else if (gridMap[xOne][nextyOne] != 1 &&          // Line check
        gridMap[xTwo][nextyTwo] != 1 &&
        gridMap[xThree][nextyThree] != 1 &&
        gridMap[xFour][nextyFour] != 1 &&
        nextyOne != (FIELDSIZEY - 2) &&
        nextyTwo != (FIELDSIZEY - 2) &&
        nextyThree != (FIELDSIZEY - 2) &&
        nextyFour != (FIELDSIZEY - 2)) {

        gridMap[xOne][yOne] = 0;                        // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 0;
        gridMap[xThree][yThree] = 0;
        gridMap[xFour][yFour] = 0;

        yOne++;                                         // increments current space of shape to appear to move down twice as fast
        yTwo++;
        yThree++;
        yFour++;

        gridMap[xOne][yOne] = 1;                        // puts 1's where shape is after moving down twice as fast
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

        nextyOne = yOne + 1;                            // have to check next space as to not go out of bounds
        nextyTwo = yTwo + 1;
        nextyThree = yThree + 1;
        nextyFour = yFour + 1;

    }

    // gridMap[xOne][yOne] = 1;                         // reassigns 1's to where the shape was if it can't move
    // gridMap[xTwo][yTwo] = 1;                         // bc previously the shape was made into 0's
    // gridMap[xThree][yThree] = 1;                     // testing to see if arbitray, take out if nothing breaks
    // gridMap[xFour][yFour] = 1;

    // no need to print out at all this step bc the shape will appear to move two spaces rather than one

}

void Grid::moveAllDown()
{
    if(xOne == xThree && xTwo == xFour) {               // Cube check
        while(gridMap[xThree][nextyThree] != 1 &&       // using while loop bc the shape will move all the way down the grid
            gridMap[xFour][nextyFour] != 1 &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;              //set = to ' ' appears to stop the
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move all the way down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyThree = yThree + 1;                    // have to check next space as to not go out of bounds
            nextyFour = yFour + 1;

        }
    } else if(xOne == xTwo || xOne == xFour || xOne == xThree) {  // Mirrored L, L, T, S shape check
        while(gridMap[xTwo][nextyTwo] != 1 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyTwo != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move all the way down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyTwo = yTwo + 1;                        // have to check next space as to not go out of bounds
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

        }

    } else if(xTwo == xThree) {                         // Z shape check
        while(gridMap[xOne][nextyOne] != 1 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyOne != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move all the way down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyOne = yOne + 1;
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

        }
    } else {                                            // Line check
        while(gridMap[xOne][nextyOne] != 1 &&           // using while loop bc the shape will move all the way down the grid
            gridMap[xTwo][nextyTwo] != 1 &&
            gridMap[xThree][nextyThree] != 1 &&
            gridMap[xFour][nextyFour] != 1 &&
            nextyOne != (FIELDSIZEY - 1) &&
            nextyTwo != (FIELDSIZEY - 1) &&
            nextyThree != (FIELDSIZEY - 1) &&
            nextyFour != (FIELDSIZEY - 1)) {

            gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
            gridMap[xTwo][yTwo] = 0;
            gridMap[xThree][yThree] = 0;
            gridMap[xFour][yFour] = 0;

            yOne++;                                     // increments current space of shape to appear to move all the way down
            yTwo++;
            yThree++;
            yFour++;

            gridMap[xOne][yOne] = 1;                    // puts 1's where shape is after moving down
            gridMap[xTwo][yTwo] = 1;
            gridMap[xThree][yThree] = 1;
            gridMap[xFour][yFour] = 1;

            nextyOne = yOne + 1;                        // have to check next space as to not go out of bounds
            nextyTwo = yTwo + 1;
            nextyThree = yThree + 1;
            nextyFour = yFour + 1;

        }
    }

    yOne--;                                             // decrements y because the original move
    yTwo--;                                             // function still needs to finish executing
    yThree--;
    yFour--;

    // no need to print out at all this step bc the shape will appear to move all the way to the bottom of the grid

}

void Grid::rotate(WINDOW *field, WINDOW *nextShapes, WINDOW *score)
// might need rotate private data, getRotate(); and setRotate(); in shapes class
{
    gridMap[xOne][yOne] = 0;                    // makes current space of shape all 0's
    gridMap[xTwo][yTwo] = 0;
    gridMap[xThree][yThree] = 0;
    gridMap[xFour][yFour] = 0;

    if((yOne == yTwo && yOne == yThree && yOne == yFour) ||
        (xOne == xTwo && xOne == xThree && xOne == xFour)) {   // Line check
        // position 1 to position 2
        xOne += 2;
        xTwo++;
        xFour--;
        yOne--;
        yThree++;
        yFour += 2;
        // position 2 to position 3
        xOne -= 2;
        xTwo--;
        xFour++;
        yOne += 2;
        yTwo++;
        yFour--;
        // position 3 to position 4
        xOne++;
        xThree--;
        xFour -= 2;
        yOne -= 2;
        yTwo--;
        yFour++;
        //position 4 to position 1
        xOne--;
        xThree++;
        xFour += 2;
        yOne++;
        yThree--;
        yFour -= 2;

    }

        gridMap[xOne][yOne] = 1;                    // makes current space of shape all 0's
        gridMap[xTwo][yTwo] = 1;
        gridMap[xThree][yThree] = 1;
        gridMap[xFour][yFour] = 1;

}

void Grid::clearRow()                                   // clears row if it's full
{                   // probs should add a shift row
    int rowFull = 0;                                    // counter that adds by one and if it
        for(int i = 1; i < FIELDSIZEY - 1; i++) {       // equals row size, it means row is full
            for(int j = 1; j < FIELDSIZEX - 1; j++) {
                if(gridMap[j][i] == 1) {
                rowFull++;
                }
            }
            if(rowFull == FIELDSIZEX - 2) {             // checks to see if row is full
                    for(int z = 1; z < FIELDSIZEX - 1; z++) {
                        gridMap[z][i] = 0;
                    }
            }                                           // resets counter back to zero after checking a row
             rowFull = 0;
        }
}

void Grid::draw_borders(WINDOW *screen) {               // draws borders for each window
    int x, y, i;

  getmaxyx(screen, y, x);
  wattron(screen, COLOR_PAIR(2));                       //starts the borders printing yellow
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
  wattroff(screen, COLOR_PAIR(2));                      //ends the borders printing yellow

}

void Grid::printField(WINDOW *field)                    // prints full field window
{


    for(int i = 1; i < FIELDSIZEY - 1; i++) {
        for(int j = 1; j < FIELDSIZEX - 1; j++) {
            draw_borders(field);

            wattron(field, COLOR_PAIR(1));              //makes the 0s and 1s cyan
            mvwprintw(field, j, i, "%d", getCoord(i, j)); // prints data of grid in the field window

        }


    }
    touchwin(field);                                //this is just to makes sure that changes are made to the field window.
    wrefresh(field);

    wclear(field);

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
    mvwprintw(score, 1, 1, "Score: ");
    wrefresh(score);
}

void Grid::gameOverDisp(WINDOW *field, WINDOW *nextShapes, WINDOW *score)   // creates/prints full gameOverDisp window
{
    wclear(field);                                      // still need to find a way to delete windows
    wclear(nextShapes);                                 // probs can throw an exception
    wclear(score);
    wrefresh(field);
    wrefresh(nextShapes);
    wrefresh(score);


    WINDOW *gameOver = newwin(24, 48, 0, 0);

    draw_borders(gameOver);
    mvwprintw(gameOver, 1, 1, "G A M E  O V E R");
    mvwprintw(gameOver, 2, 1, "Please click 'ctrl+c' to exit");
    wrefresh(gameOver);
    sleep(2);
}

void Grid::fillRow()                                    // for testing purposes
{
    for(int j = 1; j < FIELDSIZEX - 1; j++) {
        gridMap[j][8] = 1;
        gridMap[j][4] = 1;
    }
}
