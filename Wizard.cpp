#include "header.hpp"
#include <cstdio>
#include <cstring>

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
    return damage;
}
int Wizard::castSpell() {
    printf("%s casts a magic missile!\n", className);
    return magika;
}
