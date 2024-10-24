const byte sw_pin2 = 2;      //開關腳位D2，即中斷腳pin 0
const byte sw_pin3 = 3;      //開關腳位D3，即中斷腳pin 1
const byte led_pin = 13;     //LED第13腳位
volatile int blink_time;     //LED的閃爍時間

int debounce_delay=200;      //設定彈跳延遲時間

void setup() {
  
  pinMode(led_pin, OUTPUT);
  pinMode(sw_pin2, INPUT_PULLUP);         //設定D2為輸入，使用上拉電阻觸發
  pinMode(sw_pin3, INPUT_PULLUP);         //設定D3為輸入，使用上拉電阻觸發
  //設定中斷腳位0以低電位觸發blink_state1函式
  attachInterrupt(0,blink_state1,LOW);
  //設定中斷腳位1以低電位觸發blink_state2函式
  attachInterrupt(1,blink_state2,LOW);
  blink_time = 2000;                       //初始閃爍切換頻率2000ms
  // disable all interrupts
  noInterrupts();
  // TCCR1A Reset 
  TCCR1A = 0;
  // TCCR1B Reset
  TCCR1B = 0;
  // load timer
  TCNT1 = 0;
  // set compare value by OCR1?
  OCR1A = 34286;
  // 256 prescaler
  TCCR1B |= (1 << CS12);
  // set CTC mode by TCCR1?
  TCCR1A |= (1 << WGM12);
  //enable  Timer1 compare interrupt mode by TIMSK?
  TIMSK1 |= (1 << OCIE1A);
  //enable  interrupt 
  interrupts();
}

void loop() {
  
    //設計迴圈或建立新函式
    
  
  }

void blink_state1(){
      if(debounced() == true){
             blink_time = 500;
             OCR1A = 34286/2;
        }
       else {
            blink_time = blink_time;
        }
  }

void blink_state2(){
        if(debounced() == true){
            blink_time = 6000;
            OCR1A = 34286*3;
        }
       else {
            blink_time = blink_time;
        }
  }
ISR(TIMER1_COMPA_vect){
    //create a ISR() to control the routine of Timer1 interrupt and led toggled.
    TCNT1 = 0; 
    digitalWrite(13,!digitalRead(13));
}


//------------------------簡易按鈕去彈跳函式
boolean debounced() {                                  
  static unsigned long last_time = 0;                 //在靜態資料區初始化紀錄時間
  unsigned long currenttime = millis();               //呼叫millis函式，設定當前時間
  if ((currenttime - last_time) > debounce_delay) {   //觸發彈跳時，比較當前時間是否比紀錄時間大於彈跳延遲時間
    last_time = currenttime;                          //if為真，更新紀錄時間
    return true;                                      //返回真值
    }  
  else {return false;}                                //if為否，即彈跳誤差，返回否值
  }
