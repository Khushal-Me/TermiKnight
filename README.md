# TermiKnight (Text-Based RPG)

## Introduction

TermiKnight is a terminal-based C++ adventure game set in a modern-day fantasy world. Players embark on an epic journey across multiple lands, exploring mysterious structures filled with enemies, treasures, and puzzles. With multiple character classes, turn-based combat, and a dynamic inventory system, every decision shapes your adventure. The game features an auto-saving system to ensure your progress is never lost.

## Key Features

### Character Classes

Choose from four unique character classes, each with distinct stats and abilities:

- **Civilian** – Higher luck, base health, lower damage.  
  **Skill:** Heal 50% of max health during combat.
- **Bandit** – Base health, lower luck, higher damage.  
  **Skill:** Greatly improved chance to flee from combat.
- **Mage** – Lower health, high damage, base luck.  
  **Skill:** 50% chance to instantly defeat an enemy.
- **Soldier** – Higher health, higher damage, lower luck.  
  **Skill:** Double damage on a successful attack.

### Exploration & Structures

- Traverse multiple lands, each containing **randomized structures** (caves, castles, villages).
- Structures contain **1–5 rooms**, culminating in a locked final room requiring a **riddle** to access a powerful artifact.
- Rooms may contain:
  - **Enemy ambushes** – Prepare for battle!
  - **Treasure chests** – Containing weapons or healing potions.
  - **Empty rooms** – Not every room holds adventure… or does it?

### Choice-Based Turn-Based Combat

- **One-on-one combat**, with enemies appearing back-to-back.
- Strategic choices each turn:
  1. **Attack** – Deal damage (Base Attack + Weapon Bonus).
  2. **Block** – Halve incoming damage on the next enemy turn.
  3. **Flee** – Chance to escape (greatly improved for Bandits).
  4. **Use Skill** – Class-specific abilities to turn the tide of battle.
- Enemies scale according to the land you are in.

### Inventory & Items

Manage your inventory and use items strategically:
- **Weapons** – Equipable swords and other weapons to boost Attack power.
- **Health Potions** – Restore HP in the heat of battle.
- **Artifacts** – Key quest items obtained from riddle-locked rooms.
- **Inventory Management** – Use a numeric-based selection system to equip weapons and consume potions.

### Progression & Story

- Each land holds a **final room with a riddle**; solving it grants an artifact.
- Gather all required artifacts to **break the curse** and complete your quest.
- The story, though simple, sets the stage for an **epic, heroic adventure.**

### Save/Load System

- **Auto-Saving** occurs at key moments.
- **Manual Saving** is available at any time through the menu.
- Quit the game and pick up right where you left off.

## Project Structure

```
TermiKnight/
├── Makefile
├── main.cpp
├── Game.h / Game.cpp        # High-level flow, menus, user input
├── Player.h / Player.cpp    # Manages class, stats, inventory, weapon equip
├── Enemy.h / Enemy.cpp      # Defines enemy attributes & behaviors
├── Item.h / Item.cpp        # Describes potions, weapons, artifacts, etc.
├── Inventory.h / Inventory.cpp
├── World.h / World.cpp      # Tracks lands, structure spawns, progression
├── Structure.h / Structure.cpp
├── CombatManager.h / CombatManager.cpp  # Choice-based turn-by-turn battles
├── SaveManager.h / SaveManager.cpp      # Autosaves and manual saving system
└── Utilities.h / Utilities.cpp          # Random generation or other helpers
```

## How to Build

Ensure you have a modern C++ compiler (e.g., `g++ -std=c++17`).

In the TermiKnight directory, run:

```
make
```

This generates an executable named **MyRPG**.

Run the game:

```
./MyRPG
```

To clean compiled artifacts:

```
make clean
```

## How to Play

### Main Menu

1. **New Game** – Choose your class and begin your adventure.
2. **Load Game** – Restore a previous save.
3. **Quit** – Exit the game.

### Exploration

- **Move Forward** – Discover new locations and unlock the next land.
- **Explore** – Enter structures, navigate rooms, and face challenges.
- **Check Inventory** – View and manage your items.
- **Use Item** – Select weapons or potions by numeric index.
- **Save/Load** – Manage progress at any time.
- **Quit** – Return to the main menu or exit the game.

### Combat

Each turn, select an action from a numeric menu:
- **Attack** – Strike enemies using Base Attack + Weapon Bonus.
- **Block** – Reduce incoming damage on the next turn.
- **Flee** – Attempt to escape (Bandits have a higher success rate).
- **Use Skill** – Leverage unique class abilities for tactical advantage.

Enemies deal damage based on their attack power. Win battles by defeating all enemies or retreating when needed.

### Victory Condition

- Solve riddles to obtain **artifacts**.
- Collect all required artifacts to **end the curse and restore balance**.

## Estimated Playtime

- **Experienced RPG players:** ~25 minutes.
- **New players:** ~45–60 minutes.

## Final Words

Step into the world of **TermiKnight**, where strategy, luck, and combat prowess determine your fate. Will you claim victory and break the curse? The adventure awaits!

---
