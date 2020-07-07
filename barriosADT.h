/* Utilizaremos este ADT para almacenar la cantidad de personas
   y arboles neta que hay por barrio */

#ifndef BARRIOS_H
#define BARRIOS_H

typedef struct barriosCDT * barriosADT;

// Crea un CDT vacio, es decir sin ningun barrio cargado
barriosADT newBarrio(void);

// Libera los recursos reservados por el TAD
void freeBarrio(barriosADT ciudad);

/* Agrega un barrio con su cantidad de habitantes
** utilizaremos esta funcion para cargar la informacion de
** los archivos barriosBUE.csv y barriosVAN.csv */
void addBarrio(barriosADT ciudad, const char * barrio, size_t hab);

/* Agrega un arbol al barrio
** utilizaremos esta funcion para cargar la informacion de
** los archivos arbolesBUE.csv y arbolesVAN.csv */
void addArbol(barriosADT ciudad, const char * barrio);

// Ordena los barrios de mayor a menor por cantidad de arboles
void ordenCant(barriosADT ciudad);

// Ordena los barrios de mayor a menor por densidad de arboles
void ordenDens(barriosADT ciudad);

// Setea el current en el primer barrio
void toBegin(barriosADT ciudad);

// Indica si hay un siguiente barrio o no
int hasNext(barriosADT ciudad);

// Devuelve los datos del barrio actual
void next(barriosADT ciudad, char ** nombre, size_t * cantArb, size_t * hab);

#endif
