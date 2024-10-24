#include <Keypad.h>   //引用Keypad函式庫
#define KEY_ROWS 4    //按鍵模組的列數
#define KEY_COLS 4    //按鍵模組的行數

//Keypad設定
const byte colPins[4] = {2, 3, 4, 5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = { {'1','2','3','A'}, 
                                          {'4','5','6','B'}, 
                                          {'7','8','9','C'},
                                          {'*','0','#','D'} };
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);
float num[10], num_reg[99], ans;
char oper[99];

int oper_num = 0;
int pos_op = 0;

int load_ind = 0;
int digit = 0;



void setup() {  
  Serial.begin(9600);
  clr();
}

void loop() {
  char key = myKeypad.getKey();
    if(key != NO_KEY && (key =='1'|| key =='3'|| key =='4'|| key =='5'|| key =='6'|| key =='7'|| key =='8'|| key =='9'|| key =='0')) {     //輸入數字
      Serial.print(key);
      num_reg[load_ind + digit] = atoi(key);
      digit++;
      delay(100);
    }

    if(key != NO_KEY && (key =='A'|| key =='B'|| key =='C'|| key =='D')) {     //輸入符號
      Serial.print(key);
      oper[pos_op] = key; // load operator
      pos_op++; 

      while(digit >= 0){    // load operand
        num[oper_num] = num[oper_num] + num_reg[load_ind] * (10^digit);
        digit--; load_ind++;
      }
      oper_num++;           //go to next operand
      delay(100);
    }

    if(key != NO_KEY && key =='#') {     // 輸入等號
      Serial.print(key);
      ans = num[0];
      for(int i=0; oper[i] != '\0'; i++){

        switch(oper[i]){
          case 'A':
            ans = ans + num[i+1];
            break;
          case 'B':
            ans = ans - num[i+1];
            break;
          case 'C':
            ans = ans * num[i+1];
            break;
          case 'D':
            ans = ans / num[i+1];
            break;
          default:
            break;
        }
      }
      delay(100);
    }

    if(key != NO_KEY && (key =='*')) { //輸入'*'
      Serial.print(key);
      clr();
      delay(100);
    }
}

void clr() //清空數值
{
  oper_num = 0;
  pos_op = 0;
  digit = 0;

  memset(num, 0, sizeof num);
  memset(oper, 0, sizeof oper);
}
