// Game.cpp

#include "Game.h"
#include <iostream>

Game::Game() 
    : isRunning_(true) {}

void Game::run() {
    initGame();
    mainMenu();
}

void Game::initGame() {
    world_.createWorld();  // Create the 5 lands
}

void Game::mainMenu() {
    // Simple menu: "1) New Game 2) Load Game 3) Quit"
    // On "New Game", call displayClassSelection(); 
    // then player picks class -> set up initial stats
    // then gameLoop();
}

void Game::gameLoop() {
    while (isRunning_) {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);
        processInput(input);
    }
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
    // Possibly increment steps; 
    // Check if a random building spawns in the current land 
    world_.attemptSpawnStructure();
    // If spawned, print "You come across a [building type]."
}

void Game::handleExplore() {
    // Explore the current structure (if any)
    // Possibly call Structure methods, see rooms, collect items, fight, solve riddles
}

void Game::handleInventory() {
    player_.showInventory();
}

void Game::handleSaveGame() {
    // Could use SaveManager to serialize
}

void Game::handleLoadGame() {
    // Could use SaveManager to deserialize
}

void Game::handleCheckArtifacts() {
    // If the player has enough artifacts, move to the next land
    if (world_.canProgress(player_.getArtifactsCollected())) {
        world_.advanceLand();
        std::cout << "You travel to the next land.\n";
    }
}

void Game::displayClassSelection() {
    // Let user pick from: Civilian, Bandit, Mage, Soldier
    // Once chosen, set player_ stats accordingly (health, attack, luck).
}
