#include <Timer.h>
#include "dataContainer.h"

// DHT Options
#include "DHT.h"
#define DHTPIN 8     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
Timer timer;

Temperature temperature;
HeatIndex heatIndex;
Humidity humidity;

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(2000);
  setTemperature();
  setHeatIndex();
  setHumidity();
}

void setTemperature() {
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (!isnan(t)) {
      temperature.celsius = t;
  }
  if (!isnan(f)) {
      temperature.fahrenheit = f;
  }
}

void setHeatIndex() {
  if (!isnan(temperature.celsius) && isnan(humidity.percentage)) {
      // Compute heat index in Celsius (isFahreheit = false)
      heatIndex.celsius = dht.computeHeatIndex(temperature.celsius, humidity.percentage, false); 
  }
  
  if (!isnan(temperature.fahrenheit) && isnan(humidity.percentage)) {
      // Compute heat index in Fahrenheit (the default)
      heatIndex.fahrenheit = dht.computeHeatIndex(temperature.fahrenheit, humidity.percentage);
  }
}

void setHumidity() {
  float h = dht.readHumidity();
  if (!isnan(h)) {
    humidity.percentage = h;
  }
}

