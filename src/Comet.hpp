#pragma once

#include <3ds.h>

class Comet {
  private:
    double x, y;
    double vx, vy;
    double radius;
    u32    color;

  public:
    unsigned int key;

    static constexpr unsigned int COMET_KEYS[] = {
        KEY_A, KEY_B, KEY_X, KEY_Y, KEY_DUP, KEY_DDOWN, KEY_DLEFT, KEY_DRIGHT, KEY_L, KEY_R, KEY_ZL, KEY_ZR,
    };
    static constexpr u8 NUM_COMET_KEYS = 12;

    Comet(double x, double y, double vx, double vy, double radius, u32 color);
    void draw();
    void updatePosition();
    bool isOutsideScreen();
    bool isBelowScreen();
};
