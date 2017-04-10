#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEURISTICS_ON
//#define DEBUG

typedef struct {
  int id;
  int* nextCity;
  int* distance;
}city;

typedef struct listNode{
  int idCurrentCity;
  int cost;
  int heuristic;
  struct listNode*  father;

  struct listNode* nextListItem;
  struct listNode* previousListItem;
}listNode;


void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList);
int F(listNode* current, int costToMe, int costToMyFather);
int H(int* dist, int minDistance, int depth, int* path);
void reordenarOpenList(listNode* openList);
void switchItems(listNode* a, listNode* b);
void printList(listNode* a);
void agregarItem(listNode* currentNode,city* cityArray, int j, listNode* fatherNode,  int* dist);
void tacharRepetidos(listNode* openList);
void borrarItem (listNode* a);
void freeMemory (listNode*a);
int findMinimumDistances (city* cityArray, int* dist, int cityNum);
