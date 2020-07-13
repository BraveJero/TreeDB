# TPE-PI-2020

Para generar ambos ejecutables, desde la terminal ejecutar el comando "make" en el directorio actual. 
  - En caso de querer generar sólo uno correr el comando "make " seguido de la opción deseada ("VAN" o "BUE"). 
  - En caso de querer debugear el programa, correr "make debug" y se crearán ambos ejecutables,
    pero compilando el programa con los flags: "-Wall -fsanitize=address -Wuninitialized -g". 

Los posibles ejecutables que se crearán tendrán los nombres "arbolesADTBUE" y "arbolesADTVAN". 

Para correr el programa, desde la terminal ejecutar el programa creado anteriormente, agregando los argumentos de línea de comando que correspondan a:
  - El archivo que contiene a los árboles de la ciudad (Primer argumento). 
  - El archivo que contiene los barrios de la ciudad (Segundo argumento).
Por ejemplo, para Buenos Aires: "$./arbolesADTBUE ./arbolesBUE.csv ./barriosBUE.csv".

Para Buenos Aires, el ejecutable está configurado para que los datos se encuentren en cada archivo de la forma:
  - barriosBUE.csv:
    * "nombre" en la columna 1.
    * "habitantes" en la columna 2.
  - arbolesBUE.csv: 
    * "comuna" en la columna 3.
    * "nombre_cientifico" la en columna 8.
    * "diametro_altura_pecho" la en columna 12.
   
Para Vancouver, el ejecutable está configurado para que los datos se encuentren en cada archivo de la forma:
  - barriosVAN.csv:
    * "nombre" en la columna 1.
    * "habitantes" en la columna 2.
  - arbolesVAN.csv: 
    * "COMMON_NAME" en la columna 7.
    * "NEIGHBOURHOOD_NAME" en la columna 13.
    * "DIAMETER" en la columna 16.
