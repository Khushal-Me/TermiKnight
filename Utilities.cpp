// Utilities.cpp
#include "Utilities.h"
#include <cstdlib>

int Utilities::getRandomInt(int minVal, int maxVal) {
    return (std::rand() % (maxVal - minVal + 1)) + minVal;
}
