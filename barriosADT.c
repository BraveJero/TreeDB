#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "barriosADT.h"

typedef struct tBarrio{
  char * nombre;
  size_t cantArb; // Cantidad de arboles en el barrio
  size_t hab; // Cantidad de habitantes del barrio
  struct tBarrio * tail;
}tBarrio;

// Nuestro CDT es un vector de tBarrio
typedef struct barriosCDT{
  tBarrio * first; // Puntero al primero barrio
}barriosCDT;
