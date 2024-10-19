#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"



int getValueInt(listNode* node) {
    return *((int*)node->value);
}

int isEmpty(LinkedList* list) {
    int value = 0;
    if (list->count == 0)
    {
        value = 1;
    }
    return value;
}

void insertFirst(LinkedList* list, void* value) {
    listNode* newNd = (listNode*)malloc(sizeof(listNode));
    newNd->value = value;
    newNd->next = list->head;
    list->head = newNd;
    list->count++;
}

listNode *removeFirst(LinkedList* list) {
    listNode* exNd = list->head;
    list->head = list->head->next;
    list->count--;
    return exNd;
}

int mainOff(int argc, char const *argv[])
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->count = 0;

    printf("here\n");

    int x = 21;
    insertFirst(list, &x);
    printf("%d\n", getValueInt(list->head));
    printf("%d\n", getValueInt(removeFirst(list)));
    

    return 0;
}

