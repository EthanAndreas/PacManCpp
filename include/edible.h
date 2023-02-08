#pragma once

enum edible_type { FRUIT, SUPERFRUIT, DOT };

/**
 * @brief Correspond to the edible
 *
 */
class edible {
  public:
    edible();
    ~edible();
    void setType(edible_type type);

  private:
    int _x;
    int _y;
    edible_type _type;
};