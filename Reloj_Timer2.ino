#include <MsTimer2.h> //Librería Timer
#include <LiquidCrystal.h> //Librería LCD
//LCD
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // RS,E,D4,D5,D6,D7 -> Pines de Arduino
/*
 * UTN FICA CIERCOM
 * MATEO TITO
 * SISTEMAS MICROPROCESADOS
 * Reloj que usa la librería Timer2 para mostrar la hora en un LCD 16X2
 */
int segundos = 0; //Contador segundos
int minutos = 0; //Contador minutos
int horas = 0; //Contador horas
String hour1 = "00"; //String para la hora
String hour2 = "00"; //String para la hora
String hour3 = "00"; //String para la segundos
String hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
void setup() {
  MsTimer2::set(1000, reloj); //Timer a 1 seg
  MsTimer2::start(); //Inicia el reloj
  lcd.begin(16, 2); //Inicia el LCD
  lcd.setCursor(0, 0); //Posición inicial del LCD
  lcd.print("LA HORA ES"); //Mensaje de inicio
  lcd.setCursor(0, 1); //Posición inicial del LCD
  lcd.print(hour); //Muestra la hora en pantalla
}

void loop() {
}
void reloj() { //Método para el Timer
  segundos++; //Contador reloj
  if (segundos == 60) { //Condición para segundero
    minutos++; //Contador minutero
    segundos = 0; //Reset segundero
  }
  if (minutos == 60) { //Condición para minutero
    horas++; //Contador horero
    minutos = 0; //Reset minutero
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
    hour3 = String(horas); //Asigna al String
  hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
  lcd.setCursor(0, 1); //Posición inicial en el LCD
  lcd.print(hour); //Muestra la hora en pantalla
}
