// Item.cpp
#include "Item.h"

Item::Item(const std::string &name, ItemType type, int value)
    : name_(name), type_(type), value_(value) {}

std::string Item::getName() const {
    return name_;
}

ItemType Item::getType() const {
    return type_;
}

int Item::getValue() const {
    return value_;
}
