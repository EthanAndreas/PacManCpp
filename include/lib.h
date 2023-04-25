#ifndef LIB_H
#define LIB_H

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#define SCALE_PIXEL 32

#define DIFFICULTY 4

enum dir { LEFT, RIGHT, UP, DOWN, NONE };

struct Coordinate {
    int x;
    int y;
};

#endif