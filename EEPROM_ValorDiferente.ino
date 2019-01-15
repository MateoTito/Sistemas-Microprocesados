#include <EEPROM.h> //Librería memoria EEPROM
/*
 * UTN FICA CIERCOM
 * SISTEMAS MICROPROCESADOS
 * Mateo Tito
 * 
 * Descripción:
 * Sistema que permite guardar un número en la memoria EEPROM,
 * siempre y cuando este sea diferente del que previamente se
 * encuentre guardado.
 * 
 * Elementos:
 * -Arduino UNO       - Pulsador pin 2
 * 
 * Memoria EEPROM:    número -> pos20
 */
String lec; //Lee los datos por serial
int op = 0; //Controla opciones
int lec1; //Convierte String a entero
int eepr; //Lee los datos de la EEPROM
void setup() {
  Serial.begin(9600); //Inicia Cx Serial
  attachInterrupt(0, pul1, LOW); //Interrupción pulsador 1
  Serial.println("INGRESE UN NUMERO ENTRE 0 Y 255: "); //Mensaje Serial
}

void loop() {
  switch (op) { //Lee los datos por serial
    case 0:
      if (Serial.available() > 0) { //Comprueba que hayan datos
        lec = Serial.readString(); //Almacena los datos
        lec1 = lec.toInt(); //Convierte los datos
      }
      break;
  }
}

void pul1 () {
  eepr = EEPROM.read(20); //Lee la memoria
  if (op < 1) //Controla el reset del contador
    op++; //Contador
  else
    op = 0; //Reset

  switch (op) {
    case 0:
      Serial.println("INGRESE UN NUMERO ENTRE 0 Y 255: "); //Mensaje
      break;
    case 1:
      if (lec1 == eepr) { //Compara si está repetido
        Serial.println("VALOR REPETIDO"); //Mensaje Serial
      } else if (lec1 > eepr || lec1 < eepr){ //Compara si es diferente
        if (lec1 < 0 || lec1 > 255) { //Verificia que el número esté entre 0 y 255
           Serial.println("VALOR NO PERMITIDO"); //Mensaje Serial
        } else {
        EEPROM.update(20, lec1); //Actualiza el valor en la EEPROM
        Serial.println("VALOR INGRESADO"); //Mensaje Serial
        }
      }
      break;
  }
}

