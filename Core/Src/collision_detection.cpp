
#include "collision_detection.h"
#include "game_object.h"
#include "main.h"
#include <cstdint>
#include <cstdlib>
#include <map>
#include <math.h>
#include <vector>

#define COLLISION_SLOWDOWN 0.3
#define GRID_DIMENSIONS 20

void handle_collision(GameObject *a, GameObject *b, bool effect_triggers);
bool is_colliding(GameObject *a, GameObject *b);
void process_collision(GameObject *a, GameObject *b);

void detect_collisions(std::vector<GameObject *> objects, bool effect_triggers) {

  //loop through our objects, checking every other object for collisions
  while (!objects.empty()) {
    GameObject *obj_one = objects.back();
    std::vector<GameObject *> objects_temp = objects;

    //skip the last item in our temp list, as this is guaranteed to be our current obj_one
    objects_temp.pop_back();

    while(!objects_temp.empty()){

      GameObject *obj_two = objects_temp.back();
      objects_temp.pop_back();

      handle_collision(obj_one, obj_two, effect_triggers);
    }

    objects.pop_back();
  }
}

/*
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
*/

// this is strictly less efficient than doing it all as one incredibly chunky
// function, as we are reusing a lot of variables, however I feel that that is
// worth it, given the increased readability
void handle_collision(GameObject *a, GameObject *b, bool effect_triggers) {
  if (a == b) return;

  uint8_t is_a_dynamic =
      (a->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;
  uint8_t is_b_dynamic =
      (b->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;

  uint8_t dynamic_count = is_a_dynamic + is_b_dynamic;

  // early return if neither of our objects is able to move (are not dynamic
  // objects)
  if (dynamic_count == 0)
    return;

  if(!is_colliding(a, b)) return;
  
  process_collision(a, b);

  if(!effect_triggers) return;

  //make our GameObjects aware of their collisions, so they can do their own processing
  a->OnCollision(b);
  b->OnCollision(a);

}

bool is_colliding(GameObject *a, GameObject *b) {

  double diff_x = abs(a->x - b->x);
  double diff_y = abs(a->y - b->y);
  bool is_a_x_greater = (a->x) > (b->x) ? true : false;
  bool is_a_y_greater = (a->y) > (b->y) ? true : false;

  double shunt_x;
  double shunt_y;

  // detect the distance between the edge of the hitbox and the current position
  // in the hitbox. a negative distance indicates that the boxes are inside one
  // another, whereas a positive indicates that our boxes are too far apart to
  // be touching (effectively a one dimensional SDF)
  if (is_a_x_greater) {
    shunt_x = diff_x - b->hitbox[0];
  } else {
    shunt_x = diff_x - a->hitbox[0];
  }

  // early return if our X axis is large enough for us to not be colliding
  if (shunt_x > 0)
    return false;

  // repeat previous steps for Y axis
  if (is_a_y_greater) {
    shunt_y = diff_y - b->hitbox[1];
  } else {
    shunt_y = diff_y - a->hitbox[1];
  }

  if (shunt_y > 0)
    return false;

  return true;
}

void process_collision(GameObject *a, GameObject *b) {
  uint8_t is_a_dynamic =
      (a->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;
  uint8_t is_b_dynamic =
      (b->flags & FLAG_DYNAMIC_OBJECT) == FLAG_DYNAMIC_OBJECT;

  uint8_t dynamic_count = is_a_dynamic + is_b_dynamic;

  double diff_x = abs(a->x - b->x);
  double diff_y = abs(a->y - b->y);
  bool is_a_x_greater = (a->x) > (b->x) ? true : false;
  bool is_a_y_greater = (a->y) > (b->y) ? true : false;

  double shunt_x;
  double shunt_y;

  if (is_a_x_greater) {
    shunt_x = diff_x - b->hitbox[0];
  } else {
    shunt_x = diff_x - a->hitbox[0];
  }
  if (is_a_y_greater) {
    shunt_y = diff_y - b->hitbox[1];
  } else {
    shunt_y = diff_y - a->hitbox[1];
  }

  shunt_x *= -1;
  shunt_y *= -1;

  // move our objects the respective amount, minimizing the amount moved
  if (shunt_x < shunt_y) {
    double a_shunt_x = (shunt_x / dynamic_count) * is_a_dynamic;
    double b_shunt_x = (shunt_x / dynamic_count) * is_b_dynamic;

    a->velocity_x *= -(1 - COLLISION_SLOWDOWN);
    b->velocity_x *= -(1 - COLLISION_SLOWDOWN);

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

    a->velocity_y *= -(1 - COLLISION_SLOWDOWN);
    b->velocity_y *= -(1 - COLLISION_SLOWDOWN);

    if (is_a_y_greater) {
      a->y += a_shunt_y;
      b->y -= b_shunt_y;
    } else {
      a->y -= a_shunt_y;
      b->y += b_shunt_y;
    }
  }
}