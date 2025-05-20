/*
    Author: Harsh Narayan Jha

	Example input code taken from https://github.com/devkitPro/3ds-examples/blob/master/input/read-controls/source/main.c
	and https://github.com/devkitPro/3ds-examples/blob/master/graphics/gpu/2d_shapes/source/main.c

	Wouldn't be possible without those examples and the complete devkitpro team
*/

#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "3ds/services/hid.h"
#include "3ds/types.h"

using namespace std;

#define SCREEN_WIDTH     400
#define SCREEN_HEIGHT    240
#define ALPHA_MASK       0xFFFFFF00

#define NUM_STARS        128
#define NUM_COMETS       5

#define COMET_MIN_RADIUS 5
#define COMET_MAX_RADIUS 8

#define COMET_SPEED_MIN  0.1
#define COMET_SPEED_MAX  1.5

class Star {
  private:
    double x, y;
    double radius;
    u32 color;
    u8 alpha;

  public:
    Star(double x, double y, u32 color) : x(x), y(y), color(color) {
        // assign a random radius
        radius = (((double)rand()) / RAND_MAX);

        // assign a random alpha
        alpha = rand() % 255;
        color &= ALPHA_MASK;
        color |= alpha;
    }

    void Draw() { C2D_DrawCircleSolid(x, y, 0, radius, color); }
};

class Comet {
  private:
    double x, y;
    double vx, vy;
    double radius;
    u32 color;

  public:
    unsigned int key;
    static constexpr unsigned int COMET_KEYS[] = {KEY_A,     KEY_B,      KEY_X, KEY_Y, KEY_DUP, KEY_DDOWN,
                                                  KEY_DLEFT, KEY_DRIGHT, KEY_L, KEY_R, KEY_ZL,  KEY_ZR};
    static constexpr u8 NUM_COMET_KEYS = 12;

    Comet(double x, double y, double vx, double vy, double radius, u32 color)
        : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {

        // give this comet a random key
        key = Comet::COMET_KEYS[rand() % Comet::NUM_COMET_KEYS];
    };

    void Draw() { C2D_DrawCircleSolid(x, y, 0, radius, color); }

    void UpdatePosition() {
        x += vx;
        y += vy;
    }

    bool IsOutsideScreen() { return x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0; }

    bool IsBelowScreen() { return y > SCREEN_HEIGHT + radius; }
};

constexpr unsigned int Comet::COMET_KEYS[];
constexpr u8 Comet::NUM_COMET_KEYS;

class GameManager {
  private:
    Star* stars[NUM_STARS];
    vector<Comet*> comets;

    void TrySpawnNewComet() {

        if (comets.size() < NUM_COMETS) {
            // have space, spawn and return;
            if (rand() % 100 > 95) {
                double radius = ((double)rand() / RAND_MAX) * (COMET_MAX_RADIUS - COMET_MIN_RADIUS) + COMET_MIN_RADIUS;

                double x = rand() % SCREEN_WIDTH;
                if (x < radius) {
                    x = radius;
                } else if (x > SCREEN_WIDTH - radius) {
                    x = SCREEN_WIDTH - radius;
                }

                double y = 0 - (double)rand() / RAND_MAX * radius;

                double vy = ((double)rand() / RAND_MAX) * (COMET_SPEED_MAX - COMET_SPEED_MIN) + COMET_SPEED_MIN;

                // printf("Spawning a new comet at %.2lf %.2lf with velocity %.2lf\n", x, y, vy);
                comets.push_back(new Comet(x, y, 0, vy, radius, clrWhite));
            }
            return;
        }

        // full, wait for one to reach end
        for (u8 i = 0; i < comets.size(); i++) {
            if (comets.at(i)->IsBelowScreen()) {
                // remove it
                comets.erase(comets.begin() + i);
            }
        }
        // if became empty, will automatically spawn a new one!
    }

    void DrawStars() {
        for (u8 i = 0; i < NUM_STARS; i++) {
            stars[i]->Draw();
        }
    }

