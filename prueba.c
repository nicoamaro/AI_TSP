#include "stdbool.h"
#include "TSP.h"


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

    popItem(b);
    popItem(a);

    if( NULL != a->nextListItem && b != a->nextListItem){
        putItemBefore(b,a->nextListItem);
    }else if(b != a->prevListItem){
        putItemAfter(b,a->prevListItem);
    }else{
        putItemAfter(b, a);
    }

    if( NULL != aux->nextListItem && a != aux->nextListItem){
        putItemBefore(a,aux->nextListItem);
    }else if(a != aux->prevListItem){
        putItemAfter(a, aux->prevListItem);
    }else{
        putItemAfter(a, b);
    }
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
        printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
        currentNode= currentNode->nextListItem;
    }
}

void reversePrintList(listNode* a){
    listNode* currentNode = a;
    while (NULL != currentNode)
    {
        printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
        currentNode= currentNode->prevListItem;
    }
}

listNode* orderAZ(listNode* a){
    listNode *b = a->nextListItem;
    listNode *aux;

    while(NULL != a->nextListItem){
        b = a->nextListItem;
        printf("a: %d\n", a->totalCost);
        while (NULL != b){

            if (a->totalCost > b-> totalCost){
                printf("\ta: %d\tb: %d\ta>b\n",a->totalCost, b->totalCost);
                switchItems(a,b);
                aux=a;
                a=b;
                b=aux;
            }else{
                printf("\ta: %d\tb: %d\n",a->totalCost, b->totalCost);
            }
            b = b->nextListItem;
        }
        printList(searchFirst(a));
        a = a->nextListItem;
    }
    return searchFirst(a);
}

int main(int argc, char* argv[]){
    listNode *first = createItem();
    listNode *a = createItem();
    listNode *b = createItem();
    listNode *c = createItem();
    listNode *d = createItem();
    listNode *e = createItem();
    listNode *f = createItem();
    listNode *last = createItem();

    a->totalCost = 1;
    b->totalCost = 2;
    c->totalCost = 3;
    d->totalCost = 4;
    e->totalCost = 5;
    f->totalCost = 6;


    setNextElement(a,b);
    setNextElement(b,c);
    setNextElement(c,d);

    setPrevElement(d,c);
    setPrevElement(c,b);
    setPrevElement(b,a);

    printf("\nNueva lista\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    putItemAfter(e,b);
    printf("\nAgregamos elemento nro (5) despues del (2)\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    putItemBefore(f,a);
    printf("\nAgregamos elemento nro (6) antes del (1)\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");



    popItem(searchFirst(c));
    printf("\nSacamos el primer elemento\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    popItem(searchLast(c));
    printf("\nSacamos el ultimo elemento\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");



    switchItems(searchLast(c),searchFirst(c));
    printf("\nCambiamos ultimo con primero\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    switchItems(searchFirst(c)->nextListItem->nextListItem,(searchFirst(c))->nextListItem);//Hay un problema, me borra un elemento cuando son dos contiguos ultimos
    printf("\nCambiamos dos contiguos del medio\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    switchItems(searchLast(c)->prevListItem,searchLast(c));
    printf("\nCambiamos dos ultimos\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");

    switchItems(searchFirst(c)->nextListItem,searchFirst(c));//Hay un problema, me borra un elemento cuando son dos contiguos ultimos
    printf("\nCambiamos dos primeros\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");



    /*a=orderAZ(searchFirst(c));
    printf("\nOrdenamos AZ\n");
    printf("----------------------\n");
    printList(searchFirst(c));
    printf("----------------------\n");
    reversePrintList(searchLast(c));
    printf("----------------------\n");
*/


}
