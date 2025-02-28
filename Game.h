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
    bool hasActiveStructure_;

    // CORE INIT
    void initGame();
    void mainMenu();
    void gameLoop();

    // MENUS & INPUT
    void printGameMenu();
    void badInputPrompt();

    // ACTION HANDLERS
    // (We used param-less handleUseItem() to match our usage in Game.cpp)
    void handleMoveForward();
    void handleExplore();
    void handleInventory();
    void handleUseItem();
    void handleSaveGame();
    void handleLoadGame();
    void handleCheckArtifacts();

    // UTILITIES
    void displayClassSelection();
    void startNewGame();
    void printIntroStory();
    void printEndStory();
};
