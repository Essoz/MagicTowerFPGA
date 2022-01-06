#include "cover_draw.h"

void draw_cover() {
    fb_set(0, 0, 640, 480, cover);
    // title
    fb_string(320 - 56 * 4, 80, 4, 0, 640, "MAGIC    TOWER");
    
    // appendix
    fb_string(0, 480 - 16 * 1, 1, 1, 640, "FPGA Beta Ver 1.0");
    fb_string(0, 480 - 48 * 1, 1, 1, 640, "Yuxuan Jiang & Tianyu Zhang");
    fb_string(0, 480 - 32 * 1, 1, 1, 640, "UIUC ECE 385 Final Project");
}

void draw_gameover() {
    fb_set(0, 0, 640, 480, gameover);
}

void draw_gameover_slow() {
    for (int i = 0; i < 640*480; i++) {
        FB_BASE[i] = gameover[i];
    }
}
