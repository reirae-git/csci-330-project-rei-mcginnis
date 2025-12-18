#include "dungeon.hpp"

void Dungeon::generateNewFloor(){
    floor++;
    floors.push_back(Floor(floor));
}

Room* Dungeon::generateRandomRoom(int x, int y){
    int roomType = rand() % 100;
    if (roomType < 60) {
        return new BattleRoom(x,y);
    } else if (roomType < 80) {
        return new TreasureRoom(x,y);
    } else {
        return new TrapRoom(x,y);
    }
}

void Floor::generateRooms(){
    int xNum = rand() % 9;
    int yNum = rand() % 6 + 3;
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

void Floor::connectRooms(int x, int y){
    std::vector<std::vector<bool>> visited(SIZE, std::vector<bool>(SIZE, false));
    
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
    
    dfsBuildPath(x, y, bossRoom, visited);
    addSecondaryConnections(visited);
}

bool Floor::dfsBuildPath(int x, int y, Room* target, std::vector<std::vector<bool>>& visited) {
    visited[x][y] = true;
    
    if (rooms[x][y] == target) {
        return true;
    }
    
    std::vector<std::pair<int, int>> directions;
    if (y < SIZE - 1) directions.push_back({0, 1});
    if (x < SIZE - 1) directions.push_back({1, 0});
    if (y > 0) directions.push_back({0, -1});
    if (x > 0) directions.push_back({-1, 0});
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);
    
    for (auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        
        if (visited[newX][newY]) continue;
        
        connectTwoRooms(x, y, newX, newY);
        
        if (dfsBuildPath(newX, newY, target, visited)) {
            return true;
        }
    }
    
    return false;
}

void Floor::addSecondaryConnections(std::vector<std::vector<bool>>& visited) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!visited[i][j]) {
                connectIsolatedRoom(i, j, visited);
            }
            
            if (visited[i][j] && countConnections(i, j) == 1 && rand() % 100 < 30) {
                addRandomConnection(i, j);
            }
        }
    }
}

