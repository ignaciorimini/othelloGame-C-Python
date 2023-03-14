#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

// ARCHIVO DE CASOS DE PRUEBA 

void test_obtenerNombreColor(){
    // CASO 1: Le pasamos la línea de texto "Juan,R" y comparamos si en los campos de jugadorPrueba, nombre es igual a "Juan" y color a "R". 
    char linea1[] = "Juan,R";
    Jugador jugadorPrueba;
    obtenerNombreColorJugador(linea1, &jugadorPrueba);

    // strcmp() retorna 0 si las cadenas son iguales.
    assert(strcmp(jugadorPrueba.nombre, "Juan") == 0);
    assert(strcmp(jugadorPrueba.color, "R") == 0);

    // CASO 2: Le pasamos la línea de texto "Federico,N" y comparamos si en los campos de jugadorPrueba, nombre es igual a "Federico" y color a "N". 
    char linea2[] = "Federico,N";
    Jugador jugadorPrueba2;
    obtenerNombreColorJugador(linea2, &jugadorPrueba2);

    assert(strcmp(jugadorPrueba2.nombre, "Federico") == 0);
    assert(strcmp(jugadorPrueba2.color, "N") == 0);

    // CASO 3: Le pasamos la línea de texto "Alejandro,blanco" y comparamos si en los campos de jugadorPrueba, nombre es igual a "Alejandro" y color a "blanco". 
    char linea3[] = "Alejandro,blanco";
    Jugador jugadorPrueba3;
    obtenerNombreColorJugador(linea3, &jugadorPrueba3);

    assert(strcmp(jugadorPrueba3.nombre, "Alejandro") == 0);
    assert(strcmp(jugadorPrueba3.color, "blanco") == 0);
}


void test_perteneceAlTablero(){
    // CASO 1: Preguntamos si las coordenadas (0,0) (que representan al casillero A1) pertenece al tablero.
    assert(perteneceAlTablero(0,0) == 1);

    // CASO 2: Preguntamos si las coordenadas (5,6) (que representan al casillero G6) pertenece al tablero.
    assert(perteneceAlTablero(5,6) == 1);

    // CASO 3: Preguntamos si las coordenadas (7,7) (que representan al casillero H8) pertenece al tablero.
    assert(perteneceAlTablero(7,7) == 1);

    // CASO 4: Preguntamos si las coordenadas (8,0) pertenecen al tablero.
    assert(perteneceAlTablero(8,0) == 0);

    //CASO 5: Preguntamos si las coordenadas (14,27) pertenecen al tablero.
    assert(perteneceAlTablero(14,27) == 0);

    //CASO 6: Preguntamos si las coordenadas (-1,-1) pertenecen al tablero.
    assert(perteneceAlTablero(-1,-1) == 0);
}


void test_formatearJugadaPotencial(){
    // CASO 1: Comparamos si la jugada A3 se corresponde con la posición [2][0] del tablero.
    char jugada[] = "A3";
    formatearJugadaPotencial(jugada);
    assert(strcmp(jugada, "20") == 0);

    //CASO 2: Comparamos si la jugada C2 se corresponde con la posición [1][2] del tablero.
    char jugada2[]= "C2";
    formatearJugadaPotencial(jugada2);
    assert(strcmp(jugada2, "12") == 0);

    // CASO 3: Comparamos si la jugada H8 se corresponde con la posición [7][7] del tablero.
    char jugada3[]= "H8";
    formatearJugadaPotencial(jugada3);
    assert(strcmp(jugada3, "77") == 0);
}


void test_crearArrayConJugadasPosibles(){
    int posicion = 0;
    char** posicionesValidas = NULL;

    // CASO 1: Le pasamos el valor de fila=1 y columna=1 y comparamos que en la posicion 0 del array posicionesValidas se hayan agregado las coordenadas "11".
    crearArrayConJugadasPosibles(1, 1, &posicion, &posicionesValidas);
    assert(strcmp(posicionesValidas[0], "11") == 0);

    // CASO 2: Le pasamos el valor de fila=5 y columna=7 y comparamos que en la posicion 1 del array posicionesValidas se hayan agregado las coordenadas "57".
    crearArrayConJugadasPosibles(5, 7, &posicion, &posicionesValidas);
    assert(strcmp(posicionesValidas[1], "57") == 0);

    // CASO 3: Le pasamos el valor de fila=3 y columna=2 y comparamos que en la posicion 2 del array posicionesValidas se hayan agregado las coordenadas "32".
    crearArrayConJugadasPosibles(3, 2, &posicion, &posicionesValidas);
    assert(strcmp(posicionesValidas[2], "32") == 0);

    // Liberamos la memoria del array posicionesValidas.
    liberarPosicionesValidas(posicionesValidas, posicion);
}


