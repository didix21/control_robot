void lcd_program()
{
  lcd.home ();                   // go home
  lcd.print("Roda dreta =   ");
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("Roda esquerra =    ");
}

void print_lcd()
{
  lcd.setCursor (12, 0 ); 
  if (valueR<100)     //si te més de 3 valors esborrar el 
  {                   //valor sobrant de la lectura anterior
    lcd.print(" ");
  }
  lcd.print(valueR);
  lcd.print(" ");
  
  lcd.setCursor ( 12, 1 );
  if (valueL<100)
  {
    lcd.print(" ");
  }
  lcd.print(valueL);
  lcd.print(" ");
}
