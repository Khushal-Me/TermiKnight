// Player.h
#pragma once
#include <string>
#include <iostream>
#include "Inventory.h"

// Basic enum for class type
enum class ClassType {
    CIVILIAN,
    BANDIT,
    MAGE,
    SOLDIER
};

class Player {
public:
    Player();

    void setClassType(ClassType type);
    ClassType getClassType() const { return classType_; }

    int getHealth() const { return health_; }
    int getAttack() const { return attack_; }
    int getLuck()   const { return luck_; }
    void setHealth(int h) { health_ = h; }
    void takeDamage(int dmg);
    void heal(int amount);
    void useSkill(); // triggers class skill

    void showInventory() const { inventory_.listItems(); }
    Inventory& getInventory() { return inventory_; }

    void addArtifact() { artifactsCollected_++; }
    int  getArtifactsCollected() const { return artifactsCollected_; }

private:
    ClassType classType_;
    int health_;
    int maxHealth_;
    int attack_;
    int luck_;
    int artifactsCollected_;
    Inventory inventory_;

    void applyClassBonuses(ClassType type);
};
