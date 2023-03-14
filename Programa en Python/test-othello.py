from main import *
import io

# CASOS DE PRUEBA: Utilizamos el assert.

# io.StringIO es una clase de la biblioteca io de Python 
# que permite trabajar con flujos de texto en memoria como si fuera un objeto de archivo. 
# Se usa para representar el flujo de texto en memoria y leer o escribir datos en él como si fuera un archivo real.

def test_crearTablero():
    # CASO 1: El archivo ingresado representa al estado de tablero inicial.
    archivo = io.StringIO("XXXXXXXX\nXXXXXXXX\nXXXXXXXX\nXXXBNXXX\nXXXNBXXX\nXXXXXXXX\nXXXXXXXX\nXXXXXXXX\n")
    tableroEsperado = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'N', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]
    assert crearTablero(archivo) == tableroEsperado

    # ------------------------------------------------------------------------------------
    # CASO 2: El archivo ingresado representa un tablero de una partida inconclusa al azar.
    archivo = io.StringIO("XXXXXXXX\nXXXXXXXX\nXXXBBXXX\nXXNNNNXX\nXXXNBXXX\nXBBBXXXX\nXXXXXXXX\nXXXXXXXX\n")
    tableroEsperado = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'N', 'N', 'N', 'N', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'B', 'B', 'B', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]
    assert crearTablero(archivo) == tableroEsperado

    # --------------------------------------------------------------------------------
    # CASO 3: El archivo ingresado representa un tablero lleno de todas fichas blancas.
    archivo = io.StringIO("BBBBBBBB\nBBBBBBBB\nBBBBBBBB\nBBBBBBBB\nBBBBBBBB\nBBBBBBBB\nBBBBBBBB\nBBBBBBBB\n")
    tableroEsperado= [  
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B']
        ]
    assert crearTablero(archivo) == tableroEsperado

    # -------------------------------------------------------------------------------------------------
    # CASO 4: El archivo ingresado representa un tablero que está lleno pero con entradas intercaladas.
    archivo = io.StringIO("BNBNBNBN\nNBNBNBNB\nBNBNBNBN\nNBNBNBNB\nBNBNBNBN\nNBNBNBNB\nBNBNBNBN\nNBNBNBNB\n")
    tableroEsperado = [ 
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['N', 'B', 'N', 'B', 'N', 'B', 'N', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['N', 'B', 'N', 'B', 'N', 'B', 'N', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['N', 'B', 'N', 'B', 'N', 'B', 'N', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['N', 'B', 'N', 'B', 'N', 'B', 'N', 'B']
        ]
    assert crearTablero(archivo) == tableroEsperado
  
  
def test_perteneceAlTablero():
    # CASO 1: Preguntamos si las coordenadas (0,0) (que representan al casillero A1) pertenece al tablero.
    assert perteneceAlTablero(0,0) == True

    # CASO 2: Preguntamos si las coordenadas (5,6) (que representan al casillero G6) pertenece al tablero.
    assert perteneceAlTablero(5,6) == True

    # CASO 3: Preguntamos si las coordenadas (7,7) (que representan al casillero H8) pertenece al tablero.
    assert perteneceAlTablero(7,7) == True

    # CASO 4: Preguntamos si las coordenadas (8,0) pertenecen al tablero.
    assert perteneceAlTablero(8,0) == False

    # CASO 5: Preguntamos si las coordenadas (14,27) pertenecen al tablero.
    assert perteneceAlTablero(14,27) == False

    # CASO 6: Preguntamos si las coordenadas (-1,-1) pertenecen al tablero.
    assert perteneceAlTablero(-1,-1) == False


def test_obtenerTodasLasJugadasPosibles():
    # CASO 1: Jugadas posibles para las fichas blancas en el estado inicial del tablero.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'N', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]

    colorQueJuega = 'B'
    colorOpuesto = 'N'
    resultadoEsperado= {'53': {'43'}, '35': {'34'}, '24': {'34'}, '42': {'43'}}

    assert obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto) == resultadoEsperado

    # --------------------------------------------------------------------------------
    # CASO 2: Jugadas posibles para las fichas negras en el estado inicial del tablero.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'N', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]

    colorQueJuega = 'N'
    colorOpuesto = 'B'
    resultadoEsperado= {'32': {'33'}, '54': {'44'}, '23': {'33'}, '45': {'44'}}

    assert obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto) == resultadoEsperado

    # --------------------------------------------------------------------------------------------------------------------------------
    # CASO 3: Jugadas posibles para las fichas blancas en un tablero donde solo hay fichas blancas (aquí sería válido pasar el turno).
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]

    colorQueJuega = 'B'
    colorOpuesto = 'N'
    resultadoEsperado= {}

    assert obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto) == resultadoEsperado

    # ----------------------------------------------------------------------
    # CASO 4: Jugadas posibles para las fichas negras en un tablero al azar.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'N', 'N', 'N', 'N', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'B', 'B', 'B', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]

    colorQueJuega = 'N'
    colorOpuesto = 'B'
    resultadoEsperado= {'14': {'24', '23'}, '13': {'24', '23'}, '15': {'24'}, '55': {'44'}, '12': {'23'}, '54': {'44'}, '62': {'53', '44'}, '45': {'44'}, '61': {'52'}, '63': {'53'}}

    assert obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto) == resultadoEsperado

    # ----------------------------------------------------------------------------------------------------
    # CASO 5: Jugadas posibles para las fichas blancas, con una jugada que da vuelta varias fichas juntas.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'N', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'N', 'X', 'X'],
        ['X', 'X', 'N', 'N', 'N', 'N', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'B', 'B', 'B', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]

    colorQueJuega = 'B'
    colorOpuesto = 'N'
    resultadoEsperado= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}

    assert obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto) == resultadoEsperado


