/*
 * TSP.c
 *
 *  Created on: April 1, 2017
 *  Authors: Amaro Nicolas, Hernando Sebastian, Wajs Ezequiel
 */


/*Includes */
#include "TSP.h"

int cityNum;

int main(int argc, char* argv[])
{
  FILE *importFile;
  char importText[1024];
  int len;
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
  initializeCity(cityArray);
  fgets(importText, 1024, importFile);
  populateCity(cityArray, importText);
  TSP(cityArray);
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
 *
 *
 *
 * @return 	int distance    - Distancia minima calculada (h[0])
 --------------------------------------------------------------------------------*/
int findMinimumDistances(city* cityArray, int* dist)
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
 *
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void initializeCity(city* cityArray)
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
void populateCity(city* cityArray, char* data)
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
 *
 *
 *
 * @return 	NONE
 --------------------------------------------------------------------------------*/
void TSP(city* cityArray)
{
  int startNode = 3, depth=0, cityFlag=0, i=0, NA=0, Node=0, currentCity=0;
  listNode* currentNode;
  listNode* openList;
  listNode* closedList = NULL;
  listNode* fatherNode;
  listNode* ghostList = NULL;
  depthNode* depthList[cityNum];

  for(int i = 0; i < cityNum; i++) // inicializo mis listas de profundidad
    depthList[i] = NULL;

  int path[cityNum+1]; //reservo un vector para guardar el camino recorrido
  int histogram[cityNum];
  //Generar vector de distancias minimas
  int minimumDistancesArray[cityNum];
  int minDistance = findMinimumDistances(cityArray, minimumDistancesArray);
#ifdef DEBUG
  printf("Distancia minima = %d\n",minDistance);
  printf("START NODE = %d\n",cityArray[startNode].id);
#endif

  //Empiezo con el primer nodo
  //Configuro el primer nodo Lista abierta
  openList = (listNode*)malloc(sizeof (listNode));
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
  openList->isFather = 0;
  //Lista cerrada
  //closedList  = NULL; //"lista cerrada vacia"
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
    
    for(int i = 0; i < cityNum; i++)
    {
      histogram[i] = 0;
    }
    while(currentNode)
      {
        if (currentNode->father)
          {
            path[depth] = currentNode->father->idCurrentCity; //Guardo la ciudad visitada
            depth++;
          }
        currentNode = currentNode->father;//Paso un nivel mas arriba
      }
      for(int i = 0; i < depth; i++) // ignoro
      {
        histogram[path[i]] = 1;
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
        /* for(int selectedDepth = 0; selectedDepth < cityNum-1; selectedDepth++) */
        /*   { */
        /*     printf("Listas de profundidad %d:\n", selectedDepth); */
        /*     depthNode* currDepthListItem = depthList[selectedDepth]; */
        /*     if(currDepthListItem != NULL) */
        /*       { */
        /*       while(currDepthListItem->nextDepthNode) */
        /*         { */
        /*           listNode* aux = currDepthListItem->node; */
        /*           printf("Listas de profundidad %d:\n", selectedDepth); */
        /*           while(aux != NULL) */
        /*             { */
        /*               printf("%d;", aux->idCurrentCity); */
        /*               aux = aux->father; */
        /*             } */
        /*           printf("\n"); */
        /*           currDepthListItem = currDepthListItem->nextDepthNode; */
        /*         } */
        /*       } */
        /*   } */
        for(int selectedDepth = 0; selectedDepth <cityNum-1; selectedDepth++)
          {
            depthNode* currDepthListItem = depthList[selectedDepth];
            if(currDepthListItem)
              {
                if(currDepthListItem->nextDepthNode)
                  while(currDepthListItem->nextDepthNode)
                    {
                      currDepthListItem = currDepthListItem->nextDepthNode;
                      free(currDepthListItem->previousDepthNode);
                    }
                free(currDepthListItem);
              }
          }
        //Liberar memoria
        freeMemory(openList);
        freeMemory(closedList);
        if(ghostList)
          {
            freeMemory(ghostList);
          }
        return;
      }
    //////////////////// SI NO ES NODO GOAL ABRIMOS, INCLUIMOS NUEVOS NODOS EN ORDEN ////////////////////////////////////////

    if(depth == cityNum)//Si estoy en el ultimo nodo agrego solo el nodo GOAL
      {
        Node = startNode;
        if(fatherNode->idCurrentCity < Node)
          Node -= 1;
        addNode(cityArray,Node,fatherNode, minimumDistancesArray, depth, histogram, depthList,& ghostList);

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
                addNode(cityArray,j,fatherNode, minimumDistancesArray, depth, histogram, depthList, &ghostList);
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
void addNode(city* cityArray, int j, listNode* fatherNode, int *dist, int depth, int* histogram, depthNode** depthList, listNode** ghostList)
{
  listNode *pivotNode = fatherNode;
  listNode *prevNode = NULL;
  listNode *auxNode;
  int histogram2[cityNum];
  int costToMe = cityArray[fatherNode->idCurrentCity].distance[j];
  int currentCity = cityArray[fatherNode->idCurrentCity].nextCity[j];
  int currentCost = fatherNode->cost + costToMe;
  depthNode* currDepthListItem = depthList[depth-1];
  
  while(currDepthListItem) // Mientras haya algun item en la lista para comparar entro
  {
      
    if(currDepthListItem->node->idCurrentCity == currentCity) //Busco coincidencia con ciudad actual
    {
      for(int i = 0; i < cityNum; i++) //Limpio el histograma
        {
          histogram2[i] = 0;
        }
      
      auxNode = currDepthListItem->node->father; //Empiezo a armar el camino partiendo del padre
      
      while(auxNode)
      {
        histogram2[auxNode->idCurrentCity] = 1;
        auxNode = auxNode->father;
      }

      int flagDif = 0; // Reseteo flag de coincidencia de caminos recorridos 

      for(int i = 0; i < cityNum; i++)
        {
          if(histogram[i] - histogram2[i] != 0)
            {
              flagDif++;  //Si hay diferencia en el camino recorrido incremento el flag y salgo
              break;
            }
        }
       
      if(!flagDif) //llegué a un path que termina en la misma ciudad y compuesto por las mismas ciudades
        {
          if(currentCost < currDepthListItem->node->cost) // Si encontré un mejor camino bajo estas condiciones, borro el anterior.
            {
              listNode* nodeToDelete = currDepthListItem->node;
              // Borro de la lista abierta.
              if(nodeToDelete->previousListItem) // si no estoy en el primer elemento
                {
                  nodeToDelete->previousListItem->nextListItem = nodeToDelete->nextListItem;
                }
              if(nodeToDelete->nextListItem)
                nodeToDelete->nextListItem->previousListItem = nodeToDelete->previousListItem;
              // Borro de las listas de nivel.
              if(currDepthListItem->previousDepthNode) // si no estoy en el primer elemento
                {
                  currDepthListItem->previousDepthNode->nextDepthNode = currDepthListItem->nextDepthNode;
                }else
                {
                  depthList[depth-1] = currDepthListItem->nextDepthNode;
                }
              if(currDepthListItem->nextDepthNode)
                currDepthListItem->nextDepthNode->previousDepthNode = currDepthListItem->previousDepthNode;
              free(currDepthListItem);
              if(!nodeToDelete->isFather)
                {
                  free(nodeToDelete);
                }
              else
                {
                  listNode* ghostNode = nodeToDelete;
                  if(*ghostList)
                    {
                      while(ghostNode->nextListItem)
                        {
                          ghostNode  = ghostNode->nextListItem;
                        }
                      ghostNode->nextListItem = nodeToDelete;
                      nodeToDelete->previousListItem = ghostNode;
                    }
                  else //Si no hay ningun nodo en Lista CERRADA
                    {
                      *ghostList = nodeToDelete;
                      nodeToDelete->previousListItem = NULL;
                    }
                  nodeToDelete->nextListItem = NULL; // Apunto en ultimo nodo agregado de cerrada a null
                }
              break;
            }else
            {
              return; // Si el costo actual es mayor a uno que tiene el mismo camino, ni lo agrego.
            }
        }
    }
    currDepthListItem = currDepthListItem->nextDepthNode;
  }

  listNode* currentNode =(listNode*) malloc(sizeof(listNode));
  currentNode->   idCurrentCity     = currentCity;
  currentNode->   cost              = currentCost;
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
  currentNode->   isFather          = 0;
  currentNode->   father            = fatherNode;
  fatherNode->    isFather          = 1;
  currentCost = currentNode->cost + currentNode->heuristic;
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
  // Agrego el nodo actual a la lista de profundidades para comparar a futuro
  if(depthList[depth-1] == NULL) // Primer camino con esta profundidades
    {
      //printf("Inaugurando lista de nivel %d\n", depth);
      depthNode * newDepthNode = (depthNode*)malloc(sizeof(depthNode));
      depthList[depth-1] = newDepthNode;
      newDepthNode->previousDepthNode = NULL;
      newDepthNode->nextDepthNode = NULL;
      newDepthNode->node = currentNode;
    }else // si ya habían nodos con esta produndidad, lo agrego al final.
    {
      currDepthListItem = depthList[depth-1];
      while(currDepthListItem->nextDepthNode)
        currDepthListItem = currDepthListItem->nextDepthNode;
      depthNode* newDepthNode = (depthNode*)malloc(sizeof(depthNode));
      newDepthNode->nextDepthNode = NULL;
      newDepthNode->previousDepthNode = currDepthListItem;
      newDepthNode->node = currentNode;
      currDepthListItem->nextDepthNode = newDepthNode;
    }
  return;
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
