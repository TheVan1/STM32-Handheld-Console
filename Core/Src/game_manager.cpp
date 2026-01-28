
#include <cstdint>
#include <vector>
#include <game_manager.h>




uint8_t GameManager::get_player_input(uint8_t axis){
    if(axis > 2) return 0;
    return player_inputs[axis];
}
void GameManager::set_delta_time(double delta_time){
    this->delta_time = delta_time;
}

double GameManager::get_delta_time(){
    return this->delta_time;
}

