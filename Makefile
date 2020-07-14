COMPILER=gcc
FLAGS=-pedantic -std=c99
FLAG_CURRENT=
DEBUG_COMPILER=-Wall -fsanitize=address -Wuninitialized -g
OUTPUT_FILE_BUE=arbolesADTBUE
OUTPUT_FILE_VAN=arbolesADTVAN
QUERYS=query1.csv query2.csv query3.csv 

all: BUE VAN 
	
debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

VAN: FLAG_CURRENT=-DVAN
VAN: mainVAN.o 
	$(COMPILER) -o $(OUTPUT_FILE_VAN) main.o valoresADT.o

BUE: FLAG_CURRENT=-DBUE
BUE: mainBUE.o 
	$(COMPILER) -o $(OUTPUT_FILE_BUE) main.o valoresADT.o

mainBUE.o: main.c
	$(COMPILER) -c $(FLAGS) $(FLAG_CURRENT) main.c desarrollo-tads/valoresADT.c

mainVAN.o: main.c
	$(COMPILER) -c $(FLAGS) $(FLAG_CURRENT) main.c desarrollo-tads/valoresADT.c

clean:
	rm -rf $(OUTPUT_FILE_BUE) $(OUTPUT_FILE_VAN) arbolesADTVAN *.o

cleanVAN: 
	rm -rf $(OUTPUT_FILE_VAN) *.o

cleanBUE:
	rm -rf $(OUTPUT_FILE_BUE) *.o

cleanQuerys:
	rm -f $(QUERYS)

