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
    // Declaration only
    Item(const std::string &name, ItemType type, int value = 0);

    std::string getName() const;
    ItemType getType() const;
    int getValue() const;
    std::string getTypeString() const;

private:
    std::string name_;
    ItemType type_;
    int value_;
};
