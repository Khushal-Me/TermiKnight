/**
 * @file CombatManager.cpp
 * @brief This file implements the CombatManager class, which handles combat encounters between the player and enemies.
 */
#include "CombatManager.h"
#include <iostream>
#include <cstdlib>
#include "Utilities.h"

/**
 * @brief Flag indicating if the bandit's skill has been applied in the current combat.
 */
bool CombatManager::banditSkillApplied = false;
/**
 * @brief Flag indicating if the soldier's skill has been applied in the current combat.
 */
bool CombatManager::soldierSkillApplied = false;
/**
 * @brief Flag indicating if the player is currently blocking.
 */
bool CombatManager::blocking = false;

/**
 * @brief Constructs a new CombatManager object.
 *
 * Initializes the skill application flags and blocking status to false.
 */
CombatManager::CombatManager() {
    banditSkillApplied = false;
    soldierSkillApplied = false;
    blocking = false;
}
/**
 * @brief Initiates a combat encounter between the player and a group of enemies.
 *
 * This function manages the turn-based combat loop until either all enemies are defeated or the player's health reaches zero.
 *
 * @param player The player participating in the combat.
 * @param enemies A vector of enemies the player is fighting against.
 */
void CombatManager::startCombat(Player &player, std::vector<Enemy> &enemies) {
    //Utilities::clearScreen();
    std::cout << "Combat begins!\n";
    Utilities::waitForEnter();

    while (!allEnemiesDefeated(enemies) && player.getHealth() > 0) {
        playerTurn(player, enemies);
        if (allEnemiesDefeated(enemies) || player.getHealth() <= 0) break;
        enemyTurn(player, enemies);
    }

    if (player.getHealth() <= 0) {
        std::cout << "You have been defeated...\n";
    }
    else {
        std::cout << "All enemies have been vanquished!\n";
        // Potentially reward XP, items, etc.
    }

    Utilities::waitForEnter();
    //Utilities::clearScreen();
}

/**
 * @brief Handles the player's turn during combat.
 *
 * Allows the player to choose an action such as attacking, blocking, fleeing, or using a skill.
 *
 * @param player The player whose turn it is.
 * @param enemies A vector of the enemies currently engaged in combat.
 */
void CombatManager::playerTurn(Player &player, std::vector<Enemy> &enemies) {
    if (enemies.empty()) return;

    // Display a numeric menu instead of waiting for typed input
    Utilities::clearScreen();
    std::cout << "\n--- Player's Turn ---\n";
    std::cout << "1) Attack\n"
              << "2) Block\n"
              << "3) Flee\n"
              << "4) Use Skill\n"
              << "Choice: ";

    int choice;
    if (!(std::cin >> choice)) {
        // Handle bad input, skip turn
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Turn skipped.\n";
        return;
    }
    // discard leftover newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Enemy &target = enemies.front();

    switch (choice) {
    case 1: // Attack
        {
            int damage = player.getAttack();
            if (soldierSkillApplied) {
                damage *= 2;
                soldierSkillApplied = false;
            }
            target.takeDamage(damage);
            std::cout << "You deal " << damage << " damage to the " << target.getType() << ".\n";

            if (!target.isAlive()) {
                std::cout << "The " << target.getType() << " has been defeated.\n";
                enemies.erase(enemies.begin());
            } else {
                // Show updated HP
                for (auto &enemy : enemies) {
                    if (enemy.isAlive()) {
                        std::cout << "[" << enemy.getType() << " HP: "
                                  << enemy.getHealth() << "]\n";
                    }
                }
            }
        }
        break;
    case 2: // Block
        std::cout << "You raise your guard, reducing incoming damage next turn.\n";
        blocking = true;
        break;
    case 3: // Flee
        {
            std::cout << "You attempt to flee...\n";
            bool success = (std::rand() % 100) < (player.getLuck() * 2);
            if (banditSkillApplied) {
                success = (std::rand() % 100) < (player.getLuck() * 4);
                banditSkillApplied = false;
            }
            if (success) {
                std::cout << "You successfully escaped combat!\n";
                enemies.clear();
            } else {
                std::cout << "Failed to flee!\n";
            }
        }
        break;
    case 4: // Use Skill
        {
            int skillResult = player.useSkill();
            // skillResult might indicate which skill was used.
            // For example, if it's a soldier skill, set soldierSkillApplied = true, etc.
            if (skillResult == 2) { // Bandit
                banditSkillApplied = true;
            } else if (skillResult == 3) { // Mage
                int roll = std::rand() % 2;
                if (roll == 1 && !enemies.empty()) {
                    std::cout << "Mage one-shot skill successful!\n";
                    // kill first enemy
                    enemies.front().takeDamage(enemies.front().getHealth());
                    enemies.erase(enemies.begin());
                } else {
                    std::cout << "Mage one-shot skill failed!\n";
                }
            } else if (skillResult == 4) { // Soldier
                soldierSkillApplied = true;
            }
        }
        break;
    default:
        std::cout << "Invalid choice, turn skipped.\n";
        break;
    }

    // Utilities::waitForEnter();
    // Utilities::clearScreen();
}
/**
 * @brief Handles the enemies' turn during combat.
 *
 * Each alive enemy in the combat takes its turn to attack the player.
 *
 * @param player The player being attacked by the enemies.
 * @param enemies A vector of the enemies currently engaged in combat.
 */
void CombatManager::enemyTurn(Player &player, std::vector<Enemy> &enemies) {

    //Utilities::clearScreen();

    for (auto &enemy : enemies) {
        if (enemy.isAlive()) {
            int damage = enemy.getAttack();
            if (blocking){
                damage = damage/2;
                blocking = false; // Reset blocking after enemy turn
            }
            player.takeDamage(damage);
           
            std::cout << enemy.getType() << " hits you for "
                      << damage << " damage! [Player HP: "
                      << player.getHealth() << "]\n";
                      
                      
        }
    }

    Utilities::waitForEnter();
    // Utilities::clearScreen();
}

/**
 * @brief Checks if all enemies in the combat have been defeated.
 *
 * @param enemies A constant reference to the vector of enemies.
 * @return True if all enemies are not alive, false otherwise.
 */
bool CombatManager::allEnemiesDefeated(const std::vector<Enemy> &enemies) {
    for (auto &e : enemies) {
        if (e.isAlive()) return false;
    }
    return true;
}