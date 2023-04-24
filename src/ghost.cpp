#include "ghost.h"

ghost::ghost() {
    _xBoard = 0;
    _yBoard = 0;
    _xPixel = 0;
    _yPixel = 0;
    _lastDir = NONE;
    srand(time(NULL));
}
ghost::~ghost() {}

void ghost::setGhost(color c) {
    _color = c;
    switch (c) {
    case RED:
        _isInHouse = false;
        _xBoard = RED_GHOST_INIT_X;
        _yBoard = RED_GHOST_INIT_Y;
        _xPixel = RED_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
        _yPixel = RED_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
        break;
    case PINK:
        _isInHouse = true;
        _xBoard = PINK_GHOST_INIT_X;
        _yBoard = PINK_GHOST_INIT_Y;
        _xPixel = PINK_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
        _yPixel = PINK_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
        break;
    case BLUE:
        _isInHouse = true;
        _xBoard = BLUE_GHOST_INIT_X;
        _yBoard = BLUE_GHOST_INIT_Y;
        _xPixel = BLUE_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
        _yPixel = BLUE_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
        break;
    case ORANGE:
        _isInHouse = true;
        _xBoard = ORANGE_GHOST_INIT_X;
        _yBoard = ORANGE_GHOST_INIT_Y;
        _xPixel = ORANGE_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
        _yPixel = ORANGE_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
        break;
    }
}

color ghost::getGhost() { return _color; }

bool ghost::isGhostInHouse() { return _isInHouse; }

void ghost::updateDirInHouse() {

    if (_xPixel % 32 != GHOST_CENTER_X || _yPixel % 32 != GHOST_CENTER_Y)
        return;

    if (_yBoard == 13) {
        _lastDir = UP;
        _yBoard--;
    } else if (_yBoard == 12) {
        _lastDir = DOWN;
        _yBoard++;
    }
}

void ghost::leaveGhostHouse() {

    if (_yBoard == 13) {
        _yBoard--;
        _lastDir = UP;
        _isInHouse = false;
    } else if (_yBoard == 12)
        _isInHouse = false;
}

dir ghost::getLastDir() { return _lastDir; }

void ghost::updatePos() {
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

std::pair<int, int> ghost::getPos() { return std::make_pair(_xPixel, _yPixel); }

void ghost::updateDir(std::vector<std::vector<square>> vecBoard) {

    // each square is 32x32 pixels
    // wait until ghost reaches the middle of the next square
    if ((_xPixel % 32) != GHOST_CENTER_X || (_yPixel % 32) != GHOST_CENTER_Y)
        return;

    bool findPos = false;
    while (findPos == false) {

        if (vecBoard[_xBoard][_yBoard - 1].getState() == 3) {
            _yBoard--;
            _lastDir = UP;
            findPos = true;
            break;
        }

        if (vecBoard[_xBoard][_yBoard].getState() == 3) {
            _yBoard--;
            _lastDir = UP;
            findPos = true;
            break;
        }

        if (vecBoard[_xBoard + 1][_yBoard - 1].getState() == 3) {
            _xBoard++;
            _lastDir = RIGHT;
            findPos = true;
            break;
        }

        if (vecBoard[_xBoard - 1][_yBoard - 1].getState() == 3) {
            _xBoard--;
            _lastDir = LEFT;
            findPos = true;
            break;
        }

        int randDir = rand() % 4;

        switch (randDir) {

        case LEFT:
            // avoid going back
            if (_lastDir == RIGHT)
                break;

            // avoid teleporation hall
            if (_xBoard - 1 == 4 && _yBoard == 13)
                break;

            if (vecBoard[_xBoard - 1][_yBoard].getState() == 0) {
                _xBoard--;
                _lastDir = LEFT;
                findPos = true;
            }

            break;

        case RIGHT:
            // avoid going back
            if (_lastDir == LEFT)
                break;

            // avoid teleporation hall
            if (_xBoard + 1 == 16 && _yBoard == 13)
                break;

            if (vecBoard[_xBoard + 1][_yBoard].getState() == 0) {
                _xBoard++;
                _lastDir = RIGHT;
                findPos = true;
            }

            break;

        case UP:
            // avoid going back
            if (_lastDir == DOWN)
                break;

            if (vecBoard[_xBoard][_yBoard - 1].getState() == 0) {
                _yBoard--;
                _lastDir = UP;
                findPos = true;
            }

            break;

        case DOWN:
            // avoid going back
            if (_lastDir == UP)
                break;

            if (vecBoard[_xBoard][_yBoard + 1].getState() == 0) {
                _yBoard++;
                _lastDir = DOWN;
                findPos = true;
            }

            break;

        case NONE:
            break;
        }
    }
}

dir ghost::getDir() { return _lastDir; }

void ghost::updateSquare(std::vector<std::vector<square>> vecBoard) {

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

    vecBoard[_xBoard][_yBoard].getItem()->setCarater(_GHOST);
}