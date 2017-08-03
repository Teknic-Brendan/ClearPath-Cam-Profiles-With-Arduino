#include <ServoCAM.h>
ServoCAM myServoCAM=ServoCAM();
ServoCAM* myPointer = &myServoCAM;
int i=0;
double x;
double y;
boolean _flag=false;
uint8_t Pin_A = 8;
uint8_t Pin_B = 9;
uint8_t Pin_E = 6;
int _BurstSteps = 0;

void setup() {
  // put your setup code here, to run once:
//Serial.begin(115200);
pinMode(Pin_A, OUTPUT);
pinMode(Pin_B, OUTPUT);
pinMode(Pin_E, OUTPUT);
pinMode(5, INPUT_PULLUP);
pinMode(2,OUTPUT);
digitalWrite(Pin_E, HIGH);
delay(500);
myServoCAM.newMasterScale(1269);
myServoCAM.newSlaveScale(986);
myServoCAM.zero();

cli();//stop interrupts

   // set up Timer 1
   TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0

  //Set compare match register to time
  OCR2A = 200;// time should be 249, 1-256 will produce different frequencies

  // turn on CTC mode
  TCCR2A |= (1 << WGM21);

  // Set CS21 bit for 8 prescaler
  TCCR2B = 0;
  TCCR2B |= (1 << CS01) | (1 << CS00);  

  // enable timer compare interrupt
  TIMSK2=0;
  TIMSK2 |= (1 << OCIE2A);




// hardware counter setup ( refer atmega168.pdf chapter 16-bit counter1)
    TCCR1A=0;                  // reset timer/counter1 control register A
    TCCR1B=0;                   // reset timer/counter1 control register A
    TCNT1=0;                 // counter value = 0
    // set timer/counter1 hardware as counter , counts events on pin T1 ( arduino pin 5)
    // normal mode, wgm10 .. wgm13 = 0
    
    TCCR1B |=  (1<<CS10) ;// External clock source on T1 pin. Clock on rising edge.
    TCCR1B |=  (1<<CS11) ;
    TCCR1B |=  (1<<CS12) ;
    
    TCCR1B |= (1<<CS12) | (1<<CS11) | (1<<CS10);        //   start counting now   
    
  sei();//allow interrupts
}

void loop() {
  // put your main code here, to run repeatedly:

   
   while(myServoCAM.last_Master_Command()<1.182)
   {
    
   }
   TCNT1=0;
}

ISR(TIMER2_COMPA_vect)
{  
  //Prevent Interupts
//cli();

//Turn on pin 2 to see how long the ISR takes
  digitalWrite(2,HIGH);

    _BurstSteps=myPointer->updateCAM(TCNT1);
   //_BurstSteps=0;
    if(_BurstSteps!=0)
    {
    if(_BurstSteps<0)
    {
        _BurstSteps = -_BurstSteps;
        PORTB |= 1<<(Pin_A-8); 
        delayMicroseconds(1);
    }
    else
    {
        PORTB&=255-(1<<(Pin_A-8));
        delayMicroseconds(1); 
    }
    }
    
//loop through BurstSteps decrementing each value to 0    
do
{

   _flag=false;


if(_BurstSteps && _BurstSteps--)  //Assume at least one axis is active, and check/decrement BurstSteps
{
    _flag=true;
PORTB |= 1<<(Pin_B-8);  //Activate the Direction Bit for motor 1
}
  delayMicroseconds(1);     //Short Delay
  PORTB &=255-(1<<(Pin_B-8)); //Turn off all active pins
  delayMicroseconds(1);
} while(_flag);

//turn off debug pin
digitalWrite(2,LOW);
//allow interupts
//sei();

}

