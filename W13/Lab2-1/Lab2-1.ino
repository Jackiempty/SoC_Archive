#include <WiFi.h>
#include <ESPAsyncWebServer.h>

//設定腳位
//顏色感測器腳位
//to do 
const int S0 = 17;
const int S1 = 18;
const int S2 = 26;
const int S3 = 27;
const int LED = 16;
const int out = 25;
// LED pins connected to Arduino
//to do 
const int redLed = 21;
const int greenLed = 22;
const int blueLed = 23;
// Variables  
int red = 0;  
int green = 0;  
int blue = 0;  
String color = "";

const char* ssid = "Plu65"; //Wi-Fi 網路名稱
const char* password = "0970427573"; //Wi-Fi 密碼

// 建立一個非同步伺服器在通訊埠 80
AsyncWebServer server(80);

// 建立網頁
// 網頁大小相對大但是架構不會變，一般存變數的動態記憶體不足
// 要存在儲存程式程序的flash記憶體中，所以呼叫PROGMEM
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  
  <!--設定字體-->
  <style>   
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p  { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .color-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    // div{
    //   vertical-align:middle;
    //   font-size: 1.5rem;
    // }
    .b {height: 100px; width:100px;}
  </style>
</head>

<!--建立網頁內容-->
<body>    
  <h2>ESP32 COLOR Server</h2>
  <p>
     <span class="color-labels">red:</span> 
     <span id="red">%red%</span>
     <sup class="units"></sup>
  </p>
  <p>
     <span class="color-labels">green:</span> 
     <span id="green">%green%</span>
     <sup class="units"></sup>
  </p>
  <p>
     <span class = "color-labels">blue:</span>
     <span id="blue">%blue%</span>
     <sup class = "units"></sup>
  </p>
  <div class = "color-block" style="width:device-width;height:60px;border:3px #cccccc dashed;vertical-align:middle;font-size: 1.5rem;">
    <b id = "color">%color%</b>
  </div>
</body>

<script>
var color = "%color%";
setInterval(function ( ) {    <!--將紅色光資料傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("red").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/red", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {    <!--將綠色光資料傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("green").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/green", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {    <!--將藍色光資料傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("blue").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/blue", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {    <!--將顏色資料傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("color").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/color", true);
  xhttp.send();
}, 1000 ) ;

</script>
</html>)rawliteral";

// 抓取最新的顏色資料
String processor(const String& var) {
  //Serial.println(var);
  if (var == "red") {
    return String(red);
  }
  else if(var == "green")
  {
    return String(green);
  }
  else if(var == "blue"){
    return String(blue);
  }
  else if(var == "color"){
    return String(color);
  }

  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(9600);
  
    // Connect to Wi-Fi
    // to do 
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);


    //設定腳位
    // to do 
    pinMode(out, INPUT);
    pinMode(LED, OUTPUT);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT); 

    digitalWrite(LED, HIGH); 
    digitalWrite(S0, HIGH); 
    digitalWrite(S1, HIGH);   

  Serial.print("Wi-Fi Connecting");

  // 當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Wi-Fi Connected.");



  // 查詢 ESP32 的 local IP 並印出，在瀏覽器輸入此 IP 即可看到畫面
  Serial.println(WiFi.localIP());
  
  server.begin();

  // 在伺服器上建立網頁
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  }); //建立主網頁
  server.on("/red", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(red).c_str());
  }); //建立顏色顯示的網頁
  server.on("/green", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(green).c_str());
  }); //建立顏色顯示的網頁
  server.on("/blue", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(blue).c_str());
  }); //建立顏色顯示的網頁
  server.on("/color", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(color).c_str());
  }); //建立顏色顯示的網頁

  server.begin();  // 啟動伺服器
}

void loop() {
  // 建立量測顏色的迴圈
  // 因為網頁伺服器不能使用 delay 函數，所以用 millis
  // millis 用運算的次數來計算時間，更為準確，也不會阻擋程式運作
  // delay 函數運作時會完全停止程式運作，使網頁伺服器出錯
  
  //使用顏色感測器讀取顏色數值
  //
  Color(); 
  Serial.println("R Intensity: ");  
  Serial.print(red, DEC);  
  Serial.println(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.println(" B Intensity : ");  
  Serial.print(blue, DEC); 
  
  //已寫完紅色光的部分，請自行加入綠色光跟藍色光的部分
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
  digitalWrite(redLed, LOW);  
  digitalWrite(greenLed, LOW);  
  digitalWrite(blueLed, LOW);  

  Serial.println(WiFi.localIP());
}

void Color()  //顏色感測器讀取數值
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
}
