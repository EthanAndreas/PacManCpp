#include "fruit.h"

std::vector<int> vecFruitScore = {
    0,    // NONE
    100,  // CHERRY_SCORE
    300,  // STRAWBERRY_SCORE
    500,  // ORANGE_SCORE
    700,  // APPLE_SCORE
    1000, // MELON_SCORE
    2000, // GALAXIAN_SCORE
    3000, // BELL_SCORE
    5000  // KEY_SCORE
};

fruit::fruit() {
    _fruit = _NONE;
    _lastFruit = _NONE;
}

fruit::~fruit() {}

typeFruit fruit::getFruit() { return _fruit; }

int fruit::updateFruit(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
    int dotCounter) {
    if (dotCounter >= MIN_DOT_FRUIT) {
        if (dotCounter == MIN_DOT_FRUIT && _fruit == _NONE) {
            _lastFruit = (_lastFruit + 1) % 8;
            _fruit = typeFruit(_lastFruit);
            timeFruit1 = std::chrono::steady_clock::now();
            vecBoard[FRUIT_X][FRUIT_Y]->setItem(_FRUIT);
            vecBoard[FRUIT_X][FRUIT_Y]->setScore(vecFruitScore[_fruit]);
            return SET;
        }

        time_t timeFruit2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTimeFruit =
            timeFruit2 - timeFruit1;

        if (_fruit != _NONE &&
            (elapsedTimeFruit.count() >= TIME_TO_SPAWN_FRUIT)) {
            _fruit = _NONE;
            vecBoard[FRUIT_X][FRUIT_Y]->setItem(_EMPTY);
            vecBoard[FRUIT_X][FRUIT_Y]->setScore(0);
            return EXCEED;
        }
    }
    return NO_UPDATE;
}

void fruit::eatFruit(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard) {
    _fruit = _NONE;
    vecBoard[FRUIT_X][FRUIT_Y]->setItem(_EMPTY);
    vecBoard[FRUIT_X][FRUIT_Y]->setScore(0);
}