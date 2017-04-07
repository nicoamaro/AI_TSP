#include "TSP2.h"

int main(int argc, char* argv[])
{
  FILE *importFile;
  char importText[1024];
  int cityNum, len;
  char* delimiter;
  listNode openList;
  listNode closedList;
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
  TSP(cityArray, cityNum, &openList, &closedList);
  return 0;
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
  int startNode = 0;
  listNode* currentNode = openList;
  listNode* fatherNode = openList;
  listNode* previousNode = openList;

  //Empiezo con el primer nodo
  currentNode->idCurrentCity=cityArray[startNode].id;
  currentNode->totalCost = 0;
  currentNode->previousListItem = NULL;

  for(int j = 0; j < cityNum -1; j++)
  {
    currentNode                       = malloc(sizeof(listNode));
    currentNode->   idCurrentCity     = cityArray[fatherNode->idCurrentCity].nextCity[j];
    currentNode->   totalCost         = F(currentNode,cityArray[fatherNode->idCurrentCity].distance[j], fatherNode->totalCost);

    currentNode->   previousListItem  = previousNode;
    currentNode->   nextListItem      = NULL;
    previousNode->  nextListItem      = currentNode;


    previousNode = currentNode;
  }
  //Hay que cerrar el nodo que se expandio
  openList = fatherNode->nextListItem;
  closedList = fatherNode;
  closedList->previousListItem=NULL;
  closedList->nextListItem=NULL;



  //Termine de armar la lista de este nivel
  //Reordenar
  SortList(openList);
  //Tachar los repetidos
  printf("---------------------------------\n\n");
  printf("---------Open List---------------\n");


  currentNode = openList;
  while (NULL != currentNode)
  {
    printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
    currentNode= currentNode->nextListItem;
  }
  printf("----------------------------------\n\n");
  printf("---------Closed List--------------\n");
  currentNode = closedList;
  while (NULL != currentNode)
  {
    printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost,currentNode->father);
    currentNode= currentNode->nextListItem;
  }
  printf("----------------------------------\n\n");

}

int F(listNode* current, int costToMe, int costToMyFather)
{
  int G = costToMe + costToMyFather;
  return  G + H(current) ;
}

int H(listNode* current)
{
  return 0;
}

void SortList (listNode *firstNode)
{
  printf("id = %d",firstNode->idCurrentCity);
  if (firstNode != NULL)
    {
      printf("Entre");
      listNode *pivotNode = firstNode;
      listNode *currentNode = NULL;//pivotNode->nextListItem;
      listNode *tmpPivotPrevious = NULL;
      listNode *tmpPivotNext = NULL;
      listNode *tmpCurrentNext = NULL;
      int i =0;
      printf("Entre");
      while (NULL != pivotNode-> nextListItem)
        {
          currentNode = pivotNode->nextListItem;
          
          while (NULL != currentNode)
            {
              if(currentNode->totalCost < pivotNode->totalCost)
                {
                  printf("Ordenando %d", i);
                  i++;
                  tmpPivotPrevious = pivotNode->previousListItem;
                  tmpPivotNext = pivotNode->nextListItem;
                  tmpCurrentNext = currentNode->nextListItem;
                  if(currentNode->nextListItem != NULL)
                    tmpCurrentNext->previousListItem = pivotNode;
                  currentNode->nextListItem->previousListItem = pivotNode;
                  currentNode->previousListItem = pivotNode->previousListItem;  // Apuntar current->Previous = pivot->Previous
                  currentNode->nextListItem = pivotNode->nextListItem; // Apuntar current->Next = pivot
                  if(tmpPivotPrevious != NULL)
                    tmpPivotPrevious->nextListItem = currentNode;
                  pivotNode->previousListItem = currentNode;// Apuntar pivot->Previous = current
                  //pivotNode->nextListItem = tmpNext;// Apuntar pivot->Next = current->Next
                }
              currentNode = currentNode->nextListItem;
            }
          pivotNode = pivotNode->nextListItem;
        }
    }
}  
