#include  <BluetoothSerial.h> //導入 Bluetooth 程式庫
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 設定 LCD I2C 位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。

BluetoothSerial BT; //宣告 BT 為藍芽通訊物件
char var;
bool start = false;
int time_all = (1 * 600) + (5 * 10) + (0);    //設定時間
int time_min = 0;
int time_sec = 0;
int time_ms = 0;
double time_start = 0.0;
double time_pass = 0.0;
double oldTime = 0.0;
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  BT.begin("ESP32_7");   //設定藍芽名稱為 ESP32_組別號碼
  time_min = time_all / 600;
      time_sec = (time_all - time_min *600) / 10;
      time_ms =  (time_all-time_min*600 - time_sec * 10);
      lcd.print(time_min);
      lcd.print(':');
      lcd.print(time_sec);
      lcd.print(':');
      lcd.print(time_ms);
      lcd.setCursor(3,0);
}

void loop() {
  if (BT.available()) {   //若收到藍牙終端的資料，則執行特定指令
    var = BT.read();
    if(var == '1'){         //若收到1則開始/暫停
      
      start = !start;
      double time_start = millis();
      Serial.print("start");
      Serial.println(start);
      
    }
  }
  if(start == true){
    time_pass = (millis()-time_start)/100;
    Serial.print("time pass");
    Serial.println(time_pass);
    if(time_pass - oldTime >= 1){
      time_all = time_all-1;
      time_min = time_all / 600;
      time_sec = (time_all - time_min *600) / 10;
      time_ms =  (time_all-time_min*600 - time_sec * 10);
    lcd.print(time_min);
    lcd.print(':');
    lcd.print(time_sec);
    lcd.print(':');
    lcd.print(time_ms);
    
    lcd.setCursor(3,0);
    oldTime = time_pass;
    }
  }
}
