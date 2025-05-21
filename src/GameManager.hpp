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

    /** @brief Initializes the GameManager. Needs to be called at the beginning of game Once.
     *  @remarks Initializes rendering engines, console, srand and text buffers
     */
    void Init();

    /** @brief Prepares drawing functions by clearing buffers
     *  @remarks This needs to be called at the start of each frame, before drawing anything on the screen
     */
    void beginDraw();

    /** @brief Main game loop. Needs to be called each frame
     *  @remarks Calls private methods to draw things to the screen. Call this after `beginDraw()`
     */
    void update();

    /** @brief Handles input to update game state. Needs to be called each frame
     *  @param[in] keysDown Keys pressed this frame.
     *  @remarks This needs to be done only once in the program if citro2d is the sole user of the GPU.
     */
    void handleInput(u32 keysDown);

    /** @brief Deinitializes the GameManager. Needs to be called at the end of game for cleanup Once.
     *  @remarks Deinitializes rendering engines, console, srand and text buffers
     */
    void deInit();
};
