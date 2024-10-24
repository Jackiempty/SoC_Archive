#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

LiquidCrystal_I2C lcd(0x27, 16, 2);// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。 
const int sw_up = 2;    //按鈕1
const int sw_down = 3;    //按鈕2
int count = 0;
bool upOldState = 0;
bool downOldState = 0;
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);//為了下拉電阻設置5v
  pinMode(sw_up, INPUT_PULLUP);  //內建上拉電阻
  pinMode(sw_down,INPUT_PULLUP);
  
}
void loop() {
  bool swstate_up = digitalRead(sw_up);
  bool swstate_down = digitalRead(sw_down);
  Serial.print("Sw_up");
  Serial.println(swstate_down);
  if(swstate_up==LOW && upOldState!= swstate_up){
    count++;
  }
  else if(swstate_down==LOW &&downOldState != swstate_down){
    count--;
  }

  if(upOldState != swstate_up)
    upOldState = swstate_up;

   if(downOldState != swstate_down)
      downOldState = swstate_down;
  
  lcd.setCursor(5,0);//5是空五格，0是第一行
  if(count == 0){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print(0);
    }
    else
      lcd.print(count);
  lcd.setCursor(5,1);
  lcd.print("HELLOWORLD");
}
