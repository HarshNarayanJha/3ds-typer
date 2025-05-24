#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

#include "Star.hpp"
#include "Comet.hpp"

#define NUM_STARS   128
#define NUM_COMETS  5
#define MAX_SPRITES 100

#define COMET_MIN_RADIUS 1
#define COMET_MAX_RADIUS 1.8

#define COMET_SPEED_MIN 0.1
#define COMET_SPEED_MAX 1.5

class GameManager {
  private:
    // renderer
    C3D_RenderTarget* top;
    C2D_TextBuf       staticBuf, dynamicBuf;
    C2D_Font          font;

    C2D_SpriteSheet spriteSheet;

    // game entities
    Star*               stars[NUM_STARS];
    std::vector<Comet*> comets;

    /** @brief Allocates various resources needed by the GameManager
     *  @remarks They are deallocated in the deallocateResources() method
     */
    void allocateResources();

    /** @brief Tries to spawn a new comet, if possible
     *  @remarks controlled by how many are already on screen, and if a comet is near the screen bottom ready to be deallocated
     */
    void trySpawnNewComet();

    /** @brief called every frame to draw each of the stars
     *  @remarks called in the public method update()
     */
    void drawStars();

    /** @brief called every frame to draw each of the comets
     *  @remarks called in the public method update()
     */
    void drawComets();

    /** @brief called every frame to draw text
     *  @remarks called in the public method update()
     */
    void drawText();

    /** @brief Deallocates every resource allocated in allocateResources()
     *  @remarks automatically called in the GameManager destructor
     */
    void deallocateResources();

  public:
    // Color definitions
    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
    u32 clrGray  = C2D_Color32(0xE8, 0xE8, 0xE8, 0xFF);
    u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

    u32 clrClear = C2D_Color32(0x12, 0x12, 0x12, 0x12);

    GameManager();
    ~GameManager();

    /** @brief Loads sprite sheet and initializes sprite data
     *  @param[in] spriteSheetPath to load the sheet from
     *  @remarks Call before Init(). Spritesheet is unloaded in deInit
    */
    void LoadSpriteSheet(const char* spriteSheetPath);

    /** @brief Initializes the GameManager. Needs to be called at the beginning of game Once.
     *  @remarks Initializes rendering engines, console, srand.
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
     *  @remarks Deinitializes rendering engines, console, srand.
     */
    void deInit();
};
