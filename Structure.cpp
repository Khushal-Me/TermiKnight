/**
 * @file Structure.cpp
 * @brief Implements the Structure class for handling exploration, enemies, and riddles.
 */

#include "Structure.h"
#include "CombatManager.h"
#include <iostream>
#include <cstdlib>
#include <limits>

/**
 * @brief Constructs a Structure with a specified type and number of rooms.
 * @param type The type of the structure.
 * @param totalRooms The total number of rooms in the structure.
 */
Structure::Structure(StructureType type, int totalRooms)
    : type_(type),
      totalRooms_(totalRooms),
      currentRoomIndex_(0),
      fullyExplored_(false),
      foundArtifactThisRoom_(false)
{
    initRiddles();
    int r = std::rand() % riddlePool_.size();
    riddleToAsk_ = riddlePool_[r];
}

/**
 * @brief Retrieves the structure's type as a string.
 * @return The type of the structure as a string.
 */
std::string Structure::getTypeString() const {
    switch(type_) {
        case StructureType::CAVE:    return "cave";
        case StructureType::CASTLE:  return "castle";
        case StructureType::VILLAGE: return "village";
        case StructureType::HOUSE:   return "house";
    }
    return "building";
}

/**
 * @brief Checks if the structure has been fully explored.
 * @return True if all rooms have been explored, otherwise false.
 */
bool Structure::isFullyExplored() const {
    return fullyExplored_;
}

/**
 * @brief Explores the next room in the structure.
 * @param player The player exploring the room.
 * @return True if there are more rooms to explore, otherwise false.
 */
bool Structure::exploreNextRoom(Player &player) {
    if (fullyExplored_ || currentRoomIndex_ >= totalRooms_) {
        fullyExplored_ = true;
        return false;
    }

    foundArtifactThisRoom_ = false;
    std::cout << "\n-- Room #" << (currentRoomIndex_ + 1) 
              << " of " << totalRooms_ << " --\n";
    handleRoom(player);

    currentRoomIndex_++;
    if (currentRoomIndex_ >= totalRooms_) {
        fullyExplored_ = true;
    }
    return true;
}

/**
 * @brief Handles interactions when entering a room.
 * @param player The player exploring the room.
 */
void Structure::handleRoom(Player &player) {
    if (currentRoomIndex_ == (totalRooms_ - 1)) {
        std::cout << "A locked chest with a strange riddle is here...\n";
        if (doRiddle(player)) {
            std::cout << "The chest opens, revealing a sacred artifact!\n";
            foundArtifactThisRoom_ = true;
        } else {
            std::cout << "You failed to solve the riddle, the chest remains locked.\n";
        }
        return;
    }

    bool enemyHere = (std::rand() % 100 < 50);
    bool chestHere = (std::rand() % 100 < 50);

    if (enemyHere) {
        std::vector<Enemy> enemies;
        int count = (std::rand() % 2) + 1;
        for (int i = 0; i < count; i++) {
            int roll = std::rand() % 3;
            enemies.emplace_back((roll == 0 ? "Goblin" : roll == 1 ? "Wolf" : "Zombie"), 
                                 (roll == 0 ? 25 : roll == 1 ? 20 : 35), 
                                 (roll == 0 ? 5 : roll == 1 ? 4 : 6));
        }
        std::cout << "An enemy ambush!\n";
        CombatManager::startCombat(player, enemies);
        if (player.getHealth() <= 0) {
            std::cout << "You collapse...\n";
            return;
        }
    }

    if (chestHere) {
        handleChest(player);
    } else {
        std::cout << "Nothing of interest in this room.\n";
    }
}

/**
 * @brief Handles interactions when discovering a chest in a room.
 * @param player The player interacting with the chest.
 */
void Structure::handleChest(Player &player) {
    std::cout << "You find a small chest!\n";
    if (std::rand() % 100 < 50) {
        std::cout << "Inside, you find a Healing Potion.\n";
        player.getInventory().addItem(Item("Medium Healing Potion", ItemType::HEALTH_POTION, 30));
    } else {
        std::cout << "You find a Rusted Sword (+2 Attack).\n";
        player.getInventory().addItem(Item("Rusted Sword", ItemType::WEAPON, 2));
    }
}

/**
 * @brief Initializes the riddle pool for the structure.
 *
 * You can push back various riddles into riddlePool_.
 */
