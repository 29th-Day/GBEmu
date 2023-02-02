#include "common.h"
#include "emu.h"
#include "cart.h"
#include "cpu.h"
#include "timer.h"
#include "dma.h"
#include "ppu.h"
#include "gamepad.h"
#include "lcd.h"

static emu_context ctx;

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

DLLEXPORT void emu_init(char *rom_path, u8 *video_buffer) {
    if (!cart_load(rom_path)) {
        printf("Failed to load ROM file: %s\n", rom_path);
        // return -2;
        exit(-1);
    }

    printf("Cart loaded..\n");

    timer_init();
    cpu_init();
    ppu_init(video_buffer);

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;
}

DLLEXPORT void emu_frame(u8 input) {
    gamepad_set_state(input);

    u32 prev_frame = ppu_get_context()->current_frame;

    while (prev_frame == ppu_get_context()->current_frame) {
        if (!cpu_step()) {
            printf("CPU Stopped\n");
        }
    }
}

DLLEXPORT void emu_stop() {
    cart_free();
}