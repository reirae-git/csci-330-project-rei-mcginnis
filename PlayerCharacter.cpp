#include "header.hpp"
#include <cstdio>
#include <iostream>
#include <cstring>

PlayerCharacter::PlayerCharacter() {
    allClasses[0] = new Wizard();
    allClasses[1] = new Guard();
    allClasses[2] = new Soldier();
    allClasses[3] = new Paladin();
    allClasses[4] = new Sorcerer();
    playerClass = nullptr;
    currHp = 0;
}

void PlayerCharacter::displayStats() const {
    if (playerClass) {
        printf("--- Player Stats ---\n");
        playerClass->displayStats();
        printf("Current HP: %d\n", currHp);
    } else {
        printf("No class selected.\n");
    }
}

void PlayerCharacter::setPlayerClass() {
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

int PlayerCharacter::getCurrHp() const {
    return currHp;
}

PlayerClass* PlayerCharacter::getPlayerClass() const {
    return playerClass;
}

void PlayerCharacter::loseHp(int damage) {
    currHp -= damage;
    if (currHp < 0) currHp = 0;
}

void PlayerCharacter::gainHp(int heal) {
    currHp += heal;
    if (currHp > playerClass->getMaxHp()) currHp = playerClass->getMaxHp();
}