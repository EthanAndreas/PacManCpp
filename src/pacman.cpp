#include "pacman.h"

pacman::pacman() {
    _xBoard = PACMAN_INIT_X;
    _yBoard = PACMAN_INIT_Y;
    _xPixel = PACMAN_INIT_X * SCALE_PIXEL + PACMAN_CENTER_X;
    _yPixel = PACMAN_INIT_Y * SCALE_PIXEL + PACMAN_CENTER_Y;
    _lastDir = NONE;
    _oldDir = NONE;
    _score = 0;
    _powerup = false;
    _dotCounter = 0;
    _remainingLife = DEFAULT_LIVES;
}
pacman::~pacman() {}

std::pair<size_t, size_t> pacman::getPos() {
    return std::make_pair(_xPixel, _yPixel);
}

void pacman::updatePos() {
    // normal speed
    switch (_lastDir) {
    case LEFT:
        _oldDir = LEFT;
        _xPixel -= PACMAN_SPEED;
        break;
    case RIGHT:
        _oldDir = RIGHT;
        _xPixel += PACMAN_SPEED;
        break;
    case UP:
        _oldDir = UP;
        _yPixel -= PACMAN_SPEED;
        break;
    case DOWN:
        _oldDir = DOWN;
        _yPixel += PACMAN_SPEED;
        break;
    case NONE:
        break;
    }
}

bool pacman::waitSquareCenter() {

    size_t xCenter = _xBoard * SCALE_PIXEL + PACMAN_CENTER_X,
           yCenter = _yBoard * SCALE_PIXEL + PACMAN_CENTER_Y;

    // speed of 2 pixels per frame
    if (_lastDir == LEFT &&
        _xPixel - PACMAN_SPEED <= xCenter + PACMAN_RANGE_CENTER) {
        _xPixel = _xBoard * SCALE_PIXEL + PACMAN_CENTER_X;
        return true;
    } else if (_lastDir == RIGHT &&
               _xPixel + PACMAN_SPEED >= xCenter - PACMAN_RANGE_CENTER) {
        _xPixel = _xBoard * SCALE_PIXEL + PACMAN_CENTER_X;
        return true;
    } else if (_lastDir == UP &&
               _yPixel + PACMAN_SPEED <= yCenter + PACMAN_RANGE_CENTER) {
        _yPixel = _yBoard * SCALE_PIXEL + PACMAN_CENTER_Y;
        return true;
    } else if (_lastDir == DOWN &&
               _yPixel + PACMAN_SPEED >= yCenter - PACMAN_RANGE_CENTER) {
        _yPixel = _yBoard * SCALE_PIXEL + PACMAN_CENTER_Y;
        return true;
    } else if (_lastDir == NONE)
        return true;

    return false;
}

dir pacman::getLastDir() { return _lastDir; }

void pacman::updateDir(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
    dir currentDir) {

    if (_xBoard > 20 || _yBoard == 0 || _yBoard >= 26) {
        std::cerr << "Pacman out of the board in updateDir" << std::endl;
        exit(EXIT_FAILURE);
    }

    switch (currentDir) {

    case LEFT:
        // out of the board
        if (_xBoard == 0 && _yBoard != 13) {
            _lastDir = NONE;
            break;
        }
        // teleportation
        else if (_xBoard == 0 && _yBoard == 13) {
            _xBoard = 20;
            _xPixel = 20 * SCALE_PIXEL + PACMAN_CENTER_X;
        }

        if (vecBoard[_xBoard - 1][_yBoard]->getState() == HALL) {
            _xBoard--;
            _lastDir = LEFT;
        } else {
            _lastDir = NONE;
        }

        _oldDir = LEFT;
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
        }

        if (vecBoard[_xBoard + 1][_yBoard]->getState() == HALL) {
            _xBoard++;
            _lastDir = RIGHT;
        } else {
            _lastDir = NONE;
        }

        _oldDir = RIGHT;
        break;

    case UP:
        // out of the board
        if (_yBoard == 0) {
            _lastDir = NONE;
            break;
        }

        if (vecBoard[_xBoard][_yBoard - 1]->getState() == HALL) {
            _yBoard--;
            _lastDir = UP;

        } else {
            _lastDir = NONE;
        }

        _oldDir = UP;
        break;

    case DOWN:
        // out of the board
        if (_yBoard >= 26) {
            _lastDir = NONE;
            break;
        }

        if (vecBoard[_xBoard][_yBoard + 1]->getState() == HALL) {
            _yBoard++;
            _lastDir = DOWN;

        } else {
            _lastDir = NONE;
        }

        _oldDir = DOWN;
        break;

    case NONE:
        break;
    }
}

