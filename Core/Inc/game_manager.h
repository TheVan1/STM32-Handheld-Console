#ifndef INC_GAME_MANAGER_H
#define INC_GAME_MANAGER_H

#include "stm32f4xx_hal.h"
#include <array>
#include <cstdint>
#include <vector>

#endif

#ifndef __GAME_MANAGER_H
#define __GAME_MANAGER_H

class GameManager {
    private:
    uint8_t player_inputs[2];
    double delta_time;

    
    public:

        GameManager() {}
        std::array<std::array<uint8_t, 8>, 128> frame_buffer;
        virtual uint8_t get_player_input(uint8_t axis);
        virtual void set_delta_time(double delta_time);
        virtual double get_delta_time();

    
};
#endif