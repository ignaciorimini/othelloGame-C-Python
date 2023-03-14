// OTHELLO: Programa en C

// Representaremos el tablero de juego en forma de matriz 8x8 como una lista de 8 listas de 8 caracteres: List[List[Char]].
// Gráficamente:
// tablero[FILAS][COLUMNAS] = {
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//     {' ', ' ', ' ', 'B', 'N', ' ', ' ', ' '},
//     {' ', ' ', ' ', 'N', 'B', ' ', ' ', ' '},
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
//     };

// Sus valores se identifican con la pieza que se encuentra en cada posición. Estos valores pueden ser: 
//   1. El caracter ("X") correspondiente a una posición libre.
//   2. El caracter ("B") correspondiente a una pieza de color blanco.
//   3. El caracter ("N") correspondiente a una pieza de color negro.

// --------------------------------
// Para definir al tablero más fácilmente se usarán macros: #define FILAS 8 y #define COLUMNAS 8.

// Para representar a cada jugador de la partida, crearemos una estructura Jugador que es (String, String).
// Un elemento Jugador representa a un participante del juego. 
// El primer campo es un String que representa al nombre del jugador y el segundo campo es un String que representa el color con el que juega.

// Dicha estructura y los macros anteriores se definen en el archivo "funciones.h".

// --------------------------------
// Como los formatos de los archivos .txt son distintos entre Windows y Linux, al compilar en Linux es probable que los .txt generados en Windows
// no funcionen de la manera esperada. Para esto, se puede utilizar el comando "dos2unix archivoWindows.txt" para darle formato Linux a dicho archivo
// y que funcione de la manera correcta.

// --------------------------------
// Librerías a utilizar:
#include <stdio.h>  // Funciones de entrada/salida en consola.
#include <string.h> // Funciones para manipular strings.
#include <stdlib.h> // Funciones para gestionar memoria dinámica.
#include <ctype.h>  // Funciones para trabajar con caracteres.

// Las funciones que utiliza este programa se definen en un archivo aparte "funciones.c" y los casos de prueba en "testeo.c".
// Para incluirlas en este documento, llamamos a sus correspondientes archivos de cabecera .h
#include "funciones.h"
#include "testeo.h"

// --------------------------------
// Como estamos haciendo uso de 3 archivos .c distintos, al compilar se deben compilar los 3 archivos a la vez para generar un solo ejecutable:
// gcc othello.c funciones.c testeo.c -o nombreArchivo.exe

// --------------------------------
int main(int argc, char *argv[]){

    // Utilizando los argumentos arg y argv en la función main, le permitimos al usuario ingresar los argumentos del programa a la hora de ejecutarlo.
    // De esta manera, si el usuario escribe en consola el siguiente comando: a.exe archivoLectura.txt archivoEscritura.txt
    //   - argv[1] coincide con el archivo donde el programa leerá las jugadas, en este caso "archivoLectura.txt".
    //   - sys.argv[2] coincide con el archivo donde el programa escribirá en caso de partida inconclusa. En este caso es: "archivoEscritura.txt"

    // Creación de la variable FILE archivoLectura, donde se tratará de abrir el primer argumento que ingrese el usuario en la consola, en modo lectura.
    FILE* archivoLectura;
    archivoLectura = fopen(argv[1],"r");

    // Si fue ingresado un archivo inválido, se mostrará un mensaje de error y se terminará la ejecución del programa.
    if(archivoLectura==NULL){
        printf("No se pudo abrir el archivo de lectura correctamente. Ejecute de nuevo el programa.");
        return 1;
    }

    // Con fscanf leemos las 3 primeras líneas del archivo, almacenándolas en las 3 variables "linea1", "linea2" y "colorArranca".
    // Para evitar el desbordamiento de bufer si el usuario proporciona una entrada de datos muy grande, especificamos el ancho máximo de caracteres a leer: %99 %99 %9
    char linea1[100];
    char linea2[100];
    char colorArranca[10];
    fscanf(archivoLectura, "%99s %99s %9s", linea1, linea2, colorArranca);

    // Creamos dos Jugadores llamados jugador1 y jugador2.
    Jugador jugador1, jugador2;
    
    // Ya teniendo dos Jugadores creados, usando la funcion obtenerNombreColor(), almacenamos en sus respectivos campos, sus nombres y sus colores.
    obtenerNombreColorJugador(linea1, &jugador1);
    obtenerNombreColorJugador(linea2, &jugador2);

    // Creación del tablero: matriz 8x8 en forma de array bidimensional.
    // Siendo "tablero" de la forma char[8][8], queda conformado un array de 8 arrays con 8 elementos (carácteres) cada uno.
    char tablero[FILAS][COLUMNAS];
    crearTablero(tablero);

    // Determinamos el color que arrancará jugando y el color opuesto.
    char colorQueJuega= colorArranca[0];
    char colorOpuesto = (colorQueJuega == 'B') ? 'N' : 'B';

    // Si se han leído todas las jugadas exitosamente, la función leerJugadas habrá retornado un 1.
    int jugadasIngresadasSonValidas= leerJugadas(archivoLectura, tablero, &colorQueJuega, &colorOpuesto);

    // Si la partida terminó se retorna un 1.
    int estadoPartida= evaluarPartidaTerminada(tablero);

    if(jugadasIngresadasSonValidas==1 && estadoPartida==1){
        // Si todas las jugadas ingresadas fueron válidas y la partida terminó, imprimimos un mensaje de partida finalizada y procedemos a determinar e imprimir al ganador,
        // mostrando cuantas fichas hay de cada color.
        printf("Partida terminada.\n");

        // Contadores de fichas de cada color.
        int contadorBlancas= 0;
        int contadorNegras= 0;

        // Determinamos el color ganador.
        char ganador= determinarGanador(tablero, &contadorBlancas, &contadorNegras);

        // Imprimimos cuantas fichas hay de cada color.
        printf("Con %d fichas blancas y %d fichas negras, ", contadorBlancas, contadorNegras);

        // Imprimimos al ganador de la partida.
        imprimirGanador(ganador, jugador1, jugador2);

    }else if(jugadasIngresadasSonValidas==1){
        // Si todas las jugadas ingresadas fueron válidas pero no bastaron para rellenar el tablero y finalizar la partida, se imprime el tablero resultante hasta el momento
        // en un archivo, haciendo uso de la función escribirTableroEnArchivo.
        printf("Partida inconclusa.\n");
        escribirTableroEnArchivo(tablero, argv[2], colorQueJuega);
    }

    // Finalmente, imprimimos el tablero resultante y cerramos el archivo de lectura de jugadas.
    imprimirTablero(tablero);
    fclose(archivoLectura);
    
    // Llamamos a las funciones que contienen los casos de prueba (archivo testeo.c):
    test_obtenerNombreColor();
    test_perteneceAlTablero();
    test_formatearJugadaPotencial();
    test_crearArrayConJugadasPosibles();
    test_obtenerTodasLasJugadasPosibles();
    test_evaluarJugada();
    test_ejecutarMovimiento();
    test_evaluarPartidaTerminada();
    test_determinarGanador();

    return 0;
}
