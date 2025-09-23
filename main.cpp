#include <iostream>
#include "header.hpp"
#include <iostream>


int main() {
    PlayerCharacter* player = new PlayerCharacter();
    player->setPlayerClass();
    player->displayStats();
    Enemy* enemy = new Enemy("Goblin", 50, 50, 10, 5);
    Combat::startCombat(player, enemy);
    int temp;
    std::cin >> temp;
    return 0;}