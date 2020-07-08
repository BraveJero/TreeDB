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
** los archivos arbolesBUE.csv y arbolesVAN.csv 
** Retorna 1 si se pudo agregar, y -1 si la memoria no alcanzo.
*/
int addArbol(arbolesADT bosque, char * arbol, size_t diam);

// Ordena los arboles de mayor a menor por promedio de diametro
void ordenDiam(arbolesADT bosque);

// Setea el current en el primer arbol
void toBegin(arbolesADT bosque);

// Indica si hay un siguiente arbol o no, retorna 1 si hay, 0 si no.
int hasNext(arbolesADT bosque);

/* Devuelve los datos del arbol actual. 
** Retorna 1 si se pudieron devolver los datos.
** 0 si no hay mas datos.
** -1 si la memoria no alcanzo. */
int next(arbolesADT bosque, char ** arbol, size_t * cantArb, double * diamAc);

#endif
