/**
 * @file Utilities.cpp
 * @brief Implements utility functions for common operations.
 */

#include "Utilities.h"
#include <cstdlib>

/**
 * @brief Generates a random integer within a given range.
 * 
 * @param minVal The minimum value of the range (inclusive).
 * @param maxVal The maximum value of the range (inclusive).
 * @return A random integer between minVal and maxVal.
 */
int Utilities::getRandomInt(int minVal, int maxVal) {
    return (std::rand() % (maxVal - minVal + 1)) + minVal;
}
