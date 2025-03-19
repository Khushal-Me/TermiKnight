/**
 * @file Inventory.h
 * @brief This file declares the Inventory class, which manages a collection of items.
 */

 #pragma once
 #include <vector>
 #include <string>
 #include "Item.h" 
 /**
  * @brief Represents the inventory of a character, capable of storing multiple items.
  */
 class Inventory {
 public:
     /**
      * @brief Adds an item to the inventory.
      * @param item The item to add.
      */
     void addItem(const Item &item);
 
     /**
      * @brief Removes the first occurrence of an item with the given name from the inventory.
      * @param itemName The name of the item to remove.
      * @return True if an item was found and removed, false otherwise.
      */
     bool removeItem(const std::string &itemName);
 
     /**
      * @brief Checks if the inventory contains at least one item with the given name.
      * @param itemName The name of the item to check for.
      * @return True if an item with the given name exists in the inventory, false otherwise.
      */
     bool hasItem(const std::string &itemName) const;
 
     /**
      * @brief Lists all items currently in the inventory to the standard output.
      */
     void listItems() const;
 
     /**
      * @brief Removes the item at the specified index from the inventory.
      * @param index The index of the item to remove.
      * @return True if the index was valid and the item was removed, false otherwise.
      */
     bool removeIndex(size_t index);
 
     /**
      * @brief Checks if the inventory is empty.
      * @return True if the inventory contains no items, false otherwise.
      */
     bool empty() const;
 
     /**
      * @brief Returns a reference to the underlying vector of items.
      * @return A reference to the vector of Item objects in the inventory.
      */
     std::vector<Item>& getItems();
 
     /**
      * @brief Converts the inventory to a JSON object.
      * @return A nlohmann::json object representing the inventory.
      */
     nlohmann::json toJSON() const;
 
     /**
      * @brief Populates the inventory from a JSON object.
      * @param jsonData The nlohmann::json object to load the inventory from.
      */
     void fromJSON(const nlohmann::json& jsonData);
 
 private:
     /**
      * @brief The vector storing the items in the inventory.
      */
     std::vector<Item> items_;
 };