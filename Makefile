COMPILER=gcc
FLAGS=-pedantic -std=c99
FLAG_CURRENT=
DEBUG_COMPILER=-Wall -fsanitize=address -Wuninitialized -g
OUTPUT_FILE=
QUERYS=query1.csv query2.csv query3.csv 

all: BUE VAN 
	
debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

VAN: OUTPUT_FILE=arbolesADTVAN
VAN: FLAG_CURRENT=-DVAN
VAN: mainVAN.o 
	$(COMPILER) -o $(OUTPUT_FILE) main.o valoresADT.o

BUE: OUTPUT_FILE=arbolesADTBUE
BUE: FLAG_CURRENT=-DBUE
BUE: mainBUE.o 
	$(COMPILER) -o $(OUTPUT_FILE) main.o valoresADT.o

mainBUE.o: main.c
	$(COMPILER) -c $(FLAGS) $(FLAG_CURRENT) main.c desarrollo-tads/valoresADT.c

mainVAN.o: main.c
	$(COMPILER) -c $(FLAGS) $(FLAG_CURRENT) main.c desarrollo-tads/valoresADT.c

clean: 
	rm -rf $(OUTPUT_FILE) *.o

cleanQuerys:
	rm -f $(QUERYS)

