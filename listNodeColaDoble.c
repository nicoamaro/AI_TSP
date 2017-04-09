#include "listNodeColaDoble.h"

void listNodeAgregarItem ()
{

}


void listNodeCambiarItems(listNode* a, listNode* b)
{
  listNode* aux= malloc (sizeof(listNode));


  if (NULL!=a->nextListItem)
  {
    printf("a->nextListItem != NULL\n");
    a->nextListItem->previousListItem = b;
  }
  if (NULL!=b->nextListItem)
  {
    printf("b->nextListItem != NULL\n");
    b->nextListItem->previousListItem = a;
  }

  if (NULL!=a->previousListItem)
  {
    printf("a->previousListItem != NULL\n");
    a->previousListItem->nextListItem = b;
  }
  if (NULL!= b->previousListItem)
  {
    printf("b->previousListItem != NULL\n");
    b->previousListItem->nextListItem = a;
  }

  aux->previousListItem = a->previousListItem;
  aux -> nextListItem = a->nextListItem;

  a->nextListItem = b-> nextListItem;
  a->previousListItem = b->previousListItem;

  b->nextListItem = aux -> nextListItem;
  b->previousListItem = aux -> previousListItem;


  //aux=a;
  //a=b;
  //b=aux;
}
