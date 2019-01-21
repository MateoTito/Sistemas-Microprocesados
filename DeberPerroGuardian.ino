#include <avr/wdt.h> //Librería perro guardían
#include <LiquidCrystal.h> //Librería LCD
#include <MsTimer2.h> //Librería timer2
/*
 * UTN FICA CIERCOM
 * SISTEMAS MICROPROCESADOS
 * MATEO TITO
 * 
 * Descripción: 
 * Permite configurar el tiempo de activación del perro guardián
 * entre 10, 20, 30 y 40s con un conversor análogo digital.
 * 
 * Materiales: Arduino, pulsador(interrupción), potenciómetro(CAD).
 */
//LCD
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // RS,E,D4,D5,D6,D7 -> Pines de Arduino

float pot; //Almacena el CAD
int cont = 0; //Contador
boolean poten = true; //Bandera para habilitar CAD
void setup() {
  lcd.begin(16, 2); //Inicia LCD 16X2
  lcd.setCursor(0, 0); //Posición inicial
  lcd.print("CONFIGURE TIEMPO"); //Mensaje inicial
  MsTimer2::set(1000, cuenta); //Configura el timer en 1s
  attachInterrupt(0, pul, LOW); //Interrupción
}

void loop() {
  if (poten == true) { //Si está habilitado
    pot = (analogRead(0) * 5.0) / 1023.0; //CAD
    delay(10); //Delay de 10ms
    if (pot > 1.0 && pot <= 2.0) { //Rango 10s
      lcd.setCursor(0, 1); //Posición inicial
      lcd.print("WATCH DOG EN:10");
      cont = 10; //Segundos hasta activar WD
    } else if (pot > 2.0 && pot <= 3.0) { //Rango 20s
      lcd.setCursor(0, 1); //Posición inicial
      lcd.print("WATCH DOG EN:20");
      cont = 20; //Segundos hasta activar WD
    } else if (pot > 3.0 && pot <= 4.0) { //Rango 30s
      lcd.setCursor(0, 1); //Posición inicial
      lcd.print("WATCH DOG EN:30");
      cont = 30; //Segundos hasta activar WD
    } else if (pot > 4.0 && pot <= 5.0) { //Rango 40s
      lcd.setCursor(0, 1); //Posición inicial
      lcd.print("WATCH DOG EN:40");
      cont = 40; //Segundos hasta activar WD
    } else {
      lcd.setCursor(0, 1); //Posición inicial
      lcd.print("WATCH DOG EN:0  ");
      cont = 0;
    }
  }
}

void pul () { //Interrupción
  MsTimer2::start(); //Inicia contador
  lcd.setCursor(0, 0); //Posición inicial
  lcd.print("EL WATCH DOG    "); //Mensaje LCD
  poten = false; //Deshabilita CAD
  lcd.setCursor(0, 1); //Posición inicial
  lcd.print("                ");
  lcd.setCursor(0, 1); //Posición inicial
  lcd.print("EMPEZARA EN: " + String(cont));

}

void cuenta () { //Método Timer2
  cont--; //Contador tiempo WD
  lcd.setCursor(0, 1); //Posición inicial
  lcd.print("                ");
  lcd.setCursor(0, 1); //Posición inicial
  lcd.print("EMPEZARA EN: " + String(cont));
  if (cont == 1) { //Condición activar WD
    wdt_enable(WDTO_1S); //Activa WD en 1s
    MsTimer2::stop(); //Detiene timer
  }
}

