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

    // Additional utility functions like trim, toLower, etc. can be added here.
}
