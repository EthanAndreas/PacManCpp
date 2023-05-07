#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "board.h"
#include "fruit.h"
#include <SDL2/SDL.h>
#include <map>

#define SCORE_HEADER 50

#define GHOST_BLINK 3 // 3s

#define FRUIT_SCORE_DISPLAY_TIME 2

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
 * @param windowSurf
 * @param spriteBoard
 * @param count the number of frame
 * @param Pacman the pacman
 * @param vecGhost the vector of ghost
 * @param vecDot the vector of dot
 * @param vecPowerup the vector of powerup
 * @param fruit the fruit to display
 * @param curScore the current score
 * @param highScore the high score
 * @param death variable to know if pacman is dead and display the animation
 * @param start variable to know if the game is started
 * @param curLevel the current level
 * @return the number of frame
 */
int draw(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int count,
         pacman Pacman, std::vector<std::shared_ptr<ghost>> vecGhost,
         std::vector<Coordinate> vecDot, std::vector<Coordinate> vecPowerup,
         typeFruit fruit, int curScore, int highScore, short death, bool start,
         int curLevel);
/**
 * @brief Draw strings on the window
 * @param windowSurf
 * @param spriteBoard
 * @param x the x position to display the string
 * @param y the y position to display the string
 * @param str the string to display

*/
void drawString(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int x,
                int y, std::string str);
/**
 * @brief Draw the menu before the game
 * @param windowSurf
 * @param spriteBoard
 * @param highScore the high score
 */
void intro(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int highScore);
/**
 * @brief Draw the game over screen
 * @param windowSurf
 * @param spriteBoard
 * @param curScore the current score
 * @param highScore the high score
 */
void gameOver(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int curScore,
              int highScore);

#endif