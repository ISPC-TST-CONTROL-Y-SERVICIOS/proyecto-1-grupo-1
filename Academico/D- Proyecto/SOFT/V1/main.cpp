#include <Arduino.h>

# Pruebas utilizando LM35
const int pin_lm35 = A5; // El pin analógico conectado a la salida del LM35
double error; //error 
double errorPas=0; //suma de errores
float U; //señal de control
int TiempoMuestreo=1; //tiempo de muestreo en miliseg
unsigned long pasado=0; //tiempo pasado para asegurar el tiempo de muestreo
unsigned long ahora;

//Constantes del controlador
int Kp=5;
int Ki=6.5;
float ref = 23.93; //valor seteado

void setup() {
  Serial.begin(9600); // Iniciar la comunicación serie
  //analogReadResolution(12); // Establecer la resolución de lectura analógica en 12 bits
  pinMode(pin_lm35,INPUT);
}

void loop() {
  // Leer la señal analógica del LM35
  float valor_analogico = analogRead(pin_lm35);

  // Convertir la señal analógica en temperatura
  float temperatura = (valor_analogico * 5 / 1024)/0.01;

  //Imprimir la temperatura en la consola serie
  //Serial.println(valor_analogico);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" grados Celsius");

  delay(250); // Esperar un segundo antes de leer la temperatura de nuevo
  ahora=millis(); //tiempo actual
  int CambioTiempo= ahora - pasado; //dif de tiempo actual - pasado
  if (CambioTiempo>= TiempoMuestreo){
    error =ref - temperatura; //Error actual
    errorPas= error * TiempoMuestreo + errorPas; //suma acumulativa de error
    float P=Kp*error;
    float I=Ki*errorPas;
    U=P+I; //Señal de control
    pasado=ahora; //Actualiza tiempo
    Serial.print("U= ");
    Serial.println(U);

  }

  if (U < -255){
     U=-255;
  }
  if(U>190){
     U=255;

  }
Serial.print("Nueva U= ");
Serial.println(U);
}
