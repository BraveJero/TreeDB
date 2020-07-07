#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arbolesADT.h"

typedef struct tArbol{
	char * nombre;
	size_t cantArb; // Cantidad de arboles de un tipo
	double diamAc; // Suma de todos los diametros
	struct tArbol * tail;
}tArbol;

// Almacenamos los arboles en forma de lista
typedef struct arbolesCDT{
	tArbol * first; // Puntero al primer arbol
}arbolesCDT;
