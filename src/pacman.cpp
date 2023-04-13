#include "pacman.h"

pacman::pacman() {
    _xBoard = 15;
    _yBoard = 10;
    _xPixel = 484;
    _yPixel = 326;
}
pacman::~pacman() {}

dir *pacman::getLastDir() { return &_lastDir; }

void pacman::updatePos(int column, int line) {
    _xPixel = line;
    _yPixel = column;
}

void pacman::updateDir(board Board, dir currentDir) {

    // while pacman does not reach the virtual square, the position
    // is not updated
    // each square is 32x32 pixels
    if ((_xPixel / 32) != _xBoard && (_yPixel / 32) != _yBoard) {

        return;
    }

    std::vector<std::vector<square>> vBoard = Board.getBoard();

    switch (currentDir) {

    case LEFT:
        if (_xBoard <= 0)
            return;
        if (vBoard[_xBoard - 1][_yBoard].getState() == 0) {
            _xBoard--;
            _lastDir = LEFT;
        } else {
            _lastDir = NONE;
        }
        break;

    case RIGHT:
        if (_xBoard >= 26)
            return;
        if (vBoard[_xBoard + 1][_yBoard].getState() == 0) {
            _xBoard++;
            _lastDir = RIGHT;
        } else {
            _lastDir = NONE;
        }
        break;

    case UP:
        if (_yBoard >= 21)
            return;
        if (vBoard[_xBoard][_yBoard + 1].getState() == 0) {
            _yBoard++;
            _lastDir = UP;
        } else {
            _lastDir = NONE;
        }
        break;

    case DOWN:
        if (_yBoard <= 0)
            return;
        if (vBoard[_xBoard][_yBoard - 1].getState() == 0) {
            _yBoard--;
            _lastDir = DOWN;
        } else {
            _lastDir = NONE;
        }
        break;

    case NONE:
        break;
    }
}