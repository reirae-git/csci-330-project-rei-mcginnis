#include "dungeon.hpp"
//
void Dungeon::generateNewFloor(){
    floor++;
    floors.push_back(Floor(floor));
}

Room* Dungeon::generateRandomRoom(int x, int y){
    srand(time(0));
    int roomType = rand() % 100; //0-normal, 1-treasure, 2-enemy
    if (roomType < 60) {
        return new BattleRoom(x,y);
    } else if (roomType < 80) {
        return new TreasureRoom(x,y);
    } else {
        return new TrapRoom(x,y);
    }
}

void Floor::generateRooms(){
    srand(time(0));

    int xNum = rand() % 9;
    int yNum = rand() % 6 + 3; //avoids boss room being too close to start
    rooms[xNum][yNum] = new BossRoom(xNum,yNum);
    if (floorNumber == 0) {
        rooms[4][0] = new StartRoom(4,0);
        startX = 4;
        startY = 0;
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if (rooms[i][j] != nullptr) {
                continue;
            }
            rooms[i][j] = Dungeon::generateRandomRoom(i,j);
        }
    }
}

/*void Floor::connectRooms(int x, int y){
    srand(time(0));
    int connectionCount = rand() % 3 + 1; //1-4 connections
    int currDirection = rand() % 4;
    int directions[4] = {0,1,2,3}; //0-up, 1-right, 2-down, 3-left
    if (x == 0) {
        directions[3] = -1; //no left
    }
    if (x == SIZE - 1) {
        directions[1] = -1; //no right
    }
    if (y == 0) {
        directions[2] = -1; //no down
    }
    if (y == SIZE - 1) {
        directions[0] = -1; //no up
    }


    for (int i = 0; i < connectionCount; i++) {
        if (directions[currDirection] == -1 ) {
            continue;
        }
        switch (currDirection) {
            case 0:
                if (rooms[x][y]->upRoom != nullptr) {
                    break;
                }
                rooms[x][y]->upRoom = rooms[x][y+1];
                rooms[x][y+1]->downRoom = rooms[x][y];
                connectRooms(x, y+1);
                break;
            case 1:
                if (rooms[x][y]->rightRoom != nullptr) {
                    break;
                }
                rooms[x][y]->rightRoom = rooms[x+1][y];
                rooms[x+1][y]->leftRoom = rooms[x][y];
                connectRooms(x+1, y);
                break;
            case 2:
                if (rooms[x][y]->downRoom != nullptr) {
                    break;
                }
                rooms[x][y]->downRoom = rooms[x][y-1];
                rooms[x][y-1]->upRoom = rooms[x][y];
                connectRooms(x, y-1);
                break;
            case 3:
                if (rooms[x][y]->leftRoom != nullptr) {
                    break;
                }
                rooms[x][y]->leftRoom = rooms[x-1][y];
                rooms[x-1][y]->rightRoom = rooms[x][y];
                connectRooms(x-1, y);
                break;
        }
        currDirection = rand() % 4;
    }
}*/

void Floor::connectRooms(int x, int y){
    // Use a visited tracking system
    std::vector<std::vector<bool>> visited(SIZE, std::vector<bool>(SIZE, false));
    
    // Pass 1: Create main path from start to boss using DFS
    Room* bossRoom = nullptr;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (dynamic_cast<BossRoom*>(rooms[i][j]) != nullptr) {
                bossRoom = rooms[i][j];
                break;
            }
        }
        if (bossRoom) break;
    }
    
    // DFS to create path
    dfsBuildPath(x, y, bossRoom, visited);
    
    // Pass 2: Add secondary connections and connect isolated rooms
    addSecondaryConnections(visited);
}

bool Floor::dfsBuildPath(int x, int y, Room* target, std::vector<std::vector<bool>>& visited) {
    visited[x][y] = true;
    
    // Found the target!
    if (rooms[x][y] == target) {
        return true;
    }
    
    // Try directions in random order
    std::vector<std::pair<int, int>> directions;
    if (y < SIZE - 1) directions.push_back({0, 1});   // up
    if (x < SIZE - 1) directions.push_back({1, 0});   // right
    if (y > 0) directions.push_back({0, -1});         // down
    if (x > 0) directions.push_back({-1, 0});         // left
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);
    
    for (auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        
        if (visited[newX][newY]) continue;
        
        // Create connection
        connectTwoRooms(x, y, newX, newY);
        
        // Recursively explore
        if (dfsBuildPath(newX, newY, target, visited)) {
            return true; // Found path to boss!
        }
    }
    
    return false; // Dead end
}

