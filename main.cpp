#include <iostream>
#include "player.hpp"
#include "dungeon.hpp"
#include "items.hpp"

void displayMovementOptions(Room* currentRoom) {
    printf("\n--- Movement Options ---\n");
    if (currentRoom->getUpRoom()) printf("W - Move North\n");
    if (currentRoom->getDownRoom()) printf("S - Move South\n");
    if (currentRoom->getLeftRoom()) printf("A - Move West\n");
    if (currentRoom->getRightRoom()) printf("D - Move East\n");
    printf("M - Show Map\n");
    printf("I - Show Stats\n");
    printf("V - View Inventory\n");
    printf("U - Use Item\n");
    printf("Q - Quit Game\n");
    printf("\nChoice: ");
}

void showMap(Floor* floor, int currentX, int currentY) {
    printf("\n=== DUNGEON MAP ===\n");
    printf("Your position: [X]\n\n");
    
    for (int j = Floor::SIZE - 1; j >= 0; j--) {
        for (int i = 0; i < 4; i++) {
            for (int l = 0; l < Floor::SIZE; l++) {
                if (j == Floor::SIZE - 1 && i == 0) {
                    std::cout << "____";
                }
                else if (i == 0) {
                    continue;
                }        
                else if (i == 1) {
                    if (l == currentX && j == currentY) {
                        std::cout << "|[X]";
                    } else if (floor->rooms[l][j]->cleared) {
                        std::cout << "|[.]";
                    } else if (dynamic_cast<BossRoom*>(floor->rooms[l][j])) {
                        std::cout << "|[B]";
                    } else if (dynamic_cast<StartRoom*>(floor->rooms[l][j])) {
                        std::cout << "|[S]";
                    } else {
                        std::cout << "|[ ]";
                    }
                }
                else if (i == 2) {
                    if (floor->rooms[l][j]->leftRoom != nullptr) {
                        std::cout << "    ";
                    } else {
                        std::cout << "|   ";
                    }
                }
                else {
                    if (floor->rooms[l][j]->downRoom != nullptr) {
                        std::cout << "|_ _";
                    } else {
                        std::cout << "|___";
                    }
                }
                if (l == Floor::SIZE - 1) {
                    if (i == 0 && j == Floor::SIZE-1) {
                        std::cout << std::endl;
                        continue;
                    }
                    std::cout << "|" << std::endl;
                }
            }
        }
    }
    printf("\nLegend: [X]=You [.]=Cleared [B]=Boss [S]=Start [ ]=Unexplored\n");
}

// Global unlockable classes that persist across games
Paladin* globalPaladin = nullptr;
Sorcerer* globalSorcerer = nullptr;

void initializeGlobalClasses() {
    if (!globalPaladin) globalPaladin = new Paladin();
    if (!globalSorcerer) globalSorcerer = new Sorcerer();
}

void checkUnlocks(int floorsCompleted) {
    if (floorsCompleted >= 2 && globalPaladin->isLocked()) {
        globalPaladin->unlock();
        printf("\n*** CLASS UNLOCKED: PALADIN ***\n");
        printf("You can now select Paladin in your next game!\n");
    }
    if (floorsCompleted >= 5 && globalSorcerer->isLocked()) {
        globalSorcerer->unlock();
        printf("\n*** CLASS UNLOCKED: SORCERER ***\n");
        printf("You can now select Sorcerer in your next game!\n");
    }
}

