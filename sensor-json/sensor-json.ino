// Get humidity (in Percent) and temperature (in Celsius) from DHT22 
// and soild humidity from FC-28 sensor (with contrller board) 
// and output as JSON
// over serial / USB connection
// by Tobias Abarbanell
// Inspired by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // 2 digital - what pin we're connected to
#define SOILHUMIDITYPIN 0 //A0 analog

#define DHTINTERVAL 2000 // milliseconds
#define SOILINTERVAL 30 // multiplied with DHTINTERVAL, so it is 60sec

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
int soilCounter = 0;
int soilLastVal = SOILINTERVAL;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("{ \"err\": \"Failed to read from DHT sensor!\" }");
    return;
  }

  // we do not want to read soil humidity too often. In fact, we will later add code and wiring to only 
  // power up the soil probe for measurements. this should reduce corrosion on the probe.
  if (soilCounter == SOILINTERVAL) {
     soilCounter = 0;
     soilLastVal = analogRead(SOILHUMIDITYPIN);
  }
  soilCounter++;

  // output a json object with the data
  Serial.print("{\"humidity\": ");
  Serial.print(h);
  Serial.print(", ");
  Serial.print("\"temperature\": ");
  Serial.print(t);
  Serial.print(", \"soil\": ");
  Serial.print(soilLastVal);
  Serial.println("}");
}

