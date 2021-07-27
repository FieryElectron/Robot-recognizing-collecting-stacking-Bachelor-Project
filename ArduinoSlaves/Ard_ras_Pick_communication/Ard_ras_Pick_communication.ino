#include <Servo.h>

#define INI 0
#define FAR 1 
#define MID 2
#define PUT 3
#define AWAY 4

#define Tight 8
#define Loose 7

char ArmState = INI;
String Ras_cmd = "";
int plate_still = 1;

Servo claw;
Servo top;
Servo mid;
Servo bot;

Servo plate;

Servo pick;

int interval = 10;

void setup() {
  Serial.begin(57600);
  claw.attach(6); 
  top.attach(11);
  mid.attach(10);
  bot.attach(9);
  plate.attach(5);
  pick.attach(3);
  
  plate.write(90);
  claw.write(60); 
  top.write(45);
  mid.write(85);
  bot.write(95);
  pick.write(180);

  
  pinMode(2,INPUT);

  pinMode(Tight,OUTPUT);
  pinMode(Loose,OUTPUT);
  //attachInterrupt(0, Stop, RISING);//0->2  1->3
}


void Refresh_Ras_cmd(){
  if(Serial.available()){
    delay(200);
    Ras_cmd = String();
    while(Serial.available()){
      Ras_cmd += char(Serial.read());
      }
      //Serial.println(Ras_cmd);
    }
  }
  
void Feedback_Ras(String info){
  unsigned char len = info.length();
  for(unsigned char i = 0 ; i < len ; ++i){
    Serial.write(info.charAt(i));
    }
  }

void Press_Button(){
  slowMove(4,100);
  slowMove(4,179);
  Feedback_Ras("Button_Pressed");
  }

void GoTight(){
  digitalWrite(Tight,HIGH);
  digitalWrite(Loose,LOW);
  }

void GoLoose(){
  digitalWrite(Tight,LOW);
  digitalWrite(Loose,HIGH);
  delay(1000);
  digitalWrite(Tight,LOW);
  digitalWrite(Loose,LOW);
  
  }
void GoStop(){
  digitalWrite(Tight,LOW);
  digitalWrite(Loose,LOW);
  }

void SlowGrab(){
  GoTight();delay(200);
  GoStop();delay(20);
  }

void Part_Grab(){
    digitalWrite(Loose,LOW);
  for(int i = 0; i < 30000 ;++i){
    digitalWrite(Tight,HIGH);
    delayMicroseconds(35);
     digitalWrite(Tight,LOW);
    delayMicroseconds(65);
    }
    digitalWrite(Tight,LOW);
  }

void SmartGrab(){
  for(int i =0;i<2;++i){
    Part_Grab();
    }
  }


void GetCubes(){
  slowMove(4,45);
  PlateGoRight();
  delay(1000);
  slowMove(4,0);
  delay(4000);
    SmartGrab();
    GoTight();
    delay(100);
    slowMove(4,180);
    delay(1000);
    GoLoose();
    slowMove(4,90);
    delay(5000);
  }
void Arrange_Cube(){
  while(true){
    if(Serial.available()){
      int count = 0;
      delay(200);
      Ras_cmd = String();
      while(Serial.available()){
        Ras_cmd += char(Serial.read());
        ++count;
        }
        //Serial.println(count);
        //slowMove(4,0);
        GetCubes();
        
        for(int i = 0; i < count ; ++i ){
          delay(500);
          //Serial.print("i = ");Serial.println(i);
          if(Ras_cmd.charAt(i) == 'T'){
            ArmGoFar();
            }else if(Ras_cmd.charAt(i) == 'M'){
              ArmGoMid();
              }else if(Ras_cmd.charAt(i) == 'P'){
                ArmGoPut();
                }else if(Ras_cmd.charAt(i) == 'A'){
                  ArmGoAway();
                  }else if(Ras_cmd.charAt(i) == 'L'){
                    PlateGoLeft();
                    }else if(Ras_cmd.charAt(i) == 'R'){
                      PlateGoRight();
                      }
                    }
                    slowMove(4,90);
                    delay(2000);
                    Feedback_Ras("Cube_Arranged");
                    return ;
                  }
                }
              }
  


