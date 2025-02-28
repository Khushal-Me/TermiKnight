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
   - **Health (HP)** – Amount of damage you can withstand  
   - **Attack (ATK)** – Base damage dealt to enemies  
   - **Luck (LCK)** – Influences random outcomes (e.g., flee success)

3. **Exploration & Structures**  
   - **Five lands** to traverse, each capable of spawning random buildings  
   - Structures have **1–5 rooms** (increasing in later lands)  
   - The **final room** always has a **riddle**; solving it yields an **artifact**  
   - Rooms may contain **treasure chests**, **random enemies**, or special events

4. **Turn-Based Combat**  
   - **Attack**, **Block**, **Flee**, or **Use Skill**  
   - Enemies scale by land difficulty and the player’s level

5. **Inventory System & Items**  
   - **Weapons** (boost Attack), **Health Potions**, **Charms** (boost stats), **Artifacts** (main quest items)  
   - Commands to check, pick up, or use items

6. **Progression**  
   - Each land requires collecting an **artifact** from a final room  
   - **Gather 5 artifacts** across the lands to complete your quest

7. **Save/Load**  
   - **SAVE GAME** / **LOAD GAME** preserves player stats, land progression, and inventory

---

## **Project Structure**

```
TermiKnight/
├── Makefile
├── main.cpp
├── Game.h / Game.cpp
├── Player.h / Player.cpp
├── Enemy.h / Enemy.cpp
├── Item.h / Item.cpp
├── Inventory.h / Inventory.cpp
├── World.h / World.cpp
├── Structure.h / Structure.cpp
├── CombatManager.h / CombatManager.cpp
├── SaveManager.h / SaveManager.cpp (Optional)
└── Utilities.h / Utilities.cpp
```

- **`main.cpp`**: Launches the `Game`  
- **`Game.*`**: Oversees menus, exploration, progression  
- **`Player.*`**: Holds class-based abilities (Mage, Soldier, etc.) and inventory  
- **`Enemy.*`**: Defines enemy attributes (health, attack)  
- **`CombatManager.*`**: Handles turn-based battles  
- **`Item.*`, `Inventory.*`**: Manages all collectible items (potions, weapons, artifacts)  
- **`Structure.*`**: Rooms, riddles, and loot found in each building  
- **`World.*`**: Land transitions, structure spawning  
- **`SaveManager.*`**: (Optional) For saving/loading game data  
- **`Utilities.*`**: Helper functions (random generation, etc.)

---

## **How to Build**

1. Ensure you have a modern **C++ compiler** (g++ or clang++).  
2. Open a terminal in the **TermiKnight** directory.  
3. Run:
   ```bash
   make
   ```
   This uses the **`Makefile`** to compile all `.cpp` files into an executable named **`MyRPG`**.

4. **Run**:
   ```bash
   ./MyRPG
   ```

5. **Clean** up any compiled files/executable:
   ```bash
   make clean
   ```

---

## **How to Play**

1. **Main Menu**  
   - **New Game**: Choose your class and start the adventure  
   - **Load Game**: Resume a previously saved file (if implemented)  
   - **Quit**: Exit the game

2. **In-Game Menu**  
   - **Move Forward**: Travel the land, discovering random structures  
   - **Explore**: Enter and progress through multi-room structures  
   - **Check Inventory**: View your items (weapons, potions, charms)  
   - **Use Item**: Consume potions, equip weapons, etc.  
   - **Save/Load Game**: Manage your progress  
   - **Quit**: Return to the main menu

3. **Combat**  
   - **Attack**: Deal damage based on your Attack stat  
   - **Block**: Reduce incoming damage  
   - **Flee**: Attempt to escape (influenced by Luck/class)  
   - **Use Skill**: Leverage your class’s unique ability

4. **Victory**  
   - Collect **5** crucial artifacts (one per final room across five lands).  
   - End the curse, restore peace, and complete your heroic journey!

---

## **Future Enhancements**

- **OpenAI Integration**: Dynamically generate riddles or NPC dialogue with ChatGPT  
- **Deep NPC Quests**: Branching stories, side missions, moral choices  
- **Online Co-Op**: Explore the realm with friends via networked sessions  

Enjoy your **TermiKnight** adventure, forging your path through riddles, battles, and epic exploration!