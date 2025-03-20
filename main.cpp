/**
 * @file main.cpp
 * @brief Entry point for the TermiKnight text-based RPG.
 *
 * This file defines the main function, which instantiates the Game
 * object and runs the main game loop.
 */
#include "Game.h"

/**
 * @brief Main function, the program's entry point.
 *
 * Creates a Game object and calls its run() method to launch
 * the text-based RPG. Returns 0 upon normal termination.
 *
 * @return Exit code (0 indicates success).
 */
int main() {
    Game game;
    game.run();  // Begin the main menu and game loop
    return 0;
}
