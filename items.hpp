// items.hpp
#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <cstdio>
#include <cstring>
#include <vector>

// Forward declaration to avoid circular dependency
class PlayerCharacter;

enum ItemType {
    CONSUMABLE,
    WEAPON,
    ARMOR,
    ACCESSORY
};

class Item {
public:
    char name[50];
    char description[200];
    ItemType type;
    
    Item(const char* itemName, const char* desc, ItemType itemType) {
        strncpy(name, itemName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        strncpy(description, desc, sizeof(description) - 1);
        description[sizeof(description) - 1] = '\0';
        type = itemType;
    }
    
    virtual void use(PlayerCharacter* player) = 0;
    virtual void displayInfo() const {
        printf("%s - %s\n", name, description);
    }
    virtual ~Item() {}
};

// Consumables
class HealthPotion : public Item {
public:
    int healAmount;
    
    HealthPotion(int amount = 50) : Item("Health Potion", "Restores HP", CONSUMABLE) {
        healAmount = amount;
        snprintf(description, sizeof(description), "Restores %d HP", healAmount);
    }
    
    void use(PlayerCharacter* player) override;
};

class MegaPotion : public Item {
public:
    int healAmount;
    
    MegaPotion() : Item("Mega Potion", "Restores 100 HP", CONSUMABLE) {
        healAmount = 100;
    }
    
    void use(PlayerCharacter* player) override;
};

// Weapons
class Weapon : public Item {
public:
    int damageBonus;
    
    Weapon(const char* weaponName, const char* desc, int bonus) 
        : Item(weaponName, desc, WEAPON), damageBonus(bonus) {}
    
    void use(PlayerCharacter* player) override;
};

class IronSword : public Weapon {
public:
    IronSword() : Weapon("Iron Sword", "A sturdy iron blade (+5 damage)", 5) {}
};

class SteelAxe : public Weapon {
public:
    SteelAxe() : Weapon("Steel Axe", "A heavy battle axe (+8 damage)", 8) {}
};

class Excalibur : public Weapon {
public:
    Excalibur() : Weapon("Excalibur", "A legendary holy sword (+15 damage)", 15) {}
};

// Magic items (boost spell damage)
class MagicItem : public Item {
public:
    int magikaBonus;
    
    MagicItem(const char* itemName, const char* desc, int bonus)
        : Item(itemName, desc, ACCESSORY), magikaBonus(bonus) {}
    
    void use(PlayerCharacter* player) override;
};

class ApprenticeStaff : public MagicItem {
public:
    ApprenticeStaff() : MagicItem("Apprentice Staff", "A basic magic staff (+5 magika)", 5) {}
};

class MasterStaff : public MagicItem {
public:
    MasterStaff() : MagicItem("Master Staff", "A powerful wizard's staff (+10 magika)", 10) {}
};

class ArcaneOrb : public MagicItem {
public:
    ArcaneOrb() : MagicItem("Arcane Orb", "A mystical orb of power (+15 magika)", 15) {}
};

// Armor
class Armor : public Item {
public:
    int defenseBonus;
    
    Armor(const char* armorName, const char* desc, int bonus)
        : Item(armorName, desc, ARMOR), defenseBonus(bonus) {}
    
    void use(PlayerCharacter* player) override;
};

class LeatherArmor : public Armor {
public:
    LeatherArmor() : Armor("Leather Armor", "Light but sturdy (+3 defense)", 3) {}
};

class ChainMail : public Armor {
public:
    ChainMail() : Armor("Chain Mail", "Strong metal armor (+6 defense)", 6) {}
};

class PlateArmor : public Armor {
public:
    PlateArmor() : Armor("Plate Armor", "Heavy protective armor (+10 defense)", 10) {}
};

// Inventory system
class Inventory {
public:
    std::vector<Item*> items;
    Item* equippedWeapon;
    Item* equippedArmor;
    Item* equippedAccessory;
    
    Inventory() : equippedWeapon(nullptr), equippedArmor(nullptr), equippedAccessory(nullptr) {}
    
    void addItem(Item* item) {
        items.push_back(item);
        printf("Added %s to inventory!\n", item->name);
    }
    
    void displayInventory() const {
        printf("\n=== INVENTORY ===\n");
        if (items.empty()) {
            printf("Empty\n");
            return;
        }
        
        for (size_t i = 0; i < items.size(); i++) {
            printf("%zu. ", i + 1);
            items[i]->displayInfo();
        }
        
        printf("\n--- EQUIPPED ---\n");
        if (equippedWeapon) printf("Weapon: %s\n", equippedWeapon->name);
        if (equippedArmor) printf("Armor: %s\n", equippedArmor->name);
        if (equippedAccessory) printf("Accessory: %s\n", equippedAccessory->name);
    }
    
    Item* getItem(int index) {
        if (index >= 0 && index < (int)items.size()) {
            return items[index];
        }
        return nullptr;
    }
    
    void removeItem(int index) {
        if (index >= 0 && index < (int)items.size()) {
            items.erase(items.begin() + index);
        }
    }
    
    ~Inventory() {
        // Don't delete equipped items, they're in the items vector
        for (Item* item : items) {
            delete item;
        }
    }
};

#endif // ITEMS_HPP