#include "ghost.h"

ghost::ghost() {
    _xBoard = 0;
    _yBoard = 0;
    _xPixel = 0;
    _yPixel = 0;
    _xPixelEaten = 0;
    _yPixelEaten = 0;
    _lastDir = NONE;
    _mode = ANY;
    _swapMode = 0;
    _chaseMode = false;
    _scatterMode = false;
    _scatterDir = NONE;
    _scatterHouse = false;
    _frightenedMode = false;
    _isReturnHouse = false;
    _isFear = false;
    _isTime = false;
    _isInTunnel = false;
    _blueRed = false;
    _bluePink = false;
}
ghost::~ghost() {}

void ghost::setGhost(color c) {
    _color = c;
    switch (c) {
    case RED:
        _isInHouse = true;
        _xBoard = GHOST_INIT_X;
        _yBoard = GHOST_INIT_Y;
        _xPixel = GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
        _yPixel = GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
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

void ghost::updateInHouse(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, int level,
    int dotCounter, int life, time_t noEatenDotTimer1) {

    time_t noEatenDotTimer2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime =
        noEatenDotTimer2 - noEatenDotTimer1;
    if (elapsedTime.count() >= NO_EATEN_DOT_TIME)
        _isTime = true;

    // wait in ghost house
    switch (_color) {
    case RED:
        if (dotCounter >= RED_GHOST_WAIT_DOT)
            _isTime = true;
        break;
    case PINK:
        if ((life == DEFAULT_LIVES && dotCounter >= PINK_GHOST_WAIT_DOT) ||
            (life < DEFAULT_LIVES &&
             dotCounter >= PINK_GHOST_WAIT_DOT_LESS_LIFE))
            _isTime = true;
        break;
    case BLUE:
        if ((level == 1 && dotCounter >= BLUE_GHOST_WAIT_DOT_LVL1) ||
            (level == 2 && dotCounter >= BLUE_GHOST_WAIT_DOT_LVL2) ||
            (level < DEFAULT_LIVES &&
             dotCounter >= BLUE_GHOST_WAIT_DOT_LESS_LIFE))
            _isTime = true;
        break;
    case ORANGE:
        if ((level == 1 && dotCounter >= ORANGE_GHOST_WAIT_DOT_LVL1) ||
            (level == 2 && dotCounter >= ORANGE_GHOST_WAIT_DOT_LVL2) ||
            (level >= 3 && dotCounter >= ORANGE_GHOST_WAIT_DOT_LVL3) ||
            (level < DEFAULT_LIVES &&
             dotCounter >= ORANGE_GHOST_WAIT_DOT_LESS_LIFE))
            _isTime = true;
        break;
    default:
        break;
    }

    // move in ghost house
    if (_isTime == false) {

        if (_yBoard == 13) {
            if (_yPixel + GHOST_SLOW_SPEED >= _yBoard * SCALE_PIXEL +
                                                  GHOST_CENTER_X -
                                                  GHOST_SLOW_RANGE_CENTER)
                _yPixel = _yBoard * SCALE_PIXEL + GHOST_CENTER_X;
            _lastDir = UP;
            _yBoard -= GHOST_SLOW_SPEED;
        } else if (_yBoard == 12) {
            if (_yPixel + GHOST_SLOW_SPEED <= _yBoard * SCALE_PIXEL +
                                                  GHOST_CENTER_X +
                                                  GHOST_SLOW_RANGE_CENTER)
                _yPixel = _yBoard * SCALE_PIXEL + GHOST_CENTER_X;
            _lastDir = DOWN;
            _yBoard += GHOST_SLOW_SPEED;
        }
    }
    // move out ghost house
    else {
        // if the ghost has left the house
        if (_xBoard == GHOST_INIT_X && _yBoard == GHOST_INIT_Y) {
            // reset pixel position
            _xPixel = GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
            _yPixel = GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
            _mode = ANY;
            _isInHouse = false;
            _lastDir = NONE;
            return;
        }

        // next condition are set only for the 12th line
        if (_yBoard == 13) {
            _yBoard -= GHOST_SLOW_SPEED;
            _lastDir = UP;
            return;
        }

        // in the door
        if (vecBoard[_xBoard][_yBoard]->getState() == DOOR) {
            _yBoard -= GHOST_SLOW_SPEED;
            _lastDir = UP;
            return;
        }
        // at the bottom of the door
        else if (vecBoard[_xBoard][_yBoard - 1]->getState() == DOOR) {
            _yBoard -= GHOST_SLOW_SPEED;
            _lastDir = UP;
            return;
        }
        // at the bottom left of the door
        else if (vecBoard[_xBoard + 1][_yBoard - 1]->getState() == DOOR) {
            _xBoard += GHOST_SLOW_SPEED;
            _lastDir = RIGHT;
            return;
        }
        // at the bottom right of the door
        else if (vecBoard[_xBoard - 1][_yBoard - 1]->getState() == DOOR) {
            _xBoard -= GHOST_SLOW_SPEED;
            _lastDir = LEFT;
            return;
        }
    }
}

void ghost::setReturnHouse() {

    // reset dir
    _lastDir = NONE;
    _isReturnHouse = true;
    _isFear = false;

    // update eaten position
    _xPixelEaten = _xPixel;
    _yPixelEaten = _yPixel;
}

void ghost::returnHouse(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard) {

    _mode = ANY;

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
        _isInHouse = true;

        if (_color == RED) {
            _xBoard = RED_GHOST_INIT_X;
            _yBoard = RED_GHOST_INIT_Y;
            _xPixel = RED_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X;
            _yPixel = RED_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y;
        } else
            setGhost(_color);
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
        if (_xBoard == 10 && _yBoard == 12) {
            _lastDir = DOWN;
            _yBoard++;
            return;
        }
        break;
    case PINK:

        if (_xBoard == 10 && _yBoard == 12) {
            _lastDir = DOWN;
            _yBoard++;
            return;
        }
        break;
    case BLUE:
        if (_xBoard == 10 && _yBoard == 12) {
            _lastDir = LEFT;
            _xBoard--;
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
}

bool ghost::isReturnHouse() { return _isReturnHouse; }

void ghost::setFrightened(bool isFear) {

    if (_isFear == true && isFear == false && _isReturnHouse == false &&
        _isInHouse == false) {

        // reset dir
        _lastDir = NONE;
        _mode = SCATTER;
        _scatterHouse = false;
        modeTimer1 = std::chrono::steady_clock::now();
        _isFear = false;
        return;

    } else if (_isFear == false && isFear == true && _isReturnHouse == false &&
               _isInHouse == false) {

        // reset dir
        _lastDir = NONE;
        _mode = FRIGHTENED;
        _isFear = true;
        // go back when they become frightened
        switch (_lastDir) {
        case LEFT:
            _lastDir = RIGHT;
            break;
        case RIGHT:
            _lastDir = LEFT;
            break;
        case UP:
            _lastDir = DOWN;
            break;
        case DOWN:
            _lastDir = UP;
            break;
        case NONE:
            break;
        }

        updateCoord();
        return;
    }
}

bool ghost::isFrightened() { return _isFear; }

std::pair<size_t, size_t> ghost::getPos() {
    return std::make_pair(_xPixel, _yPixel);
}

std::pair<size_t, size_t> ghost::getEatenPosition() {
    return std::make_pair(_xPixelEaten, _yPixelEaten);
}

void ghost::updatePos() {

    // normal speed
    if (_isFear == false && _isReturnHouse == false && _isInTunnel == false &&
        _isInHouse == false) {
        switch (_lastDir) {
        case LEFT:
            _xPixel -= GHOST_SPEED;
            break;
        case RIGHT:
            _xPixel += GHOST_SPEED;
            break;
        case UP:
            _yPixel -= GHOST_SPEED;
            break;
        case DOWN:
            _yPixel += GHOST_SPEED;
            break;
        case NONE:
            break;
        }
    }
    // speed up the ghost
    else if (_isFear == false && _isReturnHouse == true &&
             _isInTunnel == false && _isInHouse == false) {
        switch (_lastDir) {
        case LEFT:
            _xPixel -= GHOST_RETURN_SPEED;
            break;
        case RIGHT:
            _xPixel += GHOST_RETURN_SPEED;
            break;
        case UP:
            _yPixel -= GHOST_RETURN_SPEED;
            break;
        case DOWN:
            _yPixel += GHOST_RETURN_SPEED;
            break;
        case NONE:
            break;
        }
    }
    // slow down the ghost
    else if ((_isFear == true || _isInTunnel == true || _isInHouse == true) &&
             _isReturnHouse == false) {
        switch (_lastDir) {
        case LEFT:
            _xPixel -= GHOST_SLOW_SPEED;
            break;
        case RIGHT:
            _xPixel += GHOST_SLOW_SPEED;
            break;
        case UP:
            _yPixel -= GHOST_SLOW_SPEED;
            break;
        case DOWN:
            _yPixel += GHOST_SLOW_SPEED;
            break;
        case NONE:
            break;
        }
    }
}

void ghost::updateCoord() {

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

bool ghost::waitSquareCenter() {

    size_t xCenter = _xBoard * SCALE_PIXEL + GHOST_CENTER_X;
    size_t yCenter = _yBoard * SCALE_PIXEL + GHOST_CENTER_Y;

    // normal speed
    size_t speed = GHOST_SPEED, range = GHOST_RANGE_CENTER;

    // return house speed
    if (_isFear == false && _isReturnHouse == true && _isInHouse == false) {

        speed = GHOST_RETURN_SPEED;
        range = GHOST_RETURN_RANGE_CENTER;
    }
    // fear / house / tunnel speed
    else if ((_isFear == true || _isInTunnel == true || _isInHouse == true) &&
             _isReturnHouse == false && _isInHouse == false) {

        speed = GHOST_SLOW_SPEED;
        range = GHOST_SLOW_RANGE_CENTER;
    }
    if (_lastDir == LEFT && _xPixel - speed <= xCenter + range) {
        _xPixel = _xBoard * SCALE_PIXEL + GHOST_CENTER_X;
        return true;
    } else if (_lastDir == RIGHT && _xPixel + speed >= xCenter - range) {
        _xPixel = _xBoard * SCALE_PIXEL + GHOST_CENTER_X;
        return true;
    } else if (_lastDir == UP && _yPixel + speed <= yCenter + range) {
        _yPixel = _yBoard * SCALE_PIXEL + GHOST_CENTER_Y;
        return true;
    } else if (_lastDir == DOWN && _yPixel + speed >= yCenter - range) {
        _yPixel = _yBoard * SCALE_PIXEL + GHOST_CENTER_Y;
        return true;
    } else if (_lastDir == NONE)
        return true;

    return false;
}

dir ghost::getLastDir() { return _lastDir; }

void ghost::updateDir(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
    size_t yPac, dir dirPac, int level, int dotCounter, int life,
    time_t noEatenDotTimer1) {

    if (_xBoard > 20 || _yBoard == 0 || _yBoard >= 26) {
        std::cerr << "Ghost out of the board in updateDir" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (_isReturnHouse == false && _xBoard == xPac && _yBoard == yPac)
        return;

    // if ghost is on the teleportation, take it
    if (_xBoard == 0 && _yBoard == 13 && _lastDir == LEFT) {
        _xBoard = 20;
        _xPixel = 20 * SCALE_PIXEL + GHOST_CENTER_X;
    } else if (_xBoard == 20 && _yBoard == 13 && _lastDir == RIGHT) {
        _xBoard = 0;
        _xPixel = GHOST_CENTER_X;
    }

    // if ghost enters in the teleportation hall, go to the teleportation
    // hall
    if (_xBoard <= 4 && _yBoard == 13 && _lastDir == LEFT) {
        _isInTunnel = true;
        _xBoard--;
        return;
    } else if (_xBoard >= 16 && _yBoard == 13 && _lastDir == RIGHT) {
        _isInTunnel = true;
        _xBoard++;
        return;
    }

    // if ghost takes the teleportation, make him leave the teleportation
    // hall
    // bool inTunnel_ReturnHouse = false;
    if (_xBoard <= 4 && _yBoard == 13 &&
        (_lastDir == RIGHT || _lastDir == NONE)) {
        _isInTunnel = true;
        // go back to house, keep his speed
        if (_isReturnHouse == true) {
            _lastDir = RIGHT;
            _xBoard += GHOST_RETURN_SPEED;
            _isInTunnel = false;
        } else
            _xBoard++;
        return;
    } else if (_xBoard >= 16 && _yBoard == 13 &&
               (_lastDir == LEFT || _lastDir == NONE)) {
        _isInTunnel = true;
        // go back to house, keep his speed
        if (_isReturnHouse == true) {
            _lastDir = LEFT;
            _xBoard -= GHOST_RETURN_SPEED;
            _isInTunnel = false;
        } else
            _xBoard--;
        return;
    }

    _isInTunnel = false;

    // std::cout << "test 3" << std::endl;
    // move in the house
    if (_isInHouse == true) {
        updateInHouse(vecBoard, level, dotCounter, life, noEatenDotTimer1);
        return;
    }

    // return to house
    if (_isReturnHouse == true) {
        returnHouse(vecBoard);
        return;
    }

    // if ghost is in some area, only left-right moves are allowed
    if (_xBoard >= 8 && _xBoard <= 12 && (_yBoard == 10 || _yBoard == 20)) {
        if (_lastDir == LEFT) {
            updateCoord();
            return;
        } else if (_lastDir == RIGHT) {
            updateCoord();
            return;
        }
    }

    // switching mode
    swapMode(level);

    // chase mode
    if (_mode == CHASE) {

        switch (_color) {
        case RED:
            updateDirRed(vecBoard, xPac, yPac);
            break;
        case PINK:
            updateDirPink(vecBoard, xPac, yPac, dirPac);
            break;
        case BLUE:
            updateDirBlue(vecBoard, xPac, yPac, dirPac);
            break;
        case ORANGE:
            updateDirOrange(vecBoard, xPac, yPac);
            break;
        }
    }
    // scatter mode
    else if (_mode == SCATTER) {
        switch (_color) {
        case RED:
            updateDirScatterMode(vecBoard, 19, 1);
            break;
        case PINK:
            updateDirScatterMode(vecBoard, 1, 1);
            break;
        case BLUE:
            updateDirScatterMode(vecBoard, 19, 25);
            break;
        case ORANGE:
            updateDirScatterMode(vecBoard, 1, 25);
            break;
        }
    }
    // frightened mode
    else if (_mode == FRIGHTENED)
        updateDirRunAwayMode(vecBoard);

    else
        _lastDir = NONE;
}

void ghost::updateDirRed(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
    size_t yPac) {

    std::vector<std::shared_ptr<Node>> path;

    if (_lastDir != NONE) {

        // new vecBoard without go back possibility
        std::vector<std::vector<std::shared_ptr<square>>>
            vecBoardWithoutGoBack =
                removeAboutTurn(vecBoard, _lastDir, _xBoard, _yBoard);
        // get the shortest path to pacman
        path = findShortestPath(vecBoardWithoutGoBack, _xBoard, _yBoard, xPac,
                                yPac);
    } else
        path = findShortestPath(vecBoard, _xBoard, _yBoard, xPac, yPac);

    // if a shortest path is found, assign the new direction
    if (path.size() >= 2) {

        _lastDir = findDir(path[0], path[1]);
        updateCoord();
    }

    else {
        std::vector<dir> vecPossibleDir =
            findPossibleDir(vecBoard, _lastDir, LEFT, _xBoard, _yBoard);

        if (vecPossibleDir.size() > 0) {

            _lastDir = vecPossibleDir[std::uniform_int_distribution<size_t>(
                0, vecPossibleDir.size() - 1)(_rng)];
            updateCoord();
        } else
            _lastDir = NONE;
    }
}

void ghost::updateDirPink(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
    size_t yPac, dir dirPac) {

    // get the 4th square in front of pacman
    size_t xPac4 = xPac;
    size_t yPac4 = yPac;

    // if ghost is at a distance less than 4 go on pacman
    if (abs(_xBoard - xPac) + abs(_yBoard - yPac) < 4) {
        updateDirWithShortestPath(vecBoard, xPac, yPac);
        return;
    }

    // find the 4th square in front of pacman
    size_t dist = 0;
    while (dist < 4) {

        switch (dirPac) {
        case LEFT:
            if (xPac4 == 0)
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
            if (yPac4 == 0)
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

    // new vecBoard without go back possibility
    std::vector<std::vector<std::shared_ptr<square>>> newVecBoard =
        removeAboutTurn(vecBoard, _lastDir, _xBoard, _yBoard);

    // update direction with the shortest path to the 4th square in
    // front of pacman
    updateDirWithShortestPath(newVecBoard, xPac4, yPac4);
}

void ghost::updateDirBlue(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
    size_t yPac, dir dirPac) {

    // take red chase mode when leaving the house
    if (_blueRed == false && _bluePink == false) {
        _blueRed = true;
        updateDirRed(vecBoard, xPac, yPac);
        blueTimer1 = std::chrono::steady_clock::now();
        return;
    }
    // red chase mode
    else if (_blueRed == true && _bluePink == false) {
        // check if 20 seconds are spent
        time_t blueTimer2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = blueTimer2 - blueTimer1;

        // if 20 seconds are spent, take pink chase mode
        if (elapsedTime.count() >= BLUE_GHOST_RED_TIME) {
            _blueRed = false;
            _bluePink = true;
            updateDirPink(vecBoard, xPac, yPac, dirPac);
            blueTimer1 = std::chrono::steady_clock::now();
            return;
        }

        // if not, continue red chase mode
        updateDirRed(vecBoard, xPac, yPac);
        return;
    }
    // pink chase mode
    else if (_blueRed == false && _bluePink == true) {
        // check if 12 seconds are spent
        time_t blueTimer2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = blueTimer2 - blueTimer1;

        // if 10 seconds are spent, take red chase mode
        if (elapsedTime.count() >= BLUE_GHOST_PINK_TIME) {
            _bluePink = false;
            _blueRed = true;
            updateDirRed(vecBoard, xPac, yPac);
            blueTimer1 = std::chrono::steady_clock::now();
            return;
        }

        // if not, continue pink chase mode
        updateDirPink(vecBoard, xPac, yPac, dirPac);
        return;
    }

    else {
        std::vector<dir> vecPossibleDir =
            findPossibleDir(vecBoard, _lastDir, LEFT, _xBoard, _yBoard);

        if (vecPossibleDir.size() > 0) {

            _lastDir = vecPossibleDir[std::uniform_int_distribution<size_t>(
                0, vecPossibleDir.size() - 1)(_rng)];
            updateCoord();
        } else
            _lastDir = NONE;
    }
}

void ghost::updateDirOrange(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
    size_t yPac) {

    // if ghost is at a distance greater than 8 go on pacman
    if (abs(_xBoard - xPac) + abs(_yBoard - yPac) > 8) {
        updateDirWithShortestPath(vecBoard, xPac, yPac);
        return;
    }

    // if ghost is at a distance less than 8 go in scatter mode
    else {
        if (_mode != SCATTER) {
            _mode = SCATTER;
            _scatterHouse = false;
            modeTimer1 = std::chrono::steady_clock::now();
        }
        updateDirScatterMode(vecBoard, 1, 25);
        return;
    }
}

void ghost::updateDirScatterMode(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t x,
    size_t y) {

    // when arrive in the house, go back in chase mode
    if (_xBoard == x && _yBoard == y) {
        _scatterHouse = true;
        _scatterDir = _lastDir;
    }

    if (_scatterHouse == true) {
        // top left corner
        if (_color == PINK) {
            // arrive with left direction
            if (_scatterDir == LEFT) {
                if (_lastDir == LEFT) {
                    if (_xBoard == 1 && _yBoard == 1)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 1 && _yBoard == 5)
                        _lastDir = RIGHT;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 5 && _yBoard == 5)
                        _lastDir = UP;
                } else if (_lastDir == UP) {
                    if (_xBoard == 5 && _yBoard == 1)
                        _lastDir = LEFT;
                }
                updateCoord();
                return;

            } else if (_scatterDir == UP) {
                if (_lastDir == UP) {
                    if (_xBoard == 1 && _yBoard == 1)
                        _lastDir = RIGHT;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 5 && _yBoard == 1)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 5 && _yBoard == 5)
                        _lastDir = LEFT;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 1 && _yBoard == 5)
                        _lastDir = UP;
                }
                updateCoord();
                return;
            }
        }
        // top right corner
        else if (_color == RED) {
            // arrive with right direction
            if (_scatterDir == RIGHT) {
                if (_lastDir == RIGHT) {
                    if (_xBoard == 19 && _yBoard == 1)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 19 && _yBoard == 5)
                        _lastDir = LEFT;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 15 && _yBoard == 5)
                        _lastDir = UP;
                } else if (_lastDir == UP) {
                    if (_xBoard == 15 && _yBoard == 1)
                        _lastDir = RIGHT;
                }
                updateCoord();
                return;

            } else if (_scatterDir == UP) {
                if (_lastDir == UP) {
                    if (_xBoard == 19 && _yBoard == 1)
                        _lastDir = LEFT;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 15 && _yBoard == 1)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 15 && _yBoard == 5)
                        _lastDir = RIGHT;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 19 && _yBoard == 5)
                        _lastDir = UP;
                }
                updateCoord();
                return;
            }
        }
        // bottom left corner
        else if (_color == ORANGE) {
            // arrive with left direction
            if (_scatterDir == LEFT) {
                if (_lastDir == LEFT) {
                    if (_xBoard == 1 && _yBoard == 25)
                        _lastDir = UP;
                } else if (_lastDir == UP) {
                    if (_xBoard == 1 && _yBoard == 23)
                        _lastDir = RIGHT;
                    else if (_xBoard == 5 && _yBoard == 20)
                        _lastDir = RIGHT;
                    else if (_xBoard == 9 && _yBoard == 23)
                        _lastDir = DOWN;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 5 && _yBoard == 23)
                        _lastDir = UP;
                    else if (_xBoard == 7 && _yBoard == 20)
                        _lastDir = DOWN;
                    else if (_xBoard == 9 && _yBoard == 23)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 7 && _yBoard == 23)
                        _lastDir = RIGHT;
                    else if (_xBoard == 9 && _yBoard == 25)
                        _lastDir = LEFT;
                }
                updateCoord();
                return;

            } else if (_scatterDir == DOWN) {
                if (_lastDir == DOWN) {
                    if (_xBoard == 1 && _yBoard == 25)
                        _lastDir = RIGHT;
                    else if (_xBoard == 5 && _yBoard == 23)
                        _lastDir = LEFT;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 9 && _yBoard == 25)
                        _lastDir = UP;
                    else if (_xBoard == 7 && _yBoard == 20)
                        _lastDir = LEFT;
                    else if (_xBoard == 5 && _yBoard == 23)
                        _lastDir = LEFT;
                } else if (_lastDir == UP) {
                    if (_xBoard == 9 && _yBoard == 23)
                        _lastDir = LEFT;
                    else if (_xBoard == 7 && _yBoard == 20)
                        _lastDir = LEFT;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 7 && _yBoard == 23)
                        _lastDir = UP;
                    else if (_xBoard == 5 && _yBoard == 20)
                        _lastDir = DOWN;
                    else if (_xBoard == 1 && _yBoard == 23)
                        _lastDir = DOWN;
                }
                updateCoord();
                return;
            }
        }
        // bottom right corner
        else if (_color == BLUE) {
            // arrive with right direction
            if (_scatterDir == RIGHT) {
                if (_lastDir == RIGHT) {
                    if (_xBoard == 19 && _yBoard == 25)
                        _lastDir = UP;
                } else if (_lastDir == UP) {
                    if (_xBoard == 19 && _yBoard == 23)
                        _lastDir = LEFT;
                    else if (_xBoard == 15 && _yBoard == 20)
                        _lastDir = LEFT;
                    else if (_xBoard == 11 && _yBoard == 23)
                        _lastDir = DOWN;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 15 && _yBoard == 23)
                        _lastDir = UP;
                    else if (_xBoard == 13 && _yBoard == 20)
                        _lastDir = DOWN;
                    else if (_xBoard == 11 && _yBoard == 23)
                        _lastDir = DOWN;
                } else if (_lastDir == DOWN) {
                    if (_xBoard == 13 && _yBoard == 23)
                        _lastDir = LEFT;
                    else if (_xBoard == 11 && _yBoard == 25)
                        _lastDir = RIGHT;
                }
                updateCoord();
                return;

            } else if (_scatterDir == DOWN) {
                if (_lastDir == DOWN) {
                    if (_xBoard == 19 && _yBoard == 25)
                        _lastDir = LEFT;
                    else if (_xBoard == 15 && _yBoard == 23)
                        _lastDir = RIGHT;
                } else if (_lastDir == LEFT) {
                    if (_xBoard == 11 && _yBoard == 25)
                        _lastDir = UP;
                    else if (_xBoard == 13 && _yBoard == 20)
                        _lastDir = RIGHT;
                    else if (_xBoard == 15 && _yBoard == 23)
                        _lastDir = RIGHT;
                } else if (_lastDir == UP) {
                    if (_xBoard == 11 && _yBoard == 23)
                        _lastDir = RIGHT;
                    else if (_xBoard == 13 && _yBoard == 20)
                        _lastDir = RIGHT;
                } else if (_lastDir == RIGHT) {
                    if (_xBoard == 13 && _yBoard == 23)
                        _lastDir = UP;
                    else if (_xBoard == 15 && _yBoard == 20)
                        _lastDir = DOWN;
                    else if (_xBoard == 19 && _yBoard == 23)
                        _lastDir = DOWN;
                }
                updateCoord();
                return;
            }
        }
    } else
        updateDirWithShortestPath(vecBoard, x, y);
}

