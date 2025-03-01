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
