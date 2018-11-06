/*
   UTN FICA CIERCOM
   Autor: Mateo Tito
   Deber de Sistemas Microprocesados
   Contador automático hasta 200 mediante displays multiplexados

   Componentes usados: 3 displays ánodo común (unidades, decenas y centenas),
   un decodificador BCD 7447.
*/
int A = 5; //Bit menos significativo
int B = 4;
int C = 3;
int D = 2; //Bit más significativo
int i = 0; //Variable para contador
int uni = 8; //Salida que activa display unidades
int dec = 9; //Salida que activa display decenas
int cent = 10; //Salida que activa display centenas
int decenas; //Variables para cada display
int unidades;
int centenas;
void setup() { //Todos los pines serán salidas
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(dec,OUTPUT);
  pinMode(uni,OUTPUT);
  pinMode(cent,OUTPUT);
}

void loop() {
  if (i < 200) { //La cuenta llega hasta 200
    centenas = i/100;
    decenas = (i/10) - (centenas*10);
    unidades = i - (decenas*10) - (centenas*100);
    i++;
  } else {
    i = 0; //Se resetea luego de llegar a 200
  }
//Multiplexación de los displays
  digitalWrite(uni,HIGH); //Primero se enciende unidades
  digitalWrite(dec,LOW);
  digitalWrite(cent,LOW);
  disp(unidades);
  delay(100); //Retardo muy corto para ser perceptible
  digitalWrite(uni,LOW);
  digitalWrite(dec,HIGH); //Luego se enciende decenas
  digitalWrite(cent,LOW);
  disp(decenas);
  delay(100);
  digitalWrite(uni,LOW);
  digitalWrite(dec,LOW); //Finalmente se enciende centenas
  digitalWrite(cent,HIGH);
  disp(centenas);
  delay(100);
}
void disp(int j) {
  switch (j) {
    case 0://Número 0
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 1://Número 1
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 2://Número 2
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 3://Número 3
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 4://Número 4
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 5://Número 5
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 6://Número 6
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 7://Número 7
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 8://Número 8
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,HIGH);
      break;
    case 9://Número 9
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,HIGH);
      break;
  }
}
