#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "board.h"
#include "fruit.h"
#include <SDL2/SDL.h>
#include <map>

#define GHOST_BLINK 3 // 3s

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
void draw(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, pacman Pacman,
          std::vector<ghost *> vecGhost, std::vector<Coordinate> vecDot,
          std::vector<Coordinate> vecPowerup, typeFruit fruit, int curScore);

void drawString(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int x,
                int y, std::string str);

#endif