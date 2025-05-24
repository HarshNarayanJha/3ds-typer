#pragma once

#include <3ds.h>
#include <citro2d.h>
#include "sprites.hpp"

class Comet {
  private:
    double x, y;
    double vx, vy;
    double radius;
    u32    color;

  public:
    /** @brief index of the key that is comet is made up of
     *  @remarks index from Comet::COMET_KEYS
     */
    unsigned int key;
    C2D_Sprite   sprite;

    static constexpr u8 NUM_COMET_KEYS = 12;

    static constexpr unsigned int COMET_KEYS[NUM_COMET_KEYS] = {
        KEY_A,     KEY_B,      KEY_X, KEY_Y, KEY_DUP, KEY_DDOWN,
        KEY_DLEFT, KEY_DRIGHT, KEY_L, KEY_R, KEY_ZL,  KEY_ZR,
    };
    static constexpr const char* COMET_KEYS_CHAR[NUM_COMET_KEYS] = {
        "A", "B", "X", "Y", "UP", "DOWN", "LEFT", "RIGHT", "L", "R", "ZL", "ZR"};
    static constexpr const u8 COMET_KEYS_SPRITES[NUM_COMET_KEYS] = {
        sprites_button_a_idx,     sprites_button_b_idx,      sprites_button_x_idx,
        sprites_button_y_idx,     sprites_button_dup_idx,    sprites_button_ddown_idx,
        sprites_button_dleft_idx, sprites_button_dright_idx, sprites_button_l_idx,
        sprites_button_r_idx,     sprites_button_zl_idx,     sprites_button_zr_idx};

    Comet(double x, double y, double vx, double vy, double radius, u32 color);

    void initSprite();

    double getX();
    double getY();

    void draw();
    void updatePosition();
    bool isOutsideScreen();
    bool isBelowScreen();
};
