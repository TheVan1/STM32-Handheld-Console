#include "game_object.h"
#include "player_gnorp.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <stdint.h>
#include <string.h>

GameObject::GameObject(uint8_t flags, std::vector<uint8_t> sprite) {

  this->flags = flags;
  x = 64;
  y = 32;

  /*
  the vector parameter holds the pixel data in the following way:
  x0, y0, x1, y1 ... xN, yN

  whereas we expect our GameObject pixel data to be stored as two arrays such:
  x0, x1 ... xN
  and
  y0, y1 ... yN

  this is the same amount of data, however the variable amount of data in the
  construction lends itself to a Vector, whilst the common reads and uncommon
  writes to our GameObject means that a pair of arrays is better

  this constructor handles this translation, which has an o(n) complexity. this
  shouldnt be too terrible, due to how infrequently it should be called
  */

  this->pixels[0] = new uint8_t[sprite.size() / 2];
  this->pixels[1] = new uint8_t[sprite.size() / 2];
  this->pixel_count = sprite.size() / 2;

  /*
  simple o(n) function to find the largest values of our pixels
  alongside our translation from vector to our arrays

  we're iterating 2 items at a time, as that corresponds to a single X and a
  single Y axis value from our sprite arg

  she's a little ugly, but she gets the job done
  */
  for (uint8_t i = 0; i < sprite.size(); i += 2) {
    this->pixels[0][i / 2] = sprite[i];

    if (sprite[i] > hitbox[0]) {
      hitbox[0] = sprite[i];
    }

    this->pixels[1][i / 2] = sprite[i + 1];

    if (sprite[i + 1] > hitbox[1]) {
      hitbox[1] = sprite[i + 1];
    }
  }

  pivot_point[0] = hitbox[0] / 2;
  pivot_point[1] = hitbox[1] / 2;
}
