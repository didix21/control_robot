
void ini_servo()
{
  ServoD.attach(Pin_Servo_Right);
  ServoE.attach(Pin_Servo_Left);

  ServoD.write(Stop);
  ServoE.write(Stop);

}

void ini_lcd()
{
  lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  lcd.print("Creat per Xurra");
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("KB control");
}

void ini_Serial()
{
  Serial.begin(9600);   // Serial Port Comunications at 9600 Baud rate
  strVel.reserve(10); // Reserve 10 bytes
}
