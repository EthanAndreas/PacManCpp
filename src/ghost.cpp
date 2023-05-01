#include "ghost.h"

ghost::ghost() {
    _xBoard = 0;
    _yBoard = 0;
    _xPixel = 0;
    _yPixel = 0;
    _lastDir = NONE;
    _isReturnHouse = false;
    _isFear = false;
}
ghost::~ghost() {}

void ghost::setTimer() {
    timePoint1 = std::chrono::steady_clock::now();
    std::mt19937 _rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
}

void ghost::setGhost(color c) {
    _color = c;
    switch (c) {
    case RED:
        _isInHouse = true;
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

bool ghost::isInHouse() { return _isInHouse; }

bool ghost::isReturnHouse() { return _isReturnHouse; }

void ghost::leaveGhostHouse() {

    time_t timePoint2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = timePoint2 - timePoint1;
    bool isTime = false;

    switch (_color) {
    case RED:
        if (elapsedTime.count() >= RED_GHOST_WAIT_TIME)
            _isInHouse = false;
        break;
    case PINK:
        if (elapsedTime.count() >= PINK_GHOST_WAIT_TIME)
            isTime = true;
        break;
    case BLUE:
        if (elapsedTime.count() >= BLUE_GHOST_WAIT_TIME)
            isTime = true;
        break;
    case ORANGE:
        if (elapsedTime.count() >= ORANGE_GHOST_WAIT_TIME)
            isTime = true;
        break;
    default:
        break;
    }

    if (isTime == false) {

        if (_xPixel % SCALE_PIXEL != GHOST_CENTER_X ||
            _yPixel % SCALE_PIXEL != GHOST_CENTER_Y)
            return;

        if (_yBoard == 13) {
            _lastDir = UP;
            _yBoard--;
        } else if (_yBoard == 12) {
            _lastDir = DOWN;
            _yBoard++;
        }
    } else {

        if (_yBoard == 13) {
            _yBoard--;
            _lastDir = UP;
            _isInHouse = false;
        } else if (_yBoard == 12)
            _isInHouse = false;
    }
}

void ghost::houseReturn() {

    _isReturnHouse = true;
    _isFear = false;
}

void ghost::setFrightened(bool isFear) {
    // swap speed 2 for 1
    if (isFear == true) {
        _xPixel = _xPixel - (_xPixel % 2);
        _yPixel = _yPixel - (_yPixel % 2);
    }
    _isFear = isFear;
}

bool ghost::isFrightened() { return _isFear; }

dir ghost::getLastDir() { return _lastDir; }

void ghost::updatePos() {

    if (_isFear == false) {
        // normal speed
        switch (_lastDir) {
        case LEFT:
            _xPixel -= 2;
            break;
        case RIGHT:
            _xPixel += 2;
            break;
        case UP:
            _yPixel -= 2;
            break;
        case DOWN:
            _yPixel += 2;
            break;
        case NONE:
            break;
        }
    } else if (_isFear == true) {
        // slow down the ghost
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
}

std::pair<int, int> ghost::getPos() { return std::make_pair(_xPixel, _yPixel); }

void ghost::updateDir(std::vector<std::vector<square *>> vecBoard,
                      std::pair<int, int> pacPos, dir dirPac) {

    if (_xBoard < 0 || _xBoard > 20 || _yBoard <= 0 || _yBoard >= 26) {
        std::cerr << "Ghost out of the board in updateDir" << std::endl;
        exit(EXIT_FAILURE);
    }

    // wait until ghost reaches the middle of the next square
    if (_isFear == false) {
        if (abs(_xPixel % SCALE_PIXEL - GHOST_CENTER_X) > 1 ||
            abs(_yPixel % SCALE_PIXEL - GHOST_CENTER_Y) > 1)
            return;
    } else if (_isFear == true) {
        if (_xPixel % SCALE_PIXEL != GHOST_CENTER_X ||
            _yPixel % SCALE_PIXEL != GHOST_CENTER_Y)
            return;
    }

    if (_isReturnHouse == true) {

        // arrive at the house
        if ((_color == RED && _xBoard == RED_GHOST_INIT_X &&
             _yBoard == RED_GHOST_INIT_Y) ||
            (_color == PINK && _xBoard == PINK_GHOST_INIT_X &&
             _yBoard == PINK_GHOST_INIT_Y) ||
            (_color == BLUE && _xBoard == BLUE_GHOST_INIT_X &&
             _yBoard == BLUE_GHOST_INIT_Y) ||
            (_color == ORANGE && _xBoard == ORANGE_GHOST_INIT_X &&
             _yBoard == ORANGE_GHOST_INIT_Y)) {

            _isReturnHouse = false;
            _lastDir = NONE;
            setGhost(_color);
            timePoint1 = std::chrono::steady_clock::now();
            return;
        }

        // go the initial position
        if (_xBoard == 10 && _yBoard == 10) {
            _lastDir = DOWN;
            _yBoard++;
            return;
        } else if (_xBoard == 10 && _yBoard == 11) {
            _lastDir = DOWN;
            _yBoard++;
            return;
        }

        switch (_color) {
        case RED:
            break;
        case PINK:

            if (_xBoard == 10 && _yBoard == 12) {
                _lastDir = LEFT;
                _xBoard--;
                return;
            }
            break;
        case BLUE:
            if (_xBoard == 10 && _yBoard == 12) {
                _lastDir = DOWN;
                _yBoard++;
                return;
            }
            break;
        case ORANGE:
            if (_xBoard == 10 && _yBoard == 12) {
                _lastDir = RIGHT;
                _xBoard++;
                return;
            }
            break;
        }

        // update direction with shortest path
        updateDirWithShortestPath(vecBoard, GHOST_INIT_X, GHOST_INIT_Y);
        return;
    }

    // ghost leaving the house
    // at the bottom of the door
    if (_xBoard >= 9 && _xBoard <= 11 && _yBoard >= 11 && _yBoard <= 13) {

        if (vecBoard[_xBoard][_yBoard - 1]->getState() == DOOR) {
            _yBoard--;
            _lastDir = UP;
            return;
        }
        // in the door
        if (vecBoard[_xBoard][_yBoard]->getState() == DOOR) {
            _yBoard--;
            _lastDir = UP;
            return;
        }
        // at the bottom left of the door
        if (vecBoard[_xBoard + 1][_yBoard - 1]->getState() == DOOR) {
            _xBoard++;
            _lastDir = RIGHT;
            return;
        }
        // at the bottom right of the door
        if (vecBoard[_xBoard - 1][_yBoard - 1]->getState() == DOOR) {
            _xBoard--;
            _lastDir = LEFT;
            return;
        }
    }

    // if ghost is on the teleportation, take it
    if (_xBoard == 0 && _yBoard == 13) {
        _xBoard = 20;
        _xPixel = 20 * SCALE_PIXEL + GHOST_CENTER_X;
    } else if (_xBoard == 20 && _yBoard == 13) {
        _xBoard = 0;
        _xPixel = GHOST_CENTER_X;
    }

    // if ghost enters in the teleportation hall, go to the teleportation
    // hall
    if (_xBoard <= 4 && _yBoard == 13 && _lastDir == LEFT) {
        _xBoard--;
        return;
    } else if (_xBoard >= 16 && _yBoard == 13 && _lastDir == RIGHT) {
        _xBoard++;
        return;
    }

    switch (_color) {
    case RED:
        updateDirRed(vecBoard, pacPos.first / SCALE_PIXEL,
                     pacPos.second / SCALE_PIXEL);
        break;
    case PINK:
        updateDirPink(vecBoard, pacPos.first / SCALE_PIXEL,
                      pacPos.second / SCALE_PIXEL, dirPac);
        break;
    case BLUE:
        updateDirBlue(vecBoard, pacPos.first / SCALE_PIXEL,
                      pacPos.second / SCALE_PIXEL, dirPac);
        break;
    case ORANGE:
        updateDirOrange(vecBoard);
        break;
    }
}

void ghost::updateDirRed(std::vector<std::vector<square *>> vecBoard, int xPac,
                         int yPac) {

    // get the shortest path to pacman
    std::vector<Node *> path =
        findShortestPath(vecBoard, _xBoard, _yBoard, xPac, yPac);
    // if a shortest path is found, assign the new direction
    if (path.size() >= 2) {
        _lastDir = findDir(path[0], path[1]);
        switch (_lastDir) {
        case LEFT:
            _xBoard--;
            break;
        case RIGHT:
            _xBoard++;
            break;
        case UP:
            _yBoard--;
            break;
        case DOWN:
            _yBoard++;
            break;
        case NONE:
            break;
        }
    }
    // if an error occurs on A* algorithm, take a random direction
    else
        updateDirRandom(vecBoard);
}

void ghost::updateDirPink(std::vector<std::vector<square *>> vecBoard, int xPac,
                          int yPac, dir dirPac) {

    // get the 4th square in front of pacman
    int xPac4 = xPac;
    int yPac4 = yPac;

    if (xPac < 0 || xPac > 20 || yPac <= 0 || yPac >= 26) {
        std::cerr << "Pacman out of the board in updateDirPink" << std::endl;
        exit(EXIT_FAILURE);
    }

    // if ghost is at a distance less than 4 go on pacman
    if (abs(_xBoard - xPac) + abs(_yBoard - yPac) < 4) {
        updateDirWithShortestPath(vecBoard, xPac, yPac);
        return;
    }

    int dist = 0;
    while (dist < 4) {

        switch (dirPac) {
        case LEFT:
            if (xPac4 <= 0)
                break;

            if (vecBoard[xPac4 - 1][yPac4]->getState() == WALL) {
                dist = 4;
                break;
            }
            xPac4--;
            break;

        case RIGHT:
            if (xPac4 >= 20)
                break;

            if (vecBoard[xPac4 + 1][yPac4]->getState() == WALL) {
                dist = 4;
                break;
            }
            xPac4++;
            break;

        case UP:
            if (yPac4 <= 0)
                break;

            if (vecBoard[xPac4][yPac4 - 1]->getState() == WALL) {
                dist = 4;
                break;
            }
            yPac4--;
            break;

        case DOWN:
            if (yPac4 >= 26)
                break;

            if (vecBoard[xPac4][yPac4 + 1]->getState() == WALL) {
                dist = 4;
                break;
            }
            yPac4++;
            break;

        case NONE:
            break;
        }
        dist++;
    }

    // update direction with the shortest path to the 4th square in front of
    // pacman
    updateDirWithShortestPath(vecBoard, xPac4, yPac4);
}

void ghost::updateDirBlue(std::vector<std::vector<square *>> vecBoard, int xPac,
                          int yPac, dir dirPac) {

    updateDirOrange(vecBoard);
    (void)xPac;
    (void)yPac;
    (void)dirPac;
}

void ghost::updateDirOrange(std::vector<std::vector<square *>> vecBoard) {

    // random movement
    bool findPos = false;
    while (findPos == false) {

        int randDir = std::uniform_int_distribution<int>(0, 3)(_rng);

        switch (randDir) {

        case LEFT:
            // avoid going back
            if (_lastDir == RIGHT)
                break;

            // out of the board
            if (_xBoard <= 0 && _yBoard != 13) {
                std::cerr << "Ghost out of the board in updateDir" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (vecBoard[_xBoard - 1][_yBoard]->getState() == HALL) {
                _xBoard--;
                _lastDir = LEFT;
                findPos = true;
            }

            break;

        case RIGHT:
            // avoid going back
            if (_lastDir == LEFT)
                break;

            // out of the board
            if (_xBoard >= 20 && _yBoard != 13) {
                std::cerr << "Ghost out of the board in updateDir" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (vecBoard[_xBoard + 1][_yBoard]->getState() == HALL) {
                _xBoard++;
                _lastDir = RIGHT;
                findPos = true;
            }

            break;

        case UP:
            // avoid going back
            if (_lastDir == DOWN)
                break;

            // out of the board
            if (_yBoard >= 26) {
                std::cerr << "Ghost out of the board in updateDir" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (vecBoard[_xBoard][_yBoard - 1]->getState() == HALL) {
                _yBoard--;
                _lastDir = UP;
                findPos = true;
            }

            break;

        case DOWN:
            // avoid going back
            if (_lastDir == UP)
                break;

            // out of the board
            if (_yBoard <= 0) {
                std::cerr << "Ghost out of the board in updateDir" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (vecBoard[_xBoard][_yBoard + 1]->getState() == HALL) {
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
