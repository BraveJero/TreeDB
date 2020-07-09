#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "valoresADT.h"

#define BARRIO 0
#define CANT 1
#define ARBOL 2
#define EPSILON 0.01

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

void freeValores(valoresADT datos){
  for(size_t i = 0; i < datos->max; i++){
    free(datos->valores[i].versatil);
    free(datos->valores[i].nombre);
  }
  free(datos->valores);
  free(datos);
  return;
}

static int addDato(valoresADT datos, char * rotulo, void * flex, char type){
  errno=0;
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
  if (datos->valores == NULL || errno == ENOMEM){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  datos->valores[datos->max].nombre = malloc((strlen(rotulo) + 1) * sizeof(char));
  if (datos->valores[datos->max].nombre == NULL || errno == ENOMEM){
    datos->valores = realloc(datos->valores, sizeof(tDato) *(datos->max));
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  strcpy(datos->valores[datos->max].nombre, rotulo);
  if (type == BARRIO){
    datos->valores[datos->max].cantArb = 0;
    datos->valores[datos->max].versatil = malloc(sizeof(size_t));
    if (datos->valores[datos->max].versatil == NULL || errno == ENOMEM){
      free(datos->valores[datos->max].nombre);
      datos->valores = realloc(datos->valores, sizeof(tDato) * (datos->max));
      fprintf(stderr, "Espacio de memoria insuficiente.\n");
      return -1;
    }
    *(size_t*)(datos->valores[datos->max].versatil) = *(size_t*)flex;
  }else {
    datos->valores[datos->max].cantArb = 1;
    datos->valores[datos->max].versatil = malloc(sizeof(double));
    if (datos->valores[datos->max].versatil == NULL || errno == ENOMEM){
      free(datos->valores[datos->max].nombre);
      datos->valores = realloc(datos->valores, sizeof(tDato) * (datos->max));
      fprintf(stderr, "Espacio de memoria insuficiente.\n");
      return -1;
    }
    *(double*)(datos->valores[datos->max].versatil) = *(double*)flex;
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

static int comparaBarrio(tDato * dato1, tDato * dato2){
    int resp;
    if((resp= dato2->cantArb - dato1->cantArb) == 0)
        return strcmp(dato1->nombre, dato2->nombre);
    return resp;
}

void ordenBarrio(valoresADT datos){
    qsort(datos->valores, datos->max, sizeof(tDato), (int (*)(const void *, const void *))comparaBarrio);
    return;
}

static int comparaArbol(tDato * dato1, tDato * dato2){
    float resp;
    if((resp=((*(float*)(dato2->versatil)) / dato2->cantArb) - ((*(float*)(dato1->versatil)) / dato1->cantArb)) < EPSILON && resp > -EPSILON)
        return strcmp(dato1->nombre, dato2->nombre);
    return resp;
}

void ordenArbol(valoresADT datos){
    qsort(datos->valores, datos->max, sizeof(tDato), (int (*)(const void *, const void *))comparaArbol);
    return;
}

static int comparaCant(tDato * dato1, tDato * dato2){
    float resp;
    if((resp=(dato2->cantArb / (float)(*(size_t*)(dato2->versatil))) - (dato1->cantArb / (float)(*(size_t*)(dato1->versatil)))) < EPSILON && resp > -EPSILON)
        return strcmp(dato1->nombre, dato2->nombre);
    return resp;
}

void ordenCant(valoresADT datos){
    qsort(datos->valores, datos->max, sizeof(tDato), (int (*)(const void *, const void *))comparaCant);
    return;
}

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
  errno=0;
  *nombre = malloc(sizeof(char) * (strlen(datos->valores[datos->current].nombre) + 1));
  if (*nombre == NULL || errno == ENOMEM){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
  strcpy(*nombre, datos->valores[datos->current].nombre);
  *cantArb = datos->valores[datos->current].cantArb;
  if (type == ARBOL)
    *(double*)(flex) = *(double*)(datos->valores[datos->current].versatil);
  else if (type == CANT)
    *(size_t*)(flex) = *(size_t*)(datos->valores[datos->current].versatil);
  datos->current++;
  return 1;
}

int nextBarrio(valoresADT datos, char ** nombre, size_t * cantArb){
  return next(datos, nombre, cantArb, NULL, BARRIO);
}

int nextArbol(valoresADT datos, char ** nombre, size_t * cantArb, double * diamAc){
  return next(datos, nombre, cantArb, diamAc, ARBOL);
}

int nextCant(valoresADT datos, char ** nombre, size_t * cantArb, size_t * hab){
  return next(datos, nombre, cantArb, hab, CANT);
}
