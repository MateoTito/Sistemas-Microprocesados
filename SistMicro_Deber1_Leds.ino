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
int rng = 0;
void setup() {
  for(;i<6;i++){
    pinMode(pins[i],OUTPUT); //Definir pines como salidas
  }

}

void loop() {
/*
  // Ejercicio 1
  i=0; // Resetear la variable de recorrido
  // Ciclo para encender los leds impares (ascendente)
  for(;i<3;i++){
    digitalWrite(pins[2*i+1],HIGH); // Solo impares
    delay(200);
  }
  i=0; // Reseteto de variable
  // Ciclo para apagar los impares (descendente)
  for(;i<3;i++){
    digitalWrite(pins[6-(2*i+1)],LOW);
    delay(200);
  }

  //Ejercicio 2
  i=0; // Resetear la variable de recorrido
  // Ciclo para encender los leds pares (ascendente)
  for(;i<3;i++){
    digitalWrite(pins[2*i],HIGH); // Solo pares
    delay(200);
  }
  i=1; // Reseteto de variable
  // Ciclo para apagar los pares (descendente)
  for(;i<4;i++){
    digitalWrite(pins[6-(2*i)],LOW);
    delay(200);
  }

*/
  //Ejercicio 3
  i=0;
  for(;i<6;i++){
    rng = random(0,5); // Variable aleatoria entre 0 y 5 
    digitalWrite(pins[rng],HIGH);
    delay(200);
  }
  i=0;
  for(;i<6;i++){
    rng = random(0,5); // Variable aleatoria entre 0 y 5 
    digitalWrite(pins[rng],LOW);
    delay(200);
  }
  

}
