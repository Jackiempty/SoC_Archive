//0.17578125
//8192 2048 1536 1024
//720  180  135  90
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int t = 1000;
int Count ;
int but[2] = {3, 4};
int state1[5] = {1,1,1,1,1};
int state2[5] = {1,1,1,1,1};
boolean a[] = {1, 1, 0, 0, 0, 0, 0, 1};
boolean b[] = {0, 1, 1, 1, 0, 0, 0, 0};
boolean c[] = {0, 0, 0, 1, 1, 1, 0, 0};
boolean d[] = {0, 0, 0, 0, 0, 1, 1, 1};
boolean CW = 1;

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
}



void loop() {

  int IN1 = digitalRead(but[0]);
  int IN2 = digitalRead(but[1]);
  Serial.print("In1: ");
  Serial.println(IN1);
  Serial.print("In2: ");
  Serial.println(IN2);
  
  if (state1[0] == 0 && state1[1] == 0 && state1[2] == 0 && state1[3] == 0 && state1[4] == 0 && IN1==1)
  {
    mode720();
  }
  else if (state1[4] == 0 && IN1==1)
  {
    mode90();
  }
  
  if (state2[0] == 0 && state2[1] == 0 && state2[2] == 0 && state2[3] == 0 && state2[4] == 0 && IN2==1)
  {
    mode135();
  }
  else if (state2[4] == 0 && IN2==1)
  {
    mode180();
  }
  
  delay(200);            //To do:該怎麼delay才能達到計時2秒的效果?

  for(int i=0;i<=3;i++)
  {
    state1[i] = state1[i + 1];
    state2[i] = state2[i + 1];
    Serial.print(state1[i]);
  }
  state1[4] = IN1;
  state2[4] = IN2;
}


void mode90()
{
  for (int j = 0; j < 128 ; j++) {
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[i]);
      digitalWrite(8, b[i]);
      digitalWrite(9, c[i]);
      digitalWrite(10, d[i]);
      delayMicroseconds(t);
      Count++;
    }  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("E24101018");
  lcd.setCursor(0, 1); 
  lcd.print("Steps : ");
  lcd.print(Count);
}

void mode135() 
{
  for (int j = 0; j < 192 ; j++) {
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[7-i]);
      digitalWrite(8, b[7-i]);
      digitalWrite(9, c[7-i]);
      digitalWrite(10, d[7-i]);
      delayMicroseconds(t);
      Count++;
    }  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("E24101018");
  lcd.setCursor(0, 1); 
  lcd.print("Steps : ");
  lcd.print(Count);
}

void mode180() 
{
  for (int j = 0; j < 256 ; j++) {
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[7-i]);
      digitalWrite(8, b[7-i]);
      digitalWrite(9, c[7-i]);
      digitalWrite(10, d[7-i]);
      delayMicroseconds(t);
      Count++;
    }  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("E24101018");
  lcd.setCursor(0, 1); 
  lcd.print("Steps : ");
  lcd.print(Count);
}

void mode720() 
{
    for (int j = 0; j < 1024 ; j++) {
    for (int i = 0; i < 8 ; i++) {
      digitalWrite(7, a[i]);
      digitalWrite(8, b[i]);
      digitalWrite(9, c[i]);
      digitalWrite(10, d[i]);
      delayMicroseconds(t);
      Count++;
    }  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("E24101018");
  lcd.setCursor(0, 1); 
  lcd.print("Steps : ");
  lcd.print(Count);
}
