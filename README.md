# othelloGame-C-Python
## Juego Othello de consola desarrollado en C y en Python para el final de la materia 'Programación 2' de la Licenciatura en Ciencias de la Computación de la UNR.

## Descripción del juego
**__Othello__** es un juego de estrategia para dos jugadores, también conocido como Reversi. El objetivo del juego es **tener más fichas de tu color que el oponente al final del juego.**

El tablero de Othello es un **tablero cuadrado de 8x8, con 64 casillas en total.** Cada jugador tiene 32 fichas, de un color negro y otro blanco, que se colocan en el tablero alternando los colores en las dos casillas centrales del tablero.

El juego comienza con cuatro fichas en el centro del tablero: dos fichas blancas y dos fichas negras dispuestas en forma de cuadrado. Los jugadores se turnan para colocar una ficha en el tablero, con el objetivo de capturar fichas del oponente y convertirlas en su propio color.

<p align="center">
  <img src="https://user-images.githubusercontent.com/90485317/224862048-ef84efdf-1bef-49b3-9a0b-5c8421fdef9d.png" />
</p>

Una captura ocurre cuando una ficha de un jugador es colocada en el tablero de tal manera que una línea recta (horizontal, vertical o diagonal) de fichas del oponente está flanqueada en ambos extremos por la nueva ficha y otra ficha del jugador. Las fichas flanqueadas son entonces capturadas y se colocan del color del jugador que ha hecho la captura.

Por ejemplo, en la siguiente configuración de fichas, el jugador con fichas blancas puede poner una ficha en F4, F6 o D6.

<p align="center">
  <img src="https://i.ibb.co/BGRQ2qd/othello-movement.png" />
</p>

Si se juega en la posición D6 el tablero quedaría de la siguiente forma:

<p align="center">
  <img src="https://i.ibb.co/JHR7mTJ/othello-movement2.png" />
</p>

Es obligatorio hacer una captura siempre que sea posible. Si no es posible hacer una captura, se puede pasar el turno al oponente. Si ambos jugadores pasan el turno consecutivamente, el juego termina y se cuentan las fichas. El jugador con más fichas de su color en el tablero gana el juego.



