# OTHELLO: Programa en Python

# Representaremos el tablero de juego en forma de matriz 8x8 como una lista de 8 listas de 8 caracteres: List[List[String]].
# Gráficamente:
# tablero= [ 
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'B', 'N', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'N', 'B', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
#        ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']
#        ]

# Sus valores se identifican con la pieza que se encuentra en cada posición. Estos valores pueden ser: 
#   1. El string ("X") correspondiente a una posición libre.
#   2. El string ("B") correspondiente a una pieza de color blanco.
#   3. El string ("N") correspondiente a una pieza de color negro.

# ---------------------
# Librerías a utilizar:
import sys      # Librería para que el usuario ingrese los argumentos del programa a la hora de ejecutarlo. 
import random   # Librería para elegir una jugada al azar, correspondiente a la funcionalidad del programa en el nivel 0.

# ------------------------
# Definición de funciones:


# funcionPrincipal(): None -> None

# Esta función que no recibe argumentos ni retorna nada es la encargada de llevar el flujo del programa.

def funcionPrincipal():

    # Utilizando la librería sys, le permitimos al usuario ingresar los argumentos del programa a la hora de ejecutarlo.
    # De esta manera, si el usuario escribe en consola el siguiente comando: main.py escritura.txt N 1
    #   - sys.argv[1] coincide con el archivo que lee el programa, en este caso "escritura.txt".
    #   - sys.argv[2] coincide con el color que utilizará el jugador, en este caso "N".
    #   - sys.argv[3] coincide con el nivel de dificultad deseado, en este caso "1".

    # Si no se han ingresado los argumentos correspondientes se termina el programa.
    if len(sys.argv) != 4:
        print("Faltan argumentos. Vuelva a ejecutar el programa.")
        return

    # Intentamos abrir el archivo que ingresó el usuario en consola: si la direccion es inválida termina la ejecución.
    try:
        archivoJugadas= open(sys.argv[1])
    except:
        print("La dirección ingresada no es válida. Vuelva a ejecutar el programa.")
        return
    
    # Verificamos que el usuario haya ingresado un color válido (N o B), de lo contrario termina la ejecución.
    colorJugador= sys.argv[2].upper()
    if colorJugador != "B" and colorJugador != "N":
        print("Color inválido. Vuelva a ejecutar el programa.")
        return
    
    # Verificamos que el nivel ingresado sea válido (0 o 1), sino termina la ejecución.
    nivel= sys.argv[3]
    if nivel != "0" and nivel != "1":
        print("Nivel inválido. Vuelva a ejecutar el programa.")
        return

    # Creamos el tablero llamando a crearTablero y pasandóle como argumento el archivo que ingresó el usuario en consola.
    tablero= crearTablero(archivoJugadas)

    # Imprimimos el estado actual del tablero: el resultante luego de haber leído el archivo.
    imprimirTablero(tablero)

    # Leemos el color que juega ahora mismo, también del archivo que se ingresó.
    colorQueJuega= archivoJugadas.readline()

    # Ya habiendo leído el tablero y el color, no se volverá a ingresar al archivo. Por ello, lo cerramos.
    archivoJugadas.close()

    # Determinamos el color opuesto a partir del color que juega actualmente.
    colorOpuesto="N" if colorQueJuega=="B" else "B"
    
    # Bucle que se ejecutará mientras la partida esté en curso. El bucle termina su ejecución cuando la partida termina.
    # Mientras esté en ejecución el bucle, se seguirán evaluando jugadas.
    partidaEnCurso= True
    while partidaEnCurso:

        # Llamamos a la función que se encarga de llevar a cabo el juego.
        jugar(tablero, colorQueJuega, colorJugador, colorOpuesto, nivel)

        # Cambiamos el color que juega: el siguiente turno pertenece al otro color.
        colorOpuesto= colorQueJuega
        colorQueJuega="N" if colorOpuesto=="B" else "B"

        # Verificamos si la partida sigue en curso.
        partidaEnCurso= evaluarPartidaEnCurso(tablero)
    
    # Una vez que termina el bucle, imprimimos un mensaje de partida finalizada y determinamos el ganador de la misma.
    print("Partida terminada.")
    ganador= determinarGanador(tablero)
    imprimirGanador(ganador, colorJugador)


