#include "header.hpp"
#include <cstdio>
#include <cstring>

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
    return damage;
}
int Guard::castSpell() {
    printf("%s casts a shield spell!\n", className);
    return magika; // Defensive spell reduces damage
}
