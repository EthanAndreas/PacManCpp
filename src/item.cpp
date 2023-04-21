#include "item.h"

#include <iostream>

item::item() {
    _typeCaracter = _NONE;
    _typeEdible = _NONE;
}

item::~item() {}

void item::setCarater(type typeCaracter) { _typeCaracter = typeCaracter; }

void item::setEdible(type typeEdible) { _typeEdible = typeEdible; }

type item::getCaracter() { return _typeCaracter; }

type item::getEdible() { return _typeEdible; }
