// CombatManager.h

#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class CombatManager {
public:
    static void startCombat(Player &player, std::vector<Enemy> &enemies);

private:
    static void playerTurn(Player &player, std::vector<Enemy> &enemies);
    static void enemyTurn(Player &player, std::vector<Enemy> &enemies);
    static bool allEnemiesDefeated(const std::vector<Enemy> &enemies);

    static void applyClassSkillEffects(Player &player, Enemy &enemy);
};
