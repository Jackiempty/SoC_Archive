const int Led[5] = {8, 9, 10, 11, 12};    //LED
const int sw_up = 2;    //按鈕1
const int sw_down = 3;    //按鈕2
int pos = 2;  //初始亮LED位置

void setup() {
  for(int i=0; i<5; i++){
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
  }
  digitalWrite(Led[2], HIGH);
  pinMode(sw_up, INPUT_PULLUP);  //內建上拉電阻
  pinMode(sw_down,INPUT);
}

void loop() {
  bool swstate_up = digitalRead(sw_up);
  bool swstate_down = digitalRead(sw_down);
  if(swstate_up==LOW){
    digitalWrite(Led[pos], LOW);
    pos--;
    if(pos <0 ){
      pos = 4;
    }
    digitalWrite(Led[pos], HIGH);
    delay(100);
  }
  else if(swstate_down==HIGH){
    
    digitalWrite(Led[pos], LOW);
    pos++;
    pos = pos % 5;
    digitalWrite(Led[pos], HIGH);
    delay(100);
  }
}