def test_formatearJugada():
    # CASO 1: Jugada dentro del tablero
    jugada= "C2"
    resultadoEsperado= '12'

    assert formatearJugada(jugada) == resultadoEsperado

    # ---------------------------------
    # CASO 2: Jugada dentro del tablero
    jugada= "H8"
    resultadoEsperado= '77'

    assert formatearJugada(jugada) == resultadoEsperado

    # ------------------------
    # CASO 3: Ingreso inválido
    jugada= "dsadasdasdasd"
    resultadoEsperado= ''

    assert formatearJugada(jugada) == resultadoEsperado

    # ------------------------
    # CASO 4: Ingreso inválido
    jugada= "99"
    resultadoEsperado= ''

    assert formatearJugada(jugada) == resultadoEsperado


def test_validarJugada():
    # CASO 1: Jugada válida ya que pertenece a todasLasJugadasPosibles: B5 corresponde a "41".
    jugada= "B5" 
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}
    assert validarJugada(jugada, todasLasJugadasPosibles) == True

    # ----------------------------------------------------------------------------------------
    # CASO 2: Jugada válida ya que pertenece a todasLasJugadasPosibles: G3 corresponde a "26".
    jugada= "G3"
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}
    assert validarJugada(jugada, todasLasJugadasPosibles) == True

    # ------------------------------------------------------------------------------------------
    # CASO 3: Jugada inválida por no pertenecer a todasLasJugadasPosibles. A1 corresponde a "00".
    jugada= "A1" #La jugada G3 corresponde a "26".
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}
    assert validarJugada(jugada, todasLasJugadasPosibles) == False

    # ---------------------------------------------------------------------------------------------
    # CASO 4: Jugada inválida por no pertenecer a todasLasJugadasPosibles NI pertenecer al tablero. 
    jugada= "Z7"
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}
    assert validarJugada(jugada, todasLasJugadasPosibles) == False

    # ------------------------------------------------------------------------------------
    # CASO 5: Jugada "pasar de turno" es válida ya que todasLasJugadasPosibles está vacío.
    jugada= ""
    todasLasJugadasPosibles= {}
    assert validarJugada(jugada, todasLasJugadasPosibles) == True

    # --------------------------------------------------------------------------------------------------------------------------------------
    # CASO 5: Jugada "pasar de turno" NO es válida ya que todasLasJugadasPosibles contiene elementos, es decir, jugadas posibles a realizar.
    jugada= ""
    todasLasJugadasPosibles= {'41': {'32'}}
    assert validarJugada(jugada, todasLasJugadasPosibles) == False