void Structure::initRiddles() {
    // Example riddles
    Riddle r1;
    r1.question = "What has to be broken before you can use it?";
    r1.options = {"An egg", "A promise", "A rule", "A code"};
    r1.correctIndex = 0; // "An egg"
    r1.hints = {"Often found in kitchens", "White or brown shell"};
    riddlePool_.push_back(r1);

    Riddle r2;
    r2.question = "I'm tall when I'm young, and short when I'm old. What am I?";
    r2.options = {"A tree", "A candle", "A mountain", "A building"};
    r2.correctIndex = 1; 
    r2.hints = {"It melts over time", "It provides light"};
    riddlePool_.push_back(r2);

    Riddle r3;
    r3.question = "What month of the year has 28 days?";
    r3.options = {"February", "April", "All of them", "None"};
    r3.correctIndex = 2; // "All of them"
    r3.hints = {"Trick question!", "They all have at least 28 days"};
    riddlePool_.push_back(r3);

    Riddle r4;
    r4.question = "What gets wet while drying?";
    r4.options = {"A sponge", "A tissue", "A towel", "Your hair"};
    r4.correctIndex = 2; // "A towel"
    r4.hints = {"Usually found in bathrooms", "You hold it after a shower"};
    riddlePool_.push_back(r4);

    
    Riddle r5;
    r5.question = "I am not alive, but I can grow. I do not have lungs, but I need air. I don't have a mouth, yet water kills me. What am I?";
    r5.options = {"A plant", "A fire", "A fish", "A robot"};
    r5.correctIndex = 1; // "A fire"
    r5.hints = {"Used for cooking or warmth", "Flame involved"};
    riddlePool_.push_back(r5);

    Riddle r6;
    r6.question = "What is full of holes but still holds water?";
    r6.options = {"A sponge", "A bucket", "A net", "A colander"};
    r6.correctIndex = 0; // "A sponge"
    r6.hints = {"Found near the sink", "Often used to wash dishes"};
    riddlePool_.push_back(r6);


    Riddle r7;
    r7.question = "I shave every day, but my beard stays the same. What am I?";
    r7.options = {"A father", "A barber", "A monk", "A hairdresser"};
    r7.correctIndex = 1; // "A barber"
    r7.hints = {"Professional job involves hair", "Cuts other people's hair daily"};
    riddlePool_.push_back(r7);


    Riddle r8;
    r8.question = "What has a head and a tail but no body?";
    r8.options = {"A coin", "A snake", "A cat", "A comet"};
    r8.correctIndex = 0; // "A coin"
    r8.hints = {"It's small and round", "Often used as currency"};
    riddlePool_.push_back(r8);

    Riddle r9;
    r9.question = "What can run but never walks, has a mouth but never talks, has a bed but never sleeps?";
    r9.options = {"A river", "A baby", "A computer", "A clock"};
    r9.correctIndex = 0; // "A river"
    r9.hints = {"Flows in one direction","Found in nature"};
    riddlePool_.push_back(r9);

    Riddle r10;
    r10.question = "The more of this there is, the less you see. What is it?";
    r10.options = {"Darkness", "Fog", "Shadow", "Light"};
    r10.correctIndex = 0; // "Darkness"
    r10.hints = {"Opposite of light", "Often associated with night"};
    riddlePool_.push_back(r10);
}

/**
 * @brief Handles a riddle event in the final room.
 * @param player The player attempting to solve the riddle.
 * @return True if the riddle is solved, otherwise false.
 */
bool Structure::doRiddle(Player &player) {
    std::cout << "\nMultiple-Choice Riddle:\n" 
              << riddleToAsk_.question << "\n";

    // Show 4 options
    for (int i = 0; i < (int)riddleToAsk_.options.size(); i++) {
        std::cout << (i+1) << ") " << riddleToAsk_.options[i] << "\n";
    }

    int tries = 5;
    while (tries > 0) {
        std::cout << "Enter your choice (1-4). You have " 
                  << tries << " tries left.\n> ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            tries--;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice < 1 || choice > 4) {
            std::cout << "Choice must be 1-4!\n";
            tries--;
            continue;
        }

        if (riddleToAsk_.correctIndex == (choice - 1)) {
            std::cout << "Correct!\n";
            return true;
        } else {
            tries--;
            if (tries > 0) {
                // Provide a hint if available
                size_t hintIndex = riddleToAsk_.hints.size() - tries;
                if (hintIndex < riddleToAsk_.hints.size()) {
                    std::cout << "Hint: " 
                              << riddleToAsk_.hints[hintIndex] << "\n";
                } else {
                    std::cout << "No more hints!\n";
                }
            }
        }
    }
    return false;
}
