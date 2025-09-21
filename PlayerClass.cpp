#include <cstdio>

class PlayerClass {
    public:
        char className[50];
        int maxHp;
        int defense;
        int damage;
        int magika;
        bool locked = false;
        char getClassName() { return *className;}
        int getMaxHp() { return maxHp;}
        int getDefense() { return defense;}
        int getDamage() { return damage;}
        int getMagika() { return magika;}
        bool isLocked() { return locked;}
        void unlock() {locked = false;}
        void displayStats() {
            printf("Class: %s\nMax HP: %d\nDefense: %d\nDamage: %d\nMagika: %d\n", className, maxHp, defense, damage, magika);
        }
        virtual int attack() = 0;
        virtual int castSpell() = 0;
};

class unlockableClass : public PlayerClass {
    public:
        unlockableClass() {
            locked = true;
        }
        virtual void unlock() = 0;
};

class Wizard : public PlayerClass {
    public:
        Wizard() {
            snprintf(className, sizeof(className), "Wizard");
            maxHp = 80;
            defense = 8;
            damage = 8;
            magika = 16;
            locked = false;
        }
        int attack() override {
            printf("%s attacks with a staff!\n", className);
            return damage;
        }
        int castSpell() override {
            printf("%s casts a magic missile!\n", className);
            return magika;
        }
};

class Guard : public PlayerClass {
    public:
        Guard() {
            snprintf(className, sizeof(className), "Guard");
            maxHp = 120;
            defense = 16;
            damage = 8;
            magika = 8;
            locked = false;
        }
        int attack() override {
            printf("%s attacks with a spear!\n", className);
            return damage;
        }
        int castSpell() override {
            printf("%s casts a shield spell!\n", className);
            return magika; // Defensive spell reduces damage
        }
};

class Soldier : public PlayerClass {
    public:
        Soldier() {
            snprintf(className, sizeof(className), "Soldier");
            maxHp = 100;
            defense = 8;
            damage = 16;
            magika = 8;
            locked = false;
        }
        int attack() override {
            printf("%s attacks with a sword!\n", className);
            return damage;
        }
        int castSpell() override {
            printf("%s casts a battle cry!\n", className);
            return magika; // Buff spell
        }
};

class Paladin : public unlockableClass {
    public:
        Paladin() {
            snprintf(className, sizeof(className), "Paladin");
            maxHp = 120;
            defense = 12;
            damage = 10;
            magika = 10;
        }
        void unlock() {
            locked = false;
        }
        int attack() override {
            printf("%s attacks with a holy sword!\n", className);
            return damage;
        }
        int castSpell() override {
            printf("%s casts a healing spell!\n", className);
            return magika;
        }
};

class Sorcerer : public unlockableClass {
    public:
        Sorcerer() {
            snprintf(className, sizeof(className), "Sorcerer");
            maxHp = 80;
            defense = 4;
            damage = 4;
            magika = 24;
        }
        void unlock() {
            locked = false;
        }
        int attack() override {
            printf("%s attacks with a dagger!\n", className);
            return damage;
        }
        int castSpell() override {
            printf("%s casts a fireball!\n", className);
            return magika;
        }
};