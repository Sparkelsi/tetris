#CMAKE TEXT FILE FOR TETRIS INSPIRED GAME
#KELSI ANDREWS
#KAREN NASON
#DATA STRUCTURES PROJECT


CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2) 

project(tetris)

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD "11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -lncurses")

add_executable(
    tet
    src/Grid.cpp
    src/Shapes.cpp
    src/main.cpp
)