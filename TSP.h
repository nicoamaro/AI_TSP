#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int id;
  int* nextCity;
  int* distance;
}city;

typedef struct openListNode{
  int idCurrentCity;
  int totalCost;
  struct openListNode* father;
  struct openListNode* nextListItem;
  struct openListNode* previousListItem;
}openListNode;


void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, openListNode* openList, int* closedList);
int F(openListNode* current, int costToMe);
int H(openListNode* current);
