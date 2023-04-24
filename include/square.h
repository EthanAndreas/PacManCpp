#ifndef SQUARE_H
#define SQUARE_H

#include "item.h"

/**
 * @brief This class contains the square's state (wall or hall)
 * and the item on this square (pacman, ghost, dot...).
 */
class square {
  public:
    square();
    ~square();
    /**
     * @brief Set the state of the square.
     *
     * @param state short
     *
     * @note Short value defines the state : 0 for hall, 1 for wall, 2 for
     * teleportation and 3 for cage's door.
     */
    void setState(short state);
    /**
     * @brief Get the state of the square.
     *
     * @return short
     */
    short getState();
    /**
     * @brief Set the item on the square.
     *
     * @param item*
     */
    void setItem(item *item);
    /**
     * @brief Get the item on the square.
     *
     * @return item*
     */
    item *getItem();

  private:
    short _state;
    item *_item;
};

#endif