#ifndef LIB_H
#define LIB_H

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#define HALL 0
#define WALL 1
#define DOOR 2

#define SCALE_PIXEL 32 // each square is 32x32 pixels

#define DIFFICULTY 1

enum dir { LEFT, RIGHT, UP, DOWN, NONE };

struct Coordinate {
    int x;
    int y;
};

#endif