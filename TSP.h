/*
 * TSP.h
 *
 *  Created on: April 1, 2017
 *  Authors: Amaro Nicolas, Hernando Sebastian, Wajs Ezequiel
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Defines */
#define HEURISTICS_ON  //Para implementar heuristica
/* #define DEBUG */ //Para imprimir LISTAS ABIERTA y CERRADA y otra info

/* Variable type Declarations */
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


/* Functions Declarations */
void initializeCity(city* cityArray, int cityNum);
void populateCity(city* cityArray, int cityNum, char* data);
void TSP(city* cityArray, int cityNum);
void printList(listNode* a);
void addNode(listNode* currentNode,city* cityArray, int j, listNode* fatherNode,  int* dist);
void freeMemory (listNode*a);
int findMinimumDistances (city* cityArray, int* dist, int cityNum);
