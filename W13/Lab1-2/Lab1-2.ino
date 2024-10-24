#include <WiFiClient.h> //WiFi 程式庫
#include <Wire.h> // I2C 程式庫
#include <TridentTD_LineNotify.h> //Line 程式庫
#include "DHT.h"  // DHT11 程式庫
#include <WiFi.h> //Wi-Fi 程式庫

#define LINE_TOKEN "6dwUG9IxRL0ciUfizCgtixK11GojtF0mu6yZA58apYl" //修改成上述的 Token 號碼
#define DHTTYPE DHT11
#define DHTPIN 22

const char* ssid = "Plu65"; //Wi-Fi 網路名稱
const char* password = "0970427573"; //Wi-Fi 密碼

float humidity, temp_c; //從 DHT11 讀取的值

DHT dht(DHTPIN, DHTTYPE); //啟動 DHT 程式庫
 
void setup(void)
{
  Serial.begin(9600);

  //設置 Wi-Fi 模式
  //to do 
  WiFi.mode(WIFI_AP_STA);

  Serial.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);   
  }

  Serial.println("");
  Serial.print("Wi-Fi Connected.");
  
  Serial.println(LINE.getVersion());  //顯示 Line 版本
  LINE.setToken(LINE_TOKEN);    //設定要傳送至的聊天室 Token
  dht.begin();
}
 
void loop(void)
{
  //每10秒傳送溫濕度訊息到聊天室
  temp_c = dht.readTemperature(); //讀取溫度(攝氏)
  //需補上濕度的程式碼 
  //to do
  humidity = dht.readHumidity();


  if (isnan(humidity) || isnan(temp_c)) { // 如果讀取到的溫溼度有異
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    
  //傳送至 Token 的聊天室
  //to do 
  
  String tempe="溫度:"+String(temp_c)+"℃";   
  String humid="濕度:"+String(humidity)+"％";

  // 顯示 Line版本
  Serial.println(LINE.getVersion());
 
  LINE.setToken(LINE_TOKEN);

  // 先換行再顯示
  LINE.notify("\n" + tempe + " ；" + humid);
      
  // 每2分鐘發送一次(delay120000)
  delay(10000);
    
}