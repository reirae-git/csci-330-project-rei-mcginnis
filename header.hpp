// header.hpp
#ifndef HEADER_HPP
#define HEADER_HPP

#include <cstdio>

// Forward declaration
class Enemy;

class PlayerClass;

class PlayerCharacter {
public:
    PlayerClass* playerClass;
    PlayerCharacter();
    void setPlayerClass();
    int getCurrHp() const;
    PlayerClass* getPlayerClass() const;
    void loseHp(int damage);
    void gainHp(int heal);
    void displayStats() const;
private:
    PlayerClass* allClasses[5];
    int currHp;
};

// Base class for all player classes
class PlayerClass {
public:
    char className[50];
    int maxHp;
    int defense;
    int damage;
    int magika;
    bool locked;    
    const char* getClassName() const;
    int getMaxHp() const;
    int getDefense() const;
    int getDamage() const;
    int getMagika() const;
    bool isLocked() const;  
    void displayStats() const;
    
    virtual int attack() = 0;
    virtual int castSpell() = 0;
};

class UnlockableClass : public PlayerClass {
public:
    UnlockableClass();
    void unlock();
};

// Concrete player classes
class Wizard : public PlayerClass {
public:
    Wizard();
    int attack() override;
    int castSpell() override;
};

class Guard : public PlayerClass {
public:
    Guard();
    int attack() override;
    int castSpell() override;
};

class Soldier : public PlayerClass {
public:
    Soldier();
    int attack() override;
    int castSpell() override;
};

class Paladin : public UnlockableClass {
public:
    Paladin();
    int attack() override;
    int castSpell() override;
};

class Sorcerer : public UnlockableClass {
public:
    Sorcerer();
    int attack() override;
    int castSpell() override;
};

class Enemy {
public:
    char enemyType[50];
    int hp;
    int maxHp;
    int damage;
    int defense;
    Enemy(const char* type, int health, int maxHealth, int dmg, int def);
    void displayStats() const;
    void loseHp(int dmg);
    void gainHp(int heal);
    int getHp() const;
    int getDamage() const;
    int getDefense() const;
    const char* getEnemyType() const;
};

class Combat {
public:
    PlayerCharacter &player;
    Enemy &enemy;
    static void startCombat(PlayerCharacter *player, Enemy *enemy);
    static void playerTurn(PlayerCharacter *player, Enemy *enemy);
    static void enemyTurn(PlayerCharacter *player, Enemy *enemy);
    static bool isCombatOver(PlayerCharacter *player, Enemy *enemy);
};
#endif //HEADER_HPP