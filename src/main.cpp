/*
    Author: Harsh Narayan Jha

	Example input code taken from https://github.com/devkitPro/3ds-examples/blob/master/input/read-controls/source/main.c
	and https://github.com/devkitPro/3ds-examples/blob/master/graphics/gpu/2d_shapes/source/main.c

	Wouldn't be possible without those examples and the complete devkitpro team
*/

#include <3ds.h>
#include <citro2d.h>
#include <stdlib.h> // NOLINT
#include <cstdio>

#include "Comet.hpp"
#include "GameManager.hpp"

using namespace std;

constexpr unsigned int Comet::COMET_KEYS[];
constexpr u8           Comet::NUM_COMET_KEYS;

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
    consoleInit(GFX_BOTTOM, nullptr);

    // initialize random seed
    srand(time(nullptr));

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
        // u32 kHeld = hidKeysHeld();
        //hidKeysUp returns information about which buttons have been just released
        // u32 kUp = hidKeysUp();

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
        gm.update();
        gm.handleInput(kDown);

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
