#include "Game.h"
#include "CombatManager.h"
#include <iostream>
#include <limits>
#include <cstdlib>

Game::Game()
    : isRunning_(true), hasActiveStructure_(false)
{}

void Game::run() {
    initGame();
    mainMenu();
}

void Game::initGame() {
    printIntroStory();
    world_.createWorld();  
    // Give the player some starting items (two potions)
    Item potion1("Small Healing Potion", ItemType::HEALTH_POTION, 20);
    Item potion2("Small Healing Potion", ItemType::HEALTH_POTION, 20);
    player_.getInventory().addItem(potion1);
    player_.getInventory().addItem(potion2);
}

void Game::mainMenu() {
    while (true) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "3) Quit\n";
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            badInputPrompt();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            startNewGame();
            gameLoop(); 
            break;      
        } else if (choice == 2) {
            handleLoadGame();
            gameLoop(); 
            break;
        } else if (choice == 3) {
            std::cout << "Goodbye!\n";
            isRunning_ = false;
            return;
        } else {
            std::cout << "Invalid menu choice.\n";
        }
    }
}

void Game::gameLoop() {
    while (isRunning_) {
        printGameMenu();
        int input;
        if (!(std::cin >> input)) {
            badInputPrompt();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(input) {
            case 1: handleMoveForward();    break; // Move 
            case 2: handleExplore();        break; // Explore current structure/room
            case 3: handleInventory();      break; // Show inv
            case 4: handleUseItem();        break; // Use item from inventory
            case 5: handleSaveGame();       break;
            case 6: handleLoadGame();       break;
            case 7: isRunning_ = false;     break; // Quit
            default:
                std::cout << "Invalid selection.\n";
                break;
        }
    }
    std::cout << "Exiting game...\n";
}

// Prints the in-game menu
void Game::printGameMenu() {
    std::cout << "\n=== Game Menu ===\n";
    if (hasActiveStructure_) {
        std::cout << "Currently exploring a " 
                  << world_.getCurrentStructure().getTypeString() << "\n";
    }
    std::cout << "1) Move Forward\n"
              << "2) Explore Next Room\n"
              << "3) Check Inventory\n"
              << "4) Use an Item\n"
              << "5) Save Game\n"
              << "6) Load Game\n"
              << "7) Quit\n"
              << "Choice: ";
}

void Game::badInputPrompt() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input, please try again.\n";
}

// 1) Move Forward
void Game::handleMoveForward() {
    // If we are in the middle of exploring a structure, don't allow
    if (hasActiveStructure_) {
        std::cout << "You are currently inside a structure. Finish exploring it first.\n";
        return;
    }

    // Flavor text
    int roll = std::rand() % 100;
    if (roll < 25) {
        std::cout << "A bird swoops overhead, chirping madly.\n";
    } else if (roll < 40) {
        std::cout << "You pass by a lifeless deer. The land is eerily quiet...\n";
    } else {
        std::cout << "You continue along the winding path.\n";
    }

    // Attempt structure spawn
    bool spawned = world_.attemptSpawnStructure();
    if (spawned) {
        hasActiveStructure_ = true;
        auto structType = world_.getLastSpawnedStructureType();
        std::cout << "\nYou come upon a " << structType 
                  << "! There may be multiple rooms inside.\n";
    }
    // Check if we can progress to next land 
    handleCheckArtifacts();
}

// 2) Explore next room in the structure
void Game::handleExplore() {
    if (!hasActiveStructure_) {
        std::cout << "No structure is currently available to explore.\n";
        return;
    }

    Structure &currentStruct = world_.getCurrentStructure();
    if (currentStruct.isFullyExplored()) {
        std::cout << "You've finished exploring this " 
                  << currentStruct.getTypeString() << "!\n"
                  << "Leaving the structure...\n";
        hasActiveStructure_ = false;
        return;
    }

    bool success = currentStruct.exploreNextRoom(player_);
    if (!success) {
        // Possibly fully explored or an error
        if (currentStruct.isFullyExplored()) {
            std::cout << "You have fully explored this " 
                      << currentStruct.getTypeString() << ".\n"
                      << "Leaving now...\n";
            hasActiveStructure_ = false;
        }
        return;
    }

    // Check if the final room had an artifact
    if (currentStruct.hasFoundArtifactThisRoom()) {
        Item artifact("Sacred Artifact", ItemType::ARTIFACT);
        player_.getInventory().addItem(artifact);
        player_.addArtifact();
        std::cout << "\nYou now have " << player_.getArtifactsCollected() 
                  << " total artifacts.\n";
    }

    // If after exploring that room we are done:
    if (currentStruct.isFullyExplored()) {
        std::cout << "\nYou have explored all rooms here.\n"
                  << "Leaving the structure...\n";
        hasActiveStructure_ = false;
    }
}

