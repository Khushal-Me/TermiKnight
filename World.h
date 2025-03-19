/**
 * @file World.h
 * @brief Defines the World class for managing game world progression and structures.
 */

#pragma once
#include <string>
#include <vector>
#include "Structure.h"
#include "external/json/json.hpp"

/**
 * @class World
 * @brief Represents the game world, including lands, structures, and progression mechanics.
 *
 * The World class manages different lands, handles the spawning of structures,
 * tracks explored locations, and determines when the player can advance.
 */
class World {
public:
    /**
     * @brief Constructs a World instance, initializing land and structure states.
     */
    World();

    /**
     * @brief Initializes the world by setting up land structure pools.
     */
    void createWorld();

    /**
     * @brief Attempts to spawn a structure in the current land.
     * @return True if a structure is successfully spawned, otherwise false.
     */
    bool attemptSpawnStructure();

    /**
     * @brief Checks if the player has collected enough artifacts to progress.
     * @param artifactsCollected The number of artifacts collected.
     * @return True if progression is allowed, otherwise false.
     */
    bool canProgress(int artifactsCollected);

    /**
     * @brief Advances the player to the next land if possible.
     * @return False if there are no more lands to explore, otherwise true.
     */
    bool advanceLand();

    /**
     * @brief Retrieves the type of the last spawned structure.
     * @return The name of the last spawned structure, or "nothing" if none was spawned.
     */
    std::string getLastSpawnedStructureType() const;

    /**
     * @brief Retrieves the currently active structure.
     * @return A reference to the currently active Structure.
     */
    Structure& getCurrentStructure();

    /**
     * @brief Retrieves a list of explored structures.
     * @return A vector of strings representing explored structures.
     */
    std::vector<std::string> getExploredStructures() const;

    /**
     * @brief Marks a structure as explored.
     * @param name The name of the explored structure.
     */
    void markStructureExplored(const std::string& name);

    /**
     * @brief Serializes the World object to JSON.
     * @return A JSON object representing the world state.
     */
    nlohmann::json toJSON() const;

    /**
     * @brief Loads the World object from a JSON representation.
     * @param jsonData The JSON object containing world state information.
     */
    void fromJSON(const nlohmann::json& jsonData);

    /**
     * @brief Retrieves a pointer to the currently active structure.
     * @return A pointer to the active Structure, or nullptr if none is active.
     */
    Structure* getActiveStructurePtr() const {
        return activeStructure_;
    }

private:
    int currentLandIndex_; ///< The index of the current land (0 to 2).
    bool justSpawned_; ///< Indicates whether a structure was just spawned.
    Structure* activeStructure_; ///< Pointer to the currently active structure.
    std::vector<std::string> exploredStructures_; ///< List of explored structures.

    /**
     * @brief Stores available structures for each land.
     * 
     * Each land has a vector of structure blueprints, represented as pairs of 
     * StructureType and room count. These are removed as they are spawned.
     */
    std::vector<std::vector<std::pair<StructureType,int>>> landStructurePool_;

    std::vector<Structure> structures_; ///< List of structures in the world.
};
