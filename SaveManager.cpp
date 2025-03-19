#include "SaveManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <csignal>
#include <thread>
#include <chrono>

using json = nlohmann::json;
namespace fs = std::filesystem;

// Directory and file path for the save data
const std::string SAVE_DIR = "./saves";
const std::string SAVE_FILE = SAVE_DIR + "/save_game.json";

/**
 * @brief Saves the current game state (player and world) to a JSON file.
 * 
 * @param player - The Player object to save
 * @param world - The World object to save
 */
void SaveManager::saveGame(const Player& player, const World& world) {
    json saveData;
    saveData["player"] = player.toJSON(); // Convert player data to JSON
    saveData["world"] = world.toJSON(); // Convert world data to JSON

     // Ensure the save directory exists before writing the file
    if (!fs::exists(SAVE_DIR)) {
        fs::create_directory(SAVE_DIR);
    }

    // Open the save file for writing
    std::ofstream file(SAVE_FILE);
    if (file.is_open()) {
        file << saveData.dump(4); 
        file.close();
        std::cout << "Game saved successfully.\n";
    } else {
        std::cerr << "Error: Could not save the game!\n";
    }
}

/**
 * @brief Loads a saved game from the JSON file.
 * 
 * Reads the save file and restores player and world data.
 * 
 * @param player - The Player object to restore
 * @param world - The World object to restore
 * @return true if loading was successful, false otherwise
 */
bool SaveManager::loadGame(Player& player, World& world) {
    if (!fs::exists(SAVE_FILE)) {
        std::cout << "No save file found. Starting a new game.\n";
        return false;
    }

    // Open the save file for reading
    std::ifstream file(SAVE_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open save file.\n";
        return false;
    }

    json saveData;
    try {
        file >> saveData; // Read JSON data from file
    } catch (const json::parse_error& e) {
        std::cerr << "Error: Corrupted save file! " << e.what() << "\n";
        return false;
    }
    file.close();

    // Restore player and world data from JSON
    try {
        player.fromJSON(saveData["player"]);
        world.fromJSON(saveData["world"]);
    } catch (const std::exception& e) {
        std::cerr << "Error: Save file is missing data! " << e.what() << "\n";
        return false;
    }

    std::cout << "Game loaded successfully.\n";
    return true;
}

/**
 * @brief Starts an auto-save thread that periodically saves the game every 45 seconds.
 * 
 * Launches background thread that auto saves game every 45 seconds.
 * 
 * @param player Reference to the Player object
 * @param world Reference to the World object
 */
void SaveManager::startAutoSave(Player& player, World& world) {
    std::thread([&player, &world]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(45));
            saveGame(player, world); // Automatically saves the game every 45 seconds
        }
    }).detach(); // Detach thread so it runs independently
}

/**
 * @brief Handles the SIGINT (Ctrl+C) signal for safe game exit.
 * 
 * When user attempts to exit using Ctrl+C, they are prompted to save game
 * before quitting.
 * 
 * @param signal The signal number
 */
void SaveManager::handleExitSignal(int signal) {
    std::cout << "\nBefore you quit, would you like to save the game? (y/n): ";
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Saving game before exit...\n";
        // Saving is handled in Game.cpp because we need access to player and world
    }
    std::cout << "Goodbye!\n";
    exit(0);
}
