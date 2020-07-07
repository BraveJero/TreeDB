#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "barriosADT.h"

typedef struct tBarrio{
  char * nombre;
  size_t cantArb; // Cantidad de arboles en el barrio
  size_t hab; // Cantidad de habitantes del barrio
}tBarrio;

// Nuestro CDT es un vector de tBarrio
typedef struct barriosCDT{
  tBarrio * barrios;
  size_t current;
  size_t max; // Cantidad de barrios almacenados
}barriosCDT;

barriosADT newBarrio(){
  return calloc(1, sizeof(barriosCDT));
}

void freeBarrio(barriosADT ciudad){
  for(size_t i = 0; i < ciudad->max; i++)
    free(ciudad->barrios[i].nombre);
  free(ciudad->barrios);
  free(ciudad);
}

void addBarrio(barriosADT ciudad, const char * barrio, size_t hab){
  size_t pos = ciudad->max++;
  ciudad->barrios = realloc(ciudad->barrios, (ciudad->max) * sizeof(tBarrio)); //Chequear que no retorne NULL
  ciudad->barrios[pos].nombre = malloc(sizeof(char) * (strlen(barrio) + 1));
  ciudad->barrios[pos].cantArb = 0;
  ciudad->barrios[pos].hab = hab;
}

void addArbol(barriosADT ciudad, const char * barrio);

void ordenCant(barriosADT ciudad);

void ordenDens(barriosADT ciudad);

void toBegin(barriosADT ciudad);

int hasNext(barriosADT ciudad);

void next(barriosADT ciudad, char ** nombre, size_t * cantArb, size_t * hab);
