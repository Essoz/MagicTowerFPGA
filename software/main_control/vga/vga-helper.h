#ifndef _VGA_H_
#define _VGA_H_

#include "system.h"
#include <stdint.h>
#include "../resources/english_font.h"
#include "../resources/chinese.h"
#include "../dma/memcpy_dma.h"
#define FB_WIDTH 640
#define FB_HEIGHT 480
#define FB_BASE ((volatile uint8_t*) SRAM_DUAL_CONTROLLER_0_BASE) //TODO: double-check this
// #define FB_BASE ((volatile uint8_t*) 0x400000)

#define UTF8_3BYTE_MASK 0xe0
#define UTF8_2BYTE_MASK 0xc0
#define UTF8_MASK 0x80

#define UTF8_DATA_4BITS 0x0f
#define UTF8_DATA_5BITS 0x1f
#define UTF8_DATA_6BITS 0x3f



void fb_set(int x, int y, int width, int height, const uint8_t* src);

uint16_t utf8_to_code(const uint8_t* c);
uint16_t utf8_len(const uint8_t* c);

// support scaling
void fb_test();
void fb_char_en(int x, int y, int scaling, int color, uint8_t ch);
void fb_char_zh(int x, int y, int scaling, int color, uint8_t* ch);
void fb_string (int x, int y, int scaling, int color, int linebreak, const uint8_t* string);


#endif
