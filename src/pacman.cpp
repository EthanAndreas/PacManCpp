#include "pacman.h"

pacman::pacman() {
    _xBoard = 10;
    _yBoard = 15;
    _xPixel = 326;
    _yPixel = 484;
}
pacman::~pacman() {}

dir *pacman::getLastDir() { return &_lastDir; }

void pacman::updatePos() {
    switch (_lastDir) {
    case LEFT:
        _xPixel--;
        break;
    case RIGHT:
        _xPixel++;
        break;
    case UP:
        _yPixel--;
        break;
    case DOWN:
        _yPixel++;
        break;
    case NONE:
        break;
    }
}

std::pair<int, int> pacman::getPos() {
    return std::make_pair(_xPixel, _yPixel);
}

void pacman::updateDir(std::vector<std::vector<square>> vecBoard,
                       dir currentDir) {

    // each square is 32x32 pixels
    // wait until pacman reaches the middle of the next square
    if ((_xPixel % 32) != 6 || (_yPixel % 32) != 4)
        return;

    switch (currentDir) {

    case LEFT:
        if (_xBoard <= 0)
            _lastDir = NONE;

        if (vecBoard[_xBoard - 1][_yBoard].getState() == 0) {
            _xBoard--;
            _lastDir = LEFT;

        } else if (vecBoard[_xBoard - 1][_yBoard].getState() == 2) {
            _xBoard = 20;
            _xPixel = 646;

        } else {
            _lastDir = NONE;
        }

        break;

    case RIGHT:
        if (_xBoard >= 21)
            _lastDir = NONE;

        if (vecBoard[_xBoard + 1][_yBoard].getState() == 0) {
            _xBoard++;
            _lastDir = RIGHT;

        } else if (vecBoard[_xBoard + 1][_yBoard].getState() == 2) {
            _xBoard = 0;
            _xPixel = 6;

        } else {
            _lastDir = NONE;
        }

        break;

    case UP:
        if (_yBoard >= 26)
            _lastDir = NONE;

        if (vecBoard[_xBoard][_yBoard - 1].getState() == 0) {
            _yBoard--;
            _lastDir = UP;

        } else {
            _lastDir = NONE;
        }

        break;

    case DOWN:
        if (_yBoard <= 0)
            _lastDir = NONE;

        if (vecBoard[_xBoard][_yBoard + 1].getState() == 0) {
            _yBoard++;
            _lastDir = DOWN;

        } else {
            _lastDir = NONE;
        }

        break;

    case NONE:
        break;
    }
}

dir pacman::getDir() { return _lastDir; }

void pacman::updateSquare(std::vector<std::vector<square>> vecBoard) {

    if ((_xPixel % 32) != 6 || (_yPixel % 32) != 4)
        return;

    switch (_lastDir) {
    case LEFT:
        vecBoard[_xBoard - 1][_yBoard].getItem()->setCarater(_NONE);
        break;
    case RIGHT:
        vecBoard[_xBoard + 1][_yBoard].getItem()->setCarater(_NONE);
        break;
    case UP:
        vecBoard[_xBoard][_yBoard - 1].getItem()->setCarater(_NONE);
        break;
    case DOWN:
        vecBoard[_xBoard][_yBoard + 1].getItem()->setCarater(_NONE);
        break;
    case NONE:
        break;
    }

    if (_xBoard == 0 && _yBoard == 13)
        vecBoard[21][13].getItem()->setCarater(_NONE);
    else if (_xBoard == 21 && _yBoard == 13)
        vecBoard[0][13].getItem()->setCarater(_NONE);

    vecBoard[_xBoard][_yBoard].getItem()->setCarater(_PACMAN);
}