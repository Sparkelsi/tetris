#include "Cube.hpp"

Cube::Cube()
    //:shapeID(1)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(j == 1 || j == 2){
                if(i == 1 || i == 2){
                    shape[i][j] = 1;
                }
            }
            shape[i][j] = 0;
        }
    }


}
