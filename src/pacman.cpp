#include "pacman.h"

pacman::pacman() {
    _xBoard = PACMAN_INIT_X;
    _yBoard = PACMAN_INIT_Y;
    _xPixel = PACMAN_INIT_X * SCALE_PIXEL + PACMAN_CENTER_X;
    _yPixel = PACMAN_INIT_Y * SCALE_PIXEL + PACMAN_CENTER_Y;
    _lastDir = NONE;
    _score = 0;
    _powerup = false;
}
pacman::~pacman() {}

dir pacman::getLastDir() { return _lastDir; }

void pacman::updatePos() {
    switch (_lastDir) {
    case LEFT:
        if (_xPixel > 0)
            _xPixel--;
        else
            _lastDir = NONE;
        break;
    case RIGHT:
        if (_xPixel < 20 * SCALE_PIXEL)
            _xPixel++;
        else
            _lastDir = NONE;
        break;
    case UP:
        if (_yPixel > 0)
            _yPixel--;
        else
            _lastDir = NONE;
        break;
    case DOWN:
        if (_yPixel < 26 * SCALE_PIXEL)
            _yPixel++;
        else
            _lastDir = NONE;
        break;
    case NONE:
        break;
    }
}

std::pair<int, int> pacman::getPos() {
    return std::make_pair(_xPixel, _yPixel);
}

void pacman::updateDir(std::vector<std::vector<square *>> vecBoard,
                       dir currentDir) {

    // each square is 32x32 pixels
    // wait until pacman reaches the middle of the next square
    if ((_xPixel % 32) != PACMAN_CENTER_X || (_yPixel % 32) != PACMAN_CENTER_Y)
        return;

    switch (currentDir) {

    case LEFT:
        if (_xBoard < 0 && _yBoard != 13)
            _lastDir = NONE;

        if (vecBoard[_xBoard - 1][_yBoard]->getState() == 0) {
            _xBoard--;
            _lastDir = LEFT;

        } else if (vecBoard[_xBoard - 1][_yBoard]->getState() == 2) {
            _xBoard = 20;
            _xPixel = 20 * SCALE_PIXEL + PACMAN_CENTER_X;

        } else {
            _lastDir = NONE;
        }

        break;

    case RIGHT:
        if (_xBoard > 20 && _yBoard != 13)
            _lastDir = NONE;

        if (vecBoard[_xBoard + 1][_yBoard]->getState() == 0) {
            _xBoard++;
            _lastDir = RIGHT;

        } else if (vecBoard[_xBoard + 1][_yBoard]->getState() == 2) {
            _xBoard = 1;
            _xPixel = PACMAN_CENTER_X;

        } else {
            _lastDir = NONE;
        }

        break;

    case UP:
        if (_yBoard >= 26)
            _lastDir = NONE;

        if (vecBoard[_xBoard][_yBoard - 1]->getState() == 0) {
            _yBoard--;
            _lastDir = UP;

        } else {
            _lastDir = NONE;
        }

        break;

    case DOWN:
        if (_yBoard <= 0)
            _lastDir = NONE;

        if (vecBoard[_xBoard][_yBoard + 1]->getState() == 0) {
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

void pacman::updateSquare(std::vector<std::vector<square *>> vecBoard) {

    // update item
    if (vecBoard[_xBoard][_yBoard]->getItem() == _DOT) {

        if (_lastDir == LEFT || _lastDir == RIGHT) {
            if (abs(_xPixel % 32 - PACMAN_CENTER_X) != DOT_PACMAN_CONTACT) {
                return;
            }

        } else if (_lastDir == UP || _lastDir == DOWN) {
            if (abs(_yPixel % 32 - PACMAN_CENTER_Y) != DOT_PACMAN_CONTACT) {
                return;
            }
        } else
            return;

        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        _score = _score + 10;

    } else if (vecBoard[_xBoard][_yBoard]->getItem() == _POWERUP) {

        if (_lastDir == LEFT || _lastDir == RIGHT) {
            if (abs(_xPixel % 32 - PACMAN_CENTER_X) != POWERUP_PACMAN_CONTACT) {
                return;
            }
        } else if (_lastDir == UP || _lastDir == DOWN) {
            if (abs(_yPixel % 32 - PACMAN_CENTER_Y) != POWERUP_PACMAN_CONTACT) {
                return;
            }
        } else
            return;

        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        _score = _score + 50;

        std::cout << "powerup eaten" << std::endl;
        _powerup = true;
        timePoint1 = std::chrono::steady_clock::now();
    }

    if (_powerup) {
        time_t timePoint2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = timePoint2 - timePoint1;
        if (elapsedTime.count() > POWERUP_MODE) {
            _powerup = false;
            std::cout << "powerup expired" << std::endl;
        }
    }
}

int pacman::getScore() const { return _score; }

bool pacman::ghostCollision(std::vector<ghost> vecGhost) {

    if (_powerup == false) {
        for (auto ghost : vecGhost) {
            if (abs(_xPixel - ghost.getPos().first) < GHOST_PACMAN_CONTACT &&
                abs(_yPixel - ghost.getPos().second) < GHOST_PACMAN_CONTACT)
                return true;
        }
    } else {
        for (auto ghost : vecGhost) {
            if (abs(_xPixel - ghost.getPos().first) < GHOST_PACMAN_CONTACT &&
                abs(_yPixel - ghost.getPos().second) < GHOST_PACMAN_CONTACT) {
                ghost.houseReturn();
                return false;
            }
        }
    }

    return false;
}