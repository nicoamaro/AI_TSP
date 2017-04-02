#include "TSP.h"

int main(int argc, char* argv[])
{
  FILE *importFile;
  char importText[1024];
  int cityNum, len;
  char* delimiter;
  openListNode openList;
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
  int closedList[cityNum];
  initializeCity(cityArray, cityNum);
  fgets(importText, 1024, importFile);
  populateCity(cityArray, cityNum, importText);
  TSP(cityArray, cityNum, &openList, closedList);
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


void TSP(city* cityArray, int cityNum, openListNode* openList, int* closedList)
{
  int startNode = 0, currentNodeFatherID = 0;
  openListNode* currentNode, *fatherNode, *previousNode;

  openList->idCurrentCity = cityArray[startNode].id;
  openList->totalCost = 0;
  openList->father = NULL;
  openList-> previousListItem = NULL;



  fatherNode = openList;
  previousNode = openList;

  for(int i = 0; i < cityNum - 1; i++)
  {
    currentNode                       = malloc(sizeof(openListNode));
    currentNode->   idCurrentCity     = cityArray[currentNodeFatherID].nextCity[i];
    currentNode->   totalCost         = F(currentNode,cityArray[currentNodeFatherID].distance[i]);//cityArray[currentNodeFatherID].distance[i]+ fatherNode->totalcost + H() ;

    currentNode->   father            = fatherNode;
    currentNode->   previousListItem  = previousNode;
    previousNode->  nextListItem      = currentNode;
    previousNode                      = currentNode;



  }
  
}

int F(openListNode* current, int costToMe)
{
  int G = costToMe + current->father->totalCost
  return  G + H(current) ;
}

int H(openListNode* current)
{
  return 0;
}
