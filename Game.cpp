/**
 * @file Game.cpp
 * @brief This file implements the Game class, which manages the main game loop and game logic.
 */
#include "Game.h"
#include "CombatManager.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include "SaveManager.h"
#include <csignal>
#include "Utilities.h"


/**
 * @brief Constructs a Game object.
 *
 * Initializes the game state, setting isRunning_ to true and hasActiveStructure_ to false.
 */
Game::Game()
    : isRunning_(true), hasActiveStructure_(false)
{}

/**
 * @brief Runs the main game loop.
 *
 * Initializes the game, displays the main menu, and handles the game loop until the player quits.
 */
void Game::run() {

    signal(SIGINT, SaveManager::handleExitSignal);
    SaveManager::startAutoSave(player_, world_);

    initGame();
    mainMenu();
}

/**
 * @brief Initializes the game state.
 *
 * Prints the intro story, creates the game world, and gives the player starting items.
 */
void Game::initGame() {
    //printIntroStory();
    world_.createWorld();
    // Give the player some starting items (two potions)
    Item potion1("Small Healing Potion", ItemType::HEALTH_POTION, 20);
    Item potion2("Small Healing Potion", ItemType::HEALTH_POTION, 20);
    player_.getInventory().addItem(potion1);
    player_.getInventory().addItem(potion2);
}

/**
 * @brief Displays the main menu and handles player choices.
 *
 * Allows the player to start a new game, load a game, or quit.
 */
void Game::mainMenu() {
    while (true) {
        Utilities::clearScreen();
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
            if (SaveManager::loadGame(player_, world_)) {
                std::cout << "Game loaded!\n";
                gameLoop();
            } else {
                std::cout << "Failed to load game. Returning to menu.\n";
            }
        } else if (choice == 3) {
            std::cout << "Goodbye!\n";
            isRunning_ = false;
            return;
        } else {
            std::cout << "Invalid menu choice.\n";
        }
    }
}

/**
 * @brief Runs the main game loop after the game has started or loaded.
 *
 * Handles player input and calls the appropriate game actions until the player quits.
 */
void Game::gameLoop() {
    while (isRunning_) {
        
        printGameMenu();
        int input;
        if (!(std::cin >> input)) {
            badInputPrompt();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Utilities::clearScreen();

        switch(input) {
            case 1: handleMoveForward(); break;
            case 2: handleExplore(); break;
            case 3: handleInventory(); break;
            case 4: handleUseItem(); break;
            case 5: handleSaveGame(); break;
            case 6: handleLoadGame(); break;
            case 7:
                std::cout << "Would you like to save before quitting? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    handleSaveGame();
                }
                isRunning_ = false;
                break;
            default:
                std::cout << "Invalid selection.\n";
                break;
        }
    }
    std::cout << "Exiting game...\n";
}

/**
 * @brief Prints the in-game menu options to the console.
 */
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

/**
 * @brief Handles invalid input from the player, prompting them to try again.
 */
void Game::badInputPrompt() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input, please try again.\n";
}

/**
 * @brief Handles the "Move Forward" action in the game.
 *
 * Allows the player to progress to the next land if all artifacts are collected,
 * or attempts to spawn a new structure to explore.
 */
