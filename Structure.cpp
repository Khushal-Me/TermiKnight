// Structure.cpp
#include "Structure.h"
#include "Utilities.h"
#include <iostream>

Structure::Structure(StructureType type, int minRooms, int maxRooms)
    : type_(type), minRooms_(minRooms), maxRooms_(maxRooms),
      roomCount_(0), artifactFound_(false), riddleSolved_(false) {}

StructureType Structure::getType() const {
    return type_;
}

int Structure::getRoomCount() const {
    return roomCount_;
}

void Structure::generateRooms() {
    roomCount_ = Utilities::getRandomInt(minRooms_, maxRooms_);
}

bool Structure::hasRiddleInFinalRoom() const {
    // The final room is locked by a riddle
    return true; // Always, by your new design
}

bool Structure::solveRiddle() {
    // Prompt user with a puzzle or riddle
    // If they solve it, riddleSolved_ = true
    // Return success/failure
    return (riddleSolved_ = true);
}

bool Structure::hasArtifact() const {
    // The artifact is found in the final room after solving riddle
    return (riddleSolved_ && !artifactFound_);
}

bool Structure::checkForEnemy() {
    // Some random chance to spawn an enemy upon entering
    int chance = Utilities::getRandomInt(1, 100);
    return chance < 50; // 50% example
}

std::vector<Enemy> Structure::spawnEnemies() {
    std::vector<Enemy> enemies;
    // Possibly spawn 1–2 enemies
    // ...
    return enemies;
}

void Structure::exploreRoom(int roomIndex) {
    // Possibly find items, trigger enemy. 
    std::cout << "Exploring room " << roomIndex << " in the structure.\n";
}
