#pragma once

#include "debug.h"
#include "item.h"
#include <fstream>
#include <iostream>
#include <vector>

#define PACMAN_INIT_X 10
#define PACMAN_INIT_Y 15
#define PACMAN_CENTER_X 0
#define PACMAN_CENTER_Y 4

#define GHOST_INIT_X 10
#define GHOST_INIT_Y 12
#define GHOST_CENTER_X 0
#define GHOST_CENTER_Y 4

struct Coordinate {
    int x;
    int y;
};

/*----------------------------------Square-----------------------------------*/

/**
 * @brief This class contains the square's state (wall or hall)
 * and the item on this square (pacman, ghost, dot...).
 */
class square {
  public:
    square();
    ~square();
    /**
     * @brief Set the state of the square.
     *
     * @param state short
     *
     * @note Short value defines the state : 0 for hall, 1 for wall, 2 for
     * teleportation and 3 for cage's door.
     */
    void setState(short state);
    /**
     * @brief Get the state of the square.
     *
     * @return short
     */
    short getState();
    /**
     * @brief Set the item on the square.
     *
     * @param item*
     */
    void setItem(item *item);
    /**
     * @brief Get the item on the square.
     *
     * @return item*
     */
    item *getItem();

  private:
    short _state;
    item *_item;
};

/*-----------------------------------Board------------------------------------*/

/**
 * @brief The board is formed by vector of square's vector.
 * It defines each square of the map.
 */
class board {
  public:
    board();
    ~board();
    /**
     * @brief Get the Board object
     *
     * @return std::vector<std::vector<square>>
     */
    std::vector<std::vector<square>> getBoard();
    /**
     * @brief Set the state of each square with the map defined
     * in "assets/pacman_board.txt".
     */
    void load();
    /**
     * @brief Change the element access of the board from [i][j] to [j][i].
     *
     * @note The sprite returns "x" as the column and "y" as the line. The
     * board is defined with "x" as the line and "y" as the column. So, we need
     * to transpose the board to have the same access.
     */
    void transpose();
    /**
     * @brief Set the item on the square.
     *
     * @note Initialise the position items (pacman, ghost, dot, powerup).
     */
    void setItem();
    /**
     * @brief Get the list of the dot's position.
     *
     * @return std::vector<Coordinate>
     */
    std::vector<Coordinate> getDotList();
    /**
     * @brief Get the list of the powerup's position.
     *
     * @return std::vector<Coordinate>
     */
    std::vector<Coordinate> getPowerupList();

  private:
    std::vector<std::vector<square>> _board;
};
