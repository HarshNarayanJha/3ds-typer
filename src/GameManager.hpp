#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

#include "Star.hpp"
#include "Comet.hpp"

#define NUM_STARS  128
#define NUM_COMETS 5

#define COMET_MIN_RADIUS 5
#define COMET_MAX_RADIUS 8

#define COMET_SPEED_MIN 0.1
#define COMET_SPEED_MAX 1.5

class GameManager {
  private:
    // renderer
    C3D_RenderTarget* top;

    // game entities
    Star*               stars[NUM_STARS];
    std::vector<Comet*> comets;

    void trySpawnNewComet();
    void drawStars();
    void drawComets();

  public:
    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    u32 clrGray  = C2D_Color32(0xE8, 0xE8, 0xE8, 0xFF);
    u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

    u32 clrClear = C2D_Color32(0x12, 0x12, 0x12, 0x12);

    GameManager();
    ~GameManager();
    void Init();
    void beginDraw();
    void update();
    void handleInput(u32 keysDown);
    void deInit();
};
