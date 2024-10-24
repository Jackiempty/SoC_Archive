#include <Keypad.h>   //引用Keypad函式庫
#include <Password.h> //引用Password函式庫
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
Password password = Password("20230920");
char buffer[8];
int pos = 0;

    /* Do something */

void setup()
{  
  Serial.begin(9600);
  // set(password);
}

void loop()
{
//輸入答案
  char customKey = myKeypad.getKey();
    if (customKey != NO_KEY && customKey!='#'){
      if (pos == 8) {
        Serial.println("buffer full");
      }
      else {
        buffer[pos] = customKey;
        delay(100);
        pos++;
      }
    }
    
    

  if (customKey){
    Serial.println(customKey);

//判斷答案正確性
    if(customKey == '#')
    {
      True_OR_False(8);
    }
  }
}

void True_OR_False(int buffer_index)
{
  for(int i=0; i<buffer_index; i++) password.append(buffer[i]);
  
  if( password.evaluate()==1 )
  {
    Serial.println("Correct");
    /* Do something */
  }
  else if( password.evaluate()==0 )
  {
    Serial.println("Incorrect!");
    /* Do something */
  }
  /* Do something */
  password.reset();
  clearBuffer();
}

void clearBuffer() {
  for (int i = 0; i < 8; i++) {
    buffer[i] = '\0'; // Set all elements to null character
  }
  pos = 0; // Reset position to 0
}
