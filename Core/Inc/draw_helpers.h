/*
 * ssd_1306_drivers.h
 *
 *  Created on: 16 Dec 2025
 *      Author: Vanessa
 */

#ifndef INC_DRAW_HELPERS_H
#define INC_DRAW_HELPERS_H



void put_pixel(uint8_t SSD1306_FrameBufferPages[128][8], uint8_t x, uint8_t y, uint8_t bit);
void draw_line(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void draw_circle(uint8_t frame[128][8], uint8_t x, uint8_t y, uint8_t radius, uint8_t fill);
void draw_ellipse(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t fill);
void draw_rectangle(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t fill);
void draw_quadrilateral(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t fill);
void draw_gnorp(uint8_t frame[128][8], uint8_t x, uint8_t y, uint8_t bit);

#endif 
