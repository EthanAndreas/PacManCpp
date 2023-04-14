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

void pacman::updateDir(board Board, dir currentDir) {

    // each square is 32x32 pixels
    // wait until pacman reaches the middle of the next square
    if ((_xPixel % 32) != 6 || (_yPixel % 32) != 4)
        return;

    std::vector<std::vector<square>> vBoard = Board.getBoard();

    std::cout << "xBoard: " << _xBoard << " yBoard: " << _yBoard << std::endl;
    std::cout << "xPixel: " << _xPixel << " yPixel: " << _yPixel << std::endl;

    // std::cout << vBoard[_yBoard - 1][_xBoard - 1].getState() << " "
    //           << vBoard[_yBoard - 1][_xBoard].getState() << " "
    //           << vBoard[_yBoard - 1][_xBoard + 1].getState() << std::endl;
    // std::cout << vBoard[_yBoard][_xBoard - 1].getState() << " "
    //           << vBoard[_yBoard][_xBoard].getState() << " "
    //           << vBoard[_yBoard][_xBoard + 1].getState() << std::endl;
    // std::cout << vBoard[_yBoard + 1][_xBoard - 1].getState() << " "
    //           << vBoard[_yBoard + 1][_xBoard].getState() << " "
    //           << vBoard[_yBoard + 1][_xBoard + 1].getState() << std::endl;

    switch (currentDir) {

    case LEFT:
        if (_xBoard <= 0)
            _lastDir = NONE;
        if (vBoard[_yBoard][_xBoard - 1].getState() == 0) {
            _xBoard--;
            _lastDir = LEFT;
        } else if (vBoard[_yBoard][_xBoard - 1].getState() == 2) {
            _xBoard = 20;
            _xPixel = 646;
        } else {
            _lastDir = NONE;
        }
        std::cout << "current dir LEFT && last dir : " << currentDir
                  << std::endl;
        break;

    case RIGHT:
        if (_xBoard >= 21)
            _lastDir = NONE;
        if (vBoard[_yBoard][_xBoard + 1].getState() == 0) {
            _xBoard++;
            _lastDir = RIGHT;
        } else if (vBoard[_yBoard][_xBoard + 1].getState() == 2) {
            _xBoard = 0;
            _xPixel = 6;
        } else {
            _lastDir = NONE;
        }
        std::cout << "current dir RIGHT && last dir : " << currentDir
                  << std::endl;
        break;

    case UP:
        if (_yBoard >= 26)
            _lastDir = NONE;
        if (vBoard[_yBoard - 1][_xBoard].getState() == 0) {
            _yBoard--;
            _lastDir = UP;
        } else {
            _lastDir = NONE;
        }
        std::cout << "current dir UP && last dir : " << currentDir << std::endl;
        break;

    case DOWN:
        if (_yBoard <= 0)
            _lastDir = NONE;
        if (vBoard[_yBoard + 1][_xBoard].getState() == 0) {
            _yBoard++;
            _lastDir = DOWN;
        } else {
            _lastDir = NONE;
        }
        std::cout << "current dir DOWN && last dir : " << currentDir
                  << std::endl;
        break;

    case NONE:
        break;
    }
}