void ghost::updateDirRunAwayMode(
    std::vector<std::vector<std::shared_ptr<square>>> vecBoard) {

    // find all the possible directions with avoiding last direction
    std::vector<dir> vecPossibleDir =
        findPossibleDir(vecBoard, _lastDir, NONE, _xBoard, _yBoard);

    if (vecPossibleDir.size() > 0) {

        // take a random direction among the possible ones
        _lastDir = vecPossibleDir[std::uniform_int_distribution<size_t>(
            0, vecPossibleDir.size() - 1)(_rng)];
        updateCoord();
    }

    else
        _lastDir = NONE;
}

void ghost::swapMode(int level) {

    time_t modeTimer2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = modeTimer2 - modeTimer1;

    if (_mode == ANY) {
        _mode = SCATTER;
        _scatterHouse = false;
        modeTimer1 = std::chrono::steady_clock::now();

    } else if (_mode == CHASE) {

        if ((level == 1 && _swapMode < 4) || (level >= 2 && _swapMode < 3)) {
            if (elapsedTime.count() >= CHASE_MODE) {
                _lastDir = NONE;
                _mode = SCATTER;
                _scatterHouse = false;
                modeTimer1 = std::chrono::steady_clock::now();
            }
        }
    } else if (_mode == SCATTER) {

        if (level == 1) {

            if (elapsedTime.count() >= SCATTER_MODE_1) {
                _lastDir = NONE;
                _scatterHouse = false;
                _mode = CHASE;
                _swapMode++;
                modeTimer1 = std::chrono::steady_clock::now();
            }
        } else if ((level >= 2 && level <= 4) || _color == ORANGE) {

            if ((_swapMode <= 1 && elapsedTime.count() >= SCATTER_MODE_1) ||
                (_swapMode == 2 && elapsedTime.count() >= SCATTER_MODE_2)) {
                _lastDir = NONE;
                _scatterHouse = false;
                _mode = CHASE;
                _swapMode++;
                modeTimer1 = std::chrono::steady_clock::now();
            }
        } else if (level > 4 || _color == ORANGE) {

            if (elapsedTime.count() >= SCATTER_MODE_2) {
                _lastDir = NONE;
                _scatterHouse = false;
                _mode = CHASE;
                _swapMode++;
                modeTimer1 = std::chrono::steady_clock::now();
            }
        }
    }
}