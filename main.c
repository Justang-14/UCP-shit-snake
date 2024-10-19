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
    else if (y < 0 || y >= rows)
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
    system("clear");
    int i, j;
    for (i = 0; i < cols + 2; i++)
    {
        printf("*");
    }
    printf("\n");
    
    for (i = 0; i < rows; i++)
    {
        printf("*");
        for (j = 0; j < cols; j++)
        {
            if (checkWall(wallLocs, walls, j, i))
            {
                printf("O");
            }
            else if (state->snake.x == j && state->snake.y == i)
            {
                printf("~");
            }
            else if (state->player.x == j && state->player.y == i)
            {
                printf("P");
            }
            else if (state->lantern.x == j && state->lantern.y == i && !state->hasLantern)
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
    printf("Press 'a' to move up\n");
    printf("Press 's' to move down\n");
    printf("Press 'a' to move left\n");
    printf("Press 'd' to move right\n");
    printf("Press 'u' to undo\n");
}





int main(int argc, char *argv[]) {
    initRandom();
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
        

        while (!(state->gameOver))
        {
            int newX;
            int newY;
            bool collision = true;
            char input;
            displayMap(state, wallLocs, walls, cols, rows);
            
            while (collision)
            {
                newX = state->player.x;
                newY = state->player.y;
                collision = false;
                disableBuffer();
                scanf(" %c", &input);
                enableBuffer();
                
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

                case 'u':
                    printf("%d\n", list->count);
                    if (!isEmpty(list))
                    {
                        state = (GameState*)removeFirst(list)->value;
                    }
                    break;
                
                default:
                    break;
                }
            }
            
            if  (input != 'u')
            {
                GameState* newState = (GameState*)malloc(sizeof(GameState));
                memcpy(newState, state, sizeof(GameState));
                newState->player.x = newX;
                newState->player.y = newY;
                checkItems(newState, newX, newY);
                
                int slitherX = 0;
                int slitherY = 0;
                int snakeX;
                int snakeY;
                collision = true;
                while ((slitherX == 0 && slitherY == 0) || collision)
                {
                    snakeX = newState->snake.x;
                    snakeY = newState->snake.y;
                    if (abs(snakeX-state->player.x) <= 1 && abs(snakeY-state->player.y) <= 1)
                    {
                        snakeX = newState->player.x;
                        snakeY = newState->player.y;
                        slitherX = 1;
                        collision = false;
                        newState->gameOver = true;
                    }
                    else
                    {
                        slitherX = randomUCP(-1, 1);
                        slitherY = randomUCP(-1, 1);
                        snakeX += slitherX;
                        snakeY += slitherY;
                        collision = checkWall(wallLocs, walls, snakeX, snakeY) || checkBounds(snakeX, snakeY, cols, rows);
                    }
                }
                newState->snake.x = snakeX;
                newState->snake.y = snakeY;
                
                state = newState;
                insertFirst(list, newState);
            }
            
        }
        displayMap(state, wallLocs, walls, cols, rows);
        if (state->player.x == state->treasure.x && state->player.y == state->treasure.y)
        {
            printf("\n\n\nCongratulations, you won!\n\n\n");
        }
        else
        {
            printf("You lost, better luck next time\n\n\n");
        }
        

    }
    






    return 0;
}
