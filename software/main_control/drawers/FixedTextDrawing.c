#include "FixedTextDrawing.h"


void draw_table(){
    fb_string(64, 40, 1, 1, 640, "状态正常");

    fb_string(32 + 4,64+4, 1, 1, 640, "等级");   // TODO: Set 1
    fb_string(32 + 4,89+4, 1, 1, 640, "体力");
    fb_string(32 + 4,114+4, 1, 1, 640, "攻击");
    fb_string(32 + 4,139+4, 1, 1, 640, "防御");
    fb_string(32 + 4,164+4, 1, 1, 640, "经验值");

    fb_string(48, 189, 1, 1, 640, "气息");

}
void draw_press_l(){
    fb_string(32*14, 32 * 12, 2, 1, 32 * 18, "Press-L");
}

void draw_floor_text(){

    fb_string(11*32, 8, 1, 0, 640, "主塔");
    fb_string(13*32, 10, 1, 0, 640, "F");

}

void draw_floor_num(int cur_floor){
    fb_char_en(13*32 - 8, 10, 1, 0, cur_floor + 48 + 1);
}

void draw_all_text(int cur_floor){
    draw_erase();
    draw_table();
    draw_press_l();
    draw_floor_text();
    draw_floor_num(cur_floor);

}