#pragma once

#include "graphic.h"

#define DOT_PACMAN_CONTACT 20
#define POWERUP_PACMAN_CONTACT 10

class pacman {
  public:
    pacman();
    ~pacman();
    /**
     * @brief Get the last direction of pacman.
     *
     * @return dir
     */
    dir getLastDir();
    /**
     * @brief Update the sprite position of pacman.
     *
     * @note The sprite position represents the pixel position of pacman.
     */
    void updatePos();
    /**
     * @brief Get the sprite position of pacman.
     *
     * @return std::pair<int, int>
     */
    std::pair<int, int> getPos();
    /**
     * @brief Update the direction of pacman with the direction pressed by the
     * user if the direction is valid and update the board position of pacman.
     *
     * @param vecBoard
     * @param currentDir
     */
    void updateDir(std::vector<std::vector<square>> vecBoard, dir currentDir);
    /**
     * @brief Get the last direction of pacman.
     *
     * @return dir
     */
    dir getDir();
    /**
     * @brief Fill the new square with pacman and empty the previous square.
     * Update the square and the score if pacman eats a dot or a powerup.
     *
     * @param vecBoard
     */
    void updateSquare(std::vector<std::vector<square>> vecBoard);
    /**
     * @brief Get the score of pacman.
     *
     * @return int
     */
    int getScore() const;

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    int _score;
};