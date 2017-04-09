#include "stdbool.h"

bool nextElementIs(listNode* element, listNode* next_element);

bool prevElementIs(listNode* element, listNode* prev_element);

listNode* setNextElement(listNode* element, listNode* next_element);

listNode* setPrevElement(listNode* element, listNode* prev_element);

void putItem(listNode* element, listNode* prev_element);

void putFirstItem(listNode* new_element, listNode* start);

listNode* popItem(listNode* prev_element);

listNode* createItem();

listNode* newList(unsigned int list_len);

void printList(listNode* a);
