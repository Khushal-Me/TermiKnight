// Game.h
// Orchestrates core gameplay flow (character selection, exploring lands, etc.).

#pragma once
#include "Player.h"
#include "World.h"
#include <string>

class Game {
public:
    Game();
    void run();  // Main entry for the game (menu, loops)

private:
    Player player_;  
    World world_;  
    bool isRunning_;  

    // For demonstration, track if we have an active structure to explore
    bool hasActiveStructure_ = false; 

    void initGame();              // Initialize game world, set up lands
    void mainMenu();              // Start/Load/Quit
    void gameLoop();              // Primary command loop
    void processInput(const std::string &input);

    // Command handlers
    void handleMoveForward();
    void handleExplore();         // Explore a building/structure
    void handleInventory();
    void handleSaveGame();
    void handleLoadGame();
    void handleCheckArtifacts();  // Check if enough artifacts to advance land

    // Utilities
    void displayClassSelection(); // Let the user pick Civilian/Bandit/Mage/Soldier
    void startNewGame();          // Called if user selects "New Game" in mainMenu
};
