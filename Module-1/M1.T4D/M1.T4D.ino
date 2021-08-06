// M1.T4D

// Helpful resources 

// Video about internal ISRS and groups 
// https://www.youtube.com/watch?v=ZDtRWmBMCmw&ab_channel=Electronoobs

// Atmega328P datasheet sections
// 12.2.4 PCICR – Pin Change Interrupt Control Register
//12.2.5 PCIFR – Pin Change Interrupt Flag Register
// 12.2.6 PCMSK2 – Pin Change Mask Register 2

// Start of code

// 3 leds for 3 sensors and 1 for timer
const uint8_t led1Pin = 12;
const uint8_t led2Pin = 11;
const uint8_t led3Pin = 10;
const uint8_t led4Pin = 9;


// Controled by PCMSK2 register 
// Pins belong in the port D

// PCINT20 
const uint8_t sensor1Pin = 4;

// PCINT21 
const uint8_t sensor2Pin = 5;

// PCINT22 
const uint8_t sensor3Pin = 6;


// init the led states
uint8_t led1State = LOW;
uint8_t led2State = LOW;
uint8_t led3State = LOW;

//when set there was an interrupt on D4 to D6
volatile byte Flag;


void setup()
{
  Serial.begin(9600);
  
  // defining pinmodes
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(sensor1Pin, INPUT);  
  pinMode(sensor2Pin, INPUT);   
  pinMode(sensor3Pin, INPUT);  
  
  // Enabling individual pin pinterrupts by setting the bit value to 1
  PCMSK2 |= bit (PCINT20); // Pin D04, Sensor 1
  PCMSK2 |= bit (PCINT21); // Pin D05, Sensor 2
  PCMSK2 |= bit (PCINT22); // Pin D06, Sensor 3
  
  PCIFR  |= bit (PCIF2);   // clear any outstanding interrupts
  PCICR  |= bit (PCIE2);   // enable pin change interrupts for D04 to D06
  
}

