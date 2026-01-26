#ifndef INC_GAME_MANAGER_H
#define INC_GAME_MANAGER_H

#include "stm32f4xx_hal.h"
#include <cstdint>
#include <array>
#include <vector>

class GameManager {
    private:
        uint8_t player_inputs[2];
        double delta_time;


    public:
        GameManager(){}
        std::array<std::array<uint8_t, 8>, 128> frame_buffer;
        double get_delta_time();
        uint8_t get_player_input();


};
#endif