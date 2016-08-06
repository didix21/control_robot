//Llibreries
#include <Wire.h>              //This library allows you to communicate with I2C / TWI devices.
#include <LCD.h>                
#include <LiquidCrystal_I2C.h>  // This library allows an Arduino board to control LiquidCrystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs. The library works with in either 4- or 8-bit mode (i.e. using 4 or 8 data lines in addition to the rs, enable, and, optionally, the rw control lines).
#include <TimerOne.h>           // This library allows comands to Timer Interrupts

// Pins motor1
#define in1 8   // Right rotary
#define in2 7   // Left rotary
#define enA 5   // Enable motor 1 Left

#define in3 9   // Right rotary
#define in4 10   // Left rotary
#define enB 6   // Enable motor 2 Right


//Pins encoder1
#define encAR 2
#define encBR 11

#define encAL 3
#define encBL 12


//directions
#define right true
#define left false

//Pantalla LCD
#define I2C_ADDR    0x27    //A4 a SDA (Datos)
                            //A5 a SCL (Clock)
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//Time Interruption
#define ISR_Time 100000       // Interruption Time in microseconds

//Encoder specifications
#define ticks_per_rev 11
#define reduction_gear 34

//Maximum velocity and PWM
#define MAX_PWM 255
#define MAX_VELOCITY 130

//Creació d´objectes
// LCD
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Control PID
struct pid_data 
{
  float kp, ki, kd;
  float delta;
  float sum;
  float prevError;
};


//Variables globals
long countAR=0, countBR=0, prev_countAR=0;
long countAL=0, countBL=0, prev_countAL=0;
bool gir_R=true,gir_L=true;
int vel_sensR, vel_sensL;
int vel_refR, vel_refL;

// Array and Variables for communication
String strVel="";       //
boolean comFinished= false;
char Trama[5], data=0;   // string for data recivied
int i=0, j=0, x=0;    //"i" is Index for reception data, "j" is for save data in internal variable, "x" is lenght of recivied data
int PWM_R,PWM_L;

struct pid_data pid_data_R, pid_data_L;

void setup()
{
//Initialitzations
ini_motorDC();
ini_lcd();

delay (1000);
// initialize interrupts
int_isrTimer();     //Interrupt Service Routine with Timer
int_encoder();     //Interrupt Routine when pin encoder rising

//Initialize Serial Port comunications
ini_Serial();

// Grafic Interficie Display
lcd_program();

control_pid_ini(pid_data_R, 0.01, 4, 0.1, 0);    //Delta, P estabilitat, I=Temps de resposta, D=arribar a valor despres de variació brusca
control_pid_ini(pid_data_L, 0.01, 4, 0.1, 0);    //Delta, P estabilitat, I=Temps de resposta, D=arribar a valor despres de variació brusca
imprimir();
}

void loop()
{
  char command, motor;
  if(comFinished)
  {
    command=Trama[0];
    switch (command)
    {
      case 'r':
        for(j=1; j<x; j++)        //Read until end "x" of frame
        {
          strVel += Trama[j];
        }
        vel_refR=strVel.toInt(); // Convert String to Integer
        if (vel_refR<0)
        {
          gir_R=true;
          vel_refR=-vel_refR;
        }
        else
        {
          gir_R=false;
        }
        strVel="";
      break;
      
      case 'l':
        for(j=1; j<x; j++)        //Read until end "x" of frame
        {
          strVel += Trama[j];
        }
        vel_refL=strVel.toInt(); // Convert String to Integer
        if (vel_refL<0)
        {
          gir_L=true;
          vel_refL=-vel_refL;
        }
        else
        {
          gir_L=false;
        }
        strVel="";
      break;

      case 'v':
        motor=Trama[1];
        if (motor=='r')
        {
          Serial.println(vel_sensR);
        }
        else if (motor=='l')
        {
          Serial.println(vel_sensL); 
        }
      break;
      
      default:
        Serial.println("Error comunicacion");
      break;
    }
    comFinished=false;
  }
  imprimir();  
}

