
void control(char command)    
{
  switch (command)
  {
    case 'r':
    for(j=1; j<x; j++)        //Read until end "x" of frame
    {
      strVel += Trama[j];
    }
    valueR=strVel.toInt(); // Convert String to Integer
    strVel="";
    run_motorR (valueR);
    break;
    
    case 'l':
    for(j=1; j<x; j++)        //Read until end "x" of frame
    {
      strVel += Trama[j];
    }
    valueL=strVel.toInt(); // Convert String to Integer
    strVel="";
    run_motorL (valueL);
    break;

    case 'S':
    run_motorR (Stop);
    run_motorL (Stop);
    ServoD.detach();
    ServoE.detach();
    break;

    case 'R':
    ServoD.attach(Pin_Servo_Right);
    ServoE.attach(Pin_Servo_Left);
    run_motorR (Stop);
    run_motorL (Stop);
    break;

    
    default:
    Serial.println("Error comunicación");
    break;
  }
}
