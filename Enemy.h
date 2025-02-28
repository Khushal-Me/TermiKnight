#pragma once
#include <string>

class Enemy {
public:
    Enemy(const std::string &type, int health, int attack);

    bool isAlive() const;
    void takeDamage(int dmg);
    int getAttack() const;
    std::string getType() const;

private:
    std::string type_;
    int health_;
    int attack_;
};
