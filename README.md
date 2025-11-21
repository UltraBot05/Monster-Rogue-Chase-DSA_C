# 🧟‍♂️ Monster–Rogue Chase Game  
### **DSA Mini Project — UE24CS252A : Data Structures and its Applications**  
### PESU EC
 Group 17, Section 3A
  Abhigyan Dutta (PES2UG24CS019)
  Akash Singh (PES2UG24CS042)
  A. Sheiman Joshi (PES2UG24CS003)
    
---

## ▶️ Running the Program

### **Compile**
```
gcc DSA_MP_imple.c -o chase_game
```

### **Run**
```
./chase_game
```

Press **Enter** each turn to advance the simulation.

---

## 📌 Project Overview  
This project implements a **15×15 console-based dungeon chase game**, where:

- A **Rogue (R)** tries to maximize distance and escape the Monster  
- A **Monster (M)** uses **BFS shortest-path traversal** to chase the Rogue  
- Both characters spawn **randomly** within the maze  
- The maze contains **walls, corridors, and rooms**, requiring real pathfinding  
- The game ends when the Monster reaches the Rogue  

This project demonstrates **core DSA concepts** from all four units of the syllabus.

Source File → `DSA_MP_imple.c`

---

# 🎯 Features Implemented

### ✔ Random Rogue & Monster spawn  
### ✔ Greedy Rogue Movement (maximize Manhattan distance)  
### ✔ Monster BFS Movement (shortest path)  
### ✔ Linked List Queue ADT  
### ✔ Dynamic Memory Allocation  
### ✔ ASCII Dungeon Rendering  
### ✔ Grid as Implicit Graph  

---


# Implementations (Required in Mini Project)

## Implementation 1 — Random Monster Position
- Maze scanned for all walkable tiles  
- Random monster location selected via  
```
rand(), srand(time(NULL))
```
- Ensures non-overlapping spawn with Rogue  

---

## Implementation 2 — Monster BFS Movement
Monster:
1. Performs BFS from its position  
2. Tracks visited via `dist[][]`  
3. Stores predecessors via `parent[][]`  
4. Locates Rogue  
5. Reconstructs full shortest path  
6. Moves **one** optimal step toward Rogue  

- Accurate BFS implementation.

---

# 🧩 Architecture Summary

```
                +----------------------+
                |      initGame()      |
                | Random Spawn Logic   |
                +----------+-----------+
                           |
                           v
+-------------------+   +--------------------+
|   moveRogue()     |   |   moveMonster()    |
| Greedy Algorithm  |   | BFS Shortest Path  |
+---------+---------+   +----------+---------+
          |                        |
          +------- Rendering ------+
                     v
               +------------+
               | printGame()|
               +------------+
```

---

# 🧵 Data Structures Used

| Data Structure | Purpose |
|----------------|----------|
| Singly Linked List | Queue nodes |
| Queue ADT | BFS exploration |
| Structs | Point, QNode, GameState |
| Grid as Graph | Pathfinding model |
| Dynamic Memory Allocation | QNode creation |
| Arrays | dist[][], parent[][] |

---

# 🧪 Sample Output

```
--- Rogue vs Monster ---
# # # # # # # # # # # # # # #
# . R . . # . . . . . # .   #
# . # # # . # . # # # . # . #
...
Rogue: (3, 7) | Monster: (10, 4)
Press Enter to continue...
```
