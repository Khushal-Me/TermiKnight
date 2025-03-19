/**
 * @file Enemy.h
 * @brief This file declares the Enemy class, representing an enemy character in the game.
 */

 #pragma once
 #include <string>
 
 /**
  * @brief Represents an enemy character with a type, health, and attack.
  */
 class Enemy {
 public:
     /**
      * @brief Constructs an Enemy object.
      *
      * @param type The type or name of the enemy.
      * @param health The initial health points of the enemy.
      * @param attack The attack power of the enemy.
      */
     Enemy(const std::string &type, int health, int attack);
 
     /**
      * @brief Checks if the enemy is still alive.
      *
      * @return True if the enemy's health is greater than 0, false otherwise.
      */
     bool isAlive() const;
 
     /**
      * @brief Reduces the enemy's health by a given amount.
      *
      * @param dmg The amount of damage to take.
      */
     void takeDamage(int dmg);
 
     /**
      * @brief Gets the attack power of the enemy.
      *
      * @return The attack power of the enemy.
      */
     int getAttack() const;
 
     /**
      * @brief Gets the current health of the enemy.
      *
      * @return The current health points of the enemy.
      */
     int getHealth() const;
 
     /**
      * @brief Gets the type or name of the enemy.
      *
      * @return The type or name of the enemy.
      */
     std::string getType() const;
 
 private:
     /**
      * @brief The type or name of the enemy.
      */
     std::string type_;
     /**
      * @brief The current health points of the enemy.
      */
     int health_;
     /**
      * @brief The attack power of the enemy.
      */
     int attack_;
 
 };