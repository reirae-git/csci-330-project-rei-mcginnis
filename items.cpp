#include "items.hpp"
#include "player.hpp"

void HealthPotion::use(PlayerCharacter* player) {
    printf("You drink the Health Potion!\n");
    player->gainHp(healAmount);
    printf("Restored %d HP! Current HP: %d/%d\n", 
           healAmount, player->getCurrHp(), player->getPlayerClass()->getMaxHp());
}

void MegaPotion::use(PlayerCharacter* player) {
    printf("You drink the Mega Potion!\n");
    player->gainHp(healAmount);
    printf("Restored %d HP! Current HP: %d/%d\n", 
           healAmount, player->getCurrHp(), player->getPlayerClass()->getMaxHp());
}

void Weapon::use(PlayerCharacter* player) {
    // Unequip old weapon if exists
    if (player->inventory.equippedWeapon) {
        Weapon* oldWeapon = dynamic_cast<Weapon*>(player->inventory.equippedWeapon);
        if (oldWeapon) {
            player->getPlayerClass()->damage -= oldWeapon->damageBonus;
            printf("Unequipped %s\n", oldWeapon->name);
        }
    }
    
    // Equip new weapon
    player->inventory.equippedWeapon = this;
    player->getPlayerClass()->damage += damageBonus;
    printf("Equipped %s! Damage increased by %d\n", name, damageBonus);
}

void MagicItem::use(PlayerCharacter* player) {
    // Unequip old accessory if exists
    if (player->inventory.equippedAccessory) {
        MagicItem* oldItem = dynamic_cast<MagicItem*>(player->inventory.equippedAccessory);
        if (oldItem) {
            player->getPlayerClass()->magika -= oldItem->magikaBonus;
            printf("Unequipped %s\n", oldItem->name);
        }
    }
    
    // Equip new accessory
    player->inventory.equippedAccessory = this;
    player->getPlayerClass()->magika += magikaBonus;
    printf("Equipped %s! Magika increased by %d\n", name, magikaBonus);
}

void Armor::use(PlayerCharacter* player) {
    // Unequip old armor if exists
    if (player->inventory.equippedArmor) {
        Armor* oldArmor = dynamic_cast<Armor*>(player->inventory.equippedArmor);
        if (oldArmor) {
            player->getPlayerClass()->defense -= oldArmor->defenseBonus;
            printf("Unequipped %s\n", oldArmor->name);
        }
    }
    
    // Equip new armor
    player->inventory.equippedArmor = this;
    player->getPlayerClass()->defense += defenseBonus;
    printf("Equipped %s! Defense increased by %d\n", name, defenseBonus);
}