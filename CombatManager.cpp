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
        // Grant XP or items
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
        
        // If Soldier skill is active, double damage
        // If Mage tries one-shot, 50/50, etc. You can handle logic here or in a skill method.
        target.takeDamage(damage);
        std::cout << "You deal " << damage << " damage to the " << target.getType() << ".\n";

        if (!target.isAlive()) {
            std::cout << "The " << target.getType() << " is defeated.\n";
            enemies.erase(enemies.begin());
        }
    } else if (choice == "BLOCK") {
        std::cout << "You block, reducing incoming damage.\n";
        // You could store a boolean to reduce damage in enemyTurn
    } else if (choice == "FLEE") {
        // If Bandit, higher chance. If luck is high, better chance. 
        // If success, break out of combat or return to previous location.
    } else if (choice == "USE SKILL") {
        player.useSkill();
        // Implementation of skill logic can be immediate or triggered next attack.
    } else {
        std::cout << "Invalid action, turn skipped.\n";
    }
}

void CombatManager::enemyTurn(Player &player, std::vector<Enemy> &enemies) {
    for (auto &enemy : enemies) {
        if (enemy.isAlive()) {
            int damage = enemy.getAttack();
            player.takeDamage(damage);
            std::cout << enemy.getType() << " hits you for " << damage << " damage.\n";
        }
    }
}

bool CombatManager::allEnemiesDefeated(const std::vector<Enemy> &enemies) {
    for (auto &e : enemies) {
        if (e.isAlive()) return false;
    }
    return true;
}
