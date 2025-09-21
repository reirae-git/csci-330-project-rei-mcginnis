#include <cstring>
#include <cstdio>
class Enemy {
    public:
        char enemyType[50];
        int hp;
        int maxHp;
        int damage;
        int defense;

        Enemy(const char* type, int health, int maxHealth, int dmg, int def) {
            strncpy(enemyType, type, sizeof(enemyType));
            enemyType[sizeof(enemyType) - 1] = '\0'; // Ensure null-termination
            hp = health;
            maxHp = maxHealth;
            damage = dmg;
            defense = def;
        }

        void displayStats() const {
            printf("Enemy Type: %s\nHP: %d\nDamage: %d\nDefense: %d\n", 
                   enemyType, hp, damage, defense);
        }

        void loseHp(int dmg) {
            hp -= dmg;
            if (hp < 0) hp = 0;
        }
        void gainHp(int heal) {
            hp += heal;
        }
        int getHp() const { return hp; }
        int getDamage() const { return damage; }
        int getDefense() const { return defense; }
        const char* getEnemyType() const { return enemyType; }
};