    void DrawComets() {
        for (Comet* comet : comets) {
            if (comet == NULL) {
                continue;
            }

            comet->UpdatePosition();
            comet->Draw();
        }
    }

  public:
    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    u32 clrGray = C2D_Color32(0xE8, 0xE8, 0xE8, 0xFF);
    u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    u32 clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    u32 clrBlue = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

    u32 clrClear = C2D_Color32(0x12, 0x12, 0x12, 0x12);

    GameManager() {
        for (u8 i = 0; i < NUM_STARS; i++) {
            int x = rand() % SCREEN_WIDTH;
            int y = rand() % SCREEN_HEIGHT;
            stars[i] = new Star(x, y, clrGray);
        }
    }

    ~GameManager() {
        for (u8 i = 0; i < NUM_STARS; i++) {
            delete stars[i];
        }

        for (Comet* comet : comets) {
            delete comet;
        }
    }

    void Update() {
        DrawStars();
        TrySpawnNewComet();
        DrawComets();
    }

    void HandleInput(u32 keysDown) {

        // scan all keys
        for (int k = 0; k < Comet::NUM_COMET_KEYS; k++) {
            if (keysDown & Comet::COMET_KEYS[k]) {
                // key is pressed
                // find the comet to delete

                unsigned int key = Comet::COMET_KEYS[k];
                int cometToDelete = -1;
                for (u8 c = 0; c < comets.size(); c++) {
                    if (comets[c] == NULL) {
                        continue;
                    }
                    if (comets[c]->key == key) {
                        cometToDelete = c;
                        break;
                    }
                }

                if (cometToDelete != -1) {
                    comets.erase(comets.begin() + cometToDelete);
                }
            }
        }
    }
};

int main(int argc, char** argv) {

    //Matrix containing the name of each key. Useful for printing when a key is pressed
    char keysNames[32][32] = {"KEY_A",
                              "KEY_B",
                              "KEY_SELECT",
                              "KEY_START",
                              "KEY_DRIGHT",
                              "KEY_DLEFT",
                              "KEY_DUP",
                              "KEY_DDOWN",
                              "KEY_R",
                              "KEY_L",
                              "KEY_X",
                              "KEY_Y",
                              "",
                              "",
                              "KEY_ZL",
                              "KEY_ZR",
                              "",
                              "",
                              "",
                              "",
                              "KEY_TOUCH",
                              "",
                              "",
                              "",
                              "KEY_CSTICK_RIGHT",
                              "KEY_CSTICK_LEFT",
                              "KEY_CSTICK_UP",
                              "KEY_CSTICK_DOWN",
                              "KEY_CPAD_RIGHT",
                              "KEY_CPAD_LEFT",
                              "KEY_CPAD_UP",
                              "KEY_CPAD_DOWN"};

    // Initialize services
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    //Initialize console on bottom screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_BOTTOM, NULL);

    // initialize random seed
    srand(time(0));

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    printf("\x1b[1;1HPress Start to exit.\n");
    printf("\x1b[2;1HWelcome to my 3ds-typer game.\n");
    printf("\x1b[3;1HPress the keys in the comet to destroy them.\n");

    GameManager gm;

    // Main loop
    while (aptMainLoop()) {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u32 kDown = hidKeysDown();
        //hidKeysHeld returns information about which buttons have are held down in this frame
        u32 kHeld = hidKeysHeld();
        //hidKeysUp returns information about which buttons have been just released
        u32 kUp = hidKeysUp();

        if (kDown & KEY_START) {
            break; // break in order to return to hbmenu
        }

        circlePosition pos;
        //Read the CirclePad position
        hidCircleRead(&pos);

        // begin the game
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, gm.clrClear);
        C2D_SceneBegin(top);

        // run the game loop
        gm.Update();
        gm.HandleInput(kDown);

        C3D_FrameEnd(0);

        // Flush and swap framebuffers
        // gfxFlushBuffers();
        // gfxSwapBuffers();

        //Wait for VBlank
        // gspWaitForVBlank();
    }

    // Exit services
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
