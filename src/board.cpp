#include "board.h"

board::board() {}

board::~board() {
    for (size_t i = 0; i < _board.size(); i++) {
        for (size_t j = 0; j < _board[i].size(); j++)
            _board[i][j].reset();

        _board[i].clear();
    }

    _board.clear();
}

void board::load() {

    std::ifstream inputFile("assets/pacman_board.txt");

    char c;
    // first column
    _board.push_back(std::vector<std::shared_ptr<square>>());
    while (inputFile.get(c)) {

        if (c == '\n') {
            // next column
            _board.push_back(std::vector<std::shared_ptr<square>>());
        } else {
            std::shared_ptr<square> Square = std::make_shared<square>();
            Square->setState(c - '0');
            Square->setItem(_EMPTY);
            _board.back().push_back(Square);
        }
    }
}

std::vector<std::vector<std::shared_ptr<square>>> board::getBoard() {
    return _board;
}

void board::transpose() {

    const size_t numRows = _board.size();
    const size_t numCols = _board.empty() ? 0 : _board[0].size();
    std::vector<std::vector<std::shared_ptr<square>>> tBoard(
        numCols, std::vector<std::shared_ptr<square>>(numRows));

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            tBoard[j][i] = _board[i][j];
        }
    }

    _board = tBoard;
}

void board::setItem() {

    // Dot
    size_t i = 0, j = 0;
    for (i = 0; i < _board.size(); i++) {
        for (j = 0; j < _board[i].size(); j++) {
            std::shared_ptr<square> Square = _board[i][j];
            if (Square->getState() == 0) {
                // teleportation hallway
                if (j == 13 && (i != 5 && i != 15))
                    Square->setItem(_EMPTY);
                // middle of the map
                else if (i >= 6 && i <= 14 && j >= 9 && j <= 17)
                    Square->setItem(_EMPTY);
                // pacman spawn
                else if (i == 10 && j == 20)
                    Square->setItem(_EMPTY);
                else {
                    Square->setItem(_DOT);
                    Square->setScore(DOT_POINT);
                }
            }
        }
    }

    // Powerup
    _board[1][3]->setItem(_POWERUP);
    _board[1][3]->setScore(POWERUP_POINT);
    _board[19][3]->setItem(_POWERUP);
    _board[19][3]->setScore(POWERUP_POINT);
    _board[1][20]->setItem(_POWERUP);
    _board[1][20]->setScore(POWERUP_POINT);
    _board[19][20]->setItem(_POWERUP);
    _board[19][20]->setScore(POWERUP_POINT);
}

std::vector<Coordinate> board::getDotList() {

    std::vector<Coordinate> vecDot;
    Coordinate coord;
    for (size_t i = 0; i < _board.size(); i++) {
        for (size_t j = 0; j < _board[i].size(); j++) {
            std::shared_ptr<square> Square = _board[i][j];
            if (Square->getItem() == _DOT) {
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
            std::shared_ptr<square> Square = _board[i][j];
            if (Square->getItem() == _POWERUP) {
                coord.x = i;
                coord.y = j;
                vecPowerup.push_back(coord);
            }
        }
    }
    return vecPowerup;
}
