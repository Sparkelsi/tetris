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
    }

int Shapes::getShapeID() {
    return shapeID;
}

int Shapes::getShape(int x, int y) { //this needs to change with size of grid
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == x) {
                if(j == y) {
                    return shape[x][y];
                }
            }
        }
    }
    //std::cout << "you did something wrong\n";
    return 0;
}

// int Shapes::getShapej(int x, int y) {
//     for(int i = 0; i < 4; i++) {
//         for(int j = 0; j < 4; j++) {
//             if(i == x) {
//                 if(j == y) {
//                     return y;
//                 }
//             }
//         }
//     }
//     std::cout << "you did something wrong\n";
//     return 0;
// }



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
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 0 || i == 1){
                        if(j == 0 || j == 1){
                            shape[i][j] = 1;
                        } else {
                            shape[i][j] = 0;
                        }
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            break;
        case 2:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 1){
                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            break;
        case 3:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 0 && j == 1){
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
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 0 && (j == 1 || j == 2)){
                        shape[i][j] = 1;
                    } else if(i == 1 && (j == 0 || j == 1)){
                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            break;
        case 5:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 0 && (j == 0 || j == 1)){
                        shape[i][j] = 1;
                    } else if(i == 1 && (j == 1 || j == 2)){
                        shape[i][j] = 1;
                    } else {
                        shape[i][j] = 0;
                    }
                }
            }
            break;
        case 6:
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
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
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 4; j++) {
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


void Shapes::printShape() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << shape[i][j];
        }
        std::cout << "\n";
    }
}

// int getShapeID()
// {
//     return shapeID;
// }