# -------------------------------------------------
# crearTablero(): Object File -> List[List[String]]

# Esta función recibe como argumento un archivo y retorna una matriz 8x8 (tablero de juego).
# Para ello, se leen una a una las primeras 8 lineas del archivo y por cada una de ellas se toman los 8 caracteres 
# correspondientes a cada fila del tablero para así agregarlos a una lista temporal llamada "fila". 
# Después, se agrega "fila" a la lista "tablero" que al finalizar los 8 elementos 
# será una lista de 8 listas de 8 caracteres cada una, representando así el tablero de juego.

def crearTablero(archivo):
    fila=[]
    tablero=[]

    # Bucle que recorre las 8 líneas del archivo correspondientes al estado del tablero.
    for elemento in range(8):
        linea= archivo.readline() 
        for i in range(8):
            fila.append(linea[i])
        tablero.append(fila)
        fila=[]
    
    return tablero


# ---------------------------------------------
# imprimirTablero(): List[List[String]] -> None

# Esta función recibe una matriz 8x8 (tablero de juego) como argumento y se encarga de imprimirla de forma legible. 
# Primero, imprime una línea con las letras A a H para identificar las columnas. 
# Luego, por cada fila del tablero, construye una cadena de caracteres "cadenaTablero" que representa los valores de esa fila, 
# separados por el carácter "|". Si algún valor en el tablero es igual a "X", se imprime un espacio vacío en su lugar.

def imprimirTablero(tablero):
    print("Estado del tablero:")
    print("  " + "A" + " " + "B" + " " + "C" + " " + "D" + " " + "E" + " " + "F" + " " + "G" + " " + "H") 

    contador=0
    for fila in range(8):
        cadenaTablero=""
        contador+=1

        for columna in range(8):
            if tablero[fila][columna] == "X":
                cadenaTablero+= " |"
            else:
                cadenaTablero+= tablero[fila][columna] + "|"

        print(str(contador)+ "|" +cadenaTablero)


# ----------------------------------------------------------------
# jugar(): List[List[String]], String, String, String, Int -> None

# Esta función se ejecutará siempre que la partida esté en curso. No retorna nada, solamente se encarga de alternar en la llamada a funciones dependiendo
# quien juega en este turno: si es el turno del usuario llama a la función juegaUsuario(); caso contrario llama a la función juegaPC().
# Finalmente imprime el tablero resultante luego de ejecutarse una jugada.

def jugar(tablero, colorQueJuega, colorJugador, colorOpuesto, nivel):

    if colorJugador == colorQueJuega:
        juegaUsuario(tablero, colorQueJuega, colorOpuesto)
    else:
        juegaPC(tablero, colorQueJuega, colorOpuesto, nivel)

    imprimirTablero(tablero)


# ----------------------------------------------------------
# juegaUsuario(): List[List[String]], String, String -> None

# Esta función que recibe un tablero, el color que juega y el color opuesto, cumple con la funcionalidad de pedirle jugadas al usuario.
# En caso de que las jugadas válidas sean correctas, llama a la función ejecutarMovimiento() para actualizar el estado del tablero.
# De lo contrario, se volverá a pedir al usuario que ingrese una jugada, así hasta que ingrese una jugada válida.
# Esta función no tiene ningún retorno, se encarga nada más de gestionar el turno del usuario.

