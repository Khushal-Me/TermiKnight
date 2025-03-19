#pragma once
#include <string>
#include "Game.h" 
#include "Player.h"
#include "World.h"
#include "external/json/json.hpp"

/**
 * @class SaveManager
 * @brief Manages saving and loading game data.
 * 
 * The SaveManager class handles game state persitence by saving and loading
 * player and world data to and from a save JSON file. It also includes a feature
 * that will auto save and sabe before game termination.
*/
class SaveManager {
public:
    /**
     * @brief Saves current game state to a JSON file.
     * 
     * Serializes the player and world data into JSON format and writes to 
     * a save file.
     * 
     * @param player The Player object to save.
     * @param world The World object to save.
    */
    static void saveGame(const Player& player, const World& world);

    /**
     * @brief Loads a saved game from a JSON file.
     * 
     * Reads the save file and restores the player and world data.
     * 
     * @param player The Player object to restore.
     * @param world The World object to restore.
     * @return true if the game was successfully loaded, false otherwise.
     * 
    */
    static bool loadGame(Player& player, World& world);

    /**
     * @brief Starts an auto-save thread.
     * 
     * Launches a background thread that auto saves the game every 45 sec.
     * 
     * @param player Reference to the Player object.
     * @param world Reference to the World object.
    */
    static void startAutoSave(Player& player, World& world);

    /**
     * @brief Handles the SIGINT (Ctrl+C) signal for game exit.
     * 
     * When user attempts to exit with Ctrl+C, they are prompted if they want to save.
     * 
     * @param signal The Signal number.
    */
    static void handleExitSignal(int signal);
};