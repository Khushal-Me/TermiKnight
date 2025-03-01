// Player.cpp
#include "Player.h"

Player::Player()
    : classType_(ClassType::CIVILIAN),
      health_(100), maxHealth_(100),
      attack_(10), luck_(10),
      artifactsCollected_(0)
{
}

void Player::setClassType(ClassType type) {
    classType_ = type;
    applyClassBonuses(type);
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
    // Simple demonstration:
    switch (classType_) {
        case ClassType::CIVILIAN:
            // heal 50% 
            heal(maxHealth_ / 2);
            std::cout << "Civilian skill: You heal 50% of your max health.\n";
            break;
        case ClassType::BANDIT:
            std::cout << "Bandit skill: Higher chance of fleeing (currently not fully implemented).\n";
            break;
        case ClassType::MAGE: {
            std::cout << "Mage skill: 50% chance of instantly defeating the enemy (not fully implemented here).\n";
            break;
        }
        case ClassType::SOLDIER:
            std::cout << "Soldier skill: Next attack deals double damage (not fully implemented yet).\n";
            break;
    }
}

void Player::applyClassBonuses(ClassType type) {
    switch (type) {
        case ClassType::CIVILIAN:
            maxHealth_ = 100; health_ = 100; attack_ = 8;  luck_ = 15; break;
        case ClassType::BANDIT:
            maxHealth_ = 100; health_ = 100; attack_ = 14; luck_ = 5;  break;
        case ClassType::MAGE:
            maxHealth_ = 80;  health_ = 80;  attack_ = 18; luck_ = 10; break;
        case ClassType::SOLDIER:
            maxHealth_ = 120; health_ = 120; attack_ = 16; luck_ = 3;  break;
    }
}
