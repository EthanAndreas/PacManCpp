#pragma once

#include "board.h"
#include <SDL2/SDL.h>
#include <utility>

#define SCALE_PIXEL 32

enum dir { LEFT, RIGHT, UP, DOWN, NONE };

/**
 * @brief Initialize SDL and create the window
 * and the surface to draw on
 * @param Window
 * @param windowSurf
 * @param spriteBoard
 */
void init(SDL_Window **Window, SDL_Surface **windowSurf,
          SDL_Surface **spriteBoard);
/**
 * @brief Draw the game on the window
 * and update the window.
 * Make movement of the ghost and pacman
 * @param last_dir
 * @param windowSurf
 * @param spriteBoard
 */
void draw(dir pacmanLastDir, dir ghostLastDir, SDL_Surface **windowSurf,
          SDL_Surface **spriteBoard, std::pair<int, int> pacPos,
          std::pair<int, int> ghostPos, std::vector<Coordinate> vecDot,
          std::vector<Coordinate> vecPowerup, int const cur_score);