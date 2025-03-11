// CombatManager.h

#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>


/**
 * @class CombatManager
 * @brief Manages turn-based combat sequences between a Player and one or more Enemies.
 *
 * The CombatManager class provides static methods to initiate, run, and resolve
 * combat interactions. It tracks special conditions (like blocking, class-specific
 * skill usage) and determines when all enemies are defeated or when the player
 * has fallen in battle.
 */
class CombatManager {
public:

    /**
     * @brief Default constructor.
     *
     * Although CombatManager primarily uses static methods, a default constructor
     * is provided. Typically, no instance of this class is created in normal usage.
     */
    CombatManager();
    /**
     * @brief Starts the combat loop between a player and a list of enemies.
     *
     * This static function orchestrates each round of combat until either
     * the player is defeated or all enemies have been removed. It calls
     * playerTurn() and enemyTurn() in succession.
     *
     * @param player The Player initiating combat.
     * @param enemies A vector of Enemies the player must fight.
     */
    static void startCombat(Player &player, std::vector<Enemy> &enemies);

private:
    /**
     * @brief Handles the player's turn in combat.
     *
     * During the player's turn, the player may choose to Attack, Block, Flee,
     * or Use a special Skill. Depending on the choice, this method updates
     * enemy HP or applies relevant status changes (like blocking).
     *
     * @param player The Player engaged in combat.
     * @param enemies A vector of current Enemies in the encounter.
     */
    static void playerTurn(Player &player, std::vector<Enemy> &enemies);

    /**
     * @brief Handles the enemies' turns in combat.
     *
     * Each Enemy attempts to attack if it is still alive. Damage calculations
     * consider whether the player is blocking. If the player is reduced to 0 HP,
     * the combat loop ends.
     *
     * @param player The Player defending against enemy attacks.
     * @param enemies A vector of current Enemies in the encounter.
     */
    static void enemyTurn(Player &player, std::vector<Enemy> &enemies);

    /**
     * @brief Checks whether all enemies in a given list are defeated.
     *
     * @param enemies A vector of Enemies to check.
     * @return True if no Enemies remain alive, otherwise false.
     */
    static bool allEnemiesDefeated(const std::vector<Enemy> &enemies);

     /**
     * @brief Tracks whether the Bandit's special flee skill is applied.
     *
     * If the Bandit skill is used, the chance of fleeing successfully may be
     * higher until reset. This is a simple demonstration field; actual usage
     * may vary in your implementation.
     */
    static bool banditSkillApplied;

    /**
     * @brief Tracks whether the Soldier's double damage skill is active.
     *
     * If the Soldier skill is used, the next attack deals double damage. Once
     * used, it should be reset to false.
     */
    static bool soldierSkillApplied;

    /**
     * @brief Indicates if the player is blocking during the current enemy turn.
     *
     * If the player chooses to Block, incoming damage is reduced. This flag
     * resets each turn.
     */
    static bool blocking;
};
