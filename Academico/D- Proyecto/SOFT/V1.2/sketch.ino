
#include "DHTesp.h"
#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 20,4);
const int DHT_Hab1 = 15;
const int DHT_Hab2= 18;
const int DHT_Hab3= 19;
double errorH1, errorH2, errorH3; //error 
double errorPasH1, errorPasH2, errorPasH3; //suma de errores
float H1, H2, H3; //señal de control
double U1, U2, U3; //Salida PWM
int TiempoMuestreo=1; //tiempo de muestreo en miliseg
long TiempoTrancurrido=0;
unsigned long pasado=0; //tiempo pasado para asegurar el tiempo de muestreo
unsigned long ahora;

//Constantes del controlador
int Kp=3;
int Ki=5;
float ref = 24.00; //valor seteado

DHTesp dhtHabitacion1;
DHTesp dhtHabitacion2;
DHTesp dhtHabitacion3;

void PI_H1(){
  TempAndHumidity  data = dhtHabitacion1.getTempAndHumidity();
  Serial.println("Temp Habitacion 1: " + String(data.temperature, 2) + "°C");
  delay(250); // Esperar un segundo antes de leer la temperatura de nuevo
  ahora=millis(); //tiempo actual
  TiempoTrancurrido= ((ahora - pasado)/1000); //dif de tiempo actual - pasado
  //Serial.print("TiempoTrancurridoo");
  //Serial.println(TiempoTrancurrido);
  if (TiempoTrancurrido>= TiempoMuestreo){
  errorH1 = data.temperature -ref; //Error actual
  //Serial.print("Error Actual ");
  //Serial.println(errorH1);
  errorPasH1 += errorH1 * TiempoTrancurrido; //suma acumulativa de error
  //Serial.print("Suma errores ");
  //Serial.println(errorPasH1);
  H1=((Kp*errorH1)+(Ki*errorPasH1));
  U1=constrain(H1,0,255); //limito U para PWM
  if(U1<50){ //apago el equipo para su proteccion
    U1=0;
  }
  pasado=ahora; //Actualiza tiempo
  Serial.print("Error PI H1: ");
  Serial.println(H1);
  Serial.print("PWM H1= ");
  Serial.println(U1);
  Serial.println();
  //mostramos valores en LCD
  LCD.setCursor(0, 1);
  LCD.print("Temp Hab 1: " + String(data.temperature, 2) + " C");
  delay(1000);
  }
}

void PI_H2(){
  TempAndHumidity  data = dhtHabitacion2.getTempAndHumidity();
  Serial.println("Temp Habitacion 2: " + String(data.temperature, 2) + "°C");
  delay(250); // Esperar un segundo antes de leer la temperatura de nuevo
  ahora=millis(); //tiempo actual
  TiempoTrancurrido= ((ahora - pasado)/1000); //dif de tiempo actual - pasado
  if (TiempoTrancurrido>= TiempoMuestreo){
  errorH2 = data.temperature -ref; //Error actual
  errorPasH2 += errorH2 * TiempoTrancurrido; //suma acumulativa de error
  H2=((Kp*errorH2)+(Ki*errorPasH2));
  U2=constrain(H2,0,255); //limito U para PWM
  if(U2<50){ //apago el equipo para su proteccion
    U2=0;
  }
  pasado=ahora; //Actualiza tiempo
  Serial.print("Error PI H2: ");
  Serial.println(H2);
  Serial.print("PWM H2= ");
  Serial.println(U2);
  Serial.println();
  //mostramos valores en LCD
  LCD.setCursor(0, 2);
  LCD.print("Temp Hab 2: " + String(data.temperature, 2) + " C");
  delay(1000);
  }
}

void PI_H3(){
  TempAndHumidity  data = dhtHabitacion3.getTempAndHumidity();
  Serial.println("Temp Habitacion 3: " + String(data.temperature, 2) + "°C");
  delay(250); // Esperar un segundo antes de leer la temperatura de nuevo
  ahora=millis(); //tiempo actual
  TiempoTrancurrido= ((ahora - pasado)/1000); //dif de tiempo actual - pasado
  if (TiempoTrancurrido>= TiempoMuestreo){
  errorH3 = data.temperature -ref; //Error actual
  errorPasH3 += errorH3 * TiempoTrancurrido; //suma acumulativa de error
  H3=((Kp*errorH3)+(Ki*errorPasH3));
  U3=constrain(H3,0,255); //limito U para PWM
  if(U3<50){ //apago el equipo para su proteccion
    U3=0;
  }
  pasado=ahora; //Actualiza tiempo
  Serial.print("Error PI H3: ");
  Serial.println(H3);
  Serial.print("PWM H3= ");
  Serial.println(U3);
  Serial.println();
  //mostramos valores en LCD
  LCD.setCursor(0, 3);
  LCD.print("Temp Hab 3: " + String(data.temperature, 2) + " C");
  delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT);
  //declaro senseores
  dhtHabitacion1.setup(DHT_Hab1, DHTesp::DHT22);
  dhtHabitacion2.setup(DHT_Hab2, DHTesp::DHT22);
  dhtHabitacion3.setup(DHT_Hab3, DHTesp::DHT22);
  //inicio LCD
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Temp Casa");
}


void loop() {

  PI_H1();
  PI_H2();
  PI_H3();
  
 delay(4000);
 
  }

