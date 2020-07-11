COMPILER=gcc
FLAGS=-pedantic -std=c99
FLAG_CURRENT=
DEBUG_COMPILER=-Wall -fsanitize=address -Wuninitialized -g
OUTPUT_FILE=
QUERYS=query1.csv query2.csv query3.csv 

all: BUE VAN 
	
#init: main.o 
#	$(COMPILER) -o $(OUTPUT_FILE) main.o valoresADT.o
## Si utilizamos esto en vez de poner el codigo en VAN y BUE no se generan los archivos.
## Vimos que esto es algo particular de Makefile, lo preguntamos una vez 	

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

VAN: OUTPUT_FILE=arbolesADTVAN
VAN: FLAG_CURRENT=-DVAN
VAN: main.o 
	$(COMPILER) -o $(OUTPUT_FILE) main.o valoresADT.o

BUE: OUTPUT_FILE=arbolesADTBUE
BUE: FLAG_CURRENT=-DBUE
BUE: main.o 
	$(COMPILER) -o $(OUTPUT_FILE) main.o valoresADT.o

main.o: main.c
	$(COMPILER) -c $(FLAGS) $(FLAG_CURRENT) main.c desarrollo-tads/valoresADT.c

clean: 
	rm -rf $(OUTPUT_FILE) *.o $(QUERYS)

