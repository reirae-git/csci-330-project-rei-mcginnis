#include <iostream>
#include "header.hpp"


int main() {
    PlayerCharacter* player = new PlayerCharacter();
    player->setPlayerClass();
    player->displayStats();
    return 0;}