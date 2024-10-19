#ifndef MAIN
typedef enum {false, true}  bool;

typedef struct Position {
    int x;
    int y;
}Position;

typedef struct GameState {
    Position player;
    Position snake;
    Position lantern;
    Position treasure;
    bool hasLantern;
    bool gameOver;
}GameState;

void checkItems(GameState* state, int x, int y);
bool checkBounds(int x, int y, int cols, int rows);
int buildGame(struct GameState *state, FILE *f, int rows, int cols, int **wallLocs, int walls);
bool checkWall(int** wallArray, int size, int x, int y);
void displayMap(GameState* state, int** wallLocs, int walls, int cols, int rows);

/*Snippets

for (i = 0; i < walls; i++)
        {
            printf("%d, %d\n", wallLocs[i][0],wallLocs[i][1]);
        }


*/

#define MAIN
#endif