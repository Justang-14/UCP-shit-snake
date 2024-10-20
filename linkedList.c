#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


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
