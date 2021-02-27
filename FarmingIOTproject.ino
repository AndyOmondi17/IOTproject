const int dry = 578;
const int wet = 298;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop(){
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(A0);
//  Sensor range 310-578
// Translate this into a percentage from 0%-100%
  int percentageMoisture = map(sensorVal,wet,dry,100,0);

// Serial.println(sensorVal); gives us the actual value gotten by the senosr range
  Serial.println(percentageMoisture);
   Serial.print("Moisture percentage is ");
  delay(100);
}
