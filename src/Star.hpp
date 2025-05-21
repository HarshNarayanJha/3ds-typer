#pragma once

#include <3ds.h>

class Star {
  private:
    double x, y;
    double radius;
    u32    color;
    u8     alpha;

  public:
    Star(double x, double y, u32 color);
    void draw();
};