void loop ()
{
  //have we had an interrupt?
  if (Flag == 1)
  {
    Flag = 0;

    //check for the bit that caused the interrupt
    byte interrupt = checkBit();

    if (interrupt == 4)
    {
      Serial.print("Interrupt called on sensor-1 ");
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
    
    if (interrupt == 5)
    {
      Serial.print("Interrupt called on sensor-2 ");
      if (led2State == LOW)
      {
        led2State = !led2State;
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
    
    if (interrupt == 6)
    {
      Serial.print("Interrupt called on sensor-3 ");
      if (led3State == LOW)
      {
        led3State = !led3State;
        digitalWrite(led3Pin, led3State);
        Serial.println("Motion Detected on sensor-3, Turning led-3 on");
      }
      else
      {
        led3State = !led3State;
        digitalWrite(led3Pin, led3State);
        Serial.println("Turning led-3 off");

      }
    }
    
    
  }
  
} 


byte checkBit()
{
  //check PIND D04-D06
  for (byte x = 4; x <= 6; x++)
  {
    //check for LOW pin
    byte value = PIND;
    if (bitRead(value, x) == 0)
    {
      return x;
    }
  }

  //must have gone HIGH
  return 0;
}

ISR (PCINT2_vect) //D04-06
{
  // Instead of running the interrupt code here, 
  // we only want to know that an interrupt has happened
  Flag = 1;
}




// M1.T4D

// Helpful resources 

// Video about internal ISRS and groups 
// https://www.youtube.com/watch?v=ZDtRWmBMCmw&ab_channel=Electronoobs

// Atmega328P datasheet sections
// 12.2.4 PCICR – Pin Change Interrupt Control Register
//12.2.5 PCIFR – Pin Change Interrupt Flag Register
// 12.2.6 PCMSK2 – Pin Change Mask Register 2

// Start of code

// 3 leds for 3 sensors and 1 for timer
const uint8_t led1Pin = 12;
const uint8_t led2Pin = 11;
const uint8_t led3Pin = 10;
const uint8_t led4Pin = 9;


// Controled by PCMSK2 register 
// Pins belong in the port D

// PCINT20 
const uint8_t sensor1Pin = 4;

// PCINT21 
const uint8_t sensor2Pin = 5;

// PCINT22 
const uint8_t sensor3Pin = 6;


// init the led states
uint8_t led1State = LOW;
uint8_t led2State = LOW;
uint8_t led3State = LOW;

//when set there was an interrupt on D4 to D6
volatile byte Flag;


void setup()
{
  Serial.begin(9600);
  
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
  
  PCIFR  |= bit (PCIF2);   // clear any outstanding interrupts
  PCICR  |= bit (PCIE2);   // enable pin change interrupts for D04 to D06
  
}

void loop ()
{
  //have we had an interrupt?
  if (Flag == 1)
  {
    Flag = 0;

    //check for the bit that caused the interrupt
    byte interrupt = checkBit();

    if (interrupt != 0 && interrupt == 4)
    {
      Serial.print("Interrupt called on =  ");
      Serial.println(interrupt);
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
    
    if (interrupt == 5)
    {
      Serial.print("Interrupt called on = ");
      Serial.println(interrupt);
      if (led2State == LOW)
      {
        led2State = !led2State;
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
    
    if (interrupt == 6)
    {
      Serial.print("Interrupt called on = ");
      Serial.println(interrupt);
      if (led3State == LOW)
      {
        led3State = !led3State;
        digitalWrite(led3Pin, led3State);
        Serial.println("Motion Detected on sensor-3, Turning led-3 on");
      }
      else
      {
        led3State = !led3State;
        digitalWrite(led3Pin, led3State);
        Serial.println("Turning led-3 off");

      }
    }
    
    
  }
  
} 


byte checkBit()
{
  //check PIND D04-D06
  for (byte x = 4; x <= 6; x++)
  {
    //check for LOW pin
    byte value = PIND;
    if (bitRead(value, x) == 0)
    {
      return x;
    }
  }

  //must have gone HIGH
  return 0;
}

ISR (PCINT2_vect) //D04-06
{
  // Instead of running the interrupt code here, 
  // we only want to know that an interrupt has happened
  Flag = 1;
}



// M1.T4D

// Helpful resources 

// Video about internal ISRS and groups 
// https://www.youtube.com/watch?v=ZDtRWmBMCmw&ab_channel=Electronoobs

// Atmega328P datasheet sections
// 12.2.4 PCICR – Pin Change Interrupt Control Register
//12.2.5 PCIFR – Pin Change Interrupt Flag Register
// 12.2.6 PCMSK2 – Pin Change Mask Register 2

// Start of code

// 3 leds for 3 sensors and 1 for timer
const uint8_t led1Pin = 12;
const uint8_t led2Pin = 11;
const uint8_t led3Pin = 10;
const uint8_t led4Pin = 9;


// Controled by PCMSK2 register 
// Pins belong in the port D

// PCINT20 
const uint8_t sensor1Pin = 4;

// PCINT21 
const uint8_t sensor2Pin = 5;

// PCINT22 
const uint8_t sensor3Pin = 6;


// init the led states
uint8_t led1State = LOW;
uint8_t led2State = LOW;
uint8_t led3State = LOW;

// init the pin states
bool D4_state = LOW;
bool D5_state = LOW;
bool D6_state = LOW;



void setup()
{
  Serial.begin(9600);
  
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
  
}

void loop ()
{
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  delay(1000);
} 

ISR (PCINT2_vect) //D04-06
{
  //Serial.println("ISR triggered");
  
  if(digitalRead(sensor1Pin) == HIGH)
  {
   	D4_state = HIGH;
    Serial.println("Sensor-1 Triggered the ISR");
	//Pin D4 triggered the ISR
    
    digitalWrite(led1Pin, HIGH);
    Serial.println("Motion Detected on sensor-1, Turning led-1 on");

  }

  if(digitalRead(sensor2Pin) == HIGH)
  {
   	D5_state = HIGH;
    Serial.println("Sensor-2 Triggered the ISR");
	//Pin D5 triggered the ISR
    
    digitalWrite(led2Pin, HIGH);
    Serial.println("Motion Detected on sensor-2, Turning led-2 on");

  }
  
  if(digitalRead(sensor3Pin) == HIGH)
  {
   	D6_state = HIGH;
    Serial.println("Sensor-3 Triggered the ISR");
    //Pin D6 triggered the ISR
    
    digitalWrite(led3Pin, HIGH);
    Serial.println("Motion Detected on sensor-3, Turning led-3 on");

  }
  
}




// M1.T4D

// Helpful resources 

// Video about internal ISRS and groups 
// https://www.youtube.com/watch?v=ZDtRWmBMCmw&ab_channel=Electronoobs

// Atmega328P datasheet sections
// 12.2.4 PCICR – Pin Change Interrupt Control Register
// 12.2.6 PCMSK2 – Pin Change Mask Register 2

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
  
  // Section 14.9.2 Table 14-9
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
  delay(500);
} 

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

ISR(TIMER1_COMPA_vect)
{
 TCNT1 = t1_load; 
 digitalWrite(timeLedPin, HIGH);
}





