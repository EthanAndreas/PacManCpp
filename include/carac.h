#pragma once

enum carac_type { PACMAN, GHOST };

/**
 * @brief Correspond to the caracters
 *
 */
class carac {
  public:
    carac();
    ~carac();
    void setType(carac_type type);

  private:
    int _x;
    int _y;
    carac_type _type;
};