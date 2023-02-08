#pragma once

#include "item.h"

/**
 * @brief Correspond to the board
 *
 */
class board {
  public:
    board();
    ~board();
    void init();
    void display();
    void setItem(item *i);
    item *getItem();
};
