#include <cstring>
#include <cstdio>
#include "header.hpp"

Enemy::Enemy(const char* type, int health, int maxHealth, int dmg, int def) {
    strncpy(enemyType, type, sizeof(enemyType));
    enemyType[sizeof(enemyType) - 1] = '\0'; // Ensure null-termination
    hp = health;
    maxHp = maxHealth;
    damage = dmg;
    defense = def;
}
void Enemy::displayStats() const {
    printf("Enemy Type: %s\nHP: %d\nDamage: %d\nDefense: %d\n", 
           enemyType, hp, damage, defense);
}
void Enemy::loseHp(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}
void Enemy::gainHp(int heal) {
    hp += heal;
}
int Enemy::getHp() const { return hp; }
int Enemy::getDamage() const { return damage; }
int Enemy::getDefense() const { return defense; }
const char* Enemy::getEnemyType() const { return enemyType; }