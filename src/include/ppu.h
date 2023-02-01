#pragma once

#include "common.h"

static const unsigned int LINES_PER_FRAME = 154;
static const unsigned int TICKS_PER_LINE = 456;
static const unsigned int YRES = 144;
static const unsigned int XRES = 160;

#define BYTE(i, n) (i >> (8*n) & 0xff)

typedef enum {
    FS_TILE,
    FS_DATA0,
    FS_DATA1,
    FS_IDLE,
    FS_PUSH
} fetch_state;

typedef struct _fifo_entry {
    struct _fifo_entry *next;
    u32 value; // 32 bit color
} fifo_entry;

typedef struct {
    fifo_entry *head;
    fifo_entry *tail;
    u32 size;
} fifo;

typedef struct {
    fetch_state cur_fetch_state;
    fifo pixel_fifo;
    u8 line_x;
    u8 pushed_x;
    u8 fetch_x;
    u8 bgw_fetch_data[3];
    u8 fetch_entry_data[6]; // oam data
    u8 map_y;
    u8 map_x;
    u8 tile_y;
    u8 fifo_x;
} pixel_fifo_context;

typedef struct {
    u8 y;
    u8 x;
    u8 tile;
    
    // 1 byte
    unsigned char f_cgb_pn : 3;          // 3 bits
    unsigned char f_cbg_vram_bank : 1;   // 1 bit
    unsigned char f_pn : 1;              // 1 bit
    unsigned char f_x_flip : 1;          // 1 bit
    unsigned char f_y_flip : 1;          // 1 bit
    unsigned char f_bgp : 1;             // 1 bit

    // u8 flags;

    // struct {
    //     unsigned cgb_pn : 3;
    //     unsigned cbg_vram_bank : 1;
    //     unsigned pn : 1;
    //     unsigned x_flip : 1;
    //     unsigned y_flip : 1;
    //     unsigned bgp : 1;
    // } flags;
} oam_entry;

typedef struct _oam_line_entry {
    oam_entry entry;
    struct _oam_line_entry *next;
} oam_line_entry;

typedef struct {
    oam_entry oam_ram[40];
    u8 vram[0x2000];

    pixel_fifo_context pfc;

    u8 line_sprite_count;
    oam_line_entry *line_sprites;
    oam_line_entry line_entry_array[10];

    u8 fetched_entry_count;
    oam_entry fetched_entries[3];
    u8 window_line;

    u32 current_frame;
    u32 line_ticks;
    u32 *video_buffer;
} ppu_context;

ppu_context *ppu_get_context();

void ppu_init();
void ppu_tick();

void ppu_oam_write(u16 address, u8 value);
u8 ppu_oam_read(u16 address);

void ppu_vram_write(u16 address, u8 value);
u8 ppu_vram_read(u16 address);

void ppu_mode_oam();
void ppu_mode_xfer();
void ppu_mode_hblank();
void ppu_mode_vblank();

void pipeline_process();
void pipeline_fifo_reset();

bool window_visible();