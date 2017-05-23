/******************************************************************************
  Project  : NECTEC IoT Camp 2016
  Compiler : Arduino 1.6.7
  Board    : ESPresso Lite V2
  Device   : DHT11
  Author   : Chiang Mai Maker Club
*******************************************************************************/

#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // initialize Serial port
  Serial.begin(115200);

  // initialize DHT
  dht.begin();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // print out the value you read:
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("*C \tHumidity: ");
  Serial.print(h);
  Serial.print("% \tFahrenheit:");
  Serial.print(f);
  Serial.println("*F");
  delay(200);
}
