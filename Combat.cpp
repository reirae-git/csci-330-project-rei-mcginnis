#include "header.hpp"
#include <random>
#include <cstdio>
#include <cstring>
#include <iostream>

void Combat::startCombat(PlayerCharacter *player, Enemy *enemy) {
    printf("\nA wild %s appears!\n", enemy->getEnemyType());
    enemy->displayStats();
    playerTurn(player, enemy);
}
void Combat::enemyTurn(PlayerCharacter *player, Enemy *enemy) {
    printf("\nEnemy's turn!\n");
    int dmg = enemy->getDamage();
    int netDmg = dmg - player->getPlayerClass()->getDefense();
    printf("The %s attacks you for %d damage!\n", enemy->getEnemyType(), netDmg);
    if (netDmg < 0) netDmg = 0;
    player->loseHp(netDmg);
    if (!isCombatOver(player, enemy)) {
        playerTurn(player, enemy);
    }
}

void Combat::playerTurn(PlayerCharacter *player, Enemy *enemy) {
    int choice;
    bool b = true;
    while (b) {
        printf("\nYour turn! Choose an action:\n1. Attack\n2. Cast Spell\n");
        std::cin >> choice;
        if (choice == 1 || choice == 2) {
            b = false;
        }
    }
    if (choice == 1) {
        int dmg = player->getPlayerClass()->attack();
        int netDmg = dmg - enemy->getDefense();
        if (netDmg < 0) netDmg = 0;
            enemy->loseHp(netDmg);
        printf("You dealt %d damage to the %s!\n", netDmg, enemy->getEnemyType());
    } else if (choice == 2) {
        int spellDmg = player->getPlayerClass()->castSpell();
        int netDmg = spellDmg - enemy->getDefense();
        if (netDmg < 0) netDmg = 0;
        enemy->loseHp(netDmg);
        printf("You dealt %d spell damage to the %s!\n", netDmg, enemy->getEnemyType());
    }
    
    if (!isCombatOver(player, enemy)) {
        enemyTurn(player, enemy);
    }
}
bool Combat::isCombatOver(PlayerCharacter *player, Enemy *enemy) {
    if (player->getCurrHp() <= 0) {
        printf("\nYou have been defeated by the %s...\n", enemy->getEnemyType());
        return true;
    }
    if (enemy->getHp() <= 0) {
        printf("\nYou have defeated the %s!\n", enemy->getEnemyType());
        return true;
    }
    return false;
}