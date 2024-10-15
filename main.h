#ifndef MAIN
typedef enum {false, true}  bool;

struct Position {
    int x;
    int y;
};

typedef struct State {
    struct Position player;
    struct Position snake;
    struct Position lantern;
    struct Position treasure;
    bool hasLantern;
    bool gameOver;
}State;

int buildGame(struct State *state, FILE *f, int rows, int cols, int **wallLocs, int walls);
bool checkWall(int** wallArray, int size, int x, int y);
void displayMap(int** wallLocs, int walls, int cols, int rows);

/*Snippets

for (i = 0; i < walls; i++)
        {
            printf("%d, %d\n", wallLocs[i][0],wallLocs[i][1]);
        }


*/

#define MAIN
#endif