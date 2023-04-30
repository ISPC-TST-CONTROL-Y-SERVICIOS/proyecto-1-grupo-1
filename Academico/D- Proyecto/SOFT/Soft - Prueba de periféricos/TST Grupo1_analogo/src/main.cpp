/*
 * TST proyecto 1 Grupo1
 * Integrantes 
 * Andrés Montaño -- Especialista en modelado y control de sistemas
 * Emma Gutierrez -- Rol Especialista en modelado y control de sistemas
 * Federico Birge -- Scrum Master
 * Leonardo Gonzalez -- Especialista en programación
 * Mario Gonzalez -- Especialista en electrónica y circuitos
 * Pedro Rojo -- Especialista en programación
 * Esteban Carrizo -- Product Owner
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#define DHTPIN_1 0
#define DHTPIN_2 4
#define DHTPIN_3 15
int pote1 = 36;
int pote2 = 34;
int pote3 = 39;

#define DHTTYPE DHT11


const int rs = 14, en = 12, d4 = 33, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(14,12,33,25,26,27);


void setup() {
  lcd.begin(20, 4);
  analogReadResolution(12);
}
 
void loop() {

  lcd.clear();

  float t1  = (analogRead(pote1)/10);
  float t2  = analogRead(pote2);
  float t3  = analogRead(pote3);

  float ta = map(t1, 0,409, 0,50);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SetPoint1 = ");
  lcd.print(ta,1);

  lcd.setCursor(0, 1);
  lcd.print("SetPoint2 = ");
  lcd.print(t2,1);

  lcd.setCursor(0, 2);
  lcd.print("SetPoint3 = ");
  lcd.print(t3,1);
  delay(100); 
}