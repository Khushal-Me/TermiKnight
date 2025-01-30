// Player.cpp

#include "Player.h"
#include <iostream>

Player::Player()
    : classType_(ClassType::CIVILIAN), 
      maxHealth_(100), health_(100), attack_(10), luck_(10),
      artifactsCollected_(0) {}

void Player::setClassType(ClassType type) {
    classType_ = type;
    applyClassBonuses(); 
}

ClassType Player::getClassType() const {
    return classType_;
}

void Player::setBaseStats(int health, int attack, int luck) {
    maxHealth_ = health;
    health_ = health;
    attack_ = attack;
    luck_ = luck;
}

int Player::getHealth() const {
    return health_;
}

int Player::getAttack() const {
    return attack_;
}

int Player::getLuck() const {
    return luck_;
}

void Player::takeDamage(int dmg) {
    health_ -= dmg;
    if (health_ < 0) health_ = 0;
}

void Player::heal(int amount) {
    health_ += amount;
    if (health_ > maxHealth_) health_ = maxHealth_;
}

void Player::useSkill() {
    // Each class has a unique skill
    switch (classType_) {
        case ClassType::CIVILIAN:
            // e.g., heal 50% of max health
            std::cout << "CIVILIAN skill used: healing 50%...\n";
            heal(maxHealth_ / 2);
            break;
        case ClassType::BANDIT:
            // higher chance of fleeing -> could handle in combat logic
            std::cout << "BANDIT skill might be triggered in flee attempts.\n";
            break;
        case ClassType::MAGE:
            // 50/50 chance to instantly kill
            std::cout << "MAGE skill used: attempting one-shot kill.\n";
            break;
        case ClassType::SOLDIER:
            // double damage next attack
            std::cout << "SOLDIER skill used: double damage next attack!\n";
            break;
    }
}

Inventory& Player::getInventory() {
    return inventory_;
}

void Player::showInventory() const {
    inventory_.listItems();
}

int Player::getArtifactsCollected() const {
    return artifactsCollected_;
}

void Player::addArtifact() {
    artifactsCollected_++;
}

void Player::applyClassBonuses() {
    // Adjust stats based on class
    switch (classType_) {
        case ClassType::CIVILIAN:
            setBaseStats(100, 8, 15);    // More luck, base health, less attack
            break;
        case ClassType::BANDIT:
            setBaseStats(100, 14, 5);   // Base health, higher attack, low luck
            break;
        case ClassType::MAGE:
            setBaseStats(80, 18, 10);   // Less health, high attack, base luck
            break;
        case ClassType::SOLDIER:
            setBaseStats(120, 16, 3);   // High health, high attack, low luck
            break;
    }
}
