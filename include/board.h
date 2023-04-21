#pragma once

#include "item.h"
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief This class contains the square's state (wall or hall)
 * and the item on this square (ghost, dot, fruit ...).
 *
 */
class square {
  public:
    square();
    ~square();
    void setState(short state);
    short getState();
    void setItem(item *item);
    item *getItem();

  private:
    short _state;
    item *_item;
};

/**
 * @brief The board is formed by vector of square's vector.
 * It defines the wall and the hall of the map.
 */
class board {
  public:
    board();
    ~board();
    std::vector<std::vector<square>> getBoard();
    void load();
    void transpose();
    void display();

  private:
    std::vector<std::vector<square>> _board;
};
