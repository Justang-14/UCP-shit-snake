#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[]) {
    char *file = argv[1];
    if (argc == 1) {
        printf("Arguments:\n");
        printf("%s\n", argv[1]);
        
        
    }
    else {
        printf("Handle exit\n");
    }

    char line[30];

    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("here\n");
        printf("Error: could not open '%s'\n", file);
    }
    else
    {
        if (fgets(line, 30, fp) == NULL)
        {
            printf("End of file");
        }
        else
        {
            printf("%s\n", line);
        }
    }
    






    return 0;
}