def juegaUsuario(tablero, colorQueJuega, colorOpuesto):
    jugadaInvalida= True

    while jugadaInvalida:
        jugada= input("Ingresá tu jugada: ").upper()

        # Llamamos a la función que obtiene todas las jugadas posibles para el color que juega, en el estado actual del tablero.
        todasLasJugadasPosibles= obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto)

        # Validamos si la jugada ingresada por teclado por el usuario es válida.
        if validarJugada(jugada, todasLasJugadasPosibles):

            # Si la jugada es válida y no es una cadena vacía, se llama a la función "ejecutarMovimiento" para ejecutar el movimiento y actualizar el tablero. 
            if jugada != "":
                ejecutarMovimiento(tablero, formatearJugada(jugada), todasLasJugadasPosibles, colorQueJuega)
            
            # Finalmente, se establece "jugadaInvalida" en False para detener el bucle y finalizar la ronda de juego.
            jugadaInvalida= False

        # Si la jugada no es válida, se imprime un mensaje indicando que la jugada es inválida y el bucle continúa hasta que el usuario ingrese una jugada válida.
        else:
            print("Jugada inválida.")


# ----------------------------------------------------------
# juegaPC(): List[List[String]], String, String, Int -> None

# Esta función que recibe un tablero, el color que juega, el color opuesto y el nivel de dificultad, se encarga de manejar el turno de juego de la PC.
# Para ello, obtiene todas las jugadas posibles para el color que juega y, dependiendo el nivel de dificultad, elige una jugada al azar o elige
# la jugada más efectiva. Una vez escogida la jugada, la ejecuta llamando a la función ejecutarMovimiento().
# En caso de no haber ninguna jugada posible, se pasaría de turno.
# Esta función no tiene ningún retorno, se encarga nada más de gestionar el turno de la PC.

def juegaPC(tablero, colorQueJuega, colorOpuesto, nivel):

    input("PC pensando jugada... Presiona ENTER para ver su movimiento.")

    # Llamamos a la función que obtiene todas las jugadas posibles para el color que juega, en el estado actual del tablero.
    todasLasJugadasPosibles= obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto)

    # Verificamos si hay jugadas posibles a realizar.
    if todasLasJugadasPosibles != {}:

        # Verificamos el nivel de dificultad. Si es 0, la PC elige una jugada al azar entre las jugadas posibles.
        if nivel==0:
            listaJugadas= list(todasLasJugadasPosibles.keys())
            
            # Usando el método random, obtenemos una jugada al azar.
            jugada= random.choice(listaJugadas)

        # Si la dificultad es 1, la PC elige la mejor jugada utilizando la función evaluarMejorJugada().
        else:
            jugada= evaluarMejorJugada(todasLasJugadasPosibles)

        # Ejecutamos el movimiento e imprimimos en consola la jugada realizada.
        print("Jugada realizada por la PC: " + formatearJugadaPC(jugada) + ".")
        ejecutarMovimiento(tablero, jugada, todasLasJugadasPosibles, colorQueJuega)
    
    # Si no hay jugadas posibles, la función imprime un mensaje indicando que se ha pasado de turno.
    else:
        print("Jugada realizada por la PC: pasar de turno")


# -----------------------------------
# formatearJugada(): String -> String

# Esta función recibe como argumento un String llamado "jugada", y crea una nueva forma de representación de la misma, 
# siempre y cuando "jugada" cumpla con los siguientes requisitos:
#   - Tenga 2 caracteres.
#   - El primer caracter es una letra entre la A y la H.
#   - El segundo caracter es un número comprendido entre 1 y 8.

# Si "jugada" cumple con estos requisitos, retornaremos la versión formateada de la misma de la siguiente forma:
#   1) La primera parte de la nueva forma de representación es un número obtenido restando 1 al segundo carácter de jugada. 
#   2) La segunda parte es el índice en la lista letras (que contiene las letras A a H) de la primera letra de jugada.

# De esta forma, la jugada "C5" quedaría representada como "42".
# Donde C que es una coordenada vertical (columna) queda representada por el 2.
# Y donde 5 que es una coordenada horizontal (fila) queda representada por el 4.

