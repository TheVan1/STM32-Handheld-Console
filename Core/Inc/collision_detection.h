/*
 * collision_detection.h
 *
 *  Created on: 16 Dec 2025
 *      Author: Vanessa
 */

#ifndef INC_COLLISION_DETECTION_H
#define INC_COLLISION_DETECTION_H

#include <vector>
#include <stdint.h>
#include <game_object.h>

void detect_collisions(std::vector<GameObject *> objects, bool effect_triggers);


#endif 
