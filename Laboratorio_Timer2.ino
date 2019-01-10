/*
   UTN FICA CIERCOM
   MATEO TITO - JOHANNA YEPEZ
   LABORATORIO DE SISTEMAS MICROPROCESADOS
   Realice un reloj con un pulsador con las funciones de modificar la hora y crear la alarma.
   Otro pulsador para modificar el valor del minutero para actualizar la hora y la alarma y
   otro que permita actualizar el horero.
   Pulsador 1: Modificar la hora y crear alarma.
   Pulsador 2: Modificar el minutero, actualizar alarma, actualizar la hora.
   Pulsador 3: Actualizar el horero

   MATERIALES:
   - 3 pulsadores (pines 2, 3, 4)
   - 1 Buzzer (pin 7)
   - 1 Pantalla LCD
*/

#include <MsTimer2.h> //Librería Timer
#include <LiquidCrystal.h> //Librería LCD
//LCD
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // RS,E,D4,D5,D6,D7 -> Pines de Arduino
volatile int opc = 0; //Ingresar alarma
volatile int menu = 1; //Controla opciones disponibles
int buzz = 7; //Pin buzzer
boolean buzz_off = false; //Bandera buzzer activado
int buzz_cont = 0; //Contador para desactvar el buzzer
int s = 0; //Segundos alarma
int m = 0; //Minutos alarma
int h = 0; //Horas alarma
String tiempo; //Almacena la hora ingresada por serial
String tiempo1; //Almacena los minutos ingresados por serial
String tiempo2; //Almacena los segundos
int segundos = 0; //Contador segundos
int minutos = 0; //Contador minutos
int horas = 0; //Contador horas
String hour1 = "00"; //String para la hora
String hour2 = "00"; //String para la hora
String hour3 = "00"; //String para la segundos
String hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
boolean mod_minuhora = false; //Bandera modificar el horero y minutero
boolean crea_alarm = false; //Bandera crear alarma

void setup() {
  MsTimer2::set(1000, reloj); //Timer cada 1s
  MsTimer2::start(); //Inicia el Timer2
  Serial.begin(9600); //Inicia la Cx Serial
  Serial.println("SISTEMA DE RELOJ ALARMA"); //Imprime mensaje Serial
  Serial.println("SUS OPCIONES SON: (USE PUL1)"); //Imprime mensaje Serial
  Serial.println("1)MODIFICAR HORA"); //Imprime mensaje Serial
  Serial.println("2)CREAR ALARMA"); //Imprime mensaje Serial
  attachInterrupt(digitalPinToInterrupt(2), pul1, "LOW"); //Interrupción 1
  attachInterrupt(digitalPinToInterrupt(3), pul3, "LOW" ); //Interrupción 2
  lcd.begin(16, 2); //Inicia LCD
  lcd.setCursor(0, 0); //Punto inicial LCD
  lcd.print("LA HORA ES"); //Mensaje de inicio
  lcd.setCursor(0, 1); //Posición inicial del LCD
  lcd.print(hour); //Muestra la hora en pantalla
  Serial.setTimeout(1000); //Duración para el read Serial
  pinMode(4, INPUT); //Pin para pulsador 2
  pinMode(buzz, OUTPUT); //Pin para buzzer como salida
}

void loop() {
  if (mod_minuhora == true) { //Modifica minutero
    if (digitalRead(4) == LOW) { //Activo con pulsador 2
      delay(250); //Delay anti rebotes
      horas++; //Contador para cambiar el horero
      if (horas > 23)  //Condición reset horero
        horas = 0; //Reset horero
      if (horas < 10) //Unidades del horero
        hour1 = "0" + String(horas); //Concatena al contador
      else //Decenas del horero
        hour1 = String(horas); //Asigna al String
      hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
      lcd.setCursor(0, 1); //Posición inicial en el LCD
      lcd.print(hour); //Muestra la hora en pantalla
    }
  } else if (mod_minuhora == false) { //Opción crear alarma
    if (digitalRead(4) == LOW) { //Pulsador 2 activado
      delay(250); //Delay antirebotes
      MsTimer2::start(); //Reanuda el reloj
    }
    switch (opc) { //Ingreso de horas y minutos para alarma
      case 0: //Ingreso de Hora
        if (Serial.available() > 0)  //Comprueba que hay datos
          tiempo = Serial.readString(); //Almacena datos
        break;
      case 1: //Ingreso de Minutos
        if (Serial.available() > 0)  //Comprueba que hay datos
          tiempo1 = Serial.readString(); //Almacena datos
        break;
    } //Cierre switch
  } //Cierre ingresar alarma
}

