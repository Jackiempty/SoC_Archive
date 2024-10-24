const int SEG_COM[4] = {A1, A2, A3, A4};  //控制線
const int SEG_data[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
                       {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                       {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                       {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                       {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                       {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                       {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                       {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                       {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                       {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"
int disp[4];  //顯示數字

int echoPin = 11;                 //Echo Pin
int trigPin = 12;                 //Trig Pin
float cm;                  
float duration;
float soundspeed=0.034;


void setup() {

  Serial.begin (9600);                 // Serial Port begin

  for(int i=2; i<=9; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);             //共陽極
  } 

  for(int i=0; i<=3; i++){
    pinMode(SEG_COM[i], OUTPUT);
    digitalWrite(SEG_COM[i], HIGH);    //共陽極
  } 

  pinMode(trigPin, OUTPUT);            // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
}

void loop() {
    
  // To do:給 Trig 高電位，持續 10微秒
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
    
    
  //To do:算出距離
  cm = (duration/2)*soundspeed; 
  double delay_time = duration/2; //(us)
  cm*=10;
  // Serial.println(cm);

  //To do:顯示在7段顯示器
  number_transfer(cm);  //數值轉換入陣列中
  for(int i=0; i<=3; i++){  //個、十、百、千位數
    digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字
    SEG_Drive(disp[i]);  //資料線寫入數值
    if (i==2)
    {
      digitalWrite(9, HIGH);
    }
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
    
  }
  
}

void number_transfer(int Num){  //四位數拆成四個獨立的數字，存入陣列disp[]中
  // Serial.print("num");
  // Serial.println(Num);
  disp[0] = Num/1000;
  disp[1] = Num/100%10;
  disp[2] = Num/10%10;
  disp[3] = Num%10;
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  bool Number[8];
  for(int i=0; i<8; i++)
  {
    if(SEG_data[number][i] == 1)
    {
      Number[i] = HIGH;
    }
    else if(SEG_data[number][i] == 0)
    {
      Number[i] = LOW;
    }
  }
  for(int i=2; i<=9; i++)
  {
    digitalWrite(i, Number[i-2]);
  }
}

