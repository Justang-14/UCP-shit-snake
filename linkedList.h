/*keep private structs over in the c file, but declare them here for the functions*/
#ifndef LINKEDLIST
#include <stdlib.h>

typedef struct listNode 
{
        void* value;
        struct listNode* next;
}listNode;


typedef struct LinkedList
{
    listNode* head;
    int count;

} LinkedList;

int getValueInt(listNode* node);
void insertFirst(LinkedList* list, void* value);
listNode *removeFirst(LinkedList* list);
int isEmpty(LinkedList* list);


#define LINKEDLIST
#endif