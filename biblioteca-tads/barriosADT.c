#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "barriosADT.h"

typedef struct tBarrio{
  char * nombre; // Nombre del barrio
  size_t cantArb; // Cantidad de arboles en el barrio
  size_t hab; // Cantidad de habitantes del barrio
}tBarrio;

// Nuestro CDT es un vector de tBarrio
typedef struct barriosCDT{
  tBarrio * barrios;
  size_t current; // Iterador actual
  size_t max; // Cantidad de barrios almacenados
}barriosCDT;

barriosADT newBarrio(){
  barriosADT barrio = calloc(1, sizeof(barriosCDT));
  if (barrio == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    exit(1);
  }
  return barrio;
}

void freeBarrio(barriosADT ciudad){
  for(size_t i = 0; i < ciudad->max; i++)
    free(ciudad->barrios[i].nombre);
  free(ciudad->barrios);
  free(ciudad);
  return;
}

void addBarrio(barriosADT ciudad, const char * barrio, size_t hab){
  size_t pos = ciudad->max++;
  ciudad->barrios = realloc(ciudad->barrios, (ciudad->max) * sizeof(tBarrio));
  if (ciudad->barrios == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    exit(1);
  }
  ciudad->barrios[pos].nombre = malloc(sizeof(char) * (strlen(barrio) + 1));
  if (ciudad->barrios[pos].nombre == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    exit(1);
  }
  strcpy(ciudad->barrios[pos].nombre, barrio);
  ciudad->barrios[pos].cantArb = 0;
  ciudad->barrios[pos].hab = hab;
  return;
}

void addArbol(barriosADT ciudad, const char * barrio){
  for (size_t i = 0; i < ciudad->max; i++)
    if (!strcmp(ciudad->barrios[i].nombre, barrio))
      ciudad->barrios[i].cantArb++;
  return;
}

void ordenCant(barriosADT ciudad); // TO-DO

void ordenDens(barriosADT ciudad); // TO-DO

void toBegin(barriosADT ciudad){
  ciudad->current = 0;
  return;
}

int hasNext(barriosADT ciudad){
  return (ciudad->current < ciudad->max);
}

void next(barriosADT ciudad, char ** nombre, size_t * cantArb, size_t * hab){
  if (!hasNext(ciudad))
    return;
  *nombre = ciudad->barrios[ciudad->current].nombre;
  *cantArb = ciudad->barrios[ciudad->current].cantArb;
  if (hab != NULL)
    *hab = ciudad->barrios[ciudad->current].hab;
  ciudad->current++;
  return;
}
