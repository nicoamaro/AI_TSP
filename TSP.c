/*
 * TSP.c
 *
 *  Created on: April 1, 2017
 *  Authors: Amaro Nicolas, Hernando Sebastian, Wajs Ezequiel
 */


/*Includes */
#include "TSP.h"


int main(int argc, char* argv[])
{
  FILE *importFile;
  char importText[1024];
  int cityNum, len;
  char* delimiter;
  
  if(argc != 2)
  {
    printf("Debe pasar el archivo como parámetro\n");
    return 1;
  }
  //********** EMPIEZO A CONTAR TIEMPO DESDE ACA **********
  clock_t startTime = clock();
  
  importFile = fopen(argv[1], "r");
  fgets(importText, 1024, importFile);
  delimiter = strchr(importText,';');
  *delimiter = '\0';
  cityNum = atoi(importText);
  printf("%d\n", cityNum);
  city cityArray[cityNum];
  initializeCity(cityArray, cityNum);
  fgets(importText, 1024, importFile);
  populateCity(cityArray, cityNum, importText);
  TSP(cityArray, cityNum);
  clock_t endTime = clock();
  //********** TERMINE DE CONTAR TIEMPO ACA **********
  double executionTime = (double)1000*(endTime - startTime) / CLOCKS_PER_SEC;
  printf("Tiempo de ejecucion = %f ms\n\n", executionTime);
  return 0;
}

/*--------------------------------------------------------------------------------
 * Function:    findMinimumDistances
 *
 * @brief       Calcula la distancia minima como la suma de los promedios de
 *              las 2 distancias minimas de cada ciudad.
 * 
 * @param[in]	city* cityArray	- Array que contiene la info de todas las ciudades.
 * @param[in]	int* dist       - Direccion de vector donde se van a guardar las 
 *                                segundas minimas distancias de cada ciudad. 
 * @param[in]	int cityNum     - Cantidad de ciudades.
 *
 *
 * @return 	int distance    - Distancia minima calculada (h[0])
 --------------------------------------------------------------------------------*/
int findMinimumDistances(city* cityArray, int* dist, int cityNum)
{
  int distance = 0, i = 0,j = 0;
  int min1, min2;
  for(i = 0; i < cityNum; i++)
    {
      min2 = cityArray[i].distance[0];
      min1 = cityArray[i].distance[cityNum-2];
      j = cityNum-3;
      while(j)
        {
          if (min1 > cityArray[i].distance[j])
            {
              if(min2>min1)
                min2 = min1;
              min1 = cityArray[i].distance[j];
            }
          else
            if (min2 > cityArray[i].distance[j])
                min2 = cityArray[i].distance[j];
          j--;
        }
      
      if(min1<min2)
        dist[i] = min2; // Guardo en el vector el segundo mas chico
      else
        dist[i] = min1;
      distance += (min1+min2)/2; //Para la distancia uso el promedio de los dos minimos
    }
  return (distance);
}

