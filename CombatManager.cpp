// CombatManager.cpp
#include "CombatManager.h"
#include <iostream>
#include <cstdlib>

bool CombatManager::banditSkillApplied = false;
bool CombatManager::soldierSkillApplied = false;
bool CombatManager::blocking = false;

CombatManager::CombatManager() { 
    banditSkillApplied = false; 
    soldierSkillApplied = false;
    blocking = false;
}
void CombatManager::startCombat(Player &player, std::vector<Enemy> &enemies) {
    std::cout << "Combat begins!\n";

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
}

void CombatManager::playerTurn(Player &player, std::vector<Enemy> &enemies) {
    if (enemies.empty()) return;

    // Display a numeric menu instead of waiting for typed input
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
}
void CombatManager::enemyTurn(Player &player, std::vector<Enemy> &enemies) {
    for (auto &enemy : enemies) {
        if (enemy.isAlive()) {
            int damage = enemy.getAttack();
            if (blocking){
                damage = damage/2;
            }
            player.takeDamage(damage);
            std::cout << enemy.getType() << " hits you for "
                      << damage << " damage! [Player HP: " 
                      << player.getHealth() << "]\n";
        }
    }
}

bool CombatManager::allEnemiesDefeated(const std::vector<Enemy> &enemies) {
    for (auto &e : enemies) {
        if (e.isAlive()) return false;
    }
    return true;
}
