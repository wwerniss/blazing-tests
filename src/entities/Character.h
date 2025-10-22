#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../items/Item.h"

// Forward declarations
class Item;
class Weapon;

// Base Character class
class Character {
protected:
    std::string name;
    int level;
    int health;
    int maxHealth;
    int baseAttack;
    int attack;
    int defense;
    std::vector<std::shared_ptr<Item>> inventory;
    std::shared_ptr<Weapon> equippedWeapon;
    
public:
    Character(const std::string& n, int lvl, int hp, int atk, int def);
    virtual ~Character() = default;
    
    virtual void attackTarget(Character& target);
    void takeDamage(int amount);
    void heal(int amount);
    bool isAlive() const;
    
    void addItem(std::shared_ptr<Item> item);
    void showStatus() const;
    
    // Weapon methods
    void equipWeapon(std::shared_ptr<Weapon> weapon);
    void unequipWeapon();
    bool hasWeaponEquipped() const;
    
    // Getters
    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getDefense() const;
    std::string getEquippedWeaponName() const;
    const std::vector<std::shared_ptr<Item>>& getInventory() const { return inventory; }
    std::vector<std::shared_ptr<Item>>& getInventory() { return inventory; }
    
    virtual std::string getClassName() const = 0;
};
