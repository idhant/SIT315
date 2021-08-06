// M1.T4D

// Helpful resources 

// Video about internal ISRS and groups 
// https://www.youtube.com/watch?v=ZDtRWmBMCmw&ab_channel=Electronoobs

// Video about timer interrupts
// https://www.youtube.com/watch?v=2kr5A350H7E&ab_channel=SparkFunElectronics

// Atmega328P datasheet sections

// For more PCINT ISR
// 12.2.4 PCICR – Pin Change Interrupt Control Register
// 12.2.6 PCMSK2 – Pin Change Mask Register 2

// For timer ISR
// 15.11.2 TCCR1B – Timer/Counter1 Control Register B


// Start of code

// 3 leds for 3 sensors and 1 for timer
const uint8_t led1Pin = 12;
const uint8_t led2Pin = 11;
const uint8_t led3Pin = 10;


// Timer values
const uint8_t timeLedPin = 13;

const uint16_t t1_load = 0;

// compare value to blink led every 0.5 seconds
// this is the value we want to compare the timer1 ticks by 
// We get this by having a 256 prescaler
const uint16_t t1_comp = 31250; 


// Controled by PCMSK2 register 
// Pins belong in the port D

// PCINT20 
const uint8_t sensor1Pin = 4;

// PCINT21 
const uint8_t sensor2Pin = 5;

// PCINT22 
const uint8_t sensor3Pin = 6;

void setup()
{
  Serial.begin(9600);
  
  // Sensor ISR related setup
  
  // defining pinmodes
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  
  pinMode(sensor1Pin, INPUT_PULLUP);  
  pinMode(sensor2Pin, INPUT_PULLUP);   
  pinMode(sensor3Pin, INPUT_PULLUP);  
  
  // Enabling individual pin pinterrupts by setting the bit value to 1
  PCMSK2 |= bit (PCINT20); // Pin D04, Sensor 1
  PCMSK2 |= bit (PCINT21); // Pin D05, Sensor 2
  PCMSK2 |= bit (PCINT22); // Pin D06, Sensor 3
  
  PCICR  |= bit (PCIE2);   // enable pin change interrupts for D04 to D06
  
  
  // Timer1 ISR related setup
  
  pinMode(timeLedPin, OUTPUT);
  
  // Reseting the timer1 control register A
  TCCR1A = 0;
  
  // Section 15.11.2 Table 15-6
  // Setting the prescaler to 256 by changing relevent bit values
  TCCR1B |= (1 << CS12); // bit value = 1
  TCCR1B &= ~(1 << CS11); // bit value = 0
  TCCR1B &= ~(1 << CS10); // bit value = 0
  
  // Reset timer1 and set compare value to the Output conmpare register
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  // Enable Timer 1 compare interrupt
  TIMSK1 = (1 << OCIE1A);
  
  // enable global interrupts 
  sei();
  
}

void loop ()
{
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(timeLedPin, LOW);
  delay(500);
} 

// ISR function called on the group Vectors
ISR (PCINT2_vect) //D04-06
{
  //Serial.println("ISR triggered");
  
  if(digitalRead(sensor1Pin) == HIGH)
  {
    Serial.println("Sensor-1 Triggered the ISR");
	//Pin D4 triggered the ISR
    
    digitalWrite(led1Pin, HIGH);
    Serial.println("Motion Detected on sensor-1, Turning led-1 on");

  }

  if(digitalRead(sensor2Pin) == HIGH)
  {
    Serial.println("Sensor-2 Triggered the ISR");
	//Pin D5 triggered the ISR
    
    digitalWrite(led2Pin, HIGH);
    Serial.println("Motion Detected on sensor-2, Turning led-2 on");

  }
  
  if(digitalRead(sensor3Pin) == HIGH)
  {
    Serial.println("Sensor-3 Triggered the ISR");
    //Pin D6 triggered the ISR
    
    digitalWrite(led3Pin, HIGH);
    Serial.println("Motion Detected on sensor-3, Turning led-3 on");

  }
  
}

// ISR function called on the timer1 compare vector
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = t1_load;
  //Serial.println("Timer Compare ISR triggered, blinking led");
  digitalWrite(timeLedPin, HIGH);
}


