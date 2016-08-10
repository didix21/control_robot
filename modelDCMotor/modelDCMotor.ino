#include "pins.h"
//pollada
long mA1, mA2, mB1, mB2;
long up_times_A[3]={0,0,0},up_times_B[3]={0,0,0};
int indexA = 0, indexB = 0, i=0, j, count = 0;
float speed = 0;
int pwm = 135;
char dataComing= 0;
bool motorAenabled = false, motorBenabled = false, firstTime = true;
float timeBetweenPulses; // (us/count)

void encMotorA(){// Interrupt Motor A
  mA1 = micros();
  up_times_A[indexA]=mA1-mA2;
  indexA=(indexA+1)%3;
  mA2 = mA1;
}

void encMotorB(){// Interrupt Motor B
  mB1 = micros();
  up_times_B[indexB]=mB1-mB2;
  indexB=(indexB+1)%3;
  mB2 = mB1;
}

void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  // Initialize outputs and inputs
  MYSERIAL.begin(BAUDRATE);
  pinMode(INTERRUPT_PIN_MOTOR_A,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_A,HIGH);
  pinMode(INTERRUPT_PIN_MOTOR_B,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_B,HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_A),encMotorA,RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_B),encMotorB,RISING);
  // Print information in serial port
  MYSERIAL.println("This program shows the velocity for a value of pwm,");
  MYSERIAL.println("between 155 and 235"); // Max 235 to avoid saturate the motor
  MYSERIAL.println();
  MYSERIAL.print("Type any character to begin the program: ");
  while(MYSERIAL.read()<0); // Wait until a character will be type  
}

void loop() {
  
   if(firstTime){ // Choose if you are gonna use motor A or B
    MYSERIAL.print("Type A or B for taking data from one of the motors: ");
    while(dataComing == 0);
    MYSERIAL.println(dataComing);
    switch(dataComing){ // Switch Motor A or B
      case 'A':
        digitalWrite(ENB,LOW);
        digitalWrite(ENA,HIGH);
        analogWrite(IN2,0);
        analogWrite(IN1,pwm);
        motorAenabled = true;
        delay(2000); // To stabalize the motor
      break;
  
      case 'B':
        digitalWrite(ENB,HIGH);
        digitalWrite(ENA,LOW);
        analogWrite(IN4,0);
        analogWrite(IN3,pwm);
        motorBenabled = true;
        delay(2000); // To stabalize the motor
      break;    
    }
    firstTime = false;
  }

   if(motorAenabled && !motorBenabled){
      analogWrite(IN2,0);
      analogWrite(IN1,pwm);
      for(j = 0; j<3; j++){
        timeBetweenPulses = timeBetweenPulses + up_times_A[i];
      }
      timeBetweenPulses = timeBetweenPulses/3;
  }else if (!motorAenabled && motorBenabled){
      analogWrite(IN4,0);
      analogWrite(IN3,pwm);
      for(j = 0; j<3; j++){
        timeBetweenPulses = timeBetweenPulses + up_times_B[i];
      }
      timeBetweenPulses = timeBetweenPulses/3;
  }

 for(j=0;j < 1000; j++){
    if(count >= 100){
      if(pwm == 135) pwm = 235;
      if(pwm == 235) pwm = 135;
      j--;
      count = 0;
    }
    else {  
      speed=MIN2MICROSECONDS/(COUNTS_PER_REVOLUTION*timeBetweenPulses); // Compute speed in rpm    
      MYSERIAL.println(speed);
      delay(100);
      count++;
    }
 }

}

void serialEvent (){ // Serial Event to receive characters from serial port
  while(MYSERIAL.available()){
    dataComing=MYSERIAL.read();
  }
}
