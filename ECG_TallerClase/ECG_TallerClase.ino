#define ARM_MATH_CM3 //Librería MATH del due
#include <arm_math.h>
#define tam_sig 640
#define tam_impl 29
extern float32_t InputSignal[tam_sig];
extern float32_t Impulse_response[tam_impl];
float32_t OutputSignal [tam_sig];
float32_t signalOut [tam_sig + tam_impl]; //Convolución salida
float32_t promedio = 0;
float32_t des_estand;
float32_t var;
uint32_t i = 0;
float32_t REX [tam_sig / 2];
float32_t IMX [tam_sig / 2];

/*
  Incluyen librerias
  Definen variables
  Metodos
*/
void setup() {
  Serial.begin(9600);
  //Promedio
  arm_mean_f32( & InputSignal[0], tam_sig, &promedio); //Señal desde 0, tamaño
  Serial.print("EL PROMEDIO ES: ");
  Serial.println(promedio);
  //Varianza
  arm_var_f32( & InputSignal[0], tam_sig, &var);
  Serial.print("LA VARIANZA ES: ");
  Serial.println(var);
  //Desviación estándar
  des_estand = sqrt(var);
  Serial.print("LA DESVIACION ES: ");
  Serial.println(des_estand);

}

void loop() {
  //Comentar las opciones que no se usarán
  //Convolucion con librería
  arm_conv_f32(&InputSignal[0], tam_sig, &Impulse_response[0], tam_impl, &signalOut[0]);
  plot_sig_conv(signalOut, tam_sig + tam_impl);
  
  //Primera diferencia
  running_res(&InputSignal [0], &OutputSignal [0], tam_sig );
  plot_sig();
  
  //Suma acumulativa
  running_sum(&InputSignal [0], &OutputSignal [0], tam_sig );
  plot_sig();
  
  //DFT
  cal_tdf (&InputSignal[0], &REX [0], &IMX [0], tam_sig); //Cálculo
  get_tdf (); //Asignación
  plot_signal (); //Gráfico
}
//Grafica las sumas y restas
void plot_sig () {
  uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    Serial.print(InputSignal [i] + 5);
    Serial.print(",");
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}
//Grafica la convolucion
void plot_sig_conv (float32_t *sig_entrada, uint32_t tam_signal) {
  uint32_t i;
  for (i = 0; tam_signal; i++) {
    Serial.println(sig_entrada[i] * 100);
    delay(10);
  }
}

void running_sum (float32_t *input, float32_t *output, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam; i++) {
    output [i] = input [i] + output [i - 1]; //Deja la de 1Khz y pasa la de 15Khz
  }
}

void running_res (float32_t *input, float32_t *output, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam; i++) {
    output [i] = input [i] - input [i - 1]; //Deja la de 15Khz y pasa la de 1Khz
  }
}

void cal_tdf (float32_t *input_signal, float32_t *sig_rex, float32_t *sig_imx, uint32_t tam) {
  uint32_t i, j, k;
  for (j = 0; j < tam / 2; j++) {
    sig_rex[j] = 0;
    sig_imx[j] = 0;
  }
  for (k = 0; k < tam / 2; k++) { //Almacenar en imx y rex
    for (i = 0; i < tam; i++) { //Sumatoria de todos los componentes de sig_input
      sig_rex [k] = sig_rex [k] + input_signal [i] * cos(2 * PI * k * i / tam);
      sig_imx [k] = sig_imx [k] - input_signal [i] * sin(2 * PI * k * i / tam);
    }
  }
}

void get_tdf (void) { //Obetener transformada de fourier discreta
  uint32_t i;
  for (i = 0; i < tam_sig / 2; i++) {
    OutputSignal [i] = sqrt(pow(REX[i], 2) + pow(IMX[i], 2));
  }
}

void plot_signal () {
  uint32_t i;
  for (i = 0; i < tam_sig / 2; i++) {
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}

