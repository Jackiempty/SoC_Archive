#include <Wire.h>
const int INT7 = 2;
const int INT2 = 4;
const int INT3 = 5;
const int INT4 = 6;
const int ENA  = 3;
const int ENB  = 9;  
int PWM1 = 125;
int PWM2 = 125;

int trigPin1 = 13, trigPin2 = 11;
int echoPin1 = 12, echoPin2 = 10;
double du1, cm1;
double du2, cm2;   
const float soundspeed = 0.034;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
void setup() {
  Serial.begin(9600);
  pinMode(INT7, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode (trigPin1, OUTPUT);
  pinMode (echoPin1, INPUT);
  
  pinMode (trigPin2, OUTPUT);
  pinMode (echoPin2, INPUT);
}

void loop() {
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  du1 = pulseIn(echoPin1, HIGH);

  delay(20);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  du2 = pulseIn(echoPin2, HIGH);

  
  
  cm1 = (du1/2)*soundspeed;
  cm2 = (du2/2)*soundspeed;

  Serial.print("cm1");
  Serial.println(cm1);

  Serial.print("cm2");
  Serial.println(cm2);

  if( 15<cm1 && cm1<25 && 15<cm2 && cm2<25)
  {
    Serial.println("STOP");
    STOP();
  }
  else if(cm1<15 && cm2<15)
  {
    BACK();
    Serial.println("BACK");
  }
  else if( 25<cm1 && cm1<50 && 25<cm2 && cm2<50)
  {
    Front();
    Serial.println("Frint");
  }
  else if( 0<cm1 && cm1<25 && 15<cm2 && cm2<50)
  {
    left();
    Serial.println("left");
  }
  else if( 15<cm1 && cm1<50 && 0<cm2 && cm2<25)
  {
    right();
    Serial.println("right");
  }
  

}

void BACK(){
  M1Front();
  M2Front();
  }

void Front(){
  M1BACK();
  M2BACK();
  }
void right(){
  M1BACK();
  M2STOP();
  }

void left(){
  M1STOP();
  M2BACK();
  }

void STOP(){
  M1STOP();
  M2STOP();
  }
void BackLeft(){
  M1Front();
  M2STOP();
  }

void BackRight(){
  M1STOP();
  M2Front();
  }

void M1Front(){
  digitalWrite(INT7, HIGH);
  digitalWrite(INT2, LOW);
  analogWrite(ENA, PWM1);
  }

void M1BACK(){
  digitalWrite(INT7, LOW);
  digitalWrite(INT2, HIGH);
  analogWrite(ENA, PWM1);
  }

void M1STOP(){
  digitalWrite(INT7, LOW);
  digitalWrite(INT2, LOW);
  analogWrite(ENA, PWM1);
  }

void M2Front(){
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
  analogWrite(ENB, PWM2);
  }

  
void M2BACK(){
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
  analogWrite(ENB, PWM2);
  }

void M2STOP(){
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, LOW);
  analogWrite(ENB, PWM2);
  }
