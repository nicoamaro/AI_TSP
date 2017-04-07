#include "TSP.h"

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
  listNode* currentNode;
  listNode* fatherNode = openList;
  listNode* previousNode = openList;

  //Empiezo con el primer nodo
  //Configuro el primer nodo
  openList->idCurrentCity=cityArray[startNode].id;
  openList->totalCost = 0;
  openList->previousListItem = NULL;

  for(int i=0;i<2;i++)//for(int i=0;i<cityNum-1;i++)
  {
    printf("\n\n************************* Nivel %d ******************************************\n\n",i+1);
    fatherNode = openList;
    closedList -> nextListItem = fatherNode;

    for(int j = 0; j < cityNum -1; j++)
    {
      currentNode = createItem(cityArray,cityNum,j,fatherNode);
      addItem(currentNode,previousNode);
      previousNode = currentNode;

    }
    openList = fatherNode->nextListItem;
    printf("------------------------------------------------------\n\n");
    printf("---------Open List Desordenada nivel %d----------------\n",i+1);
    printList(openList);
    printf("------------------------------------------------------\n\n");
    printf("-----------Open List Ordenada nivel %d-----------------\n",i+1);
    sortList(openList);
    printList(openList);
    printf("------------------------------------------------------\n\n");
    printf("-----------Open List Ordenada y Tachada nivel %d-------\n",i+1);
    crop(openList);
    printList(openList);
    printf("------------------------------------------------------\n\n");
    //Termine de armar la lista de este nivel
    //Cierro el nodo que se expandio
    closedList->nextListItem->nextListItem=NULL;
    printf("-------------Closed List nivel %d----------------------\n",i+1);
    printList(closedList);
    printf("------------------------------------------------------\n\n");


  }

  printf("\n\n****************************************************************************\n\n");

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

void sortList(listNode* list)
{
  listNode *moving;
  listNode *current;

  current = list;

  while(NULL!=current)
  {
    moving = current->nextListItem;
    while (NULL!= moving)
    {
      if(current->totalCost > moving->totalCost)
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
  aux->totalCost= a->totalCost;
  aux->father = a->father;

  a->idCurrentCity= b->idCurrentCity;
  a->totalCost= b->totalCost;
  a->father = b->father;

  b->idCurrentCity= aux->idCurrentCity;
  b->totalCost= aux->totalCost;
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
    int father = 0;
    if(currentNode->father != NULL)
    {
      father = currentNode->father->idCurrentCity;
    }
    printf("id=%d, cost=%d, father=%d\n",currentNode->idCurrentCity, currentNode->totalCost, father);
    currentNode= currentNode->nextListItem;
  }
}


listNode* createItem(city* cityArray,int cityNum, int j, listNode* fatherNode)//, listNode* previousNode )
{
  listNode* currentNode = malloc(sizeof(currentNode));
  currentNode->   idCurrentCity     = cityArray[fatherNode->idCurrentCity].nextCity[j];
  currentNode->   totalCost         = F(currentNode,cityArray[fatherNode->idCurrentCity].distance[j], fatherNode->totalCost);
  currentNode->   father            = fatherNode;

  return currentNode;
}

void addItem(listNode* item, listNode* listEnd)
{
  item->   previousListItem  = listEnd;
  item->   nextListItem      = NULL;
  listEnd->  nextListItem      = item;
}



void crop(listNode* openList)
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
        deleteItem(moving);
      }
      moving = moving->nextListItem;
    }
    current = current -> nextListItem;
  }
}

void deleteItem(listNode* a)
{
  listNode* aux = a;
  a->previousListItem->nextListItem = a->nextListItem;
  if(NULL!=a->nextListItem)
  {
    a->nextListItem->previousListItem = a->previousListItem;
  }
  free(aux);
}
