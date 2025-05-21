#include "GameManager.hpp"
#include "defines.hpp"

#include <citro2d.h>
#include <stdlib.h> // NOLINT

GameManager::GameManager() {
    for (u8 i = 0; i < NUM_STARS; i++) {
        int x    = rand() % SCREEN_WIDTH;
        int y    = rand() % SCREEN_HEIGHT;
        stars[i] = new Star(x, y, clrGray);
    }
}

GameManager::~GameManager() {
    for (u8 i = 0; i < NUM_STARS; i++) {
        delete stars[i];
    }

    for (Comet* comet : comets) {
        delete comet;
    }
}

void GameManager::Init() {
    // initialize graphics
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    //Initialize console on bottom screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_BOTTOM, nullptr);

    // initialize random seed
    srand(time(nullptr));

    // create top screen rendering target
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
}

void GameManager::beginDraw() {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(top, clrClear);
    C2D_SceneBegin(top);
}

void GameManager::update() {
    drawStars();
    trySpawnNewComet();
    drawComets();
}

void GameManager::handleInput(u32 keysDown) {
    // scan all keys
    for (int k = 0; k < Comet::NUM_COMET_KEYS; k++) {
        if (keysDown & Comet::COMET_KEYS[k]) {
            // key is pressed
            // find the comet to delete
            unsigned int key = Comet::COMET_KEYS[k];

            int cometToDelete = -1;
            for (u8 c = 0; c < static_cast<u8>(comets.size()); c++) {
                if (comets[c] == nullptr) {
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

void GameManager::deInit() {
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

void GameManager::trySpawnNewComet() {

    if (comets.size() < NUM_COMETS) {
        // have space, spawn and return;
        if (rand() % 100 > 95) {
            double radius = (((double)rand() / RAND_MAX) * (COMET_MAX_RADIUS - COMET_MIN_RADIUS)) + COMET_MIN_RADIUS;

            double x = rand() % SCREEN_WIDTH;
            if (x < radius) {
                x = radius;
            } else if (x > SCREEN_WIDTH - radius) {
                x = SCREEN_WIDTH - radius;
            }

            double y = 0 - ((double)rand() / RAND_MAX * radius);

            double vy = (((double)rand() / RAND_MAX) * (COMET_SPEED_MAX - COMET_SPEED_MIN)) + COMET_SPEED_MIN;

            // printf("Spawning a new comet at %.2lf %.2lf with velocity %.2lf\n", x, y, vy);
            comets.push_back(new Comet(x, y, 0, vy, radius, clrWhite));
        }
        return;
    }

    // full, wait for one to reach end
    for (u8 i = 0; i < static_cast<u8>(comets.size()); i++) {
        if (comets.at(i)->isBelowScreen()) {
            // remove it
            comets.erase(comets.begin() + i);
        }
    }
    // if became empty, will automatically spawn a new one!
}

void GameManager::drawStars() {
    for (u8 i = 0; i < NUM_STARS; i++) {
        stars[i]->draw();
    }
}

void GameManager::drawComets() {
    for (Comet* comet : comets) {
        if (comet == nullptr) {
            continue;
        }

        comet->updatePosition();
        comet->draw();
    }
}
