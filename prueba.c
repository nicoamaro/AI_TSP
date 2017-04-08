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
    listNode* orfan_element;
    if (NULL!= element)
    {
        orfan_element = element->prevListItem;
        element->prevListItem = prev_element;
        return orfan_element;
    }
    return NULL;
}

void putItem(listNode* element, listNode* prev_element){
    listNode* orfan_element;

    orfan_element = setNextElement(prev_element, element);
    setPrevElement(orfan_element, element);
    setNextElement(element, orfan_element);
    setPrevElement(element,prev_element);
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

listNode* newList(unsigned int list_len)
{
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

void test_newList()
{
}

void test_setNextElement()
{
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

void reversePrintList(listNode* a)
{
    listNode* currentNode = a;
    while (NULL != currentNode)
    {
        printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
        currentNode= currentNode->prevListItem;
    }
}

int main(int argc, char* argv[])
{
    listNode *a = createItem();
    listNode *b = createItem();
    listNode *c = createItem();
    listNode *d = createItem();
    listNode *e = createItem();


    a->totalCost = 1;
    b->totalCost = 2;
    c->totalCost = 3;
    d->totalCost = 4;
    e->totalCost = 10;

    setNextElement(a,b);
    setNextElement(b,c);
    setNextElement(c,d);

    setPrevElement(d,c);
    setPrevElement(c,b);
    setPrevElement(b,a);


    printf("----------------------\n");
    printList(a);
    printf("----------------------\n");
    reversePrintList(d);
    printf("----------------------\n");
    printf("**********************\n");

    putItem(e,d);

    printf("----------------------\n");
    printList(a);
    printf("----------------------\n");
    reversePrintList(e);
    printf("----------------------\n");

}
