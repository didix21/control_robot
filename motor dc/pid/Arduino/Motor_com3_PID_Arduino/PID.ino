//r=referencia*100.0/1023.0; //conversion de [0-100], debido al PWM
//y=sensor*100.0/1023.0; //conversion de [0-100], debido al PWM
//e=r-y; //cáclculo del errror
//p=Kp_d*e; //cálculo del término proporcional
//i=Ki_d*(e+e0)+i0; //cálculo del término intergral
//d=Kd_d*(e-e0); //cálculo del término derivativo
//u=p+i+d; //u(k)=Kp_d*e(k)+Ki_d*(e(k)+e(k-1))+i(k-1)+Kd_d*(e(k)-e(k-1))

void control_pid_ini(struct pid_data &pid, float delta, float kp, float ki, float kd) 
{
  pid.delta = delta;
  pid.kp = kp;
  pid.ki = ki;
  pid.kd = kd;
  pid.sum = 0;
  pid.prevError = 0;
}

float Get_pid(struct pid_data &pid, float error) 
{
  //Calcul de P
  float p = pid.kp * error;

  //Calcul de I
  pid.sum += error;
  float i = pid.ki * pid.delta * pid.sum;
  
  //Calcul de D
  float d = pid.kd * (error - pid.prevError) / pid.delta;
  
  pid.prevError = error;

  float _pid=p+i+d;
  //Limitació de valors
  
  if(_pid<0) _pid=0;
  if(_pid>255) _pid=255;
  
  return _pid;
}
