#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "player.hpp"
#include <cstdio>
#include <array>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <cstring>

// Forward declarations
class Room;
class Floor;
class Enemy;

class Dungeon {
public:
    int floor = 0;
    std::vector<Floor> floors;
    void generateNewFloor();
    static Room* generateRandomRoom(int x, int y);
};

// Enemy class definition - moved before Room
class Enemy {
public:
    char enemyType[50];
    int hp;
    int maxHp;
    int damage;
    int defense;
    Enemy(const char* type, int health, int maxHealth, int dmg, int def);
    Enemy() {} 
    void displayStats() const;
    void loseHp(int dmg);
    void gainHp(int heal);
    int getHp() const;
    int getDamage() const;
    int getDefense() const;
    const char* getEnemyType() const;
    static Enemy generateRandomEnemy(int level);
};

class Floor {
private:
    bool dfsBuildPath(int x, int y, Room* target, std::vector<std::vector<bool>>& visited);
    void addSecondaryConnections(std::vector<std::vector<bool>>& visited);
    void connectTwoRooms(int x1, int y1, int x2, int y2);
    int countConnections(int x, int y);
    void connectIsolatedRoom(int x, int y, std::vector<std::vector<bool>>& visited);
    void addRandomConnection(int x, int y);
public:
    int startX = 4;
    int startY = 0;
    int floorNumber;
    static const int SIZE = 9;
    std::array<std::array<Room*,SIZE>,SIZE> rooms = {};
    Floor(int number) : floorNumber(number) {
        generateRooms();
        connectRooms(startX, startY);
    };
    void generateRooms();
    void connectRooms(int x, int y);
    void displayFloor();
};

class Room {
public:
    Enemy enemy;
    PlayerCharacter* player;
    bool cleared = false;
    int xPos;
    int yPos;
    Room *leftRoom = nullptr;
    Room *rightRoom = nullptr;
    Room *upRoom = nullptr;
    Room *downRoom = nullptr;
    virtual void enterRoom(PlayerCharacter* player) = 0;
    Room* getLeftRoom() { return leftRoom; }
    Room* getRightRoom() { return rightRoom; }
    Room* getUpRoom() { return upRoom; }
    Room* getDownRoom() { return downRoom; }
    Room(int x, int y) : xPos(x), yPos(y) {}
    Room() {}
    virtual ~Room() {}
};

class BossRoom : public Room {
public:
    void enterRoom(PlayerCharacter* player) override;
    BossRoom(int x, int y) : Room(x,y) {}
};

class TreasureRoom : public Room {
public:
    void enterRoom(PlayerCharacter* player) override;
    TreasureRoom(int x, int y) : Room(x,y) {}
};

class TrapRoom : public Room {
public:
    void enterRoom(PlayerCharacter* player) override;
    TrapRoom(int x, int y) : Room(x,y) {}
};

class BattleRoom : public Room {
public:
    void enterRoom(PlayerCharacter* player) override;
    BattleRoom(int x, int y) : Room(x,y) {}
};

class StartRoom : public Room {
public:
    void enterRoom(PlayerCharacter* player) override;
    StartRoom(int x, int y) : Room(x,y) {}
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

#endif //DUNGEON_HPP