#include "Comet.hpp"
#include "defines.hpp"

#include <citro2d.h>
#include <stdlib.h> // NOLINT

Comet::Comet(double x, double y, double vx, double vy, double radius, u32 color) :
    x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {

    // give this comet a random key
    key = Comet::COMET_KEYS[rand() % Comet::NUM_COMET_KEYS];
};

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
