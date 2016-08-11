
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
char dataComing= 0, dataDisplay;
bool motorAenabled = false, motorBenabled = false, firstTime = true;
float timeBetweenPulses; // (us/count)
//
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
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  // Initialize outputs and inputs
  MYSERIAL.begin(BAUDRATE);
  pinMode(INTERRUPT_PIN_MOTOR_A,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_A,HIGH);
  pinMode(INTERRUPT_PIN_MOTOR_B,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_B,HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_A),encMotorA,RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_B),encMotorB,RISING);
  analogWrite(ENA,pwm);
  analogWrite(ENB,pwm);
  // Print information in serial port
  MYSERIAL.println("This program computes the velocity of a motor,");
  MYSERIAL.println("the program will print 100 values of velocities");
  MYSERIAL.println();
  MYSERIAL.println("Type any character to begin the program: ");
  while(MYSERIAL.read()<0); // Wait until a character will be type
  
  
}

void loop() {


//  
  if(firstTime){ // Choose if you are gonna use motor A or B
    MYSERIAL.print("Type A or B for taking data from one of the motors: ");
    firstTime = false;
  }
    switch (dataDisplay){ // Switch Motor A or B
      case 'A':
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
        motorAenabled = true;
        MYSERIAL.print(" MOTOR A ENABLED ");
      break;
  
      case 'B':
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        motorBenabled = true;
        MYSERIAL.print(" MOTOR B ENABLED ");
      break;
    }

  if(dataDisplay > 0){
    MYSERIAL.println(dataDisplay);
    dataComing = 0;
    dataDisplay = 0;
  }


  if(motorAenabled && !motorBenabled){
    analogWrite(ENA,pwm);
    timeBetweenPulses = up_times_A[0] + up_times_A[1] + up_times_A[2];
   // timeBetweenPulses = timeBetweenPulses/3;
  }else if (!motorAenabled && motorBenabled){
    analogWrite(ENB,pwm);
    delay(100);
    timeBetweenPulses = up_times_B[0] + up_times_B[1] + up_times_B[2];
    timeBetweenPulses = timeBetweenPulses/3;
  }
  
 if(motorAenabled || motorBenabled){
    if (i <= 300){ // Plot 260 velocity values
     
      delay(100);
      speed=MIN2MICROSECONDS/(COUNTS_PER_REVOLUTION*timeBetweenPulses); // Compute speed in rpm
     if(timeBetweenPulses != 0){
      if(speed <= 200) MYSERIAL.println(speed); // Print speed in rpm 
      else  MYSERIAL.println(0);
     }
     else {
      MYSERIAL.println(0);
     }
      //MYSERIAL.println(pwm); // Print speed in rpm 
      //timeBetweenPulses = 0;
      if(pwm < 255) pwm = pwm + 1;
      i++;
    }
   }
}
//
void serialEvent (){ // Serial Event to receive characters from serial port
  while(MYSERIAL.available()){
    dataComing=(char)MYSERIAL.read();
      if(dataComing != '\n'){
        dataDisplay = dataComing;
      }
  }
}
//