def formatearJugada(jugada):
    letras= "ABCDEFGH"
    jugadaNueva= ""
    
    if len(jugada) == 2 and jugada[0].isalpha() and jugada[1].isdigit():

        if int(jugada[1]) in range(1,9):

            # Restamos 1 al segundo caracter de la jugada ingresada.
            jugadaNueva+= str(int(jugada[1])-1)

            # Le asignamos un número a la letra de la jugada ingresada: A=0, B=1, etc.
            for i in range(8):
                if letras[i] == jugada[0]:
                    jugadaNueva+= str(i)

    return jugadaNueva


# -------------------------------------
# formatearJugadaPC(): String -> String

# Esta función es la inversa de la función formatearJugada(). Su funcionalidad es retornar una nueva representación de "jugada":
# pasar de la forma "42" de jugada a una representación que contenga letra y número, para que el usuario sepa la jugada que ha realizado la PC. 
# Ej: "42" es "C5".

def formatearJugadaPC(jugada):
    letras= "ABCDEFGH"
    jugadaNueva= ""

    # Como el segundo caracter de "jugada" representa a las columnas, le asignamos la letra correspondiente a dicho número.
    # A es 0, B es 1, etc. 
    for i in range(8):
        if int(jugada[1]) == i:
            jugadaNueva+= letras[i]

    # Como jugada usaba un rango entre 0 y 7 para representar a las filas, y el tablero visual maneja un rango entre 1 y 8, le debemos sumar
    # una unidad al caracter de "jugada" que representa las filas.
    jugadaNueva+= str( int(jugada[0]) + 1 )

    return jugadaNueva


# -------------------------------------------------------------------------------------------------
# obtenerTodasLasJugadasPosibles(): List[List[String]], String, String -> Dict{String: Set{String}}

# La función recibe 3 argumentos:
#   - tablero: Una matriz de 8x8 de tipo List[List[String]], que representa el tablero del juego.
#   - colorQueJuega: Una cadena de caracteres de tipo String, que representa el color que está jugando.
#   - colorOpuesto: Una cadena de caracteres de tipo String, que representa el color opuesto al que está jugando.

# La función retorna un diccionario de tipo Dict{String: Set{String}}, donde las claves son las coordenadas de las posiciones válidas para el color que juega,
# y los valores son conjuntos de coordenadas donde se encuentran fichas del color opuesto, y que se darán vuelta si se juega en esa posición.

