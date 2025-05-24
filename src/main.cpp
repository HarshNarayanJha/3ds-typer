/*
    Author: Harsh Narayan Jha

	Example input code taken from https://github.com/devkitPro/3ds-examples/blob/master/input/read-controls/source/main.c
	and https://github.com/devkitPro/3ds-examples/blob/master/graphics/gpu/2d_shapes/source/main.c

	Wouldn't be possible without those examples and the complete devkitpro team
*/

#include <3ds.h>
#include <citro2d.h>

#include "GameManager.hpp"

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

    GameManager gm;

    // Initialize
    gm.Init();

    printf("\x1b[1;1HPress Start to exit.\n");
    printf("\x1b[2;1HWelcome to my 3ds-typer game.\n");
    printf("\x1b[3;1HPress the keys in the comet to destroy them.\n");

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

        // begin drawing
        gm.beginDraw();

        // run the game loop
        gm.handleInput(kDown);
        gm.update();

        C3D_FrameEnd(0);

        //Wait for VBlank (for 30fps)
        // gspWaitForVBlank();
    }

    // Deinitialize
    gm.deInit();

    return 0;
}
