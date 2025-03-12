// Player.cpp
#include "Player.h"

using namespace std;

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
    cout << "Your health is at: " << health_ << "/" << maxHealth_ << endl;
}

int Player::useSkill() {
    // Simple demonstration:
    switch (classType_) {
        case ClassType::CIVILIAN:
            // heal 50% 
            heal(maxHealth_ / 2);
            std::cout << "Civilian skill: You heal 50% of your max health.\n";
            return 1;
            break;
        case ClassType::BANDIT:
            std::cout << "Bandit skill: Higher chance of fleeing.\n";
            return 2;
            break;
        case ClassType::MAGE: {
            std::cout << "Mage skill: 50% chance of instantly defeating the enemy.\n";
            return 3;
            break;
        }
        case ClassType::SOLDIER:
            std::cout << "Soldier skill: Next attack deals double damage.\n";
            return 4;
            break;
    }
}

void Player::applyClassBonuses(ClassType type) {
    switch (type) {
        case ClassType::CIVILIAN: {
            maxHealth_ = 100; health_ = 100; attack_ = 8;  luck_ = 15; break;
        }
        case ClassType::BANDIT:{
            maxHealth_ = 100; health_ = 100; attack_ = 14; luck_ = 10;  break;
        }
        case ClassType::MAGE: {
            maxHealth_ = 80;  health_ = 80;  attack_ = 18; luck_ = 10; break;
        }
        case ClassType::SOLDIER: {
            maxHealth_ = 120; health_ = 120; attack_ = 16; luck_ = 3;  break;
        }
    }
}

nlohmann::json Player::toJSON() const {
    return {
        {"class", static_cast<int>(classType_)},
        {"health", health_},
        {"attack", attack_},
        {"luck", luck_},
        {"artifacts_collected", artifactsCollected_},
        {"inventory", inventory_.toJSON()}
    };
}

void Player::fromJSON(const nlohmann::json& data) {
    classType_ = static_cast<ClassType>(data["class"].get<int>());
    health_ = data["health"];
    attack_ = data["attack"];
    luck_ = data["luck"];
    artifactsCollected_ = data["artifacts_collected"];
    inventory_.fromJSON(data["inventory"]);
}
