#include "square.h"

square::square() { _item = _EMPTY; }

square::~square() {}

void square::setState(short state) { _state = state; }

short square::getState() { return _state; }

void square::setItem(typeItem item) { _item = item; }

typeItem square::getItem() { return _item; }