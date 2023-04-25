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

    if (_xBoard < 0 || _xBoard > 20 || _yBoard <= 0 || _yBoard >= 26)
        exit(EXIT_FAILURE);

    // wait until pacman reaches the middle of the next square
    if ((_xPixel % SCALE_PIXEL) != PACMAN_CENTER_X ||
        (_yPixel % SCALE_PIXEL) != PACMAN_CENTER_Y)
        return;

    switch (currentDir) {

    case LEFT:
        // out of the board
        if (_xBoard <= 0 && _yBoard != 13) {
            _lastDir = NONE;
            break;
        }
        // teleportation
        else if (_xBoard == 0 && _yBoard == 13) {
            _xBoard = 20;
            _xPixel = 20 * SCALE_PIXEL + PACMAN_CENTER_X;
            break;
        }

        if (vecBoard[_xBoard - 1][_yBoard]->getState() == HALL) {
            _xBoard--;
            _lastDir = LEFT;
        } else {
            _lastDir = NONE;
        }

        break;

    case RIGHT:
        // out of the board
        if (_xBoard >= 20 && _yBoard != 13) {
            _lastDir = NONE;
            break;
        }
        // teleportation
        else if (_xBoard == 20 && _yBoard == 13) {
            _xBoard = 0;
            _xPixel = PACMAN_CENTER_X;
            break;
        }

        if (vecBoard[_xBoard + 1][_yBoard]->getState() == HALL) {
            _xBoard++;
            _lastDir = RIGHT;
        } else {
            _lastDir = NONE;
        }

        break;

    case UP:
        // out of the board
        if (_yBoard >= 26) {
            _lastDir = NONE;
            break;
        }

        if (vecBoard[_xBoard][_yBoard - 1]->getState() == HALL) {
            _yBoard--;
            _lastDir = UP;

        } else {
            _lastDir = NONE;
        }

        break;

    case DOWN:
        // out of the board
        if (_yBoard <= 0) {
            _lastDir = NONE;
            break;
        }

        if (vecBoard[_xBoard][_yBoard + 1]->getState() == HALL) {
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

    if (_xBoard < 0 || _xBoard > 20 || _yBoard <= 0 || _yBoard >= 26)
        exit(EXIT_FAILURE);

    // update item
    if (vecBoard[_xBoard][_yBoard]->getItem() == _DOT) {

        if (_lastDir == LEFT || _lastDir == RIGHT) {
            if (abs(_xPixel % SCALE_PIXEL - PACMAN_CENTER_X) !=
                DOT_PACMAN_CONTACT) {
                return;
            }

        } else if (_lastDir == UP || _lastDir == DOWN) {
            if (abs(_yPixel % SCALE_PIXEL - PACMAN_CENTER_Y) !=
                DOT_PACMAN_CONTACT) {
                return;
            }
        } else
            return;

        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        _score = _score + DOT_SCORE;

    } else if (vecBoard[_xBoard][_yBoard]->getItem() == _POWERUP) {

        if (_lastDir == LEFT || _lastDir == RIGHT) {
            if (abs(_xPixel % SCALE_PIXEL - PACMAN_CENTER_X) !=
                POWERUP_PACMAN_CONTACT) {
                return;
            }
        } else if (_lastDir == UP || _lastDir == DOWN) {
            if (abs(_yPixel % SCALE_PIXEL - PACMAN_CENTER_Y) !=
                POWERUP_PACMAN_CONTACT) {
                return;
            }
        } else
            return;

        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        _score = _score + POWERUP_SCORE;

        _powerup = true;
        timePoint1 = std::chrono::steady_clock::now();
    }

    if (_powerup) {
        time_t timePoint2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = timePoint2 - timePoint1;
        if (elapsedTime.count() > POWERUP_MODE)
            _powerup = false;
    }
}

int pacman::getScore() const { return _score; }

bool pacman::ghostCollision(std::vector<ghost *> vecGhost) {

    if (_powerup == false) {
        for (auto ghost : vecGhost) {
            if (abs(_xPixel - ghost->getPos().first) < GHOST_PACMAN_CONTACT &&
                abs(_yPixel - ghost->getPos().second) < GHOST_PACMAN_CONTACT)
                return true;
        }
    } else {
        for (auto ghost : vecGhost) {
            if (abs(_xPixel - ghost->getPos().first) < GHOST_PACMAN_CONTACT &&
                abs(_yPixel - ghost->getPos().second) < GHOST_PACMAN_CONTACT) {
                ghost->houseReturn();
                _score = _score + GHOST_SCORE;
            }
        }
    }

    return false;
}