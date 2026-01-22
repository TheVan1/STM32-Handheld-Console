#ifndef INC_GAME_LOGIC
#define INC_GAME_LOGIC


#include <cstdint>

extern "C" 
void game_init();

extern "C" 
void frame_start(uint8_t frame[128][8], uint8_t player_input_x, uint8_t player_input_y, double delta_time);

void delta_time();

uint8_t get_inputs(uint8_t axis);

#endif /* INC_GAME_LOGIC_H_ */