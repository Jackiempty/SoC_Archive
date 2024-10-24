#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <cmath>
using namespace std;

#define led1 3
#define led2 4
#define led3 5


int trigPin = 12;
int echoPin = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float duration;
int cm;
float soundspeed=0.034;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1,OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2,OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(led3,OUTPUT);
  digitalWrite(led3, LOW);
  lcd.init();
  lcd.backlight();
}

void loop() {

    
  // ex.給 Trig 高電位，持續 10微秒          
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  
    
  //To do : 算出距離
  cm = (duration/2)*soundspeed; 
  double delay_time = duration/2; //(us)
  Serial.println(cm);
  if(cm>0 && cm<=20)
  {
    digitalWrite(led1, HIGH);
    delay(delay_time);
    digitalWrite(led1, LOW);
    delay(delay_time);
  } 
  else if(cm>20 && cm<=40)
  {
    delay_time/=2;
    digitalWrite(led2, HIGH);
    delay(delay_time);
    digitalWrite(led2, LOW);
    delay(delay_time);
  }
  else if(cm>40 && cm<=60)
  {
    delay_time/=3;
    digitalWrite(led3, HIGH);
    delay(delay_time);
    digitalWrite(led3, LOW);
    delay(delay_time);
  }
  else if(cm>60)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  
  //To do : 顯示距離於lcd上
  lcd.setCursor(0,0);
  lcd.print(cm);

}