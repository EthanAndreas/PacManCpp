#include "board.h"

/*----------------------------------Square-----------------------------------*/

square::square() {}

square::~square() {}

void square::setState(short state) { _state = state; }

short square::getState() { return _state; }

void square::setItem(item *item) { _item = item; }

item *square::getItem() { return _item; }

/*-----------------------------------Board------------------------------------*/

board::board() { _board = std::vector<std::vector<square>>(); }

board::~board() {
    for (auto &line : _board) {
        for (auto &square : line) {
            square.~square();
        }
    }
}

void board::load() {

    std::ifstream inputFile("assets/pacman_board.txt");

    char c;
    square Square;
    // first column
    _board.push_back(std::vector<square>());
    while (inputFile.get(c)) {

        if (c == '\n') {
            // next column
            _board.push_back(std::vector<square>());
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

    // Pacman
    _board[PACMAN_INIT_X][PACMAN_INIT_Y].getItem()->setCarater(_PACMAN);

    // Ghost
    _board[GHOST_INIT_X][GHOST_INIT_Y].getItem()->setCarater(_GHOST);

    // Dot
    size_t i = 0, j = 0;
    for (i = 0; i < _board.size(); i++) {
        for (j = 0; j < _board[i].size(); j++) {
            square &square = _board[i][j];
            if (square.getState() == 0) {
                // teleportation hallway
                if (j == 13 && (i != 5 && i != 15))
                    square.getItem()->setEdible(_EMPTY);
                // middle of the map
                else if (i >= 6 && i <= 14 && j >= 9 && j <= 17)
                    square.getItem()->setEdible(_EMPTY);
                else
                    square.getItem()->setEdible(_DOT);
            }
        }
    }

    // Powerup
    _board[1][3].getItem()->setEdible(_POWERUP);
    _board[19][3].getItem()->setEdible(_POWERUP);
    _board[1][20].getItem()->setEdible(_POWERUP);
    _board[19][20].getItem()->setEdible(_POWERUP);
}

std::vector<Coordinate> board::getDotList() {

    std::vector<Coordinate> vecDot;
    Coordinate coord;
    for (size_t i = 0; i < _board.size(); i++) {
        for (size_t j = 0; j < _board[i].size(); j++) {
            square &square = _board[i][j];
            if (square.getItem()->getEdible() == _DOT) {
                coord.x = i;
                coord.y = j;
                vecDot.push_back(coord);
            }
        }
    }

    return vecDot;
}

std::vector<Coordinate> board::getPowerupList() {

    std::vector<Coordinate> vecPowerup;
    Coordinate coord;
    for (size_t i = 0; i < _board.size(); i++) {
        for (size_t j = 0; j < _board[i].size(); j++) {
            square &square = _board[i][j];
            if (square.getItem()->getEdible() == _POWERUP) {
                coord.x = i;
                coord.y = j;
                vecPowerup.push_back(coord);
            }
        }
    }
    return vecPowerup;
}