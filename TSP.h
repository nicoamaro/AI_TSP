#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int id;
  int* nextCity;
  int* distance;
}city;

typedef struct {
  int idCurrentCity;
  int totalCost;
  openListNode* father;
  openListNode* nextListItem;
}openListNode;


void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, openListNode* openList, int* closedList);
