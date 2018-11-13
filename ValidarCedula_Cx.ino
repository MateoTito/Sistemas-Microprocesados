#include<stdlib.h> //Conversiones lenguaje C 
/*
   UTN FICA CIERCOM
   Autor: Mateo Tito
   Deber de Sistemas Microprocesados
   Programa que permite ingresar el número de cédula con el guión y posteriormente
   validarlo. El dato se ingresa por comunicación serial. Los crterios para la
   validación son:
   -Deben ingresarse 11 dígitos, contando el guión.
   -Debe existir un guión antes del último dígito.
   -Todos los dígitos ingresados deben ser números.
   -La cédula debe cumplir el criterio del *Módulo 10 para el último dígito.
   -Los dos primeros dígitos no deben superar 24, por las provincias.
   -El tercer dígito no debe ser mayor a 5.

    *Modulo 10: Se multiplican los 9 primeros digitos por los coeficientes 2 1 2 1 2 1 2 1 2,
    de manera individual, si alguno sobrepasa 10 se le resta 9, se suman todos los
    productos y el resultado se resta a su decena superior, este resultado deberá
    ser igual al último dígito de la cédula ecuatoriana.

*/

String cedula; //Almacena la cadena de texto
int tam; //Tamaño de la cadena
int probe = 0; //Comprueba el Modulo 10
int i = 0; //Contador
int entero; //Comparar digitos con enteros
int ctrl; //Decena superio para el Modulo 10
boolean bandera = false; //Falsa si todos los dígitos son números
boolean bandera1 = false; //Falsa si los dos priemeros números son menores a 24
int dece = 0; //Extrae las decenas de la sumatoria para el Modulo 10
long num_ced; //Convertir de char a int, long para tener 32 bits de datos
char ced [10]; //Comparador y almacena los dígitos comprobados
int comp, comp1, comp2; //Variables para comparar los 3 primeros dígitos
int j = 0; //Contador para validar el último dígito

void setup() {
  Serial.begin(9600); //Configuracion Cx serial
  Serial.println("Ingrese su cedula con un guion:"); //Indica la forma de ingreso
}

void loop() {

  if (Serial.available() > 0) { //Comprueba que hay datos disponibles
    cedula = Serial.readString(); //Almacena los datos en una cadena de texto
    tam = cedula.length(); //Almacena el tamaño de la cadena de texto
    char vector [tam]; //Vector char con el tamaño de la cadena
    cedula.toCharArray(vector, tam + 1); //Se crea el vector tipo char
    //Serial.println(vector);
    if (tam == 11) { //Comprueba la cantidad correcta de datos ingresados
      if (vector[9] == '-') { //Verifica si cuenta con el guión
        for (; i < 9; i++) { // Recorre el vector para comprobar dato por dato
          ced [i] = vector [i];
          entero = atoi(&ced[i]); //Covierte cada char en int
          if (isDigit(ced[i])) { //Comprueba que todos sean números
            bandera = false; //Bandera se mantiene en reposo
          }  else { //Si algún digito no es un número
            bandera = true; //Bandera cambia a verdadero
            break; //Termina las iteraciones
          }
        }
        //Valida los 2 primeros dígitos
        comp = String(ced[0]).toInt(); //Transforma a entero el primer digito
        comp1 = String(ced[1]).toInt(); //Transforma a entero el segundo digito
        if (comp < 2) { //Si el primero es menor a 2
          bandera1 = false; //Todo en orden
        }
        else if (comp == 2) { //Si el primero es igual a 2
          if (comp1 < 5) { //El segundo no debe ser mayor a 4
            bandera1 = false; //Todo en orden
          } else {
            bandera1 = true; //Cedula no valida
            Serial.println("");
            Serial.println("Los dos primeros digitos no deben ser mayores a 24");
          }
        } else { //De otro modo el primer dígito es mayor a 2
          Serial.println("");
          Serial.println("Cedula no valida");
          Serial.println("Primer digito mayor que 2");
        }

        //Valida el tercer dígito
        comp2 = String(ced[2]).toInt(); //Convierte el tercer dígito a entero
        if (comp2 >= 6) { //Si el tercero es mayor a 5 no es válida
          Serial.println("");
          Serial.println("Cedula no valida.");
          Serial.println("Tercer digito mayor a 5");
        }

        //Valida el último dígito
        j = 0; //Reinicio de variable contador
        probe = 0; //Reinicio de variable sumador
        for (; j < 9; j++) { //Toma los digitos en posición par
          if ((String(ced[j]).toInt()) * 2 > 10) { //Si su doble producto supera a 9
            probe = probe + ((String(ced[j]).toInt()) * 2 - 9); //Se resta 9 y se suma al total
            j++; //Contador solo para pares

          } else { //Si su doble producto no supera 9
            probe = probe + String(ced[j]).toInt() * 2; //Sumatoria total
            j++; //Contador solo para pares
          }
        }
        j = 1; //Setear el contador solo para impares
        for (; j < 9; j++) {
          probe = probe + String(ced[j]).toInt(); //Sumatoria total
          j++; //Doble contador para impares
        }
        i = 0; //Reseteo de contador
        if (bandera == false) { //Si no hay inconvenientes continua el proceso
          dece = probe / 10; //Obtiene las decenas de la sumatoria total
          ctrl = (dece + 1) * 10 - probe; //Se resta de la decena superior
          ced [9] = vector [10]; //Se adjunta el digito 10
          if (ctrl == atoi(&ced[9])) { //Si el último digito se cumple la condicion del modulo 10
            Serial.println(""); //Salto de línea (estético)
            Serial.println("Cedula validada"); //Todo en orden

          } else {
            Serial.println("");
            Serial.println("Cedula no valida.");
            Serial.println("Ultimo digito incorrecto."); //No corresponde a una cedula real
          }
        } else if (bandera1 == true) { //Bandera verdadero si los dos primeros dígitos superan 24
          Serial.println("");
          Serial.println("Dos primeros digitos mayores a 24");
        } else {
          Serial.println("");
          Serial.println("Todos los digitos deben ser numeros");
        }
      } else {
        Serial.println("");
        Serial.println("Cedula no valida. Falta el guion"); //Tamaño correcto, pero falta guion
      }
    } else {
      Serial.println("");
      Serial.println("Cedula no valida"); //Si no tiene 10 dígitos y el guión
    }
  }
}
