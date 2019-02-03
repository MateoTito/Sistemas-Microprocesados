#include <LowPower.h> //Librería para modos sleep
/*
   UTN FICA CIERCOM
   SISTEMAS MICROPROCESADOS
   Mateo Tito

   Descripción:
   Sistema que lee el pin A0(COnversor análogo digital),
   luego imprime por Cx Serial el valor y duerme el 
   sistema por 19 segundos, esto reduce la corriente del
   Arduino de 14mA a 6uA. Permitiendo ahorrar energía.

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
}

void loop(){
  for (int i = 0 ;  i  <  8 ; i++) { //Permite aumentar el tiempo
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); //Sentencia LowPower
  }
  delay(200); //Tiempo hasta que se enciendan los CAD
  float cad = analogRead(A0);
  Serial.println((cad*5.0)/1023.0); //Imprime el valor del conversor
  delay(100); //Delay para asegurar lectura
}
