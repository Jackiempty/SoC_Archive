#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int trigPin1 = 9, trigPin2 = 12;
int echoPin1 = 8, echoPin2 = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);

double du1, cm1;
double du2, cm2;
const float soundspeed = 0.034;
void setup() {
  Serial.begin (9600);
  pinMode (trigPin1, OUTPUT);
  pinMode (echoPin1, INPUT);
  
  pinMode (trigPin2, OUTPUT);
  pinMode (echoPin2, INPUT);
  
  lcd.init();                 //設定lcd
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  du1 = pulseIn(echoPin1, HIGH);

  delay(200);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  du2 = pulseIn(echoPin2, HIGH);

  cm1 = (du1/2)*soundspeed;
  cm2 = (du2/2)*soundspeed;
  
  lcd.clear();
  lcd.setCursor(0,0);
  if( 15<cm1 && cm1<25 && 15<cm2 && cm2<25)
  {
    Serial.println("Stop");
    lcd.print("Stop");
  }
  else if(cm1<15 && cm2<15)
  {
    Serial.println("Back");
    lcd.print("Back");
  }
  else if( 25<cm1 && cm1<50 && 25<cm2 && cm2<50)
  {
    Serial.println("Forward");
    lcd.print("Forward");
  }
  else if( 0<cm1 && cm1<25 && 15<cm2 && cm2<50)
  {
    Serial.println("Left");
    lcd.print("Left");
  }
  else if( 15<cm1 && cm1<50 && 0<cm2 && cm2<25)
  {
    Serial.println("Right");
    lcd.print("Right");
  }
  //Serial.print("1: %d 2: %d ", cm1, cm2);
  lcd.setCursor(0, 1);
  lcd.print(cm1);
  lcd.setCursor(6, 1);
  lcd.print(cm2);

   /*
    * dosomething        // 判斷不同超音波到的距離關係，給定所屬區域 
    */

  delay (10) ;
}