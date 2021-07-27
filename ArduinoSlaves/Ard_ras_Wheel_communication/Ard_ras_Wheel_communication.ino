#include <PID_v1.h>
#include <Servo.h>

#define PWM_L_F 6
#define PWM_L_B 5
#define PWM_R_F 9
#define PWM_R_B 10

#define NormalSetPoint 50

Servo bot_door;

double pulse_L;
double pulse_R;
bool result_L;
bool result_R;
double output_PWM_L;
double output_PWM_R;
double Setpoint_L;
double Setpoint_R;
//double Kp1=0.6, Ki1=10, Kd1=0;
//double Kp2=0.6, Ki2=10, Kd2=0;
double Kp1=2.5, Ki1=10, Kd1=0.1;
double Kp2=2.5, Ki2=10, Kd2=0.1;
PID myPID_L(&pulse_L, &output_PWM_L, &Setpoint_L, Kp1, Ki1, Kd1, DIRECT);
PID myPID_R(&pulse_R, &output_PWM_R, &Setpoint_R, Kp2, Ki2, Kd2, DIRECT);

void wheelSpeed_L(){
 ++pulse_L;
}

void wheelSpeed_R(){
 ++pulse_R;
}

void Stop(){
  analogWrite(PWM_L_F,0);
  analogWrite(PWM_R_F,0);
  analogWrite(PWM_L_B,0);
  analogWrite(PWM_R_B,0);
  }
  
void Forward(){
  Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;
  analogWrite(PWM_L_B,0);analogWrite(PWM_R_B,0);
  analogWrite(PWM_L_F,105);analogWrite(PWM_R_F,100);
  delay(100);
  while(true){
    if(Serial.available()){char cmd = Serial.read();
      if(cmd == 'l'){Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint + 8;
        }else if(cmd == 'r'){Setpoint_L = NormalSetPoint + 8;Setpoint_R = NormalSetPoint;
          }else if(cmd == 's'){Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;
            }else if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_F,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}
    if(result_R){detachInterrupt(1);analogWrite(PWM_R_F,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Correction_Forward(){
  Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;analogWrite(PWM_L_B,0);analogWrite(PWM_R_B,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();
      if(cmd == 'l'){Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5 + 8;
        }else if(cmd == 'r'){Setpoint_L = NormalSetPoint/5 + 8;Setpoint_R = NormalSetPoint/5;
          }else if(cmd == 's'){Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;
            }else if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_F,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_F,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Backward(){
  Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;
  analogWrite(PWM_L_F,0);analogWrite(PWM_R_F,0);
  analogWrite(PWM_L_B,105);analogWrite(PWM_R_B,100);delay(200);
  while(true){
    if(Serial.available()){char cmd = Serial.read();
      if(cmd == 'l'){Setpoint_L = NormalSetPoint + 4;Setpoint_R = NormalSetPoint;
        }else if(cmd == 'r'){Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint + 2;
          }else if(cmd == 's'){Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;
            }else if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_B,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_B,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Correction_Backward(){
  Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;analogWrite(PWM_L_F,0);analogWrite(PWM_R_F,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();
      if(cmd == 'l'){Setpoint_L = NormalSetPoint/5 + 4;Setpoint_R = NormalSetPoint/5;
        }else if(cmd == 'r'){Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5 + 2;
          }else if(cmd == 's'){Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;
            }else if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_B,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_B,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Turnleft(){
  Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;analogWrite(PWM_L_F,0);analogWrite(PWM_R_B,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_B,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_F,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Correction_Turnleft(){
  Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;analogWrite(PWM_L_F,0);analogWrite(PWM_R_B,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_B,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_F,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Turnright(){
  Setpoint_L = NormalSetPoint;Setpoint_R = NormalSetPoint;analogWrite(PWM_L_B,0);analogWrite(PWM_R_F,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_F,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_B,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Correction_Turnright(){
  Setpoint_L = NormalSetPoint/5;Setpoint_R = NormalSetPoint/5;analogWrite(PWM_L_B,0);analogWrite(PWM_R_F,0);
  while(true){
    if(Serial.available()){char cmd = Serial.read();if(cmd == 'S'){break;}}
    result_L = myPID_L.Compute();result_R = myPID_R.Compute();
    if(result_L){detachInterrupt(0);analogWrite(PWM_L_F,output_PWM_L);pulse_L = 0;attachInterrupt(0, wheelSpeed_L, CHANGE);}if(result_R){detachInterrupt(1);analogWrite(PWM_R_B,output_PWM_R);pulse_R = 0;attachInterrupt(1, wheelSpeed_R, CHANGE);}
  }
  Stop();
}

void Feedback_Ras(String info){
  unsigned char len = info.length();
  for(unsigned char i = 0 ; i < len ; ++i){
    Serial.write(info.charAt(i));
    }
  }

void Release_Cube(){
  bot_door.attach(11);
  for(int i = 160;i>90;--i){
    bot_door.write(i);delay(20);
    }
  delay(1000);
  for(int i = 90;i>30;--i){
    bot_door.write(i);delay(20);
    }
  bot_door.detach();
  Feedback_Ras("Cube_Release");
  }

void setup() {
  Serial.begin(57600);
  pinMode(PWM_L_F, OUTPUT);
  pinMode(PWM_L_B, OUTPUT);
  pinMode(PWM_R_F, OUTPUT);
  pinMode(PWM_R_B, OUTPUT);


  
  Setpoint_L =100;
  Setpoint_R =100;
  myPID_L.SetMode(AUTOMATIC);
  myPID_L.SetSampleTime(50);
  myPID_R.SetMode(AUTOMATIC);
  myPID_R.SetSampleTime(50);
  attachInterrupt(0, wheelSpeed_L, CHANGE);//0->2  1->3
  attachInterrupt(1, wheelSpeed_R, CHANGE);//0->2  1->3
  //bot_door.attach(11);

  //bot_door.write(160);

  

}

void loop(){
  if(Serial.available()){
    char cmd = Serial.read();
    if(cmd == 'F'){
      Forward();
    }else if(cmd == 'B'){
      Backward();
    }else if(cmd == 'f'){
      Correction_Forward();
    }else if(cmd == 'b'){
      Correction_Backward();
    }else if(cmd == 'L'){
      Turnleft();
    }else if(cmd == 'R'){
      Turnright();
    }else if(cmd == 'e'){
      Correction_Turnleft();
    }else if(cmd == 'i'){
      Correction_Turnright();
    }else if(cmd == 'E'){
      Release_Cube();
    }
  }
}
