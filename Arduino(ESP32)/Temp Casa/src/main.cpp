#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHTesp.h>

//declaramos pines
const int DHT_Hab1 = 15; //sensor 1
const int DHT_Hab2 = 18; //sensor 2
const int DHT_Hab3 = 19; //sensor 3
const int pote1 = 32; // potenciometro para setear sensor 1
const int pote2 = 35; // potenciometro para setear sensor 2
const int pote3 = 34; // potenciometro para setear sensor 3
const int ledRojo_1 = 33; // pin de salida para el led rojo 1
const int ledAzul_1 = 25; // pin de salida para el led azul 1
const int ledRojo_2 = 26;  // pin de salida para el led rojo 2
const int ledAzul_2 = 27;  // pin de salida para el led azul 2
const int ledRojo_3 = 14;  // pin de salida para el led rojo 3
const int ledAzul_3 = 12;  // pin de salida para el led azul 3
    
// Constantes del controlador
double errorPasH_1 = 0; // suma de errores anteriores para el controlador 1
double errorPasH_2 = 0; // suma de errores anteriores para el controlador 2
double errorPasH_3 = 0; // suma de errores anteriores para el controlador 3
float U1, U2, U3;       // señal de control para los actuadores
int Kp = 7;             // constante proporcional
int Ki = 3;             // constante integral
float H; 

int TiempoMuestreo = 1;   // tiempo de muestreo en miliseg
unsigned long pasado = 0; // tiempo pasado para asegurar el tiempo de muestreo
unsigned long ahora;  // tiempo actual

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 20, 4);
DHTesp dhtHabitacion1;
DHTesp dhtHabitacion2;
DHTesp dhtHabitacion3;

/*funcion del controlador PI

   RECIBE POR REFERENCIA:
   - sensor: cada sensor de temperatura
   - errorPasH: la suma de errores anteriores para cada sensor

   RECIBE POR VALOR:
   - LCD_row: fila del LCD donde se mostrara la temperatura, tambien sirve para identificar el sensor
   - temp_set: temperatura seteada por el usuario con el potenciometro
   - Kp: constante proporcional
   - Ki: constante integral
   - TiempoMuestreo: tiempo de muestreo en miliseg

*/
float PI_Controller(DHTesp &sensor, int LCD_row, float &temp_set, float Kp, float Ki, int TiempoMuestreo, double &errorPasH)
{
  double errorH;                      // error actual
  //float H;                            // señal de control
  TempAndHumidity  data = sensor.getTempAndHumidity();
  //delay(250);                         // Esperar un segundo antes de leer la temperatura de nuevo
  ahora = millis();                   // tiempo actual
  int CambioTiempo = ahora - pasado;  // dif de tiempo actual - pasado
  if (CambioTiempo >= TiempoMuestreo) // si el tiempo de muestreo se cumple
  {
   // errorH = temp_set - t;      
    errorH = temp_set - data.temperature;                         // calculo error actual
    errorPasH = errorH * TiempoMuestreo + errorPasH; // suma acumulativa de error
    H = ((Kp * errorH) + (Ki * errorPasH));          // calculo de la señal de control
    pasado = ahora;                                  // Actualiza tiempo
    //Serial.print(" H " + String(H));
    int PWM_value = constrain(H, -255, 255); // Convertir U a un valor entre -255 y 255
    if (PWM_value < 50 && PWM_value > -50) // si el valor de la señal de control es menor a 50
    {
      PWM_value = 0;
    }
    LCD.setCursor(0, LCD_row);
    LCD.print("Temp: " + String(data.temperature) + " C");
    return PWM_value; // retornamos la señal de control
  }
  return 0;
}


void setup()
{
  Serial.begin(9600);
  // inicializo pines de salida
  pinMode(ledRojo_1, OUTPUT);
  pinMode(ledAzul_1, OUTPUT);
  pinMode(ledRojo_2, OUTPUT);
  pinMode(ledAzul_2, OUTPUT);
  pinMode(ledRojo_3, OUTPUT);
  pinMode(ledAzul_3, OUTPUT);
  
 //  inicio LCD
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  
  // declaro senseores
  dhtHabitacion1.setup(DHT_Hab1, DHTesp::DHT22);
  dhtHabitacion2.setup(DHT_Hab2, DHTesp::DHT22);
  dhtHabitacion3.setup(DHT_Hab3, DHTesp::DHT22);
  
}

