#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <stdint.h>
#include <vector>

#include "stm32f4xx_hal.h"
#include "collision_detection.h"
#include "game_logic.h"
#include "draw_helpers.h"
#include "game_manager.h"
#include "game_object.h"
#include "main.h"
#include "player_gnorp.h"
#include "ssd_1306.h"

#define DISPLAY_X_SIZE 128
#define DISPLAY_Y_SIZE 64

std::vector<GameObject *> objects;
std::array<std::array<uint8_t, 8>, 128> frame;

extern "C" void game_init(TIM_HandleTypeDef *timer, ADC_HandleTypeDef *adc) {

  uint32_t adc_data[2] = {0};
  HAL_ADC_Start_DMA(adc, adc_data, 2);

  GameManager *manager = new GameManager();
  manager->frame_buffer = frame;
  manager->player_inputs = adc_data;

  std::vector<uint8_t> gnorp_pixels = {2, 0, 4, 0, 1, 1, 2, 1, 3, 1, 4,
                                       1, 0, 2, 0, 3, 0, 4, 3, 4, 5, 4,
                                       0, 5, 1, 6, 2, 6, 3, 6, 4, 6};
  PlayerGnorp *player =
      new PlayerGnorp(FLAG_DYNAMIC_OBJECT | FLAG_GRAVITY_ENABLED, gnorp_pixels, manager);

  objects.push_back(player);


  std::vector<uint8_t> vertical_box_pixels = {0, 0, 1, 128};
  std::vector<uint8_t> horizontal_box_pixels = {0, 0, 128, 1};

  GameObject *box_one = new GameObject(0, vertical_box_pixels, manager);
  GameObject *box_two = new GameObject(0, vertical_box_pixels, manager);
  box_one->x = 2;
  box_one->y = 0;
  box_two->x = 126;
  box_two->y = 0;



  GameObject *box_three = new GameObject(0, horizontal_box_pixels, manager);
  GameObject *box_four = new GameObject(0, horizontal_box_pixels, manager);
  box_three->y = 2;
  box_three->x = 0;
  box_four->y = 62;
  box_four->x = 0;

  objects.push_back(box_one);
  objects.push_back(box_two);
  objects.push_back(box_three);
  objects.push_back(box_four);


  

  while (1) {
    /*------------Frame Preparation------------*/
    HAL_TIM_Base_Stop(timer);

    // the time the last frame took to run, in seconds
    double delta_time = (double)(TIM3->CNT) / 1000000;
    if (nullptr != manager)
      manager->set_delta_time(delta_time);
    else
      Error_Handler();
    TIM3->CNT = 0;

    HAL_TIM_Base_Start(timer);

    // wipe the frame buffer at the start of each frame
    memset(&manager->frame_buffer, 0, sizeof(uint8_t) * 1024);

    /*--------Frame Drawing and Tick Logic--------*/
    for (GameObject *object : objects) {
      object->Update();

      // if ((object->flags |= (FLAG_GRAVITY_ENABLED & FLAG_DYNAMIC_OBJECT)))
      //   object->velocity_y -= 400 * delta_time;

      object->x += object->velocity_x * delta_time;
      object->y += object->velocity_y * delta_time;

      // if (object->x >= 128 && object->velocity_x > 0) {
      //   object->velocity_x *= -0.4;
      //   object->x = 128;
      // }

      // if (object->x <= 0 && object->velocity_x < 0) {
      //   object->velocity_x *= -0.4;
      //   object->x = 0;
      // }

      // if (object->y >= 64 && object->velocity_y > 0) {
      //   object->velocity_y *= -0.4;
      //   object->y = 64;
      // }

      // if (object->y <= 0 && object->velocity_y < 0) {
      //   object->velocity_y *= -0.8;
      //   object->y = 0;
      // }

      object->velocity_x *= 0.999 * (1 - delta_time);
      object->velocity_y *= 0.999 * (1 - delta_time);

      draw_sprite(&manager->frame_buffer, object->x, object->y, object->pixels,
                  object->pixel_count);

      
      
    }

    detect_collisions(objects);

    /*-------------Frame Finalisation-------------*/

    /*
    after our temporary frame is created, we need to copy our temp buffer to the
    frame buffer used by the HAL_TIM_PeriodElapsedCallback IRQn

    this is *technically* not fully interrupt safe, as we could theoretically
    have the interrupt fire during this memcpy, **however**, this is
    simulaneouly unlikely and low-stakes as memcpy takes very little time, and
    if the IQRn does fire, we still show a valid frame which is partways updated

    without this fix, we get flickery behaviour, and with it I have noticed no
    artifacts or issues
    */

    std::copy(manager->frame_buffer.begin(), manager->frame_buffer.end(),
              frame.begin());

              if (HAL_ADC_Start_DMA(adc, adc_data, 2) != HAL_OK) {
        /* Start Error */
        Error_Handler();
      }
  }
}

extern "C" void frame_update() { I2C_SSD1306_Update_Whole_Display(frame); }