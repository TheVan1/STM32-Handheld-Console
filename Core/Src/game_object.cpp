#include "game_object.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <stdint.h>
#include <string.h>

GameObject::GameObject(uint8_t flags, std::vector<uint8_t> pixels) {
  

  this->flags = flags;
  x = 64;
  y = 32;



  //find the bounding box of our sprite, and set that as the hitbox
  for(uint8_t i = 0; i < pixels.size(); i++){
    if(i % 2 == 0){

    if(pixels[i] > hitbox[0]) hitbox[0] = pixels[i]; 
    }else{

    if(pixels[i] > hitbox[1]) hitbox[1] = pixels[i]; 
    }

  }

  
  pivot_point[0] = hitbox[0] / 2;
  pivot_point[1] = hitbox[1] / 2;

}

void Update();