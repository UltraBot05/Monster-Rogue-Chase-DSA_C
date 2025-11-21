/*
=============================================================================
 Dept. of CSE, PES University, EC Campus, Bangalore
 DSA Mini Project: Monster-Rogue Chase Game
 Author(s):
 Group 17, Section 3A
    Akash Singh (PES2UG24CS042)
    A. Sheiman Joshi (PES2UG24CS003)
    Abhigyan Dutta (PES2UG24CS019)
    Date: November 5, 2025
============================================================================================================================================
 MONSTER-ROGUE CHASE GAME
  Build a console-based grid game on an N × N dungeon where a monster chases a rogue, and the rogue tries to avoid capture as long as possible.
  The dungeon contains walls, rooms, and corridors, and both characters move turn by turn.
  The monster uses a strategy to move one step closer to the rogue using shortest-path search (BFS/DFS),
  while the rogue moves to the adjacent square that maximizes distance from the monster. The game ends when the monster reaches the rogue.
============================================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // For random spawn
#define N 15

// Struct to hold (row, col) coordinates
typedef struct {
    int r, c;
} Point;

// A node in the linked list queue
typedef struct QNode {
    Point p;
    struct QNode* next;
} QNode;

// The queue structure
typedef struct {
    QNode *front, *rear;
} Queue;

// Queue creation
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue operation
void enqueue(Queue* q, Point p) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->p = p;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Dequeue operation
Point dequeue(Queue* q) {
    if (q->front == NULL)
        return (Point){-1, -1};

    QNode* temp = q->front;
    Point p = temp->p;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return p;
}

int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q))
        dequeue(q);
    free(q);
}

// Struct to hold game state
typedef struct {
    char grid[N][N];
    Point roguePos;
    Point monsterPos;
    int gameRunning;
} GameState;

// -------------------- Init Game --------------------
void initGame(GameState* game) {

    // Fill grid with walls
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            game->grid[r][c] = '#';

    // Maze template (KEEPING S and E as EXAMPLES)
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

    // Copy maze layout (S and E will be converted to '.')
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {

            if (maze[r][c] == '#')
                game->grid[r][c] = '#';
            else
                game->grid[r][c] = '.';  // S/E become walkable

        }
    }

    // Collect all free cells ('.')
    Point freeCells[N*N];
    int freeCount = 0;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (game->grid[r][c] == '.') {
                freeCells[freeCount++] = (Point){r, c};
            }
        }
    }

    // Random Rogue spawn
    game->roguePos = freeCells[rand() % freeCount];

    // Random Monster spawn (ENSURE NOT SAME CELL)
    Point temp;
    do {
        temp = freeCells[rand() % freeCount];
    } while (temp.r == game->roguePos.r && temp.c == game->roguePos.c);

    game->monsterPos = temp;

    game->gameRunning = 1;
}

// Clear screen for console
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Print game board
void printGame(GameState* game) {
    clearScreen();
    printf("--- Rogue vs Monster ---\n");

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (r == game->monsterPos.r && c == game->monsterPos.c)
                printf("M ");
            else if (r == game->roguePos.r && c == game->roguePos.c)
                printf("R ");
            else
                printf("%c ", game->grid[r][c]);
        }
        printf("\n");
    }

    printf("Rogue: (%d, %d) | Monster: (%d, %d)\n",
           game->roguePos.r, game->roguePos.c,
           game->monsterPos.r, game->monsterPos.c);

    printf("Press Enter to continue...\n");
}

int isValid(GameState* game, int r, int c) {
    return (r >= 0 && r < N &&
            c >= 0 && c < N &&
            game->grid[r][c] != '#');
}

// Rogue moves greedily (maximize Manhattan distance)
void moveRogue(GameState* game) {
    Point bestMove = game->roguePos;
    int maxDist = -1;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nr = game->roguePos.r + dr[i];
        int nc = game->roguePos.c + dc[i];

        if (isValid(game, nr, nc)) {
            int dist = abs(nr - game->monsterPos.r) +
                       abs(nc - game->monsterPos.c);

            if (dist > maxDist) {
                maxDist = dist;
                bestMove = (Point){nr, nc};
            }
        }
    }

    game->roguePos = bestMove;
}

// -------------------- BFS Monster Movement --------------------
void moveMonster(GameState* game) {

    int dist[N][N];
    Point parent[N][N];
    memset(dist, -1, sizeof(dist));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    Queue* q = createQueue();

    enqueue(q, game->monsterPos);
    dist[game->monsterPos.r][game->monsterPos.c] = 0;
    parent[game->monsterPos.r][game->monsterPos.c] = (Point){-1, -1};

    int found = 0;

    // BFS loop
    while (!isQueueEmpty(q) && !found) {
        Point curr = dequeue(q);

        if (curr.r == game->roguePos.r && curr.c == game->roguePos.c) {
            found = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (isValid(game, nr, nc) && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[curr.r][curr.c] + 1;
                parent[nr][nc] = curr;
                enqueue(q, (Point){nr, nc});
            }
        }
    }

    // Path reconstruction
    if (found) {
        Point step = game->roguePos;

        if (parent[step.r][step.c].r == -1) {
        }
        else {
            while (parent[step.r][step.c].r != game->monsterPos.r ||
                   parent[step.r][step.c].c != game->monsterPos.c)
            {
                step = parent[step.r][step.c];
            }
        }

        game->monsterPos = step;
    }

    freeQueue(q);
}

// -------------------- MAIN --------------------
int main() {
    srand(time(NULL));   // Random seed

    GameState game;
    initGame(&game);

    while (game.gameRunning) {
        printGame(&game);
        while (getchar() != '\n');

        moveRogue(&game);

        if (game.roguePos.r == game.monsterPos.r &&
            game.roguePos.c == game.monsterPos.c) {
            game.gameRunning = 0;
            break;
        }

        moveMonster(&game);

        if (game.roguePos.r == game.monsterPos.r &&
            game.roguePos.c == game.monsterPos.c) {
            game.gameRunning = 0;
            break;
        }
    }

    printGame(&game);
    printf("GAME OVER! Monster caught Rogue at (%d, %d)\n",
           game.roguePos.r, game.roguePos.c);

    return 0;
}