void Floor::connectTwoRooms(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    if (dx == 1) {
        rooms[x1][y1]->rightRoom = rooms[x2][y2];
        rooms[x2][y2]->leftRoom = rooms[x1][y1];
    } else if (dx == -1) {
        rooms[x1][y1]->leftRoom = rooms[x2][y2];
        rooms[x2][y2]->rightRoom = rooms[x1][y1];
    } else if (dy == 1) {
        rooms[x1][y1]->upRoom = rooms[x2][y2];
        rooms[x2][y2]->downRoom = rooms[x1][y1];
    } else if (dy == -1) {
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
                    if (rooms[l][j]->leftRoom != nullptr) {
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

// Room implementations
void StartRoom::enterRoom(PlayerCharacter* player) {
    if (cleared) return;
    printf("\n=== Starting Room ===\n");
    printf("You stand at the entrance of the dungeon. Your journey begins here.\n");
    cleared = true;
}

void BattleRoom::enterRoom(PlayerCharacter* player) {
    if (cleared) {
        printf("\n=== Empty Battle Room ===\n");
        printf("This room has already been cleared.\n");
        return;
    }
    printf("\n=== Battle Room ===\n");
    printf("You enter a dark room and hear growling...\n");
    
    Enemy* enemy = new Enemy(Enemy::generateRandomEnemy(0));
    Combat::startCombat(player, enemy);
    
    if (!player->dead) {
        cleared = true;
        int goldFound = rand() % 20 + 10;
        printf("You found %d gold!\n", goldFound);
        
        // 30% chance to drop a health potion
        if (rand() % 100 < 30) {
            printf("The enemy dropped something!\n");
            player->inventory.addItem(new HealthPotion());
        }
    }
    delete enemy;
}

void TreasureRoom::enterRoom(PlayerCharacter* player) {
    if (cleared) {
        printf("\n=== Empty Treasure Room ===\n");
        printf("The treasure chests here have already been looted.\n");
        return;
    }
    printf("\n=== Treasure Room ===\n");
    printf("You found a treasure chest!\n");
    
    int treasureType = rand() % 100;
    if (treasureType < 30) {
        // Gold
        int goldFound = rand() % 50 + 30;
        printf("You found %d gold!\n", goldFound);
    } else if (treasureType < 50) {
        // Health potion
        player->inventory.addItem(new HealthPotion());
    } else if (treasureType < 65) {
        // Mega potion
        player->inventory.addItem(new MegaPotion());
    } else if (treasureType < 75) {
        // Weapon
        int weaponRoll = rand() % 100;
        if (weaponRoll < 60) {
            player->inventory.addItem(new IronSword());
        } else if (weaponRoll < 90) {
            player->inventory.addItem(new SteelAxe());
        } else {
            player->inventory.addItem(new Excalibur());
        }
    } else if (treasureType < 85) {
        // Armor
        int armorRoll = rand() % 100;
        if (armorRoll < 60) {
            player->inventory.addItem(new LeatherArmor());
        } else if (armorRoll < 90) {
            player->inventory.addItem(new ChainMail());
        } else {
            player->inventory.addItem(new PlateArmor());
        }
    } else {
        // Magic item
        int magicRoll = rand() % 100;
        if (magicRoll < 60) {
            player->inventory.addItem(new ApprenticeStaff());
        } else if (magicRoll < 90) {
            player->inventory.addItem(new MasterStaff());
        } else {
            player->inventory.addItem(new ArcaneOrb());
        }
    }
    
    cleared = true;
}

void TrapRoom::enterRoom(PlayerCharacter* player) {
    if (cleared) {
        printf("\n=== Disabled Trap Room ===\n");
        printf("The traps here have been disarmed.\n");
        return;
    }
    printf("\n=== Trap Room ===\n");
    printf("You hear a clicking sound...\n");
    
    int trapType = rand() % 3;
    if (trapType == 0) {
        int damage = rand() % 15 + 10;
        printf("Spikes shoot from the walls! You take %d damage!\n", damage);
        player->loseHp(damage);
    } else if (trapType == 1) {
        int damage = rand() % 20 + 15;
        printf("A poison dart hits you! You take %d damage!\n", damage);
        player->loseHp(damage);
    } else {
        printf("You notice the trap just in time and avoid it!\n");
    }
    
    if (player->getCurrHp() <= 0) {
        printf("You succumbed to the traps...\n");
        player->dead = true;
    } else {
        printf("Current HP: %d/%d\n", player->getCurrHp(), player->getPlayerClass()->getMaxHp());
    }
    
    cleared = true;
}

void BossRoom::enterRoom(PlayerCharacter* player) {
    if (cleared) {
        printf("\n=== Conquered Boss Room ===\n");
        printf("The boss has been defeated. Peace fills this chamber.\n");
        return;
    }
    printf("\n=== BOSS ROOM ===\n");
    printf("You enter a massive chamber. A powerful presence awaits...\n");
    
    Enemy* boss = new Enemy("Boss", 150, 150, 25, 10);
    printf("\nThe Boss emerges from the shadows!\n");
    Combat::startCombat(player, boss);
    
    if (!player->dead) {
        cleared = true;
        printf("\n*** FLOOR COMPLETE! ***\n");
        printf("You have defeated the boss! You can now proceed to the next floor.\n");
        
        // Boss always drops good loot
        printf("\nThe boss dropped valuable items!\n");
        player->inventory.addItem(new MegaPotion());
        
        int lootRoll = rand() % 100;
        if (lootRoll < 40) {
            player->inventory.addItem(new SteelAxe());
        } else if (lootRoll < 70) {
            player->inventory.addItem(new ChainMail());
        } else if (lootRoll < 90) {
            player->inventory.addItem(new MasterStaff());
        } else {
            // Rare legendary drop
            int legendaryRoll = rand() % 3;
            if (legendaryRoll == 0) {
                player->inventory.addItem(new Excalibur());
            } else if (legendaryRoll == 1) {
                player->inventory.addItem(new PlateArmor());
            } else {
                player->inventory.addItem(new ArcaneOrb());
            }
        }
    }
    delete boss;
}

// Enemy implementations
Enemy::Enemy(const char* type, int health, int maxHealth, int dmg, int def) {
    strncpy(enemyType, type, sizeof(enemyType));
    enemyType[sizeof(enemyType) - 1] = '\0';
    hp = health;
    maxHp = maxHealth;
    damage = dmg;
    defense = def;
}

void Enemy::displayStats() const {
    printf("Enemy Type: %s\nHP: %d/%d\nDamage: %d\nDefense: %d\n", 
           enemyType, hp, maxHp, damage, defense);
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

Enemy Enemy::generateRandomEnemy(int level) {
    std::string enemies[] = {"Goblin", "Gnome", "Orc", "Kobold", "Thief", "Zombie"};
    int randomNumber = rand() % 6;
    std::string enemyName = enemies[randomNumber];
    int mult = 1 + level;
    
    if (enemyName == "Goblin") {
        return Enemy("Goblin", 50 * mult, 50 * mult, 10 * mult, 5 * mult);
    } else if (enemyName == "Gnome") {
        return Enemy("Gnome", 40 * mult, 40 * mult, 8 * mult, 3 * mult);
    } else if (enemyName == "Orc") {
        return Enemy("Orc", 80 * mult, 80 * mult, 15 * mult, 8 * mult);
    } else if (enemyName == "Kobold") {
        return Enemy("Kobold", 35 * mult, 35 * mult, 12 * mult, 2 * mult);
    } else if (enemyName == "Thief") {
        return Enemy("Thief", 45 * mult, 45 * mult, 14 * mult, 4 * mult);
    } else { // Zombie
        return Enemy("Zombie", 60 * mult, 60 * mult, 8 * mult, 6 * mult);
    }
}

// Combat implementations
void Combat::startCombat(PlayerCharacter *player, Enemy *enemy) {
    printf("\nA wild %s appears!\n", enemy->getEnemyType());
    enemy->displayStats();
    playerTurn(player, enemy);
}

void Combat::enemyTurn(PlayerCharacter *player, Enemy *enemy) {
    printf("\n--- Enemy's Turn ---\n");
    int baseDmg = enemy->getDamage();
    // Add randomness to enemy damage (50% to 100% of base damage)
    int minDmg = baseDmg / 2;
    int variance = baseDmg - minDmg + 1;
    int dmg = minDmg + (rand() % variance);
    
    int netDmg = dmg - player->getPlayerClass()->getDefense();
    if (netDmg < 1) netDmg = 1;  // Minimum 1 damage
    
    printf("The %s attacks you for %d damage!\n", enemy->getEnemyType(), netDmg);
    player->loseHp(netDmg);
    printf("Your HP: %d/%d\n", player->getCurrHp(), player->getPlayerClass()->getMaxHp());
    
    if (!isCombatOver(player, enemy)) {
        playerTurn(player, enemy);
    }
}

void Combat::playerTurn(PlayerCharacter *player, Enemy *enemy) {
    int choice;
    bool validInput = false;
    
    while (!validInput) {
        printf("\n--- Your Turn ---\n");
        printf("Enemy HP: %d/%d\n", enemy->getHp(), enemy->maxHp);
        printf("Your HP: %d/%d\n", player->getCurrHp(), player->getPlayerClass()->getMaxHp());
        printf("\nChoose an action:\n");
        printf("1. Attack\n");
        printf("2. Cast Spell\n");
        printf("Choice: ");
        
        if (std::cin >> choice) {
            if (choice == 1 || choice == 2) {
                validInput = true;
            } else {
                printf("Invalid choice. Please enter 1 or 2.\n");
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
    
    if (choice == 1) {
        int dmg = player->getPlayerClass()->attack();
        int netDmg = dmg - enemy->getDefense();
        if (netDmg < 1) netDmg = 1;  // Minimum 1 damage
        enemy->loseHp(netDmg);
        printf("You dealt %d damage to the %s!\n", netDmg, enemy->getEnemyType());
    } else if (choice == 2) {
        int spellDmg = player->getPlayerClass()->castSpell();
        int netDmg = spellDmg - enemy->getDefense();
        if (netDmg < 1) netDmg = 1;  // Minimum 1 damage
        enemy->loseHp(netDmg);
        printf("You dealt %d spell damage to the %s!\n", netDmg, enemy->getEnemyType());
    }
    
    if (!isCombatOver(player, enemy)) {
        enemyTurn(player, enemy);
    }
}

bool Combat::isCombatOver(PlayerCharacter *player, Enemy *enemy) {
    if (player->getCurrHp() <= 0) { 
        printf("\n*** YOU HAVE BEEN DEFEATED ***\n");
        printf("The %s has slain you...\n", enemy->getEnemyType());
        player->dead = true;
        return true;
    }
    if (enemy->getHp() <= 0) {   
        printf("\n*** VICTORY! ***\n");
        printf("You have defeated the %s!\n", enemy->getEnemyType());
        return true;
    }
    return false;
}