#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listNodeColaDoble.h"

typedef struct {
  int id;
  int* nextCity;
  int* distance;
}city;

void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList);
int F(listNode* current, int costToMe);
int H(listNode* current);
void tacharRepetidos(listNode* openList);
void searchForRedundancy(listNode* openList, int cityNum);
int checkIfLastNode(listNode* node,int cityNum);
