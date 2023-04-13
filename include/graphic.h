#pragma once

#include <SDL2/SDL.h>
#include <utility>

enum dir { LEFT, RIGHT, UP, DOWN, NONE };

// SDL_Rect letter[256];
// SDL_Rect letter['a'] = letter_a;
// SDL_Rect letter['b'] = letter_b;

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
std::pair<int, int> draw(dir *lastDir, SDL_Surface **windowSurf,
                         SDL_Surface **spriteBoard);