
#include "game_object.h"
#include "collision_detection.h"
#include "main.h"
#include <cstdint>
#include <cstdlib>
#include <map>
#include <math.h>
#include <vector>

#define GRID_DIMENSIONS 20

void handle_collision(GameObject *a, GameObject *b);

void detect_collisions(std::vector<GameObject *> objects) {

  for (GameObject *obj_one : objects) {
    for (GameObject *obj_two : objects) {
      if (obj_one == obj_two)
        continue;
      handle_collision(obj_one, obj_two);
    }
  }
}

void detect_collisions_optimised(std::vector<GameObject *> objects) {

  // this key is actually 2 signed 16 bit integers, for the X and Y axis
  std::map<uint32_t, std::vector<GameObject *> *> grid;

  // ------- Optimisation Stage -------
  for (GameObject *object : objects) {

    uint16_t x_pos = (int)std::ceil(object->x) / GRID_DIMENSIONS;
    uint16_t y_pos = (int)std::ceil(object->y) / GRID_DIMENSIONS;

    uint32_t key = (x_pos << 16) | y_pos;

    if (grid.find(key) == grid.end()) {
      std::vector<GameObject *> *vec = new std::vector<GameObject *>;
      vec->push_back(object);
      grid[key] = vec;
    } else {
      grid[key]->push_back(object);
    }
  }

  // ------- Detection Stage -------

  // 1. Select a grid square to analyse
  // 2. Get the last object in that grid vector annd store it as obj_one
  // 3. Pop that off the vector
  // 4. Iterate over all of the remaining objects in the vector, checking for
  // collisions
  // 5. repeat 2-4 until the vector is empty
  // 6. repeat 1-5 until the grid has been iterated over

  for (auto const &[key, val] : grid) {
    if (val->empty())
      Error_Handler();

    while (!val->empty()) {

      GameObject *obj_one = *(val->end());
      val->pop_back();

      for (GameObject *obj_two : *val) {
        // we don't care if two objects collide if they are both static, so we
        // can skip that
        if ((obj_one->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT ||
            (obj_two->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT) {
          handle_collision(obj_one, obj_two);
        }
      }
    }
  }
}

// TODO: Fix **all** of this
void handle_collision(GameObject *a, GameObject *b) {
  double diff_x = abs(a->x - b->x);
  double diff_y = abs(a->y - b->y);
  uint8_t is_a_x_greater = a->x > b->x ? 1 : 0;
  uint8_t is_a_y_greater = a->y > b->y ? 1 : 0;

  double shunt_x;
  double shunt_y;

  if (is_a_x_greater) {
    shunt_x = diff_x - a->hitbox[0];
  } else {
    shunt_x = diff_x - b->hitbox[0];
  }

  if (shunt_x <= 0)
    return;

  if (is_a_y_greater) {
    shunt_y = diff_y - a->hitbox[1];
  } else {
    shunt_y = diff_y - b->hitbox[1];
  }

  if (shunt_y <= 0)
    return;

  uint8_t is_a_dynamic =
      (a->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;
  uint8_t is_b_dynamic =
      (b->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;
  uint8_t dynamic_count = is_a_dynamic + is_b_dynamic;

  // move our objects the respective amount, minimizing the amount moved
  if (shunt_x < shunt_y) {
    double a_shunt_x = (shunt_x / dynamic_count) * is_a_dynamic;
    double b_shunt_x = (shunt_x / dynamic_count) * is_b_dynamic;

    a->velocity_x = 0;
    b->velocity_x = 0;
    if (is_a_x_greater) {
      a->x += a_shunt_x;
      b->x -= b_shunt_x;
    } else {
      a->x -= a_shunt_x;
      b->x += b_shunt_x;
    }
  } else {
    double a_shunt_y = (shunt_y / dynamic_count) * is_a_dynamic;
    double b_shunt_y = (shunt_y / dynamic_count) * is_b_dynamic;

    a->velocity_y = 0;
    b->velocity_y = 0;
    if (is_a_y_greater) {
      a->y += a_shunt_y;
      b->y -= b_shunt_y;
    } else {
      a->y -= a_shunt_y;
      b->y += b_shunt_y;
    }
  }
}