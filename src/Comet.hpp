#pragma once

#include <3ds.h>

class Comet {
  private:
    double x, y;
    double vx, vy;
    double radius;
    u32    color;

  public:
    /** @brief index of the key that is comet is made up of
     *  @remarks index from Comet::COMET_KEYS
     */
    unsigned int key;

    static constexpr u8 NUM_COMET_KEYS = 12;

    static constexpr unsigned int COMET_KEYS[NUM_COMET_KEYS] = {
        KEY_A,     KEY_B,      KEY_X, KEY_Y, KEY_DUP, KEY_DDOWN,
        KEY_DLEFT, KEY_DRIGHT, KEY_L, KEY_R, KEY_ZL,  KEY_ZR,
    };
    static constexpr const char* COMET_KEYS_CHAR[NUM_COMET_KEYS] = {
        "A", "B", "X", "Y", "UP", "DOWN", "LEFT", "RIGHT", "L", "R", "ZL", "ZR"};

    Comet(double x, double y, double vx, double vy, double radius, u32 color);

    double getX();
    double getY();

    void draw();
    void updatePosition();
    bool isOutsideScreen();
    bool isBelowScreen();
};
