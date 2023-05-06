#ifndef FRUIT_H
#define FRUIT_H

#include "lib.h"
#include "square.h"

enum typeFruit {
    _NONE,
    _CHERRY,
    _STRAWBERRY,
    _ORANGE,
    _APPLE,
    _MELON,
    _GALAXIAN,
    _BELL,
    _KEY
};

#define FRUIT_X 10
#define FRUIT_Y 15

#define MIN_DOT_FRUIT 170

#define CHERRY_SCORE 100
#define STRAWBERRY_SCORE 300
#define ORANGE_SCORE 500
#define APPLE_SCORE 700
#define MELON_SCORE 1000
#define GALAXIAN_SCORE 2000
#define BELL_SCORE 3000
#define KEY_SCORE 5000

#define TIME_TO_SPAWN_FRUIT 10 // 10s

#define NO_UPDATE 0
#define SET 1
#define EXCEED 2

class fruit {
  public:
    fruit();
    ~fruit();
    /**
     * @brief Get the item of the fruit.
     *
     * @return typeFruit
     */
    typeFruit getFruit();
    /**
     * @brief Update the fruit.
     *
     * @param vecBoard
     * @param _dotCounter
     */
    int updateFruit(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                    int dotCounter);
    /**
     * @brief Eat the fruit.
     *
     * @param vecBoard
     */
    void eatFruit(std::vector<std::vector<std::shared_ptr<square>>> vecBoard);

  private:
    typeFruit _fruit;
    int _lastFruit;
    std::chrono::time_point<std::chrono::steady_clock> timeFruit1;
};

#endif