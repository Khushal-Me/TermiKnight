// Player.h
// Now includes class types (Civilian, Bandit, Mage, Soldier).
// Stats: Health, Attack, Luck. Skills: unique special abilities.

#pragma once
#include <string>
#include "Inventory.h"

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
    ClassType getClassType() const;

    // Stats
    void setBaseStats(int health, int attack, int luck);
    int getHealth() const;
    int getAttack() const;
    int getLuck() const;

    void takeDamage(int dmg);
    void heal(int amount);
    void useSkill(); // Class-specific skill usage

    // Inventory & artifacts
    Inventory& getInventory();
    void showInventory() const;
    int getArtifactsCollected() const;
    void addArtifact();

private:
    ClassType classType_;
    int maxHealth_;
    int health_;
    int attack_;
    int luck_;
    int artifactsCollected_;

    Inventory inventory_;

    void applyClassBonuses(); 
};
