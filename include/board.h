#ifndef BOARD_H
#define BOARD_H

#include "debug.h"
#include "ghost.h"
#include "pacman.h"
#include "square.h"

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

#endif