int runGame() {
    // Create player
    PlayerCharacter* player = new PlayerCharacter();
    
    // Set global unlockable classes
    player->setGlobalUnlockables(globalPaladin, globalSorcerer);
    
    player->setPlayerClass();
    printf("\n");
    player->displayStats();
    
    // Create dungeon
    Dungeon dungeon;
    dungeon.generateNewFloor();
    
    // Game state
    int currentX = dungeon.floors[0].startX;
    int currentY = dungeon.floors[0].startY;
    Room* currentRoom = dungeon.floors[0].rooms[currentX][currentY];
    
    printf("\n\nPress Enter to begin your adventure...");
    std::cin.ignore();
    std::cin.get();
    
    // Main game loop
    while (!player->dead) {
        // Enter current room
        currentRoom->enterRoom(player);
        
        if (player->dead) {
            printf("\n*** GAME OVER ***\n");
            break;
        }
        
        // Check if boss room cleared
        if (dynamic_cast<BossRoom*>(currentRoom) && currentRoom->cleared) {
            printf("\nWould you like to proceed to the next floor? (Y/N): ");
            char choice;
            std::cin >> choice;
            std::cin.ignore(10000, '\n'); // Clear buffer
            if (choice == 'Y' || choice == 'y') {
                dungeon.generateNewFloor();
                currentX = dungeon.floors[dungeon.floor - 1].startX;
                currentY = dungeon.floors[dungeon.floor - 1].startY;
                currentRoom = dungeon.floors[dungeon.floor - 1].rooms[currentX][currentY];
                printf("\n*** ENTERING FLOOR %d ***\n", dungeon.floor);
                continue;
            }
        }
        
        // Movement loop
        bool moved = false;
        while (!moved && !player->dead) {
            displayMovementOptions(currentRoom);
            
            char move;
            std::cin >> move;
            
            // Clear any remaining input
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                printf("Invalid input!\n");
                continue;
            }
            
            switch(move) {
                case 'W':
                case 'w':
                    if (currentRoom->getUpRoom()) {
                        currentY++;
                        currentRoom = dungeon.floors[dungeon.floor - 1].rooms[currentX][currentY];
                        printf("\nYou move north...\n");
                        moved = true;
                    } else {
                        printf("Can't move in that direction!\n");
                    }
                    break;
                    
                case 'S':
                case 's':
                    if (currentRoom->getDownRoom()) {
                        currentY--;
                        currentRoom = dungeon.floors[dungeon.floor - 1].rooms[currentX][currentY];
                        printf("\nYou move south...\n");
                        moved = true;
                    } else {
                        printf("Can't move in that direction!\n");
                    }
                    break;
                    
                case 'A':
                case 'a':
                    if (currentRoom->getLeftRoom()) {
                        currentX--;
                        currentRoom = dungeon.floors[dungeon.floor - 1].rooms[currentX][currentY];
                        printf("\nYou move west...\n");
                        moved = true;
                    } else {
                        printf("Can't move in that direction!\n");
                    }
                    break;
                    
                case 'D':
                case 'd':
                    if (currentRoom->getRightRoom()) {
                        currentX++;
                        currentRoom = dungeon.floors[dungeon.floor - 1].rooms[currentX][currentY];
                        printf("\nYou move east...\n");
                        moved = true;
                    } else {
                        printf("Can't move in that direction!\n");
                    }
                    break;
                    
                case 'M':
                case 'm':
                    showMap(&dungeon.floors[dungeon.floor - 1], currentX, currentY);
                    break;
                    
                case 'I':
                case 'i':
                    printf("\n");
                    player->displayStats();
                    break;
                    
                case 'V':
                case 'v':
                    player->inventory.displayInventory();
                    break;
                    
                case 'U':
                case 'u':
                    {
                        if (player->inventory.items.empty()) {
                            printf("Your inventory is empty!\n");
                            break;
                        }
                        
                        player->inventory.displayInventory();
                        printf("\nEnter item number to use (0 to cancel): ");
                        int itemNum;
                        
                        if (std::cin >> itemNum) {
                            if (itemNum > 0 && itemNum <= (int)player->inventory.items.size()) {
                                Item* item = player->inventory.getItem(itemNum - 1);
                                item->use(player);
                                
                                // Remove consumables after use
                                if (item->type == CONSUMABLE) {
                                    player->inventory.removeItem(itemNum - 1);
                                }
                            } else if (itemNum != 0) {
                                printf("Invalid item number!\n");
                            }
                        } else {
                            printf("Invalid input!\n");
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    }
                    break;
                    
                case 'Q':
                case 'q':
                    {
                        printf("\nThanks for playing!\n");
                        int floorsCompleted = dungeon.floor;
                        delete player;
                        return floorsCompleted;
                    }
                    
                default:
                    printf("Invalid input!\n");
                    break;
            }
        }
    }
    
    printf("\nFinal Stats:\n");
    player->displayStats();
    printf("Floors Conquered: %d\n", dungeon.floor);
    
    int floorsCompleted = dungeon.floor;
    delete player;
    return floorsCompleted;
}

int main() {
    srand(time(0));
    
    // Initialize global unlockable classes
    initializeGlobalClasses();
    
    bool playAgain = true;
    
    while (playAgain) {
        printf("========================================\n");
        printf("    WELCOME TO THE DUNGEON CRAWLER     \n");
        printf("========================================\n\n");
        
        // Show unlock status
        printf("--- Unlockable Classes ---\n");
        if (globalPaladin->isLocked()) {
            printf("Paladin: LOCKED (Complete 2 floors to unlock)\n");
        } else {
            printf("Paladin: UNLOCKED\n");
        }
        if (globalSorcerer->isLocked()) {
            printf("Sorcerer: LOCKED (Complete 5 floors to unlock)\n");
        } else {
            printf("Sorcerer: UNLOCKED\n");
        }
        printf("\n");
        
        // Run the game
        int floorsCompleted = runGame();
        
        // Check for unlocks
        checkUnlocks(floorsCompleted);
        
        // Ask to play again
        printf("\nWould you like to play again? (Y/N): ");
        char choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n'); // Clear buffer
        
        if (choice != 'Y' && choice != 'y') {
            playAgain = false;
            printf("\nThanks for playing! Final unlocks:\n");
            if (!globalPaladin->isLocked()) printf("- Paladin\n");
            if (!globalSorcerer->isLocked()) printf("- Sorcerer\n");
        }
        
        printf("\n");
    }
    
    // Cleanup global classes
    delete globalPaladin;
    delete globalSorcerer;
    
    return 0;
}