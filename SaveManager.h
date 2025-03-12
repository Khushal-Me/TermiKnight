// SaveManager.h
#pragma once
#include <string>
#include "Game.h" // or forward declare if you prefer
#include "Player.h"
#include "World.h"
#include "external/json/json.hpp"


class SaveManager {
public:
    static void saveGame(const Player& player, const World& world);
    static bool loadGame(Player& player, World& world);
    static void startAutoSave(Player& player, World& world);
    static void handleExitSignal(int signal);
};