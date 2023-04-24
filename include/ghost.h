#ifndef GHOST_H
#define GHOST_H

#include "lib.h"
#include "square.h"

#define GHOST_INIT_X 10
#define GHOST_INIT_Y 12
#define GHOST_CENTER_X 0
#define GHOST_CENTER_Y 4

enum color { RED, PINK, BLUE, ORANGE };

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
    color getColor();
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
};

#endif