
#include <cstdint>
#include <vector>

uint8_t player_inputs[2];
double delta_time;

double get_delta_time(){
    return delta_time;
}
uint8_t get_player_input(uint8_t axis){
    if(axis > 2) return 0;
    return player_inputs[axis];
}