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
    for (const auto &itm : items_) {
        if (itm.getName() == itemName) {
            return true;
        }
    }
    return false;
}

void Inventory::listItems() const {
    if (items_.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }
    std::cout << "Inventory:\n";
    for (const auto &itm : items_) {
        std::cout << " - " << itm.getName() 
                  << " (" << itm.getTypeString() << ")\n";
    }
}

bool Inventory::empty() const {
    return items_.empty();
}

std::vector<Item>& Inventory::getItems() {
    return items_;
}

// Convert to JSON
nlohmann::json Inventory::toJSON() const {
    nlohmann::json jsonData;
    for (const auto& item : items_) {
        jsonData.push_back(item.toJSON());
    }
    return jsonData;
}

// Convert from JSON
void Inventory::fromJSON(const nlohmann::json& jsonData) {
    items_.clear();
    for (const auto& itemJson : jsonData) {
        items_.push_back(Item::fromJSON(itemJson));
    }
}