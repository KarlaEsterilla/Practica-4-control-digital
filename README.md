# Practica-4-control-digital
**Karla Victoria Barrera Saavedra  Pablo Isaac Cárdenas Regalado**
Práctica 4 de control digital, Implementar una secuencia de encendido de LEDs utilizando un microcontrolador

Esta práctica, consta de 7 archivos:


`main.cpp` Este archivo es el programa principal, consta de una máquina de estados finitos cuyo objetivo es solucionar el rebote de los botones: *Este algoritmo es escalable y reutilizable* ya que se puede agregar cualquier cantidad de botones, que esta única máquina de estados reconoce el boton. Este archivo también tiene el algoritmo para manejo de interrupciones, la misma que sirve para controlar el tiempo de prendido y apagado del arreglo de leds.


`leds_off.cpp` Este pequeño código sirve para apagar todos los leds que conectemos al arduino.


`interrupcion.cpp` Este código es el encargado de la secuencia de leds se maneja a través de un switch, en el caso 0 los leds van de izquierda a derecha, en el caso 1 los leds van de derecha a izquierda, este algoritmo es *escalable* ya que sirve de para cualquier número de leds.


`Delay_not_block.cpp` Este es un retardo no bloqueante el cual usamos para la máquina de estados finitos para reconocer los rebotes.
