/*
 * ssd_1306_drivers.h
 *
 *  Created on: 16 Dec 2025
 *      Author: Vanessa
 */

#ifndef INC_DRAW_HELPERS_H
#define INC_DRAW_HELPERS_H

#include <array>
#include <stdint.h>

void put_pixel(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y, uint8_t bit);
void draw_line(std::array<std::array<uint8_t, 8>, 128> *frame, int x0, int y0, int x1, int y1, uint8_t bit);
void draw_circle(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y, uint8_t radius, uint8_t bit);
void draw_rectangle(std::array<std::array<uint8_t, 8>, 128> *frame, int x0, uint8_t y0, int x1, int y1, uint8_t bit);
void draw_gnorp(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y, uint8_t bit);
void draw_text(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y, char* text, uint8_t bit);
void draw_sprite(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y,
               uint8_t *pixels[2], uint8_t length);

#endif 
