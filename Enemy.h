// Enemy.h
#pragma once
#include <string>

class Enemy {
public:
    Enemy(const std::string &type, int level, int health, int attack);

    // Stats
    int getLevel() const;
    int getHealth() const;
    int getAttack() const;
    bool isAlive() const;

    void takeDamage(int dmg);

    std::string getType() const;

private:
    std::string type_;
    int level_;
    int health_;
    int attack_;
    int maxHealth_;
};
