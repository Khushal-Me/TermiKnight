// SaveManager.h
#pragma once
#include <string>
#include "Game.h" // or forward declare if you prefer

class SaveManager {
public:
    static bool saveGame(const Game &game, const std::string &filename);
    static bool loadGame(Game &game, const std::string &filename);
};
