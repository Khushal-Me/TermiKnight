/**
 * @file Inventory.cpp
 * @brief This file implements the Inventory class, which manages a collection of items.
 */
#include "Inventory.h"
#include <iostream>
#include <sstream>


/**
 * @brief Adds an item to the inventory.
 *
 * @param item The item to add to the inventory.
 */
void Inventory::addItem(const Item &item) {
    items_.push_back(item);
}

/**
 * @brief Removes an item from the inventory by its name.
 *
 * Iterates through the inventory and removes the first item with the matching name.
 *
 * @param itemName The name of the item to remove.
 * @return True if an item with the given name was found and removed, false otherwise.
 */
bool Inventory::removeItem(const std::string &itemName) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (it->getName() == itemName) {
            items_.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the inventory contains an item with the given name.
 *
 * @param itemName The name of the item to check for.
 * @return True if an item with the given name is in the inventory, false otherwise.
 */
bool Inventory::hasItem(const std::string &itemName) const {
    for (const auto &itm : items_) {
        if (itm.getName() == itemName) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Lists all items currently in the inventory to the console.
 *
 * If the inventory is empty, it prints a message indicating that.
 */
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

/**
 * @brief Checks if the inventory is empty.
 *xx
 * @return True if the inventory contains no items, false otherwise.
 */
bool Inventory::empty() const {
    return items_.empty();
}

/**
 * @brief Gets a reference to the vector of items in the inventory.
 *
 * This allows direct access to the underlying item storage.
 *
 * @return A reference to the vector of Item objects.
 */
const std::vector<Item>& Inventory::getItems() const {
    return items_;
}


/**
 * @brief Removes an item from the inventory at a specific index.
 *
 * @param index The index of the item to remove.
 * @return True if the index is valid and the item was removed, false otherwise.
 */
bool Inventory::removeIndex(size_t index) {
    if (index >= items_.size()) return false;
    items_.erase(items_.begin() + index);
    return true;
}

/**
 * @brief Converts the inventory to a JSON representation.
 *
 * Each item in the inventory is converted to its JSON form and added to a JSON array.
 *
 * @return A nlohmann::json object representing the inventory.
 */
nlohmann::json Inventory::toJSON() const {
    nlohmann::json jsonData;
    for (const auto& item : items_) {
        jsonData.push_back(item.toJSON());
    }
    return jsonData;
}

/**
 * @brief Populates the inventory from a JSON representation.
 *
 * Clears the current inventory and then creates Item objects from each JSON object in the input array.
 *
 * @param jsonData A constant reference to the nlohmann::json object representing the inventory.
 */
void Inventory::fromJSON(const nlohmann::json& jsonData) {
    items_.clear();
    for (const auto& itemJson : jsonData) {
        items_.push_back(Item::fromJSON(itemJson));
    }
}


/**
 * @brief Generates a list of formatted strings representing the inventory contents.
 *
 * The first line is a header ("=== Inventory ===").
 * If the inventory is empty, the next line will say "Empty".
 * Otherwise, each item is listed on its own line with a number and its name.
 *
 * @return A vector of strings, each representing one line of formatted inventory output.
 */
std::vector<std::string> Inventory::getFormattedLines() const {
    std::vector<std::string> lines;
    lines.push_back("=== Inventory ===");
    const std::vector<Item>& items = getItems();
    if (items.empty()) {
        lines.push_back("Empty");
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::ostringstream oss;
            oss << (i+1) << ") " << items[i].getName();
            lines.push_back(oss.str());
        }
    }
    return lines;
}
