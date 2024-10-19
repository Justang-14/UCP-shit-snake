#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "linkedList.h"
#include "terminal.h"
#include "random.h"

int buildGame(GameState *state, FILE *f, int rows, int cols, int **wallLocs, int walls) {
    char *line = (char*) malloc(2 * cols * sizeof(char));
    char x;
    int i, j;
    int count = 0;

    for (i = 0; i < rows; i++) {
        fgets(line, 2*cols+2, f);
        /*printf("%s\n", line);*/
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

void checkItems(GameState* state, int x, int y) {
    if (state->lantern.x == x && state->lantern.y == y)
    {
        state->hasLantern = true;
    }
    if (state->treasure.x == x && state->treasure.y == y)
    {
        state->gameOver = true;
    }
}

bool checkBounds(int x, int y, int cols, int rows) {
    bool hit = false;
    if (x < 0 || x >= cols)
    {
        hit = true;
    }
    else if (y < 0 || y >= cols)
    {
        hit = true;
    }
    return hit;
}

bool checkWall(int** wallArray, int size, int x, int y) {
    bool yesWall = false;
    int i;
    for(i = 0; i < size; i++) {
        if(x == wallArray[i][0] && y == wallArray[i][1]) {
            yesWall  = true;
        }
    }
    return yesWall;
}

void displayMap(GameState* state, int** wallLocs, int walls, int cols, int rows) {
    int i, j;
    for (i = 0; i < cols + 2; i++)
        {
            printf("*");
        }
        printf("\n");
        
        for (i = 0; i < rows + 2; i++)
        {
            printf("*");
            for (j = 0; j < cols; j++)
            {
                if (checkWall(wallLocs, walls, j, i))
                {
                    printf("O");
                }
                else if (state->player.x == j && state->player.y == i)
                {
                    printf("P");
                }
                else if (state->snake.x == j && state->snake.y == i)
                {
                    printf("~");
                }
                else if (state->lantern.x == j && state->lantern.y == i)
                {
                    printf("@");
                }
                else if (state->treasure.x == j && state->treasure.y == i)
                {
                    printf("$");
                }
                else {
                    printf(" ");
                }
            }
            printf("*\n");
        }
        
        for (i = 0; i < cols + 2; i++)
        {
            printf("*");
        }
        printf("\n");
}

/*
int main2(int argc, char *argv[])  {
    readGameFile();
    struct state = makeState();
    char[] history;


}*/


/*The strat is to store location for walls, player, snake, lantern, treasure */

/*void* doshit(int cols, int rows) {
    int map[cols][rows];//malloc this shit, maybe as a struct for state|no state should be like git
    fgets(line, 30, fp)
}*/





int main(int argc, char *argv[]) {
    char *file = argv[1];
    if (argc > 1) {
        printf("Arguments:\n");
        printf("%s\n", argv[1]);
        
        
    }
    else {
        printf("Handle exit\n");
    }

    char dimentions[6];
    int cols, rows, walls;
    GameState* state = (GameState*)malloc(sizeof(GameState));
    state->gameOver = false;
    int i, j;

    FILE *f;
    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("here\n");
        printf("Error: could not open '%s'\n", file);
    }
    else
    {
        /*dimentions are stored inline: 15 20*/
        fscanf(f, "%d %d", &rows, &cols);
        fgetc(f);
        fscanf(f, "%d", &walls);
        fgetc(f);
        printf("%d\n", walls);

        
        int **wallLocs = (int**) malloc(walls * sizeof(int*));
        for (i = 0; i < walls; i++)
        {
            wallLocs[i] = (int*) malloc(2 * sizeof(int));
        }        

        /*printf("r%d, c%d\n", rows, cols);*/
        fgetc(f);
        buildGame(state, f, rows, cols, wallLocs, walls);/*display game based off state*/

        LinkedList* list;
        list = (LinkedList*)malloc(sizeof(LinkedList));
        list->head = NULL;
        list->count = 0;

        insertFirst(list, state);
        

        while (true)
        {
            int newX = state->player.x;
            int newY = state->player.y;
            bool collision = false;
            
            char input;
            displayMap(state, wallLocs, walls, cols, rows);
            disableBuffer();
            scanf(" %c", &input);
            enableBuffer;
            
            switch (input)
            {
            case 'w':
                newY--;
                collision = checkWall(wallLocs, walls, newX, newY) || checkBounds(newX, newY, cols, rows);
                break;
            
            case 'a':
                newX--;
                collision = checkWall(wallLocs, walls, newX, newY) || checkBounds(newX, newY, cols, rows);
                break;

            case 's':
                newY++;
                collision = checkWall(wallLocs, walls, newX, newY) || checkBounds(newX, newY, cols, rows);
                break;

            case 'd':
                newX++;
                collision = checkWall(wallLocs, walls, newX, newY) || checkBounds(newX, newY, cols, rows);
                break;
            
            default:
                break;
            }
            
            if (!collision)
            {
                GameState* newState = (GameState*)malloc(sizeof(GameState));
                memcpy(newState, state, sizeof(GameState));
                newState->player.x = newX;
                newState->player.y = newY;
                checkItems(newState, newX, newY);
                insertFirst(list, newState);
                state = newState;
            }
        }
        

    }
    






    return 0;
}
