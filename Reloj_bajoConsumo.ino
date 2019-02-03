#include <MsTimer2.h> //Librería Timer
#include <LiquidCrystal.h> //Librería LCD
#include <EEPROM.h> //Librería EEPROM
#include <LowPower.h> //Librería modos sleep
#include <avr/power.h> //Librería deshabilitar perifericos
//LCD
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // RS,E,D4,D5,D6,D7 -> Pines de Arduino
/*
   UTN FICA CIERCOM
   MATEO TITO
   SISTEMAS MICROPROCESADOS

   Descripción:
   Sistema de reloj con memoria, muestra la hora en una LCD
   y deshabilita el CAD y el BOD durante cada medio segundo,
   lo que se refleja en una consumo de energía menor, además
   los perfiféricos (Como la Cx Serial) se encuentran desha-
   bilitados por defecto para mayor ahorro.

   Memoria EEPROM:
                  pos0 -> hora del reloj
                  pos1 -> minutos del reloj
                  pos2 -> segundos del reloj
*/
//Variables
int s = 0; //Segundos alarma
int m = 0; //Minutos alarma
int h = 0; //Horas alarma
int segundos = 0; //Contador segundos
int minutos = 0; //Contador minutos
int horas = 0; //Contador horas
String hour1 = "00"; //String para la hora
String hour2 = "00"; //String para la hora
String hour3 = "00"; //String para la segundos
String hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
void setup() {
//  EEPROM.write(0, 11);
//  EEPROM.write(1, 30);
//  EEPROM.write(2, 0);
  Serial.begin(9600);
  MsTimer2::set(1000, reloj); //Timer cada 1s
  MsTimer2::start(); //Inicia el Timer2
  horas = EEPROM.read(0); //Lee el horero almacenado
  minutos = EEPROM.read(1); //Lee el minutero almacenado
  lcd.begin(16, 2); //Inicia LCD
  lcd.setCursor(0, 0); //Punto inicial LCD
  lcd.print("LA HORA ES:     "); //Mensaje de inicio
  power_all_disable(); //Deshabilita todos los módulos
}

void loop() {

}

void reloj() { //Método para el Timer
  segundos++; //Contador reloj
  if (segundos == 60) { //Condición para segundero
    minutos++; //Contador minutero
    segundos = 0; //Reset segundero
    EEPROM.update(1, minutos); //Guarda los minutos
  }
  if (minutos == 60) { //Condición para minutero
    horas++; //Contador horero
    minutos = 0; //Reset minutero
    EEPROM.update(0, horas); //Guarda las horas
  }
  if (horas == 24) { //Condición para horero
    horas = 0; //Reset horero
  }
  //Asigna la hora correspondiente
  if (segundos < 10) //Unidades del segundero
    hour3 = "0" + String(segundos); //Concatena al contador
  else //Decenas del segundero
    hour3 = String(segundos); //Asigna al String
  if (minutos < 10) //Unidades del minutero
    hour2 = "0" + String(minutos); //Concatena al contador
  else //Decenas del minutero
    hour2 = String(minutos); //Asigna al String
  if (horas < 10) //Unidades del horero
    hour1 = "0" + String(horas); //Concatena al contador
  else //Decenas del horero
    hour1 = String(horas); //Asigna al String
  hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo

  lcd.setCursor(0, 1); //Posición inicial en el LCD
  lcd.print(hour); //Muestra la hora en pantalla
  Serial.println(hour); Comprobar que no hay Cx Serial
  delay(350); //Delay de 350 ms para evitar errores
  LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF); //Ahorra energía

}
