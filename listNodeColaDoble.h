#ifndef listNodeColaDoble_H
#define listNodeColaDoble_H
#include "stdbool.h"

typedef struct listNode{
  int idCurrentCity;
  int totalCost;

  struct listNode* father;

  struct listNode* nextListItem;
  struct listNode* prevListItem;
}listNode;


bool nextElementIs(listNode* element, listNode* next_element);

bool prevElementIs(listNode* element, listNode* prev_element);

listNode* setNextElement(listNode* element, listNode* next_element);

listNode* setPrevElement(listNode* element, listNode* prev_element);

void putItemAfter(listNode* new_element, listNode* prev_element);

void putItemBefore(listNode* new_element, listNode* next_element);

void putItemInfo(listNode* node, int idCurrentCity_data,int totalCost_data);

void putItemAsChildOf(listNode*father,listNode* child);

listNode* searchLast(listNode* some_element);

listNode* searchFirst(listNode* some_element);

listNode* popItem(listNode* poped_element);

void switchItems (listNode* a, listNode* b);

listNode* createItem();

listNode* newList(unsigned int list_len);

void printList(listNode* a);

void printFatherPath(listNode* a);

void reversePrintList(listNode* a);

void cleanItem(listNode* node);

listNode* orderAZ(listNode* a);

listNode* orderZA(listNode* a);

#endif
