#ifndef LIB_H
#define LIB_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#define HALL 0
#define WALL 1
#define DOOR 2

#define SCALE_PIXEL 32 // each square is 32x32 pixels

#define DIFFICULTY 1

enum dir { LEFT, RIGHT, UP, DOWN, NONE };

#define time_t                          \
    std::chrono::time_point<            \
        std::chrono::_V2::steady_clock, \
        std::chrono::duration<long int, std::ratio<1, 1000000000>>>

struct Coordinate {
    int x;
    int y;
};

#endif