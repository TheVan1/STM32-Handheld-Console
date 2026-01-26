
#ifndef INC_GAME_LOGIC
#define INC_GAME_LOGIC

#include "main.h"

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#pragma once
#ifdef __cplusplus
#
#include <cstdint>
extern "C" {
#endif

void game_init(TIM_HandleTypeDef* timer, ADC_HandleTypeDef *adc);
 void frame_update();

#ifdef __cplusplus
}
#endif

#endif /* INC_GAME_LOGIC_H_ */

#endif /* GAME_LOGIC_H */