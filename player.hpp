// player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdio>
#include <cstring>
#include <iostream>
#include "items.hpp"

// Forward declaration
class Enemy;

class PlayerClass;
class Paladin;
class Sorcerer;

class PlayerCharacter {
public:
    bool dead;
    PlayerClass* playerClass;
    Inventory inventory;
    
    PlayerCharacter();
    void setPlayerClass();
    void setGlobalUnlockables(Paladin* paladin, Sorcerer* sorcerer);
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


#endif //PLAYER_HPP