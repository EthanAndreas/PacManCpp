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
#define FRUIT_PACMAN_CONTACT 20

#define DOT_SCORE 10
#define POWERUP_SCORE 50
#define GHOST_SCORE 200
#define FRUIT_SCORE 1000

#define POWERUP_MODE 10 // 10s

class pacman {
  public:
    pacman();
    ~pacman();
    /**
     * @brief Init pacman.
     *
     */
    void init();
    /**
     * @brief Reset pacman.
     *
     */
    void reset();
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
    time_t getPowerupTimer();
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
     * @brief Get the color of the ghost eaten by pacman.
     * @return color
     */
    color getGhostEatenColor();
    /**
     * @brief Get the Ghost Eaten Score object.
     *
     * @return size_t
     */
    size_t getGhostEatenScore();
    /**
     * @brief Get the Fruit Eaten object.
     *
     */
    std::vector<typeFruit> getEatenFruit();
    /**
     * @brief Get the Fruit Eaten object.
     *
     * @return short
     */
    short getFruitEaten();
    /**
     * @brief Get the fruit eaten timer object.
     *
     * @return time_t
     */
    time_t getfruitEatenTimer();
    /**
     * @brief Set the fruit eaten score object.
     *
     * @param score
     */
    void setFruitEatenScore(short score);
    /**
     * @brief Get the score of fruit eaten by pacman.
     *
     * @param fruitEaten
     */
    short getFruitEatenScore();
    /**
     * @brief Get the number of dots eaten by pacman.
     *
     * @return size_t
     */
    size_t getDotCounter();
    /**
     * @brief Get the Dot Counter Level object.
     *
     * @return size_t
     */
    size_t getDotCounterLevel();
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
     * @brief Get previous direction of pacman.
     *
     */
    dir getOldDir();
    /**
     * @brief Get the no eaten dot timer object.
     *
     * @return time_t
     */
    time_t getNoEatenDotTimer();

  private:
    // board coordinates corresponding to coordinates of the board vector
    // pixel coordinates corresponding to the sprite position
    size_t _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir, _oldDir;
    size_t _score;
    size_t _dotCounter;
    size_t _dotCounterLevel;
    bool _powerup;
    time_t powerupTimer1;
    // ghostEaten is the number of ghost eaten in a level
    // ghostEatenScore is the score of the ghost eaten with one powerup
    short _ghostEaten, _ghostEatenScore;
    color _ghostEatenColor;
    // fruitEaten is the number of fruit eaten in a level
    // fruitEatenScore is the score of the fruit eaten
    std::vector<typeFruit> _eatenFruit;
    short _fruitEaten, _fruitEatenScore;
    time_t fruitEatenTimer1;
    short _remainingLife;
    // timer since the last dot eaten by pacman
    time_t noEatenDotTimer1;
};

#endif