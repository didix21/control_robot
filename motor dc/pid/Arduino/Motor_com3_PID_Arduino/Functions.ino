void run_motorR (int vel)
{
  if (vel<0)
  {
    digitalWrite (in3, LOW);
    digitalWrite (in4, HIGH);
    vel=-vel;
  }
  else
  {
    digitalWrite (in4, LOW);
    digitalWrite (in3, HIGH);
  }
  analogWrite(enB,vel);
}

void run_motorL (int vel)
{
  if (vel<0)
  {
    digitalWrite (in1, LOW);
    digitalWrite (in2, HIGH);
    vel=-vel;
  }
  else
  {
    digitalWrite (in2, LOW);
    digitalWrite (in1, HIGH);
  }
  analogWrite(enA,vel);
}


int GetVelocityR()
{
  int rpm;
  int count= countAR-prev_countAR;
  rpm=(60/((float)ISR_Time/1000000))*count/(ticks_per_rev*reduction_gear);           //Velocity calculation every Time Sample -->  
                                                              //Ts=ISR_Time(microSeconds)/1000000=convert to seconds
                                                              //In a minute how many times repeat this Ts--> exemple for Ts=0,1s  60/0,1=600
                                                              //tick counts since last interrupt, when during Ts-->(count) actual_count minus last count, then multiplicate for how much interrupts there are in  minute
                                                              //if i know how much counts there are in a minute, and i know how much tocks there are in a revolution, tick counts is devided by ticks in a revolution
  prev_countAR=countAR; 

  return rpm;
}

int GetVelocityL()
{
  int rpm;
  int count= countAL-prev_countAL;
  rpm=(60/((float)ISR_Time/1000000))*count/(ticks_per_rev*reduction_gear);           //Velocity calculation every Time Sample -->  
                                                              //Ts=ISR_Time(microSeconds)/1000000=convert to seconds
                                                              //In a minute how many times repeat this Ts--> exemple for Ts=0,1s  60/0,1=600
                                                              //tick counts since last interrupt, when during Ts-->(count) actual_count minus last count, then multiplicate for how much interrupts there are in  minute
                                                              //if i know how much counts there are in a minute, and i know how much tocks there are in a revolution, tick counts is devided by ticks in a revolution
  prev_countAL=countAL; 

  return rpm;
}
