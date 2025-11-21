# 🎮 DSA Mini Project: Monster-Rogue Chase Game

**Dept. of CSE, PES University, EC Campus, Bangalore**  
**Group 17, Section 3A**  
- Akash Singh (PES2UG24CS042)
- A. Sheiman Joshi (PES2UG24CS003)
- Abhigyan Dutta (PES2UG24CS019)

---

## 📋 Problem Statement

Build a console-based grid game on an **N × N dungeon** where:
- A **monster chases a rogue**
- The **rogue tries to avoid capture** as long as possible
- The dungeon contains **walls, rooms, and corridors**
- Both characters **move turn by turn**
- The **monster uses BFS** (shortest-path search) to chase
- The **rogue maximizes distance** from the monster
- Game ends when the **monster catches the rogue**

---

## 🎯 Data Structures Used

### ✅ Linear Data Structure (Required)
**Queue (Linked List Implementation)**
- Used for BFS traversal
- Implements FIFO (First In First Out)
- Operations: `enqueue()`, `dequeue()`, `isEmpty()`

### ✅ Non-Linear Data Structure (Required)
**Graph (Implicit 2D Grid)**
- The N×N dungeon grid represents a graph
- Each cell is a node
- Adjacent walkable cells are edges
- BFS explores this graph structure

---

## 📚 Syllabus Coverage (Unit 3)

✅ **Graphs: Introduction, Properties, Representation**  
✅ **Graph Representation: Adjacency matrix** (2D grid array)  
✅ **Graph Traversal: Breadth First Search (BFS)**  
✅ **Queue Implementation using Linked List** (Unit 2)  
✅ **Application: Shortest path finding in a grid network**

---

## 🔧 How to Compile and Run

```bash
# Compile
gcc DSA_Miniproj.c -o game.exe

# Run
./game.exe
```

---

## 🎮 Gameplay

1. The game displays a 15×15 dungeon grid
2. **R** = Rogue (you), **M** = Monster (chaser), **#** = Wall, **.** = Path
3. Press **Enter** to advance each turn
4. **Rogue moves first** (tries to run away)
5. **Monster moves second** (chases using shortest path)
6. Game continues until Monster catches Rogue

---

## 📖 Complete Code Explanation (Line by Line)

### **Lines 1-20: Header and Problem Statement**
```c
/*
=============================================================================
Dept. of CSE, PES University, EC Campus, Bangalore
DSA Mini Project: Monster-Rogue Chase Game
...
============================================================================
*/
```
**Explanation:** Documentation header with project details, authors, and problem statement.

---

### **Lines 22-26: Include Libraries and Constants**
```c
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>   
#define N 15 // Grid size (N x N)
```
**Explanation:**
- `stdio.h` - Standard input/output (printf, scanf, getchar)
- `stdlib.h` - Memory allocation (malloc, free), system commands
- `string.h` - Memory operations (memset)
- `time.h` - Time functions (currently unused, but kept for potential random features)
- `N 15` - Defines grid size as 15×15 constant

---

### **Lines 28-31: Point Structure**
```c
typedef struct {
    int r, c;
} Point;
```
**Explanation:**
- Creates a structure to hold coordinates
- `r` = row position (0 to N-1)
- `c` = column position (0 to N-1)
- Used for: rogue position, monster position, queue elements
- **Why needed?** Makes it easy to pass around (x,y) coordinates as a single unit

---

### **Lines 33-42: Queue Node and Queue Structures**
```c
// A node in the linked list queue
typedef struct QNode {
    Point p;
    struct QNode* next;
} QNode;

// The queue structure
typedef struct {
    QNode *front, *rear;
} Queue;
```
**Explanation:**

**QNode (Queue Node):**
- Each node stores a `Point` (grid position)
- `next` pointer links to the next node
- This creates a **linked list** structure

**Queue:**
- `front` - pointer to the first element (where we dequeue from)
- `rear` - pointer to the last element (where we enqueue to)
- **Why linked list?** Syllabus requires Queue implementation using linked list (Unit 2)
- **Why needed?** BFS algorithm requires a queue to explore cells level by level

---