void Game::handleMoveForward() {
    // 1. If the player can progress to next land, do that first
    if (world_.canProgress(player_.getArtifactsCollected())) {
        bool moved = world_.advanceLand();
        if (!moved) {
            // No more lands
            std::cout << "*** You have all artifacts ***\n";
            printEndStory();
            isRunning_ = false; 
        } else {
            hasActiveStructure_ = false;
            std::cout << "You travel to the next land...\n";
        }
        // Because we advanced land, skip spawning a structure in this same step
        
        return;
    }

    // 2. If we do not advance, attempt to spawn
    if (hasActiveStructure_) {
        std::cout << "You're still in a structure. Finish exploring first.\n";
        
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
    //Utilities::waitForEnter();
}

/**
 * @brief Handles the "Explore Next Room" action in the game.
 *
 * Allows the player to explore the next room in the currently active structure.
 */
void Game::handleExplore() {
    if (!hasActiveStructure_) {
        std::cout << "No structure is currently available to explore.\n";
        //Utilities::waitForEnter();
        return;
    }
    // Double-check the pointer we are about to use
    Structure* sPtr = nullptr;

    // So let's create a safe getter in World if needed:
    sPtr = world_.getActiveStructurePtr();
    if (!sPtr) {
        // If the pointer is null, we forcibly reset hasActiveStructure_
        hasActiveStructure_ = false;
        std::cout << "Structure pointer is null (possibly advanced land?).\n";
        //Utilities::waitForEnter();
        return;
    }
    // Now we can safely use *sPtr
    Structure &currentStruct = *sPtr;

    // Structure &currentStruct = world_.getCurrentStructure();
    if (currentStruct.isFullyExplored()) {
        std::cout << "You've finished exploring this "
                  << currentStruct.getTypeString() << "!\n"
                  << "Leaving the structure...\n";
        hasActiveStructure_ = false;
        //Utilities::waitForEnter();
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
        //Utilities::waitForEnter();
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

    //Utilities::waitForEnter();
}

/**
 * @brief Handles the "Check Inventory" action in the game.
 *
 * Displays the items currently in the player's inventory.
 */
void Game::handleInventory() {
    //player_.showInventory();
    Utilities::clearScreen(); 
    std::cout << "Health: " 
          << player_.getHealth() << " / " 
          << player_.getMaxHealth() << "\n\n";

    player_.showInventorySideBySideWithMenu(); 
    Utilities::waitForEnter();
}

/**
 * @brief Handles the "Use an Item" action in the game.
 *
 * Allows the player to select and use an item from their inventory.
 */
void Game::handleUseItem() {
    Utilities::clearScreen();

    Inventory &inv = player_.getInventory();
    if (inv.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    std::cout << "Health: " 
          << player_.getHealth() << " / " 
          << player_.getMaxHealth() << "\n\n";
    // Display items as a numbered list
    const std::vector<Item>& items = inv.getItems();
    std::cout << "\nWhich item do you want to use? Enter the number:\n";
    for (size_t i = 0; i < items.size(); i++) {
        std::cout << (i+1) << ") " << items[i].getName()
                  << " (" << items[i].getTypeString() << ")\n";
    }
    std::cout << (items.size() + 1) << ") Cancel\n> ";

    int choice;
    if (!(std::cin >> choice)) {
        // handle bad input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. No item used.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == static_cast<int>(items.size() + 1)) {
        std::cout << "Canceled item use.\n";
        return;
    }

    // Validate choice range
    if (choice < 1 || static_cast<size_t>(choice) > items.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // We have a valid item index
    size_t idx = choice - 1;
    const Item &chosenItem = items[idx];
    ItemType type = chosenItem.getType();

    switch(type) {
        case ItemType::HEALTH_POTION:
        {
            int healValue = chosenItem.getValue();
            player_.heal(healValue);
            std::cout << "You drink " << chosenItem.getName()
                      << " and recover " << healValue
                      << " HP. Your health is now "
                      << player_.getHealth() << ".\n"; 
             Utilities::waitForEnter();
            // remove the item from inventory
            inv.removeIndex(idx);
            break;
        }
        case ItemType::WEAPON:
        {
            // Let’s equip the weapon and increase Attack
            std::cout << "You equip " << chosenItem.getName()
                      << " (+ " << chosenItem.getValue() << " Attack).\n";
            // Then call some method in Player to handle equipping logic
            player_.equipWeapon(chosenItem.getValue());
            // We might keep it in inventory or remove it.
            // Typically you do not remove the weapon from inventory if it's “equipped”
            Utilities::waitForEnter();
            break;
        }
        default:
        {
            std::cout << "You attempt to use " << chosenItem.getName()
                      << ", but nothing special happens.\n";
            Utilities::waitForEnter();
            break;
        }
    }
}

/**
 * @brief Handles the "Save Game" action in the game.
 *
 * Calls the SaveManager to save the current game state.
 */
void Game::handleSaveGame() {
    SaveManager::saveGame(player_, world_);
}

/**
 * @brief Handles the "Load Game" action in the game.
 *
 * Calls the SaveManager to load a previously saved game state.
 */
void Game::handleLoadGame() {
    if (SaveManager::loadGame(player_, world_)) {
        std::cout << "Game loaded successfully!\n";
        isRunning_ = true;
    } else {
        std::cout << "Failed to load game.\n";
    }
}

/**
 * @brief Checks if the player has collected enough artifacts to progress to the next land.
 *
 * If so, it advances the land or ends the game if all artifacts are collected.
 */
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

/**
 * @brief Displays the class selection menu and allows the player to choose their class.
 */
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

/**
 * @brief Starts a new game, prompting the player for class selection.
 */
void Game::startNewGame() {
    Utilities::clearScreen();
    printIntroStory();
    Utilities::waitForEnter();
    Utilities::clearScreen();  
    std::cout << "Starting a new game...\n";
    displayClassSelection();
    std::cout << "Your quest begins!\n";
}

/**
 * @brief Prints the introductory story of the game.
 */
void Game::printIntroStory() {
    std::cout << "\n=== PROLOGUE ===\n"
              << "A dark curse has fractured the world into three lands.\n"
              << "Each land has 3 hidden structures, each with a final riddle-locked artifact.\n"
              << "Collect all 9 to break the curse...\n";
}

/**
 * @brief Prints the ending story of the game.
 */
void Game::printEndStory() {
    std::cout << "\n=== EPILOGUE ===\n"
              << "With the ninth artifact claimed, the realm is restored.\n"
              << "You are hailed as a hero for ages to come!\n";
}