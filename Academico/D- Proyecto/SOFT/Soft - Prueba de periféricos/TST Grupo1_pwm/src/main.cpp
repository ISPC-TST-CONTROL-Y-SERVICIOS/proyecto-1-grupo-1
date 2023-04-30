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

int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int ciclo = 0;
int ciclo1 = 0;
const int rs = 14, en = 12, d4 = 33, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(14,12,33,25,26,27);
 
void setup() {
  lcd.begin(20, 4);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(23, ledChannel);

}
 
void loop() {
 
  for (int ciclo = 0; ciclo <= 255; ciclo++) {
    //ledcWrite(ledChannel, ciclo);
    //delay(10);
    int rev = map (ciclo,0,255,0,100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turbina = ");
    lcd.print(rev);
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("Ciclo util= ");
    lcd.print(ciclo);
    delay(150);
    ciclo1 = 255 - ciclo;
    ledcWrite(ledChannel, ciclo1);
  }
 delay(5000);
  for (int ciclo = 255; ciclo >= 0; ciclo--) {
    //ledcWrite(ledChannel, ciclo);
    int rev = map (ciclo,0,255,0,100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turbina = ");
    lcd.print(rev);
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("Ciclo util= ");
    lcd.print(ciclo);
    delay(150);
    ciclo1 = 255 - ciclo;
    ledcWrite(ledChannel, ciclo1);

}
 delay(5000);
}
 
