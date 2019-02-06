#include <LowPower.h> //Librería para modos sleep
/*
   UTN FICA CIERCOM
   SISTEMAS MICROPROCESADOS
   Mateo Tito

   Descripción:
   Sistema que se "duerme" durante 25 segundos
   al presionar el pulsador.

   Estructura:
              LowPower.powerDown(WDT, modos);
   
   Watchdog timer (WDT):
                  SLEEP_15MS
                  SLEEP_30MS
                  SLEEP_60MS
                  SLEEP_120MS
                  SLEEP_250MS
                  SLEEP_500MS
                  SLEEP_1S
                  SLEEP_2S
                  SLEEP_4S
                  SLEEP_8S
                  SLEEP_FOREVER
  Modos:
        ADC_OFF -> Apaga los convertidores AD
        BOD_OFF -> Apaga el detector de tensión baja

*/
void setup(){
  Serial.begin(9600); //Inicia Cx Serial
  attachInterrupt(0, dormir, LOW);
}

void loop(){
}

void dormir () {
  for (int i = 0 ;  i  <  12 ; i++) { //Permite aumentar el tiempo
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); //Sentencia LowPower
  }
  delay(200); //Tiempo hasta que se enciendan los CAD
}

