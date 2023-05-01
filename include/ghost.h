#ifndef GHOST_H
#define GHOST_H

#include "shortestpath.h"
#include <random>

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

#define updateWithShortestPath(vecBoard, xPac, yPac) \
    updateDirRed(vecBoard, xPac, yPac)
#define updateDirRandom(vecBoard) updateDirOrange(vecBoard)

class ghost {
  public:
    ghost();
    ~ghost();
    /**
     * @brief Set the timer object.
     *
     */
    void setTimer();
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
    bool isReturnHouse();
    /**
     * @brief Set the ghost in the ghost house
     */
    void leaveGhostHouse();
    /**
     * @brief Ghost go back to the house.
     *
     */
    void houseReturn();
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
    void updateDir(std::vector<std::vector<square *>> vecBoard,
                   std::pair<int, int> pacPos, dir dirPac);
    /**
     * @brief Update direction of red ghost. Red ghost is following the pacman.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     */
    void updateDirRed(std::vector<std::vector<square *>> vecBoard, int xPac,
                      int yPac);
    /**
     * @brief Update direction of pink ghost. Pink ghost is anticipating the
     * pacman, it is going to the position of the pacman + 4.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void updateDirPink(std::vector<std::vector<square *>> vecBoard, int xPac,
                       int yPac, dir dirPac);
    void updateDirBlue(std::vector<std::vector<square *>> vecBoard, int xPac,
                       int yPac, dir dirPac);
    /**
     * @brief Update of the orange ghost. Orange ghost takes a random direction.
     *
     * @param vecBoard
     */
    void updateDirOrange(std::vector<std::vector<square *>> vecBoard);

  private:
    color _color;
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    bool _isInHouse;
    bool _isReturnHouse;
    time_t timePoint1;
    std::mt19937 _rng;
};

#endif