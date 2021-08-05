// M1.T3C

const uint8_t led1Pin = 12;
const uint8_t led2Pin = 11;
const uint8_t sensor1Pin = 2;
const uint8_t sensor2Pin = 3;

// init the led state
uint8_t led1State = LOW;
uint8_t led2State = LOW;


void setup()
{
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);     
  pinMode(sensor1Pin, INPUT);  
  pinMode(sensor2Pin, INPUT);   
  
  attachInterrupt(digitalPinToInterrupt(sensor1Pin), handleMotionDetected1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), handleMotionDetected2, CHANGE);

  Serial.begin(9600);
}

void loop()
{
  // Looping anyways to see interrupts work when polling
  //Serial.println("Looping....");
  delay(1000);
}


// Because the ISR method cannot have any parameters or return anything
// I created two methods to do the same thing but for different sensors and leds

void handleMotionDetected1()
{
  if (led1State == LOW)
  {
  	led1State = !led1State;
  	digitalWrite(led1Pin, led1State);
  	Serial.println("Motion Detected on sensor-1, Turning led-1 on");
  }
  else
  {
    led1State = !led1State;
  	digitalWrite(led1Pin, led1State);
  	Serial.println("Turning led-1 off");
  
  }
}

void handleMotionDetected2()
{
  if (led2State == LOW)
  {
  	led2State = !led1State;
  	digitalWrite(led2Pin, led2State);
  	Serial.println("Motion Detected on sensor-2, Turning led-2 on");
  }
  else
  {
    led2State = !led2State;
  	digitalWrite(led2Pin, led2State);
  	Serial.println("Turning led-2 off");
  
  }
}