void Floor::addSecondaryConnections(std::vector<std::vector<bool>>& visited) {
    srand(time(0));
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // If room wasn't visited, try to connect it to a visited neighbor
            if (!visited[i][j]) {
                connectIsolatedRoom(i, j, visited);
            }
            
            // Add occasional extra connections (30% chance if room has only 1 connection)
            if (visited[i][j] && countConnections(i, j) == 1 && rand() % 100 < 30) {
                addRandomConnection(i, j);
            }
        }
    }
}

void Floor::connectTwoRooms(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    if (dx == 1) { // right
        rooms[x1][y1]->rightRoom = rooms[x2][y2];
        rooms[x2][y2]->leftRoom = rooms[x1][y1];
    } else if (dx == -1) { // left
        rooms[x1][y1]->leftRoom = rooms[x2][y2];
        rooms[x2][y2]->rightRoom = rooms[x1][y1];
    } else if (dy == 1) { // up
        rooms[x1][y1]->upRoom = rooms[x2][y2];
        rooms[x2][y2]->downRoom = rooms[x1][y1];
    } else if (dy == -1) { // down
        rooms[x1][y1]->downRoom = rooms[x2][y2];
        rooms[x2][y2]->upRoom = rooms[x1][y1];
    }
}

int Floor::countConnections(int x, int y) {
    int count = 0;
    if (rooms[x][y]->upRoom) count++;
    if (rooms[x][y]->downRoom) count++;
    if (rooms[x][y]->leftRoom) count++;
    if (rooms[x][y]->rightRoom) count++;
    return count;
}

void Floor::connectIsolatedRoom(int x, int y, std::vector<std::vector<bool>>& visited) {
    // Try to connect to a visited neighbor
    std::vector<std::pair<int, int>> neighbors;
    if (y < SIZE - 1 && visited[x][y+1]) neighbors.push_back({0, 1});
    if (x < SIZE - 1 && visited[x+1][y]) neighbors.push_back({1, 0});
    if (y > 0 && visited[x][y-1]) neighbors.push_back({0, -1});
    if (x > 0 && visited[x-1][y]) neighbors.push_back({-1, 0});
    
    if (!neighbors.empty()) {
        auto dir = neighbors[rand() % neighbors.size()];
        connectTwoRooms(x, y, x + dir.first, y + dir.second);
        visited[x][y] = true;
    }
}

void Floor::addRandomConnection(int x, int y) {
    std::vector<std::pair<int, int>> availableDirections;
    
    if (y < SIZE - 1 && !rooms[x][y]->upRoom) availableDirections.push_back({0, 1});
    if (x < SIZE - 1 && !rooms[x][y]->rightRoom) availableDirections.push_back({1, 0});
    if (y > 0 && !rooms[x][y]->downRoom) availableDirections.push_back({0, -1});
    if (x > 0 && !rooms[x][y]->leftRoom) availableDirections.push_back({-1, 0});
    
    if (!availableDirections.empty()) {
        auto dir = availableDirections[rand() % availableDirections.size()];
        connectTwoRooms(x, y, x + dir.first, y + dir.second);
    }
}

void Floor::displayFloor(){
    for (int j = SIZE - 1; j >= 0; j--) {
        for (int i = 0; i < 4; i++) {
            for (int l = 0; l < SIZE; l++) {
                if (j == SIZE - 1 && i == 0) {
                    std::cout << "____";
                }
                else if (i == 0) {
                    continue;
                }        
                else if (i == 1) {
                    std::cout << "|   ";
                }
                else if (i == 2) {
                    if (rooms[l][j]->leftRoom != nullptr    ) {
                        std::cout << "    ";
                    } else {
                        std::cout << "|   ";
                    }
                }
                else {
                    if (rooms[l][j]->downRoom != nullptr) {
                        std::cout << "|_ _";
                    } else {
                        std::cout << "|___";
                    }
                }
                if (l == SIZE - 1) {
                    if (i == 0 && j==SIZE-1) {
                        std::cout << std::endl;
                        continue;
                    }
                    std::cout << "|" << std::endl;
                }
            }
        }
    }
}

/*void Floor::displayFloor(){
    for (int j = SIZE - 1; j >= 0; j--) {
        for (int i = 0; i < SIZE; i++) {
            std::cout << "[R] ";
        }
        std::cout << std::endl;
    }
}
*/
