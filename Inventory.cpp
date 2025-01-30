// Inventory.cpp
#include "Inventory.h"
#include <iostream>

void Inventory::addItem(const Item &item) {
    items_.push_back(item);
}

bool Inventory::removeItem(const std::string &itemName) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (it->getName() == itemName) {
            items_.erase(it);
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(const std::string &itemName) const {
    for (const auto &i : items_) {
        if (i.getName() == itemName) return true;
    }
    return false;
}

void Inventory::listItems() const {
    std::cout << "Inventory:\n";
    for (const auto &i : items_) {
        std::cout << "- " << i.getName() << "\n";
    }
}
