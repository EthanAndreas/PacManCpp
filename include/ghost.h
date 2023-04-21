#pragma once

#include "board.h"
#include "debug.h"
#include "graphic.h"

class ghost {
  public:
    ghost();
    ~ghost();
    dir *getLastDir();
    void updatePos();
    std::pair<int, int> getPos();
    void updateDir(board Board);

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
};