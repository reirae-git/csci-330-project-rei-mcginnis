#include "dungeon.hpp"
#include <iostream>

int main() {
    std::cout << "Creating dungeon..." << std::endl;
    Dungeon dungeon;
    std::cout << "Generating new floor..." << std::endl;
    dungeon.generateNewFloor();
    std::cout << "Displaying floor..." << std::endl;
    dungeon.floors[0].displayFloor();
    int temp;
    std::cin >> temp;
    return 0;
}