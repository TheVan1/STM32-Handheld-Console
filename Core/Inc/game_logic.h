#ifndef INC_GAME_LOGIC
#define INC_GAME_LOGIC

#include <cstdint>

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void frame_start(uint8_t frame[128][8], uint8_t player_input_x,
                 uint8_t player_input_y, double delta_time);
void game_init();

#ifdef __cplusplus
}
#endif
void delta_time();

uint8_t get_inputs(uint8_t axis);

#endif /* INC_GAME_LOGIC_H_ */

#endif /* GAME_LOGIC_H */