#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include <array>

#include <iostream>

void put_pixel(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y,
               uint8_t bit);

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void draw_line(std::array<std::array<uint8_t, 8>, 128> *frame, int x0, int y0, int x1, int y1, uint8_t bit) {
  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = y0 < y1 ? 1 : -1;
  double error = dx + dy;

  while (1) {
    put_pixel(frame, x0, y0, bit);
    double e2 = 2 * error;
    if (e2 >= dy) {
      if (x0 == x1)
        break;
      error = error + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      if (y0 == y1)
        break;
      error = error + dx;
      y0 = y0 + sy;
    }
  }
}

// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void draw_circle(std::array<std::array<uint8_t, 8>, 128> frame, int x, int y, int radius,
                 uint8_t bit) {
  double t1 = (double)(radius) / 16;
  int current_x = radius;
  int current_y = 0;
  while (current_y < current_x) {
    put_pixel(&frame, current_x + x, current_y + y, bit);
    put_pixel(&frame, -current_x + x, current_y + y, bit);
    put_pixel(&frame, -current_x + x, -current_y + y, bit);
    put_pixel(&frame, current_x + x, -current_y + y, bit);

    put_pixel(&frame, current_y + x, current_x + y, bit);
    put_pixel(&frame, -current_y + x, current_x + y, bit);
    put_pixel(&frame, -current_y + x, -current_x + y, bit);
    put_pixel(&frame, current_y + x, -current_x + y, bit);

    current_y = current_y + 1;
    t1 = t1 + current_y;
    double t2 = t1 - current_x;
    if (t2 >= 0) {
      t1 = t2;
      current_x = current_x - 1;
    }
  }
}

/* params:
x1, y1, x2, y2: bounding box vertices
fill: whether it should be a lineart or solid rectangle
*/
void draw_rectangle(std::array<std::array<uint8_t, 8>, 128> *frame, int x0, int y0, int x1,
                    int y1, uint8_t bit) {

  draw_line(frame, x0, y0, x0, y1, bit);
  draw_line(frame, x0, y1, x1, y0, bit);
  draw_line(frame, x1, y0, x1, y1, bit);
  draw_line(frame, x0, y1, x1, y1, bit);
}

void draw_quadrilateral(std::array<std::array<uint8_t, 8>, 128> *frame, int x0, int y0,
                        int x1, int y1, uint8_t x2, int y2,
                        int x3, int y3, uint8_t bit) {
  draw_line(frame, x0, y0, x1, y1, bit);
  draw_line(frame, x0, y0, x2, y2, bit);
  draw_line(frame, x1, y1, x3, y3, bit);
  draw_line(frame, x2, y2, x3, y3, bit);
}

void draw_gnorp(std::array<std::array<uint8_t, 8>, 128> frame, int x, int y, uint8_t bit) {
  put_pixel(&frame, x + 2, y, bit);
  put_pixel(&frame, x + 4, y, bit);

  put_pixel(&frame, x + 1, y + 1, bit);
  put_pixel(&frame, x + 2, y + 1, bit);
  put_pixel(&frame, x + 2, y + 1, bit);
  put_pixel(&frame, x + 3, y + 1, bit);
  put_pixel(&frame, x + 4, y + 1, bit);

  put_pixel(&frame, x, y + 2, bit);

  put_pixel(&frame, x, y + 3, bit);

  put_pixel(&frame, x, y + 4, bit);
  put_pixel(&frame, x + 3, y + 4, bit);
  put_pixel(&frame, x + 5, y + 4, bit);

  put_pixel(&frame, x, y + 5, bit);

  put_pixel(&frame, x + 1, y + 6, bit);
  put_pixel(&frame, x + 2, y + 6, bit);
  put_pixel(&frame, x + 2, y + 6, bit);
  put_pixel(&frame, x + 3, y + 6, bit);
  put_pixel(&frame, x + 4, y + 6, bit);
}

void draw_sprite(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y,
               uint8_t *pixels[2], uint8_t length, uint8_t fill) {

  // iterate over our vector of pixels and place them in the correct place,
  // offset by our position
  for (int i = 0; i < length; i++) {
    if(fill && i < length - 1) draw_line(frame, pixels[0][i] + x, pixels[1][i] + y, pixels[0][i + 1] + x, pixels[1][i + 1] + y, 1);
    put_pixel(frame, pixels[0][i] + x, pixels[1][i] + y, 1);                 
  }
}

// simple function to be able to place a pixel in a 128x64 grid, from the buffer
// pages
void put_pixel(std::array<std::array<uint8_t, 8>, 128> *frame, int x, int y,
               uint8_t bit) {
  // early return if we would write outside of our bounds
  if (y > 63 || x > 127 || x < 0 || y < 0)
    return;
  uint8_t page = y / 8;

  // bit shift our currently placed bit into the correct spot in the page
  (*frame)[x][page] |= bit << (y - (page * 8));
}

void draw_text(uint8_t ** frame, uint8_t x, uint8_t y, char *text) {}