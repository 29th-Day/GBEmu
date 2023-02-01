#include "gamepad.h"

// #include <string.h>

typedef struct {
    bool action;
    bool direction;
    gamepad_state controller;
} gamepad_context;

static gamepad_context ctx = {0};

gamepad_state *gamepad_get_state() {
    return &ctx.controller;
}

void gamepad_set_state(u8 value) {
    u8 *state = (u8 *)&ctx.controller;
    *state = value;
}

// bool gamepad_button_sel() {
//     return ctx.button_sel;
// }

// bool gamepad_dir_sel() {
//     return ctx.dir_sel;
// }

void gamepad_set_mode(u8 value) {
    ctx.action = value & 0x20;      // bit 5
    ctx.direction = value & 0x10;   // bit 4
}

u8 gamepad_get_output() {
    u8 output = 0xCF; // 1100 1111

    if (!ctx.action) {
        if (gamepad_get_state()->a) {
            output &= ~(1 << 0);
        }
        if (gamepad_get_state()->b) {
            output &= ~(1 << 1);
        }
        if (gamepad_get_state()->select) {
            output &= ~(1 << 2);
        }
        if (gamepad_get_state()->start) {
            output &= ~(1 << 3);
        }
    }

    if (!ctx.direction) {
        if (gamepad_get_state()->right) {
            output &= ~(1 << 0);
        }
        if (gamepad_get_state()->left) {
            output &= ~(1 << 1);
        }
        if (gamepad_get_state()->up) {
            output &= ~(1 << 2);
        }
        if (gamepad_get_state()->down) {
            output &= ~(1 << 3);
        }
    }

    return output;
}