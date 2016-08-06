void serialEvent()
{
  while(Serial.available()) 
  {
    data=(char)Serial.read();
   
    if (data != 'z')
    {
      Trama[i++]=data;
   
    } 
    else
    {
       comFinished = true;
       x=i;
       i=0;
    }
   
  }
}


void encoderCountAR()
{
  countAR++;
}

void encoderCountAL()
{
  countAL++;
}


void ISR_Callback()
{
  detachInterrupt(digitalPinToInterrupt(encAR));    //Disable interrupt when calculating
  detachInterrupt(digitalPinToInterrupt(encAL));

  //Right
  vel_sensR= GetVelocityR();
  float error = (vel_refR - vel_sensR);
  PWM_R=(int) Get_pid(pid_data_R, error);
  if (gir_R) PWM_R=-PWM_R;
  run_motorR (PWM_R);
  
  //Left
  vel_sensL= GetVelocityL();
  error = vel_refL - vel_sensL;
  PWM_L=(int) Get_pid(pid_data_L, error);
  if (gir_L) PWM_L=-PWM_L;
  run_motorL (PWM_L);
  
 
  attachInterrupt(digitalPinToInterrupt(encAR), encoderCountAR, RISING);  //Interrupt pin, ISR function, Mode
  attachInterrupt(digitalPinToInterrupt(encAL), encoderCountAL, RISING);

}

