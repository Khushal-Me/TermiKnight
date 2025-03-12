#pragma once
#include <string>
#include <vector>
#include "Structure.h"

class World {
public:
    World();

    void createWorld();
    bool attemptSpawnStructure();
    bool canProgress(int artifactsCollected);
    bool advanceLand(); // returns false if no more lands
    std::string getLastSpawnedStructureType() const;
    Structure& getCurrentStructure();

    std::vector<std::string> getExploredStructures() const;
    void markStructureExplored(const std::string& name);

    nlohmann::json toJSON() const;
    void fromJSON(const nlohmann::json& jsonData);

private:
    int currentLandIndex_; // 0..2 for 3 lands
    bool justSpawned_;
    Structure* activeStructure_;
    std::vector<std::string> exploredStructures_;

    // For each land, store a vector of structure "blueprints" 
    // or (StructureType, roomCount). We'll remove them as we spawn.
    std::vector<std::vector<std::pair<StructureType,int>>> landStructurePool_; 
};
