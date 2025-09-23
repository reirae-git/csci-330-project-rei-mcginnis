#include "header.hpp"
#include <cstdio>
#include <cstring>

Sorcerer::Sorcerer() {
    snprintf(className, sizeof(className), "Sorcerer");
    maxHp = 70;
    defense = 4;
    damage = 4;
    magika = 24;
}
int Sorcerer::attack() {
    printf("%s attacks with a dagger!\n", className);
    return damage;
}
int Sorcerer::castSpell() {
    printf("%s casts a lightning bolt!\n", className);
    return magika;
}
