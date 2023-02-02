#pragma once

#include "common.h"

#define DLLEXPORT __declspec(dllexport)

typedef struct {
    bool paused;
    bool running;
    u64 ticks;
} emu_context;

void emu_cycles(int cpu_cycles);

DLLEXPORT void emu_init(char *rom_path, u8 *video_buffer);
DLLEXPORT void emu_frame(u8 input);
DLLEXPORT void emu_stop();