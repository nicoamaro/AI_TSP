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
//#define DEBUG  //Para imprimir LISTAS ABIERTA y CERRADA y otra info

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
  int isFather;
  struct listNode*  father;

  struct listNode* nextListItem;
  struct listNode* previousListItem;
}listNode;

typedef struct depthNode{
  struct listNode* node;
  struct depthNode* nextDepthNode;
  struct depthNode* previousDepthNode;
}depthNode;


/* Functions Declarations */
void initializeCity(city* cityArray);
void populateCity(city* cityArray, char* data);
void TSP(city* cityArray);
void printList(listNode* a);
void addNode(city* cityArray, int j, listNode* fatherNode,  int* dist, int depth, int* histogram, depthNode** depthList);
void freeMemory (listNode*a);
int findMinimumDistances (city* cityArray, int* dist);
