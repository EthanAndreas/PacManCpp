#include "square.h"

square::square() {}

square::~square() {}

void square::setState(short state) { _state = state; }

short square::getState() { return _state; }

void square::setItem(item *item) { _item = item; }

item *square::getItem() { return _item; }