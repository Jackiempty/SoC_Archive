#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <cmath>
using namespace std;

#define led1 3

int trigPin = 12;
int echoPin = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float duration;
float cm, inches;
float soundspeed=0.034;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1,OUTPUT);
  digitalWrite(led1, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  // ex.給 Trig 高電位，持續 10微秒          
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  
    
  //To do : 算出距離
  cm = (duration/2)*soundspeed; 
  double delay_time = duration/3; //(us)
  Serial.println(cm);

  if(cm>0 && cm<=30)
  {
    digitalWrite(led1, HIGH);
    delay(delay_time);
    digitalWrite(led1, LOW);
    delay(delay_time);
  } 
 
  
  
  //To do : 顯示距離於lcd上
  lcd.setCursor(0,0);
  lcd.print(cm);

}