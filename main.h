#ifndef MAIN
typedef enum {false, true}  bool;

struct Position {
    int x;
    int y;
};

struct State {
    struct Position player;
    struct Position snake;
    struct Position lantern;
    struct Position treasure;
    bool hasLantern;
    bool gameOver;
};

int buildGame(struct State *state, FILE *f, int rows, int cols, int **wallLocs, int walls) {
    char *line = (char*) malloc(2 * cols * sizeof(char));
    char x;
    int i, j;
    int count = 0;

    for (i = 0; i < rows; i++) {
        fgets(line, 2*cols+2, f);
        printf("%s\n", line);
        for (j = 0; j < cols; j++) {
            x = line[2*j];
            switch (x)
            {
            case '1':
                /*
                **(wallLocs+count) = j;
                *(*(wallLocs+count) + 1) = i;
                */
                wallLocs[count][0] = j;
                wallLocs[count][1] = i;

                count++;
                break;

            case '2':
                state->lantern.x = j;
                state->lantern.y = i;
                break;

            case '3':
                state->player.x = j;
                state->player.y = i;
                break;

            case '4':
                state->snake.x = j;
                state->snake.y = i;
                break;

            case '5':
                state->treasure.x = j;
                state->treasure.y = i;
                break;
            
            default:

                break;
            }            
        }
    }
    return 0;
}

#define MAIN
#endif