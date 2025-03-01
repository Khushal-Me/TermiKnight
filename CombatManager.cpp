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
        std::cout << "All enemies have been vanquished!\n";
        // Potentially reward XP, items, etc.
    }
}

void CombatManager::playerTurn(Player &player, std::vector<Enemy> &enemies) {
    if (enemies.empty()) return;
    std::cout << "Your turn! (ATTACK / BLOCK / FLEE / USE SKILL)\n> ";
    std::string choice;
    std::getline(std::cin, choice);

    Enemy &target = enemies.front(); 
    if (choice == "ATTACK") {
        int damage = player.getAttack();
        // You could add logic for special class skills or a random roll

        target.takeDamage(damage);
        std::cout << "You deal " << damage << " damage to the " << target.getType() << ".\n";

        if (!target.isAlive()) {
            std::cout << "The " << target.getType() << " is defeated.\n";
            enemies.erase(enemies.begin());
        }
    } else if (choice == "BLOCK") {
        std::cout << "You raise your guard, reducing incoming damage next turn.\n";
        // Could store a flag if you'd like
    } else if (choice == "FLEE") {
        std::cout << "You attempt to flee...\n";
        bool success = (std::rand() % 100) < (player.getLuck() * 2); 
        if (success) {
            std::cout << "You successfully escaped combat!\n";
            enemies.clear(); // no more enemies
        } else {
            std::cout << "Failed to flee!\n";
        }
    } else if (choice == "USE SKILL") {
        player.useSkill();
        // Insert logic for class-specific effects (e.g., doubling damage, healing, etc.)
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
