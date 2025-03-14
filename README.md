# **TermiKnight (Text-Based RPG)**

**TermiKnight** is a **terminal-based** C++ adventure game set in a **modern-day fantasy** world. Players explore **multiple lands**, each containing randomly generated structures (caves, castles, or villages) filled with rooms, enemies, and puzzles. The game features **multiple character classes**, a **turn-based combat system** with **numeric choices**, **riddle-based progression**, and an **inventory system** that supports **weapon-equipping** and **potion usage**. A **SaveManager** automatically persists player progress, ensuring your heroic feats are never lost!

## **Key Features**

1. **Character Classes**  
   - **Civilian**: Higher luck, base health, lower damage  
     - *Skill*: Heal 50% of max health during combat  
   - **Bandit**: Base health, lower luck, higher damage  
     - *Skill*: Greatly improved flee chance  
   - **Mage**: Lower health, high damage, base luck  
     - *Skill*: 50% chance to instantly defeat an enemy  
   - **Soldier**: Higher health, higher damage, lower luck  
     - *Skill*: Double damage on a successful attack  

2. **Stats & Weapon Equipping**  
   - **Health (HP)** – how much damage you can take  
   - **Attack (ATK)** – base damage against enemies  
   - **Luck (LCK)** – influences random outcomes (flee success, certain skills)  
   - **Weapon**: Equipping a weapon from your inventory **increases your Attack** by the weapon’s bonus value.

3. **Exploration & Structures**  
   - Traverse **multiple lands**, each offering random buildings (caves, castles, villages).  
   - Structures contain **1–5 rooms**, the final locked by a **riddle** you must solve for an **artifact**.  
   - Rooms can have **enemy ambushes**, **treasure chests** (loot), or nothing at all.

4. **Choice-Based Turn-Based Combat**  
   - Numeric options for **Attack**, **Block**, **Flee**, **Use Skill**.  
   - Blocking halves incoming damage for the next enemy turn.  
   - Certain class skills increase flee chance (Bandit) or allow double damage (Soldier).  
   - Enemies scale with your current land or your own level (depending on your design).

5. **Inventory & Items**  
   - **Weapons** (grant bonus Attack), **Health Potions** (restore HP), **Artifacts** (quest items).  
   - **Choice-Based** usage: you pick an item by its numeric index in your inventory.  
   - Weapons, once “used,” boost your Attack stat permanently (or until you replace it).

6. **Progression**  
   - Each land demands collecting an **artifact** from a final riddle-locked room.  
   - Accumulate the required artifacts to unlock the next land.  
   - Ultimately, gather all artifacts to break the curse and win the game.

7. **Save/Load**  
   - A **SaveManager** automatically or manually saves your game state (player stats, land progression, inventory).  
   - **Load Game** to restore your progress at any time.

---

## **Project Structure**

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
├── SaveManager.h / SaveManager.cpp      # No longer optional; auto/manual saves
└── Utilities.h / Utilities.cpp          # Random generation or other helpers
```

**Highlights**:
- **`Game.*`**: Manages the main loop, menus, and transitions between exploration and combat.  
- **`CombatManager.*`**: Provides numeric combat menus (1=Attack, 2=Block, etc.).  
- **`Player.*`**: Splits base attack from **weaponBonus_** so equipping a weapon updates the final Attack.  
- **`SaveManager.*`**: Now a core part of the code, regularly autosaves or loads from file.

---

## **How to Build**

1. Ensure you have a modern **C++ compiler** (e.g., `g++ -std=c++17`).  
2. In your **TermiKnight** directory, type:
   ```bash
   make
   ```
   to build. This generates an executable named **`MyRPG`**.

3. **Run** the game:
   ```bash
   ./MyRPG
   ```
4. **Clean** compiled artifacts:
   ```bash
   make clean
   ```

---

## **How to Play**

1. **Main Menu**  
   - **New Game**: Pick your class (Civilian, Bandit, Mage, Soldier) and begin the adventure.  
   - **Load Game**: Load a previously saved file.  
   - **Quit**: Exit the game.

2. **Exploration & Structures**  
   - **Move Forward**: You may discover a new building or eventually unlock the next land.  
   - **Explore**: Enter a structure, revealing multiple rooms – the last one typically locked by a riddle.  
   - **Check Inventory**: Lists items.  
   - **Use Item**: Numeric-based selection – e.g., pick a healing potion to restore HP or equip a new weapon.  
   - **Save** / **Load**: Manage your progress.  
   - **Quit**: Return to main menu or confirm exit.

3. **Combat**  
   - On your turn, a **numeric menu** displays:
     1. **Attack** (deal damage = baseAttack + weaponBonus)  
     2. **Block** (halves incoming damage next turn)  
     3. **Flee** (chance to escape, higher if Bandit skill is active)  
     4. **Use Skill** (class-specific ability, e.g., Mage’s 50% one-shot).  
   - Enemies each have HP and Attack, decreasing your HP on their turn.  
   - Win by defeating all enemies or flee if you must.

4. **Victory**  
   - Solve riddles in final rooms to obtain **artifacts**.  
   - Collect all required artifacts to end the curse and restore balance.

---

## **Future Enhancements**

- **Advanced Quests / NPCs**: Additional side quests, story branching, or shops for buying advanced weapons.  
- **Online Co-Op**: Partner up with friends, each controlling a different character.  
- **OpenAI Integration**: Real-time generated riddles or dynamic NPC conversations.

**Enjoy** the deeper, more customizable combat system with numeric prompts for both **battles** and **item usage**. Now that **SaveManager** is integrated by default, your progress is always safe—go forth and conquer the lands of **TermiKnight**!