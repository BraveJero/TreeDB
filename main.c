#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "desarrollo-tads/valoresADT.h"
#define MAX_CHAR 250
#define DELIM ";"

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
  FILE * barriosFile = fopen( argv[1], "r");
  FILE * arbolesFile = fopen( argv[2], "r");
  FILE * query1 = fopen("resultados/query1.csv", "wt");
  FILE * query2 = fopen("resultados/query2.csv", "wt");
  FILE * query3 = fopen("resultados/query3.csv", "wt");
  char aux[MAX_CHAR], * nombre, * habitantes, * diametro, * especie, * tok;
  valoresADT barrios = newValores();
  valoresADT arboles = newValores();

  fgets(aux, MAX_CHAR, barriosFile);
  while(fgets(aux, MAX_CHAR, barriosFile) != NULL){
    nombre = strtok(aux, DELIM);
    habitantes = strtok(NULL, DELIM);
    addBarrio(barrios, nombre, atoi(habitantes));
  }

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
    addArbol(arboles, especie, atof(diametro));
    addCant(barrios, nombre);
  }

  fprintf(query1, "BARRIOS;ARBOLES\n");
  size_t cant;
  ordenBarrio(barrios);
  toBegin(barrios);
  while(hasNext(barrios)){
    nextBarrio(barrios, &nombre, &cant);
    fprintf(query1, "%s;%zu\n", nombre, cant);
    free(nombre);
  }

  fprintf(query2, "BARRIOS;ARBOLES_POR_HABITANTE\n");
  ordenCant(barrios);
  size_t hab;
  toBegin(barrios);
  while(hasNext(barrios)){
    nextCant(barrios, &nombre, &cant, &hab);
    fprintf(query2, "%s;%2.2g\n", nombre, cant/(double)hab);
    free(nombre);
  }

  fprintf(query3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");
  ordenArbol(arboles);
  toBegin(arboles);
  double diamAc;
  while(hasNext(arboles)){
    nextArbol(arboles, &especie, &cant, &diamAc);
    fprintf(query3, "%s;%2.2g\n", especie, diamAc/cant);
    free(especie);
  }

  freeValores(barrios);
  freeValores(arboles);
  fclose(barriosFile);
  fclose(arbolesFile);
  fclose(query1);
  fclose(query2);
  fclose(query3);
}
