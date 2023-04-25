#include "square.h"

square::square() {
    _item = _EMPTY;
    _score = 0;
}

square::~square() {}

void square::setState(short state) { _state = state; }

void square::setScore(int score) { _score = score; }

short square::getState() { return _state; }

int square::getScore() { return _score; }

void square::setItem(typeItem item) { _item = item; }

typeItem square::getItem() { return _item; }