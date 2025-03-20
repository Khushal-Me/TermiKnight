/**
 * @file Player.cpp
 * @brief Implements the Player class, which represents the game’s main character controlled by the user.
 */

#include "Player.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructs a default Player with CIVILIAN class stats and initial values.
 *
 * Initializes health, maxHealth, attack, luck, baseAttack, weaponBonus,
 * and artifactsCollected to default values.
 */
Player::Player()
    : classType_(ClassType::CIVILIAN),
      health_(100), maxHealth_(100),
      attack_(10), luck_(10),
      baseAttack_(10),
      weaponBonus_(0),
      artifactsCollected_(0)
{
}

/**
 * @brief Equips a weapon that increases the player's Attack by a specified bonus.
 *
 * This method sets the player's weaponBonus_ to the given bonus and
 * recalculates the final attack value via updateAttack().
 *
 * @param bonus An integer representing the weapon's attack bonus.
 */
void Player::equipWeapon(int bonus) {
    std::cout << "Equipping weapon with bonus: " << bonus << "\n";
    weaponBonus_ = bonus;
    updateAttack();
}

/**
 * @brief Updates the player's final Attack value by adding baseAttack_ and weaponBonus_.
 *
 * This is called whenever the player's class or equipped weapon changes.
 * The final attack_ is set to (baseAttack_ + weaponBonus_).
 */
void Player::updateAttack() {
    attack_ = baseAttack_ + weaponBonus_;
}

/**
 * @brief Assigns a new class type to the player and applies corresponding stat bonuses.
 *
 * @param type The new ClassType (e.g., CIVILIAN, BANDIT, MAGE, SOLDIER).
 */
void Player::setClassType(ClassType type) {
    classType_ = type;
    applyClassBonuses(type);
}

/**
 * @brief Reduces the player's health by a given amount of damage.
 *
 * @param dmg The amount of damage the player takes.
 */
void Player::takeDamage(int dmg) {
    health_ -= dmg;
    if (health_ < 0) health_ = 0;
}

/**
 * @brief Restores the player's health by a given amount, not exceeding maxHealth.
 *
 * @param amount The amount of health to restore.
 */
void Player::heal(int amount) {
    health_ += amount;
    if (health_ > maxHealth_) health_ = maxHealth_;
    cout << "Your health is at: " << health_ << "/" << maxHealth_ << endl;
}

/**
 * @brief Activates the player's class-specific skill.
 *
 * Skills vary by class:
 * - CIVILIAN heals 50% of max health.
 * - BANDIT improves next flee chance.
 * - MAGE has a 50% chance to instantly defeat an enemy.
 * - SOLDIER doubles the damage on the next attack.
 *
 * @return An integer code indicating which skill was used:
 *         1 = CIVILIAN, 2 = BANDIT, 3 = MAGE, 4 = SOLDIER.
 */
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

/**
 * @brief Applies stat bonuses and maximum health adjustments based on the player's class.
 *
 * This method is called when the player's class type is changed. It resets
 * the weapon bonus to 0 and recalculates the final attack using updateAttack().
 *
 * @param type The new ClassType being applied.
 */
void Player::applyClassBonuses(ClassType type) {
    switch (type) {
        case ClassType::CIVILIAN: {
            maxHealth_ = 100; health_ = 100; baseAttack_ = 8;  luck_ = 15; break;
        }
        case ClassType::BANDIT:{
            maxHealth_ = 100; health_ = 100; baseAttack_ = 14; luck_ = 10;  break;
        }
        case ClassType::MAGE: {
            maxHealth_ = 80;  health_ = 80;  baseAttack_ = 18; luck_ = 10; break;
        }
        case ClassType::SOLDIER: {
            maxHealth_ = 120; health_ = 120; baseAttack_ = 16; luck_ = 3;  break;
        }
    }
    weaponBonus_ = 0;
    updateAttack(); 
}

/**
 * @brief Serializes the player's data into a JSON object for saving.
 *
 * This includes the player's class, current health, attack, luck, collected artifacts,
 * and inventory contents.
 *
 * @return A nlohmann::json object representing the player's current state.
 */
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

/**
 * @brief Restores the player's state from a JSON object.
 *
 * This updates classType_, health, attack, luck, artifactsCollected, and the player's inventory
 * based on the provided JSON data.
 *
 * @param data A nlohmann::json object previously generated by Player::toJSON().
 */
void Player::fromJSON(const nlohmann::json& data) {
    classType_ = static_cast<ClassType>(data["class"].get<int>());
    health_ = data["health"];
    attack_ = data["attack"];
    luck_ = data["luck"];
    artifactsCollected_ = data["artifacts_collected"];
    inventory_.fromJSON(data["inventory"]);
}
