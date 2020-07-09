/* Utilizaremos este ADT para almacenar la cantidad de personas
   y arboles neta que hay por barrio */

#ifndef VALORES_H
#define VALORES_H

typedef struct valoresCDT * valoresADT;

// Crea un CDT vacio, es decir sin ningun barrio cargado
valoresADT newValores(void);

// Libera los recursos reservados por el TAD
void freeBarrio(valoresADT ciudad);

int addBarrio(valoresADT datos, char * nombre, size_t cant);

int addArbol(valoresADT datos, char * nombre, double diam);

int addCant(valoresADT datos, char * nombre);

// Ordena los barrios de mayor a menor por cantidad de arboles
void ordenBarrio(valoresADT ciudad);


void ordenArbol(valoresADT datos); // TO-DO

// Ordena los barrios de mayor a menor por densidad de arboles
void ordenCant(valoresADT ciudad);


// Setea el current en el primer barrio
void toBegin(valoresADT ciudad);

// Indica si hay un siguiente barrio o no
int hasNext(valoresADT ciudad);

/* Devuelve los datos del barrio actual (nombre, cantidad de arboles, cantidad de habitantes).
** Si hab==NULL no devuelve la cantidad de habitantes. (Para query 1).
** Retorna 1 si se pudieron devolver los datos.
** -1 si la memoria no alcanzo.
** 0 si no hay mas datos. */

int nextBarrio(valoresADT datos, char ** nombre, size_t * cantArb);

int nextArbol(valoresADT datos, char ** nombre, size_t * cantArb, void * flex);

int nextCant(valoresADT datos, char ** nombre, size_t * cantArb, void * flex);


#endif
