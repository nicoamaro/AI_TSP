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
  int arrows = cityNum*(cityNum - 1)/2;
  int distances[arrows];
  char* delimiter;
  printf("Importando distancias\n");
  for(int i = 0; i < arrows; i++)
  {
    delimiter = strchr(data,';');
    *delimiter = '\0';
    distances[i] = atoi(data);
    data = delimiter + 1;
  }

  printf("Imprimiendo Array\n");
  for(int i = 0; i < cityNum; i++)
  {
    printf("\nCiudad %d:\n", cityArray[i].id);
    for(int j = 0; j < cityNum - 1; j++)
    {
  //    printf("\t Distancia a Ciudad %d: %d\n", cityArray[i].nextCity[j], cityArray[i].distance[j]);
    }
  }

  printf("Cargando Array\n");
  for(int i = 0; i < cityNum - 1; i++)
  {
    printf("%d\n",i);
    for(int j = i + 1; j < cityNum; j++)
    {
      printf("%d\n",j);
      cityArray[i].distance[j-i-1] = distances[(i*cityNum)+(j - 1)];
      cityArray[i].nextCity[j-i-1] = j;

      cityArray[j].distance[i] = distances[((i*cityNum))+(j - 1)];
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
