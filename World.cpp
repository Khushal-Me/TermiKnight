// World.cpp

#include "World.h"
#include "Utilities.h"
#include <iostream>

World::World()
    : currentLandIndex_(0) {}

void World::createWorld() {
    // Not strictly necessary to pre-generate everything,
    // but you can define the range of rooms per land, etc.
}

void World::attemptSpawnStructure() {
    // Based on random chance or step count, spawn a new structure
    int roll = Utilities::getRandomInt(1, 100);
    if (roll < 30) {
        // 30% chance we find a building
        // e.g., determine structure type
        StructureType type = static_cast<StructureType>(Utilities::getRandomInt(0, 2));
        int minRooms = 1 + currentLandIndex_; 
        int maxRooms = 2 + currentLandIndex_ * 2; 
        Structure structure(type, minRooms, maxRooms);
        structure.generateRooms();
        std::cout << "You come across a " 
                  << (type == StructureType::CAVE ? "cave" : 
                      type == StructureType::CASTLE ? "castle" : "village")
                  << " with " << structure.getRoomCount() << " rooms.\n";
        // We could store this structure as an "active" structure to explore
    }
}

bool World::canProgress(int artifactsCollected) const {
    // For example, if each land requires 1 artifact, or total 5 by the end
    // Adjust logic as needed
    return artifactsCollected >= (currentLandIndex_ + 1);
}

void World::advanceLand() {
    currentLandIndex_++;
    if (currentLandIndex_ >= 5) {
        std::cout << "You have explored all lands!\n";
    } else {
        std::cout << "You travel to land " << currentLandIndex_ + 1 << ".\n";
    }
}
