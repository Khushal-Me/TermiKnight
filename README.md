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

2. **Stats**:  
   - **Health (HP)** – Amount of damage a character can withstand  
   - **Attack (ATK)** – Base damage dealt to enemies  
   - **Luck (LCK)** – Influences random outcomes (e.g., flee success)  

3. **Exploration & Structures**  
   - **Five lands** to traverse, each capable of spawning random buildings  
   - Structures have **1–5 rooms** (number increases with difficulty in later lands)  
   - **Final Room** always guarded by a **riddle**; solving it grants an **artifact**  
   - Rooms may contain **treasure chests**, **random enemies**, or additional events  

4. **Turn-Based Combat**  
   - **Attack**, **Block**, **Flee**, or **Use Skill**  
   - Enemies scale in difficulty based on the current land and the player’s level  

5. **Inventory System & Items**  
   - **Weapons** (alter Attack), **Health Potions**, **Charms** (boost stats), **Artifacts** (primary quest items)  
   - Commands: “CHECK INVENTORY,” “PICK UP <item>,” “USE <potion>,” etc.  

6. **Progression**  
   - Each land requires **collecting an artifact** from the final room of a structure  
   - Accumulate 5 artifacts total to complete the full journey  

7. **Save/Load**  
   - **SAVE GAME** and **LOAD GAME** commands preserve player stats, location, and inventory  

---

## **Project Structure**

```
TermiKnight/
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

- **`main.cpp`**: Entry point, creates `Game` instance and starts the main loop  
- **`Game.*`**: Orchestrates high-level flow (character creation, exploration, main loop, saving/loading)  
- **`Player.*`**: Defines player stats and class-specific abilities  
- **`Enemy.*`**: Describes enemy stats and combat behavior  
- **`CombatManager.*`**: Manages turn-based combat between the player and enemies  
- **`Item.*`, `Inventory.*`**: Manages item details (weapon, potion, charm, artifact) and inventory logic  
- **`Structure.*`**: Represents caves, castles, villages with randomly generated rooms, riddles, and loot  
- **`World.*`**: Maintains the five-land progression and triggers structure encounters  
- **`SaveManager.*`** *(Optional)*: Handles serialization/deserialization for game state  
- **`Utilities.*`**: Random number generation, helper functions, etc.

---

## **Building the Game**

1. Clone or download the **TermiKnight** repository  
2. Open a terminal in the project directory  
3. Compile using a C++17 (or later) compiler (e.g., `g++`):
   ```bash
   g++ -std=c++17 main.cpp Game.cpp Player.cpp Enemy.cpp CombatManager.cpp \
       Item.cpp Inventory.cpp Structure.cpp World.cpp SaveManager.cpp Utilities.cpp \
       -o TermiKnight
   ```
   Adjust filenames if you’ve omitted or merged any.

---

## **How to Play**

1. Run the **`TermiKnight`** executable:
   ```bash
   ./TermiKnight
   ```
2. **Main Menu**  
   - **New Game**: Choose a class (Civilian, Bandit, Mage, Soldier) and begin your journey  
   - **Load Game**: Resume a previously saved adventure  
   - **Quit**: Exit the game  

3. **In-Game Commands**  
   - **MOVE FORWARD**: Explore the land; random structures may appear  
   - **EXPLORE**: Enter a discovered cave/castle/village  
   - **CHECK INVENTORY**: View and manage your items  
   - **ATTACK / BLOCK / FLEE / USE SKILL**: Combat actions against enemies  
   - **SAVE GAME / LOAD GAME**: Save or restore your progress  
   - **QUIT**: Exit to the main menu or end your session  

4. **Progress Through Lands**  
   - Collect each **artifact** from a riddle-locked final room to advance  
   - Combat difficulty and room counts increase in later lands  
   - Achieve victory upon gathering all five artifacts

---

## **Future Enhancements**
- **OpenAI Integration**: Use ChatGPT to dynamically generate riddles or dialogue  
- **Complex NPCs**: More in-depth branching quests and character interactions  
- **Multiplayer / Networking**: Co-op exploration in a shared terminal environment  

**Embark on your TermiKnight journey** and conquer all five lands with skillful combat, cunning puzzle-solving, and strategic item management! Enjoy the challenge!
