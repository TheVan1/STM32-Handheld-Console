
#include "player_gnorp.h"
#include "main.h"

void PlayerGnorp::Update(){
    if(nullptr == manager) Error_Handler();

    double dtime = manager->get_delta_time();
    velocity_x += (manager->get_player_input(0) - 128) * dtime;

    return;
    
}