void loop()
{
  // SENSOR 1
  LCD.clear(); //borramos los datos del LCD
  LCD.setCursor(0, 0);
  LCD.print("Habitacion 1");
  int valuPote1 = analogRead(pote1);                                       // lectura del potenciometro
  float ref1 = map(valuPote1, 0, 4096, 16, 30); //mapeo el potenciometro en rando de 16 a 30
  LCD.setCursor(0, 2);
  LCD.print("Temp Set " + String(ref1));
 // Serial.println("Temp Set " + String(ref1));
 
  U1 = PI_Controller(dhtHabitacion1, 1, ref1, Kp, Ki, TiempoMuestreo, errorPasH_1); // seña de control para el sensor 1
  Serial.println("Error PI H1: "+String(H));
  Serial.println("PWM H1: "+String(U1));
  if (U1 > 0)// si la señal de control es mayor a 0 necesito calefaccion
  {
    LCD.setCursor(0, 3);
    LCD.print("Calefaccion");
    //Serial.println("CALEFFACCION");
    analogWrite(ledRojo_1, U1); //"Actua calefaccion"
    analogWrite(ledAzul_1, 0);  // mantego apagada la refrigeracion
  }
  else // si la señal de control es menor a 0 necesito refrigeracion
  {
    LCD.setCursor(0, 3);
    LCD.print("Refrigeracion");
    //Serial.println("REFRIGERACION");
    analogWrite(ledAzul_1, U1 * (-1)); //"actua refrigeracion"
    analogWrite(ledRojo_1, 0);         // mantego apagada la calefaccion
  }
delay(3000);
   //SENSOR 2
   LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Habitacion 2");
  int valuPote2 = analogRead(pote2);
  float ref2 = map(valuPote2, 0, 4096, 16, 30);
  LCD.setCursor(0, 2);
  LCD.print("Temp Set " + String(ref2));
  U2 = PI_Controller(dhtHabitacion2, 1, ref2, 2, 2, TiempoMuestreo, errorPasH_2);
  Serial.println("Error PI H2: "+String(H));
  Serial.println("PWM H2: "+String(U2));
  if (U2 > 0)
  {
    LCD.setCursor(0, 3);
    LCD.print("Calefaccion");
    //Serial.println("Actua calefaccion");
    analogWrite(ledRojo_2, U2); //"Actua calefaccion"
    analogWrite(ledAzul_2, 0);
  }
  else
  {
    LCD.setCursor(0, 3);
    LCD.print("Refrigeracion");
    //Serial.println("actua refrigeracion");
    analogWrite(ledAzul_2, U2 * (-1)); //"actua refrigeracion"
    analogWrite(ledRojo_2, 0);
    
  }
  delay(3000);

  // SENSOR 3
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Habitacion 3");
  int valuPote3 = analogRead(pote3);
  float ref3 = map(valuPote3, 0, 4096, 16, 30);
  LCD.setCursor(0, 2);
  LCD.print("Temp Set " + String(ref3));
  U3 = PI_Controller(dhtHabitacion3, 1, ref3, 10, 10, TiempoMuestreo, errorPasH_3);
  Serial.println("Error PI H3: "+String(H));
  Serial.println("PWM H3: "+String(U3));
  if (U3 > 0)
  {
    LCD.setCursor(0, 3);
    LCD.print("");
    LCD.print("Calefaccion");
    analogWrite(ledRojo_3, U3); //"Actua calefaccion"
    analogWrite(ledAzul_3, 0);
    //Serial.println("Actua calefaccion");
  }
  else
  {
    LCD.setCursor(0, 3);
    LCD.print("Refrigeracion");
    analogWrite(ledAzul_3, U3 * (-1)); //"actua refrigeracion"
    analogWrite(ledRojo_3, 0);
    //Serial.println("actua refrigeracion");
  }
  Serial.println("---------------------------------");
  
 delay(3000);
}