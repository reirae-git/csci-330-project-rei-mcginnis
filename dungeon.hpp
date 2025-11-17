#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "header.hpp"
#include <cstdio>
#include <array>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>

//made this but couldnt figure it out so for now its gonna be just random rooms
//
class Room;
class Floor;

class Dungeon {
public:
    int floor = 0;
    std::vector<Floor> floors;
    void generateNewFloor();
    static Room* generateRandomRoom(int x, int y);
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
    PlayerCharacter* player;
    bool cleared = false;
    int xPos;
    int yPos;
    Room *leftRoom = nullptr;
    Room *rightRoom = nullptr;
    Room *upRoom = nullptr;
    Room *downRoom = nullptr;
    virtual void enterRoom() = 0;
    Room* getLeftRoom() {
        return leftRoom;
    }
    Room* getRightRoom() {
        return rightRoom;
    }
    Room* getUpRoom() {
        return upRoom;
    }
    Room* getDownRoom() {
        return downRoom;
    }
    Room(int x, int y) : xPos(x), yPos(y) {}
   void EnterRoom(PlayerCharacter* player){
    this->player = player;
   }
};

class BossRoom : public Room {
public:
    void enterRoom(){

    };

    BossRoom(int x, int y) : Room(x,y) {}
};

class TreasureRoom : public Room {
public:
    void enterRoom(){

    };

    TreasureRoom(int x, int y) : Room(x,y) {}
};

class TrapRoom : public Room {
public:
    void enterRoom(){

    };

    TrapRoom(int x, int y) : Room(x,y) {}
};

class BattleRoom : public Room {
public:
    void enterRoom(){

    };

    BattleRoom(int x, int y) : Room(x,y) {}
};

class StartRoom : public Room {
public:
    void enterRoom(){

    };

    StartRoom(int x, int y) : Room(x,y) {}
};

#endif //DUNGEON_HPP