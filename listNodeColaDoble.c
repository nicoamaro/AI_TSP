#include "stdbool.h"
#include "listNodeColaDoble.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


bool nextElementIs(listNode* element, listNode* next_element){
    return (element->nextListItem == next_element) ? true : false;
}

bool prevElementIs(listNode* element, listNode* prev_element){
    return (element->prevListItem == prev_element) ? true : false;
}

listNode* setNextElement(listNode* element, listNode* next_element){
    listNode* orfan_element;
    if (NULL!= element){
        orfan_element = element->nextListItem;
        element->nextListItem = next_element;
        return orfan_element;
    }
    return NULL;
}

listNode* setPrevElement(listNode* element, listNode* prev_element){
    listNode* orfan_element;
    if (NULL!= element)
    {
        orfan_element = element->prevListItem;
        element->prevListItem = prev_element;
        return orfan_element;
    }
    return NULL;
}

void putItemAfter(listNode* new_element, listNode* prev_element){
    listNode* orfan_element;
    orfan_element = setNextElement(prev_element, new_element);
    setPrevElement(orfan_element, new_element);
    setNextElement(new_element, orfan_element);
    setPrevElement(new_element,prev_element);
}

void putItemBefore(listNode* new_element, listNode* next_element){
    listNode* orfan_element;

    orfan_element = setPrevElement(next_element,new_element);
    setNextElement(orfan_element, new_element);

    setPrevElement(new_element, orfan_element);
    setNextElement(new_element,next_element);
}

listNode* searchLast(listNode* some_element){
    listNode* last_element = some_element;
    while (NULL != last_element->nextListItem){
        last_element = last_element->nextListItem;
    }
    return last_element;
}

listNode* searchFirst(listNode* some_element){
    listNode* first_element = some_element;
    while (NULL != first_element->prevListItem){
        first_element = first_element->prevListItem;
    }
    return first_element;
}

listNode* popItem(listNode* poped_element){

    if (NULL != poped_element->prevListItem){
        poped_element->prevListItem->nextListItem = poped_element->nextListItem;
    }
    if (NULL != poped_element->nextListItem){
        poped_element->nextListItem->prevListItem = poped_element->prevListItem;
    }



    return poped_element;
}

void switchItems (listNode* a, listNode* b){
    listNode* aux = malloc(sizeof(listNode));
    aux->nextListItem = b->nextListItem;
    aux->prevListItem = b->prevListItem;

    if(a->prevListItem == NULL && a->nextListItem == b){ //El caso en que A sea contiguo de B y sean los primeros dos
        popItem(a);
        putItemAfter(a,b);
        return;
    }

    if(b->prevListItem == NULL && b->nextListItem == a){
        popItem(b);
        putItemAfter(b,a);
        return;
    }

    if(a->nextListItem == NULL && a->prevListItem == b){
        popItem(a);
        putItemBefore(a,b);
        return;
    }
    if(b->nextListItem == NULL && b->prevListItem == a){
        popItem(b);
        putItemBefore(b,a);
        return;
    }

    popItem(b);
    if( NULL != a->nextListItem && b != a->nextListItem){
        putItemBefore(b,a->nextListItem);
    }else if(b != a->prevListItem){
        putItemAfter(b,a->prevListItem);
    }else{
        putItemAfter(b, a);
    }

    popItem(a);
    if( NULL != aux->nextListItem && a != aux->nextListItem){
        //printf("entro aca\n" );
        putItemBefore(a,aux->nextListItem);
    }else if(a != aux->prevListItem){
        putItemAfter(a, aux->prevListItem);
    }else{
        printf("entro aca\n" );
        putItemAfter(a, b);
    }
}

void putItemInfo(listNode* node, int idCurrentCity_data,int totalCost_data, int distance_data){
    node->distance = distance_data;
    node->idCurrentCity = idCurrentCity_data;
    node->totalCost = totalCost_data;
    return;
}

void putItemAsChildOf(listNode*father,listNode* child){
    child->father = father;
    return;
}

listNode* createItem(){

    listNode* new_item = malloc(sizeof(listNode));
    new_item->father = NULL;
    new_item->nextListItem = NULL;
    new_item->prevListItem = NULL;
    return new_item;
}

void cleanItem(listNode* node){
    node->nextListItem = NULL;
    node->prevListItem = NULL;
}

listNode* newList(unsigned int list_len){
    listNode* first_item = createItem();
    listNode* new_item;
    listNode* prev_item = first_item;

    for(int i = 0; i < list_len; i++)
    {
        new_item = createItem();
        setNextElement(prev_item, new_item);
        setPrevElement(new_item, prev_item);
        prev_item = new_item;
    }

    return first_item;
}

void printList(listNode* a){
    listNode* currentNode = a;
    while (NULL != currentNode)
    {
        printf("id=%d, cost=%d\n",currentNode->idCurrentCity, currentNode->totalCost);
        currentNode= currentNode->nextListItem;
    }
}


void printFatherPath(listNode* a){
    listNode* currentNode = a;

    while (NULL != currentNode)
    {
        printf("id=%d, cost=%d\n",currentNode->idCurrentCity, currentNode->distance);
        currentNode= currentNode->father;
    }
}

void reversePrintList(listNode* a){
    listNode* currentNode = a;
    while (NULL != currentNode)
    {
        printf("id=%d, cost=%d\n",currentNode->idCurrentCity, currentNode->totalCost);
        currentNode= currentNode->prevListItem;
    }
}

listNode* orderAZ(listNode* a){
    listNode *b = a->nextListItem;
    listNode *aux;

    while(NULL != a->nextListItem){
        b = a->nextListItem;
        //printf("a: %d\n", a->totalCost);
        while (NULL != b){

            if (a->totalCost > b-> totalCost){
                //printf("\ta: %d\tb: %d\ta>b\n",a->totalCost, b->totalCost);
                switchItems(a,b);
                aux=a;
                a=b;
                b=aux;
            }
            b = b->nextListItem;
        }
        //printList(searchFirst(a));
        a = a->nextListItem;
    }
    return searchFirst(a);
}

listNode* orderZA(listNode* a){
    listNode *b = a->nextListItem;
    listNode *aux;

    while(NULL != a->nextListItem){
        b = a->nextListItem;
        //printf("a: %d\n", a->totalCost);
        while (NULL != b){

            if (a->totalCost < b-> totalCost){
                //printf("\ta: %d\tb: %d\ta>b\n",a->totalCost, b->totalCost);
                switchItems(a,b);
                aux=a;
                a=b;
                b=aux;
            }
            b = b->nextListItem;
        }
        //printList(searchFirst(a));
        a = a->nextListItem;
    }
    return searchFirst(a);
}
