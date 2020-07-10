#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "desarrollo-tads/valoresADT.h"
#define MAX_CHAR 250
#define DELIM ";"
#define SIG_FIGURES 100 // 10 ^ n donde n es la cantidad de sifras significativas deseadas.
#define FREE freeValores(arboles); freeValores(barrios);

#ifdef VAN

#define BARRIO 12
#define ARBOL 6
#define DIAM 15

#endif

#ifdef BUE

#define BARRIO 2
#define ARBOL 7
#define DIAM 11

#endif

int main(int argc, char const *argv[]){
  errno = 0;
  FILE * barriosFile = fopen( argv[2], "r");
  FILE * arbolesFile = fopen( argv[1], "r");
  FILE * query1 = fopen("query1.csv", "wt");
  FILE * query2 = fopen("query2.csv", "wt");
  FILE * query3 = fopen("query3.csv", "wt");
  char aux[MAX_CHAR], * nombre, * habitantes, * diametro, * especie, * tok;
  valoresADT barrios = newValores(); // Aca alamacenamos barrios y sus respectiva cantidad de arboles y habitantes
  if(barrios==NULL)
    exit(1);
  valoresADT arboles = newValores(); // Aca almacenamos arboles y sus respectivos diametros y cantidad
  if(arboles==NULL){
    freeValores(barrios);
    exit(1);
  }

  // Hacemos una unica pasada al archivo de barrios, y guardamos todo en el TAD para procesarlo despues
  fgets(aux, MAX_CHAR, barriosFile);
  while(fgets(aux, MAX_CHAR, barriosFile) != NULL){
    nombre = strtok(aux, DELIM);
    habitantes = strtok(NULL, DELIM);
    if(addBarrio(barrios, nombre, atoi(habitantes)) == -1){ // Si devuelve -1, no hay mas memoria: libera los recursos y exitea.
      FREE
      exit(1);
    }
  }

  /* Hacemos una unica pasada al archivo de arboles, y guardamos todo en el TAD para procesarlo despues.
  ** Utilizamos los punteros auxiliares para guardar la informacion al TAD */
  fgets(aux, MAX_CHAR, arbolesFile);
  while(fgets(aux, MAX_CHAR, arbolesFile) != NULL){
    tok = strtok(aux, DELIM);
    for(int i = 0; tok != NULL; i++, tok = strtok(NULL, DELIM)){
      if(i == BARRIO)
        nombre = tok;
      else if(i == ARBOL)
        especie = tok;
      else if(i == DIAM)
        diametro = tok;
    }
    if(addArbol(arboles, especie, atof(diametro)) == -1 || addCant(barrios, nombre) == -1 ){
      FREE
      exit(1);
    }
  }


  // Resolucion de la Query 1.
  fprintf(query1, "BARRIOS;ARBOLES\n");
  size_t cant;
  ordenBarrio(barrios);
  toBegin(barrios);
  while(hasNext(barrios)){
    if(nextBarrio(barrios, &nombre, &cant) == -1){
      FREE
      exit(1);
    }
    fprintf(query1, "%s;%zu\n", nombre, cant);
    free(nombre); // Recordamos que la funcion nextBarrio guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  // Resolucion de la Query 2.
  fprintf(query2, "BARRIOS;ARBOLES_POR_HABITANTE\n");
  ordenCant(barrios);
  size_t hab;
  toBegin(barrios);
  while(hasNext(barrios)){
    if(nextCant(barrios, &nombre, &cant, &hab) == -1){
      FREE
      exit(1);
    }
    fprintf(query2, "%s;%g\n", nombre, ((int)((cant/(double)hab)*SIG_FIGURES)/(float)SIG_FIGURES));
    free(nombre); // Recordamos que la funcion nextCant guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  // Resultados de la Query 3.
  fprintf(query3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");
  ordenArbol(arboles);
  toBegin(arboles);
  double diamAc;
  while(hasNext(arboles)){
    if(nextArbol(arboles, &especie, &cant, &diamAc) == -1){
      FREE
      exit(1);
    }
    fprintf(query3, "%s;%g\n", especie, ((int)((diamAc/cant)*SIG_FIGURES))/(float)SIG_FIGURES);
    free(especie); // Recordamos que la funcion nextArbol guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  FREE
  fclose(barriosFile);
  fclose(arbolesFile);
  fclose(query1);
  fclose(query2);
  fclose(query3);
}
