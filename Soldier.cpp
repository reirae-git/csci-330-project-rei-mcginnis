#include "header.hpp"
#include <cstdio>
#include <cstring>

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
    return damage;
}
int Soldier::castSpell() {
    printf("%s casts a battle cry!\n", className);
    return magika; // Buff spell
}