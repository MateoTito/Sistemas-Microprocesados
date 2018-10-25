/*
 * UTN FICA CIERCOM
 * Autor: Mateo Tito
 * Deber de Sistemas Microprocesados
 * 1.- Realizar un juego de lueces que se prendan secuencialmente los leds impartes (1,3,5). 
 * 2.- Realizar un programa que se enciendan uno por uno los leds pares (0,2,4). 
 * 3.- Realizar un juego que se enciendan y apaguen los leds de forma aleatoria.
 */
 
//Variables a usar
int i=0; //Para recorrer ciclos
int pins [6] = {2, 3, 4, 5, 6, 7}; //Pines a usarse
int rng = 0; //Variable entera para usar aleatorio(luego)

void setup() {
  randomSeed(40);
  for(;i<6;i++){
    pinMode(pins[i],OUTPUT); //Definir pines como salidas
  }

}

void loop() {

  // Ejercicio 1
  i=0; // Resetear la variable de recorrido
  // Ciclo para encender los leds impares (ascendente)
  for(;i<3;i++){
    digitalWrite(pins[2*i+1],HIGH); // Solo impares
    delay(200); // Retardo de 200ms
  }
  i=0; // Reseteto de variable
  // Ciclo para apagar los impares (descendente)
  for(;i<3;i++){
    digitalWrite(pins[6-(2*i+1)],LOW);
    delay(200); // Retardo de 200ms
  }

  //Ejercicio 2
  i=0; // Resetear la variable de recorrido
  // Ciclo para encender los leds pares (ascendente)
  for(;i<3;i++){
    digitalWrite(pins[2*i],HIGH); // Solo pares
    delay(200); // Retardo de 200ms
  }
  i=1; // Reseteto de variable
  // Ciclo para apagar los pares (descendente)
  for(;i<4;i++){
    digitalWrite(pins[6-(2*i)],LOW);
    delay(200); // Retardo de 200ms
  }

  //Ejercicio 3
  i=0;
  for(;i<6;i++){ // Genera 6 números aleatorios para encender
    rng = random(0,5); // Variable aleatoria entre 0 y 5 
    digitalWrite(pins[rng],HIGH);
    delay(200); // Retardo de 200ms 
  }
  i=0;
  for(;i<6;i++){ // Genera 6 números aleatorias para apagar
    rng = random(0,5); // Variable aleatoria entre 0 y 5 
    digitalWrite(pins[rng],LOW);
    delay(300); // Retardo de 300ms
  }

  // No es parte de los ejercicios
  // Enciende y apaga los 6 leds secuencialmente para indicar
  // que se volverá a repetir el código
  i=5;
  for(;i>=0;i--){ // Apagado secuencial descendente (Todos)
    digitalWrite(pins[i],LOW);
    //delay(300); // Retardo de 300ms
  }
  i=0;
  for(;i<6;i++){ // Encendido secuencial ascendente (Todos)
    digitalWrite(pins[i],HIGH);
    delay(300); // Retardo de 000ms
  }
  i=5;
  for(;i>=0;i--){ // Apagado secuencial descendente (Todos)
    digitalWrite(pins[i],LOW);
    delay(300); // Retardo de 300ms
  }
}
