// Item.h
#pragma once
#include <string>

enum class ItemType {
    WEAPON,
    HEALTH_POTION,
    CHARM,
    ARTIFACT,
    MISC
};

class Item {
public:
    Item(const std::string &name, ItemType type, int value = 0);

    std::string getName() const;
    ItemType getType() const;
    int getValue() const;  // damage for a weapon, healing amount for potions, etc.

private:
    std::string name_;
    ItemType type_;
    int value_;
};