void slowMove(int num,int tar){
  switch(num){
    case 0:{
    int before = claw.read();
    int range = tar - before;
    if(range>0){
      for(int i = 0;i<range;++i){
        claw.write(before+i);
        delay(interval);
        }
      }else{
        for(int i = 0;i<-range;++i){
        claw.write(before-i);
        delay(interval);
        }
        }
    break;
    }
    case 1:{
    int before = top.read();
    int range = tar - before;
    if(range>0){
      for(int i = 0;i<range;++i){
        top.write(before+i);
        delay(interval);
        }
      }else{
        for(int i = 0;i<-range;++i){
        top.write(before-i);
        delay(interval);
        }
        }
    break;
    }
    case 2:{
    int before = mid.read();
    int range = tar - before;
    if(range>0){
      for(int i = 0;i<range;++i){
        mid.write(before+i);
        delay(interval);
        }
      }else{
        for(int i = 0;i<-range;++i){
        mid.write(before-i);
        delay(interval);
        }
        }
    break;
    }
    case 3:{
    int before = bot.read();
    int range = tar - before;
    if(range>0){
      for(int i = 0;i<range;++i){
        bot.write(before+i);
        delay(interval);
        }
      }else{
        for(int i = 0;i<-range;++i){
        bot.write(before-i);
        delay(interval);
        }
        }
    break;
    }
    case 4:{
    int before = pick.read();
    int range = tar - before;
    if(range>0){
      for(int i = 0;i<range;++i){
        pick.write(before+i);
        delay(interval);
        }
      }else{
        for(int i = 0;i<-range;++i){
        pick.write(before-i);
        delay(interval);
        }
        }
    break;
    }
    
    }
  }

void ArmGoFar(){
    if(ArmState == INI){
      slowMove(0,80);slowMove(3,45);slowMove(2,65); slowMove(1,6);delay(1000);slowMove(0,36);
    }else if(ArmState == PUT){
      slowMove(0,80);slowMove(3,45);slowMove(2,65); slowMove(1,6);delay(1000);slowMove(0,36);
      }else if(ArmState == AWAY){
        slowMove(0,80);slowMove(3,45);slowMove(2,65); slowMove(1,6);delay(1000);slowMove(0,36);
        }
      ArmState = FAR;
  }

void ArmGoMid(){
  if(ArmState == PUT){
      slowMove(1,12);slowMove(3,80);slowMove(2,15);delay(1000);slowMove(0,36);
      }else if(ArmState == AWAY){
        slowMove(1,12);slowMove(3,80);slowMove(2,15);delay(1000);slowMove(0,36);
        }
      ArmState = MID;
  }

void ArmGoPut(){
  if(ArmState == FAR){
        slowMove(3,50);slowMove(1,10);slowMove(2,70);slowMove(3,45);slowMove(2,160);slowMove(1,130);slowMove(0,80);
      }else if(ArmState == MID){
        slowMove(3,80);slowMove(1,8);slowMove(2,28);slowMove(3,85);slowMove(2,35);slowMove(2,160);slowMove(3,45);slowMove(1,130);slowMove(0,80);
        }
        ArmState = PUT;
  }

void ArmGoAway(){
  if(ArmState == FAR){
        slowMove(3,50);slowMove(1,10);slowMove(2,70);slowMove(3,110);slowMove(2,90);slowMove(1,130);slowMove(0,80);
      }else if(ArmState == MID){
        slowMove(3,110);slowMove(1,10);slowMove(2,70);slowMove(2,90);slowMove(1,130);slowMove(0,80);
      }
        ArmState = AWAY;
  }

 void PlateGoLeft(){
  plate.write(110);
  delay(600);
  while(true){
    if(digitalRead(2)){
      plate.write(90);
      break;
      }
    }
 }

void PlateGoRight(){
  plate.write(70);
  delay(300);
  while(true){
    if(digitalRead(2)){
      plate.write(90);
      break;
      }
    }
  }


void loop() {

    if(Serial.available()){
    char cmd = Serial.read();
//    Serial.println(cmd);
    if(cmd == 'B'){
      Press_Button();
    }else if(cmd == 'A'){
      Arrange_Cube();
    }
    else if(cmd == 'j'){
      slowMove(4,0);
      digitalWrite(Loose,HIGH);
      digitalWrite(Tight,LOW);
      delay(500);
      digitalWrite(Loose,LOW);
      digitalWrite(Tight,LOW);
      }
      else if(cmd == 'k'){
        PlateGoRight();
        }
  }
}
  
  




