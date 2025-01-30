// World.h
#pragma once
#include <vector>
#include "Structure.h"

class World {
public:
    World();

    void createWorld();  
    void attemptSpawnStructure();  
    bool canProgress(int artifactsCollected) const;
    void advanceLand();

private:
    int currentLandIndex_;
    // Possibly store structures or a concept of "active structure" for the land
    // 5 lands with increasing difficulty
};
