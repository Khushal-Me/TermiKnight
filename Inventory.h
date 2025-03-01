// Inventory.h
#pragma once
#include <vector>
#include <string>
#include "Item.h"

class Inventory {
public:
    void addItem(const Item &item);
    bool removeItem(const std::string &itemName);
    bool hasItem(const std::string &itemName) const;
    void listItems() const;

    bool empty() const; // newly added
    std::vector<Item>& getItems(); // newly added

private:
    std::vector<Item> items_;
};
