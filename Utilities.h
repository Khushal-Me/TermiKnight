/**
 * @file Utilities.h
 * @brief Provides utility functions for general-purpose operations.
 */

#pragma once
#include <string>

/**
 * @namespace Utilities
 * @brief A collection of helper functions for common operations.
 */
namespace Utilities {

    /**
     * @brief Generates a random integer within a given range.
     * 
     * @param minVal The minimum value of the range (inclusive).
     * @param maxVal The maximum value of the range (inclusive).
     * @return A random integer between minVal and maxVal.
     */
    int getRandomInt(int minVal, int maxVal);


    /**
     * @brief Clears the terminal screen, cross-platform.
     */
    void clearScreen();

    /**
     * @brief Gets the current terminal width (in characters).
     * 
     * @return Number of columns of the terminal.
     */
    int getTerminalWidth();

    
    /**
    * @brief Prompts the player to press Enter to continue.
    *
    * This function pauses execution and waits for the user to press Enter.
    * It's useful for allowing players to read important output before the screen is cleared.
    */
    void waitForEnter();
}


