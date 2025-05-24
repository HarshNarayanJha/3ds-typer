#include "GameManager.hpp"
#include "Comet.hpp"
#include "defines.hpp"

#include <citro2d.h>
#include <stdlib.h> // NOLINT

/* constructor */
GameManager::GameManager() {
    allocateResources();
}

/* destructor */
GameManager::~GameManager() {
    deallocateResources();
}

/* Private Methods */

void GameManager::allocateResources() {
    // create stars
    for (u8 i = 0; i < NUM_STARS; i++) {
        int x    = rand() % SCREEN_WIDTH;
        int y    = rand() % SCREEN_HEIGHT;
        stars[i] = new Star(x, y, clrGray);
    }

    // allocate text memory
    staticBuf  = C2D_TextBufNew(4096); // up to 4096 glyphs in the buffer
    dynamicBuf = C2D_TextBufNew(4096);
    font       = C2D_FontLoadSystem(CFG_REGION_USA);
}

void GameManager::trySpawnNewComet() {

    if (comets.size() < NUM_COMETS) {
        // have space, spawn and return;
        if (rand() % 100 > 95) {
            double radius = (((double)rand() / RAND_MAX) * (COMET_MAX_RADIUS - COMET_MIN_RADIUS)) +
                COMET_MIN_RADIUS;

            double x = rand() % SCREEN_WIDTH;
            if (x < radius) {
                x = radius;
            } else if (x > SCREEN_WIDTH - radius) {
                x = SCREEN_WIDTH - radius;
            }

            double y = 0 - ((double)rand() / RAND_MAX * radius);

            double vy = (((double)rand() / RAND_MAX) * (COMET_SPEED_MAX - COMET_SPEED_MIN)) +
                COMET_SPEED_MIN;

            // printf("Spawning a new comet at %.2lf %.2lf with velocity %.2lf\n", x, y, vy);
            Comet* new_comet = new Comet(x, y, 0, vy, radius, clrWhite);
            C2D_SpriteFromSheet(&new_comet->sprite, spriteSheet,
                                Comet::COMET_KEYS_SPRITES[new_comet->key]);
            new_comet->initSprite();

            comets.push_back(new_comet);
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

// Unused right now
void GameManager::drawText() {
    for (Comet* comet : comets) {
        if (comet == nullptr)
            continue;

        char     buf[3];
        C2D_Text text;

        snprintf(buf, sizeof(buf), "%s", Comet::COMET_KEYS_CHAR[comet->key]);
        C2D_TextFontParse(&text, font, dynamicBuf, buf);
        C2D_TextOptimize(&text);
        C2D_DrawText(&text, C2D_AlignCenter | C2D_WithColor, comet->getX() + 1, comet->getY() - 2,
                     0.0f, 0.4f, 0.4f, clrBlack);
    }
}

void GameManager::deallocateResources() {
    // delete all the stars
    for (u8 i = 0; i < NUM_STARS; i++) {
        delete stars[i];
    }

    // delete any allocated comets
    for (Comet* comet : comets) {
        delete comet;
    }

    // free text memory
    C2D_FontFree(font);
    C2D_TextBufDelete(staticBuf);
    C2D_TextBufDelete(dynamicBuf);
}

/* Public methods */

void GameManager::LoadSpriteSheet(const char* spriteSheetPath) {
    spriteSheet = C2D_SpriteSheetLoad(spriteSheetPath);
    if (!spriteSheet)
        svcBreak(USERBREAK_PANIC);
}

void GameManager::Init() {
    // initialize file system
    romfsInit();
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

    // clear dynamic text buffer
    C2D_TextBufClear(dynamicBuf);
}

void GameManager::update() {
    drawStars();
    trySpawnNewComet();
    drawComets();
    // drawText();
}

void GameManager::handleInput(u32 keysDown) {
    // scan all keys
    for (unsigned int k = 0; k < Comet::NUM_COMET_KEYS; k++) {
        if (keysDown & Comet::COMET_KEYS[k]) {
            // key is pressed
            int cometToDelete = -1;
            for (u8 c = 0; c < static_cast<u8>(comets.size()); c++) {
                if (comets[c] == nullptr) {
                    continue;
                }
                if (comets[c]->key == k) {
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
    // free the sprite sheet
    C2D_SpriteSheetFree(spriteSheet);

    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();
}
