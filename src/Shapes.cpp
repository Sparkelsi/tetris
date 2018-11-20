#include "Shapes.hpp"
#include <iostream>

// #define SHAPEI = 2;
// #define SHAPEJ = 4;

Shapes::Shapes() 
    :shapeID(0)
    {
        for(int i = 0; i < SHAPEI; i++) {
            for(int j = 0; j < SHAPEJ; j++) {
                shape[i][j] = 0;
            }
        }
    }

Shapes::Shapes(int shapeID)
    :shapeID(shapeID)
    {
        makeShape(shapeID);
    }

int Shapes::getShapeID() {
    return shapeID;
}

int Shapes::getShape(int x, int y) { //this needs to change with size of grid
    // for(int i = 0; i < SHAPEI; i++) {
    //     for(int j = 0; j < SHAPEJ; j++) {
    //         if(i == y) {
    //             if(j == x) {
    //                 return shape[x][y];
    //             }
    //         }
    //     }
    // }
    //std::cout << "you did something wrong\n";
    if(y < SHAPEI && x < SHAPEJ)
        return shape[y][x];
    else
        throw std::out_of_range("wrong");
}

/*  1 = cube
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
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 1 || j == 2){

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();                      //refresh() added after every break to negate the affect of sleep(1).
            break;
        case 2:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(i == 1){

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 3:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 1) {

                        shape[i][j] = 1;
                    } else if(i == 1 && j != 3){

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 4:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 1) {

                        shape[i][j] = 1;
                    } else if(i == 1 && j ==0) {

                        shape[i][j] = 1;
                    } else if(i == 0 && j == 2) {

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 5:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 1) {

                        shape[i][j] = 1;
                    } else if(i == 0 && j == 0) {

                        shape[i][j] = 1;
                    } else if(i == 1 && j == 2) {

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 6:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 0){

                        shape[i][j] = 1;
                    } else if(i == 1 && j != 3){

                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            refresh();
            break;
        case 7:
            for(int i = 0; i < SHAPEI; i++) {
                for(int j = 0; j < SHAPEJ; j++) {
                    if(j == 2){

                        shape[i][j] = 1;
                    } else if(i == 1 && j != 3){

                        shape[i][j] = 1;
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

    for(int i = 0; i < SHAPEI; i++) {
        for(int j = 0; j < SHAPEJ; j++) {

            if(shapeID == 1){
                if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                     //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(1));                     //next shape prints cyan.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 2){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                      //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(10));                     //next shape prints yellow.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 3){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                         //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(3));                     //next shape prints red.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 4){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                      //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(4));                     //next shape prints green.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 5){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                      //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(9));                     //next shape prints white.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 6){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                      //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(7));                     //next shape prints magenta.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }else if(shapeID == 7){
                 if(shape[i][j] == 0)
                {
                    wattron(nextShapes, COLOR_PAIR(6));                         //prints 0's black so they don't show.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
                else
                {
                    wattron(nextShapes, COLOR_PAIR(8));                     //next shape prints blue.
                    mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
                }
             }

            x++;
        }
        x -= 4;
        y++;

        //mvwprintw(nextShapes, y, x, "\n");
      //  std::cout << "\n";
    }
    //mvwprintw(nextShapes, y, x, "\n\n");
}
