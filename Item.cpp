/**
 * @file item.cpp
 * @brief Implements the Item class, which represents a collectible or usable object in the game.
 */
#include "Item.h"

/**
 * @brief Constructs a new Item with a given name, type, and value.
 * 
 * @param name  The display name of the item (e.g., "Rusted Sword").
 * @param type  The category of the item (Weapon, Health Potion, etc.).
 * @param value An integer that may represent attack bonus (for weapons), healing amount (for potions), etc.
 */
Item::Item(const std::string &name, ItemType type, int value)
    : name_(name), type_(type), value_(value) {
}
/**
 * @brief Retrieves the name of this Item.
 * 
 * @return A string representing the item's name.
 */
std::string Item::getName() const {
    return name_;
}
/**
 * @brief Retrieves the type (category) of this Item.
 * 
 * @return An ItemType enum indicating whether it's a weapon, potion, etc.
 */
ItemType Item::getType() const {
    return type_;
}
/**
 * @brief Retrieves the integral value for this Item.
 * 
 * @return An integer representing damage bonus, healing amount, or other stat effect.
 */
int Item::getValue() const {
    return value_;
}

/**
 * @brief Converts the ItemType enum to a readable string.
 * 
 * @return A human-readable string indicating the item's category (e.g., "Weapon", "Health Potion").
 */
std::string Item::getTypeString() const {
    switch (type_) {
        case ItemType::WEAPON:        return "Weapon";
        case ItemType::HEALTH_POTION: return "Health Potion";
        case ItemType::CHARM:         return "Charm";
        case ItemType::ARTIFACT:      return "Artifact";
        default:                      return "Misc";
    }
}

/**
 * @brief Serializes this Item to a JSON object.
 * 
 * @return A nlohmann::json representation, containing the item's name, type (as int), and value.
 */
nlohmann::json Item::toJSON() const {
    return {
        {"name", name_},
        {"type", static_cast<int>(type_)},  // Store type as int
        {"value", value_}
    };
}

/**
 * @brief Constructs an Item from a JSON object.
 * 
 * @param jsonData A nlohmann::json object containing "name", "type", and "value".
 * @return A fully initialized Item instance.
 */
Item Item::fromJSON(const nlohmann::json& jsonData) {
    return Item(
        jsonData["name"].get<std::string>(),
        static_cast<ItemType>(jsonData["type"].get<int>()),
        jsonData["value"].get<int>()
    );
}
