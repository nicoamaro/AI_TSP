#include "TSP.h"

int main(int argc, char* argv[])
{
  FILE *importFile;
  char importText[1024];
  int cityNum, len;
  char* delimiter;
  listNode* openList;
  listNode* closedList;
  

  if(argc != 2)
  {
    printf("Debe pasar el archivo como parámetro\n");
    return 1;
  }
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
  openList = malloc(sizeof (listNode));
  TSP(cityArray, cityNum, openList, closedList);
  return 0;
}

int findMinimumDistances(city* cityArray, int* dist, int cityNum)
{
  int distance = 0, previous = 0, i = 0,j = 0;
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


void TSP(city* cityArray, int cityNum, listNode* openList, listNode* closedList)
{
  int startNode = 3, depth=0, cityFlag=0, i=0, NA=0, Node=0, currentCity=0;
  listNode* currentNode;
  listNode* fatherNode = openList;
  int path[cityNum]; //reservo un vector para guardar el camino recorrido
  //Generar vector de distancias minimas
  int minimumDistancesArray[cityNum];
  int minDistance = findMinimumDistances(cityArray, minimumDistancesArray, cityNum);
#ifdef DEBUG
  printf("Distancia minima = %d\n",minDistance);
  // GOAL = (openList->idCurrentCity == startNode && depth == cityNum);
  //Empiezo con el primer nodo
  //Configuro el primer nodo Lista abierta
  printf("START NODE = %d\n",cityArray[startNode].id);
#endif
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

  //Salgo cuando lista esta vacia con error o encuentro GOAL
  while(openList)//for(int i=0;i<20;i++)//while(openList)
  {
    NA++;
    fatherNode = openList; //father Node primer elemento de openlist
    currentNode = fatherNode;//currentNode para recorrer el camino de parents
        
    ////////BUSCAMOS CAMINO RECORRIDO SIGUIENDO LOS NODOS FATHER
    ////////////////////
    depth = 0; //reseteo contador de profundidad
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
        printf("\n\n************************* GOAL  ******************************************\n\n");
#ifdef DEBUG
        printf("------------------------------------------------------\n\n"); 
        printf("---------Open List Desordenada nivel %d----------------\n",NA);
        printList(openList);
        printf("------------------------------------------------------\n\n");
        printf("---------Closed  List Desordenada nivel %d----------------\n",NA);
        printList(closedList);
#endif
        printf("Total COST = %d\n",openList->cost);
        printf("Path: ");
        while(depth)
          {
            printf("%d;",path[depth-1]);
            depth--;
          }
        printf("\nNodos Abiertos: %d\n\n",NA);
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
        agregarItem(currentNode,cityArray,Node,fatherNode, minimumDistancesArray);
        
      }
    else
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
                agregarItem(currentNode,cityArray,j,fatherNode, minimumDistancesArray);
                
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

int F(listNode* current, int costToMe, int costToMyFather)
{
  int G = costToMe + costToMyFather;
  return  G;// + H(current) ;
}

int H(int* dist, int minDistance, int depth, int* path)//ES CUALQUIERA ESTO, NO SE USA
{
  #ifdef HEURISTICS_ON
  int h = minDistance;
  for(int i = 0; i < depth; i++)
    {
      h -= dist[path[i]];
    }
  return (h);
#endif /* CON HEURISTICA */
  return 0;
  
}

void reordenarOpenList(listNode* openList)
{
  listNode *moving;
  listNode *current;

  current = openList;

  while(NULL!=current)
  {
    moving = current->nextListItem;
    while (NULL!= moving)
    {
      if(current->cost+current->heuristic  > moving->cost+moving->heuristic)
      {

        switchItems(current, moving);
      }
      moving = moving->nextListItem;
    }
    current = current -> nextListItem;
    if(NULL != current)
    {
      moving = current->nextListItem;
    }
  }
}

void switchItems(listNode* a, listNode* b)
{
  listNode* aux= malloc (sizeof(listNode));

  aux->idCurrentCity= a->idCurrentCity;
  aux->cost= a->cost;
  aux->heuristic = a->heuristic;
  aux->father = a->father;

  a->idCurrentCity= b->idCurrentCity;
  a->cost= b->cost;
  a->heuristic = b->heuristic;
  a->father = b->father;

  b->idCurrentCity= aux->idCurrentCity;
  b->cost= aux->cost;
  b->heuristic = aux->heuristic;
  b->father = aux->father;
  /*

  aux->previousListItem = a->previousListItem;
  aux -> nextListItem = a->nextListItem;

  a->nextListItem = b-> nextListItem;
  a->previousListItem = b->previousListItem;

  b->nextListItem = aux -> nextListItem;
  b->previousListItem = aux -> previousListItem;

  (a->nextListItem)->previousListItem = a;
  (b->nextListItem)->previousListItem = b;

  (a->previousListItem)->nextListItem = a;
  (b->previousListItem)->nextListItem = b;
  //aux=a;
  //a=b;
  //b=aux;
*/
  free(aux);
}

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


void agregarItem(listNode* currentNode,city* cityArray, int j, listNode* fatherNode, int *dist)
{
  listNode *pivotNode = fatherNode;
  listNode *prevNode = NULL;
  int costToMe = cityArray[fatherNode->idCurrentCity].distance[j];
  currentNode->   idCurrentCity     = cityArray[fatherNode->idCurrentCity].nextCity[j];
  currentNode->   cost              = fatherNode->cost + costToMe;
#ifdef HEURISTICS_ON
  if(costToMe >= dist[currentNode->idCurrentCity]) //Si el costo es mayor o igual al segundo min
    currentNode->   heuristic         = fatherNode->heuristic - dist[currentNode->idCurrentCity];//Le restamos la distancia minima del nodo a la heuristica del nodo padre
  else
    currentNode->   heuristic         = fatherNode->heuristic - costToMe; //Si no le resto el costo para que h sea consistente.
#else
  currentNode->   heuristic         = 0;
#endif
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



void tacharRepetidos(listNode* openList)
{
  listNode *moving;
  listNode *current;

  current = openList;


  while(NULL!=current)
  {
    moving = current->nextListItem;
    while (NULL!= moving)
    {
      if(current->idCurrentCity == moving->idCurrentCity)
      {
        borrarItem(moving);
      }
      moving = moving->nextListItem;
    }
    current = current -> nextListItem;
  }
}

void borrarItem(listNode* a)
{
  a->previousListItem->nextListItem = a->nextListItem;
  if(NULL!=a->nextListItem)
  {
    a->nextListItem->previousListItem = a->previousListItem;
  }
  free(a);
}

void freeMemory(listNode* a)
{
  while(a->nextListItem)
    {
      a = a->nextListItem;
      if (a->previousListItem) //Necesario?
        {
          // printf("Liberando\n");
          free(a->previousListItem);
        }
    }
  //printf("Liberando ultimo\n");
    free(a);
}
