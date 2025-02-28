// CombatManager.cpp

#include "CombatManager.h"
#include <iostream>
#include <cstdlib>

void CombatManager::startCombat(Player &player, std::vector<Enemy> &enemies) {
    std::cout << "Combat begins!\n";

    while (!allEnemiesDefeated(enemies) && player.getHealth() > 0) {
        playerTurn(player, enemies);
        if (allEnemiesDefeated(enemies) || player.getHealth() <= 0) break;
        enemyTurn(player, enemies);
    }

    if (player.getHealth() <= 0) {
        std::cout << "You have been defeated...\n";
    } else {
        std::cout << "All enemies defeated!\n";
        // Grant XP or items if desired
    }
}

void CombatManager::playerTurn(Player &player, std::vector<Enemy> &enemies) {
    if (enemies.empty()) return;
    std::cout << "Your turn! (ATTACK / BLOCK / FLEE / USE SKILL)\n> ";
    std::string choice;
    std::getline(std::cin, choice);

    Enemy &target = enemies.front(); // Simple logic: target first enemy
    if (choice == "ATTACK") {
        int damage = player.getAttack();
        
        // Insert class-based logic here if needed:
        // e.g., if Soldier skill is active -> damage *= 2 
        // if Mage skill -> 50% chance of one-shot, etc.

        target.takeDamage(damage);
        std::cout << "You deal " << damage << " damage to the " << target.getType() << ".\n";

        if (!target.isAlive()) {
            std::cout << "The " << target.getType() << " is defeated.\n";
            enemies.erase(enemies.begin());
        }
    } else if (choice == "BLOCK") {
        std::cout << "You block, reducing incoming damage.\n";
        // You could store a boolean or set a "defense mode" for the next enemyTurn
    } else if (choice == "FLEE") {
        // Check player's luck or class skill
        // If success, break out of the combat:
        std::cout << "You attempt to flee...\n";
        bool success = (std::rand() % 100) < (player.getLuck() * 2); // example
        if (success) {
            std::cout << "You escaped combat!\n";
            enemies.clear(); // no more combat
        } else {
            std::cout << "You failed to flee.\n";
        }
    } else if (choice == "USE SKILL") {
        player.useSkill();
        // Implementation depends on your Player class skill logic
    } else {
        std::cout << "Invalid action, turn skipped.\n";
    }
}

void CombatManager::enemyTurn(Player &player, std::vector<Enemy> &enemies) {
    for (auto &enemy : enemies) {
        if (enemy.isAlive()) {
            int damage = enemy.getAttack();
            player.takeDamage(damage);
            std::cout << enemy.getType() << " hits you for " 
                      << damage << " damage.\n";
        }
    }
}

bool CombatManager::allEnemiesDefeated(const std::vector<Enemy> &enemies) {
    for (auto &e : enemies) {
        if (e.isAlive()) return false;
    }
    return true;
}
