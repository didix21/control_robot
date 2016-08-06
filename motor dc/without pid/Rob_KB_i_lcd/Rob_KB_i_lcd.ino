//Llibreries
#include <Servo.h>             //This library allows an Arduino board to control RC (hobby) servo motors.
#include <Wire.h>              //This library allows you to communicate with I2C / TWI devices.
#include <LCD.h>                
#include <LiquidCrystal_I2C.h>  // This library allows an Arduino board to control LiquidCrystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs. The library works with in either 4- or 8-bit mode (i.e. using 4 or 8 data lines in addition to the rs, enable, and, optionally, the rw control lines).


//Pantalla LCD
#define I2C_ADDR    0x27    //A4 a SDA (Datos) (Gris)
                            //A5 a SCL (Clock) (Lila)
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//Pins Servos
#define Pin_Servo_Right 8
#define Pin_Servo_Left 9
#define Stop 90

//Creació d´objectes
//Servos
Servo ServoD;
Servo ServoE;
// LCD
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Array and Variables for communication
String strVel="";       //
boolean comFinished= false;
char Trama[5], data=0;   // string for data recivied
int i=0, j=0, x=0;    //"i" is Index for reception data, "j" is for save data in internal variable, "x" is lenght of recivied data
int valueR,valueL;


void setup() 
{
  // put your setup code here, to run once:

  ini_servo();
  ini_lcd();
  ini_Serial();

  delay (1000);
  lcd_program();
}

void loop() 
{
 
  if(comFinished)
  {
    control(Trama[0]);    //Send command to switch
    comFinished=false;
  }
print_lcd();
}