void test_obtenerTodasLasJugadasPosibles(){
    // CASO 1: Jugadas posibles para las fichas blancas en el estado inicial del tablero.
    char tablero[FILAS][COLUMNAS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', 'N', ' ', ' ', ' '},
        {' ', ' ', ' ', 'N', 'B', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    char colorQueJuega = 'B';
    char colorOpuesto = 'N';
    char** posicionesValidas= NULL;
    
    int cantidadPosiciones = obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto, &posicionesValidas);
    char *jugadasEsperadas[] = {"35", "53", "24", "42"};

    for (int i = 0; i < cantidadPosiciones; i++) {
        assert(strcmp(posicionesValidas[i], jugadasEsperadas[i]) == 0);
    }

    // Liberamos la memoria del array posicionesValidas.
    liberarPosicionesValidas(posicionesValidas, cantidadPosiciones);

    // --------------------------------------------------------------------------------
    // CASO 2: Jugadas posibles para las fichas negras en el estado inicial del tablero.
    char tablero2[FILAS][COLUMNAS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', 'N', ' ', ' ', ' '},
        {' ', ' ', ' ', 'N', 'B', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    char colorQueJuega2 = 'N';
    char colorOpuesto2 = 'B';
    char** posicionesValidas2= NULL;
    
    int cantidadPosiciones2 = obtenerTodasLasJugadasPosibles(tablero2, colorQueJuega2, colorOpuesto2, &posicionesValidas2);
    char *jugadasEsperadas2[] = {"32", "54", "23", "45"};

    for (int i = 0; i < cantidadPosiciones2; i++) {
        assert(strcmp(posicionesValidas2[i], jugadasEsperadas2[i]) == 0);
    }

    liberarPosicionesValidas(posicionesValidas2, cantidadPosiciones2);

    // --------------------------------------------------------------------------------
    // CASO 3: Jugadas posibles para las fichas blancas en un tablero donde solo hay fichas blancas (aquí sería válido pasar el turno).
    char tablero3[FILAS][COLUMNAS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', 'B', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', 'B', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    char colorQueJuega3 = 'B';
    char colorOpuesto3 = 'N';
    char** posicionesValidas3= NULL;
    
    int cantidadPosiciones3 = obtenerTodasLasJugadasPosibles(tablero3, colorQueJuega3, colorOpuesto3, &posicionesValidas3);
    char *jugadasEsperadas3[] = {};

    // Como la lista es vacía, cantidadPosiciones3= 0, por lo tanto nunca se entra en el siguiente bucle.
    for (int i = 0; i < cantidadPosiciones3; i++) {
        assert(strcmp(posicionesValidas3[i], jugadasEsperadas3[i]) == 0);
    }

    liberarPosicionesValidas(posicionesValidas3, cantidadPosiciones3);

    // ----------------------------------------------------------------------
    // CASO 4: Jugadas posibles para las fichas negras en un tablero al azar.
    char tablero4[FILAS][COLUMNAS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', 'B', ' ', ' ', ' '},
        {' ', ' ', 'N', 'N', 'N', 'N', ' ', ' '},
        {' ', ' ', ' ', 'N', 'B', ' ', ' ', ' '},
        {' ', 'B', 'B', 'B', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    char colorQueJuega4 = 'N';
    char colorOpuesto4 = 'B';
    char** posicionesValidas4= NULL;
    
    int cantidadPosiciones4 = obtenerTodasLasJugadasPosibles(tablero4, colorQueJuega4, colorOpuesto4, &posicionesValidas4);

    // Al ser una lista y no un conjunto, hay algunas jugadas repetidas. Esto no cambia nada dentro del programa, ya que no utilizamos la cantidad de jugadas posibles
    // sino que comparamos las jugadas leídas con algunos de los elementos de esta lista.
    char *jugadasEsperadas4[] = {"14", "13", "15", "55", "12", "14", "54", "13", "62", "45", "61", "63"};

    for (int i = 0; i < cantidadPosiciones4; i++) {
        assert(strcmp(posicionesValidas4[i], jugadasEsperadas4[i]) == 0);
    }

    liberarPosicionesValidas(posicionesValidas4, cantidadPosiciones4);
}


void test_evaluarJugada(){
    // Creamos un array con algunas jugadas válidas.
    char* posicionesValidas[] = {"A1", "B2", "C3"};

    // CASO 1: Evaluación de una jugada válida.
    char jugadaValida[] = "A1";
    assert(evaluarJugada(jugadaValida, 3, posicionesValidas) == 1);

    // CASO 2: Evaluación de una jugada inválida.
    char jugadaInvalida[] = "D4";
    assert(evaluarJugada(jugadaInvalida, 3, posicionesValidas) == 0);

    // CASO 3: Evaluación del salto de línea en una lista vacía: jugada válida.
    char jugadaPasar[] = "\n";
    char* posicionesValidas2[] = {};
    jugadaPasar[0]= '\0';
    assert(evaluarJugada(jugadaPasar, 0, posicionesValidas2) == 1);
}


void test_ejecutarMovimiento(){
    // Estado inicial del tablero.
    char tablero[FILAS][COLUMNAS] = {{' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ','B','N',' ',' ',' '},
                                     {' ',' ',' ','N','B',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' '},
                                     {' ',' ',' ',' ',' ',' ',' ',' '}};

    // CASO 1: Juegan las blancas y ejecutan el movimiento F4 = "35".
    char* jugada = "35";
    char colorQueJuega = 'B';
    char colorOpuesto = 'N';

    ejecutarMovimiento(tablero, jugada, colorQueJuega, colorOpuesto);

    // Una vez ejecuta la jugada verificamos que haya fichas blancas en F4 y en E4.
    assert(tablero[3][4] == 'B');
    assert(tablero[3][5] == 'B');

    // -------------------------------------------------------------
    // CASO 2: Juegan las negras y ejecutan el movimiento D3 = "23".
    char* jugada2 = "23";
    colorQueJuega = 'N';
    colorOpuesto = 'B';

    ejecutarMovimiento(tablero, jugada2, colorQueJuega, colorOpuesto);

    // Una vez ejecuta la jugada verificamos que haya fichas blancas en D3 y en D4.
    assert(tablero[2][3] == 'N');
    assert(tablero[3][3] == 'N');

    // --------------------------------------------------------------
    // CASO 3: Juegan las blancas y ejecutan el movimiento C4 = "32".
    char *jugada3 = "32";
    colorQueJuega = 'B';
    colorOpuesto = 'N';

    ejecutarMovimiento(tablero, jugada3, colorQueJuega, colorOpuesto);

    // Una vez ejecuta la jugada verificamos que haya fichas blancas en C4 y en D4.
    assert(tablero[3][2] == 'B');
    assert(tablero[3][3] == 'B');
}


void test_evaluarPartidaTerminada() {
    // CASO 1: Tablero inicial.
    char tablero[FILAS][COLUMNAS] = {
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','B','N',' ',' ',' '},
        {' ',' ',' ','N','B',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '}
    };

    int resultado = evaluarPartidaTerminada(tablero);
    assert(resultado == 0);

    // ------------------------
    // CASO 2: Tablero al azar.
    char tablero2[FILAS][COLUMNAS] = {
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ','N',' '},
        {' ',' ',' ','B','B','N',' ',' '},
        {' ',' ','N','N','N','N',' ',' '},
        {' ',' ',' ','N','B',' ',' ',' '},
        {' ','B','B','B',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '}
    };
    int resultado2 = evaluarPartidaTerminada(tablero2);
    assert(resultado2 == 0);

    // -------------------------
    // CASO 3: Tablero completo.
    char tablero3[FILAS][COLUMNAS] = {
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'}
    };
    int resultado3 = evaluarPartidaTerminada(tablero3);
    assert(resultado3 == 1);

    // --------------------------------------------------------------------------------
    // CASO 4: Tablero incompleto pero a ningún jugador le quedan jugadas por realizar.
    char tablero4[FILAS][COLUMNAS] = {
        {' ','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','N','B','N','B','N'},
        {'B','B','B','B','B','N','B','N'},
        {'B','B','B','N','B','N','B','N'},
        {'B','B','B','N','B','B','B','N'},
        {'B','B','B','N','B','N','B','N'},
        {'B','B','B','N','B','N','B','B'}
    };
    int resultado4 = evaluarPartidaTerminada(tablero4);
    assert(resultado4 == 1);
}


void test_determinarGanador(){
    int contadorBlancas= 0;
    int contadorNegras= 0;

    // CASO 1: Tablero lleno de fichas blancas.
    char tablero[FILAS][COLUMNAS] = {
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'},
        {'B','B','B','B','B','B','B','B'}
    };

    char resultado = determinarGanador(tablero, &contadorBlancas, &contadorNegras);
    assert(resultado == 'B');


    // ---------------------------------------
    // CASO 2: Tablero lleno de fichas negras.
    contadorBlancas= 0;
    contadorNegras= 0;

    char tablero2[FILAS][COLUMNAS] = {
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'},
        {'N','N','N','N','N','N','N','N'}
    };

    char resultado2 = determinarGanador(tablero2, &contadorBlancas, &contadorNegras);
    assert(resultado2 == 'N');


    // -------------------------
    // CASO 3: Tablero empatado.
    contadorBlancas= 0;
    contadorNegras= 0;

    char tablero3[FILAS][COLUMNAS] = {
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'},
        {'B','N','B','N','B','N','B','N'}
    };

    char resultado3 = determinarGanador(tablero3, &contadorBlancas, &contadorNegras);
    assert(resultado3 == 'X');
}


// Las funciones crearTablero(), liberarPosicionesValidas(), formatearJugadaIngresada() leerJugadas(), imprimirTablero(), imprimirGanador(), escribirTableroEnArchivo()
// no retornan nada, por lo tanto, se omiten sus casos de prueba. 