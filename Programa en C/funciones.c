#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ARCHIVO DE DEFINICIÓN DE FUNCIONES

// ----------------------------------
// crearTablero(): Char[8][8] -> None

// Esta función es la encargada de inicializar el tablero de juego. Para ello, toma un array de arrays de caracteres (matriz bidimensional) de tamaño 8x8 como entrada
// y la inicializa con todos caracteres vacíos (' ') en cada posición, excepto las cuatro posiciones del medio que tendrán 2 piezas negras ('N') y 2 piezas blancas ('B').

void crearTablero(char tablero[FILAS][COLUMNAS]) {
    // Bucle que recorre las filas.
    for (int i = 0; i < FILAS; i++) {
        // Bucle que recorre las columnas.
        for (int j = 0; j < COLUMNAS; j++) {
            // Asignamos el String vacío a cada posición del tablero.
            tablero[i][j] = ' ';
        }
    }

    // Valores del medio del tablero.
    tablero[3][3] = 'B';
    tablero[4][4] = 'B';
    tablero[3][4] = 'N';
    tablero[4][3] = 'N';
}


// ----------------------------------------------------
// obtenerNombreColorJugador(): Char*, Jugador* -> None

// Esta función recibe dos argumentos: un puntero a una línea de texto (char *) y un puntero a una estructura Jugador.
// La función se encarga de separar el nombre y el color que hay en la línea de texto pasada como argumento,
// y almacena dichos datos en los campos de la estructura del argumento Jugador.

void obtenerNombreColorJugador(char* linea, Jugador* jugador) {
    char *nombre;
    char *color;

    // Con la función strtok dividimos la linea de texto en dos partes, a partir de la división que establece la coma.
    // Si la línea de texto es: "Alejandro,N", entonces nombre= Alejandro, es decir, lo que está antes de la coma.
    nombre = strtok(linea, ",");

    // La otra parte de la línea de texto corresponde al color del jugador.
    // Si la línea de texto es: "Alejandro,N", entonces color= N, es decir, lo que está después de la coma.
    color = strtok(NULL, " ");

    // Asignamos el nombre y el color a la estructura Jugador que fue pasada como argumento. Como estamos usando
    // un puntero que referencia a una estructura, esto lo hacemos a través de la sintaxis de acceso "->" = (*jugador).nombre.
    strcpy(jugador->nombre, nombre);
    strcpy(jugador->color, color);
}


// -------------------------------------
// perteneceAlTablero(): Int, Int -> Int

// Esta función determina si un par de coordenadas (posiciónX, posiciónY), representadas por números enteros, está dentro de los límites del tablero de juego. 
// Si ambas coordenadas son mayores o iguales a cero y menores a 8, la función devuelve True, lo que significa que las coordenadas pertenecen al tablero. 
// Si alguna de las coordenadas es menor a cero o mayor o igual a 8, la función devuelve False, lo que significa que las coordenadas no pertenecen al tablero.

int perteneceAlTablero(int posicionX, int posicionY){
    if(posicionX >= 0 && posicionX < FILAS && posicionY >= 0 && posicionY < COLUMNAS){
        return 1;
    }else{
        return 0;
    }
}


// -----------------------------------------
// formatearJugadaPotencial(): Char* -> None

// Esta función transforma la jugada leída de 2 caracteres, que se encuentra en formato letra-número a un formato numérico-numérico
// que se utilizará para poder acceder a la matriz que representa al tablero.
// Como los índices del array bidimensional que representa al tablero van del 0 al 7, se le asigna a cada letra de la A a la H
// un número comenzando por 0 y se le resta una unidad al caracter númerico de la jugada.
// Finalmente, como el primer caracter de la jugada representa a las columnas y el segundo a las filas, estos se voltean, ya que el acceso a la matriz tiene un formato fila-columna.

