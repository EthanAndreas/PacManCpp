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
    void updateDir(std::vector<std::vector<square>> vecBoard);
    dir getDir();
    void updateSquare(std::vector<std::vector<square>> vecBoard);

  private:
    int _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
};