/*--------------------------------------------------------------------------------
 * Function:    initializeCity
 *
 * @brief       Reserva lugar en memoria del vector de ciudades y guarda su id.
 * 
 * @param[in]	city* cityArray	- Array donde se va a guardar info de todas las
 *                                ciudades.
 * @param[in]	int cityNum     - Cantidad de ciudades.
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void initializeCity(city* cityArray, int cityNum)
{
  for(int i = 0; i < cityNum; i++)
  {
    cityArray[i].nextCity = malloc((cityNum - 1 )*sizeof(int));
    cityArray[i].distance = malloc((cityNum - 1 )*sizeof(int));
    cityArray[i].id = i;
  }
  return;
}


/*--------------------------------------------------------------------------------
 * Function:    populateCity
 *
 * @brief       Completa el array de ciudades con la informacion pasada en data.
 * 
 * @param[in]	city* cityArray	- Array a completar con la info de todas las ciudades.
 * @param[in]	int cityNum     - Cantidad de ciudades.
 * @param[in]	char* data      - Puntero a inicio de informacion a guardar.
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void populateCity(city* cityArray, int cityNum, char* data)
{

  int distances;
  char* delimiter;
  printf("Importando distancias\n");
  printf("Cargando Array\n");
  for(int i = 0; i < cityNum - 1; i++)
  {
    for(int j = i + 1; j < cityNum; j++)
    {
      delimiter = strchr(data,';');
      *delimiter = '\0';
      distances = atoi(data);
      data = delimiter + 1;

      cityArray[i].distance[j-1] = distances;
      cityArray[i].nextCity[j-1] = j;

      cityArray[j].distance[i] = distances;
      cityArray[j].nextCity[i] = i;
    }
  }

  printf("Imprimiendo Array\n");
  for(int i = 0; i < cityNum; i++)
  {
    printf("\nCiudad %d:\n", cityArray[i].id);
    for(int j = 0; j < cityNum-1; j++)
    {
      printf("\t Distancia a Ciudad %d: %d\n", cityArray[i].nextCity[j], cityArray[i].distance[j]);
    }
  }

  return;

}

/*--------------------------------------------------------------------------------
 * Function:    TSP
 *
 * @brief       Se encarga de aplicar el algoritmo A* para resolver TSP
 * 
 * @param[in]	city* cityArray	- Array que contiene la info de todas las ciudades.
 * @param[in]	int cityNum     - Cantidad de ciudades.
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void TSP(city* cityArray, int cityNum)
{
  int startNode = 3, depth=0, cityFlag=0, i=0, NA=0, Node=0, currentCity=0;
  listNode* currentNode;
  listNode* openList;
  listNode* closedList;
  listNode* fatherNode;
  int path[cityNum]; //reservo un vector para guardar el camino recorrido
  //Generar vector de distancias minimas
  int minimumDistancesArray[cityNum];
  int minDistance = findMinimumDistances(cityArray, minimumDistancesArray, cityNum);
#ifdef DEBUG
  printf("Distancia minima = %d\n",minDistance);
  printf("START NODE = %d\n",cityArray[startNode].id);
#endif

  //Empiezo con el primer nodo
  //Configuro el primer nodo Lista abierta
  openList = malloc(sizeof (listNode));
  openList->idCurrentCity = startNode;
  openList->cost = 0;
 
#ifdef HEURISTICS_ON
  openList->heuristic = minDistance;
#else
  openList->heuristic = 0;
#endif
  
  openList->previousListItem = NULL;
  openList->nextListItem = NULL;
  openList->father = NULL;
  //Lista cerrada
  closedList  = NULL; //"lista cerrada vacia"
  fatherNode = openList;

  //Salgo cuando lista esta vacia con error o encuentro GOAL
  while(openList)
  {
    NA++;  //Contador de NODOS ABIERTOS
    fatherNode = openList; //father Node primer elemento de openlist
    currentNode = fatherNode;//currentNode para recorrer el camino de parents
        
    ////////BUSCAMOS CAMINO RECORRIDO SIGUIENDO LOS NODOS FATHER
    ////////////////////
    depth = 0; //reseteo contador de profundidad (CIUDADES VISITADAS)
    path[depth] = currentNode->idCurrentCity; //Primer elemento de camino es ciudad actual
    depth++;
    while(currentNode)
      {
        if (currentNode->father)
          {
            path[depth] = currentNode->father->idCurrentCity; //Guardo la ciudad visitada
            depth++;
          }
        currentNode = currentNode->father;//Paso un nivel mas arriba
      }
    ////////////////////
    
    if(openList->idCurrentCity == startNode && depth > 1) // Encontre GOAL!!!!
      {
#ifdef DEBUG
        printf("\n\n************************* GOAL  ******************************************\n\n");
        printf("------------------------------------------------------\n\n"); 
        printf("---------Open List Desordenada nivel %d----------------\n",NA);
        printList(openList);
        printf("------------------------------------------------------\n\n");
        printf("---------Closed  List Desordenada nivel %d----------------\n",NA);
        printList(closedList);
#endif
        printf("\nPath: ");
        while(depth)
          {
            printf("%d;",path[depth-1]);
            depth--;
          }
        printf("\nTotal COST = %d\n",openList->cost);
        printf("Nodos Abiertos: %d\n",NA);
        //Liberar memoria
        freeMemory(openList);
        freeMemory(closedList);
        return;
      }
    //////////////////// SI NO ES NODO GOAL ABRIMOS, INCLUIMOS NUEVOS NODOS EN ORDEN ////////////////////////////////////////
    
    if(depth == cityNum)//Si estoy en el ultimo nodo agrego solo el nodo GOAL
      {
        currentNode = malloc(sizeof(listNode));
        Node = startNode;
        if(fatherNode->idCurrentCity < Node)
          Node -= 1;
        addNode(currentNode,cityArray,Node,fatherNode, minimumDistancesArray);
        
      }
    else //Si no estoy en el ultimo nodo agrego todas las ciudades no visitadas.
      {
        for(int j = 0; j < cityNum -1; j++)
          {
            currentCity = cityArray[fatherNode->idCurrentCity].nextCity[j];
            for(int k = 0; k < depth; k++)
              {
                if (currentCity == path[k])
                  {
                    cityFlag = 1;
                    break;
                  }
              }
            if (!cityFlag) //Si no esta en el camino recorrido agrego el nodo
              {
                currentNode = malloc(sizeof(listNode));
                addNode(currentNode,cityArray,j,fatherNode, minimumDistancesArray);
                
              }
            cityFlag = 0;
          }
      }
    ////////////////////////////////////////////////////////////////////////////////
    
    ////// SACAMOS NODO ABIERTO DE LISTA ABIERTA Y LO PASAMOS A FINAL DE LISTA CERRADA //////
    openList = fatherNode->nextListItem; //Cambio primer item de lista abierta
    openList->previousListItem = NULL; 
    currentNode = closedList;
    if(closedList)
      {
        while(currentNode->nextListItem)
          {
            currentNode = currentNode->nextListItem;
          }
        currentNode->nextListItem = fatherNode;
        fatherNode->previousListItem = currentNode;
      }  
    else //Si no hay ningun nodo en Lista CERRADA
      {
        closedList = fatherNode;
      }
    fatherNode->nextListItem = NULL; // Apunto en ultimo nodo agregado de cerrada a null
    ////////////////////////////////////////////////////////////////////////////////

    //printf("------------------------------------------------------\n\n");
    //printf("---------Open List Desordenada nivel %d----------------\n",i+1);
    //printList(openList);
    //printf("------------------------------------------------------\n\n");
    //printf("-----------Open List Ordenada nivel %d-----------------\n",i+1);
    //    reordenarOpenList(openList);
    //printList(openList);
    //printf("------------------------------------------------------\n\n");
    //printf("-----------Open List Ordenada y Tachada nivel %d-------\n",i+1);
    //    tacharRepetidos(openList);
    //printList(openList);
    //printf("------------------------------------------------------\n\n");
    //Termine de armar la lista de este nivel
    //Cierro el nodo que se expandio
    //printf("-------------Closed List nivel %d----------------------\n",i+1);
    //printList(closedList);
    //printf("------------------------------------------------------\n\n");
    //i++;
  }

  //SI SALGO DEL WHILE POR ACA NO ENCONTRE EL GOAL!!!!!!
  printf("\n\n****************************************************************************\n\n");
  printf("ERROR!! NO SE ENCONTRO SOLUCION.\n");

}


/*--------------------------------------------------------------------------------
 * Function:    printList
 *
 * @brief       Imprime en pantalla todos los nodos de la lista con su info.
 * 
 * @param[in]	listNode* a	- Direccion de primer nodo de la lista a imprimir.
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void printList(listNode* a)
{
  listNode* currentNode = a;
  while (NULL != currentNode)
  {
    int myFather = 0;
    if (currentNode->father != NULL)
      {
        myFather = currentNode->father->idCurrentCity;
      }
    printf("id=%d, cost=%d, heur=%d, father=%d\n",currentNode->idCurrentCity, currentNode->cost, currentNode->heuristic,myFather);
    currentNode= currentNode->nextListItem;
  }
}


/*--------------------------------------------------------------------------------
 * Function:    addNode
 *
 * @brief       Agrega un nodo a la lista en orden dependiendo del costo total.
 * 
 * @param[in]   listNode* currentNode - Direccion de nodo actual a agregar.
 * @param[in]	city* cityArray	- Array que contiene la info de todas las ciudades.
 * @param[in]   int  j          - Indice de ciudad actual en array para el nodo padre.
 * @param[in]	listNode* fatherNode  - Direccion de nodo padre.
 * @param[in]   int* dist       - Direccion de vector de distancias minimas.
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void addNode(listNode* currentNode,city* cityArray, int j, listNode* fatherNode, int *dist)
{
  listNode *pivotNode = fatherNode;
  listNode *prevNode = NULL;
  int costToMe = cityArray[fatherNode->idCurrentCity].distance[j];
  currentNode->   idCurrentCity     = cityArray[fatherNode->idCurrentCity].nextCity[j];
  currentNode->   cost              = fatherNode->cost + costToMe;
#ifdef HEURISTICS_ON
  // h[n] = h[n-1] - dist(min2)[currentCity] + |dist(n-1 a n) - dist(min2)[currentCity]|
  int h0 = fatherNode->heuristic - dist[currentNode->idCurrentCity];
  int h1 = costToMe - dist[currentNode->idCurrentCity];
  if (h1 < 0)
    h1 = -h1;
  currentNode->heuristic = h0+h1;
#else
  currentNode->   heuristic         = 0;
#endif
  // Si esta bien calculada h esto no deberia que chequearlo.
  if (currentNode->heuristic < 0) //La heuristica tiene que ser siempre >= 0
    currentNode->heuristic = 0;
  currentNode->   father            = fatherNode;
  int currentCost = currentNode->cost + currentNode->heuristic;
  while(pivotNode->nextListItem)//Recorro la lista hasta encontrar el lugar donde insertar el nodo
    {
      if(currentCost < (pivotNode->cost+pivotNode->heuristic)) //Tengo que insertar el nodo antes
        {
          currentNode->   previousListItem  = pivotNode->previousListItem;
          prevNode                          = pivotNode->previousListItem;
          if(prevNode)
            prevNode->    nextListItem      = currentNode;
          currentNode->   nextListItem      = pivotNode;
          pivotNode->     previousListItem  = currentNode;
          break;
        }
        pivotNode = pivotNode->nextListItem;
    }
      if(!pivotNode->nextListItem) //Llegue al final de la lista
        {
          currentNode->   previousListItem  = pivotNode;
          currentNode->   nextListItem      = NULL;
          pivotNode->     nextListItem      = currentNode;
        }
}


/*--------------------------------------------------------------------------------
 * Function:    freeMemory
 *
 * @brief       Libera la memoria de todos los nodos de la lista a partir del nodo
 *              indicado.
 * 
 * @param[in]	listNode* a	- Direccion de primer nodo a partir del cual
 *                                liberar memoria.
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void freeMemory(listNode* a)
{
  while(a->nextListItem)
    {
      a = a->nextListItem;
      if (a->previousListItem) //Necesario?
        {
          free(a->previousListItem);
        }
    }
  free(a);
}
