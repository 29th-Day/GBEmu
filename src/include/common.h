#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t  u8;    // 1 byte, max: 0xFF
typedef uint16_t u16;   // 2 bytes, max: 0xFFFF
typedef uint32_t u32;   // 4 bytes
typedef uint64_t u64;   // 8 bytes

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)

#define BIT_SET(a, n, on) (on ? (a |= (1 << n)) : (a &= ~(1 << n)))

#define BETWEEN(n, min, max) ((n >= min) && (n <= max))

#define COMBINE(hi, lo) ((hi << 8) | lo)

#define NO_IMPL { fprintf(stderr, "NOT YET IMPLEMENTED\n"); exit(-5); }