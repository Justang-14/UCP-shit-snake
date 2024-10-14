#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct listNode
{
        void* value;
        struct listNode* next;

}listNode;

typedef struct LinkedList
{
    listNode* head;


} LinkedList;

int getValueInt(listNode* node) {
    return *((int*)node->value);
}

void insertFirst(LinkedList* list, void* value) {
    listNode* newNd = (listNode*)malloc(sizeof(listNode));
    newNd->value = value;
    newNd->next = list->head;
    list->head = newNd;
}

int main(int argc, char const *argv[])
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;

    printf("here\n");

    int x = 21;
    insertFirst(list, &x);
    printf("%d\n", getValueInt(list->head));
    

    return 0;
}

