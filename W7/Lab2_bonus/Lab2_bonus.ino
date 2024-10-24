#include <Enerlib.h>
Energy energy;// 
const byte swPin1=2;
const byte swPin2=3;
const byte ledPin=13;
int debounce_delay = 300;

volatile boolean state=0;
volatile boolean light = 0;
void wakeISR(){
  if(debounced()){
    Serial.println("IN interrupt");
      state = !state;
      
    }
}

void blinking(){
  if(debounced()){
    light = !light;
    }
  }

void setup(){
    Serial.begin(9600);
    pinMode(swPin1,INPUT_PULLUP);
    pinMode(swPin2, INPUT_PULLUP);
    pinMode(ledPin,OUTPUT);
    attachInterrupt(1,blinking,LOW);
    attachInterrupt(0,wakeISR,LOW);
    Serial.println("Running...");
}

void loop()
{
    if(state==1){
      Serial.println("Was sleeping...");
      }
    else if(state==2){
      Serial.println("Was awake...");
      }
      Serial.println(light);
      if(light)
          digitalWrite(13,HIGH);
       else
          digitalWrite(13,LOW);
      if(state)
        energy.PowerDown();
    
}

boolean debounced() {                                  
  static unsigned long last_time = 0;                 //在靜態資料區初始化紀錄時間
  unsigned long currenttime = millis();               //呼叫millis函式，設定當前時間
  if ((currenttime - last_time) > debounce_delay) {   //觸發彈跳時，比較當前時間是否比紀錄時間大於彈跳延遲時間
    last_time = currenttime;                          //if為真，更新紀錄時間
    return true;                                      //返回真值
    }  
  else {return false;}                                //if為否，即彈跳誤差，返回否值
  }