def test_formatearJugadaPC():
    # La jugada "41" representa a la posicion B5 del tablero.
    jugada= "41"
    resultadoEsperado= "B5"
    assert formatearJugadaPC(jugada) == resultadoEsperado

    # La jugada "26" representa a la posicion G3 del tablero.
    jugada= "26"
    resultadoEsperado= "G3"
    assert formatearJugadaPC(jugada) == resultadoEsperado


def test_evaluarMejorJugada():
    # La jugada "45" es la más efectiva: es la que da vuelta la mayor cantidad de fichas del color opuesto.
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34', '36', '24'}}
    resultadoEsperado= "45"
    assert evaluarMejorJugada(todasLasJugadasPosibles) == resultadoEsperado

    # La jugada "07" es la más efectiva: es la que da vuelta la mayor cantidad de fichas del color opuesto.
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35', '25'}, '42': {'33', '43'}, '46': {'35'}, '22': {'33'}, '07': {'34', '25', '43', '16'}}
    resultadoEsperado= "07"
    assert evaluarMejorJugada(todasLasJugadasPosibles) == resultadoEsperado

    # Como todas las jugadas son igual de efectivas, nos devuelve la primera del diccionario.
    todasLasJugadasPosibles= {'41': {'32'}, '45': {'34'}, '26': {'35'}, '42': {'33'}, '46': {'35'}, '22': {'33'}, '07': {'34'}}
    resultadoEsperado= "41"
    assert evaluarMejorJugada(todasLasJugadasPosibles) == resultadoEsperado


def test_evaluarPartidaEnCurso():
    # CASO 1: Tablero inicial.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'B', 'N', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]
    assert evaluarPartidaEnCurso(tablero) == True

    # ------------------------
    # CASO 2: Tablero al azar.
    tablero = [ 
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'N', 'X'],
        ['X', 'X', 'X', 'B', 'B', 'N', 'X', 'X'],
        ['X', 'X', 'N', 'N', 'N', 'N', 'X', 'X'],
        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
        ['X', 'B', 'B', 'B', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
        ]
    assert evaluarPartidaEnCurso(tablero) == True

    # -------------------------
    # CASO 3: Tablero completo.
    tablero = [ 
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'B']
        ]
    assert evaluarPartidaEnCurso(tablero) == False

    # -------------------------
    # CASO 4: Tablero incompleto pero a ningún jugador le quedan jugadas por realizar.
    tablero = [ 
        [' ', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'N', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'N', 'B', 'B'],
        ['B', 'B', 'B', 'N', 'B', 'N', 'B', 'B']
        ]
    assert evaluarPartidaEnCurso(tablero) == False


def test_determinarGanador():
    # CASO 1: Tablero lleno de fichas blancas
    tablero = [ 
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'],
        ['B', 'B', 'B', 'B', 'B', 'B', 'B', 'B']
        ]
    assert determinarGanador(tablero) == "B"

    # ---------------------------------------
    # CASO 2: Tablero lleno de fichas negras.
    tablero = [ 
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
        ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N']
        ]
    assert determinarGanador(tablero) == "N"

    # -------------------------
    # CASO 3: Tablero empatado.
    tablero = [ 
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N'],
        ['B', 'N', 'B', 'N', 'B', 'N', 'B', 'N']
        ]
    assert determinarGanador(tablero) == "X"


# Las funciones imprimirTablero(), ejecutarMovimiento(), juegaUsuario(), juegaPC(), jugar(), imprimirGanador() y funcionPrincipal() 
# no retornan nada, por lo tanto, se omiten sus casos de prueba.  
