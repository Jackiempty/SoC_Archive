#include <Keypad.h> //引用Keypad函式庫
#define KEY_ROWS 4 //按鍵模組的列數
#define KEY_COLS 4 //按鍵模組的行數

const byte colPins[4] = {2, 3, 4, 5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = {
    {'1','2','3','A'}, 
    {'4','5','6','B'}, 
    {'7','8','9','C'},
    {'*','0','#','D'}
};
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);
int number = 0;

void setup(){
    Serial.begin(9600);
    for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
    }
}

void loop() {
  number_transfer(number);  //數值轉換入陣列中
  for(int i=0; i<=3; i++){  //個、十、百、千位數
    digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字
    SEG_Drive(disp[i]);  //資料線寫入數值
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
  }
}

void number_transfer(int Num){  //四位數拆成四個獨立的數字，存入陣列disp[]中
  disp[0] = Num/100
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
