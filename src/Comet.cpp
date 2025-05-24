#include "Comet.hpp"
#include "defines.hpp"

#include <citro2d.h>
#include <stdlib.h> // NOLINT

constexpr u8           Comet::NUM_COMET_KEYS;
constexpr unsigned int Comet::COMET_KEYS[];
constexpr const char*  Comet::COMET_KEYS_CHAR[];

Comet::Comet(double x, double y, double vx, double vy, double radius, u32 color) :
    x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {

    // give this comet a random key
    key = rand() % Comet::NUM_COMET_KEYS;
};

double Comet::getX() {
    return x;
}

double Comet::getY() {
    return y;
}

void Comet::draw() {
    C2D_DrawCircleSolid(x, y, 0, radius, color);
}

void Comet::updatePosition() {
    x += vx;
    y += vy;
}

bool Comet::isOutsideScreen() {
    return x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0;
}

bool Comet::isBelowScreen() {
    return y > SCREEN_HEIGHT + radius;
}
