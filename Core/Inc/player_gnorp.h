#ifndef INC_PLAYER_GNORP
#define INC_PLAYER_GNORP

#include <game_object.h>
#include <cstdint>
#include <vector>

class PlayerGnorp : public GameObject{
    public:
        PlayerGnorp(uint8_t flags, std::vector<uint8_t> pixels) : GameObject( flags, pixels){}
        void Update() override;
    
};

#endif