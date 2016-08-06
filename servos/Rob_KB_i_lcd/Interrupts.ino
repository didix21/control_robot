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

