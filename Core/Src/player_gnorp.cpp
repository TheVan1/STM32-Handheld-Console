
#include "player_gnorp.h"
#include "game_object.h"
#include "main.h"
#include <cstdlib>

bool is_jump_charged = false;

void PlayerGnorp::Update() {
  if (nullptr == manager)
    Error_Handler();

  double dtime = manager->get_delta_time();

  velocity_x += -(manager->get_player_input(0) - 128) * dtime;
  // velocity_y += (manager->get_player_input(1) - 128) * dtime;

  if (manager->get_player_input(1) > 170 && is_jump_charged) {
    velocity_y = 50;
    is_jump_charged = false;
  }

  return;
}

void PlayerGnorp::OnCollision(GameObject *colliding_object) {
  if (colliding_object->y < this->y)
    is_jump_charged = true;
}