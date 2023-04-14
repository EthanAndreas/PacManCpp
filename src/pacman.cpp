#include "pacman.h"

pacman::pacman() {
    _xBoard = 10;
    _yBoard = 15;
    _xPixel = 326;
    _yPixel = 484;
}
pacman::~pacman() {}

dir *pacman::getLastDir() { return &_lastDir; }

void pacman::updatePos(int column, int line) {
    _xPixel = column;
    _yPixel = line;
}

void pacman::updateDir(board Board, dir currentDir) {

    // each square is 32x32 pixels
    // wait until pacman reaches the middle of the next square
    if ((_xPixel % 32) != 6 || (_yPixel % 32) != 4)
        return;

    std::vector<std::vector<square>> vBoard = Board.getBoard();

    std::cout << "xBoard: " << _xBoard << " yBoard: " << _yBoard << std::endl;
    std::cout << "xPixel: " << _xPixel << " yPixel: " << _yPixel << std::endl;

    switch (currentDir) {

    case LEFT:
        if (_xBoard <= 0)
            _lastDir = NONE;
        if (vBoard[_yBoard][_xBoard - 1].getState() == 0) {
            _xBoard--;
            _lastDir = LEFT;
        } else {
            _lastDir = NONE;
        }
        break;

    case RIGHT:
        if (_xBoard >= 21)
            _lastDir = NONE;
        if (vBoard[_yBoard][_xBoard + 1].getState() == 0) {
            _xBoard++;
            _lastDir = RIGHT;
        } else {
            _lastDir = NONE;
        }
        break;

    case UP:
        if (_yBoard >= 26)
            _lastDir = NONE;
        if (vBoard[_yBoard + 1][_xBoard].getState() == 0) {
            _yBoard++;
            _lastDir = UP;
        } else {
            _lastDir = NONE;
        }
        break;

    case DOWN:
        if (_yBoard <= 0)
            _lastDir = NONE;
        if (vBoard[_yBoard - 1][_xBoard].getState() == 0) {
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