#include "common.h"
#include "emu.h"
#include "cart.h"
#include "cpu.h"
#include "timer.h"
#include "dma.h"
#include "ppu.h"

#include "gamepad.h"

#include "lcd.h"


/* 
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/

static emu_context ctx;

static u32 prev_frame = 0;

emu_context *emu_get_context() {
    return &ctx;
}

int emu_run(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    timer_init();
    cpu_init();
    ppu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while(ctx.running) {
        if (ctx.paused) {
            continue;
        }

        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return 0;
        }
    }

    return 0;
}

void emu_cycles(int cpu_cycles) {

    for (int i = 0; i < cpu_cycles; i++) {
        for (int n = 0; n < 4; n++) {
            ctx.ticks++;
            timer_tick();
            ppu_tick();
        }

        dma_tick();
    }
}

DLLEXPORT void emu_init(char *rom_path) {
    if (!cart_load(rom_path)) {
        printf("Failed to load ROM file: %s\n", rom_path);
        // return -2;
        exit(-1);
    }

    printf("Cart loaded..\n");

    timer_init();
    cpu_init();
    ppu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    printf("size: %zu", sizeof(test));
}

DLLEXPORT void emu_frame(u8 *frame, bool input) {

    if (input) {
        gamepad_get_state()->select = 0;
    } else {
        gamepad_get_state()->select = 1;
    }

    while (prev_frame == ppu_get_context()->current_frame) {
        if (!cpu_step()) {
            printf("CPU Stopped\n");
        }
    }

    prev_frame = ppu_get_context()->current_frame;
    
    // frame = ppu_get_context()->video_buffer;

    for (int i = 0; i < 23040; i++) {
        frame[i] = (u8)(ppu_get_context()->video_buffer[i] >> 6);
    }
}