// Structure.h
// Represents a randomly generated building or "structure" with multiple rooms and potential enemies/items.

#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"

enum class StructureType {
    CAVE,
    CASTLE,
    VILLAGE
};

class Structure {
public:
    Structure(StructureType type, int minRooms, int maxRooms);

    // Basic info
    StructureType getType() const;
    int getRoomCount() const;

    // Exploration
    void generateRooms();  // Randomly set the number of rooms
    bool hasRiddleInFinalRoom() const;
    bool solveRiddle();    // Logic for riddles, returns true if solved
    bool hasArtifact() const; // True if final room has artifact

    // Enemy / Item spawning
    bool checkForEnemy();  // Possibly random chance to spawn enemy
    std::vector<Enemy> spawnEnemies(); // return the actual enemies

    // Room-based logic
    void exploreRoom(int roomIndex);

private:
    StructureType type_;
    int roomCount_;
    int minRooms_;
    int maxRooms_;

    bool artifactFound_;
    bool riddleSolved_;
};
