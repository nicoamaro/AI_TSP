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

  struct listNode* father;
  struct listNode* nextListItem;
  struct listNode* previousListItem;
}listNode;


void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList);
int F(listNode* current, int costToMe, int costToMyFather);
int H(listNode* current);
void sortList(listNode* openList);
void switchItems(listNode* a, listNode* b);
void printList(listNode* a);
listNode* createItem(city* cityArray,int cityNum, int j, listNode* fatherNode);
void addItem(listNode* item, listNode* listEnd);
void crop(listNode* openList);
void deleteItem(listNode* a);
