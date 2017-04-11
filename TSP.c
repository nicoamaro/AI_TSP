#include "TSP.h"
#include "listNodeColaDoble.h"

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


  TSP(cityArray, cityNum, openList, closedList);
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
    openList = createItem();
    putItemInfo(openList, cityArray[startNode].id, 0);
    listNode* currentNode = openList;
    listNode* fatherNode;
    listNode* previousNode = openList;
    int i=0;
    printf("UNO!!!!!\n" );
    while(!checkIfLastNode(currentNode, cityNum) )   //for(int i=0;i<3;i++)
    {
        printf("\n\n************************* Nivel %d ******************************************\n\n",i+1);
        fatherNode = openList;
        for(int j = 0; j < cityNum -1; j++)
        {
            currentNode = createItem();
            putItemAfter(currentNode,previousNode);
            putItemAsChildOf(fatherNode,currentNode);

            putItemInfo(currentNode, cityArray[fatherNode->idCurrentCity].nextCity[j], F(currentNode,cityArray[fatherNode->idCurrentCity].distance[j]) );
            //FIXME: Estoy pasando mal el ID number de city
            previousNode = currentNode;

        }
        openList = fatherNode->nextListItem;
        popItem(fatherNode);
        if (i==0){
            closedList = fatherNode;
            cleanItem(fatherNode);
        }else{
            putItemAfter(fatherNode,searchLast(closedList));
        }

        printf("------------------------------------------------------\n\n");
        printf("---------Open List Desordenada nivel %d----------------\n",i+1);
        printList(openList);
        printf("------------------------------------------------------\n\n");

        printf("--Open List Ordenada y sin caminos repetidos nivel %d--\n",i+1);
        searchForRedundancy(openList,cityNum);
        printList(openList);
        printf("------------------------------------------------------\n\n");

        printf("-----------Open List Ordenada nivel %d-----------------\n",i+1);
        orderAZ(openList);
        openList = searchFirst(openList);
        printList(openList);
        printf("------------------------------------------------------\n\n");

        //printf("-----------Open List Ordenada y Tachada nivel %d-------\n",i+1);
        //tacharRepetidos(openList);
        //printList(openList);
        //printf("------------------------------------------------------\n\n");

        printf("-------------Closed List nivel %d----------------------\n",i+1);
        printList(closedList);
        printf("------------------------------------------------------\n\n");
        i++;

    }
    printf("\n\n****************************************************************************\n\n");
    printf("-------------Llegamos al final!----------------------\n");
    printf("Total Cost: %d\n", openList->totalCost);
    printFatherPath(openList);
    printf("\n****************************************************************************\n\n");

}

int F(listNode* current, int costToMe)
{
    int costToMyFather = current->father->totalCost;
    int G = costToMe + costToMyFather;
    return  G + H(current);
}

int H(listNode* current)
{
  return 0;
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
                popItem(moving);
                free(moving);
            }
            moving = moving->nextListItem;
        }
        current = current -> nextListItem;
    }
}

void searchForRedundancy(listNode* openList, int cityNum){
    listNode *current = openList;
    listNode *movingFather;

    while (NULL != current) {
        movingFather = current->father;
        while(NULL != movingFather){
            if (current->idCurrentCity == movingFather->idCurrentCity && !checkIfLastNode(current, cityNum) ){ //TODO:Agregar check si es el final del camino
                popItem(current);
                free(current);
                return;
            }
            movingFather = movingFather->father;
        }
        current = current->nextListItem;
    }
}

int checkIfLastNode(listNode* node,int cityNum){
    int hops = 1;
    if (NULL == node->father) {
        return 0;
    }

    listNode *movingFather = node->father;

    while(NULL != movingFather){
        if ( node->idCurrentCity == movingFather->idCurrentCity && hops == cityNum ){
            return 1;
        }
        hops++;
        movingFather = movingFather->father;
    }
    return 0;
}
