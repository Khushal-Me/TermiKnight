#include "Item.h"

Item::Item(const std::string &name, ItemType type, int value)
    : name_(name), type_(type), value_(value) {
}

std::string Item::getName() const {
    return name_;
}

ItemType Item::getType() const {
    return type_;
}

int Item::getValue() const {
    return value_;
}

std::string Item::getTypeString() const {
    switch (type_) {
        case ItemType::WEAPON:        return "Weapon";
        case ItemType::HEALTH_POTION: return "Health Potion";
        case ItemType::CHARM:         return "Charm";
        case ItemType::ARTIFACT:      return "Artifact";
        default:                      return "Misc";
    }
}

nlohmann::json Item::toJSON() const {
    return {
        {"name", name_},
        {"type", static_cast<int>(type_)},  // Store type as int
        {"value", value_}
    };
}

// Convert from JSON
Item Item::fromJSON(const nlohmann::json& jsonData) {
    return Item(
        jsonData["name"].get<std::string>(),
        static_cast<ItemType>(jsonData["type"].get<int>()),
        jsonData["value"].get<int>()
    );
}
