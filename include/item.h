#pragma once

#include "carac.h"
#include "edible.h"

enum type { _PACMAN, _GHOST, _FRUIT, _SUPERFRUIT, _DOT };

/**
 * @brief Correspond to the item.
 * It can be a caracter (pacman or ghost) or an edible (fruit,
 * superfruit or dot)
 */
class item {
  public:
    item();
    ~item();
    void init();
    void display();
    type getType();
    void setCarac(carac *c);
    void setEdible(edible *e);
    carac *getCarac();
    edible *getEdible();

  private:
    union {
        carac *_carac;
        edible *_edible;
    } _item;
    type _type;
};