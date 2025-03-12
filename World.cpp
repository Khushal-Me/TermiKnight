#include "World.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "external/json/json.hpp"

World::World()
  : currentLandIndex_(0),
    justSpawned_(false),
    activeStructure_(nullptr)
{
}

void World::createWorld() {
    std::srand((unsigned)time(nullptr));

    // For each land, store 3 different structure types
    // Land 0 => each structure has 2 rooms
    // Land 1 => 3 rooms
    // Land 2 => 5 rooms

    landStructurePool_.resize(3);
    // land 0 (index=0)
    landStructurePool_[0] = {
        {StructureType::CAVE, 2},
        {StructureType::CASTLE, 2},
        {StructureType::VILLAGE, 2}
    };
    // land 1 (index=1)
    landStructurePool_[1] = {
        {StructureType::CAVE, 3},
        {StructureType::CASTLE, 3},
        {StructureType::VILLAGE, 3}
    };
    // land 2 (index=2)
    landStructurePool_[2] = {
        {StructureType::CAVE, 5},
        {StructureType::CASTLE, 5},
        {StructureType::VILLAGE, 5}
    };
}

bool World::attemptSpawnStructure() {
    if (currentLandIndex_ >= 3) {
        justSpawned_ = false;
        return false;
    }
    // If we've already used up the 3 structures in this land, can't spawn more
    if (landStructurePool_[currentLandIndex_].empty()) {
        justSpawned_ = false;
        return false;
    }

    int roll = std::rand() % 100;
    if (roll < 40) {
        // pick a random index from the pool for this land
        auto &pool = landStructurePool_[currentLandIndex_];
        int pickIndex = std::rand() % pool.size();
        auto stype = pool[pickIndex].first;
        int rooms = pool[pickIndex].second;

        // create a new structure on the heap or in a vector
        structures_.push_back(Structure(stype, rooms)); // e.g. push_back
        activeStructure_ = &structures_.back();         // pointer to newly added item

        pool.erase(pool.begin() + pickIndex);
        justSpawned_ = true;
        return true;
        
    }
    justSpawned_ = false;
    return false;
}

bool World::canProgress(int artifactsCollected) {
    // land 0 => need 3 artifacts
    // land 1 => need 6
    // land 2 => need 9
    int required = (currentLandIndex_ + 1) * 3;
    return (artifactsCollected >= required);
}

bool World::advanceLand() {
    currentLandIndex_++;
    if (currentLandIndex_ >= 3) {
        activeStructure_ = nullptr;  // For absolute safety
        return false;
    }
    activeStructure_ = nullptr;
    return true;
}

std::string World::getLastSpawnedStructureType() const {
    if (!justSpawned_ || !activeStructure_) {
        return "nothing";
    }
    return activeStructure_->getTypeString();
}

Structure& World::getCurrentStructure() {
    return *activeStructure_;
}

// Convert World object to JSON
nlohmann::json World::toJSON() const {
    return {
        {"current_land", currentLandIndex_},
        {"explored_structures", exploredStructures_}
    };
}

// Load World object from JSON
void World::fromJSON(const nlohmann::json& jsonData) {
    currentLandIndex_ = jsonData["current_land"].get<int>();
    exploredStructures_ = jsonData["explored_structures"].get<std::vector<std::string>>();
}
