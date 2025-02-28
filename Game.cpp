// Game.cpp

#include "Game.h"
#include <iostream>
#include <limits> // for std::numeric_limits<std::streamsize>

Game::Game() 
    : isRunning_(true) 
{}

void Game::run() {
    initGame();
    mainMenu();
}

void Game::initGame() {
    // Initialize the world (create 5 lands, etc.)
    world_.createWorld();  
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
            // Handle non-integer input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        // Clear leftover newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            startNewGame();
            gameLoop(); // enter the game command loop
            break;      // once gameLoop ends, we exit mainMenu
        } else if (choice == 2) {
            handleLoadGame();
            // If successful, go to gameLoop
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
    std::cout << "\nType a command (MOVE FORWARD, EXPLORE, CHECK INVENTORY, SAVE GAME, LOAD GAME, QUIT)\n";
    while (isRunning_) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        processInput(input);
    }
    std::cout << "Exiting Game...\n";
}

void Game::processInput(const std::string &input) {
    if (input == "MOVE FORWARD") {
        handleMoveForward();
    } else if (input == "EXPLORE") {
        handleExplore();
    } else if (input == "CHECK INVENTORY") {
        handleInventory();
    } else if (input == "SAVE GAME") {
        handleSaveGame();
    } else if (input == "LOAD GAME") {
        handleLoadGame();
    } else if (input == "QUIT") {
        isRunning_ = false;
    } else {
        std::cout << "Unknown command.\n";
    }
}

void Game::handleMoveForward() {
    // Possibly increment steps or track distance traveled
    // Check if a random building spawns in the current land
    bool spawned = world_.attemptSpawnStructure();
    if (spawned) {
        // Mark that there's an active structure to explore
        hasActiveStructure_ = true;
        // This is a placeholder; your real code might check structure type
        std::string structureType = world_.getLastSpawnedStructureType();
        std::cout << "You come across a " << structureType << "!\n"
                  << "Type EXPLORE to investigate.\n";
    } else {
        std::cout << "You continue down the path...\n";
    }

    // Optionally check if we can advance the land 
    handleCheckArtifacts();
}

void Game::handleExplore() {
    if (!hasActiveStructure_) {
        std::cout << "There's no structure to explore right now.\n";
        return;
    }

    // In a real implementation, you'd retrieve a pointer/reference to the spawned structure
    // For demonstration, let's say we can spawn an enemy to fight:
    auto enemies = world_.getEnemiesInCurrentStructure(); 
    if (!enemies.empty()) {
        std::cout << "Enemies appear in the building!\n";
        // Now let's do a simple combat
        CombatManager::startCombat(player_, enemies);
        // After combat, if the player survives, maybe there's an item or riddle
        if (player_.getHealth() > 0) {
            std::cout << "You search the building after defeating enemies...\n";
            // Possibly find an artifact or item
            bool foundArtifact = true; // mock logic
            if (foundArtifact) {
                player_.addArtifact();
                std::cout << "You found an artifact! You now have " 
                          << player_.getArtifactsCollected() << " artifacts.\n";
            }
        }
    } else {
        std::cout << "This building seems empty...\n";
    }

    // Reset hasActiveStructure_ so we can't re-explore the same one
    hasActiveStructure_ = false;
}

void Game::handleInventory() {
    player_.showInventory();
}

void Game::handleSaveGame() {
    // Could use SaveManager to serialize
    // For now, just a placeholder
    std::cout << "[DEBUG] Game saved (placeholder)!\n";
}

void Game::handleLoadGame() {
    // Could use SaveManager to deserialize
    // For now, just a placeholder
    std::cout << "[DEBUG] Game loaded (placeholder)!\n";
    // Suppose we set isRunning_ = true in case it was false
    isRunning_ = true;
}

void Game::handleCheckArtifacts() {
    if (world_.canProgress(player_.getArtifactsCollected())) {
        world_.advanceLand();
        std::cout << "You travel to the next land.\n";
    }
}

void Game::displayClassSelection() {
    std::cout << "\nChoose your class:\n"
              << "1) Civilian (High Luck, Lower Damage)\n"
              << "2) Bandit (Higher Damage, Lower Luck)\n"
              << "3) Mage (High Damage, Less Health)\n"
              << "4) Soldier (High Health, High Damage, Low Luck)\n"
              << "Choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

    switch (choice) {
        case 1:
            player_.setClassType(ClassType::CIVILIAN);
            std::cout << "You chose Civilian.\n";
            break;
        case 2:
            player_.setClassType(ClassType::BANDIT);
            std::cout << "You chose Bandit.\n";
            break;
        case 3:
            player_.setClassType(ClassType::MAGE);
            std::cout << "You chose Mage.\n";
            break;
        case 4:
            player_.setClassType(ClassType::SOLDIER);
            std::cout << "You chose Soldier.\n";
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Civilian.\n";
            player_.setClassType(ClassType::CIVILIAN);
            break;
    }
}

void Game::startNewGame() {
    std::cout << "Starting a new game...\n";
    displayClassSelection();

    // Potentially reset stats if needed
    player_.setHealth(player_.getHealth()); // just example if you want to readjust
    // If you want to do anything else on new game start:
    // e.g. set starting inventory, gold, etc.
    // For now, it's just a placeholder

    std::cout << "New game started. Begin your adventure!\n";
}