void pacman::updateSquare(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
    std::vector<std::shared_ptr<ghost>> vecGhost, fruit *Fruit) {

    if (_xBoard > 20 || _yBoard >= 26) {
        std::cerr << "Pacman out of the board in updateSquare" << std::endl;
        exit(EXIT_FAILURE);
    }

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

        _score = _score + vecBoard[_xBoard][_yBoard]->getScore();
        _dotCounter++;
        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        vecBoard[_xBoard][_yBoard]->setScore(0);

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

        _score = _score + vecBoard[_xBoard][_yBoard]->getScore();
        vecBoard[_xBoard][_yBoard]->setItem(_EMPTY);
        vecBoard[_xBoard][_yBoard]->setScore(0);

        _powerup = true;
        for (auto Ghost : vecGhost) {
            if (Ghost->isInHouse() == false)
                Ghost->setFrightened(true);
        }

        timePoint1 = std::chrono::steady_clock::now();

    } else if (_xBoard == FRUIT_X && _yBoard == FRUIT_Y &&
               vecBoard[_xBoard][_yBoard]->getItem() == _FRUIT) {

        if (_lastDir == LEFT || _lastDir == RIGHT) {
            if (abs(_xPixel % 32 - PACMAN_CENTER_X) != FRUIT_PACMAN_CONTACT) {
                return;
            }
        } else if (_lastDir == UP || _lastDir == DOWN) {
            if (abs(_yPixel % 32 - PACMAN_CENTER_Y) != FRUIT_PACMAN_CONTACT) {
                return;
            }
        } else
            return;

        _score = _score + vecBoard[_xBoard][_yBoard]->getScore();
        Fruit->eatFruit(vecBoard);
        _dotCounter = 0;
    }

    if (_powerup) {
        time_t timePoint2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = timePoint2 - timePoint1;
        if (elapsedTime.count() > POWERUP_MODE) {
            _powerup = false;
            for (auto Ghost : vecGhost) {
                if (Ghost->isInHouse() == false)
                    Ghost->setFrightened(false);
            }
        }
    }
}

time_t pacman::getTimePoint1() { return timePoint1; }

bool pacman::isPowerup() { return _powerup; }

size_t pacman::getScore() { return _score; }

bool pacman::ghostCollision(std::vector<std::shared_ptr<ghost>> vecGhost) {

    for (auto Ghost : vecGhost) {
        if (abs(_xPixel - Ghost->getPos().first) < GHOST_PACMAN_CONTACT &&
            abs(_yPixel - Ghost->getPos().second) < GHOST_PACMAN_CONTACT) {
            if (Ghost->isReturnHouse() == false &&
                Ghost->isFrightened() == true) {
                Ghost->setReturnHouse();
                _score = _score + GHOST_SCORE;
                return false;
            } else if (Ghost->isReturnHouse() == false &&
                       Ghost->isFrightened() == false)
                return true;
        }
    }

    return false;
}

size_t pacman::getDotCounter() { return _dotCounter; }

void pacman::resetDotCounter() { _dotCounter = 0; }

short pacman::getRemainingLife() { return _remainingLife; }

void pacman::looseLife() { _remainingLife--; }

void pacman::resetPos() {
    _xBoard = PACMAN_INIT_X;
    _yBoard = PACMAN_INIT_Y;
    _xPixel = PACMAN_INIT_X * SCALE_PIXEL + PACMAN_CENTER_X;
    _yPixel = PACMAN_INIT_Y * SCALE_PIXEL + PACMAN_CENTER_Y;
    _lastDir = NONE;
    _powerup = false;
}

dir pacman::getOldDir() { return _oldDir; }