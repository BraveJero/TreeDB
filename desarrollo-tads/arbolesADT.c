#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arbolesADT.h"

typedef struct tArbol{
	char * nombre; // Nombre cientifico del arbol
	size_t cantArb; // Cantidad de arboles de un tipo
	double diamAc; // Suma de todos los diametros
}tArbol;

// Nuestro CDT es un vector de tArbol
typedef struct arbolesCDT{
	tArbol * arboles;
	size_t current; // Iterador actual
	size_t max; // Cantidad de arboles almacenados
}arbolesCDT;

arbolesADT newArbol(void){
	return calloc(1, sizeof(arbolesCDT));
}

void freeArbol(arbolesADT bosque){
	for (size_t i = 0; i < bosque->max; i++)
		free(bosque->arboles[i].nombre);
	free(bosque->arboles);
	free(bosque);
}

static int getIndex(tArbol * arboles, char * arbol, size_t dim){
	for (size_t i = 0; i < dim; i++)
		if (!strcmp(arboles[i].nombre, arbol))
			return i;
	return -1;
}

int addArbol(arbolesADT bosque, char * arbol, size_t diam){
	int index = getIndex(bosque->arboles, arbol, bosque->max);
	if (index != -1){
		bosque->arboles[index].cantArb++;
		bosque->arboles[index].diamAc += diam;
		return 1;
	}
	bosque->arboles = realloc(bosque->arboles, sizeof(tArbol) * (bosque->max + 1));
	if (bosque->arboles == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
	bosque->arboles[bosque->max].nombre = malloc(sizeof(strlen(arbol)));
	if (bosque->arboles[bosque->max].nombre == NULL){
    fprintf(stderr, "Espacio de memoria insuficiente.\n");
    return -1;
  }
	strcpy(bosque->arboles[bosque->max].nombre, arbol);
	bosque->arboles[bosque->max].diamAc = diam;
	bosque->max++;
	return 1;
}

void ordenDiam(arbolesADT bosque); // TO-DO

void toBegin(arbolesADT bosque){
	bosque->current = 0;
	return;
}

int hasNext(arbolesADT bosque){
	return (bosque->current < bosque->max);
}

int next(arbolesADT bosque, char ** arbol, size_t * cantArb, double * diamAc){
	if (!hasNext(bosque))
		return 0;
	*arbol=malloc(strlen(bosque->arboles[bosque->current].nombre)*(sizeof(char)));
	if  (*arbol == NULL){
    		fprintf(stderr, "Espacio de memoria insuficiente.\n");
		return -1;
	}
	strcpy(*arbol, bosque->arboles[bosque->current].nombre); //Chequear. 
	*cantArb = bosque->arboles[bosque->current].cantArb;
	*diamAc = bosque->arboles[bosque->current].diamAc;
	bosque->current++;
	return 1;
}