// 3) Check Inventory
void Game::handleInventory() {
    player_.showInventory();
}

// 4) Use Item
void Game::handleUseItem() {
    Inventory &inv = player_.getInventory();
    if (inv.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    std::cout << "\nWhich item do you want to use?\n";
    inv.listItems(); 
    std::cout << "(Type the exact name of the item, or 'cancel')\n> ";

    std::string itemName;
    std::getline(std::cin, itemName);
    if (itemName == "cancel") {
        std::cout << "No item used.\n";
        return;
    }
    if (!inv.hasItem(itemName)) {
        std::cout << "You do not have " << itemName << ".\n";
        return;
    }

    // Basic logic: if it's a "Healing" potion, we heal
    if (itemName.find("Healing") != std::string::npos) {
        bool found = false;
        int healValue = 0;

        // Let's find the item in inventory to get its .getValue()
        for (auto &itm : inv.getItems()) {
            if (itm.getName() == itemName) {
                healValue = itm.getValue();
                inv.removeItem(itemName);
                found = true;
                break;
            }
        }
        if (found) {
            player_.heal(healValue);
            std::cout << "You drink " << itemName << " and recover " 
                      << healValue << " HP. Your health is now " 
                      << player_.getHealth() << ".\n";
        }
    } else {
        std::cout << "You attempt to use " << itemName 
                  << ", but nothing special happens.\n";
    }
}

// 5) Save
void Game::handleSaveGame() {
    std::cout << "[DEBUG] Game saved. (placeholder)\n";
}

// 6) Load
void Game::handleLoadGame() {
    std::cout << "[DEBUG] Game loaded. (placeholder)\n";
    isRunning_ = true;
}

// Check if we can move to next land
void Game::handleCheckArtifacts() {
    if (world_.canProgress(player_.getArtifactsCollected())) {
        bool moved = world_.advanceLand();
        if (!moved) {
            std::cout << "\n*** You have collected all 9 artifacts and restored balance! ***\n";
            printEndStory();
            isRunning_ = false;
        } else {
            std::cout << "\nYou travel to the next land...\n";
        }
    }
}

void Game::displayClassSelection() {
    std::cout << "\nChoose your class:\n"
              << "1) Civilian (Higher luck, lower damage)\n"
              << "2) Bandit (Higher damage, lower luck)\n"
              << "3) Mage (High damage, less health)\n"
              << "4) Soldier (High health, high damage, low luck)\n"
              << "Choice: ";
    int choice;
    if (!(std::cin >> choice)) {
        badInputPrompt();
        choice = 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: player_.setClassType(ClassType::CIVILIAN); std::cout << "You chose Civilian.\n"; break;
        case 2: player_.setClassType(ClassType::BANDIT);   std::cout << "You chose Bandit.\n"; break;
        case 3: player_.setClassType(ClassType::MAGE);     std::cout << "You chose Mage.\n"; break;
        case 4: player_.setClassType(ClassType::SOLDIER);  std::cout << "You chose Soldier.\n"; break;
        default:
            std::cout << "Invalid choice. Defaulting to Civilian.\n";
            player_.setClassType(ClassType::CIVILIAN);
            break;
    }
}

void Game::startNewGame() {
    std::cout << "Starting a new game...\n";
    displayClassSelection();
    std::cout << "Your quest begins!\n";
}

void Game::printIntroStory() {
    std::cout << "\n=== PROLOGUE ===\n"
              << "A dark curse has fractured the world into three lands.\n"
              << "Each land has 3 hidden structures, each with a final riddle-locked artifact.\n"
              << "Collect all 9 to break the curse...\n";
}

void Game::printEndStory() {
    std::cout << "\n=== EPILOGUE ===\n"
              << "With the ninth artifact claimed, the realm is restored.\n"
              << "You are hailed as a hero for ages to come!\n";
}
