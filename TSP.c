#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    printf("Debe pasar el archivo como parámetro\n");
    return 1;
  }

  return 0;
}
