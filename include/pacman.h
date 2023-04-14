#pragma once

#include "board.h"
#include "graphic.h"

class pacman {
  public:
    pacman();
    ~pacman();
    dir *getLastDir();
    void updatePos();
    std::pair<int, int> getPos();
    void updateDir(board Board, dir currentDir);

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
};