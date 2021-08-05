// M1.T2P

const uint8_t ledPin = 13;
const uint8_t sensorPin = 2;


// init the led state
uint8_t ledState = LOW;


void setup()
{
  pinMode(ledPin, OUTPUT);     
  pinMode(sensorPin, INPUT);   
  
  attachInterrupt(digitalPinToInterrupt(sensorPin), handleMotionDetected, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Looping....");
  delay(1000);
}


void handleMotionDetected()
{
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  Serial.println("Motion Detected, Turning led on");
}
