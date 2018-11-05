#include "Shapes.hpp"
#include <iostream>

Shapes::Shapes()
    :shapeID(0)
    {
        for(int i = 0; i < 4; i++) {
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
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == x) {
                if(j == y) {
                    return shape[x][y];
                }
            }
        }
    }
    std::cout << "you did something wrong\n";
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

void Shapes::makeShape(int shapeID) {
    switch(shapeID) {
        case 1:
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    if(i == 2 || i == 3){
                        if(j == 0 || j == 1){
                            shape[i][j] = 1;
                        //    std::cout << shape[i][j];// << "both ifs work\n";
                        } else {
                            shape[i][j] = 0;
                        }
                    } else {
                        shape[i][j] = 0;
                        //std::cout << "in else"
                    }
                //    std::cout << shape[i][j];
                }
                //std::cout << "\n";
            }
        //    std::cout << "cube printed successfully \n";
        default:
            break;
    }
}


void Shapes::printShape() {
    for(int i = 0; i < 4; i++) {
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
