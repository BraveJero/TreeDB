#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "valoresADT.h"

#define BARRIO 0
#define CANT 1
#define ARBOL 2
#define EPSILON 0.01
#define N 5

int main(int argc, char const *argv[])
{
    valoresADT nuevo = newValores();
    addBarrio(nuevo, "Almagro", 100);
    addBarrio(nuevo, "Liniers", 200);
    addBarrio(nuevo, "Junin", 120);
    addBarrio(nuevo, "AAA", 300);
    int ok =addBarrio(nuevo, "Almagro", 10000);
    if(ok == 0)
        printf("Ok\n");
    addCant(nuevo, "Almagro");
    addCant(nuevo, "Liniers");
    addCant(nuevo, "Flores");
    addCant(nuevo, "Almagro");
    addCant(nuevo, "Liniers");
    addCant(nuevo, "Flores");
    addCant(nuevo, "Almagro");
    addCant(nuevo, "Liniers");
    addCant(nuevo, "Flores");
    addCant(nuevo, "Almagro");
    addCant(nuevo, "Liniers");
    addCant(nuevo, "Flores");
    addCant(nuevo, "Almagro");
    for(int i=0; i<4; i++)
        addCant(nuevo, "AAA");
    for(int i=0; i< 10; i++)
        addCant(nuevo, "Junin");
    toBegin(nuevo);
    char * nombre;
    size_t cant;
    while(hasNext(nuevo)){
        nextBarrio(nuevo, &nombre, &cant);
        printf("El barrio %s tiene %ld arboles.\n", nombre, cant);
        free(nombre);
    }
    size_t cant2;
    ordenCant(nuevo);
    toBegin(nuevo);
    while(hasNext(nuevo)){
        nextCant(nuevo, &nombre, &cant, &cant2);
        printf("El barrio %s tiene %f arboles por habitante.\n", nombre, cant/(float)cant2);
        free(nombre);
    }
    

    freeValores(nuevo);



    return 0;
}
