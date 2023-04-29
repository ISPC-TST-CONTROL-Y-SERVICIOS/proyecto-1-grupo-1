/*TST proyecto 1 Grupo1
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
#include <DHT.h>
#define DHTPIN_1 0
#define DHTPIN_2 4
#define DHTPIN_3 15

#define DHTTYPE DHT11


const int rs = 14, en = 12, d4 = 33, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(14,12,33,25,26,27);
DHT dht1(DHTPIN_1, DHTTYPE);
DHT dht2(DHTPIN_2, DHTTYPE);
DHT dht3(DHTPIN_3, DHTTYPE);


void setup() {
  lcd.begin(20, 4);
  dht1.begin();
  dht2.begin();
  dht3.begin();
}
 
void loop() {

  lcd.clear();

  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();
  float t3 = dht3.readTemperature();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp-1 = ");
  lcd.print(t1);
  lcd.setCursor(0, 1);
  lcd.print("Temp-2 = ");
  lcd.print(t2);
  lcd.setCursor(0, 2);
  lcd.print("Temp-2 = ");
  lcd.print(t3);

  delay(2000);
  lcd.clear();
  delay(1000); 
}