### **Lines 44-49: Create Queue Function**
```c
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
```
**Explanation:**
- **Line 45:** Allocates memory for a new Queue structure
- **Line 46:** Initializes both front and rear to NULL (empty queue)
- **Line 47:** Returns pointer to the newly created queue
- **Why needed?** Before using a queue, we must create and initialize it

---

### **Lines 51-64: Enqueue Function**
```c
void enqueue(Queue* q, Point p) {
    QNode* temp = (QNode*)malloc(sizeof(QNode)); // create new node
    temp->p = p;
    temp->next = NULL;

    if (q->rear == NULL) { // if our queue turns out to be empty
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp; 
    q->rear = temp;       
}
```
**Explanation:**
- **Line 52:** Creates a new node for the queue
- **Line 53:** Stores the Point data in the node
- **Line 54:** Sets next to NULL (this will be the last node)
- **Line 56-59:** If queue is empty, make this node both front and rear
- **Line 60:** Link old rear's next to new node
- **Line 61:** Update rear to point to new node
- **How it works:** Adds element to the END of queue (FIFO principle)
- **Why needed?** BFS needs to add newly discovered cells to explore them later

---

### **Lines 66-80: Dequeue Function**
```c
Point dequeue(Queue* q) {
    if (q->front == NULL) { // check for empty queue
        Point empty = {-1, -1};
        return empty; 
    }
    QNode* temp = q->front; // store old front
    Point p = temp->p;
    q->front = q->front->next; 
    if (q->front == NULL) { // if queue became empty
        q->rear = NULL;
    }
    free(temp); // free old front node
    return p;
}
```
**Explanation:**
- **Line 67-70:** Safety check - if queue is empty, return invalid point (-1, -1)
- **Line 71:** Store reference to current front node
- **Line 72:** Extract the Point data from front node
- **Line 73:** Move front pointer to next node
- **Line 74-76:** If queue became empty, set rear to NULL too
- **Line 77:** Free memory of the removed node (prevent memory leak)
- **Line 78:** Return the extracted Point
- **How it works:** Removes element from the FRONT of queue (FIFO principle)
- **Why needed?** BFS needs to get the next cell to explore

---

### **Lines 82-85: IsQueueEmpty Function**
```c
int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}
```
**Explanation:**
- Checks if front pointer is NULL
- Returns 1 (true) if empty, 0 (false) if not empty
- **Why needed?** BFS loop continues while queue is not empty

---

### **Lines 87-93: FreeQueue Function**
```c
void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
```
**Explanation:**
- **Line 88-90:** Dequeue all elements (each dequeue frees a node)
- **Line 91:** Free the queue structure itself
- **Why needed?** Prevent memory leaks - clean up all allocated memory

---

### **Lines 95-101: GameState Structure**
```c
typedef struct {
    char grid[N][N];
    Point roguePos;
    Point monsterPos;
    int gameRunning;
} GameState;
```
**Explanation:**
- **`grid[N][N]`** - 2D array storing the dungeon map
  - `'#'` = wall
  - `'.'` = walkable path
  - This represents our **GRAPH** (non-linear data structure)
- **`roguePos`** - Current position of the rogue
- **`monsterPos`** - Current position of the monster
- **`gameRunning`** - Flag: 1 = game active, 0 = game over
- **Why needed?** Keeps all game data together, avoids global variables (requirement)

---

### **Lines 103-106: InitGame Function Start**
```c
void initGame(GameState* game) {
    for (int r = 0; r < N; r++) {  //walls
        for (int c = 0; c < N; c++) {
            game->grid[r][c] = '#';
```
**Explanation:**
- Takes pointer to GameState as parameter (to modify it)
- Nested loops iterate through every cell in the 15×15 grid
- Initially fills entire grid with walls `'#'`
- **Why?** Start with everything blocked, then carve out the maze

---

### **Lines 110-127: Hardcoded Maze Template**
```c
char maze[N][N] = {
    "###############",
    "#S. . .#..... #",
    "#.###.#.###.#.#",
    "#...#...#...#.#",
    "#.###.#.#.###.#",
    "#.#...#.#.#...#",
    "#.#.###.#.#.#.#",
    "#.#...#...#.#.#",
    "#.###.#####.#.#",
    "#.#...#.....#.#",
    "#.###.#.###.#.#",
    "#.#...#.#...#.#",
    "#.#####.#.###.#",
    "#.....#...#..E#",
    "###############"
};
```
**Explanation:**
- Creates a 15×15 character array with the maze layout
- `#` = walls (boundaries and obstacles)
- `.` = open paths (corridors and rooms)
- `S` = Starting position for Rogue (top-left area)
- `E` = Starting position for Monster (bottom-right area)
- **Why hardcoded?** Ensures interesting maze with guaranteed paths
- **Design:** Creates corridors, rooms, and strategic obstacles

