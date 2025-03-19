/**
 * @file Structure.h
 * @brief Defines the Structure class, representing various buildings in the game world.
 */

#pragma once
#include <string>
#include <vector>
#include "Enemy.h"
#include "Item.h"
#include "Player.h"

/**
 * @enum StructureType
 * @brief Enumerates the types of structures that can appear in the game.
 */
enum class StructureType {
    CAVE,    ///< Represents a cave structure.
    CASTLE,  ///< Represents a castle structure.
    VILLAGE, ///< Represents a village structure.
    HOUSE    ///< Represents a house structure.
};

/**
 * @struct Riddle
 * @brief Represents a multiple-choice riddle used in the game.
 */
struct Riddle {
    std::string question;             ///< The riddle question.
    std::vector<std::string> options; ///< The four multiple-choice answers.
    int correctIndex;                 ///< The index (0..3) of the correct answer.
    std::vector<std::string> hints;   ///< Hints to help the player solve the riddle.
};

/**
 * @class Structure
 * @brief Represents a structure in the game that can contain rooms, enemies, and riddles.
 *
 * The Structure class handles the exploration of rooms, managing riddles, spawning enemies,
 * and rewarding the player with artifacts or items.
 */
class Structure {
public:
    /**
     * @brief Constructs a Structure with a specific type and number of rooms.
     * @param type The type of the structure.
     * @param totalRooms The total number of rooms in the structure.
     */
    Structure(StructureType type, int totalRooms);

    /**
     * @brief Retrieves the structure's type as a string.
     * @return The type of the structure as a string.
     */
    std::string getTypeString() const;

    /**
     * @brief Checks if the structure has been fully explored.
     * @return True if all rooms have been explored, otherwise false.
     */
    bool isFullyExplored() const;

    /**
     * @brief Explores the next room in the structure.
     * @param player The player exploring the room.
     * @return True if there are more rooms to explore, otherwise false.
     */
    bool exploreNextRoom(Player &player);

    /**
     * @brief Checks if an artifact was found in the current room.
     * @return True if an artifact was found, otherwise false.
     */
    bool hasFoundArtifactThisRoom() const { return foundArtifactThisRoom_; }

private:
    StructureType type_; ///< The type of the structure.
    int totalRooms_; ///< The total number of rooms in the structure.
    int currentRoomIndex_; ///< The current room index during exploration.
    bool fullyExplored_; ///< Indicates if the structure has been fully explored.
    bool foundArtifactThisRoom_; ///< Indicates if an artifact was found in the current room.

    std::vector<Riddle> riddlePool_; ///< Pool of riddles available for this structure.
    Riddle riddleToAsk_; ///< The selected riddle for the final room.

    /**
     * @brief Initializes the riddle pool for the structure.
     */
    void initRiddles();

    /**
     * @brief Handles a riddle event in the structure.
     * @param player The player attempting to solve the riddle.
     * @return True if the player solves the riddle, otherwise false.
     */
    bool doRiddle(Player &player);

    /**
     * @brief Handles interactions when entering a room.
     * @param player The player exploring the room.
     */
    void handleRoom(Player &player);

    /**
     * @brief Handles interactions when discovering a chest in a room.
     * @param player The player interacting with the chest.
     */
    void handleChest(Player &player);
};
