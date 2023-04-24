#include "ghost.h"

ghost::ghost() {
    _xBoard = GHOST_INIT_X;
    _yBoard = GHOST_INIT_Y;
    _xPixel = GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
    _yPixel = GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
    _lastDir = NONE;
    srand(time(NULL));
}
ghost::~ghost() {}

void ghost::setGhost(color c) { _color = c; }

color ghost::getColor() { return _color; }

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
            // TODO : add wait function to launch ghost by ghost
            _yBoard--;
            _lastDir = UP;
            findPos = true;
            break;
        }

        if (vecBoard[_xBoard][_yBoard].getState() == 3) {
            // TODO : add wait function to launch ghost by ghost
            _yBoard--;
            _lastDir = UP;
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