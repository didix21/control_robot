void imprimir()
{

  // IMPRIMIR PWM
  int print_PWM=(int)100*PWM_R/MAX_PWM;
  if (print_PWM<0)
  {
    lcd.setCursor (4,0);
    if(print_PWM>-100)
    {
      lcd.print(" ");
      if(print_PWM>-10)
      {
        lcd.print(" ");
      }
    }
  }
  else
  {
    lcd.setCursor (5, 0 );               
    if (print_PWM<100)
    {
      lcd.print(" ");
      if (print_PWM<10)
      {
        lcd.print(" ");
      }
    }
  } 
  lcd.print(print_PWM);
  lcd.print("%");

  print_PWM=(int)100*PWM_L/MAX_PWM;
  if (print_PWM<0)
  {
    lcd.setCursor (11,0);
    if(print_PWM>-100)
    {
      lcd.print(" ");
      if(print_PWM>-10)
      {
        lcd.print(" ");
      }
    }
  }
  else
  {
    lcd.setCursor (12, 0 );               
    if (print_PWM<100)
    {
      lcd.print(" ");
      if (print_PWM<10)
      {
        lcd.print(" ");
      }
    }
  }
  lcd.print(print_PWM);
  lcd.print("%");


  // PRINT VELOCITY
  //Right
  lcd.setCursor ( 5, 1 );
  if (vel_sensR<100)
  {
    lcd.print(" ");
    if (vel_sensR<10)
    {
      lcd.print(" ");
    }
  }
  lcd.print(vel_sensR);
  lcd.print(" ");
  
  //Left
  lcd.setCursor ( 12, 1 );
  if (vel_sensL<100)
  {
    lcd.print(" ");
    if (vel_sensL<10)
    {
      lcd.print(" ");
    }
  }
  lcd.print(vel_sensL);
  lcd.print(" ");
}
