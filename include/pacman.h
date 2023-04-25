#ifndef PACMAN_H
#define PACMAN_H

#include "ghost.h"
#include "lib.h"
#include "square.h"

#define PACMAN_INIT_X 10
#define PACMAN_INIT_Y 15
#define PACMAN_CENTER_X 0
#define PACMAN_CENTER_Y 4

#define DOT_PACMAN_CONTACT 20
#define POWERUP_PACMAN_CONTACT 10
#define GHOST_PACMAN_CONTACT 5

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
    void updateDir(std::vector<std::vector<square *>> vecBoard, dir currentDir);
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
    void updateSquare(std::vector<std::vector<square *>> vecBoard);
    /**
     * @brief Get the score of pacman.
     *
     * @return int
     */
    int getScore() const;

    bool ghostCollision(std::vector<ghost *> vecGhost);

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    int _score;
    bool _powerup;
    time_t timePoint1;
};

#endif