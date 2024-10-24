//0.17578125
//8192 2048 1536 1024
//720  180  135  90
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
double timeStart ;
int Count ;
int but[2] = {3, 4};
int state1[5] = {1,1,1,1,1};
int state2[5] = {1,1,1,1,1};
boolean a[] = {1, 1, 0, 0, 0, 0, 0, 1};
boolean b[] = {0, 1, 1, 1, 0, 0, 0, 0};
boolean c[] = {0, 0, 0, 1, 1, 1, 0, 0};
boolean d[] = {0, 0, 0, 0, 0, 1, 1, 1};
boolean CW = 1;
int echoPin = 11;                 //Echo Pin
int trigPin = 12;                 //Trig Pin
float duration;
float cm;
boolean btLastState = 1;
const double SoundVelocity = 0.034364; 
void setup() {
  Serial.begin(9600);
  lcd.init(); //初始化LCD
  lcd.backlight(); //開啟背光
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(but[0],INPUT_PULLUP);
  pinMode(but[1],INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);            // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
}



void loop() {
  
  int IN2 = digitalRead(but[1]);
  Serial.print("cm:");
  Serial.println(cm);
  Serial.print("In2: ");
  Serial.println(IN2);
  Serial.print("CW: ");
  Serial.println(CW);
  if(IN2 == 0){
    delay(1);
      CW = !CW;
  }

   if(CW == true){
    mode360_CW();
   }
   else{
    mode360_CCW(); 
   }
}


void mode360_CCW()
{
  for (int j = 0; j < 512 ; j++) {
    digitalWrite(trigPin,HIGH);
  double timeStart = millis();
  while(millis()-timeStart > 0.01)
    break;
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration*SoundVelocity;
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[i]);
      digitalWrite(8, b[i]);
      digitalWrite(9, c[i]);
      digitalWrite(10, d[i]);
      delayMicroseconds(cm*100+1000);
      Count++;
    }  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("CounterClockwise");
  lcd.setCursor(0, 1); 
  lcd.print("cm : ");
  lcd.print(cm);
}

void mode360_CW() 
{
  for (int j = 0; j < 512 ; j++) {
    digitalWrite(trigPin,HIGH);
  double timeStart = millis();
  while(millis()-timeStart > 0.01)
    break;
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration*SoundVelocity;
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[7-i]);
      digitalWrite(8, b[7-i]);
      digitalWrite(9, c[7-i]);
      digitalWrite(10, d[7-i]);
      delayMicroseconds(cm*100+1000);
      Count++;
    }  
   }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Clockwise");
  lcd.setCursor(0, 1); 
  lcd.print("cm : ");
  lcd.print(cm);
}
