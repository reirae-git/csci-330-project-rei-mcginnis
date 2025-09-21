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
    ~PlayerCharacter();
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
    
    PlayerClass();
    virtual ~PlayerClass() = default;
    
    const char* getClassName() const { return className; }
    int getMaxHp() const { return maxHp; }
    int getDefense() const { return defense; }
    int getDamage() const { return damage; }
    int getMagika() const { return magika; }
    bool isLocked() const { return locked; }
    virtual void unlock() { locked = false; }
    
    void displayStats() const {
        printf("Class: %s\nMax HP: %d\nDefense: %d\nDamage: %d\nMagika: %d\n", 
               className, maxHp, defense, damage, magika);
    }
    
    virtual void attack() = 0;
    virtual void castSpell() = 0;
};

class UnlockableClass : public PlayerClass {
public:
    UnlockableClass();
    virtual void unlock() = 0;
};

// Concrete player classes
class Wizard : public PlayerClass {
public:
    Wizard();
    void attack() override;
    void castSpell() override;
};

class Guard : public PlayerClass {
public:
    Guard();
    void attack() override;
    void castSpell() override;
};

class Soldier : public PlayerClass {
public:
    Soldier();
    void attack() override;
    void castSpell() override;
};

class Paladin : public UnlockableClass {
public:
    Paladin();
    void unlock() override;
    void attack() override;
    void castSpell() override;
};

class Sorcerer : public UnlockableClass {
public:
    Sorcerer();
    void unlock() override;
    void attack() override;
    void castSpell() override;
};

#endif