/**
 * @file CombatManager.h
 * @brief Declares the CombatManager class responsible for turn-based combat flow.
 */
#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

/**
 * @class CombatManager
 * @brief Provides static methods to run combat between a Player and multiple Enemies.
 *
 * Manages turn order, allows player actions (attack, block, flee, skill), 
 * and processes enemy attacks in turn-based sequence.
 */
class CombatManager {
public:
    /**
     * @brief Starts a combat loop between the player and a list of enemies.
     * @param player Reference to the Player object.
     * @param enemies Vector of Enemy objects in the encounter.
     */
    static void startCombat(Player &player, std::vector<Enemy> &enemies);

private:
    /**
     * @brief Processes the player's turn.
     * @param player Reference to the Player.
     * @param enemies Vector of Enemy objects remaining in combat.
     */
    static void playerTurn(Player &player, std::vector<Enemy> &enemies);
    /**
     * @brief Processes the enemies' turn.
     * @param player Reference to the Player.
     * @param enemies Vector of Enemy objects performing attacks.
     */
    static void enemyTurn(Player &player, std::vector<Enemy> &enemies);
    /**
     * @brief Checks if all enemies in the vector are defeated.
     * @param enemies Vector of Enemy objects to check.
     * @return True if all are defeated (HP <= 0), otherwise false.
     */
    static bool allEnemiesDefeated(const std::vector<Enemy> &enemies);
};
