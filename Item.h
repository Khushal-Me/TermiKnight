/**
 * @file item.h
 * @brief Defines the Item class and its related enumerations, representing
 *        various objects (weapons, potions, artifacts, etc.) within the game.
 */
#pragma once
#include <string>
#include "external/json/json.hpp"


/**
 * @enum ItemType
 * @brief An enumeration of possible item categories within the game.
 *
 * Each ItemType indicates how the item behaves or is used:
 * - WEAPON: Increases player Attack when equipped.
 * - HEALTH_POTION: Restores player HP when consumed.
 * - CHARM: Could grant extra luck or other stat boosts.
 * - ARTIFACT: Main quest items typically used to progress the story.
 * - MISC: Any other items not fitting the above categories.
 */
enum class ItemType {
    WEAPON,
    HEALTH_POTION,
    CHARM,
    ARTIFACT,
    MISC
};


/**
 * @class Item
 * @brief Represents a single in-game object that can be carried or used by the player.
 *
 * Items can be consumables (like potions) or equipable (like weapons). 
 * Each Item has a name, a type, and an integer value that typically denotes
 * how much it heals for (if a potion) or how much attack bonus it provides (if a weapon).
 */
class Item {
public:
     /**
     * @brief Constructs an Item with a specified name, type, and value.
     *
     * @param name  A display name for the item (e.g., "Rusted Sword").
     * @param type  The category (ItemType) of this item.
     * @param value The numeric value associated with the item. For example,
     *             weapon bonus damage, potion healing amount, etc.
     */
    Item(const std::string &name, ItemType type, int value = 0);

    /**
     * @brief Retrieves the name of this item.
     * @return A std::string representing the item's name.
     */
    std::string getName() const;

    /**
     * @brief Retrieves the type/category of this item.
     * @return An ItemType enum, indicating whether it's a WEAPON, HEALTH_POTION, etc.
     */
    ItemType getType() const;

     /**
     * @brief Retrieves the numeric value associated with this item.
     * @return An integer, often representing damage bonus or healing amount.
     */
    int getValue() const;

     /**
     * @brief Provides a human-readable label for the item's type.
     * @return A std::string such as "Weapon", "Health Potion", etc.
     */
    std::string getTypeString() const;

    /**
     * @brief Serializes this Item to a JSON object for saving or data transfer.
     * @return A nlohmann::json object containing the item's fields.
     */
    nlohmann::json toJSON() const;

    /**
     * @brief Creates an Item instance from a JSON object.
     *
     * @param jsonData A nlohmann::json structure containing "name", "type", and "value".
     * @return A fully constructed Item based on the data in jsonData.
     */
    static Item fromJSON(const nlohmann::json& jsonData);

private:
    std::string name_;      ///< The item's display name.
    ItemType type_;         ///< The category/type of the item.
    int value_;             ///< The integer value representing damage, healing, etc.
};          
