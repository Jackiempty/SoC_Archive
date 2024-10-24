#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <String.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。 
const int sw_up = 2;    //按鈕1
const int sw_down = 3;    //按鈕2
int count = 0;
int flash = 0;
bool upOldState = 0;
bool downOldState = 0;
String birthday[3] = {"911129", "910123", "900310"};
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
 
  
  
  while(flash < 3){
    lcd.backlight();
    lcd.setCursor(5,0);
    lcd.print("First Group");
    lcd.setCursor(0,1);
    lcd.print("has three people");
    delay(250);
    lcd.noBacklight();
    flash++;
    delay(250);
    }
    if(flash == 3){
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5,0);
    lcd.print("User Serial");
    lcd.setCursor(3,1);
    lcd.print("monitor");
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    flash++;
    }
   
   int num = Serial.read() - 48;
   Serial.print(num);
   lcd.print(birthday[num]);
   delay(1000);
   lcd.setCursor(3,0);
   
}
