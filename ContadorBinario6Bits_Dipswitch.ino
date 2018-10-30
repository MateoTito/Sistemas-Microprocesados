/*
 * UTN FICA CIERCOM
 * Nombres: Tito Mateo, Yépez Johanna
 * Trabajo en Grupo
 * Switch que controla 4 juegos de luces diferentes
 * mediante estas combinaciones:
 * 1000: Se encienden los leds impares secuencialmente (ascendente)
 * y luego se apagan secuencialmente (descendente)
 * 0100: Se encienden los leds pares uno por uno (ascendente)
 * Y luego se apagan secuencialmente (descendente)
 * 0010: Se encienden los leds secuencialmente desde los extremos,
 * luego se apagan en secuencia desde el centro
 * 0001: Dos leds se encienden a manera de barrido
 * Contador Binario de 6 bits (hasta 127 en decimal) mediante pulsador 
 * 
 * Los elementos que se necesitarán para armar el circuito son: 6 leds,
 * 6 resistencias de bajo valor(330 ohm), un botón pulsador de dos o 
 * cuatro patas, un dipswitch de 4 bits.
 */
int pins [6] = {8, 9, 10, 11, 12, 13}; // Pines para leds
int sw[4] = {2, 3, 4, 5}; // Pines para dipswitch
int i = 0; // Variable de recorrido
int but = 7; // Pin para el pulsador del contador
int on = 0; // Bit 1
int n = 0; // Bit 2
int j = 0; // Bit 3
int k = 0; // Bit 4
int l = 0; // Bit 5
int m = 0; // Bit 6

void setup() {
  for (; i < 4; i++) {
    pinMode(sw[i], INPUT_PULLUP); // Declarar pines como salida en Pull Up
  }
  i = 0;
  for (; i < 6; i++) {
    pinMode(pins[i], OUTPUT); // Declarar pines de salida
  }
  pinMode(7, INPUT); // Pin para el botón
}

void loop() {
  // JUEGOS DE LUCES
  /////////////////////////////////////////////////////////////

  if (digitalRead(2) == HIGH && digitalRead(3) == LOW &&
      digitalRead(4) == LOW && digitalRead(5) == LOW) {
    // LEDS IMPARES
    i = 0; // Resetear la variable de recorrido
    // Ciclo para encender los leds impares (ascendente)
    for (; i < 3; i++) {
      digitalWrite(pins[2 * i + 1], HIGH); // Solo impares
      delay(200); // Retardo de 200ms
    }
    i = 0; // Reseteto de variable
    // Ciclo para apagar los impares (descendente)
    for (; i < 3; i++) {
      digitalWrite(pins[6 - (2 * i + 1)], LOW);
      delay(200); // Retardo de 200ms
    }
    reseteo(); // Cuando se use esta función se resetea el contador binario
  }
  
  /////////////////////////////////////////////////////////////
  // OPCIÓN 2
  
  else if (digitalRead(2) == LOW && digitalRead(3) == HIGH &&
           digitalRead(4) == LOW && digitalRead(5) == LOW) {
    //LEDS PARES
    i = 0; // Resetear la variable de recorrido
    for (; i < 3; i++) {
      digitalWrite(pins[2 * i], HIGH); //Encender los leds pares (ascendente)
      delay(200);// Retardo de 200ms
      digitalWrite(pins[2 * i], LOW); //Apagado de leds pares (descendente)
      delay(200); //Retardo de 200ms
    }
    reseteo(); // Cuando se use esta función se resetea el contador binario
  }
  
  /////////////////////////////////////////////////////////////
  // OPCIÓN 3
  
  else if (digitalRead(2) == LOW && digitalRead(3) == LOW &&
           digitalRead(4) == HIGH && digitalRead(5) == LOW) {
    // LEDS DE EXTREMOS AL CENTRO Y VISCEVERSA
    i = 0; 
    for (; i < 3; i++) { //Enciende los leds de los extremos
      digitalWrite(pins[i], HIGH); //Extremo inferior
      digitalWrite(pins[5 - i], HIGH); //Extremo superior
      delay(200); // Retardo de 200ms
    }
    i = 2;
    for (; i >= 0; i--) { //Apaga los leds de los extremos
      digitalWrite(pins[i], LOW); //Extremo inferior
      digitalWrite(pins[5 - i], LOW); //Extremo superior
      delay(200); // Retardo de 200ms
    }
    i = 0;
    reseteo(); // Cuando se use esta función se resetea el contador binario
  }
  /////////////////////////////////////////////////////////////
  // OPCIÓN 4
  
  else if (digitalRead(2) == LOW && digitalRead(3) == LOW &&
           digitalRead(4) == LOW && digitalRead(5) == HIGH) {
    // LEDS EN BARRIDO
    i = 1;
    for (; i < 6; i++) { //Enciende de dos en dos los leds
      digitalWrite(pins[i - 1], HIGH); //Led superior
      delay(200); // Retardo de 200ms
      digitalWrite(pins[i], HIGH); //Led inferior
      delay(200); // Retardo de 200ms
      digitalWrite(pins[i - 1], LOW);
      delay(200); // Retardo de 200ms
    }
    digitalWrite(pins[5], LOW); //Apaga solo un led
    delay(200); // Retardo de 200ms
    reseteo(); // Cuando se use esta función se resetea el contador binario
  }
  
  /////////////////////////////////////////////////////////////
  // CONTADOR BINARIO
  else if (digitalRead(2) == LOW && digitalRead(3) == LOW &&
           digitalRead(4) == LOW && digitalRead(5) == LOW) {
   if (digitalRead(but) == HIGH) {
      delay(300); //delay antirebotes
      on = 1 - on; //cambia de estado de 1 a 0 o viceversa
      n++;
      j++;
      k++;
      l++;
      m++;
    }
    if (on == 1) //comparo estado de on
      digitalWrite(pins[5], HIGH); //enciendo led
    else
      digitalWrite(pins[5], LOW); //apago led
    // Segundo Bit
    if (n == 2) {
      digitalWrite(pins[4], HIGH); //enciendo led
    } else if (n == 4) {
      digitalWrite(pins[4], LOW); //apago led
      n = 0;
    }
    // Tercer Bit
    if (j == 4) {
      digitalWrite(pins[3], HIGH); //enciendo led
    } else if (j == 8) {
      digitalWrite(pins[3], LOW); //apago led
      j = 0;
    }
    // Cuarto Bit
    if (k == 8) {
      digitalWrite(pins[2], HIGH); //enciendo led
    } else if (k == 16) {
      digitalWrite(pins[2], LOW); //apago led
      k = 0;
    }
    //Quinto Bit
    if (l == 16) {
      digitalWrite(pins[1], HIGH); //enciendo led
    } else if (l == 32) {
      digitalWrite(pins[1], LOW); //apago led
      l = 0;
    }
    //Sexto Bit
    if (m == 32) {
      digitalWrite(pins[0], HIGH); //enciendo led
    } else if (m == 64) {
      digitalWrite(pins[0], LOW); //apago led
      m = 0;
    }
  }

  /////////////////////////////////////////////////////////////
  // Si no se activa SOLAMENTE una de las 4
  // opciones todos los leds parpadearán
  else {
    i = 0;
    for (; i < 6; i++) { // Apaga todos los leds
      digitalWrite(pins[i], LOW);
    }
    delay(200); // Retardo de 200ms
    reseteo(); // Cuando se use esta función se resetea el contador binario
  }
}
// Método para resetear el contador
void reseteo() {
  on = 0;
  j = 0;
  k = 0;
  l = 0;
  m = 0;
  n = 0;
}
