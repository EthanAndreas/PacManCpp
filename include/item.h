#ifndef ITEM_H
#define ITEM_H

enum typeCaracter { _NONE, _PACMAN, _GHOST };
enum typeEdible { _EMPTY, _FRUIT, _POWERUP, _DOT };

/**
 * @brief Correspond to the item.
 * It can be a caracter (pacman or ghost) or an edible (fruit,
 * superfruit or dot)
 */
class item {
  public:
    item();
    ~item();
    /**
     * @brief Set the Carater object (pacman or ghost).
     *
     * @param Caracter
     */
    void setCarater(typeCaracter Caracter);
    /**
     * @brief Set the Edible object (dot, powerup or fruit).
     *
     * @param Edible
     */
    void setEdible(typeEdible Edible);
    /**
     * @brief Get the Carater.
     *
     * @return typeCaracter
     */
    typeCaracter getCaracter();
    /**
     * @brief Get the Edible.
     *
     * @return typeEdible
     */
    typeEdible getEdible();

  private:
    typeCaracter _Caracter;
    typeEdible _Edible;
};

#endif