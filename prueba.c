#include "stdbool.h"
#include "TSP.h"


bool nextElementIs(listNode* element, listNode* next_element){
    return (element->nextListItem == next_element) ? true : false;
}

bool prevElementIs(listNode* element, listNode* prev_element){
    return (element->prevListItem == prev_element) ? true : false;
}

listNode* setNextElement(listNode* element, listNode* next_element){
    listNode* orfan_element = element->nextListItem;
    element->nextListItem = next_element;
    return orfan_element;
}

listNode* setPrevElement(listNode* element, listNode* prev_element){
    listNode* orfan_element = element->prevListItem;
    element->prevListItem = prev_element;
    return orfan_element;
}

void putItem(listNode* element, listNode* prev_element){
    listNode* orfan_element;
    orfan_element = setNextElement(prev_element, element);
    setPrevElement(orfan_element, element);
}

listNode* popItem(listNode* prev_element){
    listNode* poped_element;
    poped_element = setNextElement(prev_element, prev_element->nextListItem->nextListItem);
    setPrevElement(prev_element->nextListItem->nextListItem, prev_element);

    return poped_element;
}

listNode* createItem(){
    listNode* new_item = malloc(sizeof(listNode));
    new_item->nextListItem = NULL;
    new_item->prevListItem = NULL;
    return new_item;
}

listNode* newList(unsigned int list_len){
    listNode* first_item = createItem();
    listNode* new_item;
    listNode* prev_item = first_item;

    for(int i = 0; i < list_len; i++){
	new_item = createItem();
	setNextElement(prev_item, new_item);
	setPrevElement(new_item, prev_item);
	prev_item = new_item;
    }

    return first_item;
}

void test_newList(){
}

void test_setNextElement(){
}

void printList(listNode* a)
{
  listNode* currentNode = a;
  while (NULL != currentNode)
  {
    printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
    currentNode= currentNode->nextListItem;
  }
}

int main(int argc, char* argv[])
{
    test_newList();
/*
  listNode *aux=malloc(sizeof(listNode));
  listNode *current, *prev, *openList;
  openList = aux;

  openList -> idCurrentCity    = 0;
  openList -> totalCost        = 0;
  openList -> father           = 0;

  openList -> nextListItem     = NULL;
  openList -> prevListItem     = NULL;

  prev=openList;


  for (int i=1;i<5;i++)
  {
    current = malloc(sizeof(listNode));
    current -> idCurrentCity    = i;
    current -> totalCost        = i*i;
    current -> father           = i*i*i;

    current -> nextListItem     = NULL;
    current -> prevListItem     = prev;
    prev-> nextListItem         = current;

    prev = current;

  }
  printList(openList);
  printf("************************\n" );
  printf("probando 2do elemento contra ultimo\n");
  printf("a: %p, b: %p\n",openList, current );
  switchItems(current->prevListItem->prevListItem, current->prevListItem);
  printf("a: %p, b: %p\n",openList, current );
  printf("************************\n" );
  printList(openList);
  */
}

