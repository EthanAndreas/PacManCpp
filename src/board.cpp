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
board::~board() {
    for (auto &line : _board) {
        for (auto &square : line) {
            square.~square();
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
            _board.back().push_back(Square);
        }
    }
}

void board::display() {

    for (auto &line : _board) {
        for (auto &square : line) {
            std::cout << square.getState() << " ";
        }
        std::cout << std::endl;
    }
}