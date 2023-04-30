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
const int rs = 14, en = 12, d4 = 33, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(14,12,33,25,26,27);


void setup() {
  lcd.begin(20, 4);
}
 
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("TST ISPC Cohorte2022");
  lcd.setCursor(0, 1);
  lcd.print("Sistemas de control");
  lcd.setCursor(0, 3);
  lcd.print("Proyecto 1 Grupo 1");
  delay(2000);
  lcd.clear();
  delay(1000); 
}