---

### **Lines 129-143: Copy Maze and Find Spawn Points**
```c
for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
        game->grid[r][c] = maze[r][c];
        if (maze[r][c] == 'S') { // Find Rogue start
            game->roguePos.r = r;
            game->roguePos.c = c;
            game->grid[r][c] = '.'; // Change 'S' to a floor '.'
        } else if (maze[r][c] == 'E') { // Find Monster start
            game->monsterPos.r = r;
            game->monsterPos.c = c;
            game->grid[r][c] = '.'; // Change 'E' to a floor '.'
        }
    }
}
```
**Explanation:**
- **Line 131:** Copy each character from maze template to game grid
- **Line 132-136:** When `'S'` is found:
  - Save this position as rogue's starting position
  - Replace `'S'` with `'.'` (so it's a walkable floor)
- **Line 137-141:** When `'E'` is found:
  - Save this position as monster's starting position
  - Replace `'E'` with `'.'` (so it's a walkable floor)
- **Why?** `S` and `E` are only markers for initialization, not displayed during gameplay

---

### **Line 145: Set Game Running Flag**
```c
game->gameRunning = 1;
```
**Explanation:**
- Sets flag to 1 (true) to start the game loop
- Will be set to 0 when monster catches rogue

---

### **Lines 148-154: ClearScreen Function**
```c
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/macOS
    #endif
}
```
**Explanation:**
- **Line 149:** Checks if compiling for Windows
- **Line 150:** Uses Windows command `cls` to clear screen
- **Line 151-152:** For Linux/Mac, uses `clear` command
- **Why needed?** Creates smooth animation by clearing old game state before showing new one

---

### **Lines 156-177: PrintGame Function**
```c
void printGame(GameState* game) {
    clearScreen();
    printf("--- Rogue vs Monster ---\n");
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (r == game->monsterPos.r && c == game->monsterPos.c) {
                printf("M ");
            } else if (r == game->roguePos.r && c == game->roguePos.c) {
                printf("R ");
            } else {
                printf("%c ", game->grid[r][c]);
            }
        }
        printf("\n");
    }
    printf("Rogue: (%d, %d) | Monster: (%d, %d)\n", 
           game->roguePos.r, game->roguePos.c, 
           game->monsterPos.r, game->monsterPos.c);
    printf("Press Enter to continue...\n");
}
```
**Explanation:**
- **Line 157:** Clear previous screen
- **Line 158:** Print title
- **Line 159-173:** Loop through every cell:
  - **Line 161-162:** If cell is monster position, print `'M'` (**checked first!**)
  - **Line 163-164:** If cell is rogue position, print `'R'`
  - **Line 165-166:** Otherwise print the actual grid character (`#` or `.`)
- **Line 169:** Print newline after each row
- **Line 171-173:** Display current coordinates of both characters
- **Why check Monster first?** When they're on same spot (game over), we want to show `'M'` (winner)

---

### **Lines 179-183: IsValid Function**
```c
int isValid(GameState* game, int r, int c) {
    return (r >= 0 && r < N &&  // in row bound
            c >= 0 && c < N &&  // in col bound
            game->grid[r][c] != '#'); // not a wall
}
```
**Explanation:**
- Checks if a cell at (r, c) is a valid move
- **Condition 1:** `r >= 0 && r < N` - row is within bounds
- **Condition 2:** `c >= 0 && c < N` - column is within bounds
- **Condition 3:** `grid[r][c] != '#'` - cell is not a wall
- Returns 1 (true) if ALL conditions met, 0 (false) otherwise
- **Why needed?** Prevents characters from moving out of bounds or through walls

---

### **Lines 185-210: MoveRogue Function**
```c
void moveRogue(GameState* game) {
    Point bestMove = game->roguePos; // default: stay put
    int maxDist = -1;

    // Directions: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nextR = game->roguePos.r + dr[i];
        int nextC = game->roguePos.c + dc[i];

        if (isValid(game, nextR, nextC)) { 
            // calc dist b/w rogue and monster
            int dist = abs(nextR - game->monsterPos.r) + abs(nextC - game->monsterPos.c);
            
            if (dist > maxDist) {
                maxDist = dist;
                bestMove.r = nextR;
                bestMove.c = nextC;
            }
        }
    }
    game->roguePos = bestMove; // update rogue position
}
```
**Explanation:**

**Rogue's Strategy: MAXIMIZE distance from monster**

- **Line 186:** Start with current position as best move
- **Line 187:** Track maximum distance found (-1 initially)
- **Line 190-191:** Arrays for 4 directions:
  - `dr[] = {-1, 1, 0, 0}` - row changes (up, down, no change, no change)
  - `dc[] = {0, 0, -1, 1}` - column changes (no change, no change, left, right)
- **Line 193-207:** Try all 4 adjacent cells:
  - **Line 194-195:** Calculate next cell coordinates
  - **Line 197:** Check if move is valid (in bounds, not wall)
  - **Line 199:** Calculate **Manhattan distance** to monster
    - Manhattan distance = `|x1-x2| + |y1-y2|`
    - Counts "steps" needed to reach destination
  - **Line 201-205:** If this move gives MORE distance than current best:
    - Update maxDist
    - Save this as the best move
- **Line 209:** Apply the best move found

**Why this strategy?** Rogue tries to survive longer by running away from monster

---

### **Lines 212-279: MoveMonster Function (BFS Implementation)**
```c
void moveMonster(GameState* game) {
    // BFS state arrays
    int dist[N][N];
    Point parent[N][N];
    memset(dist, -1, sizeof(dist)); // -1 = unvisited

    // Directions: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Create queue for BFS
    Queue* q = createQueue();

    // Start BFS from monster's position
    enqueue(q, game->monsterPos);
    dist[game->monsterPos.r][game->monsterPos.c] = 0;
    parent[game->monsterPos.r][game->monsterPos.c] = (Point){-1, -1}; // no parent

    int foundRogue = 0;

    // --- BFS Main Loop (Graph Traversal) ---
    while (!isQueueEmpty(q) && !foundRogue) {
        Point curr = dequeue(q);

        if (curr.r == game->roguePos.r && curr.c == game->roguePos.c) {
            foundRogue = 1; // we found the rogue
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextR = curr.r + dr[i];
            int nextC = curr.c + dc[i];

            // Check if neighbor is valid and unvisited
            if (isValid(game, nextR, nextC) && dist[nextR][nextC] == -1) {
                dist[nextR][nextC] = dist[curr.r][curr.c] + 1; // update distance
                parent[nextR][nextC] = curr; // set parent for path
                enqueue(q, (Point){nextR, nextC}); // add to queue
            }
        }
    }

    // --- Path Reconstruction ---
    if (foundRogue) {
        Point step = game->roguePos; // start from rogue
        
        // Backtrack until we find the step adjacent to the monster
        if (parent[step.r][step.c].r == -1) {
            // Rogue is right next to monster (or on same spot)
        } else {
            while (parent[step.r][step.c].r != game->monsterPos.r ||
                   parent[step.r][step.c].c != game->monsterPos.c) {
                step = parent[step.r][step.c]; // go to parent
            }
        }
        // 'step' is now the first move on the shortest path
        game->monsterPos = step;
    }
    // If !foundRogue, monster is trapped and doesn't move
    freeQueue(q); // clean up queue memory
}
```

**Explanation:**

**Monster's Strategy: Use BFS to find SHORTEST PATH to rogue**

#### **Setup Phase (Lines 214-220):**
- **Line 214:** `dist[N][N]` - stores distance from monster to each cell
- **Line 215:** `parent[N][N]` - stores the previous cell in shortest path
- **Line 216:** Initialize all distances to -1 (meaning "not visited yet")
- **Line 219-220:** Direction arrays (same as rogue)

#### **BFS Initialization (Lines 222-229):**
- **Line 223:** Create empty queue
- **Line 226:** Add monster's starting position to queue
- **Line 227:** Monster is distance 0 from itself
- **Line 228:** Monster has no parent (it's the starting point)
- **Line 230:** Flag to track if we found the rogue

#### **BFS Main Loop (Lines 233-254):**

**This is the CORE of the graph traversal algorithm (Unit 3 syllabus)**

- **Line 233:** Continue while queue has cells to explore AND rogue not found
- **Line 234:** Get next cell to explore from front of queue
- **Line 236-239:** If current cell is rogue's position:
  - Set flag and break (found shortest path!)
- **Line 241-253:** Explore all 4 neighbors:
  - **Line 242-243:** Calculate neighbor coordinates
  - **Line 246:** Check if neighbor is valid AND not yet visited
  - **Line 247:** Set neighbor's distance = current distance + 1
  - **Line 248:** Record that we reached neighbor from current cell (for path reconstruction)
  - **Line 249:** Add neighbor to queue (will explore it later)

**How BFS works:**
1. Start from monster position (distance 0)
2. Explore all cells 1 step away (distance 1)
3. Then all cells 2 steps away (distance 2)
4. Continue until rogue is found
5. This GUARANTEES shortest path!

#### **Path Reconstruction (Lines 257-271):**
- **Line 257:** If we found the rogue
- **Line 258:** Start backtracking from rogue's position
- **Line 261-262:** Special case: rogue is right next to monster (path length 1)
- **Line 264-267:** Follow parent pointers backwards until we reach the cell NEXT to monster
  - This gives us the FIRST STEP of the shortest path
- **Line 270:** Move monster to that first step
- **Line 273:** Clean up queue memory

**Why this works?**
- BFS finds shortest path
- But monster only moves ONE step per turn
- So we take the FIRST step of that shortest path
- Next turn, BFS runs again with new positions

---

### **Lines 281-318: Main Function (Game Loop)**
```c
int main() {
    GameState game;
    initGame(&game);

    while (game.gameRunning) {
        printGame(&game);
        while (getchar() != '\n'); // wait for Enter key
        moveRogue(&game);
        // Check for capture after rogue's move
        if (game.roguePos.r == game.monsterPos.r && game.roguePos.c == game.monsterPos.c) {
            game.gameRunning = 0;
            break;
        }
        moveMonster(&game);

        // Check for capture after monster's move
        if (game.roguePos.r == game.monsterPos.r && game.roguePos.c == game.monsterPos.c) {
            game.gameRunning = 0;
            break;
        }
    }

    // Game over screen
    printGame(&game);
    printf("GAME OVER! The Monster caught the Rogue at (%d, %d)!\n", 
           game.roguePos.r, game.roguePos.c);

    return 0;
}
```

**Explanation:**

#### **Initialization (Lines 282-283):**
- **Line 282:** Create GameState variable on stack
- **Line 283:** Initialize game (setup maze, spawn points)

#### **Main Game Loop (Lines 285-305):**
- **Line 285:** Loop continues while `gameRunning` is 1

**Each Turn:**
1. **Line 286:** Display current game state
2. **Line 287:** Wait for user to press Enter (getchar reads characters until newline)
3. **Line 288:** Rogue moves first (tries to run away)
4. **Line 290-293:** Check if rogue moved onto monster's position
   - If yes: game over (rogue got caught)
5. **Line 294:** Monster moves (chases using BFS)
6. **Line 297-300:** Check if monster caught rogue
   - If yes: game over

**Why two checks?**
- Rogue might run into monster (unlikely but possible)
- Monster might catch rogue (most common)

#### **Game Over (Lines 303-306):**
- **Line 304:** Display final board state (will show 'M' at capture position)
- **Line 305-306:** Print game over message with final position
- **Line 308:** Return 0 (successful program execution)

---

## 🎯 Algorithm Summary

### **Rogue's Algorithm (Greedy - Maximize Distance)**
```
1. Look at 4 adjacent cells (up, down, left, right)
2. For each valid cell:
   - Calculate Manhattan distance to monster
3. Move to cell with MAXIMUM distance
4. If all moves are blocked, stay in place
```
**Time Complexity:** O(1) - always checks exactly 4 cells  
**Space Complexity:** O(1) - uses fixed variables

---

### **Monster's Algorithm (BFS - Shortest Path)**
```
1. Create queue and add monster's position
2. Mark monster's position as visited (distance 0)
3. While queue not empty:
   a. Dequeue current cell
   b. If current cell is rogue, FOUND!
   c. For each neighbor (up/down/left/right):
      - If valid and unvisited:
        - Mark as visited
        - Set distance = current distance + 1
        - Set parent to current cell
        - Enqueue neighbor
4. Backtrack from rogue to monster using parent pointers
5. Take FIRST step of that path
```
**Time Complexity:** O(N²) - might visit all cells  
**Space Complexity:** O(N²) - distance, parent arrays, and queue

---

## 🏆 Why This Implementation is Perfect for DSA

### ✅ **No Global Variables**
- Everything passed through function parameters
- All state in `GameState` structure
- Clean, modular design

### ✅ **Linear Data Structure: Queue**
- Implemented using linked list (Unit 2 requirement)
- Dynamic memory allocation
- Proper enqueue/dequeue operations

### ✅ **Non-Linear Data Structure: Graph**
- 2D grid represents implicit graph
- Each cell is a vertex
- Adjacent walkable cells are edges

### ✅ **Graph Traversal: BFS**
- Complete BFS implementation (Unit 3)
- Uses queue for level-order traversal
- Finds shortest path in unweighted graph

### ✅ **Real-World Application**
- Pathfinding in games
- Navigation systems
- AI decision making

### ✅ **Memory Management**
- Proper malloc/free for queue nodes
- No memory leaks
- Clean resource deallocation

---

## 📊 Game Flow Diagram

```
START
  ↓
Initialize Game (setup maze, spawn positions)
  ↓
┌─────────────────────────────────┐
│  GAME LOOP (while running)      │
│                                  │
│  1. Display current game state  │
│  2. Wait for user (Enter key)   │
│  3. Rogue moves (maximize dist) │
│  4. Check if caught → END       │
│  5. Monster moves (BFS chase)   │
│  6. Check if caught → END       │
│                                  │
└─────────────────────────────────┘
  ↓
Display GAME OVER message
  ↓
END
```

---

## 🧠 Key Concepts Demonstrated

1. **Data Structures:**
   - Structures (Point, QNode, Queue, GameState)
   - 2D Arrays (grid representation)
   - Linked Lists (queue implementation)

2. **Algorithms:**
   - BFS (Breadth-First Search)
   - Shortest path finding
   - Greedy approach (rogue movement)

3. **Programming Concepts:**
   - Pointers and dynamic memory
   - Modular functions
   - Conditional compilation (#ifdef)
   - Type definitions (typedef)

4. **Problem Solving:**
   - Graph traversal
   - Pathfinding
   - Game AI strategies

---

## 🎓 Educational Value

This project demonstrates:
- ✅ Understanding of queue operations
- ✅ Graph representation and traversal
- ✅ BFS algorithm implementation
- ✅ Memory management in C
- ✅ Structured programming without globals
- ✅ Practical application of DSA concepts

---

## 🔍 Testing Suggestions

1. **Test Monster AI:** Watch if monster always takes shortest path
2. **Test Rogue AI:** Check if rogue maximizes distance
3. **Test Edge Cases:** What happens if rogue is trapped?
4. **Test Memory:** Run with valgrind to check for leaks
5. **Test Different Mazes:** Modify maze template for variety

---

## 📝 Possible Extensions

1. **Multiple monsters** - Add more chasers
2. **Power-ups** - Temporary speed boost for rogue
3. **Dynamic maze** - Random maze generation
4. **Score system** - Track survival time
5. **Manual control** - Let user control rogue with arrow keys
6. **AI difficulty** - Monster doesn't always use optimal path

---

## ✨ Conclusion

This project successfully implements a console-based chase game that demonstrates:
- Proper use of linear (Queue) and non-linear (Graph) data structures
- Complete BFS algorithm for shortest path finding
- Clean C programming without global variables
- Practical application of DSA concepts from the syllabus

**The monster ALWAYS catches the rogue eventually** because BFS guarantees the shortest path, and the rogue can only maximize distance, not escape forever in a bounded grid!

---

**End of Documentation** 🎮
