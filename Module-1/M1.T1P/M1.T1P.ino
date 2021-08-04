// M1.T1P

int ledPin = 13;
int sensorPin = 2;

void setup()
{
 pinMode(ledPin, OUTPUT);     
 pinMode(sensorPin, INPUT);     
 Serial.begin(9600);
}

void loop()
{
  int sensorStatus = digitalRead(2);
  Serial.print("Motion Sensor Value: ");
  Serial.println(sensorStatus);
  
  if (sensorStatus == 1)
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion Detected, LED: ON "); 
  }
    
  else 
  {
    digitalWrite(ledPin, LOW);
    Serial.println("No Change detected, LED: OFF ");
  }

  delay(1000);
}