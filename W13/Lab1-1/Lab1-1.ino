#include <WiFi.h> //Wi-Fi 程式庫
#include <Wire.h> //I2C 程式庫
#include <LiquidCrystal_I2C.h> //LCD_I2C 模組程式庫

LiquidCrystal_I2C lcd(0x27, 16, 2);

int section=8;
//輸入網路名稱與密碼
const char* ssid = "Plu65"; //Wi-Fi 網路名稱
const char* password = "0970427573"; //Wi-Fi 密碼
const char *ntpServer = "pool.ntp.org"; //校時伺服器
long  gmtOffset_sec = section*3600;  //格林威治時間, GMT+8 就是 8*3600
const int   daylightOffset_sec = 0; //日光調節時間, 有為 3600, 沒有則為 0
const int debounce_delay = 500;
int button1 = 19;
void setup(){
    Serial.begin(9600);
    //設定按鈕
    pinMode(button1,INPUT_PULLUP);

    //初始化LCD
    lcd.init();
    lcd.backlight();
    
    //Connect to Wi-Fi
    WiFi.mode(WIFI_STA); //設置 Wi-Fi 模式
    WiFi.begin(ssid, password); 

    Serial.print("Wi-Fi Connecting");

    //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
    while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(500);   
    }

    Serial.println("");
    Serial.print("Wi-Fi Connected.");

    
    //取得網路時間
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    
    //連上拿到時間資料後就切斷連線
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

void loop(){
    delay(1000);
    
    printLocalTime();  
}

bool debounced(){
  static unsigned long last_time = 0;                 //在靜態資料區初始化紀錄時間
  unsigned long currenttime = millis();               //呼叫millis函式，設定當前時間
  if ((currenttime - last_time) > debounce_delay) {   //觸發彈跳時，比較當前時間是否比紀錄時間大於彈跳延遲時間
    last_time = currenttime;                          //if為真，更新紀錄時間
    return true;                                      //返回真值
    }  
  else {return false;}    
  }

void printLocalTime(){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    //切換時區
    //do something
    
    int state = digitalRead(button1);
    
    if( state == LOW){
        if(debounced() == true){
          Serial.println("success");
          section = (section+1)%24;
          }
      }

      gmtOffset_sec = section*3600;

    //顯示於 LCD 螢幕
     lcd.setCursor(0, 0);
     lcd.print(&timeinfo,"%Y");   //YEAR
     lcd.print(" ");
     lcd.print(&timeinfo,"%B");   //MONTH
     lcd.print(" ");
     lcd.print(&timeinfo,"%d");   //DAY


     lcd.setCursor(0, 1);
     lcd.print(&timeinfo,"%H");   //HOUR
     lcd.print(":");
     lcd.print(&timeinfo,"%M");   //MIN
     lcd.print(":");
     lcd.print(&timeinfo,"%S");   //SEC
     lcd.print(" ");
     //顯示時區
     //do something
     lcd.print(section);
      
}
