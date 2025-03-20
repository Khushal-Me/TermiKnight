/**
 * @file Player.h
 * @brief Declares the Player class, representing the main character and their stats, inventory, and abilities.
 */
#pragma once
#include <string>
#include <iostream>
#include "Inventory.h"

/**
 * @enum ClassType
 * @brief Enumerates the possible classes a player can choose.
 *
 * Classes affect base stats and grant unique skills:
 * - CIVILIAN: Higher luck, moderate stats, can heal 50%.
 * - BANDIT: Higher damage, improved flee chances.
 * - MAGE: High damage but lower health, 50% chance to one-shot.
 * - SOLDIER: High health and damage, next attack can be doubled.
 */
enum class ClassType {
    CIVILIAN,
    BANDIT,
    MAGE,
    SOLDIER
};

/**
 * @class Player
 * @brief Represents the player's character, storing health, attack, luck, inventory, and class-specific logic.
 *
 * The Player can equip weapons (increasing Attack), use potions, 
 * and activate class-specific skills during combat. The class 
 * also manages saving/loading of the player's data via JSON.
 */
class Player {
public:
    /**
     * @brief Constructs a Player with default (CIVILIAN) stats and initial values.
     */
    Player();

    /**
     * @brief Changes the player's class and applies relevant stat changes.
     * @param type The ClassType to switch to (CIVILIAN, BANDIT, MAGE, SOLDIER).
     */
    void setClassType(ClassType type);


    /**
     * @brief Retrieves the player's current class type.
     * @return The ClassType enum representing the player's class.
     */
    ClassType getClassType() const { return classType_; }

    /**
     * @brief Gets the player's current health.
     * @return An integer representing HP.
     */
    int getHealth() const { return health_; }

    /**
     * @brief Gets the player's current attack value.
     *
     * This is the final attack after combining baseAttack_ and any weapon bonuses.
     * @return The player's final attack stat.
     */
    int getAttack() const { return attack_; }

     /**
     * @brief Retrieves the player's luck stat.
     * @return An integer representing how luck influences certain actions (like fleeing).
     */
    int getLuck()   const { return luck_; }

    /**
     * @brief Manually sets the player's health.
     * @param h The new health value.
     */
    void setHealth(int h) { health_ = h; }

    /**
     * @brief Decreases the player's health by the given damage.
     * @param dmg The amount of damage to apply.
     */
    void takeDamage(int dmg);

    /**
     * @brief Heals the player by a specified amount, not exceeding maxHealth_.
     * @param amount The HP to restore.
     */
    void heal(int amount);

    /**
     * @brief Activates the player's class-specific skill.
     *
     * @return An integer code (1=CIVILIAN, 2=BANDIT, 3=MAGE, 4=SOLDIER) 
     *         indicating which skill was used.
     */
    int useSkill(); // triggers class skill

    /**
     * @brief Displays all items in the player's inventory.
     */
    void showInventory() const { inventory_.listItems(); }

     /**
     * @brief Provides access to the player's Inventory object for further manipulation.
     * @return A reference to the player's Inventory.
     */
    Inventory& getInventory() { return inventory_; }

    /**
     * @brief Increments the count of artifacts collected by the player.
     */
    void addArtifact() { artifactsCollected_++; }

    /**
     * @brief Retrieves the total number of artifacts the player has collected.
     * @return An integer representing how many artifacts the player holds.
     */
    int  getArtifactsCollected() const { return artifactsCollected_; }

    /**
     * @brief Equips a weapon, adding its bonus to the player's attack.
     * @param bonus The bonus attack value to add.
     */
    void equipWeapon(int bonus);

    /**
     * @brief Serializes the player's data into a JSON object for saving.
     * @return A nlohmann::json object representing the player's current state.
     */
    nlohmann::json toJSON() const;

    /**
     * @brief Deserializes a JSON object into the player's data for loading.
     * @param data The JSON object to read from.
     */
    void fromJSON(const nlohmann::json& data);

private:
    ClassType classType_;        ///< The player's class type
    int health_;                 ///< The player's current health
    int maxHealth_;              ///< The player's maximum health
    int attack_;                 ///< The player's final attack value (base + weapon)
    int luck_;                   ///< The player's luck stat (influences certain actions)
    int artifactsCollected_;     ///< The number of quest artifacts collected

    int baseAttack_;             ///< The player's base attack value
    int weaponBonus_;            ///< The bonus attack from equipped weapons 

    Inventory inventory_;        ///< The player's inventory of items

    
    /**
     * @brief Recalculates the player's final Attack after changes to baseAttack_ or weaponBonus_.
     */
    void updateAttack();

    /**
     * @brief Applies stat bonuses and maximum health adjustments based on the player's class.
     * @param type The new ClassType being applied.
     */
    void applyClassBonuses(ClassType type);
};
