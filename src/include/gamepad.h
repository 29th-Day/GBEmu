#pragma once

// https://gbdev.io/pandocs/Joypad_Input.html

#include "common.h"

typedef struct {
    unsigned char right : 1;
    unsigned char left : 1;
    unsigned char down : 1;
    unsigned char up : 1;
    unsigned char b : 1;
    unsigned char a : 1;
    unsigned char select : 1;
    unsigned char start : 1;
} gamepad_state;

gamepad_state *gamepad_get_state();
void gamepad_set_state(u8 value);

void gamepad_set_mode(u8 value);

u8 gamepad_get_output();