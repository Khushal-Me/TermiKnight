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
    bool removeIndex(size_t index);

    bool empty() const; 
    std::vector<Item>& getItems(); 

    nlohmann::json toJSON() const;
    void fromJSON(const nlohmann::json& jsonData);

private:
    std::vector<Item> items_;
};