void formatearJugadaPotencial(char* jugada){
    
    switch(jugada[0]){
        case 'A':
            jugada[0]= '0';
            break;
        case 'B':
            jugada[0]= '1';
            break;    
        case 'C':
            jugada[0]= '2';
            break;
        case 'D':
            jugada[0]= '3';
            break;
        case 'E':
            jugada[0]= '4';
            break;
        case 'F':
            jugada[0]= '5';
            break;
        case 'G':
            jugada[0]= '6';
            break;
        case 'H':
            jugada[0]= '7';
            break;  
    }

    // Sentencias para dar vuelta los caracteres.
    char temporal = jugada[0];
    jugada[0] = jugada[1]-1;
    jugada[1] = temporal;
}


// ----------------------------------------
// formatearJugadaIngresada(): Char*, Char*

// Esta función se encarga de formatear la jugada ingresada por el usuario para que pueda ser utilizada por el programa en el juego. 
// Primero verifica si la jugada es un salto de línea, si es así, jugadaParaImprimir tendra el valor "pasar de turno". 
// Si no es un salto de línea, jugadaParaImprimir valdrá lo mismo que la jugada leída. Luego, se pregunta si la jugada tiene 2 caracteres y 
// de ser así se llamará a la función "formatearJugadaPotencial" para que se formatee como una jugada posible en el tablero.

void formatearJugadaIngresada(char* jugada, char* jugadaParaImprimir){

    // Preguntamos si la jugada es el salto de línea.
    if(jugada[0] == '\n'){

        jugada[0] = '\0';
        // Si es el salto de línea, jugadaParaImprimir tendrá el valor "pasar de turno". Esto es para visualizar la jugada en consola.
        char string[20]= "pasar de turno";
        strcpy(jugadaParaImprimir, string);

    }else{

        // En cambio, si la jugada que se está leyendo no es el salto de línea, pasamos a la etapa de formateo.
        // La siguiente sentencia borra el salto de línea de cada jugada que lee la función fgets.
        if(jugada[strlen(jugada)-1] == '\n'){
            jugada[strlen(jugada)-1]= '\0';
        }

        // Copiamos el valor leido en jugadaParaImprimir.
        strcpy(jugadaParaImprimir, jugada);
            
        // Se pregunta si la jugada leída tiene 2 caracteres. De ser asi, la jugada se convierte en una potencial jugada posible y debemos de analizarla.
        if(strlen(jugada)==2){

            // En la siguiente linea se convierte el primer caracter (letra) en mayusculas, por si se ingresan en minusculas y asi el programa puede progresar.
            // Como en la funcion formatearJugadaPotencial() se compara el primer caracter con letras mayusculas, debemos convertir las minusculas en caso de haberlas.
            jugada[0]= toupper(jugada[0]);

            // Formateamos la jugada para que pase a tener un valor NUMERO|NUMERO, pertenecientes a las entradas de la matriz del tablero.
            formatearJugadaPotencial(jugada);
        }

    }   
}


// ---------------------------------------------------------------
// crearArrayConJugadasPosibles(): Int, Int, Int*, Char*** -> None

// Esta función actualiza el array de de posiciones con nuevas posiciones válidas, y se asegura de que el mismo tenga la cantidad de memoria 
// necesaria para almacenar todas las posiciones que se pueden jugar.
// Como la cantidad de jugadas posibles vienen determinadas dependiendo la ejecución, debemos manejar el array de posicionesValidas dinámicamente.

