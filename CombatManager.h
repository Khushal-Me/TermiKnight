// CombatManager.h

#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class CombatManager {
public:
    CombatManager();
    static void startCombat(Player &player, std::vector<Enemy> &enemies);

private:
    static void playerTurn(Player &player, std::vector<Enemy> &enemies);
    static void enemyTurn(Player &player, std::vector<Enemy> &enemies);
    static bool allEnemiesDefeated(const std::vector<Enemy> &enemies);
    static bool banditSkillApplied;
    static bool soldierSkillApplied;
    static bool blocking;
};
