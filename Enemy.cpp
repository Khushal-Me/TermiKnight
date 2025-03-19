/**
 * @file Enemy.cpp
 * @brief This file implements the Enemy class, representing an enemy character in the game.
 */
#include "Enemy.h"

/**
 * @brief Constructs an Enemy object.
 *
 * @param type The type or name of the enemy.
 * @param health The initial health points of the enemy.
 * @param attack The attack power of the enemy.
 */
Enemy::Enemy(const std::string &type, int health, int attack)
    : type_(type), health_(health), attack_(attack) {
}

/**
 * @brief Checks if the enemy is still alive.
 *
 * @return True if the enemy's health is greater than 0, false otherwise.
 */
bool Enemy::isAlive() const {
    return health_ > 0;
}

/**
 * @brief Reduces the enemy's health by a given amount.
 *
 * If the damage reduces the health below zero, the health is set to zero.
 *
 * @param dmg The amount of damage to take.
 */
void Enemy::takeDamage(int dmg) {
    health_ -= dmg;
    if (health_ < 0) health_ = 0;
}

/**
 * @brief Gets the attack power of the enemy.
 *
 * @return The attack power of the enemy.
 */
int Enemy::getAttack() const {
    return attack_;
}

/**
 * @brief Gets the type or name of the enemy.
 *
 * @return The type or name of the enemy.
 */
std::string Enemy::getType() const {
    return type_;
}

/**
 * @brief Gets the current health of the enemy.
 *
 * @return The current health points of the enemy.
 */
int Enemy::getHealth() const {
    return health_;
}