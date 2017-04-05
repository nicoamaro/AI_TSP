#include "TSP.h"

int main(int argc, char* argv[])
{
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
}



void switchItems(listNode* a, listNode* b)
{
  listNode* aux= malloc (sizeof(listNode));

  a->prevListItem->nextListItem = b;
  (aux->nextListItem) = (a->nextListItem);
  (aux->prevListItem) = (a->prevListItem);

  (a->nextListItem) = (b->nextListItem);
  (a->prevListItem) = (b->prevListItem);

  (b->nextListItem) = (aux->nextListItem);
  (b->prevListItem) = (aux->prevListItem);



  /*if (NULL!= a->nextListItem && b != a->nextListItem)
  {
    printf("a->nextListItem != NULL\n");
    //a->nextListItem->prevListItem = b;
  }
  if (NULL!= b->nextListItem && a!= b->nextListItem)
  {
    printf("b->nextListItem != NULL\n");
    b->nextListItem->prevListItem = a;
  }

  if (NULL!= a->prevListItem && b != a->prevListItem)
  {
    printf("a->prevListItem != NULL\n");
    a->prevListItem->nextListItem = b->prevListItem->nextListItem;
  }
  if (NULL!= b->prevListItem && a != b->prevListItem)
  {
    printf("b->prevListItem != NULL\n");
    //b->prevListItem->nextListItem = a;
  }

  //aux->prevListItem = a->prevListItem;
  //aux -> nextListItem = a->nextListItem;

  *a->nextListItem = b-> nextListItem;
  //a->prevListItem = b->prevListItem;
  *a->prevListItem = b;

  *b->nextListItem = aux;
  //b->nextListItem = aux -> nextListItem;
  *b->prevListItem = aux -> prevListItem;


  printf("a: %p, b: %p\n",a,b );
  //aux = a;
  //a = b;
  //b = aux;
  printf("a: %p, b: %p\n",a,b );
*/
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
