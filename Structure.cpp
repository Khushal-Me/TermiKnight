// Structure.cpp
#include "Structure.h"
#include "CombatManager.h"
#include <iostream>
#include <cstdlib>
#include <limits>

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

std::string Structure::getTypeString() const {
    switch(type_) {
        case StructureType::CAVE:    return "cave";
        case StructureType::CASTLE:  return "castle";
        case StructureType::VILLAGE: return "village";
        case StructureType::HOUSE:   return "house";
    }
    return "building";
}

bool Structure::isFullyExplored() const {
    return fullyExplored_;
}

bool Structure::exploreNextRoom(Player &player) {
    if (fullyExplored_) {
        std::cout << "This structure is already fully explored.\n";
        return false;
    }
    if (currentRoomIndex_ >= totalRooms_) {
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

void Structure::handleRoom(Player &player) {
    // If final room => do riddle
    if (currentRoomIndex_ == (totalRooms_ - 1)) {
        std::cout << "A locked chest with a strange riddle is here...\n";
        bool solved = doRiddle(player);
        if (solved) {
            std::cout << "The chest opens, revealing a sacred artifact!\n";
            foundArtifactThisRoom_ = true;
        } else {
            std::cout << "You failed to solve the riddle, the chest remains locked.\n";
        }
        return;
    }

    // Otherwise normal room
    bool enemyHere = false;
    bool chestHere = false;
    // E.g., first room => guaranteed enemy + chest
    if (currentRoomIndex_ == 0) {
        enemyHere = true;
        chestHere = true;
    } else {
        int rollEnemy = std::rand() % 100;
        if (rollEnemy < 50) enemyHere = true;
        int rollChest = std::rand() % 100;
        if (rollChest < 50) chestHere = true;
    }

    if (enemyHere) {
        std::vector<Enemy> enemies;
        int count = (std::rand() % 2) + 1;
        for (int i = 0; i < count; i++) {
            int roll = std::rand() % 3;
            if (roll == 0) enemies.emplace_back("Goblin", 25, 5);
            else if (roll == 1) enemies.emplace_back("Wolf", 20, 4);
            else enemies.emplace_back("Zombie", 35, 6);
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

void Structure::handleChest(Player &player) {
    std::cout << "You find a small chest!\n";
    int roll = std::rand() % 100;
    if (roll < 50) {
        std::cout << "Inside, you find a Healing Potion.\n";
        player.getInventory().addItem(Item("Medium Healing Potion", ItemType::HEALTH_POTION, 30));
    } else {
        std::cout << "You find a Rusted Sword (+2 Attack).\n";
        player.getInventory().addItem(Item("Rusted Sword", ItemType::WEAPON, 2));
    }
}

bool Structure::doRiddle(Player &player) {
    std::cout << "\nMultiple-Choice Riddle:\n" << riddleToAsk_.question << "\n";
    // Present 4 options
    for (int i = 0; i < (int)riddleToAsk_.options.size(); i++) {
        std::cout << (i+1) << ") " << riddleToAsk_.options[i] << "\n";
    }

    int tries = 5;
    while (tries > 0) {
        std::cout << "Enter your choice (1-4). You have " << tries << " tries left.\n> ";
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
                    std::cout << "Hint: " << riddleToAsk_.hints[hintIndex] << "\n";
                } else {
                    std::cout << "No more hints!\n";
                }
            }
        }
    }
    return false;
}

void Structure::initRiddles() {
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
    r3.correctIndex = 2;
    r3.hints = {"Trick question", "They all have at least 28 days"};
    riddlePool_.push_back(r3);

    // Add more if you want...
}