def obtenerTodasLasJugadasPosibles(tablero, colorQueJuega, colorOpuesto):
    # Estas listas (direccionHorizontal y direccionVertical) representan las ocho direcciones posibles en las que se puede mover en el tablero.

    # Explicado gráficamente: el primer número equivale al movimiento horizontal y el segundo al vertical.
    # Si "B" está en la posicion tablero[4][5] -> (-1 -1) equivale a tablero[3][4]
    # -1 -1 | 0 -1 | 1 -1
    # -1 0  |  B   | 1 0
    # -1 1  | 0 1  | 1 1
    direccionHorizontal= [-1, -1, -1, 0, 0, 1, 1, 1]
    direccionVertical= [-1, 0, 1, -1, 1, -1, 0, 1]

    diccionarioJugadasValidas= {}

    # Bucle que recorre las filas.
    for i in range(8):

        # Bucle que recorre las columnas.
        for j in range(8):

            # Preguntamos si se encuentra una ficha del color que está jugando.
            if tablero[i][j] == colorQueJuega:

                # Si se encontró una ficha del color que está jugando, iteramos 8 veces (8 posibles posiciones), para analizar el estado del tablero en las posiciones
                # aledañas a donde se encontró nuestra ficha.

                # Gráficamente:
                # X | X | X
                # X | B | X
                # X | X | N
                # Debemos analizar qué se encuentra alrededor de la ficha "B", para determinar si hay posibles jugadas a realizar.

                for r in range(8):
                    fichasADarVuelta= set() #Conjunto donde se guardarán las fichas a dar vuelta.

                    # filaAlrededor y columnaAlrededor serán las coordenadas aledañas a la posición donde se encuentra una ficha del color que está jugando.
                    # Hacemos uso de direccionHorizontal y direccionVertical nuevamente, para ir rodeando las coordenadas de nuestra ficha.
                    filaAlrededor= i + direccionHorizontal[r]
                    columnaAlrededor= j + direccionVertical[r]

                    # En esta sentencia, verificamos que las coordenadas que estamos analizando pertenezcan al tablero.
                    estaEnTablero= perteneceAlTablero(filaAlrededor, columnaAlrededor)

                    # Preguntamos si encontramos una ficha del color opuesto, significando una posible jugada a realizar.
                    if estaEnTablero and tablero[filaAlrededor][columnaAlrededor]== colorOpuesto:

                        # Si es qué encontramos una ficha del color opuesto, entramos en un bucle, utilizando la misma dirección (mismos valores de filaAlrededor y
                        # columnaAlrededor) para determinar, si la jugada llegase a ser válida, cuántas fichas opuestas tendremos que dar vuelta.
                        condicion= True
                        while condicion:

                            # A medida que vamos iterando, agregamos las fichas del color opuesto en el conjunto fichasADarVuelta.
                            # Si la jugada termina siendo válida, los elementos de este conjunto serán las fichas del color opuesto
                            # que tendremos que dar vuelta.
                            fichasADarVuelta.add(str(str(filaAlrededor)+str(columnaAlrededor)))

                            filaAlrededor+= direccionHorizontal[r]
                            columnaAlrededor+= direccionVertical[r]

                            # Si nos salimos del tablero, la jugada que estamos analizando se convierte en inválida.
                            if not perteneceAlTablero(filaAlrededor, columnaAlrededor):
                                condicion= False
                            else:
                                # Verificamos qué, siguiendo en la misma dirección en que encontramos una ficha del color opuesto,
                                # haya un lugar vacío (espacio del tablero con una "X"), significando que podemos colocar allí una ficha
                                # del color que está jugando.
                                if tablero[filaAlrededor][columnaAlrededor] == 'X':
                                    jugadaValida= str(str(filaAlrededor)+str(columnaAlrededor))

                                    # diccionarioJugadasValidas es un diccionario cuyas claves son las jugadas posibles a realizar
                                    # y sus valores son las fichas que se voltearán en caso de ejecutar la jugada almacenada en la clave.

                                    # Gráficamente: diccionarioJugadasValidas= {"41": {"12", "24"}}
                                    # El diccionario anterior nos muestra que la jugada "41" es válida, y en caso de ejecutarse dará vuelta
                                    # las posiciones "12" y "24".

                                    # En esta instancia las jugadas se expresan como un String de dos números, donde el primero específica la
                                    # fila y el segundo la columna del tablero en la que nos estamos ubicando.
                                    # Siendo que los índices de las listas arrancan en 0, la jugada "41" = tablero[4][1] equivale a la quinta fila
                                    # del tablero en la segunda posición, es decir, B5.

                                    # En la siguiente sentencia, creamos un diccionario vacío si es la primera vez que evaluamos una jugada, es decir,
                                    # si todavía no sabemos por lo menos una posición de una ficha a dar vuelta.
                                    if jugadaValida not in diccionarioJugadasValidas:
                                        diccionarioJugadasValidas[jugadaValida]= set()

                                    # Si ya hemos evaluado una posible posición y sabemos que da vuelta fichas en una dirección particular,
                                    # pero también da vuelta fichas en una dirección distinta, lo que hacemos en la siguiente línea es UNIR
                                    # los elementos del conjunto fichasADarVuelta a lo que ya había almacenado en diccionarioJugadasValidas[jugadaValida].
                                    # De este modo, no estaremos sobreescribiendo las fichas que se voltearían en una dirección distinta a la que se esta
                                    # evaluando en esta iteración.

                                    # Gráficamente:
                                    # X | X | (X) -> jugada válida
                                    # X | N | X
                                    # B | N | (X) -> jugada válida 
                                    # Como vemos, la ficha "B" da vuelta una ficha en la dirección horizontal hacia la derecha, y también
                                    # da vuelta una ficha en una dirección oblicua hacia arriba a la derecha.
                                    diccionarioJugadasValidas[jugadaValida]= diccionarioJugadasValidas[jugadaValida] | fichasADarVuelta
                                
                                # Si evaluando una dirección particular, llegamos a que en una posición no hay una ficha del color opuesto,
                                # saldremos del bucle while (condicion= False). 

                                # Por lo tanto, el bucle se ejecutará utilizando una misma dirección (mismos valores de direccionHorizontal y direccionVertical), 
                                # siempre y cuando las coordenadas evaluadas no se salgan del tablero, y siempre que en dichas coordenadas haya una ficha del color opuesto.
                                if tablero[filaAlrededor][columnaAlrededor] != colorOpuesto:
                                    condicion= False

    return diccionarioJugadasValidas


