// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(const std::string &type, int health, int attack)
    : type_(type), health_(health), attack_(attack) {
}

bool Enemy::isAlive() const {
    return health_ > 0;
}

void Enemy::takeDamage(int dmg) {
    health_ -= dmg;
    if (health_ < 0) health_ = 0;
}

int Enemy::getAttack() const {
    return attack_;
}

std::string Enemy::getType() const {
    return type_;
}

int Enemy::getHealth() const {
    return health_;
}
