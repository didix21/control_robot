void ini_motorDC()
{
  //Right Motor
  pinMode (enA, OUTPUT);       // Enable outputs pins 
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);

  //Left Motor
  pinMode (enB, OUTPUT);       // Enable outputs pins 
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
}


void ini_Serial()
{
  Serial.begin(9600);     // Serial Port Comunications at 9600 Baud rate
  strVel.reserve(10);     // Reserve 10 bytes
}

void ini_lcd()
{
   lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd.setBacklight(HIGH);
   lcd.home ();                   // go home
   lcd.print("Creat per Xurra");
   lcd.setCursor ( 0, 1 );        // go to the 2nd line
   lcd.print("2 Motors control PID");
}

void lcd_program()
{
  lcd.home ();                   // go home
  lcd.print("PWMr=     l=            ");
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("RPMr=     l=            ");
}


// Interruptions
void int_isrTimer()
{
  Timer1.initialize(ISR_Time);  // Time of interruption
  Timer1.attachInterrupt( ISR_Callback) ;   // Callback function
}

void int_encoder()
{
  attachInterrupt(digitalPinToInterrupt(encAR), encoderCountAR, RISING);  //Interrupt pin, ISR function, Mode
  attachInterrupt(digitalPinToInterrupt(encAL), encoderCountAL, RISING);
}

