#ifndef INC_PLAYER_GNORP_H
#define INC_PLAYER_GNORP_H

#include "game_object.h"
#include <cstdint>
#include "game_manager.h"
#include <vector>

class PlayerGnorp : public GameObject{
    public:
        PlayerGnorp(uint8_t flags, std::vector<uint8_t> pixels, GameManager * manager) : GameObject( flags, pixels, manager){}
        void Update() override;
        void OnCollision(GameObject * colliding_object) override;
    
};

#endif