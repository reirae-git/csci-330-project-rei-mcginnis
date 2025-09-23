#include "header.hpp"
#include <cstdio>
#include <cstring>

void PlayerClass::displayStats() const{
    printf("Class: %s\nMax HP: %d\nDefense: %d\nDamage: %d\nMagika: %d\n", className, maxHp, defense, damage, magika);
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