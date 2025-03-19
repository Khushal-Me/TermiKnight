/**
 * @file World.cpp
 * @brief Implements the World class for managing game world progression and structures.
 */

#include "World.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * @brief Constructs a World instance, initializing state variables.
 */
World::World()
  : currentLandIndex_(0),
    justSpawned_(false),
    activeStructure_(nullptr)
{
}

/**
 * @brief Initializes the world by setting up land structure pools.
 */
void World::createWorld() {
    std::srand((unsigned)time(nullptr));

    // Set up structure pools for three lands
    landStructurePool_.resize(3);
    landStructurePool_[0] = { {StructureType::CAVE, 2}, {StructureType::CASTLE, 2}, {StructureType::VILLAGE, 2} };
    landStructurePool_[1] = { {StructureType::CAVE, 3}, {StructureType::CASTLE, 3}, {StructureType::VILLAGE, 3} };
    landStructurePool_[2] = { {StructureType::CAVE, 5}, {StructureType::CASTLE, 5}, {StructureType::VILLAGE, 5} };
}

/**
 * @brief Attempts to spawn a structure in the current land.
 * @return True if a structure is successfully spawned, otherwise false.
 */
bool World::attemptSpawnStructure() {
    if (currentLandIndex_ >= 3 || landStructurePool_[currentLandIndex_].empty()) {
        justSpawned_ = false;
        return false;
    }

    int roll = std::rand() % 100;
    if (roll < 40) {
        auto &pool = landStructurePool_[currentLandIndex_];
        int pickIndex = std::rand() % pool.size();
        auto stype = pool[pickIndex].first;
        int rooms = pool[pickIndex].second;

        structures_.push_back(Structure(stype, rooms));
        activeStructure_ = &structures_.back();

        pool.erase(pool.begin() + pickIndex);
        justSpawned_ = true;
        return true;
    }

    justSpawned_ = false;
    return false;
}

/**
 * @brief Checks if the player has collected enough artifacts to progress.
 * @param artifactsCollected The number of artifacts collected.
 * @return True if progression is allowed, otherwise false.
 */
bool World::canProgress(int artifactsCollected) {
    return artifactsCollected >= ((currentLandIndex_ + 1) * 3);
}

/**
 * @brief Advances the player to the next land if possible.
 * @return False if there are no more lands to explore, otherwise true.
 */
bool World::advanceLand() {
    currentLandIndex_++;
    activeStructure_ = nullptr;
    return currentLandIndex_ < 3;
}

/**
 * @brief Retrieves the type of the last spawned structure.
 * @return The name of the last spawned structure, or "nothing" if none was spawned.
 */
std::string World::getLastSpawnedStructureType() const {
    if (!justSpawned_ || !activeStructure_) {
        return "nothing";
    }
    return activeStructure_->getTypeString();
}

/**
 * @brief Retrieves the currently active structure.
 * @return A reference to the currently active Structure.
 */
Structure& World::getCurrentStructure() {
    return *activeStructure_;
}

/**
 * @brief Serializes the World object to JSON.
 * @return A JSON object representing the world state.
 */
nlohmann::json World::toJSON() const {
    return {
        {"current_land", currentLandIndex_},
        {"explored_structures", exploredStructures_}
    };
}

/**
 * @brief Loads the World object from a JSON representation.
 * @param jsonData The JSON object containing world state information.
 */
void World::fromJSON(const nlohmann::json& jsonData) {
    currentLandIndex_ = jsonData["current_land"].get<int>();
    exploredStructures_ = jsonData["explored_structures"].get<std::vector<std::string>>();
}
