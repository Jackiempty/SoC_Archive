#include <SPI.h>
char buff [50];
volatile byte indx;
volatile boolean process;

String textSend="";
String textReceive="";

void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); //設定主入從出
   SPCR |= _BV(SPE); //開啟從機的SPI通訊
   SPCR |= _BV(SPIE); // turn on interrupts
   indx = 0;     // buffer 裡頭為空
   process = false;
   SPI.attachInterrupt(); //啟用中斷函式
}
ISR (SPI_STC_vect){   //SPI中斷程序
   byte c = SPDR;     //從SPI Data Register獲取資料(byte)
    
  // add to buffer if room
  if (indx < sizeof buff)
  {
    buff [indx++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process = true;
      
  }  // end of room available
  
}

void loop (void) {    // 等待中斷函式回傳true
  if (process)
  {
    buff [indx] = 0;  
    Serial.println (buff);
    indx = 0;
    process = false;
  }  // end of flag set
    
}