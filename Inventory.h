// Inventory.h
// Manages a collection of items.

#pragma once
#include "Item.h"
#include <vector>

class Inventory {
public:
    void addItem(const Item &item);
    bool removeItem(const std::string &itemName);
    bool hasItem(const std::string &itemName) const;
    void listItems() const;

private:
    std::vector<Item> items_;
};
