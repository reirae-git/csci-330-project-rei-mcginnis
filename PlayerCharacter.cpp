#include "header.hpp"
#include <cstdio>
#include <iostream>
#include <cstring>

class PlayerCharacter {
    public:
        PlayerClass* playerClass;
        PlayerClass* allClasses[5] = {new Wizard(), new Guard(), new Soldier(), new Paladin(),new Sorcerer()};
        int currHp;
        int getCurrHp() { return currHp; }
        PlayerClass* getPlayerClass() { return playerClass; }
        void loseHp(int damage) { currHp -= damage; if (currHp < 0) currHp = 0; }
        void gainHp(int heal) { currHp += heal; if (currHp > playerClass->getMaxHp()) currHp = playerClass->getMaxHp(); }
        PlayerCharacter() {
            playerClass = nullptr;
            currHp = 0;
        }
        void setPlayerClass() {
            char buffer[50];
            printf("What class would you like to be? (Wizard");
            for (int i = 1; i < 5; i++) {
                if (!allClasses[i]->isLocked()) {
                    printf(", %s", allClasses[i]->getClassName());
                }
            }
            printf("): ");
            std::cin >> buffer;
            for (int i = 0; i < 5; i++) {
                if (strcmp(buffer, allClasses[i]->getClassName()) == 0) {
                    if (allClasses[i]->isLocked()) {
                        printf("Class %s is locked. Choose another class.\n", allClasses[i]->getClassName());
                        setPlayerClass();
                        return;
                    }
                    playerClass = allClasses[i];
                    currHp = playerClass->getMaxHp();
                    printf("You are now a %s!\n", playerClass->getClassName());
                    return;
                }
            }
            printf("Invalid class name. Please try again.\n");
            setPlayerClass();
        }
        void displayStats() {
            if (playerClass) {
                printf("--- Player Stats ---\n");
                playerClass->displayStats();
                printf("Current HP: %d\n", currHp);
            } else {
                printf("No class selected.\n");
            }
        }
};