#include "vga-helper.h"




void fb_set(int x, int y, int width, int height, const uint8_t* src) {
	int y_max = y + height;
//	int x_max = x + width;
	for(int dy = y; dy < y_max; dy++) {
		uint8_t* vga_ptr = ((uint8_t*) FB_BASE) + dy * FB_WIDTH;
//		const uint16_t* src_ptr = src + (dy-y) * width;
//		for(int dx = x; dx < x_max; dx++) {
//			vga_ptr[dx] = src[(dy-y) * width + dx-x];
//		}
		memcpy_dma(vga_ptr + x, src + (dy-y) * width, width * sizeof(uint8_t));
	}
}
//from https://lantian.pub/en/article/modify-computer/cyclone-iv-fpga-development-bugs-resolve.lantian/
uint16_t utf8_to_code(const uint8_t* c) {
	if(!((*c) & UTF8_MASK)) return *c;

    if(UTF8_3BYTE_MASK == ((*c) & UTF8_3BYTE_MASK)) {
        // Detected the beginning of a 3 byte UTF-8 code
    	return (((*c) & UTF8_DATA_4BITS) << 12)
    			| (((*(c+1)) & UTF8_DATA_6BITS) << 6)
				| ((*(c+2)) & UTF8_DATA_6BITS);
    } else if(UTF8_2BYTE_MASK == ((*(c+1)) & UTF8_2BYTE_MASK)) {
        // Detected the beginning of a 2 byte UTF-8 code
    	return (((*c) & UTF8_DATA_5BITS) << 6)
    			| ((*(c+1)) & UTF8_DATA_6BITS);
    } else {
    	return *c;
    }
}

uint16_t utf8_len(const uint8_t* c) {
	if(!((*c) & UTF8_MASK)) return 1;

    if(UTF8_3BYTE_MASK == ((*c) & UTF8_3BYTE_MASK)) {
        // Detected the beginning of a 3 byte UTF-8 code
    	return 3;
    } else if(UTF8_2BYTE_MASK == ((*(c+1)) & UTF8_2BYTE_MASK)) {
        // Detected the beginning of a 2 byte UTF-8 code
    	return 2;
    } else {
    	return 1;
    }
}

void fb_char_en(int x, int y, int scaling, int color, uint8_t ch){
    volatile uint8_t* relPos;
    uint8_t  font_data;
    for (int dy = 0; dy < 16; dy++){
        font_data = font_data_en[ch][dy];
        for (int dx = 0; dx < 8; dx++){
            for (int j = 0; j < scaling; j++){
                for (int i = 0; i < scaling; i++){
                    relPos = FB_BASE + (y + dy * scaling + j) * FB_WIDTH + x + dx * scaling + i;
                    if (font_data & (1 << (7 - dx))) {
                        if (color == 0)  // black
                            *relPos = 5;
                        else            // white 
                            *relPos = 15;
                    }
                }
            }
        }
    }
}

void fb_char_zh(int x, int y, int scaling, int color, uint8_t* ch){
    volatile uint8_t* relPos;
    uint16_t  font_data;
    int idx;

    uint16_t code = utf8_to_code(ch);
    
	if(code >= CHINESE_ENCODE_START && code <= CHINESE_ENCODE_END) {
		for(int dy = 0; dy < 16; dy++) {
			idx = ((code - CHINESE_ENCODE_START) * 16 + dy) * 2;
			font_data = (((uint16_t) font_data_zh[idx]) << 8) | font_data_zh[idx+1];
			for(int dx = 0; dx < 16; dx++) {
                for (int j = 0; j < scaling; j++){
                    for (int i = 0; i < scaling; i++){
                        relPos = (FB_BASE) + (y + dy * scaling + j) * FB_WIDTH + x + dx * scaling + i;
                        if(font_data & (1 << (15 - dx))) {
                            if (color == 0)  // black
                                *relPos = 5;
                            else            // white 
                                *relPos = 15;
                        }
                    }
                }
            }
        }
    }
}
void fb_string (int x, int y, int scaling, int color, int linebreak, const uint8_t* string){
    const uint8_t* ptr = string;
	int pos_x = 0, pos_y = 0;
	while(*ptr) {
		if(*ptr == '\n') {
			pos_y++;
			pos_x = 0;
			ptr += 1;
			continue;
        }
		uint16_t len = utf8_len(ptr);
		if(len > 1) {       // chinese
			if(x + (pos_x * 8 + 16) * scaling >= linebreak) {      // can set linebreak = FB_WIDTH
				pos_y++;
				pos_x = 0;
			}
			fb_char_zh(x + pos_x * 8 * scaling, y + pos_y * 16 * scaling, scaling, color, ptr);
			pos_x += 2;
		} else {            // english
			if(x + (pos_x * 8 + 8) * scaling >= linebreak) {
				pos_y++;
				pos_x = 0;
			}
			fb_char_en(x + pos_x * 8 * scaling, y + pos_y * 16 * scaling, scaling, color, *ptr);
			pos_x += 1;
		}
		ptr += len;
	}
}

void fb_test() {
	for (int y = 0; y <= 479; y++) {
		for (int x = 0; x <= 639; x++) {
			FB_BASE[y * 640 + x] = 0; // transparent
		}
	}
}