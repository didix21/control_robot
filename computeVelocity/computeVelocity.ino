
/* This program it is used to compute the velocity graph of a DC motor for different values of PWM.
 * Before run it, please check pins.h file to configure arduino pins and the main characteristics
 * of your DC Motor.
 */

#include "pins.h" 

long mA1, mA2, mB1, mB2;
long up_times_A[3]={0,0,0},up_times_B[3]={0,0,0};
int indexA = 0, indexB = 0, i=0, j;
float speed = 0;
int pwm = 0;
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
  MYSERIAL.println("This program computes the velocity of a motor,");
  MYSERIAL.println("the program will print 100 values of velocities");
  MYSERIAL.println();
  MYSERIAL.print("Type any character to begin the program: ");
  while(MYSERIAL.read()<0); // Wait until a character will be type
  
  
  
}

void loop() {

   if(firstTime){ // Choose if you are gonna use motor A or B
    MYSERIAL.println("Type A or B for taking data from one of the motors: A");
    while(dataComing == 0);
    firstTime = false;
   }

  switch(dataComing){ // Switch Motor A or B
    case 'A':
      digitalWrite(ENB,LOW);
      digitalWrite(ENA,HIGH);
      motorAenabled = true;
    break;

    case 'B':
      digitalWrite(ENB,HIGH);
      digitalWrite(ENA,LOW);
      motorBenabled = true;
    break;
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
 
  while (i <= 260){ // Plot 260 velocity values
    if(pwm < 255){
      pwm = pwm + 1;
    }    
    speed=MIN2MICROSECONDS/(COUNTS_PER_REVOLUTION*timeBetweenPulses); // Compute speed in rpm
    delay(100);
    MYSERIAL.println(speed); // Print speed in rpm 
    i++;
  }

}

void serialEvent (){ // Serial Event to receive characters from serial port
  while(MYSERIAL.available()){
    dataComing=MYSERIAL.read();
  }
}


