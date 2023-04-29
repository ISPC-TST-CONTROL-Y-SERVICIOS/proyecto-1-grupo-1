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
#define DHTPIN 4
#define DHTTYPE DHT11


const int rs = 14, en = 12, d4 = 33, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(14,12,33,25,26,27);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  lcd.begin(20, 4);
  dht.begin();
}
 
void loop() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura = ");
  float t = dht.readTemperature();
      if (isnan(t)) {
      lcd.print("Failed to read from DHT sensor!");
      return;
    }
  lcd.print(t);

  delay(2000);
  lcd.clear();
  delay(1000); 
}


/*
void loop() {
  // Wait for a time between measurements
  if ((millis() - timerDHT) > TIMEDHT) {
    // Update the timer
    timerDHT = millis();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(false);

    // Check if any reads failed and exit early (to try again)
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // Where: HIGH = Temperature, LOW = Humidity
    if (digitalRead(SW1TPIN) == LOW) {
      Serial.print(F("Temperature: "));
      Serial.println(t);
    } else {
      Serial.print(F("% Humidity: "));
      Serial.println(h);
    }
  }
}*/