void crearArrayConJugadasPosibles(int fila, int columna, int* posicion, char*** posicionesValidas){
    // Cada vez que se llame a esta función, la variable posicion que coincide con cantidadPosiciones de la función obtenerTodasLasJugadasPosibles()
    // incrementará su valor una unidad, para así poder agregar un nuevo elemento al array de posiciones válidas.
    *posicion+= 1;

    // Creamos dos arrays de caracteres, donde almacenaremos en forma de cadena los valores númericos de las variables fila y columna.
    char stringFila[10];
    char stringColumna[10];

    // Se usa la función sprintf para copiar el valor (Int) de fila y columna como una cadena de caracteres en los arreglos stringFila y stringColumna.
    sprintf(stringFila, "%d", fila);
    sprintf(stringColumna, "%d", columna);

    // Se utiliza la función strcat para concatenar los contenidos de stringFila y stringColumna en stringFila. 
    // Es decir, se unen los valores de fila y columna en un solo string.
    strcat(stringFila, stringColumna);

    // Al no saber cuantos elementos tendrá el array, lo asignamos dinámicamente, es decir, cambiaremos el tamaño del array en ejecución.
    // Para eso, se utiliza la función realloc, que cambia el tamaño de la memoria asignada a posicionesValidas. 
    // En particular, se redimensiona el arreglo para que tenga un espacio adicional.
    // La sentencia (char**) se usa para castear el tipo de puntero que devuelve realloc, que es un puntero void.
    *posicionesValidas = (char**) realloc(*posicionesValidas, sizeof(char*) * (*posicion));

    // Se asigna memoria con la función malloc para almacenar el string stringFila en el espacio correspondiente del arreglo posicionesValidas. 
    // strlen() devuelve la cantidad de caracteres de stringFila, y se le suma 1 para reservar espacio para el carácter nulo que indica el fin de la cadena.
    (*posicionesValidas)[*posicion - 1] = (char*) malloc(sizeof(char) * (strlen(stringFila) + 1));

    // Se utiliza la función strcpy para copiar el contenido de stringFila en el espacio recién reservado del arreglo posicionesValidas. 
    // La posición donde se copia el string es la última del arreglo, es decir, la que corresponde al valor de *posicion - 1.
    strcpy((*posicionesValidas)[*posicion - 1], stringFila);
}


// ------------------------------------------------------------------------
// obtenerTodasLasJugadasPosibles(): Char[8][8], Char, Char, Char*** -> Int

// La función busca todas las posibles jugadas válidas para el jugador que está en turno y las almacena en un array de cadenas de caracteres. 
// Para ello, recorre el tablero y, cuando encuentra una ficha del color que está jugando, itera las ocho posibles posiciones a su alrededor 
// para encontrar las jugadas posibles. Finalmente, la función devuelve la cantidad de posibles jugadas a realizar.