# -----------------------------------------
# perteneceAlTablero(): Int, Int -> Boolean

# Esta función determina si un par de coordenadas (posiciónX, posiciónY), representadas por números enteros,
# está dentro de los límites del tablero de juego (8x8). 
# Si ambas coordenadas son mayores o iguales a cero y menores a 8, la función devuelve True, 
# lo que significa que las coordenadas pertenecen al tablero. 
# Si alguna de las coordenadas es menor a cero o mayor o igual a 8, la función devuelve False, 
# lo que significa que las coordenadas no pertenecen al tablero.

def perteneceAlTablero(posicionX, posicionY):
    if posicionX >= 0 and posicionX < 8 and posicionY >= 0 and posicionY < 8:
        return True
    else:
        return False


# -------------------------------------------------------------
# validarJugada(): String, Dict{String: Set{String}} -> Boolean

# Esta función que verifica si una jugada es válida, recibe una cadena de caracteres "jugada" y un diccionario "todasLasJugadasPosibles". 
# Si la "jugada" no es el salto de línea y la "jugadaFormateada" se encuentra en las claves del diccionario, la función retorna True, indicando que la "jugada" es válida. 
# Si la "jugada" es vacía y el diccionario "todasLasJugadasPosibles" está vacío, la función también retorna True, ya que no hay jugadas posibles en este caso. 
# En cualquier otro caso, la función retorna False, indicando que la "jugada" no es válida.

def validarJugada(jugada, todasLasJugadasPosibles):

    if jugada!="":
        jugadaFormateada= formatearJugada(jugada)

        if jugadaFormateada in todasLasJugadasPosibles.keys():
            return True
        else:
            return False

    else:

        if todasLasJugadasPosibles == {}:
            return True
        else:
            return False


# -------------------------------------------------------------------------------------------
# ejecutarMovimiento(): List[List[String]], String, Dict{String: Set{String}}, String -> None

# Esta función recibe el estado actual del tablero, la jugada ya formateada, el diccionario de todas las jugadas posibles y el color que juega.
# Su funcionalidad es voltear las fichas que da vuelta "jugada". Para eso coloca una ficha del "colorQueJuega" en la posición que representa "jugada", y
# voltea las fichas almacenadas en "todasLasJugadasPosibles[jugada]", ya que en "todasLasJugadasPosibles" se indica la jugada seguida de las posiciones
# que da vuelta. Como esta función solo modifica el estado de la variable "tablero", no retorna ningún valor.

def ejecutarMovimiento(tablero, jugada, todasLasJugadasPosibles, colorQueJuega):
    # fichasADarVuelta es un conjunto de las posiciones que voltea "jugada".
    fichasDarVuelta= todasLasJugadasPosibles[jugada]

    # Colocamos una ficha de "colorQueJuega" en la posición que representa "jugada".
    posicionX= int(jugada[0])
    posicionY= int(jugada[1])
    tablero[posicionX][posicionY]=  colorQueJuega

    # Bucle que "voltea" el color de las posiciones almacenadas en el conjunto fichasADarVuelta.
    for elemento in fichasDarVuelta:
        posicionX= int(elemento[0])
        posicionY= int(elemento[1])

        tablero[posicionX][posicionY]= colorQueJuega


