/* Utilizaremos este ADT para almacenar las estadisticas
   de cada tipo de arbol */

#ifndef ARBOLES_H
#define ARBOLES_H

typedef arbolesCDT * arbolesADT;

// Crea un CDT vacio, es decir sin ningun arbol cargado
arbolesADT newArbol(void);

// Libera los recursos reservados por el TAD
void freeArbol(arbolesADT bosque);

/* Agrega un arbol con su diametro
** utilizaremos esta funcion para cargar la informacion de
** los archivos arbolesBUE.csv y arbolesVAN.csv */
void addArbol(arbolesADT bosque, char * arbol, size_t diam);

// Ordena los arboles de mayor a menor por promedio de diametro
void ordenDiam(arbolesADT bosque);

// Setea el current en el primer arbol
void toBegin(arbolesADT bosque);

// Indica si hay un siguiente arbol o no
int hasNext(arbolesADT bosque);

// Devuelve los datos del arbol actual
void next(arbolesADT bosque, char ** arbol, size_t * cantArb, double * diamAc);

#endif
