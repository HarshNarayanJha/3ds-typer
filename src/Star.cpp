#include "Star.hpp"

#include <citro2d.h>
#include <stdlib.h> // NOLINT

#define ALPHA_MASK 0xFFFFFF00

Star::Star(double x, double y, u32 color) : x(x), y(y), color(color) {
    // assign a random radius
    radius = (((double)rand()) / RAND_MAX);

    // assign a random alpha
    alpha = rand() % 255;
    color &= ALPHA_MASK;
    color |= alpha;
}

void Star::draw() {
    C2D_DrawCircleSolid(x, y, 0, radius, color);
}
