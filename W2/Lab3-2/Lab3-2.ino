const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
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
//int number = 0;
int timer = 0;

void setup() {
  Serial.begin(9600);
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
  }
}

void loop() {
  timer = millis()/1000;
  number_transfer(timer);  //數值轉換入陣列中
  for(int i=0; i<=3; i++){  //個、十、百、千位數
    digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字
    SEG_Drive(disp[i]);  //資料線寫入數值
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
  }
}

void number_transfer(int Num){  //四位數拆成四個獨立的數字，存入陣列disp[]中
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
