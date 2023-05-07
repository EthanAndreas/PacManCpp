#ifndef GHOST_H
#define GHOST_H

#include "shortestpath.h"
#include <random>

enum color { RED, PINK, BLUE, ORANGE };

#define GHOST_INIT_X 10
#define GHOST_INIT_Y 10
#define GHOST_CENTER_X 0
#define GHOST_CENTER_Y 4

#define RED_GHOST_INIT_X 10
#define RED_GHOST_INIT_Y 13
#define PINK_GHOST_INIT_X 10
#define PINK_GHOST_INIT_Y 13
#define BLUE_GHOST_INIT_X 9
#define BLUE_GHOST_INIT_Y 12
#define ORANGE_GHOST_INIT_X 11
#define ORANGE_GHOST_INIT_Y 12

#define GHOST_HOUSE_SPEED 1
#define GHOST_HOUSE_RANGE_CENTER GHOST_HOUSE_SPEED - 1
#define GHOST_FEAR_SPEED 1
#define GHOST_FEAR_RANGE_CENTER GHOST_FEAR_SPEED - 1
#define GHOST_SPEED 2
#define GHOST_RANGE_CENTER GHOST_SPEED - 1
#define GHOST_RETURN_SPEED 3
#define GHOST_RETURN_RANGE_CENTER GHOST_RETURN_SPEED - 1

// macro for wait time in function of difficulty
#define RED_GHOST_WAIT_DOT 0
#define PINK_GHOST_WAIT_DOT 0
#define BLUE_GHOST_WAIT_DOT_LVL1 30
#define BLUE_GHOST_WAIT_DOT_LVL2 0
#define ORANGE_GHOST_WAIT_DOT_LVL1 90
#define ORANGE_GHOST_WAIT_DOT_LVL2 50
#define ORANGE_GHOST_WAIT_DOT_LVL3 0

#define RED_GHOST_WAIT_DOT_LESS_LIFE 0
#define PINK_GHOST_WAIT_DOT_LESS_LIFE 7
#define BLUE_GHOST_WAIT_DOT_LESS_LIFE 17
#define ORANGE_GHOST_WAIT_DOT_LESS_LIFE 32

// swap for the blue ghost between chase mode of red and pink ghost
#define BLUE_GHOST_RED_TIME 20  // 20s
#define BLUE_GHOST_PINK_TIME 12 // 12s

#define CHASE_MODE 20    // 20s
#define SCATTER_MODE_1 7 // 7s
#define SCATTER_MODE_2 5 // 5s

#define NO_EATEN_DOT_TIME 7 // 7s

#define DEFAULT_LIVES 1

#define updateDirWithShortestPath(vecBoard, xPac, yPac) \
    updateDirRed(vecBoard, xPac, yPac)

enum mode { ANY, CHASE, SCATTER, FRIGHTENED };

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
    bool isInHouse();
    /**
     * @brief Update the position of the ghost in the ghost house.
     *
     * @param vecBoard
     * @param level
     * @param dotCounter
     * @param life
     */
    void
    updateInHouse(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                  int level, int dotCounter, int life, time_t noEatenDotTimer1);
    /**
     * @brief Ghost go back to the house.
     *
     */
    void setReturnHouse();
    /**
     * @brief Check if the ghost is returning in the ghost house.
     *
     * @return true
     * @return false
     */
    bool isReturnHouse();
    /**
     * @brief Make the ghost go to the ghost house.
     *
     * @param vecBoard
     */
    void
    returnHouse(std::vector<std::vector<std::shared_ptr<square>>> vecBoard);
    /**
     * @brief Set the frightened object.
     *
     * @param isFear
     */
    void setFrightened(bool isFear);
    /**
     * @brief Check if the ghost is frightened.
     *
     * @return true
     * @return false
     */
    bool isFrightened();
    /**
     * @brief Get the sprite position of the ghost.
     *
     * @return std::pair<size_t, size_t>
     */
    std::pair<size_t, size_t> getPos();
    /**
     * @brief Get the last eaten position of the ghost.
     *
     * @return std::pair<size_t, size_t>
     */
    std::pair<size_t, size_t> getEatenPosition();
    /**
     * @brief Update the sprite position of the ghost.
     *
     * @param count - frame number
     * @note The sprite position represents the pixel position of the ghost.
     */
    void updatePos();
    /**
     * @brief Update the board position of the ghost.
     *
     */
    void updateCoord();
    /**
     * @brief Wait the ghost to be in the center of a square in function of
     * the ghost speed, of the direction and of the sprite position.
     *
     * @return true
     * @return false
     */
    bool waitSquareCenter();
    /**
     * @brief Get the last direction of the ghost.
     *
     * @return dir*
     */
    dir getLastDir();
    /**
     * @brief Update the direction of the ghost with a  valid random
     * direction and update the board position of the ghost.
     *
     * @param vecBoard
     */
    void updateDir(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                   size_t xPac, size_t yPac, dir dirPac, int level,
                   int dotCounter, int life, time_t noEatenDotTimer1);
    /**
     * @brief Update direction of red ghost. Red ghost is following the pacman.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     * @param level
     * @param dotCounter
     * @param life
     */
    void
    updateDirRed(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                 size_t xPac, size_t yPac);
    /**
     * @brief Update direction of pink ghost. Pink ghost is anticipating the
     * pacman, it is going to the position of the pacman + 4.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirPink(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                  size_t xPac, size_t yPac, dir dirPac);
    /**
     * @brief Update direction of blue ghost. Swap between the chase mode of red
     * and pink ghost.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirBlue(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                  size_t xPac, size_t yPac, dir dirPac);
    /**
     * @brief Update direction of orange ghost. Orange ghost is following the
     * pacman if the distance between the pacman and the ghost is greater than
     * 8, else it is going to the ghost house.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirOrange(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                    size_t xPac, size_t yPac);
    /**
     * @brief Update the direction of the ghost in scatter mode.
     *
     * @param vecBoard
     * @param x
     * @param y
     */
    void updateDirScatterMode(
        std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t x,
        size_t y);
    /**
     * @brief Update the direction in run away mode. Ghost is going to the
     * opposite direction of the pacman.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void updateDirRunAwayMode(
        std::vector<std::vector<std::shared_ptr<square>>> vecBoard);
    /**
     * @brief Swap between chase and scatter mode.
     *
     */
    void swapMode(int level);

  private:
    color _color;
    // board coordinates corresponding to coordinates of the board vector
    // pixel coordinates corresponding to the sprite position
    size_t _xBoard, _yBoard, _xPixel, _yPixel, _xPixelEaten, _yPixelEaten;
    dir _lastDir;
    mode _mode;
    int _swapMode;
    bool _scatterHouse;
    dir _scatterDir;
    // mode of the ghost
    bool _chaseMode, _scatterMode, _frightenedMode;
    // state of the ghost
    bool _isTime, _isInHouse, _isReturnHouse, _isFear, _isInTunnel;
    // blue ghost is following the red ghost during 20s and the pink ghost
    // during 12s
    bool _blueRed, _bluePink;
    // timer for switching mode
    time_t modeTimer1;
    // timer orange ghost
    time_t blueTimer1;
    // random number generator
    std::mt19937 _rng;
};

#endif