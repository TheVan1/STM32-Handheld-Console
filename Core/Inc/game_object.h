#ifndef INC_GAME_OBJECT
#define INC_GAME_OBJECT

#include "game_manager.h"
#include <stdint.h>
#include <string.h>
#include <vector>

#define FLAG_DYNAMIC_OBJECT 0b00000010
#define FLAG_GRAVITY_ENABLED 0b00000001

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
class GameObject {
public:
  // position vars
  double x;
  double y;

  double velocity_x;
  double velocity_y;

  // flags are:
  //  dynamic object : 0, static object : 1
  //  gravity enabled : 0, disabled : 1
  uint8_t flags;

  //assuming a rectangular hitbox for now, originating from 0, 0
  uint8_t hitbox[2];

  uint8_t pivot_point[2];
  uint8_t *pixels[2];
  uint8_t pixel_count;


  GameObject(uint8_t flags, std::vector<uint8_t> pixels);

  GameManager* manager;

  virtual void Update(){}
};


#endif /* GAME_OBJECT_H */
#endif /* INC_GAME_OBJECT_H_ */