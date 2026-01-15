#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>

void put_pixel(uint8_t SSD1306_FrameBufferPages[128][8], uint8_t x, uint8_t y,
               uint8_t bit);

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void draw_line(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1,
               uint8_t y1) {
  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = y0 < y1 ? 1 : -1;
  double error = dx + dy;

  while (1) {
    put_pixel(frame, x0, y0, 1);
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
void draw_circle(uint8_t frame[128][8], uint8_t x, uint8_t y, uint8_t radius,
                 uint8_t bit) {
  double t1 = (double)(radius) / 16;
  uint8_t current_x = radius;
  uint8_t current_y = 0;
  while (current_y < current_x) {
    put_pixel(frame, current_x + x, current_y + y, bit);
    put_pixel(frame, -current_x + x, current_y + y, bit);
    put_pixel(frame, -current_x + x, -current_y + y, bit);
    put_pixel(frame, current_x + x, -current_y + y, bit);

    put_pixel(frame, current_y + x, current_x + y, bit);
    put_pixel(frame, -current_y + x, current_x + y, bit);
    put_pixel(frame, -current_y + x, -current_x + y, bit);
    put_pixel(frame, current_y + x, -current_x + y, bit);

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
void draw_rectangle(uint8_t frame[128][8], uint8_t x0, uint8_t y0, uint8_t x1,
                    uint8_t y1, uint8_t fill) {
  if (fill == 0) {
    draw_line(frame, x0, y0, x0, y1);
    draw_line(frame, x0, y1, x1, y0);
    draw_line(frame, x1, y0, x1, y1);
    draw_line(frame, x0, y1, x1, y1);
  }
}

void draw_quadrilateral(uint8_t frame[128][8], uint8_t x0, uint8_t y0,
                        uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
                        uint8_t x3, uint8_t y3, uint8_t fill) {
  if (fill == 0) {
    draw_line(frame, x0, y0, x1, y1);
    draw_line(frame, x0, y0, x2, y2);
    draw_line(frame, x1, y1, x3, y3);
    draw_line(frame, x2, y2, x3, y3);
  }
}

void draw_gnorp(uint8_t frame[128][8], uint8_t x, uint8_t y, uint8_t bit) {
  put_pixel(frame, x + 2, y, bit);
  put_pixel(frame, x + 4, y, bit);

  put_pixel(frame, x + 1, y + 1, bit);
  put_pixel(frame, x + 2, y + 1, bit);
  put_pixel(frame, x + 2, y + 1, bit);
  put_pixel(frame, x + 3, y + 1, bit);
  put_pixel(frame, x + 4, y + 1, bit);

  put_pixel(frame, x, y + 2, bit);

  put_pixel(frame, x, y + 3, bit);

  put_pixel(frame, x, y + 4, bit);
  put_pixel(frame, x + 3, y + 4, bit);
  put_pixel(frame, x + 5, y + 4, bit);

  put_pixel(frame, x, y + 5, bit);

  put_pixel(frame, x + 1, y + 6, bit);
  put_pixel(frame, x + 2, y + 6, bit);
  put_pixel(frame, x + 2, y + 6, bit);
  put_pixel(frame, x + 3, y + 6, bit);
  put_pixel(frame, x + 4, y + 6, bit);
}

// simple function to be able to place a pixel in a 128x64 grid, from the buffer
// pages
void put_pixel(uint8_t SSD1306_FrameBufferPages[128][8], uint8_t x, uint8_t y,
               uint8_t bit) {
  uint8_t page = y / 8;

  // early return if we would write outside of our bounds
  if (page > 7 || x > 127)
    return;

  // bit shift our currently placed bit into the correct spot in the page
  SSD1306_FrameBufferPages[x][page] |= bit << (y - (page * 8));
}