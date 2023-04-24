#pragma once

#include "graphic.h"

class ghost {
  public:
    ghost();
    ~ghost();
    /**
     * @brief Get the last direction of the ghost.
     *
     * @return dir*
     */
    dir getLastDir();
    /**
     * @brief Update the sprite position of the ghost.
     *
     * @note The sprite position represents the pixel position of the ghost.
     */
    void updatePos();
    /**
     * @brief Get the sprite position of the ghost.
     *
     * @return std::pair<int, int>
     */
    std::pair<int, int> getPos();
    /**
     * @brief Update the direction of the ghost with a  valid random direction
     * and update the board position of the ghost.
     *
     * @param vecBoard
     */
    void updateDir(std::vector<std::vector<square>> vecBoard);
    /**
     * @brief Get the last direction of the ghost.
     *
     * @return dir
     */
    dir getDir();
    /**
     * @brief Fill the new square with the ghost and empty the previous square.
     *
     * @param vecBoard
     */
    void updateSquare(std::vector<std::vector<square>> vecBoard);

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
};