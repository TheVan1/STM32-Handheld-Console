#ifndef INC_PLAYER_GNORP_H
#define INC_PLAYER_GNORP_H

#include "game_object.h"
#include <cstdint>
#include "game_manager.h"
#include <vector>

class PlayerGnorp : public GameObject{
    public:
        PlayerGnorp(uint8_t flags, std::vector<uint8_t> pixels) : GameObject( flags, pixels){}
        void Update() override;
    
};

#endif