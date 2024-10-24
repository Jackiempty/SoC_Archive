#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define LED 2        //使用 ESP32 內建 LED
const int s0 = 17;  
const int s1 = 18;  
const int S2 = 26;  
const int S3 = 27;  
const int out = 25;   
// LED pins connected to Arduino
int redLed = 21;  
int greenLed = 22;  
int blueLed = 23;
// Variables  
float red = 0;  
float green = 0;  
float blue = 0;  
String color = "";

// 紀錄量測間隔時間，因為數值較大，用 unsigned long
unsigned long previousMillis = 0;

// 每 n 秒量測，1000->1秒，2000->2秒
const long interval = 2000;

const char* ssid = "Plu65"; //Wi-Fi 網路名稱
const char* password = "0970427573"; //Wi-Fi 密碼


// 建立 MQTT 連線所需的 client ID，可使用隨機生成
String mqtt_ClientID = "mqttClientID";  
 
// 定義 MQTT 連線時，用來識別 publish/subscribe 資料類別的 topic
// 請依照組別更改groupX
const char* sub_topic = "group1/esp32mqtt";
const char* pub_led_topic = "group1/esp32s_led_state";  // 控制 ESP32 上的 LED
const char* pub_init_topic = "group1/esp32s_is_back";   // 確認 ESP32 與 MQTT broker 已連線
const char* pub_red_topic = "group1/esp32s_red";      // 傳輸溫度
const char* pub_green_topic = "group1/esp32s_green";      // 傳輸溫度
const char* pub_blue_topic = "group1/esp32s_blue";      // 傳輸溫度
const char* pub_color_topic = "group1/esp32s_color";      // 傳輸溫度
 
// EMQX MQTT broker 的連線資訊
const char *mqtt_server = "broker.emqx.io";  // broker 所在的網址
const char *mqtt_userName = "emqx";  // EMQX broker 的公用帳號
const char *mqtt_password = "public";  // EMQX broker 的公用密碼

// 初始 Wi-Fi client 與 MQTT client 連線
WiFiClient espClient;
PubSubClient client(espClient);

// 初始化儲存溫度與濕度的變數
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
char msg1[MSG_BUFFER_SIZE];
char msg2[MSG_BUFFER_SIZE];
char msg3[MSG_BUFFER_SIZE];

 
void setup_wifi() { // 設定 Wi-Fi 連線
  delay(10);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA); //設置 Wi-Fi 模式
  WiFi.begin(ssid, password); 

  Serial.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Wi-Fi Connected.");

  randomSeed(micros());

  // 連線成功後將連線的 IP 資訊印出
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//接收 MQTT broker subscribe 來的資訊 (LED 亮暗)
void callback(char *topic, byte *payload, unsigned int length) { // 資訊包含 topic 與 topic 內的資料
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  payload[length] = '\0';
  String message = (char *)payload;  // 儲存 topic 內的資料 payload 到 message 裡

  // 驗證傳來的 topic 是我定義中要求的 topic
  // strcmp 會比較()內兩個字串，相同的話回傳 0，不同的話會輸出差幾個字母數，並用正負表示哪邊比較大
  if (strcmp(topic, sub_topic) == 0) {

    if (message == "off") {
      digitalWrite(LED, LOW);  // 收到 off 關掉 ESP32 的 LED
      client.publish(pub_led_topic, "off");
    }
    if (message == "on") {
      digitalWrite(LED, HIGH);  // 收到 on 開啟 ESP32 的 LED
      client.publish(pub_led_topic, "on");
    }
  }
}
 
void reconnect() {
  // 對 MQTT 進行連線建立，若未建立成功會持續在此循環
  while (!client.connected()) {
    Serial.println("Attempting EMQX MQTT connection...");
    // 用亂數確保建立唯一的 ClientID
    mqtt_ClientID += String(random(0xffff), HEX);
    // 嘗試建立連線
    if (client.connect((mqtt_ClientID, mqtt_userName, mqtt_password)))
    {
      Serial.print(" connected with Client ID: ");
      Serial.println(mqtt_ClientID);
      // 若建立成功，可在其他裝置訂閱 pub_init_topic 收到 "Hi, I'm online!" 的訊息
      client.publish(pub_init_topic, "Hi, I'm online!");
      // 重新接收資料
      client.subscribe(sub_topic);
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      // 可於此查詢連線失敗原因編碼
      // https://github.com/knolleary/pubsubclient/blob/master/src/PubSubClient.h
      Serial.println(" try again in 5 seconds");
      // 若 MQTT 連線失敗，每 5 秒重試
      delay(5000);
    }
  }
}
 
void setup() { 

  pinMode(LED, OUTPUT);  // 將 LED Pin 腳位設為輸出
  digitalWrite(LED, LOW);  // 將 LED Pin 腳位設為數位輸出(0V/5V)，並預設為低(0V)

  pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
   
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);
  pinMode(out, INPUT);
    
    
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT); 

  Serial.begin(9600);
  
  setup_wifi(); // 進入設定 Wi-Fi 連線的 void function

  client.setServer(mqtt_server, 1883); // 設定 MQTT broker 的連線
  client.setCallback(callback);  // 接收從其他 MQTT client 傳來的資料
}
 
void loop() {
  
  if (!client.connected())  {  // 若 MQTT 連線建立失敗就重新連線
      reconnect();
  }
  client.loop();


  //使用感光模組
  //使用 millis 做間隔，每 2 秒讀一次
  unsigned long currentMillis = millis();

    Color(); 
    Serial.print("R Intensity:");  
    Serial.print(red, 1);  
    Serial.print(" G Intensity: ");  
    Serial.print(green, 1);  
    Serial.print(" B Intensity : ");  
    Serial.print(blue, 1); 

      if (red > blue && red > green && red > 235)
  {  
    digitalWrite(redLed, HIGH);  
    color = "RED";
  }  
    if (green > blue && green > red && green > 235)
    {  
        digitalWrite(greenLed, HIGH);  
        color = "GREEN";
    }
    if (blue > red && blue > green && blue > 235)
    {  
        digitalWrite(blueLed, HIGH);  
        color = "BLUE";
    } 
    
    delay(300);   
    digitalWrite(redLed, HIGH);  
    digitalWrite(greenLed, HIGH);  
    digitalWrite(blueLed, HIGH);  

    snprintf(msg, MSG_BUFFER_SIZE, "%.0lf", red); //印出溫度
    snprintf(msg1, MSG_BUFFER_SIZE, "%.0lf", green); //印出溫度
    snprintf(msg2, MSG_BUFFER_SIZE, "%.0lf", blue); //印出溫度
    snprintf(msg3, MSG_BUFFER_SIZE, "%s", color); //印出溫度

    //Serial.print("Publish message: ");
    //Serial.print(msg1);

    client.publish(pub_red_topic, msg);  // 綁定 topic，發送溫度
    client.publish(pub_green_topic, msg1);
    client.publish(pub_blue_topic, msg2);
    client.publish(pub_color_topic, msg3);
    


}

void Color()  //感光模組讀取顏色數值
{    
  //請設定s2,s3腳位的電位來選擇不同色光的濾波器
  //讀取紅色光
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = 255-pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  //讀取藍色光
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = 255-pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  //讀取綠色光
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = 255-pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  green = 255-pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
