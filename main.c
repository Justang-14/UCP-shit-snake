#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "linkedList.h"
#include "terminal.h"
#include "random.h"

/*parse map data and save it in proper locations*/
int buildGame(GameState *state, FILE *f, int rows, int cols, int **wallLocs, int walls) {
    char *line = (char*) malloc(2 * cols * sizeof(char));
    char x;
    int i, j;
    int count = 0;

    for (i = 0; i < rows; i++) {
        fgets(line, 2*cols+2, f);
        for (j = 0; j < cols; j++) {
            x = line[2*j];
            /*assign based on number code*/
            switch (x)
            {
            case '1':
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
    free(line);
    return 0;
}

/*check if ther is an item on a space*/
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

/*check if in-coord are outside the bounds*/
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

/*checks if there is a wall at a space*/
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

/*when playing fog of war this function will diplay the game*/
#ifdef DARK
void displayMap(GameState* state, int** wallLocs, int walls, int cols, int rows) {
    system("clear");
    /*determine the default sight and change it if player has lantern*/
    int sight = 3;
    if (state->hasLantern) {
        sight = 6;
    }
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
            /*determine if player can see the space*/
            if ((abs(j-state->player.x) + abs(i-state->player.y)) <= sight)
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
                    printf(".");
                }
            }
            else
            {
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
#endif

/*if playing easy mode this will display the game*/
#ifndef DARK
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
#endif



int main(int argc, char *argv[]) {
    initRandom();
    char *file = argv[1];
    if (argc > 1) {
        printf("Arguments:\n");
        printf("%s\n", argv[1]);
        
        
    }
    else {
        printf("Must be run with argument <file.txt>\n");
    }

    /*init necessary variables*/
    char dimentions[6];
    int cols, rows, walls;
    GameState* state = (GameState*)malloc(sizeof(GameState));
    state->gameOver = false;
    int i, j;

    FILE *f;
    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("Error: could not open '%s'\n", file);
    }
    else
    {
        /*grab precursor data and consume newlines*/
        fscanf(f, "%d %d", &rows, &cols);
        fgetc(f);
        fscanf(f, "%d", &walls);
        fgetc(f);
        
        int **wallLocs = (int**) malloc(walls * sizeof(int*));
        for (i = 0; i < walls; i++)
        {
            wallLocs[i] = (int*) malloc(2 * sizeof(int));
        }        
        
        /*fgetc(f); ########################uncomment for windows##################################*/
        /*init game*/
        buildGame(state, f, rows, cols, wallLocs, walls);
        fclose(f);

        LinkedList* list;
        listNode* nd;
        list = (LinkedList*)malloc(sizeof(LinkedList));
        list->head = NULL;
        list->count = 0;

        
        

        while (!(state->gameOver))
        {
            int newX;
            int newY;
            bool collision = true;
            char input;
            displayMap(state, wallLocs, walls, cols, rows);
            
            while (collision)
            {
                /*read input*/
                newX = state->player.x;
                newY = state->player.y;
                collision = false;
                disableBuffer();
                scanf(" %c", &input);
                enableBuffer();
                
                /*change player position and check for collisions*/
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

                    /*checks for undo case and removes node from list*/
                case 'u':
                    printf("%d\n", list->count);
                    if (!isEmpty(list))
                    {
                        nd = (GameState*)removeFirst(list);
                        free(state);
                        
                        state = nd->value;
                        free(nd);
                    }
                    break;
                
                default:
                    break;
                }
            }
            
            /*carrry out normal functionality if not undo*/
            if  (input != 'u')
            {
                /*here we store the pre-move state as it should be saved now*/
                insertFirst(list, state);
                GameState* newState = (GameState*)malloc(sizeof(GameState));
                /*copy current state to update with moves*/
                memcpy(newState, state, sizeof(GameState));
                newState->player.x = newX;
                newState->player.y = newY;
                checkItems(newState, newX, newY);
                
                int slitherX = 0;
                int slitherY = 0;
                int snakeX;
                int snakeY;
                /*do snake movement*/
                collision = true;
                while ((slitherX == 0 && slitherY == 0) || collision)
                {
                    snakeX = newState->snake.x;
                    snakeY = newState->snake.y;
                    /*check snake bite*/
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
                /*update current state pointer*/
                state = newState;
                
            }
            
        }
        displayMap(state, wallLocs, walls, cols, rows);
        /*determine outcome*/
        if (state->player.x == state->treasure.x && state->player.y == state->treasure.y)
        {
            printf("\n\n\nCongratulations, you won!\n\n\n");
        }
        else
        {
            printf("You lost, better luck next time\n\n\n");
        }

        /*free memory*/
        free(state);
        while (!isEmpty(list))
        {
            nd = removeFirst(list);
            state = nd->value;
            free(nd);
            free(state);
        }
        free(list);
        for (i = 0; i < walls; i++)
        {
            free(wallLocs[i]);
        } 
        free(wallLocs);
    }
    return 0;
}
