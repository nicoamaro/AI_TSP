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
  struct listNode* previousListItem;
}listNode;

typedef struct list{
  struct listNode *firstNode;
  struct listNode *lastNode;
  int elements;
}list;

void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList);
int F(listNode* current, int costToMe, int costToMyFather);
int H(listNode* current);
void SortList (listNode * firstNode);
