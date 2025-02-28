# **TermiKnight (Text-Based RPG)**

**TermiKnight** is a **terminal-based** C++ adventure game set in a **modern-day fantasy** world. Players explore **five lands**, each containing randomly generated structures (caves, castles, or villages) filled with rooms, enemies, and puzzles. The game features **multiple character classes**, **turn-based combat**, **riddle-based progression**, and an **inventory system** to collect artifacts and items.

## **Key Features**

1. **Character Classes**  
   - **Civilian**: Higher luck, base health, lower damage  
     - *Skill*: Heal 50% of max health during combat  
   - **Bandit**: Base health, lower luck, higher damage  
     - *Skill*: Greater chance to successfully flee  
   - **Mage**: Lower health, high damage, base luck  
     - *Skill*: 50% chance to instantly defeat an enemy  
   - **Soldier**: Higher health, higher damage, lower luck  
     - *Skill*: Double damage on a successful attack  

2. **Stats**  
   - **Health (HP)** – Amount of damage a character can withstand  
   - **Attack (ATK)** – Base damage dealt to enemies  
   - **Luck (LCK)** – Influences random outcomes (e.g., flee success)  

3. **Exploration & Structures**  
   - **Five lands** to traverse, each capable of spawning random buildings  
   - Structures have **1–5 rooms** (increasing in later lands)  
   - The **final room** always has a **riddle**, granting an **artifact** upon solving  
   - Rooms may contain **treasure chests**, **random enemies**, or extra events  

4. **Turn-Based Combat**  
   - **Attack**, **Block**, **Flee**, or **Use Skill**  
   - Enemies scale with the current land and the player’s level  

5. **Inventory System & Items**  
   - **Weapons** (boost Attack), **Health Potions**, **Charms** (boost stats), **Artifacts** (quest items)  
   - Commands: “CHECK INVENTORY,” “USE <potion>,” “EQUIP <weapon>,” etc.  

6. **Progression**  
   - Each land requires **collecting an artifact** from its final room  
   - **Collect 5 artifacts** to complete the journey  

7. **Save/Load**  
   - **SAVE GAME / LOAD GAME** preserves player stats, land progression, and inventory  

---

## **Project Structure**

```
TermiKnight/
├── Makefile
├── main.cpp
├── Game.h / Game.cpp
├── Player.h / Player.cpp
├── Enemy.h / Enemy.cpp
├── CombatManager.h / CombatManager.cpp
├── Item.h / Item.cpp
├── Inventory.h / Inventory.cpp
├── Structure.h / Structure.cpp
├── World.h / World.cpp
├── SaveManager.h / SaveManager.cpp (Optional)
└── Utilities.h / Utilities.cpp
```

**Description**:
- **`main.cpp`**: Entry point, instantiates `Game` and starts the main loop.  
- **`Game.*`**: Handles main gameplay flow (menus, exploration, etc.).  
- **`Player.*`**: Stores stats (health, attack, luck), class-based skills, and an `Inventory`.  
- **`Enemy.*`**: Simple class for enemy types, health, and attack.  
- **`CombatManager.*`**: Runs turn-based encounters between a `Player` and `Enemy` objects.  
- **`Item.*`, `Inventory.*`**: Manages items (weapons, potions, artifacts) and storing them.  
- **`Structure.*`**: Represents a building/castle/cave, with multiple rooms, riddles, and loot.  
- **`World.*`**: Tracks progression across five lands and triggers structure spawns.  
- **`SaveManager.*`** (optional): Could handle file I/O for game state serialization.  
- **`Utilities.*`** (optional): Random number generation or other helper functions.

---

## **Building the Game**

1. **Ensure** you have a modern C++ compiler (e.g., `g++`).  
2. **Open a terminal** in the **TermiKnight** directory.  
3. **Run**:
   ```bash
   make
   ```
   This executes the **`Makefile`** instructions, compiling each `.cpp` to an object file, then linking into an executable named **`TermiKnight`**.

4. **Run**:
   ```bash
   ./TermiKnight
   ```

5. **Cleaning**:  
   ```bash
   make clean
   ```
   Removes compiled object files and the `TermiKnight` executable.

---

## **How to Play**

1. **Main Menu**  
   - **New Game**: Choose your class (Civilian, Bandit, Mage, Soldier)  
   - **Load Game**: Resume a previous save (if implemented)  
   - **Quit**: Exit the game  

2. **In-Game Menu** (numeric choices)  
   - **Move Forward**: Travel the land, random chance to find a structure  
   - **Explore**: Enter the structure, explore multiple rooms, solve riddles  
   - **Check Inventory**: View items (weapons, potions, charms)  
   - **Use an Item**: Select an item (like a potion) to use  
   - **Save Game / Load Game**: Manage your progress  
   - **Quit**: Return to the main menu or exit  

3. **Combat**  
   - **Attack**: Deal damage based on your Attack stat  
   - **Block**: Reduce incoming damage  
   - **Flee**: Attempt to escape using your Luck or class skill  
   - **Use Skill**: Class-specific abilities (heal, one-shot kill, double damage, etc.)

4. **Progress & Victory**  
   - Each structure’s final room has a riddle-protected **artifact**.  
   - Collect **5 artifacts** across the lands to ultimately break the curse and win!

---

## **Future Enhancements**

- **OpenAI Integration**: Dynamic dialogue or riddle generation via ChatGPT  
- **Rich NPC Interactions**: Multiple story paths, dialogues, quests  
- **Multiplayer**: Cooperative or PvP gameplay via networking libraries  

**Embark on your TermiKnight adventure** and restore peace to the realm through strategy, cunning, and heroic feats. Good luck!