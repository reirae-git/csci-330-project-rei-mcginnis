#include "player.hpp"

PlayerCharacter::PlayerCharacter() {
    allClasses[0] = new Wizard();
    allClasses[1] = new Guard();
    allClasses[2] = new Soldier();
    allClasses[3] = nullptr;  // Will be set by setGlobalUnlockables
    allClasses[4] = nullptr;  // Will be set by setGlobalUnlockables
    playerClass = nullptr;
    currHp = 0;
    dead = false;
}

void PlayerCharacter::setGlobalUnlockables(Paladin* paladin, Sorcerer* sorcerer) {
    allClasses[3] = paladin;
    allClasses[4] = sorcerer;
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

void PlayerClass::displayStats() const{
    printf("Class: %s\nMax HP: %d\nDefense: %d\nDamage: %d-%d\nMagika: %d-%d\n", 
           className, maxHp, defense, damage/2, damage, magika/2, magika);
}

const char* PlayerClass::getClassName() const{
    return className;
}

int PlayerClass::getMaxHp() const{
    return maxHp;
}

int PlayerClass::getDefense() const{
    return defense;
}

int PlayerClass::getDamage() const{
    return damage;
}

int PlayerClass::getMagika() const{
    return magika;
}

bool PlayerClass::isLocked() const{
    return locked;
}

UnlockableClass::UnlockableClass() {
    locked = true;
}

void UnlockableClass::unlock() {
    locked = false;
}

Sorcerer::Sorcerer() {
    snprintf(className, sizeof(className), "Sorcerer");
    maxHp = 70;
    defense = 4;
    damage = 4;
    magika = 24;
}

int Sorcerer::attack() {
    printf("%s attacks with a dagger!\n", className);
    // Random damage between damage/2 and damage
    int minDmg = damage / 2;
    int variance = damage - minDmg + 1;
    return minDmg + (rand() % variance);
}

int Sorcerer::castSpell() {
    printf("%s casts a fireball!\n", className);
    // Random damage between magika/2 and magika
    int minDmg = magika / 2;
    int variance = magika - minDmg + 1;
    return minDmg + (rand() % variance);
}

Soldier::Soldier() {
    snprintf(className, sizeof(className), "Soldier");
    maxHp = 100;
    defense = 8;
    damage = 16;
    magika = 8;
    locked = false;
}

int Soldier::attack() {
    printf("%s attacks with a sword!\n", className);
    int minDmg = damage / 2;
    int variance = damage - minDmg + 1;
    return minDmg + (rand() % variance);
}

int Soldier::castSpell() {
    printf("%s casts a small fire bolt!\n", className);
    int minDmg = magika / 2;
    int variance = magika - minDmg + 1;
    return minDmg + (rand() % variance);
}

Wizard::Wizard() {
    snprintf(className, sizeof(className), "Wizard");
    maxHp = 80;
    defense = 8;
    damage = 8;
    magika = 16;
    locked = false;
}

int Wizard::attack() {
    printf("%s attacks with a staff!\n", className);
    int minDmg = damage / 2;
    int variance = damage - minDmg + 1;
    return minDmg + (rand() % variance);
}

int Wizard::castSpell() {
    printf("%s casts a magic missile!\n", className);
    int minDmg = magika / 2;
    int variance = magika - minDmg + 1;
    return minDmg + (rand() % variance);
}

Paladin::Paladin() {
    snprintf(className, sizeof(className), "Paladin");
    maxHp = 100;
    defense = 12;
    damage = 12;
    magika = 8;
}

int Paladin::attack() {
    printf("%s attacks with a holy sword!\n", className);
    int minDmg = damage / 2;
    int variance = damage - minDmg + 1;
    return minDmg + (rand() % variance);
}

int Paladin::castSpell() {
    printf("%s casts a healing spell!\n", className);
    int minDmg = magika / 2;
    int variance = magika - minDmg + 1;
    return minDmg + (rand() % variance);
}

Guard::Guard() {
    snprintf(className, sizeof(className), "Guard");
    maxHp = 120;
    defense = 16;
    damage = 8;
    magika = 8;
    locked = false;
}

int Guard::attack() {
    printf("%s attacks with a spear!\n", className);
    int minDmg = damage / 2;
    int variance = damage - minDmg + 1;
    return minDmg + (rand() % variance);
}

int Guard::castSpell() {
    printf("%s casts a minor attack spell!\n", className);
    int minDmg = magika / 2;
    int variance = magika - minDmg + 1;
    return minDmg + (rand() % variance);
}