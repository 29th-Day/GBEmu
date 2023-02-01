#pragma once

#include "common.h"

typedef struct {
    bool start;
    bool select;
    bool a;
    bool b;
    bool up;
    bool down;
    bool left;
    bool right;
} gamepad_state;

gamepad_state *gamepad_get_state();

void gamepad_init();

bool gamepad_button_sel();  // selecting buttons?
bool gamepad_dir_sel();     // selecting directions?

void gamepad_set_sel(u8 value); // set selection

u8 gamepad_get_output();