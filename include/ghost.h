#ifndef GHOST_H
#define GHOST_H

#include "lib.h"
#include "square.h"

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

// macro for wait time in function of difficulty
#define RED_GHOST_WAIT_TIME (6 / DIFFICULTY)     // 6s for easy
#define PINK_GHOST_WAIT_TIME (12 / DIFFICULTY)   // 12s for easy
#define BLUE_GHOST_WAIT_TIME (18 / DIFFICULTY)   // 18s for easy
#define ORANGE_GHOST_WAIT_TIME (24 / DIFFICULTY) // 24s for easy

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
    void updateDir(std::vector<std::vector<square *>> vecBoard);
    /**
     * @brief Get the last direction of the ghost.
     *
     * @return dir
     */
    dir getDir();
    /**
     * @brief Ghost go back to the house.
     *
     */
    void houseReturn();

  private:
    color _color;
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    bool _isInHouse;
    time_t timePoint1;
};

#endif