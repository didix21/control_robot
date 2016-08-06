#include "pins.h" 

long m1, m2;
long up_times[3]={0,0,0};
int index = 0;
float speed = 0;
int pwm = 0;
long elapsedTime=0, tf=0, to=0;

void encoderCaught(){// Interrupt
  m1 = micros();
  up_times[index]=m1-m2;
  index=(index+1)%3
  m2 = m1;
}

void setup() {
  
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  pinMode(INTERRUPT_PIN,INPUT);
  digitalWrite(INTERRUPT_PIN,HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN),encoderCaugh,RISING);
  to= millis();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  

}
