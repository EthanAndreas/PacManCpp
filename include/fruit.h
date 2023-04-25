#ifndef FRUIT_H
#define FRUIT_H

#include "lib.h"
#include <chrono>

enum typeFruit {
    _CHERRY,
    _STRAWBERRY,
    _ORANGE,
    _APPLE,
    _MELON,
    _GALAXIAN,
    _BELL,
    _KEY
};

#define FRUIT_X 10
#define FRUIT_Y 15

#define CHERRY_SCORE 100
#define STRAWBERRY_SCORE 300
#define ORANGE_SCORE 500
#define APPLE_SCORE 700
#define MELON_SCORE 1000
#define GALAXIAN_SCORE 2000
#define BELL_SCORE 3000
#define KEY_SCORE 5000

#define TIME_TO_SPAWN_FRUIT 10 // 10s

#endif