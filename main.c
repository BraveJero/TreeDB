#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "desarrollo-tads/valoresADT.h"

#define MAX_CHAR 250
#define DELIM ";"
#define QUERYS 3
//Representa la cantidad de columnas a leer
#define ALEER 3 

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

// Cierra 'cant_files' de 'files'.
void closeFiles(FILE * files[], size_t cant_files);

// Libera los recursos utilizados por 'arboles' y 'barrios' y cierra los #cant_files archivos de 'files'.
void outOfMemmory(valoresADT arboles, valoresADT barrios, FILE * files[], size_t cant_files);

int main(int argc, char const *argv[]){
  if( argc != 3 ){
    fprintf(stderr, "Cantidad invalida de parametros.\n");
    exit(1);
  }
  errno = 0;
  FILE * barriosFile = fopen(argv[2], "r");
  FILE * arbolesFile = fopen(argv[1], "r");
  FILE * query1 = fopen("query1.csv", "wt");
  FILE * query2 = fopen("query2.csv", "wt");
  FILE * query3 = fopen("query3.csv", "wt");
  size_t cant_files = QUERYS + argc - 1;
  FILE * files[] = {barriosFile, arbolesFile, query1, query2, query3};
  if (errno==ENOENT){
    closeFiles(files, cant_files);  //De no poder abrir un archivo cierro todos los que pude abrir.
    fprintf(stderr, "No se pudo abrir un archivo.\n");
    exit(1);
  }

  char aux[MAX_CHAR], * nombre, * habitantes, * diametro, * especie, * tok;  //Punteros auxiliares.
  valoresADT barrios = newValores(); // Aca alamacenamos barrios y sus respectiva cantidad de arboles y habitantes
  if (barrios==NULL){
    fprintf(stderr, "No hay memoria suficiente para almacenar los datos.\n"); //Aviso que me quede sin memoria.
    closeFiles(files, cant_files);
    exit(1); //Corto el programa.
  }
  valoresADT arboles = newValores(); // Aca almacenamos arboles y sus respectivos diametros y cantidad
  if (arboles==NULL){
    freeValores(barrios);
    fprintf(stderr, "No hay memoria suficiente para almacenar los datos.\n"); //Aviso que me quede sin memoria.
    closeFiles(files, cant_files);
    exit(1); //Corto el programa.
  }

  // Hacemos una unica pasada al archivo de barrios, y guardamos todo en el TAD para procesarlo despues
  fgets(aux, MAX_CHAR, barriosFile);
  while(fgets(aux, MAX_CHAR, barriosFile) != NULL){
    nombre = strtok(aux, DELIM);
    habitantes = strtok(NULL, DELIM);
    int resp_addBarrio = addBarrio(barrios, nombre, atoi(habitantes));
    if(resp_addBarrio == -1){ // Si devuelve -1, no hay mas memoria: libera los recursos y exitea.
      outOfMemmory(arboles, barrios, files, cant_files);
    }
    if(resp_addBarrio == 0){
      fprintf(stderr, "El barrio '%s' aparece mas de una vez en '%s'. Se tomo la primera aparicion del barrio.\n", nombre, argv[2]);
    }
  }

  /* Hacemos una unica pasada al archivo de arboles, y guardamos todo en el TAD para procesarlo despues.
  ** Utilizamos los punteros auxiliares para guardar la informacion al TAD */
  fgets(aux, MAX_CHAR, arbolesFile);
  while(fgets(aux, MAX_CHAR, arbolesFile) != NULL){
    tok = strtok(aux, DELIM);
    for(int i = 0, read=0; tok != NULL && read < ALEER; i++, tok = strtok(NULL, DELIM)){
      if(i == BARRIO){
        nombre = tok;
        read++;              //Utilizamos 'read' como flag para dejar de leer cuando ya obtuvimos las columnas deseadas. 
      } else if(i == ARBOL){
        especie = tok;
        read++;
      } else if(i == DIAM){
        diametro = tok;
        read++;
      }
    }
    if(addArbol(arboles, especie, atof(diametro)) == -1){
      outOfMemmory(arboles, barrios, files, cant_files);
    }
    if(addCant(barrios, nombre) == 0){
      fprintf(stderr, "El barrio '%s' en '%s' no pertenece a '%s'\n", nombre, argv[1], argv[2]);
    }
  }


  /*------------- Resolucion de la Query 1 -------------*/
  fprintf(query1, "BARRIO;ARBOLES\n");
  size_t cant;
  ordenBarrio(barrios);
  toBegin(barrios);
  while(hasNext(barrios)){
    if(nextBarrio(barrios, &nombre, &cant) == -1){
      outOfMemmory(arboles, barrios, files, cant_files);
    }
    fprintf(query1, "%s;%zu\n", nombre, cant);
    free(nombre); // Recordamos que la funcion nextBarrio guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  /*------------- Resolucion de la Query 2 -------------*/
  fprintf(query2, "BARRIO;ARBOLES_POR_HABITANTE\n");
  ordenCant(barrios);
  size_t hab;
  toBegin(barrios);
  while(hasNext(barrios)){
    if(nextCant(barrios, &nombre, &cant, &hab) == -1){
      outOfMemmory(arboles, barrios, files, cant_files);
    }
    if(hab!=0)  //De tener un barrio sin habitantes, calcular los arboles por habitante es absurdo. Como el query 1 admite un barrio con 0 habitantes. No cortamos el programa.
      fprintf(query2, "%s;%.2f\n", nombre, ((int)((cant/(double)hab)*SIG_FIGURES)/(float)SIG_FIGURES));
    else 
      fprintf(query2, "%s;%s\n", nombre, "No tiene habitantes.");
    free(nombre); // Recordamos que la funcion nextCant guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  /*------------- Resolucion de la Query 3 -------------*/
  fprintf(query3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");
  ordenArbol(arboles);
  toBegin(arboles);
  double diamAc;
  while(hasNext(arboles)){
    if(nextArbol(arboles, &especie, &cant, &diamAc) == -1){
      outOfMemmory(arboles, barrios, files, cant_files);
    }
    fprintf(query3, "%s;%.2f\n", especie, ((int)((diamAc/cant)*SIG_FIGURES))/(float)SIG_FIGURES);
    free(especie); // Recordamos que la funcion nextArbol guarda una COPIA, por lo que es necesario liberar ese espacio.
  }

  freeValores(arboles); freeValores(barrios);
  closeFiles(files, cant_files);
}

void outOfMemmory(valoresADT arboles, valoresADT barrios, FILE * files[], size_t cant_files){
  freeValores(arboles); 
  freeValores(barrios);  //Libera todos los recursos ocupados.
  fprintf(stderr, "No hay memoria suficiente para almacenar los datos.\n"); //Aviso que me quede sin memoria.
  closeFiles(files, cant_files);
  exit(1);
}

void closeFiles(FILE * files[], size_t cant_files){
  for(size_t i=0; i<cant_files; i++)
    if (files[i]!=NULL)
      fclose(files[i]);
  return;
}
