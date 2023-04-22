#include "item.h"

#include <iostream>

item::item() {
    _Caracter = _NONE;
    _Edible = _EMPTY;
}

item::~item() {}

void item::setCarater(typeCaracter Caracter) { _Caracter = Caracter; }

void item::setEdible(typeEdible Edible) { _Edible = Edible; }

typeCaracter item::getCaracter() { return _Caracter; }

typeEdible item::getEdible() { return _Edible; }
