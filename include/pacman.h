#ifndef PACMAN_H
#define PACMAN_H

#include "fruit.h"
#include "ghost.h"
#include "lib.h"
#include "square.h"

#define PACMAN_INIT_X 10
#define PACMAN_INIT_Y 20
#define PACMAN_CENTER_X 0
#define PACMAN_CENTER_Y 4

#define PACMAN_SPEED 2
#define PACMAN_RANGE_CENTER PACMAN_SPEED - 1

#define DOT_PACMAN_CONTACT 20
#define POWERUP_PACMAN_CONTACT 10
#define GHOST_PACMAN_CONTACT 15
#define FRUIT_PACMAN_CONTACT 10

#define DOT_SCORE 10
#define POWERUP_SCORE 50
#define GHOST_SCORE 200
#define FRUIT_SCORE 1000

#define DEFAULT_LIVES 3

#define POWERUP_MODE 10 // 10s

class pacman {
  public:
    pacman();
    ~pacman();
    /**
     * @brief Get the sprite position of pacman.
     *
     * @return std::pair<size_t, size_t>
     */
    std::pair<size_t, size_t> getPos();
    /**
     * @brief Update the sprite position of pacman.
     *
     * @note The sprite position represents the pixel position of pacman.
     */
    void updatePos();
    /**
     * @brief Wait for pacman to be in the center of a square in function of
     * his direction and his sprite position.
     *
     * @return true
     * @return false
     */
    bool waitSquareCenter();
    /**
     * @brief Update the direction of pacman with the direction pressed by
     * the user if the direction is valid and update the board position of
     * pacman.
     *
     * @param vecBoard
     * @param currentDir
     */
    void updateDir(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                   dir currentDir);
    /**
     * @brief Get the last direction of pacman.
     *
     * @return dir
     */
    dir getLastDir();
    /**
     * @brief Fill the new square with pacman and empty the previous square.
     * Update the square and the score if pacman eats a dot or a powerup.
     *
     * @param vecBoard
     */
    void
    updateSquare(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                 std::vector<std::shared_ptr<ghost>> vecGhost, fruit *Fruit);
    /**
     * @brief Set the powerup of pacman.
     *
     * @param powerup
     */
    time_t getTimePoint1();
    /**
     * @brief Set the powerup of pacman.
     *
     * @return true
     * @return false
     */
    bool isPowerup();
    /**
     * @brief Get the score of pacman.
     *
     * @return size_t
     */
    size_t getScore();
    /**
     * @brief Reset the score of pacman.
     *
     */
    void resetScore();
    /**
     * @brief Check if pacman is in collision with a ghost.
     * If pacman is in collision with a ghost, the ghost is eaten if
     * pacman is in powerup mode, else pacman is eaten.
     *
     * @param vecGhost
     * @return true
     * @return false
     */
    bool ghostCollision(std::vector<std::shared_ptr<ghost>> vecGhost);
    /**
     * @brief Get the number of dots eaten by pacman.
     *
     * @return size_t
     */
    size_t getDotCounter();
    /**
     * @brief Reset the dot counter.
     *
     */
    void resetDotCounter();
    /**
     * @brief Get the remaining life of pacman.
     *
     * @return short
     */
    short getRemainingLife();
    /**
     * @brief Decrement the remaining life of pacman.
     *
     */
    void looseLife();
    /**
     * @brief Reset the position of pacman.
     *
     */
    void resetPos();
    /**
     * @brief Get previous direction of pacman.
     *
     */
    dir getOldDir();

  private:
    // board coordinates corresponding to coordinates of the board vector
    // pixel coordinates corresponding to the sprite position
    size_t _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir, _oldDir;
    size_t _score;
    size_t _dotCounter;
    bool _powerup;
    time_t timePoint1;
    short _remainingLife;
};

#endif