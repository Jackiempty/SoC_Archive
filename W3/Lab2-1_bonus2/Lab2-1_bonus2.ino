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

//全域變數設定

char buffer[8];
int correct;
int pos = 0;
int button_num = 0;
int head = 99;
    /* Do something */
void True_OR_False(int buffer_index);
void setup()
{  
  Serial.begin(115200);
  randomSeed(analogRead(A5));
  correct = random(99);
  
}

void loop()
{
//輸入答案

  char customKey = myKeypad.getKey();
  
    if (customKey != NO_KEY && customKey!='#' && customKey!='*' && customKey!= 'A' && customKey!='B' && customKey!='C' && customKey!='D'){
      Serial.println(customKey);
      if (pos == 2) {
        Serial.println("buffer full");
      }
      else {
        buffer[pos] = customKey;
        delay(100);
        pos++;
      }
    }
   
    


    if(customKey == '#' && pos==2)
    {
      
      True_OR_False(2);
    }
  
}

void True_OR_False(int buffer_index)
{
  //Serial.println(correct);
  int guess_num = 0;
  for(int i=0;i<buffer_index;i++){
      guess_num = guess_num +(buffer[i]-48)*pow(10,1-i);
      Serial.println(guess_num);
    }
    
    if(guess_num > correct){
    head = guess_num;
    Serial.print("The range is : ");
    Serial.print(button_num ); 
    Serial.print("to");
    Serial.println(head);
    }
    else if(guess_num < correct){
    button_num = guess_num; 
    Serial.print("The range is : ");
    Serial.print(button_num ); 
    Serial.print("to");
    Serial.println(head);
    }
    else if(guess_num == correct){
      Serial.println("Bingo!!!!!");
      }
    clearBuffer();
}

void clearBuffer() {
  for (int i = 0; i < 8; i++) {
    buffer[i] = '\0'; // Set all elements to null character
  }
  pos = 0; // Reset position to 0
}
