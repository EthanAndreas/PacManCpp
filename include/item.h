#pragma once

enum type { _NONE, _PACMAN, _GHOST, _FRUIT, _POWERUP, _DOT };

/**
 * @brief Correspond to the item.
 * It can be a caracter (pacman or ghost) or an edible (fruit,
 * superfruit or dot)
 */
class item {
  public:
    item();
    ~item();
    void setCarater(type typeCaracter);
    void setEdible(type typeEdible);
    type getCaracter();
    type getEdible();

  private:
    type _typeCaracter;
    type _typeEdible;
};