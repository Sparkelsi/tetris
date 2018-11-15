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
            break;
        default:
            break;
    }
}


void Shapes::printShape(WINDOW* nextShapes, int y, int x) {
    for(int i = 0; i < SHAPEI; i++) {
        for(int j = 0; j < SHAPEJ; j++) {
            mvwprintw(nextShapes, y, x, "%d", shape[i][j]);
            //wrefresh(nextShapes);
            x++;
        }
        x -= 4;
        y++;
        //mvwprintw(nextShapes, y, x, "\n");
      //  std::cout << "\n";
    }
    //mvwprintw(nextShapes, y, x, "\n\n");
}
