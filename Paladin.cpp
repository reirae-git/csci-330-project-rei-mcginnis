#include "header.hpp"
#include <cstdio>
#include <cstring>

Paladin::Paladin() {
    snprintf(className, sizeof(className), "Paladin");
    maxHp = 100;
    defense = 12;
    damage = 12;
    magika = 8;
}
int Paladin::attack() {
    printf("%s attacks with a holy sword!\n", className);
    return damage;
}
int Paladin::castSpell() {
    printf("%s casts a healing spell!\n", className);
    return magika;
}