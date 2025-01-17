/*
Testris Inspired Game - Project for Data Structures
Kelsi Andrews
Karen Nason
*/

#include "Shapes.hpp"
#include <iostream>

Shapes::Shapes()
    :shapeID(0)
    {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                shape[i][j] = 0;
            }
        }
    }

Shapes::Shapes(int shapeID)
    :shapeID(shapeID)
    {
        makeShape(shapeID);
        //makeShape(3);
    }

int Shapes::getShapeID() {
    return shapeID;
    //return 3;
}

int Shapes::getShape(int x, int y) { //this needs to change with size of grid
    if(y < 2 && x < 4)
        return shape[y][x];
    else
        throw std::out_of_range("you're going out of bounds somewhere");
}

/*
*   1 = cube
*   2 = line
*   3 = T shape
*   4 = S shape
*   5 = Z shape
*   6 = L shape
*   7 = mirrored L shape
*/
void Shapes::makeShape(int shapeID) {
    switch(shapeID) {
        case 1:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 1 || j == 2){
                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 2:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 0){
                        shape[i][j] = 2;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 3:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 1) {
                        shape[i][j] = 3;
                    } else if(i == 1 && j != 3){
                        shape[i][j] = 3;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 4:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 1) {
                        shape[i][j] = 4;
                    } else if(i == 1 && j ==0) {
                        shape[i][j] = 4;
                    } else if(i == 0 && j == 2) {
                        shape[i][j] = 4;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 5:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 1) {
                        shape[i][j] = 5;
                    } else if(i == 0 && j == 0) {
                        shape[i][j] = 5;
                    } else if(i == 1 && j == 2) {
                        shape[i][j] = 5;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 6:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 0){
                        shape[i][j] = 6;
                    } else if(i == 1 && j != 3){
                        shape[i][j] = 6;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 7:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(j == 2){
                        shape[i][j] = 7;
                    } else if(i == 1 && j != 3){
                        shape[i][j] = 7;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        default:
            break;
    }
}


void Shapes::printShape(WINDOW* nextShapes, int y, int x) {

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {

                if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(11));                     //prints 0s black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(shapeID));                     //next shape prints shapeID color_pair.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }

            x++;
        }

        x -= 4;
        y++;
    }
}
