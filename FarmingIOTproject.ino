#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
const int dry = 578;
const int wet = 298;

int calibrationTime = 30; 
//the time when the sensor outputs a low impulse long unsigned int lowIn; 
//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int lowIn;
long unsigned int pause = 5000; 
boolean lockLow = true; 
boolean takeLowTime; 
int pirPin = 3;  
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println(F("Sensors Loading"));
  pinMode(pirPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW); //give the sensor some time to calibrate 
  Serial.print("calibrating sensors ");
//  will load for 30 seconds before ending
  for(int i = 0; i < calibrationTime; i++)
  { Serial.print("."); 
    delay(1000); 
  } 
  Serial.println(" done"); 
  Serial.println("Sensors are active"); 
  delay(50); 

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

  if(digitalRead(pirPin) == HIGH)
    { digitalWrite(ledPin, HIGH); //the led visualizes the sensors output pin state 
        if(lockLow){ //makes sure we wait for a transition to LOW before any further output is made: 
            lockLow = false; 
            Serial.println("---"); 
            Serial.print("motion detected at "); 
            Serial.print(millis()/1000); 
            Serial.println(" sec"); 
            delay(50); 
            } takeLowTime = true; 
            } 
            if(digitalRead(pirPin) == LOW)
              { digitalWrite(ledPin, LOW); //the led visualizes the sensors output pin state 
                if(takeLowTime)
                { lowIn = millis(); //save the time of the transition from high to LOW 
                    takeLowTime = false; 
                    //make sure this is only done at the start of a LOW phase 
                } //if the sensor is low for more than the given pause, //we assume that no more motion is going to happen 
                if(!lockLow && millis() - lowIn > pause)
                    { //makes sure this block of code is only executed again after //a new motion sequence has been detected 
                      lockLow = true; 
                      Serial.print("motion ended at "); //output 
                      Serial.print((millis() - pause)/1000); 
                      Serial.println(" sec"); 
                      delay(50); 
                    } 
                }
                 delay(2000);
              }
