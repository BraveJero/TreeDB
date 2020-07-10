/* Utilizaremos este ADT para almacenar la cantidad de personas
   y arboles neta que hay por barrio */

#ifndef VALORES_H
#define VALORES_H

typedef struct valoresCDT * valoresADT;

// Crea un CDT vacio.
valoresADT newValores(void);

// Libera los recursos reservados por el TAD
void freeValores(valoresADT datos);

/*Agrega un barrio a datos, con su nombre, y cantidad de hab.
** Retorna 1 se se agrego correctamente.
** 0 si se trato de agregar un barrio repetido.
** -1 si la memoria no alcanzo.
*/
int addBarrio(valoresADT datos, char * nombre, size_t cant);

/*Agrega un arbol a datos, con su nombre y diametro AP.
** Retorna 1 se se agrego correctamente.
** -1 si la memoria no alcanzo.
*/
int addArbol(valoresADT datos, char * nombre, double diam);

/*Agrega un arbol al barrio "nombre" dentro de datos.
** Retorna 1 se se agrego correctamente.
** 0 si el barrio no pertenecia a datos.
*/
int addCant(valoresADT datos, char * nombre);

//Ordena los datos dadas las instrucciones del query 1;
void ordenBarrio(valoresADT datos);

//Ordena los datos dadas las instrucciones del query 2;
void ordenCant(valoresADT datos);

//Ordena los datos dadas las instrucciones del query 3;
void ordenArbol(valoresADT datos);

// Setea el current en el primer barrio
void toBegin(valoresADT datos);

// Indica si hay un siguiente barrio o no
int hasNext(valoresADT datos);

/* Devuelve los datos del barrio actual (nombre, cantidad de arboles, cantidad de habitantes).
** Retorna 1 si se pudieron devolver los datos.
** Al guardar una COPIA de "nombre", retorna -1 si la memoria no alcanzo.
** 0 si no hay mas datos. */
int nextCant(valoresADT datos, char ** nombre, size_t * cantArb, size_t * hab);

/* Devuelve los datos del barrio actual (nombre, cantidad de arboles).
** Retorna 1 si se pudieron devolver los datos.
** Al guardar una COPIA de "nombre", retorna -1 si la memoria no alcanzo.
** 0 si no hay mas datos. */
int nextBarrio(valoresADT datos, char ** nombre, size_t * cantArb);

/* Devuelve los datos del arbol actual (nombre, cantidad de arboles de esta especie).
** Retorna 1 si se pudieron devolver los datos.
** Al guardar una COPIA de "nombre", retorna -1 si la memoria no alcanzo.
** 0 si no hay mas datos. */
int nextArbol(valoresADT datos, char ** nombre, size_t * cantArb, double * diamAc);



#endif