# ---------------------------------------------------------
# evaluarMejorJugada(): Dict{String: Set{String}} -> String

# Esta función evalúa la mejor jugada dentro del diccionario "todasLasJugadasPosibles" al recorrer cada clave y valor y mantener un registro
# de la clave que representa la jugada con la mayor cantidad de fichas que darían vuelta. 
# Finalmente, la función devuelve la clave que representa la mejor jugada.

def evaluarMejorJugada(todasLasJugadasPosibles):
    cantidadDeFichasQueDaVuelta = 0
    claveJugada = None

    # Recorremos todo el diccionario "todasLasJugadasPosibles" en busca de la mejor jugada.
    for clave, valor in todasLasJugadasPosibles.items():

        # Preguntamos si la cantidad de elementos del conjunto "valor" es mayor a cantidadDeFichasQueDaVuelta.
        # De ser así, "clave" estaría indicando una jugada que da vuelta más fichas que las anteriores jugadas analizadas.
        if len(valor) > cantidadDeFichasQueDaVuelta:
            cantidadDeFichasQueDaVuelta = len(valor)
            claveJugada = clave

    return claveJugada


# ------------------------------------------------------
# evaluarPartidaEnCurso(): List[List[String]] -> Boolean

# Esta función determina y evalúa si la partida está en curso o no. Para ello, se llaman a dos funciones
# obtenerTodasLasJugadasPosibles que reciben el tablero y dos caracteres que representan los colores de cada jugador. 
# Si ambas devuelven un diccionario vacío, significa que no hay jugadas posibles para ninguno de los dos jugadores, 
# lo que indica que la partida ha terminado y devuelve False. De lo contrario, devuelve True indicando que la partida sigue en curso.

def evaluarPartidaEnCurso(tablero):

    jugadasPosiblesBlanco= obtenerTodasLasJugadasPosibles(tablero, "N", "B")
    jugadasPosiblesNegro= obtenerTodasLasJugadasPosibles(tablero, "B", "N")

    if jugadasPosiblesBlanco == {} and jugadasPosiblesNegro == {}:
        return False
    else:
        return True


# -------------------------------------------------
# determinarGanador(): List[List[String]] -> String

# Esta función recorre toda la matriz que representa al tablero de juego y cuenta las fichas que hay de cada color.
# Luego, imprime la cantidad de fichas de cada color y devuelve "B" si hay más fichas de color blanco, "N" si hay más del color negro
# o "X" si hay la misma cantidad de cada color, significando un empate.

def determinarGanador(tablero):
    contadorBlancas= 0
    contadorNegras= 0

    for i in range(8):
        for j in range(8):
            # Suma una unidad al contador de fichas blancas si encuentra "B" en una posición del tablero.
            if tablero[i][j] == "B":
                contadorBlancas+=1

            # De lo contrario, suma una unidad al contador de fichas negras.
            else:
                contadorNegras+=1
    
    print("Fichas blancas: " + str(contadorBlancas))
    print("Fichas negras: " + str(contadorNegras))

    if contadorBlancas>contadorNegras:
        return "B"
    elif contadorBlancas==contadorNegras:
        return "X"
    else:
        return "N"


# -----------------------------------------
# imprimirGanador(): String, String -> None

# Esta función no tiene retorno ya que solamente se encarga de imprimir en pantalla el resultado de la partida.
# Si el retorno de la función determinarGanador() coincide con el color que le pertenecía al usuario, imprime un mensaje de victoria.
# Si el retorno es una "X" imprime que la partida resultó en empate, y si no coincide con estos dos anteriores, indica que la PC ha resultado victoriosa.

def imprimirGanador(ganador, colorJugador):
    if ganador==colorJugador:
        print("Ganaste la partida!")
    elif ganador=="X":
        print("La partida resultó en empate.")
    else:
        print("Lamentablemente perdiste, ganó la PC.")


# Llamamos a la función principal del programa.
funcionPrincipal()