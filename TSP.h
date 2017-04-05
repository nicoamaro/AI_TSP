#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int id;
  int* nextCity;
  int* distance;
}city;

typedef struct listNode{
  int idCurrentCity;
  int totalCost;
  int father;

  struct listNode* nextListItem;
  struct listNode* prevListItem;
}listNode;


void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList);
int F(listNode* current, int costToMe, int costToMyFather);
int H(listNode* current);
void reordenarOpenList(listNode* openList);
void switchItems(listNode* a, listNode* b);
void printList(listNode* a);
void agregarItem(listNode* currentNode,city* cityArray,int cityNum, int j, listNode* fatherNode, listNode* previousNode );
void tacharRepetidos(listNode* openList);
void borrarItem (listNode* a);
