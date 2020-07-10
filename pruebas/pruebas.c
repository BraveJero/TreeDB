#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHAR 300


void getLine(FILE * file, char * resp);

int main(int argc, const char * argv[]){
  FILE * input = fopen(argv[1], "r");
  FILE * output = fopen("/home/juan/Documents/TPE-PI-2020/pruebas/output.txt", "wt");
  char resp[MAX_CHAR];

  for(getLine(input, resp); resp[0] != 0; getLine(input,resp)){
    char * tok = strtok(resp, ";");
    for (int i = 0; tok != NULL; i++){
      //if( i == 2 || i == 7 || i == 11)
        //fprintf(output, "|%s| ", tok);
      tok = strtok(NULL, ";" );
    }
    //fputc('\n', output);
  }

  fclose(input);
  fclose(output);
}

void getLine(FILE * file, char * resp){
  if (feof(file)){
    resp[0] = 0;
    return;
  }
  int c;
  size_t dim = 0;
  while ((c = fgetc(file)) != '\n'){
    resp[dim] = c;
    dim++;
  }
  resp[dim] = 0;
  return;
}
