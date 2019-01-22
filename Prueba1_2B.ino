#include <avr/wdt.h> //Librería perro guardían (reinicio sistema)

/*
 * UTN FICA CIERCOM
 * SISTEMAS MICROPROCESADOS
 * PRUEBA 1 SEGUNDO BIMESTRE
 * MATEO TITO
 * 
 * Descripción:
 * Se trata de un sistema con con 4 botones, uno máster y 3 para la contraseña.
   La contraseña es de 5 dígitos que debe ser la combinación de los 3 botones.
   El sistema al presionar una vez (solo botón máster) y sin contraseña envía por comunicación
   serial el mensaje de activado o desactivado.
   Si es digitada la contraseña es correcta (se presiona la combinación de los 3 botones y luego
   el máster), envía por mensaje serial que se puede encender el carro. Caso contrario, se tendrá
   hasta 2 intentos más para acertar a la contraseña. Si no es el caso, el control se reinicia y
   genera otra contraseña de forma aleatoria de la combinación de los pulsadores. La nueva
   contraseña se envía por comunicación serial.

   Materiales: 4 Pulsadores 
                pin2 -> interrupción/master
                pin7 -> botón 1 (Ingresa 1 a la pass)
                pin8 -> botón 2 (Ingresa 2 a la pass)
                pin9 -> botón 3 (Ingresa 3 a la pass)
*/
//Variables del sistema
int mas = 0; //Variable para controlar opciones
int b1 = 7; //Botrón 1
int b2 = 8; //Botrón 2
int b3 = 9; //Botrón 3
int pass_s [5] = {0, 0, 0, 0, 0}; //Array contraseña por pulsadores
boolean enable_pass = false; //Des/Habilita el ingreso de la pass
boolean pass_ingre = false; //Verificación de la pass (5 dígitos)
boolean equivocado = false; //Controla los intentos
int i = 0; //Contador
int intentos = 3; //Número de intentos
int contra_1; //Variables para pass aleatoria
int contra_2;
int contra_3;
int contra_4;
int contra_5;
int contra [5] = {contra_1, contra_2, contra_3, contra_4, contra_5}; //Array pass
void setup() {
  Serial.begin(9600); //Inicia Cx
  randomSeed(analogRead(0)); //Semilla de random, lee ruido eléctrico
  contra_1 = random(1, 4); //Asigna números random
  contra_2 = random(1, 4);
  contra_3 = random(1, 4);
  contra_4 = random(1, 4);
  contra_5 = random(1, 4);
  int contra [5] = {contra_1, contra_2, contra_3, contra_4, contra_5}; //Asigna contraseña con #'s random
  Serial.println(String(contra[0]) + String(contra[1]) + String(contra[2]) + String(contra[3]) + String(contra[4]));
  attachInterrupt(0, master, LOW); //Botón Master
  pinMode(b1, INPUT); //Botones para contraseña 1
  pinMode(b2, INPUT); //2
  pinMode(b3, INPUT); //3
}

void loop() {
  if (enable_pass == true) { //Si está habilitado el ingreso de pass
    if (i < 5) { //Valida solo 5 dígitos
      if (digitalRead(b1) == LOW) { //Botón 1 asigna "1"
        delay(300); //Delay antirebotes
        pass_s [i] = 1; //Asigna contraseña ingresada
        //Serial.println(String(pass_s[i]) + "en la pos " + String(i));
        i++;
      }
      if (digitalRead(b2) == LOW) { //Botón 1 asigna "2"
        delay(300);//Delay antirebotes
        pass_s [i] = 2; //Asigna contraseña ingresada
        //Serial.println(String(pass_s[i]) + "en la pos " + String(i));
        i++;
      }
      if (digitalRead(b3) == LOW) { //Botón 1 asigna "3"
        delay(300);//Delay antirebotes
        pass_s [i] = 3; //Asigna contraseña ingresada
        //Serial.println(String(pass_s[i]) + "en la pos " + String(i));
        i++;
      }
    } else {
      Serial.println("PRESIONE MASTER"); //Presionar master para comprobar pass
      enable_pass = false; //Deshabilita el ingreso de pass hasta comprobación
      pass_ingre = true; //Habilita comprobación
    }
  }
}

void master () { //Botón master
int contra [5] = {contra_1, contra_2, contra_3, contra_4, contra_5};
  if (equivocado == false) { //Si se equivoca no cambia hasta terminar los 3 intentos
    if (mas < 3) { //Controla las 3 opciones disponibles
      mas++; //contador
    } else {
      mas = 0; //reset
    }
  }
  switch (mas) { //Opciones
    case 1:
      Serial.println("ACTIVADO"); //Mensaje de Activación al presionar master
      enable_pass = true; //Habilita ingreso de pass
      break;
    case 2:
      if (pass_ingre == true ) { //Verifica que haya ingreado alguna pass
        if (pass_s [0] == contra[0] && pass_s[1] == contra[1] && pass_s[2] == contra[2] &&
            pass_s [3] == contra[3] && pass_s[4] == contra[4]) { //Compara las pass
          Serial.println("PUEDE ENCENDER EL CARRO"); //Mensaje de confirmación
          pass_ingre = false; //Deshabilita el ingreso de pass
          equivocado = false; //Puede acceder a la opción 3
        } else {
          intentos = intentos - 1; //Pierde un intento
          Serial.println("PASS INCORRECTA"); //Mensaje de error
          Serial.println("INTENTOS RESTANTES: " + String(intentos)); //Indica intentos disponibles
          if (intentos > 0) { //Si todavía tiene intentos
            pass_ingre = false;
            enable_pass = true;
            equivocado = true;
            i = 0;
          } else { //Si se queda sin intentos
            Serial.println("REINICIADO");
            Serial.print("LA NUEVA PASS ES: ");
            wdt_enable(WDTO_1S); //Reinicia el sistema
          }
        }
      }
      break;
    case 3:
      Serial.println("DESACTIVADO");
      break;
  }
}

