#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <math.h>
const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
const int SEG_data[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
                       {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                       {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                       {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                       {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                       {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                       {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                       {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                       {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                       {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"

int disp[4] ;  //欲顯示數字
//MPU-6050設定
MPU6050 accelgyro;        // 預設 I2C 位址為 0x68
int16_t ax, ay, az, gx, gy, gz;
int16_t angleX, angleY, angleZ;
int16_t oldX = 6;
int16_t oldY = 0;
int16_t oldZ = 0;
//全域變數設定
    /* Do something */
const double number = 180 / M_PI;
int steps = 0;
int currentstep = 0;
void setup()
{
  Serial.begin(115200);
  accelgyro.initialize();
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
  }
}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    /* Do something */
  angleX = atan(ax / sqrt(pow(ay,2) + pow(az,2))) * number;
  angleY = atan(ay / sqrt(pow(ax,2) + pow(az,2))) * number;
  angleZ = atan(sqrt(pow(ay,2) + pow(ax,2) / az)) * number;
  /*Serial.print("Angle X-axis");
  Serial.println(angleX);
  Serial.print("Angle Y-axis");
  Serial.println(angleY);
  Serial.print("Angle Z-axis");
  Serial.println(angleZ);*/
  
  if(abs(angleX-oldX) > 30){
    oldX = angleX;
    steps++;
    Serial.print("Steps ");
    Serial.println(steps);
    }
   else if(abs(angleY-oldY) > 30){
    oldY = angleY;
    steps++;
    Serial.print("Steps ");
    Serial.println(steps);
    }
    else{
      steps = steps;
      }
  
  number_transfer(steps);
  
    for(int i=0; i<=3; i++){  //個、十、百、千位數
      digitalWrite(SEG_COM[3-i], LOW);  //觸發第i位數顯示數字
      SEG_Drive(disp[i]);  //資料線寫入數值
      delay(5);
      digitalWrite(SEG_COM[3-i], HIGH);  //結束觸發第i位數
    }
  
 
}

void number_transfer(int Num){  //四位數拆成四個獨立的數字，存入陣列disp[]中
  disp[0] = Num/1000;
  disp[1] = Num/100%10;
  disp[2] = Num/10%10;
  disp[3] = Num%10;
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  bool Number[8];
  for(int i=0; i<8; i++)
  {
    if(SEG_data[number][i] == 1)
    {
      Number[i] = HIGH;
    }
    else if(SEG_data[number][i] == 0)
    {
      Number[i] = LOW;
    }
  }
  for(int i=2; i<=9; i++)
  {
    digitalWrite(i, Number[i-2]);
  }
}
