#ifndef GHOST_H
#define GHOST_H

#include "lib.h"
#include "square.h"
#include <chrono>

#define GHOST_INIT_X 10
#define GHOST_INIT_Y 10

#define RED_GHOST_INIT_X 10
#define RED_GHOST_INIT_Y 10

#define PINK_GHOST_INIT_X 9
#define PINK_GHOST_INIT_Y 12

#define BLUE_GHOST_INIT_X 10
#define BLUE_GHOST_INIT_Y 13

#define ORANGE_GHOST_INIT_X 11
#define ORANGE_GHOST_INIT_Y 12

#define GHOST_CENTER_X 0
#define GHOST_CENTER_Y 4

enum color { RED, PINK, BLUE, ORANGE };

#define time_t                          \
    std::chrono::time_point<            \
        std::chrono::_V2::steady_clock, \
        std::chrono::duration<long int, std::ratio<1, 1000000000>>>

// macro for wait time in function of difficulty
#define RED_GHOST_WAIT_TIME (8 / DIFFICULTY)
#define PINK_GHOST_WAIT_TIME (14 / DIFFICULTY)
#define BLUE_GHOST_WAIT_TIME (20 / DIFFICULTY)
#define ORANGE_GHOST_WAIT_TIME (26 / DIFFICULTY)

class ghost {
  public:
    ghost();
    ~ghost();
    /**
     * @brief Set the color of the ghost.
     *
     * @param c
     */
    void setGhost(color c);
    /**
     * @brief Get the color of the ghost.
     *
     * @return color
     */
    color getGhost();
    /**
     * @brief Check if the ghost is in the ghost house.
     *
     * @return true
     * @return false
     */
    bool isGhostInHouse();
    /**
     * @brief Update the direction of the ghost in the ghost house.
     */
    void updateDirInHouse();
    /**
     * @brief Set the ghost in the ghost house
     */
    void leaveGhostHouse();
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
    color _color;
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    bool _isInHouse;
    time_t _timePoint1;
};

#endif