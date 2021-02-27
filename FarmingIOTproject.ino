#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
const int dry = 578;
const int wet = 298;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop(){
  delay(2000);

  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(A0);
//  Sensor range 310-578
// Translate this into a percentage from 0%-100%
  int percentageMoisture = map(sensorVal,wet,dry,100,0);

// Serial.println(sensorVal); gives us the actual value gotten by the senosr range
//  Serial.println(percentageMoisture("% "));
//   Serial.print("% ");
  Serial.print(F("Soil Moisture: "));
  Serial.print(percentageMoisture);
//  delay(2000);


  // Wait a few seconds between measurements.
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("% Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
//  Serial.print(f);
  Serial.print(F(" Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
//  Serial.print(hif);
  Serial.println(F(""));
}
