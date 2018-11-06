/*
   UTN FICA CIERCOM
   Autor: Mateo Tito
   Deber de Sistemas Microprocesados
   Contador medienta un pulsador se aumente el valor (1 al 40) 
   y mediante otro pulsador se resta ese valor

   Componentes usados: 2 displays ánodo común (unidades y decenas),
   un decodificador BCD 7447, 2 pulsadores.
*/
int A = 5; //Bit menos significativo
int B = 4;
int C = 3;
int D = 2; //Bit más significativo
int b1 = 6; //Pulsador 1
int b2 = 7; //Pulsador 2
int i = 0; //Variable contador
int dec = 9; //salida para display decenas
int uni = 8; //salida para display unidades
int decenas;//variables decenas y unidades
int unidades;
void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(dec,OUTPUT);
  pinMode(uni,OUTPUT);
}

void loop() {
  if (digitalRead(b1) == HIGH) { //Cuenta ascendente
    delay(200); //Delay antirebotes
    if (i < 40) { //Solo permite aumentar hasta 40
      i++;
      decenas = i/10; 
      unidades = i - (decenas*10);
    }
  }
  else if (digitalRead(b2) == HIGH) { //Cuenta descendente
    delay(200); //Delay anti rebotes
    if (i > 0) { //Solo permite reducir hasta 0
      i--;
      decenas = i/10;
      unidades = i - (decenas*10);
    }
  }
  digitalWrite(uni,HIGH); //Enciende unidades
  digitalWrite(dec,LOW);
  contador(unidades);
  delay(100); //Retardo poco perceptible
  digitalWrite(uni,LOW);
  digitalWrite(dec,HIGH); //Enciende decenas
  contador(decenas);
  delay(100); //Retardo poco perceptible
}
void contador(int j) { //Método para enceder display
  switch (j) {
    case 0://Número 0 binario
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 1://Número 1 binario
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 2://Número 2 binario
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 3://Número 3 binario
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);
      break;
    case 4://Número 4 binario
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 5://Número 5 binario
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 6://Número 6 binario
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 7://Número 7 binario
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);
      break;
    case 8://Número 8 binario
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,HIGH);
      break;
    case 9://Número 9 binario
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,HIGH);
      break;
  }
}
