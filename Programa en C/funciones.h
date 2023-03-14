// ARCHIVO DE CABECERA: Funciones del programa.

#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_
#include <stdio.h>

// Definición de constantes para trabajar con el tablero.
#define FILAS 8
#define COLUMNAS 8

// Creación de la estructura Jugador que es (String, String).
// Un elemento Jugador representa a un participante del juego. 
// El primer campo es un String que representa al nombre del jugador y el segundo campo es un String que representa el color con el que juega.
typedef struct{
    char nombre[100];
    char color[2];
} Jugador;


// PROTOTIPOS DE LAS FUNCIONES: Las mismas se desarrollan en el archivo "funciones.c".
void crearTablero(char tablero[FILAS][COLUMNAS]);
void obtenerNombreColorJugador(char *linea, Jugador *jugador);
int perteneceAlTablero(int posicionX, int posicionY);
void formatearJugadaPotencial(char* jugada);

void crearArrayConJugadasPosibles(int fila, int columna, int *posicion, char ***posicionesValidas);
int obtenerTodasLasJugadasPosibles(char tablero[FILAS][COLUMNAS], char colorQueJuega, char colorOpuesto, char *** posicionesValidas);
int evaluarJugada(char *jugada, int cantidadPosiciones, char **posicionesValidas);
void liberarPosicionesValidas(char** posicionesValidas, int cantidadPosiciones);
void ejecutarMovimiento(char tablero[FILAS][COLUMNAS], char *jugada, char colorQueJuega, char colorOpuesto);
void formatearJugadaIngresada(char* jugada, char* jugadaParaImprimir);
int leerJugadas(FILE *archivoLectura, char tablero[FILAS][COLUMNAS], char* colorQueJuega, char* colorOpuesto);

void imprimirTablero(char tablero[FILAS][COLUMNAS]);
int evaluarPartidaTerminada(char tablero[FILAS][COLUMNAS]);
char determinarGanador(char tablero[FILAS][COLUMNAS], int* contadorBlancas, int* contadorNegras);
void imprimirGanador(char ganador, Jugador jugador1, Jugador jugador2);
void escribirTableroEnArchivo(char tablero[FILAS][COLUMNAS], char* archivoIngresadoParaEscribir, char colorQueJuega);

#endif