#include "pins.h" 

long mA1, mA2, mB1, mB2;
long up_times_A[3]={0,0,0},up_times_B[3]={0,0,0};
int indexA = 0, indexB = 0, i=0;
float speed = 0;
int pwm = 0;
char dataComing= 0;
bool motorAenabled = false, motorBenabled = false, firstTime = true;

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
  
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  pinMode(INTERRUPT_PIN_MOTOR_A,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_A,HIGH);
  pinMode(INTERRUPT_PIN_MOTOR_B,INPUT);
  digitalWrite(INTERRUPT_PIN_MOTOR_B,HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_A),encMotorA,RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MOTOR_B),encMotorB,RISING);
//  to= millis();

  MYSERIAL.println("This program computes the velocity of a motor,");
  MYSERIAL.println("the program will print 100 values of velocities");
  MYSERIAL.println();
  MYSERIAL.print("Type any character to begin the program: ");
  while(MYSERIAL.read()<0);
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if(firstTime){
    MYSERIAL.println("Type A or B to take data from one of the motors: A");
    while(dataComing == 0);
    firstTime = false;
   }

  switch(dataComing){
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
  }else if (!motorAenabled && motorBenabled){
    analogWrite(IN4,0);
    analogWrite(IN3,pwm);
  }
 
  while (i <= 260){
    if(pwm < 255){
      pwm = pwm + 1;
    }
    delay(100);
    MYSERIAL.println(speed);
    i++;
  }

}

void serialEvent (){
  while(MYSERIAL.available()){
    dataComing=MYSERIAL.read();
  }
}


