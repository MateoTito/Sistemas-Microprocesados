#include <MsTimer2.h> //Librería Timer
#include <LiquidCrystal.h> //Librería LCD
//LCD
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // RS,E,D4,D5,D6,D7 -> Pines de Arduino
/*
   UTN FICA CIERCOM
   MATEO TITO
   SISTEMAS MICROPROCESADOS

   Sistema de reloj que permite ingresar una alarma mediante comunicación serial,
   para el reloj hace uso de la librería Timer2, el reloj se muestra en una pantalla
   LCD y hace uso de la librería LiquidCrystal. El proceso de configuración de la
   alarma se ayuda de una interrupción en el pin 2.
*/
volatile int opc = 0; //Casos para el ingreso de alarma
int buzz = 7; //Pin para el buzzer de la alarma
int m = 0; //Almacena los minutos ingresados
int h = 0; //Almacena las horas ingresadas
String tiempo; //Horas
String tiempo1; //Minutos
String tiempo2; //Segundos
int segundos = 0; //Contador segundos
int minutos = 0; //Contador minutos
int horas = 0; //Contador horas
String hour1 = "00"; //String para la hora
String hour2 = "00"; //String para la hora
String hour3 = "00"; //String para la segundos
String hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
boolean buzz_off = false; //Bandera para buzzer
void setup() {
  pinMode(buzz, OUTPUT); //Buzzer
  MsTimer2::set(1000, reloj); //Timer cada 1s
  MsTimer2::start(); //Inicia el Timer2
  Serial.begin(9600); //Inicia la Cx Serial
  Serial.println("INGRESE ALARMA: HORA?"); //Imprime mensaje Serial
  attachInterrupt(0, ingreso, "LOW"); //Interrupción
  lcd.begin(16, 2); //Inicia LCD
  lcd.setCursor(0, 0); //Punto inicial LCD
  lcd.print("LA HORA ES"); //Mensaje de inicio
  lcd.setCursor(0, 1); //Posición inicial del LCD
  lcd.print(hour); //Muestra la hora en pantalla
  Serial.setTimeout(1000); //Espera en la lectura por serial
}

void loop() {
  switch (opc) {
    case 0: //Ingreso de Hora
      if (Serial.available() > 0)  //Comprueba que hay datos
        tiempo = Serial.readString(); //Almacena datos
      break;
    case 1: //Ingreso de Minutos
      if (Serial.available() > 0)  //Comprueba que hay datos
        tiempo1 = Serial.readString(); //Almacena datos
      break;
  }
}

void ingreso () { //Método para el ingreso de la alarma
  opc++; //Contador para opciones
  switch (opc) {
    case 1: //Almacena hora
      h = tiempo.toInt(); //Asignación
      Serial.println("INGRESE ALARMA: MINUTOS?"); //Mensaje por serial
      break;
    case 2:
      m = tiempo1.toInt(); //Almacena minutos
      Serial.println("INGRESE ALARMA: SEGUNDOS?"); //Mensaje por serial
      break;
    case e:
      if (m > 59 || m < 0 || h > 24 || h < 0) { //Validación de los valores ingresados
        Serial.println("ALARMA MAL INGRESADA"); //Mensaje por serial
      } else { //Mensaje por serial
        Serial.println("SU ALARMA: " + String(h) + ":" + String(m) + ":" + String(s));
      }
      break;
    case 4: //Reset de la alarma
      Serial.println("RESET ALARMA"); //Mensaje por serial
      opc = 0; //Reinicia la variable
      Serial.println("INGRESE ALARMA: HORA?"); //Imprime mensaje Serial
      tiempo = ""; //Limpia los strings
      tiempo1 = "";
      tiempo2 = "";
      break;
  }
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
    hour1 = String(horas); //Asigna al String
  hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
  lcd.setCursor(0, 1); //Posición inicial en el LCD
  lcd.print(hour); //Muestra la hora en pantalla
  if (s == hour3.toInt() && m == hour2.toInt() && h == hour1.toInt()) {
    buzz_off == true; //Bander alarma
    lcd.setCursor(0, 0); //Posición inicial LCD
    lcd.print("DESPIERTA!!!"); //Mensaje en LCD
    Serial.println("ALARMA ACTIVADA"); //Mensaje por serial
    digitalWrite(buzz, HIGH); //Activa la alarma
  }
  if (buzz_off == true) {
    buzz_cont++; //Cuenta los segundos desde la alarma activada
    if (buzz_cont == 59) { //Un minuto
      digitalWrite(buzz, LOW); //Apaga la alarma
      lcd.setCursor(0, 0); //Posición inicial
      lcd.print("LA HORA ES: "); //Mensaje por LCD
      Serial.println("ALARMA DESACTIVADA"); //Mensaje por serial
      buzz_cont = 0; //Reset contador
      buzz_off = false; //Cambio de estado bandera
    }
  }
}
