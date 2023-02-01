#pragma once

#include "common.h"

#define DLLEXPORT __declspec(dllexport)

typedef struct {
    bool paused;
    bool running;
    u64 ticks;
} emu_context;

typedef struct {
    struct {
        unsigned char a : 4;
        unsigned char b : 4;
    } member;
} test;

emu_context *emu_get_context();

int emu_run(int argc, char *argv[]);

void emu_cycles(int cpu_cycles);

DLLEXPORT void emu_init(char *rom_path);
DLLEXPORT void emu_frame(u8 *frame, u8 input);