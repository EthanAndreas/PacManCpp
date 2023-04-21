#include "board.h"

square::square() {}
square::~square() {}

void square::setState(short state) { _state = state; }
short square::getState() { return _state; }

void square::setItem(item *item) { _item = item; }
item *square::getItem() { return _item; }

board::board() { _board = std::vector<std::vector<square>>(); }
board::~board() {
    for (auto &line : _board) {
        for (auto &square : line) {
            square.~square();
        }
    }
}

/**
 * @brief Set the state of each square with the map defined
 * in "assets/pacman_board.txt".
 */
void board::load() {

    std::ifstream inputFile("assets/pacman_board.txt");

    char c;
    square Square;
    _board.push_back(std::vector<square>()); // first column
    while (inputFile.get(c)) {

        if (c == '\n') {
            _board.push_back(std::vector<square>()); // next column
        } else {
            Square.setState(c - '0');
            Square.setItem(new item());
            _board.back().push_back(Square);
        }
    }
}

std::vector<std::vector<square>> board::getBoard() { return _board; }

void board::transpose() {
    const size_t numRows = _board.size();
    const size_t numCols = _board.empty() ? 0 : _board[0].size();
    std::vector<std::vector<square>> tBoard(numCols,
                                            std::vector<square>(numRows));

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            tBoard[j][i] = _board[i][j];
        }
    }

    _board = tBoard;
}

void board::setItem() {

    size_t i = 0, j = 0;
    for (i = 0; i < _board.size(); i++) {
        for (j = 0; j < _board[i].size(); j++) {
            square &square = _board[i][j];
            if (square.getState() == 0) {
                // teleportation hallway
                if (((i <= 4) || (i >= 16 && i <= 20)) && j == 12)
                    square.getItem()->setEdible(_NONE);
                // middle of the map
                else if (i >= 6 && i <= 14 && j >= 9 && j <= 17)
                    square.getItem()->setEdible(_NONE);
                else
                    square.getItem()->setEdible(_DOT);
            }
        }
    }

    _board[1][3].getItem()->setEdible(_POWERUP);
    _board[19][3].getItem()->setEdible(_POWERUP);
    _board[1][20].getItem()->setEdible(_POWERUP);
    _board[19][20].getItem()->setEdible(_POWERUP);
}

void board::display() {

    // display state
    std::cout << "State:" << std::endl;
    for (auto &line : _board) {
        for (auto &square : line) {
            std::cout << square.getState() << " ";
        }
        std::cout << std::endl;
    }
    // display item edible
    std::cout << "Item edible:" << std::endl;
    for (auto &line : _board) {
        for (auto &square : line) {
            std::cout << square.getItem()->getEdible() << " ";
        }
        std::cout << std::endl;
    }
}