int obtenerTodasLasJugadasPosibles(char tablero[FILAS][COLUMNAS], char colorQueJuega, char colorOpuesto, char *** posicionesValidas){
    
    // Esta variable se utilizará como contador para agregar las posibles posiciones a un array.
    int cantidadPosiciones= 0;    

    // Estas listas (direccionHorizontal y direccionVertical) representan las ocho direcciones posibles en las que se puede mover en el tablero.
    // Explicado gráficamente: el primer número equivale al movimiento horizontal y el segundo al vertical.
    // Si "B" está en la posicion tablero[4][5] -> (-1 -1) equivale a tablero[3][4]
    // -1 -1 | 0 -1 | 1 -1
    // -1 0  |  B   | 1 0
    // -1 1  | 0 1  | 1 1
    int direccionHorizontal[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int direccionVertical[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Serie de bucles para recorrer el tablero.
    // Bucle para incrementar las filas.
    for(int i=0; i < FILAS; i++){   
        
        // Bucle para incrementar las columnas.
        for(int j=0; j < COLUMNAS; j++){       

            // Preguntamos si se encuentra una ficha del color que está jugando.
            if(tablero[i][j] == colorQueJuega){

                // Si se encontró una ficha del color que está jugando, iteramos 8 veces (8 posibles posiciones), para analizar el estado del tablero en las posiciones
                // aledañas a donde se encontró nuestra ficha.
                for(int r=0; r < 8; r++){

                    // filaAlrededor y columnaAlrededor serán las coordenadas aledañas a la posición donde se encuentra una ficha del color que está jugando.
                    // Hacemos uso de direccionHorizontal y direccionVertical nuevamente, para ir rodeando las coordenadas de nuestra ficha.
                    int filaAlrededor= i + direccionHorizontal[r];
                    int columnaAlrededor = j + direccionVertical[r];

                    // En esta sentencia, verificamos que las coordenadas que estamos analizando pertenezcan al tablero.
                    int estaEnTablero= perteneceAlTablero(filaAlrededor, columnaAlrededor);

                    // Preguntamos si encontramos una ficha del color opuesto, significando una posible jugada a realizar.
                    if (estaEnTablero == 1 && tablero[filaAlrededor][columnaAlrededor] == colorOpuesto){
                        
                        // Si es qué encontramos una ficha del color opuesto, entramos en un bucle, utilizando la misma dirección (mismos valores de filaAlrededor y
                        // columnaAlrededor) para determinar si la jugada es válida.
                        // Dicha condición de validación depende de que haya una secuencia de fichas del color opuesto en la misma dirección y que
                        // al final de la secuencia se encuentre una casilla vacía.
                        int condicion= 1;
                        while(condicion==1){
                            filaAlrededor+= direccionHorizontal[r];
                            columnaAlrededor+= direccionVertical[r];

                            // Si nos salimos del tablero, la jugada que estamos analizando se convierte en inválida.
                            if(perteneceAlTablero(filaAlrededor, columnaAlrededor) == 0){
                                condicion= 0;
                            }else{
                                
                                // Verificamos qué, siguiendo en la misma dirección en que encontramos una ficha del color opuesto,
                                // haya un lugar vacío, significando que podemos colocar allí una ficha del color que está jugando.
                                if(tablero[filaAlrededor][columnaAlrededor] == ' '){
                                    // Llegados hasta acá, sabemos que la posición "tablero[filaAlrededor][columnaAlrededor]" es una posible
                                    // jugada a realizar. Por eso, agregamos esta jugada al array posicionesValidas a través de la función crearArrayConJugadasPosibles().
                                    crearArrayConJugadasPosibles(filaAlrededor, columnaAlrededor, &cantidadPosiciones, posicionesValidas);
                                    condicion= 0;
                                }

                                // Si evaluando una dirección particular, llegamos a que en una posición no hay una ficha del color opuesto,
                                // saldremos del bucle while (condicion = 0). 
                                // Por lo tanto, el bucle se ejecutará utilizando una misma dirección (mismos valores de direccionHorizontal y direccionVertical), 
                                // siempre y cuando las coordenadas evaluadas no se salgan del tablero, y siempre que en dichas coordenadas haya una ficha del color opuesto.
                                if(tablero[filaAlrededor][columnaAlrededor] != colorOpuesto){
                                    condicion= 0;
                                }
                            }

                            
                        }

                    }
                }
            }

        }
    }

    // Retornamos la cantidad de posiciones que tiene el array posicionesValidas para poder recorrerlo luego.
    return cantidadPosiciones;
}


// -----------------------------------------------
// liberarPosicionesValidas(): Char**, Int -> None

// Esta función se encarga de liberar la memoria previamente asignada al array "posicionesValidas" y sus elementos correspondientes. 
// Mediante un bucle for y con el parámetro cantidadPosiciones, la función recorre cada fila del arreglo y libera la memoria asignada a cada cadena de caracteres. 
// Luego, libera la memoria asignada al array en sí. De esta manera, la función libera completamente la memoria asignada a la lista y sus elementos correspondientes.

void liberarPosicionesValidas(char** posicionesValidas, int cantidadPosiciones){
    for (int i = 0; i < cantidadPosiciones; i++) {
        free(posicionesValidas[i]);
    }
    free(posicionesValidas);
}


// ------------------------------------------
// evaluarJugada(): Char*, Int, Char** -> Int

// Esta función se encarga de analizar si una jugada es válida. Para eso, hace uso del array posicionesValidas y la cantidad de posiciones que este tiene.
// Si la jugada es el salto de línea, la cantidad de posiciones del array posicionesValidas debe ser 0 para que sea una jugada válida.
// En cambio, si la jugada no es vacía, comparamos la jugada con todos los valores de posicionesValidas. En caso de encontrar coincidencias, la jugada será válida.
// Si la jugada es válida se devuelve un 1, caso contrario la función retorna 0.

int evaluarJugada(char* jugada, int cantidadPosiciones, char** posicionesValidas){

    if(cantidadPosiciones==0 && jugada[0]== '\0'){
        // Si la cantidad de posiciones del array posicionesValidas es 0 y la jugada es el salto de línea, pasar de turno resulta una jugada válida y se retorna un 1.
        return 1;
    }

    // Recorremos todo el array de posicionesValidas y preguntamos si alguna de todas las jugadas almacenadas en él coinciden con la jugada que se ha leído.
    // Si encontramos una coincidencia, significa que la jugada leída es válida y se retorna un 1.
    for(int i = 0; i<cantidadPosiciones; i++) {
        
        if(strcmp(jugada, posicionesValidas[i]) == 0){
            return 1;
        }
    }

    // Si no hemos encontrado coincidencias con la jugada leída y el arreglo posicionesValidas, se devuelve un 0, indicando que la jugada leída es inválida.
    return 0;
}


// -----------------------------------------------------------
// ejecutarMovimiento(): Char[8][8], Char*, Char, Char -> None

// Esta función se encarga de "dar vuelta" las fichas opuestas de cada jugada que lee. Para ello, coloca una ficha del color que juega en la posición del tablero que representa "jugada" 
// y luego itera sobre las ocho posibles direcciones del tablero, buscando una ficha del color opuesto. 
// Si se encuentra una ficha del color opuesto, la función continúa buscando a lo largo de esa dirección hasta que encuentra una ficha del mismo color que está jugando, 
// momento en el cual cambia todas las fichas del color opuesto a lo largo de esa dirección a fichas del color que juega.

void ejecutarMovimiento(char tablero[FILAS][COLUMNAS], char *jugada, char colorQueJuega, char colorOpuesto){

    // Estas listas (direccionHorizontal y direccionVertical) representan las ocho direcciones posibles en las que se puede mover en el tablero.
    int direccionHorizontal[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int direccionVertical[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Con la jugada ya formateada en dos valores númericos, la separamos en dos variables para acceder a los valores del tablero.
    // Con sscanf extraemos en forma de entero los valores de los caracteres númericos de jugada. Si jugada es "46", entonces int posicionX = 4 | int posicionY = 6.
    int posicionX, posicionY;
    sscanf(jugada, "%1d%1d", &posicionX, &posicionY);

    // Le asignamos el color que juega en este turno a la casilla vacía que hay en la posición que representa la jugada.
    tablero[posicionX][posicionY] = colorQueJuega;

    // Se recorre un bucle que itera sobre las 8 posibles direcciones, verificando si en cada dirección particular se encuentra una ficha del colorOpuesto en las coordenadas adyacentes. 
    // Si no se encuentra, se pasa a la siguiente dirección.
    for(int i=0; i<FILAS; i++){
        int filaAlrededor= posicionX + direccionHorizontal[i];
        int columnaAlrededor = posicionY + direccionVertical[i];

        int estaEnTablero= perteneceAlTablero(filaAlrededor, columnaAlrededor);

        // Se pregunta si encuentra una ficha del color opuesto alrededor de una ficha del color que juega.
        if (estaEnTablero == 1 && tablero[filaAlrededor][columnaAlrededor] == colorOpuesto){   

            // Si se encuentra una ficha del colorOpuesto, entonces se sigue moviendo en esa dirección verificando si la siguiente ficha es del colorOpuesto, 
            // de ser así se continúa moviendo en esa dirección.  
            int condicion= 1;
            while(condicion==1){
                filaAlrededor+= direccionHorizontal[i];
                columnaAlrededor+= direccionVertical[i];

                // Si se llega al borde del tablero o se encuentra una casilla vacía, se termina el bucle.
                if(perteneceAlTablero(filaAlrededor, columnaAlrededor) == 0){
                    condicion= 0;
                    
                }else if(tablero[filaAlrededor][columnaAlrededor] == ' '){
                    condicion= 0;

                }else if(tablero[filaAlrededor][columnaAlrededor] == colorQueJuega){
                    // Si se encuentra una ficha del colorQueJuega, se retrocede en la dirección opuesta y se cambian todas las fichas del colorOpuesto por colorQueJuega.
                    filaAlrededor -= direccionHorizontal[i];
                    columnaAlrededor -= direccionVertical[i];

                    while (filaAlrededor != posicionX || columnaAlrededor != posicionY) {
                        tablero[filaAlrededor][columnaAlrededor] = colorQueJuega;
                        filaAlrededor -= direccionHorizontal[i];
                        columnaAlrededor -= direccionVertical[i];
                    }

                    condicion=0;
                }

            }
        }
    }
}


// -----------------------------------------------------
// leerJugadas(): FILE*, Char[8][8], Char*, Char* -> Int

// Los argumentos de esta función son:
//      - FILE* archivoLectura: puntero al archivo donde están escritas las jugadas a evaluar.
//      - char tablero[8][8]: array bidimensional de caracteres que representa el tablero.
//      - char* colorQueJuega: puntero a un caracter que representa el color de la ficha que jugará en el turno actual.
//      - char* colorOpuesto: puntero a un caracter que representa el color opuesto a colorQueJuega.

// Esta función lee las jugadas que están escritas en archivoLectura y las procesa.
// Para esto, usa un bucle que lee cada jugada con la función fgets y, luego, procesa cada jugada con la función evaluarJugada.
// La función retorna un int que representa el valor de salida de la función. Si la función retorna 1, significa que se han leido todas las jugadas con éxito, 
// mientras que un retorno igual a 0 significa que ha habido un error en la lectura de alguna jugada.

int leerJugadas(FILE* archivoLectura, char tablero[FILAS][COLUMNAS], char* colorQueJuega, char* colorOpuesto){
    
    // Esta variable se usará para leer cada jugada del archivo.
    char jugada[30];
    
    // En la función main() se ha decidido utilizar la función fscanf para leer las 3 primeras líneas, en cambio para leer
    // las jugadas a evaluar se utilizará la función fgets.
    // Como fscanf no lee los saltos de línea y fgets si lo hace, la siguiente línea lee el salto de línea que quedó entre el color que arranca y la primer jugada.
    // fgets(<arrayDondeSeGuarda>, <longitudMaximaCadena>, <variableFile>)
    fgets(jugada, sizeof(jugada), archivoLectura);
    
    // Este bucle itera siempre y cuando se pueda seguir leyendo el archivo. De lo contrario, terminará su ejecución.
    while(!feof(archivoLectura)){

        // Si la última jugada del archivo es un salto de línea y este es válido, con esta sentencia se podrá validar.
        // De lo contrario, al leer cada jugada se sobreescribirá la variable por lo que se haya leído.
        jugada[0]= '\n';

        // Leemos cada línea del archivo y la guardamos en jugada.
        fgets(jugada, sizeof(jugada), archivoLectura);

        // ------------------------------
        // FORMATEAR LA JUGADA INGRESADA:
        // Las jugadas ingresadas son de la forma LETRA|NUMERO: "A5".
        // Para trabajar en el programa necesitamos formatear dicha jugada para así poder acceder a los valores del tablero.
        // En la variable jugadaParaImprimir copiaremos el valor de las  jugadas ingresadas para poder imprimirlas luego.
        char jugadaParaImprimir[30];

        formatearJugadaIngresada(jugada, jugadaParaImprimir);

        // -----------------------------------
        // OBTENER TODAS LAS JUGADAS POSIBLES:
        // Se declara "char** posicionesValidas" que es un puntero que apunta a un puntero que apunta a un caracter.
        // Es una variable que guarda la direccion de memoria de un array de strings, donde cada string es a su vez, un array de caracteres.
        // En este array se almacenarán las posibles jugadas que tiene cada color en el estado actual del tablero.
        char** posicionesValidas= NULL;

        // Se llama a obtenerTodasLasJugadasPosibles() para obtener todas las jugadas posibles del color que juega en este turno,
        // en el estado actual del tablero y almacenarlas en posicionesValidas.
        // La llamada a esta función se le asigna a la variable cantidadPosiciones ya que obtenerTodasLasJugadasPosibles() devuelve
        // en forma de entero, la cantidad de jugadas posibles a realizar.
        int cantidadPosiciones= obtenerTodasLasJugadasPosibles(tablero, *colorQueJuega, *colorOpuesto, &posicionesValidas);

        // ------------------------
        // VALIDACIÓN DE LA JUGADA:
        // Evaluamos si la jugada que se está leyendo actualmente es válida.
        int jugadaValida= evaluarJugada(jugada, cantidadPosiciones, posicionesValidas);

        // Liberamos los espacios de memoria del array posicionesValidas.
        liberarPosicionesValidas(posicionesValidas, cantidadPosiciones);

        if(jugadaValida==1 && jugada[0]=='\0'){
            // Si la jugada es válida y es un salto de línea, no se hace nada.
        }else if (jugadaValida==1){
            // Si la jugada es válida y no es un salto de línea, ejecutamos el movimiento.
            ejecutarMovimiento(tablero, jugada, *colorQueJuega, *colorOpuesto);
        }else{
            // Si la jugada es inválida, imprimimos un mensaje de error y termina la función.
            printf("La jugada %s realizada por %c resulta invalida. La partida no puede continuar.\n", jugadaParaImprimir, *colorQueJuega);

            // Retornamos el valor de jugadaValida, que llegados a esta línea, equivale a 0, indicando que ha habido un error en la lectura de una jugada.
            return jugadaValida;
        }
        
        // Cambia el turno del color que juega. Si la jugada que se leyó pertenecía a las fichas blancas, la siguiente pertenecerá a las fichas negras.
        *colorOpuesto= *colorQueJuega;
        *colorQueJuega = (*colorQueJuega == 'B') ? 'N' : 'B';
    }

    // Retornamos 1, significando de que se han leído con éxito todas las jugadas.
    return 1;
}


// -------------------------------------
// imprimirTablero(): Char[8][8] -> None

// Esta función se encarga de imprimir en la consola una representación visual del tablero, mostrando las posiciones de las fichas en el mismo.
// Primero, se itera sobre la variable columnas y se imprimen los nombres de las columnas separados por un espacio en la misma línea.
// Luego, se itera sobre las filas de la matriz tablero y se imprimen los números de las filas. 
// Finalmente, se recorre todo el tablero y se imprime cada ficha en su casilla correspondiente entre barras verticales para separarla visualmente de las otras fichas de la misma fila.

void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    printf("Tablero final: \n");
    printf("  ");
    char* columnas= "ABCDEFGH";

    // Imprimimos los índices de cada columna utilizando el array de caracteres "columnas".
    for (int i = 0; i < COLUMNAS; i++) {
        printf("%c ", columnas[i]);
    }
    printf("\n");

    // Imprimimos cada entrada de la matriz del tablero.
    for (int i = 0; i < FILAS; i++) {
        printf("%d", i+1);
        
        for (int j = 0; j < COLUMNAS; j++) {
            printf("|");
            printf("%c", tablero[i][j]);
        }
        printf("\n");
    }
}


// --------------------------------------------
// evaluarPartidaTerminada(): Char[8][8] -> Int

// Esta función evalúa si la partida ha terminado al verificar si ambos jugadores no tienen ninguna jugada posible. 
// En primer lugar, llama a la función obtenerTodasLasJugadasPosibles para obtener la cantidad de posibles jugadas para ambos jugadores. 
// Si ambas cantidades son iguales a cero, lo que significa que no hay posibles jugadas para ninguno de los jugadores, 
// la función imprime un mensaje y devuelve 1, lo que indica que la partida ha terminado. Si no, la función devuelve 0, lo que significa que la partida aún no ha terminado.

int evaluarPartidaTerminada(char tablero[FILAS][COLUMNAS]){
    // Variables donde se almacenarán las posibles jugadas de cada jugador.
    char** posicionesValidasNegras= NULL;
    char** posicionesValidasBlancas= NULL;

    // Variables que almacenan la cantidad de jugadas a realizar de cada jugador.
    int cantidadPosicionesNegras= obtenerTodasLasJugadasPosibles(tablero, 'N', 'B', &posicionesValidasNegras);
    int cantidadPosicionesBlancas= obtenerTodasLasJugadasPosibles(tablero, 'B', 'N', &posicionesValidasBlancas);

    // Si no quedan jugadas posibles a realizar para ningun jugador, termina la partida.
    if(cantidadPosicionesNegras==0 && cantidadPosicionesBlancas==0){
        liberarPosicionesValidas(posicionesValidasNegras, cantidadPosicionesNegras);
        liberarPosicionesValidas(posicionesValidasBlancas, cantidadPosicionesBlancas);

        return 1;
    }else{
        return 0;
    }
}


// ---------------------------------------------------
// determinarGanador(): Char[8][8], Int*, Int* -> Char

// Esta función recorre toda la matriz que representa al tablero de juego y cuenta las fichas que hay de cada color.
// Luego, devuelve "B" si hay más fichas de color blanco, "N" si hay más del color negro o "X" si hay la misma cantidad de cada color, significando un empate.
// Como estamos recibiendo la dirección de las variables enteras contadorBlancas y contadorNegras, podemos modificar su valor en la función
// y que dichos cambios sigan iguales en la función main, lo que nos va a permitir imprimir la cantidad de fichas de cada color luego.

char determinarGanador(char tablero[FILAS][COLUMNAS], int* contadorBlancas, int* contadorNegras){

    // Bucle para incrementar las filas.
    for(int i=0; i < FILAS; i++){
        // Bucle para incrementar las columnas.
        for(int j=0; j < COLUMNAS; j++){

            if(tablero[i][j] == 'B'){
                // Suma una unidad al contador de fichas blancas si encuentra "B" en una posición del tablero.
                *contadorBlancas= *contadorBlancas + 1;
            }else if(tablero[i][j] == 'N'){
                // Suma una unidad al contador de fichas blancas si encuentra "B" en una posición del tablero.
                *contadorNegras= *contadorNegras + 1;
            }

        }
    }

    if(*contadorBlancas > *contadorNegras){
        return 'B';
    }else if(*contadorBlancas == *contadorNegras){
        return 'X';
    }else{
        return 'N';
    }
}


// -------------------------------------------------
// imprimirGanador(): Char, Jugador, Jugador -> None

// Esta función no tiene retorno ya que solamente se encarga de imprimir en pantalla el resultado de la partida.
// Para eso, compara el retorno de la funcion determinarGanador y lo compara con el color de cada jugador, almacenado en su estructura.

void imprimirGanador(char ganador, Jugador jugador1, Jugador jugador2){

    if(ganador == 'X'){
        printf("La partida resulto en empate.\n");
    }else if(ganador == jugador1.color[0]){
        printf("resulta ganador el jugador de fichas %s cuyo nombre es %s.\n", jugador1.color,jugador1.nombre);
    }else{
        printf("resulta ganador el jugador de fichas %s cuyo nombre es %s.\n", jugador2.color,jugador2.nombre);
    }
}


// -----------------------------------------------------------
// escribirTableroEnArchivo(): Char[8][8], Char*, Char -> None

// Esta función recorre toda la matriz del tablero y escribe el valor de cada posición del mismo en su estado actual en el archivo que es pasado como argumento.
// Para eso, se vale de las funciones de escritura de archivos: fprintf y fwrite.

void escribirTableroEnArchivo(char tablero[FILAS][COLUMNAS], char* archivoIngresadoParaEscribir, char colorQueJuega){
    // Creación de la variable FILE archivoEscritura, donde se escribirá el tablero resultante luego de una partida inconclusa.
    FILE* archivoEscritura;
    archivoEscritura = fopen(archivoIngresadoParaEscribir,"w");

    // Bucle para incrementar las filas.
    for(int i=0; i < FILAS; i++){
        // Bucle para incrementar las columnas.
        for(int j=0; j < COLUMNAS; j++){

            if(tablero[i][j]== ' '){
                // Si en alguna posición del tablero se encuentra un caracter vacío, que representa un espacio libre, se imprime una X.
                fprintf(archivoEscritura, "X");
            }else{
                // De lo contrario, se imprime lo que haya en cada posición del tablero.
                fwrite(&tablero[i][j], sizeof(char), 1, archivoEscritura);
            }


        }
        fprintf(archivoEscritura, "\n");
    }

    // Se imprime el color que continua jugando.
    fwrite(&colorQueJuega, sizeof(char), 1, archivoEscritura);

    // Se cierra el archivo donde se ha escrito.
    fclose(archivoEscritura);
}