void pul1 () {
  menu = 1 - menu; //Posibles dos opciones para el pulsador 1
  switch (menu) { //Opciones -> 1)Modificar hora y 2)Crear alamar
    case 0: //Modificar la hora
      Serial.println("MODIFICANDO HORA..."); //Imprime mensaje Serial
      Serial.println("PUL2 -> MINUTERO"); //Imprime mensaje Serial
      Serial.println("PUL3 -> HORERO"); //Imprime mensaje Serial
      Serial.println("PRESIONE PUL1 y LUEGO PUL2 PARA ACTUALIZAR"); //Imprime mensaje Serial
      MsTimer2::stop(); //Detinene el reloj
      mod_minuhora = true; //Habilita modificar minutos y horas
      crea_alarm = false; //Deshabilita crear alarma
      break;
    case 1: //Crear la alarma
      Serial.println("CREANDO ALARMA..."); //Imprime mensaje Serial
      mod_minuhora = false; //Deshabilita modificar minutos y horas
      crea_alarm = true; //Habilitar crear alarma
      Serial.println("INGRESE ALARMA: HORA?"); //Imprime mensaje Serial
      break;
  }
}

void pul3 () { //Pusaldor 3 interrupción
  if (crea_alarm == true) { //Si está habilitado crear alarma
    opc++; //Contador para ingreso de datos
    switch (opc) {
      case 1:
        h = tiempo.toInt(); //Almacena horas como entero
        Serial.println("INGRESE ALARMA: MINUTOS?");
        break;
      case 2:
        m = tiempo1.toInt(); //Almacena minutos como entero
        Serial.println("PRESIONE PARA GUARDAR");
        break;
      case 3:
        if (h >= 24 || m >= 60)  //Valida los datos ingresados
          Serial.println("ALARMA MAL INGRESADA"); //Mensaje de información
        else
          Serial.println("SU ALARMA: " + String(h) + ":" + String(m) + ":" + String(s));
        break;
      case 5:
        Serial.println("RESET ALARMA");
        opc = 0;
        Serial.println("INGRESE ALARMA: HORA?"); //Imprime mensaje Serial
        tiempo = ""; //Reset de Strings
        tiempo1 = "";
        tiempo2 = "";
        break;
    }
  } else if (mod_minuhora == true) { //Si modificar la hora y minutos está habilitado
    minutos++; //Contador minutos
    if (minutos > 59) //Si minutos sobrepasa los 59
      minutos = 0; //Reset minutero
    if (minutos < 10)  //Unidades del minutero
      hour2 = "0" + String(minutos); //Concatena al contador
    else //Decenas del minutero
      hour2 = String(minutos); //Asigna al String
    hour = hour1 + ":" + hour2 + ":" + hour3; //String reloj completo
    lcd.setCursor(0, 1); //Posición inicial en el LCD
    lcd.print(hour); //Muestra la hora en pantalla
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
    lcd.setCursor(0, 0);
    lcd.print("DESPIERTA!!!");
    Serial.println("ALARMA ACTIVADA");
    digitalWrite(buzz, HIGH);
    buzz_off = true;
  }
  if (buzz_off == true) {
    buzz_cont++;
    if (buzz_cont == 59) {
      digitalWrite(buzz, LOW);
      lcd.setCursor(0, 0);
      lcd.print("LA HORA ES: ");
      Serial.println("ALARMA DESACTIVADA");
      buzz_cont = 0;
      buzz_off = false;
    }
  }
}
