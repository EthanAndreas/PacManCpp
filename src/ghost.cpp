#include "ghost.h"

ghost::ghost() {
    _xBoard = 10;
    _yBoard = 12;
    _xPixel = 322;
    _yPixel = 386;
    _lastDir = NONE;
    srand(time(NULL));
}
ghost::~ghost() {}

dir *ghost::getLastDir() { return &_lastDir; }

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

void ghost::updateDir(board Board) {

    // each square is 32x32 pixels
    // wait until ghost reaches the middle of the next square
    if ((_xPixel % 32) != 2 || (_yPixel % 32) != 2)
        return;

    std::vector<std::vector<square>> vecBoard = Board.getBoard();

    DEB(std::cout << "Ghost" << std::endl;);

    DEB(std::cout << "current dir : " << _lastDir << std::endl);

    DEB(std::cout << "xBoard: " << _xBoard << " yBoard: " << _yBoard
                  << std::endl);
    DEB(std::cout << "xPixel: " << _xPixel << " yPixel: " << _yPixel
                  << std::endl);

    DEB(std::cout << "board state: " << std::endl;);
    DEB(std::cout << vecBoard[_yBoard - 1][_xBoard - 1].getState() << " "
                  << vecBoard[_yBoard - 1][_xBoard].getState() << " "
                  << vecBoard[_yBoard - 1][_xBoard + 1].getState()
                  << std::endl);
    DEB(std::cout << vecBoard[_yBoard][_xBoard - 1].getState() << " "
                  << vecBoard[_yBoard][_xBoard].getState() << " "
                  << vecBoard[_yBoard][_xBoard + 1].getState() << std::endl)
    DEB(std::cout << vecBoard[_yBoard + 1][_xBoard - 1].getState() << " "
                  << vecBoard[_yBoard + 1][_xBoard].getState() << " "
                  << vecBoard[_yBoard + 1][_xBoard + 1].getState()
                  << std::endl);

    bool findPos = false;
    while (findPos == false) {

        if (vecBoard[_xBoard][_yBoard - 1].getState() == 3) {
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

            DEB(std::cout << "current dir LEFT & last dir : " << randDir
                          << std::endl);
            break;

        case RIGHT:

            // avoid going back
            if (_lastDir == LEFT)
                break;

            // avoid teleporation hall
            if (_xBoard + 1 == 24 && _yBoard == 13)
                break;

            if (vecBoard[_xBoard + 1][_yBoard].getState() == 0) {
                _xBoard++;
                _lastDir = RIGHT;
                findPos = true;
            }

            DEB(std::cout << "current dir RIGHT & last dir : " << randDir
                          << std::endl);
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

            DEB(std::cout << "current dir UP & last dir : " << randDir
                          << std::endl);
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

            DEB(std::cout << "current dir DOWN & last dir : " << randDir
                          << std::endl);
            break;

        case NONE:
            break;
        }
    }
}
