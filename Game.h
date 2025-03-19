/**
 * @file Game.h
 * @brief This file declares the Game class, which manages the main game loop and game logic.
 */

 #pragma once
 #include "Player.h"
 #include "World.h"
 #include <string>
 
 /**
  * @brief The main class responsible for running the game.
  *
  * Manages the game loop, player input, world interactions, and overall game flow.
  */
 class Game {
 public:
     /**
      * @brief Constructs a Game object.
      */
     Game();
 
     /**
      * @brief Runs the main game loop, including the menu and gameplay.
      */
     void run();  // Main entry for the game (menu, loops)
 
 private:
     /**
      * @brief The player character in the game.
      */
     Player player_;
     /**
      * @brief The game world containing lands and structures.
      */
     World world_;
     /**
      * @brief Flag indicating whether the game is currently running.
      */
     bool isRunning_;
     /**
      * @brief Flag indicating whether the player is currently inside an explorable structure.
      */
     bool hasActiveStructure_;
 
     /**
      * @brief Initializes the core game components.
      */
     void initGame();
     /**
      * @brief Displays and handles the main menu of the game.
      */
     void mainMenu();
     /**
      * @brief The main loop of the game, handling player actions and game updates.
      */
     void gameLoop();
 
     /**
      * @brief Prints the in-game menu options to the console.
      */
     void printGameMenu();
     /**
      * @brief Handles invalid input from the player.
      */
     void badInputPrompt();
 
     /**
      * @brief Handles the action of moving forward in the game world.
      */
     void handleMoveForward();
     /**
      * @brief Handles the action of exploring the next room in a structure.
      */
     void handleExplore();
     /**
      * @brief Handles the action of checking the player's inventory.
      */
     void handleInventory();
     /**
      * @brief Handles the action of using an item from the player's inventory.
      */
     void handleUseItem();
     /**
      * @brief Handles the action of saving the current game state.
      */
     void handleSaveGame();
     /**
      * @brief Handles the action of loading a previously saved game state.
      */
     void handleLoadGame();
     /**
      * @brief Checks if the player has collected enough artifacts to progress.
      */
     void handleCheckArtifacts();
 
     /**
      * @brief Displays the class selection menu at the start of a new game.
      */
     void displayClassSelection();
     /**
      * @brief Starts a new game, initializing player and world states.
      */
     void startNewGame();
     /**
      * @brief Prints the introductory story of the game.
      */
     void printIntroStory();
     /**
      * @brief Prints the ending story of the game.
      */
     void printEndStory();
 };