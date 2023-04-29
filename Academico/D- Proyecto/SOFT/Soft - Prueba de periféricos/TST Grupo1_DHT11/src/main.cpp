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
