// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 8     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(11, 12, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read Humidity as percent
  float h = dht.readHumidity();
  // Read soil moisture as units
  float m = analogRead(A0);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f) || isnan(m)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.print("ERROR TO READ SENSORS");    
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Convert the moisture value in purcentage 
  m = ((520 - m) * 100) / 260;
  // 0 is the max wet
  if (m < 0)
  {
    m = 0;
  }
  // 100 is the max dry
  else if (m > 100)
  {
    m = 100;
  }
  
  //Serial.println("===============================================");
  //
  //Serial.print(F("Moisture: "));
  //Serial.print(m);
  //Serial.println(" units");
  //
  //Serial.print(F("Humidity: "));
  //Serial.print(h);
  //Serial.println("%");
  //
  //Serial.print(F("Temperature celsius: "));
  //Serial.print(t);
  //Serial.println("°C");
  //
  //Serial.print(F("Temperature fahrenheit: "));
  //Serial.print(f);
  //Serial.println("°F");
  //
  //Serial.print(F("Heat index celsius: "));
  //Serial.print(hic);
  //Serial.println("°C");
  //
  //Serial.print(F("Heat index fahrenheit: "));
  //Serial.print(hif);
  //Serial.println("°F");
  //
  //Serial.println("===============================================");
  //Serial.println(" ");

  lcd.setCursor(9, 0);
  lcd.print("H :");

  lcd.setCursor(0, 1);
  lcd.print("Tc:");
  lcd.setCursor(3, 1);
  lcd.print(int(t));
  lcd.setCursor(6, 1);
  lcd.print("C");
  
  lcd.setCursor(9, 1);
  lcd.print("Tf:");
  lcd.setCursor(12, 1);
  lcd.print(int(f));
  lcd.setCursor(15, 1);
  lcd.print("F"); 
  
  lcd.setCursor(0, 0);
  lcd.print("M :");
  lcd.setCursor(3, 0);
  lcd.print(int(m));
  lcd.setCursor(6, 0);
  lcd.print("%");
  
  lcd.setCursor(9, 0);
  lcd.print("H :");
  lcd.setCursor(12, 0);
  lcd.print(int(h));
  lcd.setCursor(15, 0);
  lcd.print("%");

  delay(5000);
  lcd.clear();
}
