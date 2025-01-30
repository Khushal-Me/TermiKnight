// Utilities.cpp
#include "Utilities.h"
#include <cstdlib>
#include <ctime>

int Utilities::getRandomInt(int min, int max) {
    // Example: returns a random integer between min and max inclusive
    return rand() % (max - min + 1) + min;
}
