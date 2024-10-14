#include <stdio.h>
#include <stdlib.h>
#include "main.h"




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
    struct State state;
    state.gameOver = true;
    int i;

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
        printf("%d\n", wallLocs == NULL);
        

        printf("r%d, c%d\n", rows, cols);
        fgetc(f);
        buildGame(&state, f, rows, cols, wallLocs, walls);/*display game based off state*/
        printf("wallLocs[0][0,1] = [%d, %d]\n", wallLocs[0][0],wallLocs[0][1]);

        for (i = 0; i < walls; i++)
        {
            printf("%d, %d\n", wallLocs[i][0],wallLocs[i][1]);
        }

    }
    






    return 0;
}
