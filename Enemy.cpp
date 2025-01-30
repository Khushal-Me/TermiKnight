// Enemy.cpp

#include "Enemy.h"

Enemy::Enemy(const std::string &type, int level, int health)
    : type_(type), level_(level), health_(health), maxHealth_(health) {}

int Enemy::getLevel() const {
    return level_;
}

int Enemy::getHealth() const {
    return health_;
}

void Enemy::takeDamage(int dmg) {
    health_ -= dmg;
    if (health_ < 0) {
        health_ = 0;
    }
}

std::string Enemy::getType() const {
    return type_;
}

bool Enemy::isAlive() const {
    return (health_ > 0);
}
