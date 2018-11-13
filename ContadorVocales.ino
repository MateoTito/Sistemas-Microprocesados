/*
   UTN FICA CIERCOM
   Autor: Mateo Tito
   Deber de Sistemas Microprocesados
   Programa que permite determinar el número de vocales dentro de una palabra. 
   Este dato es ingresado por comunicación serial y la respuesta del mismo de igual manera. 
   

*/
String text; //Cadena de texto para los datos receptados
//String textlow;
int tam; //Tamaño de la cadena de texto
int i = 0; //Contador
int alph = 0; //Contador para el número de vocales
void setup() {
  Serial.begin(9600); //Configuracion Cx serial
  Serial.println("Ingrese la palabra:"); //Indica la forma de ingreso
}

void loop() {
  if (Serial.available() > 0) { //Determina si hay datos en la Cx
    text = Serial.readString(); //Lee los datos
    //textlow = text.toUpperCase();
    tam = text.length(); //Extrae el tamaño de la cadena ingresada
    char vector [tam]; //Define un vector con el tamaño e la cadena
    text.toCharArray(vector, tam + 1); //Convierte el String a un vector char
    for (; i < tam; i++) { //Recorre el array char
      switch (vector[i]) { //Dertemina y cuenta vocales mayúsculas y minúsculas
        case 'a':
          alph++;
          break;
        case 'e':
          alph++;
          break;
        case 'i':
          alph++;
          break;
        case 'o':
          alph++;
          break;
        case 'u':
          alph++;
          break;
        case 'A':
          alph++;
          break;
        case 'E':
          alph++;
          break;
        case 'I':
          alph++;
          break;
        case 'O':
          alph++;
          break;
        case 'U':
          alph++;
          break;
      }
    }
    Serial.print("Su palabra: "); //Presenta los resultados
    Serial.println(text); //Texto ingresado
    Serial.print("Numero de vocales: ");
    Serial.println(alph); //Número de vocales ingresadas
  }
}
