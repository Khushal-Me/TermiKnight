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
    std::cout << "Your turn! (ATTACK / BLOCK / FLEE / USE SKILL)\n> ";
    std::string choice;
    std::getline(std::cin, choice);

    Enemy &target = enemies.front(); 

    if (choice == "ATTACK") {
        int damage = player.getAttack();
        // You could add logic for special class skills or a random roll
        if(soldierSkillApplied){
            damage = damage*2;
            soldierSkillApplied = false;
        }
        target.takeDamage(damage);
        std::cout << "You deal " << damage << " damage to the " << target.getType() << ".\n";

        if (!target.isAlive()) {
            std::cout << "The " << target.getType() << " has been defeated.\n";
            enemies.erase(enemies.begin());
        }
        else {
            for (auto &enemy : enemies) {
                if (enemy.isAlive()) {
                    std::cout << "[" << enemy.getType() << " HP: " << enemy.getHealth() << "]\n";
                }
            }
        }

    } else if (choice == "BLOCK") {
        std::cout << "You raise your guard, reducing incoming damage next turn.\n";
        // store a flag
        blocking = true;

    } else if (choice == "FLEE") {
        std::cout << "You attempt to flee...\n";
        bool success = (std::rand() % 100) < (player.getLuck() * 2); 
        if (banditSkillApplied){
            bool success = (std::rand() % 100) < (player.getLuck() * 4); 
            banditSkillApplied = false;
        }
        if (success) {
            std::cout << "You successfully escaped combat!\n";
            enemies.clear(); // no more enemies
        } 
        else {
            std::cout << "Failed to flee!\n";
        }

    } else if (choice == "USE SKILL") {
        int skill = player.useSkill();
        if (skill == 2) { //bandit skill
            banditSkillApplied = true;
        }
        else if (skill == 3){
            int rand = std::rand() % 2;
            if(rand == 1){
                for (auto &enemy : enemies) {
                    if (enemy.isAlive()) {
                        std::cout << enemy.getType() << " deafeated.\n";
                        enemy.takeDamage(enemy.getHealth());
                        break;
                    }
                }
            }
            else {
                std::cout << "Skill failed!\n";
            } 
        }
        else if (skill == 4){
            soldierSkillApplied = true;
        }
    } 
    else {
        std::cout << "Invalid action, turn skipped.\n";
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
