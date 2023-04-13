#include "board.h"

square::square() {
    _state = 0;
    _item = nullptr;
}
square::~square() {}

void square::setState(short state) { _state = state; }
short square::getState() { return _state; }

void square::setItem(item *item) { _item = item; }
item *square::getItem() { return _item; }

board::board() { _board = std::vector<std::vector<square>>(); }
board::~board() {}

/**
 * @brief Set the state of each square with the map defined
 * in "assets/pacman_board.txt".
 */
void board::load() {

    std::ifstream inputFile("assets/pacman_board.txt");

    char c;
    square Square;
    _board.push_back(std::vector<square>());
    while (inputFile.get(c)) {

        if (c == '\n')
            _board.push_back(std::vector<square>());
        else {
            Square.setState(c - '0');
            _board.back().push_back(Square);
        }
    }

    inputFile.close();
}

void board::display() {

    for (auto &line : _board) {
        for (auto &square : line) {
            std::cout << square.getState() << " ";
        }
        std::cout << std::endl;
    }
}