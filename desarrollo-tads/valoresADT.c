#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "valoresADT.h"

#define BARRIO 0
#define CANT 1
#define ARBOL 2

typedef struct tDato{
  char * nombre; // Nombre del barrio o arbol
  void * versatil; // Diametro acumulado o habitantes
  size_t cantArb; // Cantidad de arboles en el barrio o de un cierto tipo
}tDato;

// Nuestro CDT es un vector de tDato
typedef struct valoresCDT{
  tDato * valores; // Datos guardados dependiendo del query
  size_t current; // Iterador actual
  size_t max; // Cantidad de valores almacenados
}valoresCDT;

valoresADT newValores(){
  return calloc(1, sizeof(valoresCDT));
}

void freevalores(valoresADT datos){
  for(size_t i = 0; i < datos->max; i++){
    free(datos->valores[i].versatil);
    free(datos->valores[i].nombre);
  }
  free(datos->valores);
  free(datos);
  return;
}

static int addDato(valoresADT datos, char * rotulo, void * flex, char type){
  for (size_t i = 0; i < datos->max; i++){
    if (!strcmp(datos->valores[i].nombre, rotulo)){
      if (type == BARRIO)
        return 0;
      if (type == ARBOL)
        *(double*)(datos->valores[i].versatil) += *(double*)flex;
      datos->valores[i].cantArb++;
      return 1;
    }
  }
  if (type == CANT)
    return 0;
  datos->valores = realloc(datos->valores, sizeof(tDato) * (datos->max + 1));
  if (datos->valores == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  datos->valores[datos->max].nombre = malloc((strlen(rotulo) + 1) * sizeof(char));
  if (datos->valores[valores->max].nombre == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  strcpy(datos->valores[valores->max].nombre, rotulo);
  if (type == BARRIO){
    datos->valores[valores->max].cantArb = 0;
    datos->valores[valores->max].versatil = malloc(sizeof(size_t));
    if (datos->valores[valores->max].versatil == NULL){
      fprintf(stderr, "Espacio de memoria insuficiente.\n");
      return -1;
    }
    *(size_t*)(datos->valores[valores->max].versatil) = *(size_t*)flex;
  }else {
    datos->valores[valores->max].cantArb = 1;
    datos->valores[valores->max].versatil = malloc(sizeof(double));
    if (datos->valores[valores->max].versatil == NULL){
      fprintf(stderr, "Espacio de memoria insuficiente.\n");
      return -1;
    }
    *(double*)(datos->valores[valores->max].versatil) = *(double*)flex;
  }
  datos->max++;
  return 1;
}

int addBarrio(valoresADT datos, char * nombre, size_t cant){
  return addDato(datos, nombre, &cant, BARRIO);
}

int addArbol(valoresADT datos, char * nombre, double diam){
  return addDato(datos, nombre, &diam, ARBOL);
}

int addCant(valoresADT datos, char * nombre){
  return addDato(datos, nombre, NULL, CANT);
}

void ordenBarrio(valoresADT datos); // TO-DO

void ordenArbol(valoresADT datos); // TO-DO

void ordenCant(valoresADT datos); // TO-DO

void toBegin(valoresADT datos){
  datos->current = 0;
  return;
}

int hasNext(valoresADT datos){
  return (datos->current < datos->max);
}

static int next(valoresADT datos, char ** nombre, size_t * cantArb, void * flex, char type){
  if (!hasNext(datos))
    return 0;

  *nombre = malloc(sizeof(char) * (strlen(datos->valores[valores->current].nombre) + 1));
  if (*nombre == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  strcpy(*nombre, datos->valores[valores->current].nombre);
  *cantArb = datos->valores[valores->current].cantArb;
  if (type == ARBOL)
    *(double*)(flex) = *(double*)(datos->valores[valores->current].versatil);
  else if (type == CANT)
    *(size_t*)(flex) = *(size_t*)(datos->valores[valores->current].versatil);
  return 1;
}

int nextBarrio(valoresADT datos, char ** nombre, size_t * cantArb){
  return next(datos, nombre, cantArb, NULL, BARRIO);
}

int nextArbol(valoresADT datos, char ** nombre, size_t * cantArb, void * flex){
  return next(datos, nombre, cantArb, flex, ARBOL);
}

int nextCant(valoresADT datos, char ** nombre, size_t * cantArb, void * flex){
  return next(datos, nombre, cantArb, flex, CANT);
}
