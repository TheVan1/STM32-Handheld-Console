/*
 * ssd_1306_drivers.h
 *
 *  Created on: 16 Dec 2025
 *      Author: Vanessa
 */

#ifndef INC_DRAW_HELPERS_H
#define INC_DRAW_HELPERS_H



#include <stdint.h>
void put_pixel(uint8_t SSD1306_FrameBufferPages[128][8], int x, int y, uint8_t bit);
void draw_line(uint8_t frame[128][8], int x0, int y0, int x1, int y1, uint8_t bit);
void draw_circle(uint8_t frame[128][8], int x, int y, uint8_t radius, uint8_t bit);
void draw_rectangle(uint8_t frame[128][8], int x0, uint8_t y0, int x1, int y1, uint8_t bit);
void draw_gnorp(uint8_t frame[128][8], int x, int y, uint8_t bit);
void draw_text(uint8_t frame[128][8], int x, int y, char* text, uint8_t bit);
void draw_sprite(uint8_t SSD1306_FrameBufferPages[128][8], int x, int y,
               uint8_t *pixels[2], uint8_t length);

#endif 
