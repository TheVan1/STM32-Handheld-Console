#include "game_logic.h"
#include "draw_helpers.h"
#include "game_object.h"
#include "player_gnorp.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include <cstddef>
#include <stdint.h>
#include <vector>



uint8_t player_input_x;
uint8_t player_input_y;


GameObject *gnorping_it;
std::vector<GameObject*> objects;
extern "C" void game_init() {

  std::vector<uint8_t> gnorp_pixels = {2, 0, 4, 0, 1, 1, 2, 1, 3, 1, 4,
                                       1, 0, 2, 0, 3, 0, 4, 3, 4, 5, 4,
                                       0, 5, 1, 6, 2, 6, 3, 6, 4, 6};

  PlayerGnorp *gnorping_it =
      new PlayerGnorp(FLAG_DYNAMIC_OBJECT | FLAG_GRAVITY_ENABLED, gnorp_pixels);

  gnorping_it->velocity_x = 0;
  gnorping_it->velocity_y = 0;

  objects.push_back(gnorping_it);
}

extern "C" void frame_start(uint8_t frame[128][8], uint8_t player_input_x,
                            uint8_t player_input_y, double delta_time) {

   for (GameObject *obj : objects) {

    // obj->Update();

    if ((obj->flags & FLAG_GRAVITY_ENABLED) != 0) {
      obj->velocity_y -= 300 * delta_time;
    }

    // TODO: check for collisions

    if (obj->flags & FLAG_GRAVITY_ENABLED && obj->y <= 0 &&
        obj->velocity_y <= 0) {
      obj->velocity_y = 0;
      obj->y = 0;
    }

    obj->x += obj->velocity_x * delta_time;
    obj->y += obj->velocity_y * delta_time;

    // Drawing stuff goes here
    draw_sprite(frame, obj->x, obj->y, obj->pixels, obj->pixel_count);
  }
}

void destroy_object(GameObject *object) {
  for (uint16_t i = 0; i < objects.size(); i++) {
    if (objects[i] == object) {
      // objects[i]->FreeMemory();
      objects.erase(objects.begin() + i);
    }
  }
}

uint8_t get_inputs(uint8_t axis){
  if(axis == 0) return player_input_x;
  if(axis == 1) return player_input_y;
  return 0;
}